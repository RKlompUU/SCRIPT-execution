#ifndef SIG_H
#define SIG_H

#include <script/interpreter.h>

#include <iostream>
#include <key.h>

class DisabledSignatureChecker : public BaseSignatureChecker
{
public:
    virtual bool CheckSig(const std::vector<unsigned char>& scriptSig, const std::vector<unsigned char>& vchPubKey, const CScript& scriptCode, SigVersion sigversion) const
    {
      CKey priv;
      CPubKey pub(vchPubKey);
      priv.Set(scriptSig.begin(), scriptSig.end(), false);
      //CPrivKey privKey
      return priv.Load(priv.GetPrivKey(), pub, false);
    }

    virtual bool CheckLockTime(const CScriptNum& nLockTime) const
    {
         return true;
    }

    virtual bool CheckSequence(const CScriptNum& nSequence) const
    {
         return true;
    }

    virtual ~DisabledSignatureChecker() {}
};

#endif
