//
// Created by Darwin Yuan on 2022/9/4.
//

#ifndef GRAPH_DA38DD99521046FB99DF8E6597BBA9A1
#define GRAPH_DA38DD99521046FB99DF8E6597BBA9A1

#include <graph-dsl/core/dsl/node_like/NodeLikeTrait.h>
#include <graph-dsl/core/GraphContext.h>
#include <graph-dsl/Status.h>

namespace graph_dsl {
    template<typename T>
    struct GraphPort;

    template<typename PORT, typename NODE_LIKE>
    struct GraphPort<auto (PORT) -> NODE_LIKE> final {
        using NodeLikeType = typename NodeLikeTrait<NODE_LIKE>::Type;
        constexpr static auto NODE_LIST = NODE_LIKE::NODE_LIST;

        template<typename TUPLE>
        struct InstanceType {
            auto Enabled() -> bool { return m_downStreamNode.Enabled(); }

            auto Build(GraphContext &context) -> Status {
                return m_downStreamNode.Build(context);
            }

            auto Release(GraphContext &context) {
                m_downStreamNode.Release(context);
            }

        private:
            typename NodeLikeType::template InstanceType<TUPLE>  m_downStreamNode;
        };
    };
}

#endif //GRAPH_DA38DD99521046FB99DF8E6597BBA9A1
