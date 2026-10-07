cmake_minimum_required(VERSION 3.16)

project(libcutl
    VERSION 1.11.0
    LANGUAGES CXX
)

include(GNUInstallDirs)

# ------------------------------------------------------------
# Sources
# ------------------------------------------------------------

file(GLOB_RECURSE LIBCUTL_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/libcutl/*.cxx"
)

if(NOT LIBCUTL_SOURCES)
    message(FATAL_ERROR "No libcutl .cxx source files found")
endif()

add_library(cutl SHARED ${LIBCUTL_SOURCES})

add_library(libcutl::cutl ALIAS cutl)

set_target_properties(cutl PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_include_directories(cutl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(cutl PROPERTIES
    OUTPUT_NAME cutl
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

# ------------------------------------------------------------
# Install library
# ------------------------------------------------------------

install(TARGETS cutl
    EXPORT libcutlTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------
# Install headers
# ------------------------------------------------------------

file(GLOB_RECURSE LIBCUTL_HEADERS CONFIGURE_DEPENDS
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/libcutl/*.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/libcutl/*.ixx"
    "${CMAKE_CURRENT_SOURCE_DIR}/libcutl/*.txx"
)

foreach(header IN LISTS LIBCUTL_HEADERS)
    get_filename_component(header_dir "${header}" DIRECTORY)

    install(
        FILES "${CMAKE_CURRENT_SOURCE_DIR}/${header}"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${header_dir}"
    )
endforeach()

# ------------------------------------------------------------
# CMake package
# ------------------------------------------------------------

set(LIBCUTL_CMAKE_INSTALL_DIR
    "${CMAKE_INSTALL_LIBDIR}/cmake/libcutl"
)

# Install the exported target information.
install(
    EXPORT libcutlTargets
    FILE libcutlTargets.cmake
    NAMESPACE libcutl::
    DESTINATION "${LIBCUTL_CMAKE_INSTALL_DIR}"
)

# Generate libcutlConfig.cmake directly.
file(GENERATE
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/libcutlConfig.cmake"
    CONTENT
"include(\"\${CMAKE_CURRENT_LIST_DIR}/libcutlTargets.cmake\")
"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/libcutlConfig.cmake"
    DESTINATION "${LIBCUTL_CMAKE_INSTALL_DIR}"
)

# ------------------------------------------------------------
# pkg-config
# ------------------------------------------------------------

set(LIBCUTL_PKGCONFIG_INSTALL_DIR
    "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)

file(GENERATE
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/libcutl.pc"
    CONTENT
"prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=\${prefix}
libdir=\${exec_prefix}/${CMAKE_INSTALL_LIBDIR}
includedir=\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}

Name: libcutl
Description: C++ utility library
Version: ${PROJECT_VERSION}
Libs: -L\${libdir} -lcutl
Cflags: -I\${includedir}
"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/libcutl.pc"
    DESTINATION "${LIBCUTL_PKGCONFIG_INSTALL_DIR}"
)
