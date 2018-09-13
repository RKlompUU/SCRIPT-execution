#include <script/interpreter.h>
#include <script/script_error.h>
#include <scrpt_vrfy/sig.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

#include <key.h>
#include <random.h>
#include <init.h>
#include <script/sigcache.h>
#include <validation.h>
#include <util.h>

using namespace std;


static unsigned char gethex(const char *s);
static std::vector<unsigned char> readFile(const char *filename);
static std::vector<unsigned char> readStdin();
static bool eval_script(std::vector<std::vector<unsigned char> >& stack,
                        const CScript& script,
                        unsigned int flags,
                        const BaseSignatureChecker& checker,
                        SigVersion sigversion,
                        ScriptError* serror);
static void createKeySet();

int main(int argc, const char** argv)
{
  //AppInitBasicSetup();
  SHA256AutoDetect();
  RandomInit();

  ECC_Start();
  ECCVerifyHandle pubECCHandle;
  SetupEnvironment();
  SetupNetworking();
  InitSignatureCache();
//  InitScriptExecutionCache();

  //return 0;

  if(!ECC_InitSanityCheck()) {
      cerr << ("Elliptic curve cryptography sanity check failure. Aborting.") << endl;
        ECC_Stop();
      return false;
  }
  if (argc < 2)
  {
    std::cerr << "Provide 2 arguments: [0|<path to input>] <path to output>" << std::endl;
      ECC_Stop();
    return 1;
  }

  if (strcmp(argv[1],"s") == 0)
  {
    createKeySet();
      ECC_Stop();
    return 0;
  }

  vector<unsigned char> scrpt_b;
  if (strcmp(argv[1],"0") == 0)
  {
    scrpt_b = readStdin();
  }
  else
    scrpt_b = readFile(argv[1]);
  vector<unsigned char> out_b = readFile(argv[2]);

  scrpt_b.insert(scrpt_b.end(), out_b.begin(), out_b.end());

  std::vector<std::vector<unsigned char>> stack;
  CScript script(scrpt_b.begin(), scrpt_b.end());
  unsigned int flags = SCRIPT_VERIFY_NONE;
  SigVersion sigVersion = SIGVERSION_BASE;
  ScriptError err;
  //DisabledSignatureChecker sigchecker;
  DisabledSignatureChecker sigchecker;

  cout << "Script validator boot.." << endl;

  for(auto i : script)
    cout << hex << setw(2) << setfill('0') << (unsigned int)i;
  cout << endl;

  //bool EvalScript(std::vector<std::vector<unsigned char> >& stack, const CScript& script, unsigned int flags, const BaseSignatureChecker& checker, SigVersion sigversion, ScriptError* serror)


  if (eval_script(stack, script, flags, sigchecker, sigVersion, &err))
  {
    cout << "Eval: success" << endl;
  }
  else
  {
    cout << "Eval: failure, err: " << ScriptErrorString(err) << endl;
  }

  cout << "Script validator shutdown.." << endl;

    ECC_Stop();
  return 0;
}


static unsigned char gethex(const char *s) {
  //while (isspace(*s)) s++;
  //assert(*s);
  return strtoul(s, NULL, 16);
}

static std::vector<unsigned char> readFile(const char *filename)
{
    std::vector<unsigned char> res;

    // open the file:
    std::streampos fileSize;
    std::ifstream file(filename);

    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string s = buffer.str();
    for( int i = 0; i < fileSize; i+=2 )
    {
      if( s[i] == '\n' )
      {
        i -= 1;
        continue;
      }
      std::string c;
      c += s[i];
      c += s[i+1];
      unsigned char u = gethex(c.c_str());
    //  cout << "c: " << c << ", " << u << endl;
      res.push_back(u);
    }

    return res;
}

static std::vector<unsigned char> readStdin()
{
    std::vector<unsigned char> res;

    std::string s;
    std::getline(std::cin, s);;
    for( unsigned int i = 0; i < s.size(); i+=2 )
    {
      if( s[i] == '\n' )
      {
        i -= 1;
        continue;
      }
      std::string c;
      c += s[i];
      c += s[i+1];
      unsigned char u = gethex(c.c_str());
    //  cout << "c: " << c << ", " << u << endl;
      res.push_back(u);
    }

    return res;
}

static bool eval_script(std::vector<std::vector<unsigned char> >& stack,
                        const CScript& script,
                        unsigned int flags,
                        const BaseSignatureChecker& checker,
                        SigVersion sigversion,
                        ScriptError* serror)
{
  if(!EvalScript(stack, script, flags, checker, sigversion, serror))
    return false;
  if (stack.size() == 0 || !CastToBool(stack.back()))
  {
    *serror = SCRIPT_ERR_EVAL_FALSE;
    return false;
  }
  return true;
}

void createKeySet()
{
  CKey priv;
  priv.MakeNewKey(true);

  CPubKey pub = priv.GetPubKey();
  assert(priv.VerifyPubKey(pub));

  for( unsigned int i = 0; i < priv.size(); i++ )
  {
    unsigned char u = *(priv.begin() + i);
    cout << hex << setw(2) << setfill('0') << u;
  }
}
