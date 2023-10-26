
project(TestProject)

add_executable(test1 "test/test1.cpp" )

enable_testing()

target_link_libraries(test1 Saint-Nec-Engine-Lib CATCH-Lib)