# CMakeList.txt : projet CMake pour Saint-Nec-Engine, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.
add_executable (Saint-Nec-Engine "src/Saint-Nec-Engine.cpp" "src/Saint-Nec-Engine.h")
target_link_directories(Saint-Nec-Engine PUBLIC ../Saint-nec-Engine-lib/src)
target_link_libraries(Saint-Nec-Engine Saint-Nec-Engine-Lib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Saint-Nec-Engine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
