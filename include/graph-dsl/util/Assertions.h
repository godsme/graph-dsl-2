//
// Created by Darwin Yuan on 2022/9/4.
//

#ifndef GRAPH_546D8DBA0F18412AAB20AFC73B5FCE1C
#define GRAPH_546D8DBA0F18412AAB20AFC73B5FCE1C

#include <graph-dsl/Status.h>

#define GRAPH_EXPECT_SUCC(call) do { \
   auto status = call;               \
   if(status != Status::OK) {        \
      return status;                 \
   }                                 \
} while(0)

#define GRAPH_EXPECT_TRUE(cond) do { \
   if(!(cond)) {                     \
      return Status::FAILED;         \
   }                                 \
} while(0)

#endif //GRAPH_546D8DBA0F18412AAB20AFC73B5FCE1C
