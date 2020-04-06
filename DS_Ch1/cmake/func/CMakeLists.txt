# Find all source files in a directory.
aux_source_directory(. LIB_SRCS)

# add the library that runs
add_library(func ${LIB_SRCS})

# state that anybody linking to us needs to include the current source dir
# to find func.h, and we also need to.
target_include_directories(func
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                           )

# define the symbol stating we are using the declspec(dllexport) when
# building on windows
target_compile_definitions(func PRIVATE "EXPORTING_FUNC")

# install rules
install(TARGETS func DESTINATION lib)
install(FILES func.h DESTINATION include)
