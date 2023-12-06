project(PriorityQueue_test)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(${PROJECT_NAME} 
    src/priority_queue_test.cc
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    GTest::GTest
    lib::QuickSort
)

add_test(PriorityQueue_test PriorityQueue)