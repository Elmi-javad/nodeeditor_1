file(GLOB_RECURSE CPPS  ./*.cpp )

add_executable(regex ${CPPS})

target_link_libraries(regex nodes)
