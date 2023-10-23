# CMakeList.txt : projet CMake pour TEST, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_policy(SET CMP0072 NEW)


add_library (CATCH-LIB
				"catch.cpp"
				)

target_include_directories(CATCH-Lib  PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
  ... other required includes
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET test1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
