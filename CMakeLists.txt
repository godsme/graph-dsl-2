cmake_minimum_required(VERSION 3.20)
project(graph)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/third-party"
        "${CMAKE_CURRENT_SOURCE_DIR}/../nano-caf-2/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/../maco/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/../holo/include"
)

set(graph_dsl
        include/graph-dsl/Status.h
        include/graph-dsl/util/TupleElementIndex.h
        include/graph-dsl/core/GraphContext.h
        include/graph-dsl/core/dsl/GraphPort.h
        include/graph-dsl/core/runtime/NodeCb.h
        include/graph-dsl/core/runtime/DeviceInfo.h
        include/graph-dsl/core/runtime/RootState.h
        include/graph-dsl/core/dsl/NodeIndex.h
        include/graph-dsl/core/dsl/node_like/NodeLikeTrait.h
        include/graph-dsl/core/dsl/node_like/NodeLikeRef.h
        include/graph-dsl/core/dsl/node_like/NodeLikeMaybe.h
        include/graph-dsl/core/dsl/node_like/NodeLikeEither.h
        )

add_executable(graph_ut
        ${graph_dsl}
        third-party/catch.cpp
        test/ut/TestNodeLikeRef.cpp
        test/ut/TestNodeLikeMaybe.cpp
        test/ut/TestNodeLikeEither.cpp)

set(nano-caf-lib ${CMAKE_CURRENT_SOURCE_DIR}/../nano-caf-2/cmake-build-release/libnano_caf.a)

target_link_libraries(graph_ut ${nano-caf-lib})
#target_link_libraries(graph_ft ${nano-caf-lib} pthread)
#target_link_libraries(graph_multi_device  pthread ${nano-caf-lib})

