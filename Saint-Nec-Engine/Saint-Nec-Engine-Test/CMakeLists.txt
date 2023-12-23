cmake_minimum_required (VERSION 3.8)
project(TestProject) # Ajoutez cette ligne avec le nom de votre projet

add_executable(testBoxCollider "test/testBox.cpp" )
add_executable(testSphereCollider "test/testSphere.cpp" )
add_executable(testCollision "test/testCollision.cpp" )
add_executable(testInteraction "test/testInteraction.cpp" )
add_executable(testManager "test/testManager.cpp" )

enable_testing()

# Saint Nec lib ---------------------------------------------------------------------------------------
target_link_directories(testBoxCollider PUBLIC ../Saint-nec-Engine-lib)
target_link_libraries(testBoxCollider Saint-Nec-Engine-Lib)

target_link_directories(testSphereCollider PUBLIC ../Saint-nec-Engine-lib)
target_link_libraries(testSphereCollider Saint-Nec-Engine-Lib)

target_link_directories(testCollision PUBLIC ../Saint-nec-Engine-lib)
target_link_libraries(testCollision Saint-Nec-Engine-Lib)

target_link_directories(testInteraction PUBLIC ../Saint-nec-Engine-lib)
target_link_libraries(testInteraction Saint-Nec-Engine-Lib)

target_link_directories(testManager PUBLIC ../Saint-nec-Engine-lib)
target_link_libraries(testManager Saint-Nec-Engine-Lib)
# CATCH ------------------------------------------------------------------------------------------------
add_subdirectory ("Dependencies")
target_link_libraries(testBoxCollider CATCH-Lib)
target_link_libraries(testSphereCollider CATCH-Lib)
target_link_libraries(testCollision CATCH-Lib)
target_link_libraries(testInteraction CATCH-Lib)
target_link_libraries(testManager CATCH-Lib)