cmake_minimum_required (VERSION 3.8)
project(TestProject) # Ajoutez cette ligne avec le nom de votre projet

add_executable(Test1 test/main_test.cpp test/test1.cpp)

enable_testing()

target_include_directories(Test1 PRIVATE ../Saint-Nec-Engine-Lib/src)
target_link_libraries(Test1 ${CMAKE_SOURCE_DIR}/../Saint-Nec-Engine-Lib/src)
