#ifndef SIG_H
#define SIG_H

#include <script/interpreter.h>

class DisabledSignatureChecker : public BaseSignatureChecker
{
public:
    virtual bool CheckSig(const std::vector<unsigned char>& scriptSig, const std::vector<unsigned char>& vchPubKey, const CScript& scriptCode, SigVersion sigversion) const
    {
        return true;
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
