//
// Created by Darwin Yuan on 2022/9/4.
//

#ifndef GRAPH_791DEE3DD5F34DC8904F17C69B338246
#define GRAPH_791DEE3DD5F34DC8904F17C69B338246

#include <graph-dsl/core/runtime/RootState.h>

namespace graph_dsl {
    struct GraphContext {
        GraphContext() = default;

        template<typename NODES, int INDEX>
        inline auto GetNode() -> decltype(auto) {
            return (std::get<INDEX>(*reinterpret_cast<NODES*>(m_subgraphNodes)));
        }

        template<typename NODES, int INDEX>
        inline auto GetRootNode() -> decltype(auto) {
            return (std::get<INDEX>(*reinterpret_cast<NODES*>(m_roots)));
        }

        template<typename ROOT_NODES>
        auto UpdateRootNodes(ROOT_NODES& nodes) {
            m_roots = reinterpret_cast<void*>(&nodes);
        }

        template<typename NODES_CB>
        auto SwitchSubgraphContext(NODES_CB& nodes) {
            m_subgraphNodes = reinterpret_cast<void*>(&nodes);
        }

        auto GetRootState() const -> decltype(auto) {
            return (m_rootState);
        }

        auto UpdateRootState(const RootState& state) {
            m_rootState = state;
        }

    private:
        void*                    m_roots{};
        void*                    m_subgraphNodes{};
        RootState                m_rootState{};
    };
}

#endif //GRAPH_791DEE3DD5F34DC8904F17C69B338246
