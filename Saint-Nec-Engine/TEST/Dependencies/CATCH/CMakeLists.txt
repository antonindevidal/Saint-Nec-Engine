# CMakeList.txt : projet CMake pour TEST, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_policy(SET CMP0072 NEW)


add_library (CATCH-Lib
				"catch.cpp"
				"catch.hpp"
				)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
