//
// Created by Darwin Yuan on 2022/9/4.
//

#ifndef GRAPH_29FE1F07A2B4476FA59BCE612F0E654D
#define GRAPH_29FE1F07A2B4476FA59BCE612F0E654D

#include <graph-dsl/core/dsl/node_like/NodeLikeTrait.h>
#include <graph-dsl/Status.h>
#include <maco/basic.h>
#include <holo/holo.h>
#include <variant>

namespace graph_dsl {
    struct GraphContext;

    template<typename COND, typename NODE_LIKE_1, typename NODE_LIKE_2>
    struct NodeLikeEither final {
        using DecoratedNode1 = typename NodeLikeTrait<NODE_LIKE_1>::Type;
        using DecoratedNode2 = typename NodeLikeTrait<NODE_LIKE_2>::Type;

        constexpr static auto NODE_LIST = holo::concat( DecoratedNode1::NODE_LIST
                                                      , DecoratedNode2::NODE_LIST);

        template<typename NODE_CB_TUPLE>
        struct InstanceType {
        private:
            template<std::size_t FROM, std::size_t TO>
            auto Transfer(GraphContext& context) -> Status {
                if(m_node.index() == FROM) {
                    std::get<FROM>(m_node).Release(context);
                }
                if(m_node.index() != TO) {
                    m_node.template emplace<TO>();
                    return std::get<TO>(m_node).Build(context);
                }
                return Status::OK;
            }

            template<size_t N>
            inline auto CleanUp(GraphContext& context) {
                std::get<N>(m_node).Release(context);
                m_node = std::monostate{};
            }

        public:
            auto Enabled() const -> bool { return m_node.index() != 0; }

            auto Build(GraphContext& context) -> Status {
                if(COND::Satisfied(context)) { return Transfer<2, 1>(context); }
                else                         { return Transfer<1, 2>(context); }
            }

            auto Release(GraphContext& context) {
                switch(m_node.index()) {
                    case 1: { CleanUp<1>(context); break; }
                    case 2: { CleanUp<2>(context); break; }
                    default: break;
                }
            }

        private:
            using Node1 = typename DecoratedNode1::template InstanceType<NODE_CB_TUPLE>;
            using Node2 = typename DecoratedNode2::template InstanceType<NODE_CB_TUPLE>;
            std::variant<std::monostate, Node1, Node2> m_node;
        };
    };

    template<typename COND, typename NODE_LIKE_1, typename NODE_LIKE_2>
    struct NodeLikeTrait<NodeLikeEither<COND, NODE_LIKE_1, NODE_LIKE_2>> {
        using Type = NodeLikeEither<COND, NODE_LIKE_1, NODE_LIKE_2>;
    };
}

#define __g_EITHER(...) __MACO_template_type(graph_dsl::NodeLikeEither<__VA_ARGS__>)

#endif //GRAPH_29FE1F07A2B4476FA59BCE612F0E654D
