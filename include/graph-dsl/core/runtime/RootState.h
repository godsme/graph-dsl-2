//
// Created by Darwin Yuan on 2022/9/4.
//

#ifndef GRAPH_789E0521B37F43FEBC97D47C7513DA6A
#define GRAPH_789E0521B37F43FEBC97D47C7513DA6A

#include <graph-dsl/core/runtime/DeviceInfo.h>

namespace graph_dsl {
    struct RootState {
        DeviceInfo const* deviceInfo{};
        std::size_t size{};

        auto GetDeviceInfo(uint8_t deviceId) const -> struct DeviceInfo const* {
            for(size_t i=0; i < size; i++) {
                if(deviceInfo[i].deviceId == deviceId) {
                    return deviceInfo + i;
                }
            }
            return nullptr;
        }

        auto CleanUp() {
            deviceInfo = nullptr;
            size = 0;
        }
    };

    inline constexpr auto operator==(RootState const& lhs, RootState const& rhs) noexcept -> bool {
        if(lhs.size != rhs.size) return false;
        for(auto i=0; i<lhs.size; i++) {
            if(lhs.deviceInfo[i] != rhs.deviceInfo[i]) return false;
        }
        return true;
    }

    inline constexpr auto operator!=(RootState const& lhs, RootState const& rhs) noexcept -> bool {
        return !operator==(lhs, rhs);
    }
}

#endif //GRAPH_789E0521B37F43FEBC97D47C7513DA6A
