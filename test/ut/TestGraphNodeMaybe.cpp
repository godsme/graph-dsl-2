//
// Created by Darwin Yuan on 2022/7/3.
//
#include <graph-dsl/core/dsl/primitive/GraphNodeMaybe.h>
#include <graph-dsl/core/dsl/primitive/GraphNodeRef.h>
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

    using MaybeType = GraphNodeMaybe<Cond, Node>;
    using Maybe = typename MaybeType::InstanceType<TupleCb>;
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