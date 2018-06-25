#include <script/interpreter.h>
#include "sig.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char** argv)
{
  if (argc < 2)
    return 1;

  std::ifstream input(argv[1], std::ios::binary );
  // copies all data into buffer
  std::vector<char> buffer((
          std::istreambuf_iterator<char>(input)),
          (std::istreambuf_iterator<char>()));

  for(auto i : buffer)
    cout << i << endl;
  return 0;


  std::vector<std::vector<unsigned char>> stack;
  CScript script;
  unsigned int flags = SCRIPT_VERIFY_NONE;
  SigVersion sigVersion = SIGVERSION_BASE;
  ScriptError err;
  DisabledSignatureChecker sigchecker;

  cout << "Script validator boot.." << endl;

  //bool EvalScript(std::vector<std::vector<unsigned char> >& stack, const CScript& script, unsigned int flags, const BaseSignatureChecker& checker, SigVersion sigversion, ScriptError* serror)

  if (EvalScript(stack, script, flags, sigchecker, sigVersion, &err))
    cout << "Eval: success" << endl;
  else
  {
    cout << "Eval: failure, err: " << err << endl;
  }

  cout << "Script validator shutdown.." << endl;

  return 0;
}
