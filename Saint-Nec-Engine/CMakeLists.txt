
cmake_minimum_required (VERSION 3.3)

#SET CPP Version for all platforms and projects
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Saint-Nec-Engine")

# Incluez les sous-projets.
add_subdirectory ("Saint-Nec-Engine")
add_subdirectory ("Saint-Nec-Engine-Lib/src")
add_subdirectory ("Saint-Nec-Engine-Test")

