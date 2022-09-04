//
// Created by Darwin Yuan on 2022/9/4.
//

#ifndef GRAPH_1D105A4D523543ADB4639413AB7A3EB9
#define GRAPH_1D105A4D523543ADB4639413AB7A3EB9

#include <graph-dsl/Status.h>
#include <tuple>

namespace graph_dsl::detail {
    template<typename TUPLE, typename F, std::size_t ... I>
    auto TupleForeach(TUPLE&& tuple, F&& f, std::index_sequence<I...>) {
        Status status = Status::OK;
        return (((status = f(std::get<I>(std::forward<TUPLE>(tuple)))) == Status::OK) && ...) ?
               Status::OK : status;
    }

    template<typename TUPLE, typename F, size_t ... I>
    auto TupleForeach_r(TUPLE&& tuple, F&& f, std::index_sequence<I...>) {
        Status status = Status::OK;
        return (((status = f(std::get<sizeof...(I) - I - 1>(std::forward<TUPLE>(tuple)))) == Status::OK) && ...) ?
               Status::OK : status;
    }

    template<typename TUPLE, typename F, size_t ... I>
    auto TupleForeachVoid(TUPLE&& tuple, F&& f, std::index_sequence<I...>) {
        (f(std::get<I>(std::forward<TUPLE>(tuple))), ...);
    }

    template<typename TUPLE, typename F, size_t ... I>
    constexpr auto TupleExists(TUPLE&& tuple, F&& f, std::index_sequence<I...>) {
        return (f(std::get<I>(std::forward<TUPLE>(tuple))) || ...);
    }
}

namespace graph_dsl {
    template<typename TUPLE, typename F, size_t ... I>
    auto TupleForeach(TUPLE&& tuple, F&& f) {
        return detail::TupleForeach
                ( std::forward<TUPLE>(tuple)
                , std::forward<F>(f)
                , std::make_index_sequence<std::tuple_size_v<std::decay_t<TUPLE>>>{});
    }

    template<typename TUPLE, typename F, size_t ... I>
    auto TupleForeach_r(TUPLE&& tuple, F&& f) {
        return detail::TupleForeach_r
                ( std::forward<TUPLE>(tuple)
                , std::forward<F>(f)
                , std::make_index_sequence<std::tuple_size_v<std::decay_t<TUPLE>>>{});
    }

    template<typename TUPLE, typename F, size_t ... I>
    auto TupleForeachVoid(TUPLE&& tuple, F&& f) {
        detail::TupleForeachVoid
                ( std::forward<TUPLE>(tuple)
                , std::forward<F>(f)
                , std::make_index_sequence<std::tuple_size_v<std::decay_t<TUPLE>>>{});
    }

    template<typename TUPLE, typename F>
    constexpr auto TupleExists(TUPLE&& tuple, F&& f) {
        return detail::TupleExists
                ( std::forward<TUPLE>(tuple)
                , std::forward<F>(f)
                , std::make_index_sequence<std::tuple_size_v<std::decay_t<TUPLE>>>{});
    }
}

#endif //GRAPH_1D105A4D523543ADB4639413AB7A3EB9
