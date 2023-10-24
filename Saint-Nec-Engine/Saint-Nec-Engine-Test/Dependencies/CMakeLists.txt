# CMakeList.txt : projet CMake pour TEST, incluez la source et définissez
# la logique spécifique au projet ici.
#


add_library (CATCH-Lib
				"CATCH/catch.cpp"
				"CATCH/catch.hpp"
				)

target_include_directories(CATCH-Lib INTERFACE CATCH)