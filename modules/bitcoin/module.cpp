#include <span>

#include "module.h"
#include "script/script.h"
#include "script/interpreter.h"
#include "primitives/block.h"
#include "primitives/transaction.h"
#include "consensus/validation.h"
#include "streams.h"
#include "validation.h"

namespace {
    class FuzzedSignatureChecker : public BaseSignatureChecker
    {
    public:
        bool CheckECDSASignature(const std::vector<unsigned char>& scriptSig, const std::vector<unsigned char>& vchPubKey, const CScript& scriptCode, SigVersion sigversion) const override
        {
            return true;
        }

        bool CheckSchnorrSignature(Span<const unsigned char> sig, Span<const unsigned char> pubkey, SigVersion sigversion, ScriptExecutionData& execdata, ScriptError* serror = nullptr) const override
        {
            return true;
        }
        bool CheckLockTime(const CScriptNum& nLockTime) const override
        {
            return true;
        }

        bool CheckSequence(const CScriptNum& nSequence) const override
        {
            return true;
        }

        virtual ~FuzzedSignatureChecker() = default;
    };
}

namespace bitcoinfuzz {
namespace module {
Bitcoin::Bitcoin(void) : BaseModule("Bitcoin") {}

std::optional<bool> Bitcoin::script_parse(std::span<const uint8_t> buffer) const
{
    DataStream ds{buffer};
    CScript script;
    try {
        ds >> script;
    } catch (const std::ios_base::failure& e) {
        return false;
    }
    if (script.IsUnspendable()) return false;
    return true;
}

std::optional<bool> Bitcoin::script_eval(const std::vector<uint8_t>& input_data, unsigned int flags, size_t version) const
{
    CScript script_sig(input_data.begin(), input_data.end());
    std::vector<std::vector<unsigned char>> stack;
    SigVersion sig_version;
    if (version == 0) {
        sig_version = SigVersion::BASE;
    } else {
        sig_version = SigVersion::WITNESS_V0;
    }
    return EvalScript(stack, script_sig, flags, FuzzedSignatureChecker(), sig_version, nullptr);
}

std::optional<std::vector<bool>> Bitcoin::deserialize_block(std::span<const uint8_t> buffer) const
{
    DataStream ds{buffer};
    CBlock block;
    std::vector<bool> res{};
    try {
        ds >> TX_WITH_WITNESS(block);
    } catch (const std::ios_base::failure&) {
        return res;
    }
    if (block.vtx.empty()) {
        res.push_back(false);
    } else {
        res.push_back(!IsBlockMutated(block, true));
    }
    return res;
}

} // namespace module
} // namespace bitcoinfuzz
