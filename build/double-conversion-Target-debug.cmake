# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(double-conversion_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(double-conversion_FRAMEWORKS_FOUND_DEBUG "${double-conversion_FRAMEWORKS_DEBUG}" "${double-conversion_FRAMEWORK_DIRS_DEBUG}")

set(double-conversion_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET double-conversion_DEPS_TARGET)
    add_library(double-conversion_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET double-conversion_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${double-conversion_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${double-conversion_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### double-conversion_DEPS_TARGET to all of them
conan_package_library_targets("${double-conversion_LIBS_DEBUG}"    # libraries
                              "${double-conversion_LIB_DIRS_DEBUG}" # package_libdir
                              "${double-conversion_BIN_DIRS_DEBUG}" # package_bindir
                              "${double-conversion_LIBRARY_TYPE_DEBUG}"
                              "${double-conversion_IS_HOST_WINDOWS_DEBUG}"
                              double-conversion_DEPS_TARGET
                              double-conversion_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "double-conversion"    # package_name
                              "${double-conversion_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${double-conversion_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET double-conversion::double-conversion
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${double-conversion_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${double-conversion_LIBRARIES_TARGETS}>
                 )

    if("${double-conversion_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET double-conversion::double-conversion
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     double-conversion_DEPS_TARGET)
    endif()

    set_property(TARGET double-conversion::double-conversion
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${double-conversion_LINKER_FLAGS_DEBUG}>)
    set_property(TARGET double-conversion::double-conversion
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${double-conversion_INCLUDE_DIRS_DEBUG}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET double-conversion::double-conversion
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${double-conversion_LIB_DIRS_DEBUG}>)
    set_property(TARGET double-conversion::double-conversion
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${double-conversion_COMPILE_DEFINITIONS_DEBUG}>)
    set_property(TARGET double-conversion::double-conversion
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${double-conversion_COMPILE_OPTIONS_DEBUG}>)

########## For the modules (FindXXX)
set(double-conversion_LIBRARIES_DEBUG double-conversion::double-conversion)
