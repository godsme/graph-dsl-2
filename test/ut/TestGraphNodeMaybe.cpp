////
//// Created by Darwin Yuan on 2022/7/3.
////
//#include <graph-dsl/core/dsl/primitive/GraphNodeMaybe.h>
//#include <graph-dsl/core/dsl/primitive/GraphNodeRef.h>
//#include <graph-dsl/core/runtime/NodeCb.h>
//#include <catch.hpp>
//
//using namespace graph_dsl;
//
//namespace {
//    static bool satisfied = false;
//    struct Cond {
//        static auto Satisfied(GraphContext&) noexcept -> bool {
//            return satisfied;
//        }
//    };
//
//    struct Node : NodeSignature {
//    };
//
//    struct Node1 : NodeSignature {
//    };
//
//    using TupleCb = std::tuple<NodeCb<Node1>, NodeCb<Node>>;
//
//    using Maybe = typename GraphNodeMaybe<Cond, GraphNodeRef<Node>>::InstanceType<TupleCb>;
//}
//
//SCENARIO("TestGraphNodeMaybe") {
//
//}