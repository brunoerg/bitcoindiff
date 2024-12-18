#include <span>

#include "module.h"
#include "descriptor.h"
#include "chainparams.h"
#include "script/script.h"
#include "script/interpreter.h"
#include "primitives/block.h"
#include "primitives/transaction.h"
#include "consensus/validation.h"
#include "util/chaintype.h"
#include "streams.h"
#include "validation.h"

namespace {
    class FuzzedSignatureChecker : public BaseSignatureChecker
    {
    public:
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
    CScript script(input_data.begin(), input_data.end());
    if (script.empty()) return std::nullopt;

    // Skip sequence and locktime
    auto hex_str{HexStr(script)};
    if (hex_str.find("b1") != std::string::npos || hex_str.find("b2") != std::string::npos) return std::nullopt;

    std::vector<std::vector<unsigned char>> stack;
    SigVersion sig_version = (version == 0) ? SigVersion::BASE : SigVersion::WITNESS_V0;

    return EvalScript(stack, script, 0, FuzzedSignatureChecker(), sig_version, nullptr);
}

std::optional<bool> Bitcoin::descriptor_parse(std::string str) const
{
    // TODO: Move it to a constructor
    static ECC_Context ecc_context{};
    SelectParams(ChainType::MAIN);


    FlatSigningProvider signing_provider;
    std::string error;
    const auto desc = Parse(str, signing_provider, error, /*require_checksum=*/false);
    return !desc.empty();
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
