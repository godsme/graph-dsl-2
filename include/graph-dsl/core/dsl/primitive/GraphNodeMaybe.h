//
// Created by Darwin Yuan on 2022/7/3.
//

#ifndef GRAPH_DSL_2_776A733183E6411199F785D220F1CD54
#define GRAPH_DSL_2_776A733183E6411199F785D220F1CD54

#include <graph-dsl/core/dsl/primitive/GraphNodeTrait.h>
#include <graph-dsl/Status.h>
#include <optional>

namespace graph_dsl {
    struct GraphContext;

    template<typename COND, typename NODE_LIKE>
    struct GraphNodeMaybe {
        using DecoratedNode = typename GraphNodeTrait<NODE_LIKE>::Type;
        constexpr static auto NODE_LIST = DecoratedNode::NODE_LIST;

        template<typename CB_TUPLE>
        struct InstanceType {
            auto Build(GraphContext& context) -> Status {
                return COND::Satisfied(context).with_value([&](auto satisfied) {
                    if(satisfied) {
                        return DoBuild(context);
                    } else {
                        Release(context);
                        return Status::OK;
                    }
                });
            }

            auto Release(GraphContext& context) {
                if(m_node) {
                    m_node->Release(context);
                    m_node.reset();
                }
            }

            auto Enabled() const -> bool { return m_node.has_value(); }

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
            using NodeType = typename DecoratedNode::template InstanceType<CB_TUPLE>;
            std::optional<NodeType> m_node;
        };
    };

    template<typename COND, typename NODE_LIKE>
    struct GraphNodeTrait<GraphNodeMaybe<COND, NODE_LIKE>> {
        using Type = GraphNodeMaybe<COND, NODE_LIKE>;
    };
}

#endif //GRAPH_DSL_2_776A733183E6411199F785D220F1CD54