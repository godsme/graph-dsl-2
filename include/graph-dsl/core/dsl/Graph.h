//
// Created by Darwin Yuan on 2022/9/11.
//

#ifndef GRAPH_7C34E86C03DE4658811BA811C93A8D72
#define GRAPH_7C34E86C03DE4658811BA811C93A8D72

#include <maco/basic.h>
#include <maco/map.h>
#include <holo/holo.h>
#include <graph-dsl/core/dsl/SubGraphSelector.h>

namespace graph_dsl {
    template<typename ... SELECTOR>
    struct Graph {
        constexpr static auto ALL_NON_LEAF_NODES = \
            holo::make_list(SubGraphSelector<SELECTOR>::SubGraph::ALL_NON_LEAF_NODES ...)
          | holo::flatten()
          | holo::unique();
    };
}

namespace graph_dsl::detail {
    template<typename, typename ... SUB_GRAPH_SELECTOR>
    using Graph = graph_dsl::Graph<SUB_GRAPH_SELECTOR...>;
}

#define __sUb_gRaPh_each_condition(x) , auto x
#define __sUb_gRaPh_conditions(...) __MACO_map(__sUb_gRaPh_each_condition, __VA_ARGS__)
#define __g_GRAPH(...) graph_dsl::detail::Graph<void __sUb_gRaPh_conditions(__VA_ARGS__)>

#endif //GRAPH_7C34E86C03DE4658811BA811C93A8D72
