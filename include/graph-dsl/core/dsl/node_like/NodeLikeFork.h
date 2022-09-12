//
// Created by Darwin Yuan on 2022/9/4.
//

#ifndef GRAPH_13713B9A357C45BB85C15037910AB9F9
#define GRAPH_13713B9A357C45BB85C15037910AB9F9

#include <graph-dsl/core/dsl/node_like/NodeLikeTrait.h>
#include <graph-dsl/util/TupleForEach.h>
#include <maco/basic.h>
#include <holo/holo.h>

namespace graph_dsl {
    struct GraphContext;

    template<typename ... NODEs_LIKE>
    struct NodeLikeFork final {
        constexpr static auto NODE_LIST =
                  holo::make_list(NodeLikeTrait<NODEs_LIKE>::Type::NODE_LIST...)
                | holo::flatten();

        template<typename NODE_CB_TUPLE>
        struct InstanceType {
            auto Enabled() const -> bool {
                return TupleExists(m_nodes, [](auto& node) { return node.Enabled(); });
            }

            auto Build(GraphContext& context) -> Status {
                return TupleForeach(m_nodes, [&](auto& node) { return node.Build(context); });
            }

            auto Release(GraphContext& context) -> void {
                TupleForeachVoid(m_nodes, [&](auto& node) { node.Release(context); });
            }

        private:
            std::tuple<typename NodeLikeTrait<NODEs_LIKE>::Type::template InstanceType<NODE_CB_TUPLE>...> m_nodes;
        };
    };

    template<typename ... NODEs_LIKE>
    struct NodeLikeTrait<NodeLikeFork<NODEs_LIKE...>> {
        using Type = NodeLikeFork<NODEs_LIKE...>;
    };

    namespace detail {
        template <typename ... Ts>
        struct ToFork {
            using Type = NodeLikeFork<typename Ts::type...>;
        };

        template<typename ... Ts>
        constexpr auto ToNodeLikeFork(holo::type_list<Ts...>) -> auto {
            using List = decltype(holo::list_t<Ts...> | holo::unique);
            if constexpr (List::Size == 1) {
                return typename List::head::type{};
            } else {
                return typename List::template export_to<ToFork>::Type{};
            }
        }
    }

    template<typename ... NODEs_LIKE1, typename ... NODEs_LIKE2>
    constexpr auto NodeLikeMerge(NodeLikeFork<NODEs_LIKE1...>, NodeLikeFork<NODEs_LIKE2...>) -> auto {
        return detail::ToNodeLikeFork(holo::type_list<NODEs_LIKE1..., NODEs_LIKE2...>{});
    }

    template<typename ... NODEs_LIKE, typename T>
    constexpr auto NodeLikeMerge(NodeLikeFork<NODEs_LIKE...>, T) -> auto {
        return detail::ToNodeLikeFork(holo::type_list<NODEs_LIKE..., T>{});
    }

    template<typename ... NODEs_LIKE, typename T>
    constexpr auto NodeLikeMerge(T, NodeLikeFork<NODEs_LIKE...>) -> auto {
        return detail::ToNodeLikeFork(holo::type_list<T, NODEs_LIKE...>{});
    }

    template<typename T1, typename T2>
    constexpr auto NodeLikeMerge(T1, T2) -> auto {
        return detail::ToNodeLikeFork(holo::type_list<T1, T2>{});
    }
}

#define __g_FORK(...) __MACO_template_type(graph_dsl::NodeLikeFork<__VA_ARGS__>)

#endif //GRAPH_13713B9A357C45BB85C15037910AB9F9
