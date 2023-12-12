project(Huffman)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_DIR}/src/huffman.cc)
add_library(lib::Huffman ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_sources(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} lib::priorityQueue)

# add_subdirectory(test)