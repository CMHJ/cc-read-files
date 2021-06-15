cmake_minimum_required(VERSION 3.0.0)
project(read-word-lists VERSION 1.0.0)

add_executable(read-word-lists
    src/main.c
    src/trie.c
)

target_link_libraries(read-word-lists
    pthread
)