cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(main VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the build type on single-configuration generators.
set(CMAKE_BUILD_TYPE "Debug") 

# Specify flags used by the CXX compiler during all build types.
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -static-libgcc -fexec-charset=GBK")

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# configure a header file to pass the version number only
configure_file(mainConfig.h.in mainConfig.h)

# add the func library
add_subdirectory(func)

# add the executable
add_executable(main main.cxx)
target_link_libraries(main PUBLIC func)

# add the binary tree to the search path for include files
# so that we will find mainConfig.h
target_include_directories(main PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

# add the install targets
install(TARGETS main DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/mainConfig.h"
  DESTINATION include
  )

# enable testing
include(CTest)

# does the application run
add_test(NAME Runs COMMAND main 25)

# does the usage message work?
add_test(NAME Usage COMMAND main)
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
  )

# define a function to simplify adding tests
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction(do_test)

# do a bunch of result based tests
do_test(main 4 "4 is 2")
do_test(main 9 "9 is 3")
do_test(main 5 "5 is 2.236")
do_test(main 7 "7 is 2.645")
do_test(main 25 "25 is 5")
do_test(main -25 "-25 is [-nan|nan|0]")
do_test(main 0.0001 "0.0001 is 0.01")

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${main_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${main_VERSION_MINOR}")
include(CPack)

