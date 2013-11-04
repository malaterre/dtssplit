cmake_minimum_required(VERSION 2.8)
project(dts)

add_executable(dtssplit dtssplit.cxx)
target_link_libraries(dtssplit z)
