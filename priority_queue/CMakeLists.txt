project(PriorityQueue)

add_library(${PROJECT_NAME} INTERFACE)
add_library(lib::priorityQueue ALIAS ${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/export>
        $<INSTALL_INTERFACE:include>
)

add_subdirectory(test)