//
// Created by Darwin Yuan on 2022/9/5.
//

#ifndef GRAPH_B762BC06ED16426798A6E4BCFBC2FC50
#define GRAPH_B762BC06ED16426798A6E4BCFBC2FC50

#include <graph-dsl/core/dsl/GraphNode.h>
#include <holo/holo.h>
#include <maco/basic.h>
#include <maco/map.h>

namespace graph_dsl {
    template<typename ... NODES>
    struct SubGraph {
        constexpr static auto ALL_NON_LEAF_NODES = \
             holo::list_t<typename NODES::NodeType...>
           | holo::unique();
    };
}

namespace graph_dsl::detail {
    template<typename, typename ... NODES>
    using SubGraph = graph_dsl::SubGraph<NODES...>;
};

#define __sUb_gRaPh_each_node(x) , __sUb_gRaPh_node x
#define __sUb_gRaPh_nodes(...) __MACO_map(__sUb_gRaPh_each_node, __VA_ARGS__)
#define __g_SUB_GRAPH(...) graph_dsl::detail::SubGraph<void __sUb_gRaPh_nodes(__VA_ARGS__)>

#endif //GRAPH_B762BC06ED16426798A6E4BCFBC2FC50
