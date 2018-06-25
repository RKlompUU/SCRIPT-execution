#include <script/interpreter.h>
#include <script/script_error.h>
#include "sig.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


static unsigned char gethex(const char *s) {
  //while (isspace(*s)) s++;
  //assert(*s);
  return strtoul(s, NULL, 16);
}

std::vector<unsigned char> readFile(const char *filename)
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


int main(int argc, const char** argv)
{
  if (argc < 3)
    return 1;

  vector<unsigned char> scrpt_b = readFile(argv[1]);
  vector<unsigned char> out_b = readFile(argv[2]);

  scrpt_b.insert(scrpt_b.end(), out_b.begin(), out_b.end());

  std::vector<std::vector<unsigned char>> stack;
  CScript script(scrpt_b.begin(), scrpt_b.end());
  unsigned int flags = SCRIPT_VERIFY_NONE;
  SigVersion sigVersion = SIGVERSION_BASE;
  ScriptError err;
  DisabledSignatureChecker sigchecker;

  cout << "Script validator boot.." << endl;

  for(auto i : script)
    cout << hex << (unsigned int)i;
  cout << endl;

  //bool EvalScript(std::vector<std::vector<unsigned char> >& stack, const CScript& script, unsigned int flags, const BaseSignatureChecker& checker, SigVersion sigversion, ScriptError* serror)

  if (EvalScript(stack, script, flags, sigchecker, sigVersion, &err))
    cout << "Eval: success" << endl;
  else
  {
    cout << "Eval: failure, err: " << ScriptErrorString(err) << endl;
  }

  cout << "Script validator shutdown.." << endl;

  return 0;
}
