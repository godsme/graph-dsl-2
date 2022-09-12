//
// Created by Darwin Yuan on 2022/9/11.
//

#ifndef GRAPH_A868A3CFAC9144CDA0731569477888FD
#define GRAPH_A868A3CFAC9144CDA0731569477888FD

namespace graph_dsl {
    template<typename> struct SubGraphSelector;

    template<typename COND, typename SUB_GRAPH>
    struct SubGraphSelector<auto (COND) -> SUB_GRAPH> {
        using SubGraph = SUB_GRAPH;
    };
}

#endif //GRAPH_A868A3CFAC9144CDA0731569477888FD
