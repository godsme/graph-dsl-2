//
// Created by Darwin Yuan on 2022/9/4.
//

#ifndef GRAPH_DA38DD99521046FB99DF8E6597BBA9A1
#define GRAPH_DA38DD99521046FB99DF8E6597BBA9A1

#include <graph-dsl/core/dsl/node_like/NodeLikeTrait.h>
#include <graph-dsl/core/dsl/node_like/NodeLikeRef.h>
#include <graph-dsl/core/dsl/node_like/NodeLikeFork.h>
#include <graph-dsl/core/dsl/node_like/NodeLikeEither.h>
#include <graph-dsl/core/dsl/node_like/NodeLikeMaybe.h>
#include <graph-dsl/Status.h>
#include <cstddef>

namespace graph_dsl {
    struct GraphContext;

    template<typename T>
    struct GraphPort;

    template<typename PORT, typename NODE_LIKE>
    struct GraphPort<auto (PORT) -> NODE_LIKE> final {
        using PortType = PORT;
        using NodeLikeType = typename NodeLikeTrait<NODE_LIKE>::Type;
        constexpr static auto NODE_LIST = NodeLikeType::NODE_LIST;

        template<typename NODE_CB_TUPLE>
        struct InstanceType {
            auto Enabled() -> bool { return m_nodeLike.Enabled(); }

            auto Build(GraphContext &context) -> Status {
                return m_nodeLike.Build(context);
            }

            auto Release(GraphContext &context) {
                m_nodeLike.Release(context);
            }

        private:
            using NodeLike = typename NodeLikeType::template InstanceType<NODE_CB_TUPLE>;
            NodeLike m_nodeLike;
        };
    };
}

#endif //GRAPH_DA38DD99521046FB99DF8E6597BBA9A1
