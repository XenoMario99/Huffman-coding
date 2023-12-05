project(QuickSort)

add_library(${PROJECT_NAME} INTERFACE)
add_library(lib::QuickSort ALIAS ${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/export>
        $<INSTALL_INTERFACE:include>
)
