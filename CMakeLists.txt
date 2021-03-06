cmake_minimum_required (VERSION 3.12)

cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0042 NEW)
set(CMAKE_MACOSX_RPATH 1)

project(tabipb)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(TABIPB_ROOT ${PROJECT_SOURCE_DIR})
set(TABIPB_BUILD ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${TABIPB_BUILD}/bin)
set(EXECUTABLE_INSTALL_PATH bin)

################################################
##### For APBS Sphinx
################################################
option(ENABLE_TABIPB_SPHINX "open boundary element method-tabipb SPHINX" OFF)
if(ENABLE_TABIPB_SPHINX)

  if(APPLE)
    list(APPEND CMAKE_MODULE_LINKER_FLAGS "-Wl,-undefined,dynamic_lookup")
  endif()
  if(WIN32)
    list(APPEND CMAKE_MODULE_LINKER_FLAGS "/LIBPATH:C:\Python34\libs")
  endif()

  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../cmake")

  find_package(PythonInterp 3.4 REQUIRED)
  find_package(PythonInclude REQUIRED)
  find_package(Cython REQUIRED)

  include_directories("${PYTHON_INCLUDE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")

  add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/tabipb_py.c"
                     COMMAND "${PYTHON_EXECUTABLE}" -m cython
                     -o "${CMAKE_CURRENT_BINARY_DIR}/tabipb_py.c"
                     "${CMAKE_CURRENT_SOURCE_DIR}/src/tabipb_sph.pyx"
                     MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/src/tabipb_sph.pyx")

  add_library(tabipb_sph MODULE
              tabipb_py.c
              src/array.h
              src/d_sign.c
              src/daxpy.c
              src/dcopy.c
              src/ddot.c
              src/dgemv.c
              src/dnrm2.c
              src/drot.c
              src/drotg.c
              src/dscal.c
              src/dtrsv.c
              src/f2c.h
              src/gl_variables.c
              src/gl_variables.h
              src/gmres.c
              src/readin.c
              src/tabipb.c
              src/TABIPBstruct.h
              src/TABIPBWrap.c
              src/treecode.c
              src/treecode.h
              src/xmalloc.c
              src/xmalloc.h)

  set_target_properties(tabipb_sph PROPERTIES PREFIX "")

endif()

################################################
##### Make a directory for the executable
################################################
file(MAKE_DIRECTORY build/bin)

include_directories("/src")

  # FFLAGS depend on the compiler
  get_filename_component (C_COMPILER_NAME ${CMAKE_C_COMPILER} NAME)

  if (C_COMPILER_NAME MATCHES "gcc.*")
    #set (CMAKE_C_FLAGS_RELEASE "-c -O3")
    set (CMAKE_C_FLAGS_DEBUG   "")
  elseif (C_COMPILER_NAME MATCHES "icc.*")
    set (CMAKE_C_FLAGS_RELEASE "-fast -c")
    set (CMAKE_C_FLAGS_DEBUG   "")
  else ()
    message ("CMAKE_C_COMPILER full path: " ${CMAKE_C_COMPILER})
    message ("C compiler: " ${C_COMPILER_NAME})
  endif ()

# C code for standalone; don't include pp_timer.c in Windows version
  if(WIN32)
        add_executable(tabipb
          src/main.c src/tabipb.c src/gmres.c src/daxpy.c src/dcopy.c src/ddot.c
          src/dgemv.c src/dnrm2.c src/drot.c src/drotg.c src/dscal.c src/d_sign.c
          src/dtrsv.c src/readin.c src/treecode.c src/gl_variables.c
          src/xmalloc.c)
  else()
        add_executable(tabipb
          src/main.c src/tabipb.c src/gmres.c src/daxpy.c src/dcopy.c src/ddot.c
          src/dgemv.c src/dnrm2.c src/drot.c src/drotg.c src/dscal.c src/d_sign.c
          src/dtrsv.c src/readin.c src/pp_timer.c src/treecode.c src/gl_variables.c
          src/xmalloc.c)
  endif()


################################################
###### APBS components
################################################

option(ENABLE_TABIPB_APBS "TABIPB APBS" OFF)
if(ENABLE_TABIPB_APBS)
  add_definitions(-DTABIPB_APBS)
  include_directories(
        ../../src/
        ../../tools/windows/configuration\ headers/
        ../../externals/fetk/maloc/src/base
        ../../externals/fetk/maloc/src/vsys
        ../../externals/fetk/maloc/src/vsh
        ../../externals/fetk/maloc/src/psh
        )

  option(BUILD_SHARED_LIBS "Build shared libraries." OFF)

  # make sure that the default is a RELEASE
  if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE RELEASE CACHE STRING
        "Choose the type of build, options are: None Debug Release."
        FORCE)
  endif (NOT CMAKE_BUILD_TYPE)

  # FFLAGS depend on the compiler
  get_filename_component (C_COMPILER_NAME ${CMAKE_C_COMPILER} NAME)

  if (C_COMPILER_NAME MATCHES "gcc.*")
    #set (CMAKE_C_FLAGS_RELEASE "-c -O3")
    set (CMAKE_C_FLAGS_DEBUG   "")
  elseif (C_COMPILER_NAME MATCHES "icc.*")
    set (CMAKE_C_FLAGS_RELEASE "-fast -c")
    set (CMAKE_C_FLAGS_DEBUG   "")
  else ()
    message ("CMAKE_C_COMPILER full path: " ${CMAKE_C_COMPILER})
    message ("C compiler: " ${C_COMPILER_NAME})
  endif ()

  set (LIBFILES
    src/TABIPBWrap.c src/tabipb.c src/gmres.c src/daxpy.c src/dcopy.c src/ddot.c
    src/dgemv.c src/dnrm2.c src/drot.c src/drotg.c src/dscal.c src/d_sign.c
    src/dtrsv.c src/readin.c src/treecode.c src/gl_variables.c src/xmalloc.c)

  message(***** ${CMAKE_INSTALL_PREFIX} *****)

  if(NOT DEFINED ${CMAKE_INSTALL_PREFIX})
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
  endif()

  if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
  endif()

  set(TABIPB_LIBNAME TABIPBlib)
  add_library(${TABIPB_LIBNAME} ${LIBFILES})

endif()

#Math linking is unnecessary for Windows
if(NOT WIN32)
    target_link_libraries(tabipb m)
endif()

################################################
###### Install
################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
install(TARGETS tabipb RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin)
