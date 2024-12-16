#include <optional>
#include <span>
#include <bitcoinfuzz/basemodule.h>


namespace bitcoinfuzz
{
    namespace module
    {
        class Btcd : public BaseModule
        {
        public:
            Btcd(void);
            std::optional<bool> script_eval(const std::vector<uint8_t>& input_data, unsigned int flags, size_t version) const override;
            ~Btcd() noexcept override = default;
        };

    }
}