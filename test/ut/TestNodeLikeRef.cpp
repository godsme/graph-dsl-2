//
// Created by Darwin Yuan on 2022/9/4.
//
#include <graph-dsl/core/dsl/node_like/NodeLikeRef.h>
#include <graph-dsl/core/runtime/NodeCb.h>
#include <catch.hpp>

using namespace graph_dsl;

namespace {
    struct Node : NodeSignature {};
    struct Node1 : NodeSignature {};

    using TupleCb = std::tuple<NodeCb<Node1>, NodeCb<Node>>;
    using NodeRef = typename NodeLikeRef<Node>::InstanceType<TupleCb>;

    static_assert(NodeLikeRef<Node>::NODE_LIST == holo::list_t<Node>);
    static_assert(NodeLikeRef<Node1>::NODE_LIST == holo::list_t<Node1>);
}

SCENARIO("TestGraphNodeRef") {
    NodeRef ref{};
    REQUIRE_FALSE(ref.Enabled());

    GraphContext context{};
    TupleCb nodesCb{};
    context.SwitchSubgraphContext(nodesCb);

    auto&& cb = context.GetNode<TupleCb, 1>();
    REQUIRE_FALSE(cb.Present());

    auto&& cb1 = context.GetNode<TupleCb, 0>();
    REQUIRE_FALSE(cb1.Present());

    REQUIRE(ref.Build(context) == Status::OK);
    REQUIRE(ref.Enabled());
    REQUIRE(cb.Present());
    REQUIRE_FALSE(cb1.Present());

    REQUIRE(ref.Build(context) == Status::OK);
    REQUIRE(ref.Enabled());
    REQUIRE(cb.Present());
    REQUIRE_FALSE(cb1.Present());

    ref.Release(context);
    REQUIRE_FALSE(ref.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE_FALSE(cb1.Present());
}