//
// Created by Darwin Yuan on 2022/9/4.
//

#ifndef GRAPH_0FAEA77DCCDB4F97B956E9D8A4DDF6D8
#define GRAPH_0FAEA77DCCDB4F97B956E9D8A4DDF6D8

#include <tuple>
#include <type_traits>

namespace graph_dsl::detail {
    template<typename T, typename TUPLE, template<typename> typename F, int I = 0, typename = void>
    struct TupleElementByType;

    template<typename T, template<typename> typename F, int I, class H, class... Tail>
    struct TupleElementByType<T, std::tuple<H, Tail...>, F, I,
            std::enable_if_t<std::is_same_v<T, typename F<H>::type>>> {
        constexpr static int INDEX = I;
    };

    template<typename T, template<typename> typename F, int I, class H, class... Tail>
    struct TupleElementByType<T, std::tuple<H, Tail...>, F, I,
            std::enable_if_t<!std::is_same_v<T, typename F<H>::type>>> {
        constexpr static int INDEX = TupleElementByType<T, std::tuple<Tail...>, F, I + 1>::INDEX;
    };

    template<typename T, template<typename> typename F, int I>
    struct TupleElementByType<T, std::tuple<>, F, I> {
        constexpr static int INDEX = -1;
    };
}

namespace graph_dsl {
    template<typename T, typename TUPLE, template<typename> typename F>
    constexpr static int TupleElementIndex = detail::TupleElementByType<T, TUPLE, F>::INDEX;
}

#endif //GRAPH_0FAEA77DCCDB4F97B956E9D8A4DDF6D8
