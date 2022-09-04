//
// Created by Darwin Yuan on 2022/7/3.
//
#include <graph-dsl/core/dsl/node_like/NodeLikeEither.h>
#include <graph-dsl/core/dsl/node_like/NodeLikeRef.h>
#include <graph-dsl/core/runtime/NodeCb.h>
#include <catch.hpp>

using namespace graph_dsl;

namespace {
    static bool satisfied = false;
    struct Cond {
        static auto Satisfied(GraphContext&) noexcept -> bool {
            return satisfied;
        }
    };

    struct Node : NodeSignature {};
    struct Node1 : NodeSignature {};
    struct Node2 : NodeSignature {};

    using TupleCb = std::tuple<NodeCb<Node>, NodeCb<Node2>, NodeCb<Node1>>;

    using EitherType = __g_EITHER(Cond, Node1, Node2);
    using Either = typename EitherType::InstanceType<TupleCb>;

    static_assert(__g_EITHER(Cond, Node1, Node2)::NODE_LIST == holo::list_t<Node1, Node2>);
    static_assert(__g_EITHER(Cond, Node2, Node1)::NODE_LIST == holo::list_t<Node2, Node1>);
}

SCENARIO("TestGraphNodeEither") {
    satisfied = false;

    Either either{};
    REQUIRE_FALSE(either.Enabled());

    GraphContext context{};
    TupleCb nodesCb{};
    context.SwitchSubgraphContext(nodesCb);

    auto&& cb = context.GetNode<TupleCb, 0>();
    REQUIRE_FALSE(cb.Present());

    auto&& cb1 = context.GetNode<TupleCb, 2>();
    REQUIRE_FALSE(cb1.Present());

    auto&& cb2 = context.GetNode<TupleCb, 1>();
    REQUIRE_FALSE(cb2.Present());

    REQUIRE(either.Build(context) == Status::OK);
    REQUIRE(either.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE_FALSE(cb1.Present());
    REQUIRE(cb2.Present());

    REQUIRE(either.Build(context) == Status::OK);
    REQUIRE(either.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE_FALSE(cb1.Present());
    REQUIRE(cb2.Present());

    satisfied = true;
    REQUIRE(either.Build(context) == Status::OK);
    REQUIRE(either.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE_FALSE(cb2.Present());
    REQUIRE(cb1.Present());

    REQUIRE(either.Build(context) == Status::OK);
    REQUIRE(either.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE_FALSE(cb2.Present());
    REQUIRE(cb1.Present());

    either.Release(context);
    REQUIRE_FALSE(either.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE_FALSE(cb1.Present());
    REQUIRE_FALSE(cb2.Present());
}