//
// Created by Darwin Yuan on 2022/9/11.
//
#include <graph-dsl/core/dsl/GraphNode.h>

namespace {
    struct Node1 {};
    struct Node2 : graph_dsl::NodeSignature {};
    struct Node3 : graph_dsl::NodeSignature {};
    struct Node4 : graph_dsl::NodeSignature {};
    struct Port1{};
    struct Port2{};
    struct Cond{};

    using Node = __g_NODE(Node1,
                            (Port1) -> __g_FORK(Node2, Node3),
                            (Port2) -> __g_EITHER(Cond, Node3, Node4));

    static_assert(Node::DIRECT_DECEDENTS == holo::list_t<Node2, Node3, Node4>);
}