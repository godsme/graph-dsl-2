//
// Created by Darwin Yuan on 2022/7/3.
//

#ifndef GRAPH_DSL_2_776A733183E6411199F785D220F1CD54
#define GRAPH_DSL_2_776A733183E6411199F785D220F1CD54

#include <graph-dsl/core/dsl/node_like/NodeLikeTrait.h>
#include <graph-dsl/Status.h>
#include <maco/basic.h>
#include <optional>

namespace graph_dsl {
    struct GraphContext;

    template<typename COND, typename NODE_LIKE>
    struct NodeLikeMaybe final {
    private:
        using DecoratedNode = typename NodeLikeTrait<NODE_LIKE>::Type;
    public:
        constexpr static auto NODE_LIST = DecoratedNode::NODE_LIST;

        template<typename NODE_CB_TUPLE>
        struct InstanceType {
            auto Enabled() const -> bool { return m_node.has_value(); }

            auto Build(GraphContext& context) -> Status {
                if(COND::Satisfied(context)) {
                    return DoBuild(context);
                } else {
                    Release(context);
                    return Status::OK;
                }
            }

            auto Release(GraphContext& context) {
                if(m_node) {
                    m_node->Release(context);
                    m_node.reset();
                }
            }

        private:
            auto DoBuild(GraphContext& context) -> Status {
                if(!m_node) {
                    m_node.template emplace();
                    if(auto status = m_node->Build(context); status != Status::OK) {
                        m_node.reset();
                        return status;
                    }
                }
                return Status::OK;
            }

        private:
            using NodeType = typename DecoratedNode::template InstanceType<NODE_CB_TUPLE>;
            std::optional<NodeType> m_node;
        };
    };

    template<typename COND, typename NODE_LIKE>
    struct NodeLikeTrait<NodeLikeMaybe<COND, NODE_LIKE>> {
        using Type = NodeLikeMaybe<COND, NODE_LIKE>;
    };
}

#define __g_MAYBE(...) __MACO_template_type(graph_dsl::NodeLikeMaybe<__VA_ARGS__>)

#endif //GRAPH_DSL_2_776A733183E6411199F785D220F1CD54
