//
// Created by Darwin Yuan on 2022/7/3.
//
#include <graph-dsl/core/dsl/node_like/NodeLikeMaybe.h>
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

    using TupleCb = std::tuple<NodeCb<Node1>, NodeCb<Node>>;

    using MaybeType = __g_MAYBE(Cond, Node);
    using Maybe = typename MaybeType::InstanceType<TupleCb>;

    static_assert(__g_MAYBE(Cond, Node)::NODE_LIST == holo::list_t<Node>);
    static_assert(__g_MAYBE(Cond, Node1)::NODE_LIST == holo::list_t<Node1>);
}

SCENARIO("TestGraphNodeMaybe") {
    Maybe maybe{};
    REQUIRE_FALSE(maybe.Enabled());

    GraphContext context{};
    TupleCb nodesCb{};
    context.SwitchSubgraphContext(nodesCb);

    auto&& cb = context.GetNode<TupleCb, 1>();
    REQUIRE_FALSE(cb.Present());

    auto&& cb1 = context.GetNode<TupleCb, 0>();
    REQUIRE_FALSE(cb1.Present());

    satisfied = false;
    REQUIRE(maybe.Build(context) == Status::OK);
    REQUIRE_FALSE(maybe.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE_FALSE(cb1.Present());

    satisfied = true;
    REQUIRE(maybe.Build(context) == Status::OK);
    REQUIRE(maybe.Enabled());
    REQUIRE(cb.Present());
    REQUIRE_FALSE(cb1.Present());

    REQUIRE(maybe.Build(context) == Status::OK);
    REQUIRE(maybe.Enabled());
    REQUIRE(cb.Present());
    REQUIRE_FALSE(cb1.Present());

    maybe.Release(context);
    REQUIRE_FALSE(maybe.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE_FALSE(cb1.Present());
}