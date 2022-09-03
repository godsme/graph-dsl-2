//
// Created by Darwin Yuan on 2022/9/4.
//

#ifndef GRAPH_285777B5226E42BE8497B12B7F59AF9D
#define GRAPH_285777B5226E42BE8497B12B7F59AF9D

#include <graph-dsl/Status.h>
#include <nano-caf/actor/ActorPtr.h>

namespace graph_dsl {
    template<typename NODE>
    struct NodeCb {
        using NodeType = NODE;

        auto AddRef() -> void { m_refs++; }
        auto Release() -> void { m_refs--; }
        auto Present() -> bool { return m_refs > 0; }

        auto Stop() -> Status {
            if(m_running) {
                m_running = false;
                m_actor.Release();
            }
            return Status::OK;
        }

        auto CleanUp() -> Status {
            if(m_refs == 0) {
                return Stop();
            }
            return Status::OK;
        }

        inline auto GetActorHandle() -> decltype(auto) {
            return (m_actor);
        }

    protected:
        nano_caf::ActorPtr m_actor{};
        uint8_t m_refs{0};
        bool    m_running{false};
    };
}

#endif //GRAPH_285777B5226E42BE8497B12B7F59AF9D
