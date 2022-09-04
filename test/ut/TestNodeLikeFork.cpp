//
// Created by Darwin Yuan on 2022/9/4.
//
#include <graph-dsl/core/dsl/node_like/NodeLikeFork.h>
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

    static bool satisfied1 = false;
    struct Cond1 {
        static auto Satisfied(GraphContext&) noexcept -> bool {
            return satisfied1;
        }
    };

    struct Node : NodeSignature {};
    struct Node1 : NodeSignature {};
    struct Node2 : NodeSignature {};
    struct Node3 : NodeSignature {};

    using TupleCb = std::tuple<NodeCb<Node3>, NodeCb<Node1>, NodeCb<Node>, NodeCb<Node2>>;

    using MaybeType = __g_MAYBE(Cond, Node);
    using Maybe = typename MaybeType::InstanceType<TupleCb>;

    using MaybeType1 = __g_MAYBE(Cond1, Node1);
    using Maybe1 = typename MaybeType1::InstanceType<TupleCb>;

    static_assert(__g_FORK(Node1, Node2)::NODE_LIST == holo::list_t<Node1, Node2>);
    static_assert(__g_FORK(MaybeType, MaybeType1)::NODE_LIST == holo::list_t<Node, Node1>);
}

SCENARIO("TestGraphNodeFork") {
    satisfied = false;
    satisfied1 = false;

    __g_FORK(MaybeType, MaybeType1)::InstanceType<TupleCb> fork{};
    REQUIRE_FALSE(fork.Enabled());

    GraphContext context{};
    TupleCb nodesCb{};
    context.SwitchSubgraphContext(nodesCb);

    auto&& cb = context.GetNode<TupleCb, 2>();
    REQUIRE_FALSE(cb.Present());

    auto&& cb1 = context.GetNode<TupleCb, 1>();
    REQUIRE_FALSE(cb1.Present());

    auto&& cb2 = context.GetNode<TupleCb, 3>();
    REQUIRE_FALSE(cb2.Present());

    auto&& cb3 = context.GetNode<TupleCb, 0>();
    REQUIRE_FALSE(cb3.Present());

    REQUIRE(fork.Build(context) == Status::OK);
    REQUIRE_FALSE(fork.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE_FALSE(cb1.Present());
    REQUIRE_FALSE(cb2.Present());
    REQUIRE_FALSE(cb3.Present());

    REQUIRE(fork.Build(context) == Status::OK);
    REQUIRE_FALSE(fork.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE_FALSE(cb1.Present());
    REQUIRE_FALSE(cb2.Present());
    REQUIRE_FALSE(cb3.Present());

    satisfied = true;
    REQUIRE(fork.Build(context) == Status::OK);
    REQUIRE(fork.Enabled());
    REQUIRE(cb.Present());
    REQUIRE_FALSE(cb1.Present());
    REQUIRE_FALSE(cb2.Present());
    REQUIRE_FALSE(cb3.Present());

    satisfied1 = true;
    REQUIRE(fork.Build(context) == Status::OK);
    REQUIRE(fork.Enabled());
    REQUIRE(cb.Present());
    REQUIRE(cb1.Present());
    REQUIRE_FALSE(cb2.Present());
    REQUIRE_FALSE(cb3.Present());

    satisfied = false;
    REQUIRE(fork.Build(context) == Status::OK);
    REQUIRE(fork.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE(cb1.Present());
    REQUIRE_FALSE(cb2.Present());
    REQUIRE_FALSE(cb3.Present());

    satisfied1 = false;
    REQUIRE(fork.Build(context) == Status::OK);
    REQUIRE_FALSE(fork.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE_FALSE(cb1.Present());
    REQUIRE_FALSE(cb2.Present());
    REQUIRE_FALSE(cb3.Present());

    satisfied1 = true;
    REQUIRE(fork.Build(context) == Status::OK);
    REQUIRE(fork.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE(cb1.Present());
    REQUIRE_FALSE(cb2.Present());
    REQUIRE_FALSE(cb3.Present());

    fork.Release(context);
    REQUIRE_FALSE(fork.Enabled());
    REQUIRE_FALSE(cb.Present());
    REQUIRE_FALSE(cb1.Present());
    REQUIRE_FALSE(cb2.Present());
    REQUIRE_FALSE(cb3.Present());
}