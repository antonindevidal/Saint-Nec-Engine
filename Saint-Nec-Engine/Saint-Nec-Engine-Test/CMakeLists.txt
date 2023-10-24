cmake_minimum_required (VERSION 3.8)
project(TestProject) # Ajoutez cette ligne avec le nom de votre projet

add_executable(test1 "test/main_test.cpp" "test/test1.cpp" )

enable_testing()

# Saint Nec lib ---------------------------------------------------------------------------------------
target_link_directories(test1 PUBLIC ../Saint-nec-Engine-lib)
target_link_libraries(test1 Saint-Nec-Engine-Lib)


# CATCH ------------------------------------------------------------------------------------------------
add_subdirectory ("Dependencies")
target_link_libraries(test1 CATCH-Lib)