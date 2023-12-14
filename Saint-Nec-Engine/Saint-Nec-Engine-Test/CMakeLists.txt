cmake_minimum_required (VERSION 3.8)
project(TestProject) # Ajoutez cette ligne avec le nom de votre projet

add_executable(test_BoxCollider "test/testBox.cpp" )
add_executable(test_SphereCollider "test/testSphere.cpp" )
add_executable(test_Collision "test/testCollision.cpp" )
add_executable(test_Interaction "test/testInteraction.cpp" )

enable_testing()

# Saint Nec lib ---------------------------------------------------------------------------------------
target_link_directories(test_BoxCollider PUBLIC ../Saint-nec-Engine-lib)
target_link_libraries(test_BoxCollider Saint-Nec-Engine-Lib)

target_link_directories(test_SphereCollider PUBLIC ../Saint-nec-Engine-lib)
target_link_libraries(test_SphereCollider Saint-Nec-Engine-Lib)

target_link_directories(test_Collision PUBLIC ../Saint-nec-Engine-lib)
target_link_libraries(test_Collision Saint-Nec-Engine-Lib)

target_link_directories(test_Interaction PUBLIC ../Saint-nec-Engine-lib)
target_link_libraries(test_Interaction Saint-Nec-Engine-Lib)
# CATCH ------------------------------------------------------------------------------------------------
add_subdirectory ("Dependencies")
target_link_libraries(test_BoxCollider CATCH-Lib)
target_link_libraries(test_SphereCollider CATCH-Lib)
target_link_libraries(test_Collision CATCH-Lib)
target_link_libraries(test_Interaction CATCH-Lib)