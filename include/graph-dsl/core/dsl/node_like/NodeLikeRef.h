//
// Created by Darwin Yuan on 2022/7/3.
//

#ifndef GRAPH_37B623D6E7FF463B8066085002964996
#define GRAPH_37B623D6E7FF463B8066085002964996

#include <graph-dsl/core/dsl/node_like/NodeLikeTrait.h>
#include <graph-dsl/core/dsl/NodeIndex.h>
#include <graph-dsl/Status.h>
#include <holo/holo.h>

namespace graph_dsl {
    struct GraphContext;

    struct NodeSignature {};

    template <typename NODE>
    struct NodeLikeRef {
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
    struct NodeLikeTrait<NODE, std::enable_if_t<std::is_base_of_v<NodeSignature, NODE>>> {
        using Type = NodeLikeRef<NODE>;
    };
}

#endif //GRAPH_37B623D6E7FF463B8066085002964996
