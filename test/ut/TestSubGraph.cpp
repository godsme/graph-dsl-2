//
// Created by Darwin Yuan on 2022/9/11.
//
#include <graph-dsl/core/dsl/SubGraph.h>
#include <catch.hpp>

namespace {
    struct Root1 : graph_dsl::NodeSignature {};
    struct Node1 : graph_dsl::NodeSignature {};
    struct Node2 : graph_dsl::NodeSignature {};
    struct Node3 : graph_dsl::NodeSignature {};
    struct Node4 : graph_dsl::NodeSignature {};
    struct Node5 : graph_dsl::NodeSignature {};
    struct Node6 : graph_dsl::NodeSignature {};
    struct Port1{};
    struct Port2{};
    struct Port3{};
    struct Port4{};
    struct Port5{};
    struct Cond1{};
    struct Cond2{};

    using Subgraph1 = __g_SUB_GRAPH(
               (Root1,
                    (Port1) -> __g_FORK(Node2, Node3),
                    (Port2) -> __g_EITHER(Cond1, Node3, Node1)),
               (Node1,
                    (Port3) -> Node2,
                    (Port4) -> __g_MAYBE(Cond2, Node4)),
               (Root1,
                    (Port1) -> Node5,
                    (Port5) -> Node6)
            );

    static_assert(Subgraph1::ALL_NON_LEAF_NODES == holo::list_t<Root1, Node1>);
}