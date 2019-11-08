add_executable(lta1 lta1.cpp)
target_link_libraries(lta1 benchmark)

add_executable(lta2 lta2.cpp)
target_link_libraries(lta2 benchmark)

add_executable(benchmarkVisit BenchmarkVisit.cpp)
target_link_libraries(benchmarkVisit benchmark)
