cmake_minimum_required(VERSION 3.15)
project(ZDPlasKin Fortran)

enable_language(Fortran)

set(SOURCES
    dvode_f90_m.F90
    zdplaskin_m.F90
    master_module.F90
    zdpSolver.F90
)

add_library(ZDPlasKin SHARED ${SOURCES})

# use a full path to link bolsig_x86_64.so
target_link_options(ZDPlasKin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/bolsig_x86_64.so)

target_compile_options(ZDPlasKin PRIVATE
    -std=legacy
    -fPIC
    -fallow-argument-mismatch
    -w
)

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
file(GLOB MY_LIBRARYS "${CMAKE_SOURCE_DIR}/*.so")
install(FILES ${MY_HEADERS} DESTINATION include)
install(FILES ${MY_LIBRARYS} DESTINATION lib)