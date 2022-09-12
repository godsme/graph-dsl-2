//
// Created by Darwin Yuan on 2022/9/4.
//

#ifndef GRAPH_4D47476CA7D34861A3353572B0F64790
#define GRAPH_4D47476CA7D34861A3353572B0F64790

#include <graph-dsl/core/dsl/GraphPort.h>
#include <graph-dsl/core/dsl/NodeIndex.h>
#include <graph-dsl/util/TupleForEach.h>
#include <graph-dsl/util/Assertions.h>
#include <maco/basic.h>
#include <maco/map_2.h>
#include <holo/holo.h>

namespace graph_dsl {
    template<typename NODE, typename ... PORTS>
    struct GraphNode final {
        using NodeType = NODE;
        constexpr static auto ALL_PORTS = \
             holo::list_t<typename GraphPort<PORTS>::PortType...>
           | holo::unique();

        constexpr static auto DIRECT_DECEDENTS =
                  holo::make_list(GraphPort<PORTS>::NODE_LIST...)
                | holo::flatten()
                | holo::unique();

        template<typename NODE_CB_TUPLE>
        class InstanceType {
            using Ref = NodeIndex<NODE, NODE_CB_TUPLE>;

            auto Build(GraphContext &context) -> Status {
                m_enabled = true;
                GRAPH_EXPECT_SUCC(TupleForeach(m_ports, [&context](auto&& port) { return port.Build(context); }));
                return Status::OK;
            }

            auto Release(GraphContext &context) -> void {
                if(m_enabled) {
                    TupleForeachVoid(m_ports, [&context](auto&& port) { return port.Release(context); });
                    m_enabled = false;
                }
            }

        public:
            auto Refresh(GraphContext &context) -> Status {
                if(Ref::GetNode(context).Present()) {
                    return Build(context);
                } else {
                    Release(context);
                    return Status::OK;
                }
            }

        private:
            std::tuple<typename GraphPort<PORTS>::template InstanceType<NODE_CB_TUPLE> ...> m_ports;
            bool m_enabled{};
        };
    };
}

#define __gRaPh_each_link(x) , auto x
#define __gRaPh_links(node, ...) node __MACO_map_2(__gRaPh_each_link, __VA_ARGS__)
#define __sUb_gRaPh_node(...) graph_dsl::GraphNode<__gRaPh_links(__VA_ARGS__)>
#define __g_NODE(...) graph_dsl::GraphNode<__gRaPh_links(__VA_ARGS__)>

#endif //GRAPH_4D47476CA7D34861A3353572B0F64790
