//
// Created by Darwin Yuan on 2022/9/4.
//

#ifndef GRAPH_ACA3139CE0F74224ACE31A4602232F2D
#define GRAPH_ACA3139CE0F74224ACE31A4602232F2D

#include <cstdint>
#include <tuple>

namespace graph_dsl {
    struct DeviceInfo {
        const uint8_t deviceId;
        const bool isPreview;

        inline constexpr auto Tie() const noexcept {
            return std::tie(deviceId, isPreview);
        }
    };

    inline constexpr auto operator==(DeviceInfo const& lhs, DeviceInfo const& rhs) noexcept -> bool {
        return lhs.Tie() == rhs.Tie();
    }

    inline constexpr auto operator!=(DeviceInfo const& lhs, DeviceInfo const& rhs) noexcept -> bool {
        return !operator==(lhs, rhs);
    }

    inline constexpr auto operator<(DeviceInfo const& lhs, DeviceInfo const& rhs) noexcept -> bool {
        return lhs.Tie() < rhs.Tie();
    }

    inline constexpr auto operator<=(DeviceInfo const& lhs, DeviceInfo const& rhs) noexcept -> bool {
        return lhs.Tie() <= rhs.Tie();
    }

    inline constexpr auto operator>(DeviceInfo const& lhs, DeviceInfo const& rhs) noexcept -> bool {
        return lhs.Tie() > rhs.Tie();
    }

    inline constexpr auto operator>=(DeviceInfo const& lhs, DeviceInfo const& rhs) noexcept -> bool {
        return lhs.Tie() >= rhs.Tie();
    }
}

#endif //GRAPH_ACA3139CE0F74224ACE31A4602232F2D
