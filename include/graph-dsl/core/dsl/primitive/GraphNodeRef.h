//
// Created by Darwin Yuan on 2022/7/3.
//

#ifndef GRAPH_B336B490BFCD4CC1BCB8267D5467D155
#define GRAPH_B336B490BFCD4CC1BCB8267D5467D155

#include <graph-dsl/core/dsl/primitive/GraphNodeTrait.h>
#include <graph-dsl/core/dsl/NodeIndex.h>
#include <graph-dsl/Status.h>
#include <holo/holo.h>

namespace graph_dsl {
    struct GraphContext;

    struct NodeSignature {};

    template <typename NODE>
    struct GraphNodeRef {
        constexpr static auto NODE_LIST = holo::list_t<NODE>;

        template<typename CB_TUPLE>
        struct InstanceType : NodeIndex<NODE, CB_TUPLE> {
            using Parent = NodeIndex<NODE, CB_TUPLE>;

            auto Build(GraphContext& context) -> Status {
                if(!m_enabled) {
                    Parent::GetNode(context).AddRef();
                    m_enabled = true;
                }
                return Status::OK;
            }

            auto Release(GraphContext& context) -> void {
                if(m_enabled) {
                    Parent::GetNode(context).Release();
                    m_enabled = false;
                }
            }

            auto Enabled() const -> bool { return m_enabled; }

        private:
            bool m_enabled{false};
        };
    };

    template<typename NODE>
    struct GraphNodeTrait<NODE, std::enable_if_t<std::is_base_of_v<NodeSignature, NODE>>> {
        using Type = GraphNodeRef<NODE>;
    };
}

#endif //GRAPH_B336B490BFCD4CC1BCB8267D5467D155
