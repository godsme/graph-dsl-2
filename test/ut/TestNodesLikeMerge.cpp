//
// Created by Darwin Yuan on 2022/9/12.
//
#include <graph-dsl/core/dsl/node_like/NodeLikeEither.h>
#include <graph-dsl/core/dsl/node_like/NodeLikeRef.h>
#include <graph-dsl/core/dsl/node_like/NodeLikeFork.h>
#include <graph-dsl/core/dsl/node_like/NodeLikeMaybe.h>

using namespace graph_dsl;

namespace {
    struct Node1 : NodeSignature {};
    struct Node2 : NodeSignature {};
    struct Node3 : NodeSignature {};
    struct Node4 : NodeSignature {};

    struct Cond{};
    using NodeFork1 = NodeLikeFork<Node2, Node3>;
    using NodeFork2 = NodeLikeFork<Node2, Node4>;
    using Either1 = NodeLikeEither<Cond, Node1, Node4>;

    static_assert(std::is_same_v<decltype(NodeLikeMerge(Node1{}, Node2{})), NodeLikeFork<Node1, Node2>>) ;
    static_assert(std::is_same_v<decltype(NodeLikeMerge(Node1{}, Node1{})), Node1>) ;
    static_assert(std::is_same_v<decltype(NodeLikeMerge(Node1{}, NodeFork1{})), NodeLikeFork<Node1, Node2, Node3>>) ;
    static_assert(std::is_same_v<decltype(NodeLikeMerge(NodeFork1{}, Node1{})), NodeLikeFork<Node2, Node3, Node1>>) ;
    static_assert(std::is_same_v<decltype(NodeLikeMerge(NodeFork1{}, NodeFork2{})), NodeLikeFork<Node2, Node3, Node4>>);
    static_assert(std::is_same_v<decltype(NodeLikeMerge(NodeFork2{}, NodeFork1{})), NodeLikeFork<Node2, Node4, Node3>>);
    static_assert(std::is_same_v<decltype(NodeLikeMerge(Either1{}, NodeFork1{})), NodeLikeFork<Either1, Node2, Node3>>);
}