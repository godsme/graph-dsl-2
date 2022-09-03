//
// Created by Darwin Yuan on 2022/9/4.
//

#ifndef GRAPH_1EA633038873418F8E38A182C6BD53D2
#define GRAPH_1EA633038873418F8E38A182C6BD53D2

#include <graph-dsl/util/TupleElementIndex.h>
#include <graph-dsl/core/GraphContext.h>

namespace graph_dsl {
    struct GraphContext;

    template <typename NODE, typename NODES>
    struct NodeIndex {
    private:
        template<typename T> struct Trait { using type = typename T::NodeType; };
        constexpr static int INDEX = TupleElementIndex<NODE, NODES, Trait>;
        static_assert(INDEX >= 0, "no type in tuple");

    public:
        inline static auto GetNode(GraphContext& context) -> decltype(auto) {
            return (context.GetNode<NODES, INDEX>());
        }

        inline static auto GetRootNode(GraphContext& context) -> decltype(auto) {
            return (context.GetRootNode<NODES, INDEX>());
        }
    };
}

#endif //GRAPH_1EA633038873418F8E38A182C6BD53D2
