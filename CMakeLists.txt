cmake_minimum_required(VERSION 3.15)
project(ZDPlasKin Fortran)

enable_language(Fortran)


set(BOLSIG_DST ${CMAKE_BINARY_DIR}/bolsig_x86_64.so)

add_custom_command(
    OUTPUT ${BOLSIG_DST}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/bolsig_x86_64.so
            ${BOLSIG_DST}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/bolsig_x86_64.so
    COMMENT "Copy external bolsig library to build directory"
)

add_custom_target(copy_bolsig ALL DEPENDS ${BOLSIG_DST})

add_library(bolsig SHARED IMPORTED)
set_target_properties(bolsig PROPERTIES
    IMPORTED_LOCATION ${BOLSIG_DST}
)



set(SOURCES
    dvode_f90_m.F90
    zdplaskin_m.F90
    master_module.F90
    zdpSolver.F90
)
add_library(ZDPlasKin SHARED ${SOURCES})

target_compile_options(ZDPlasKin PRIVATE
    -std=legacy
    -fPIC
    -fallow-argument-mismatch
    -w
)

target_link_libraries(ZDPlasKin PRIVATE bolsig)

add_dependencies(ZDPlasKin copy_bolsig)

# --------------------------
# set library name
# --------------------------
set_target_properties(ZDPlasKin PROPERTIES
    OUTPUT_NAME "ZDPlasKin"
    SUFFIX ".so"
)

# --------------------------
# install rule
# --------------------------

# 1. install share library
install(TARGETS ZDPlasKin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)



# 2. install the header file
file(GLOB MY_HEADERS "${CMAKE_SOURCE_DIR}/*.H")
install(FILES ${MY_HEADERS} DESTINATION include)

# 3.install the extern library bolsig_x86_64.so
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/bolsig_x86_64.so
        DESTINATION lib)