#include <optional>
#include <span>
#include <bitcoinfuzz/basemodule.h>


namespace bitcoinfuzz
{
    namespace module
    {
        class Bitcoin : public BaseModule
        {
        public:
            Bitcoin(void);
            std::optional<bool> script_parse(std::span<const uint8_t> buffer) const override;
            std::optional<std::vector<bool>> deserialize_block(std::span<const uint8_t> buffer) const override;
            ~Bitcoin() noexcept override = default;
        };

    }
}
