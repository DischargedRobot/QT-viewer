# Conan automatically generated toolchain file
# DO NOT EDIT MANUALLY, it will be overwritten

# Avoid including toolchain file several times (bad if appending to variables like
#   CMAKE_CXX_FLAGS. See https://github.com/android/ndk/issues/323
include_guard()
message(STATUS "Using Conan toolchain: ${CMAKE_CURRENT_LIST_FILE}")
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeToolchain' generator only works with CMake >= 3.15")
endif()

########## 'user_toolchain' block #############
# Include one or more CMake user toolchain from tools.cmake.cmaketoolchain:user_toolchain



########## 'generic_system' block #############
# Definition of system, platform and toolset


set(CMAKE_GENERATOR_PLATFORM "x64" CACHE STRING "" FORCE)

message(STATUS "Conan toolchain: CMAKE_GENERATOR_TOOLSET=v143")
set(CMAKE_GENERATOR_TOOLSET "v143" CACHE STRING "" FORCE)


########## 'compilers' block #############



########## 'libcxx' block #############
# Definition of libcxx from 'compiler.libcxx' setting, defining the
# right CXX_FLAGS for that libcxx



########## 'vs_runtime' block #############
# Definition of VS runtime CMAKE_MSVC_RUNTIME_LIBRARY, from settings build_type,
# compiler.runtime, compiler.runtime_type

cmake_policy(GET CMP0091 POLICY_CMP0091)
if(NOT "${POLICY_CMP0091}" STREQUAL NEW)
    message(FATAL_ERROR "The CMake policy CMP0091 must be NEW, but is '${POLICY_CMP0091}'")
endif()
message(STATUS "Conan toolchain: Setting CMAKE_MSVC_RUNTIME_LIBRARY=$<$<CONFIG:Debug>:MultiThreadedDebug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "$<$<CONFIG:Debug>:MultiThreadedDebug>")


########## 'vs_debugger_environment' block #############
# Definition of CMAKE_VS_DEBUGGER_ENVIRONMENT from "bindirs" folders of dependencies
# for execution of applications with shared libraries within the VS IDE

set(CMAKE_VS_DEBUGGER_ENVIRONMENT "PATH=$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/bin;C:/Users/user/.conan2/p/b/opens769fd176b006d/p/bin;C:/Users/user/.conan2/p/b/pcre23012e7355d789/p/bin;C:/Users/user/.conan2/p/b/doubl939b7f123f641/p/bin;C:/Users/user/.conan2/p/b/freetfdd35eef06d56/p/bin;C:/Users/user/.conan2/p/b/bzip2827565812739f/p/bin;C:/Users/user/.conan2/p/b/brotl6d7426260b727/p/bin;C:/Users/user/.conan2/p/b/libjp043311aae795c/p/bin;C:/Users/user/.conan2/p/b/libpna37919b28b92d/p/bin;C:/Users/user/.conan2/p/b/zliba252c37263f92/p/bin;C:/Users/user/.conan2/p/b/sqlite216284357a5b/p/bin;C:/Users/user/.conan2/p/b/libpq7b477c5efd65a/p/bin;C:/Users/user/.conan2/p/b/opena7a3b519efd52d/p/bin;C:/Users/user/.conan2/p/b/zstdf9734e9ec0a3a/p/bin;C:/Users/user/.conan2/p/b/md4c5671ffc7b79cd/p/bin>;%PATH%")


########## 'cppstd' block #############
# Define the C++ and C standards from 'compiler.cppstd' and 'compiler.cstd'

function(conan_modify_std_watch variable access value current_list_file stack)
    set(conan_watched_std_variable 14)
    if (${variable} STREQUAL "CMAKE_C_STANDARD")
        set(conan_watched_std_variable )
    endif()
    if (${access} STREQUAL "MODIFIED_ACCESS" AND NOT ${value} STREQUAL ${conan_watched_std_variable})
        message(STATUS "Warning: Standard ${variable} value defined in conan_toolchain.cmake to ${conan_watched_std_variable} has been modified to ${value} by ${current_list_file}")
    endif()
    unset(conan_watched_std_variable)
endfunction()

message(STATUS "Conan toolchain: C++ Standard 14 with extensions OFF")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
variable_watch(CMAKE_CXX_STANDARD conan_modify_std_watch)


########## 'parallel' block #############
# Define VS paralell build /MP flags

string(APPEND CONAN_CXX_FLAGS " /MP8")
string(APPEND CONAN_C_FLAGS " /MP8")


########## 'extra_flags' block #############
# Include extra C++, C and linker flags from configuration tools.build:<type>flags
# and from CMakeToolchain.extra_<type>_flags

# Conan conf flags start: Debug
# Conan conf flags end


########## 'cmake_flags_init' block #############
# Define CMAKE_<XXX>_FLAGS from CONAN_<XXX>_FLAGS

foreach(config IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${config} config)
    if(DEFINED CONAN_CXX_FLAGS_${config})
      string(APPEND CMAKE_CXX_FLAGS_${config}_INIT " ${CONAN_CXX_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_C_FLAGS_${config})
      string(APPEND CMAKE_C_FLAGS_${config}_INIT " ${CONAN_C_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_SHARED_LINKER_FLAGS_${config})
      string(APPEND CMAKE_SHARED_LINKER_FLAGS_${config}_INIT " ${CONAN_SHARED_LINKER_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_EXE_LINKER_FLAGS_${config})
      string(APPEND CMAKE_EXE_LINKER_FLAGS_${config}_INIT " ${CONAN_EXE_LINKER_FLAGS_${config}}")
    endif()
endforeach()

if(DEFINED CONAN_CXX_FLAGS)
  string(APPEND CMAKE_CXX_FLAGS_INIT " ${CONAN_CXX_FLAGS}")
endif()
if(DEFINED CONAN_C_FLAGS)
  string(APPEND CMAKE_C_FLAGS_INIT " ${CONAN_C_FLAGS}")
endif()
if(DEFINED CONAN_SHARED_LINKER_FLAGS)
  string(APPEND CMAKE_SHARED_LINKER_FLAGS_INIT " ${CONAN_SHARED_LINKER_FLAGS}")
endif()
if(DEFINED CONAN_EXE_LINKER_FLAGS)
  string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " ${CONAN_EXE_LINKER_FLAGS}")
endif()


########## 'extra_variables' block #############
# Definition of extra CMake variables from tools.cmake.cmaketoolchain:extra_variables



########## 'try_compile' block #############
# Blocks after this one will not be added when running CMake try/checks

get_property( _CMAKE_IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE )
if(_CMAKE_IN_TRY_COMPILE)
    message(STATUS "Running toolchain IN_TRY_COMPILE")
    return()
endif()


########## 'find_paths' block #############
# Define paths to find packages, programs, libraries, etc.

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

# Definition of CMAKE_MODULE_PATH
list(PREPEND CMAKE_MODULE_PATH "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/lib/cmake/Qt5Qml" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/lib/cmake/Qt5Widgets" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/lib/cmake/Qt5Gui" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/lib/cmake/Qt5LinguistTools" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/bin/archdatadir/bin" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/lib/cmake/Qt5Core" "C:/Users/user/.conan2/p/b/opens769fd176b006d/p/lib/cmake")
# the generators folder (where conan generates files, like this toolchain)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Definition of CMAKE_PREFIX_PATH, CMAKE_XXXXX_PATH
# The explicitly defined "builddirs" of "host" context dependencies must be in PREFIX_PATH
list(PREPEND CMAKE_PREFIX_PATH "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/lib/cmake/Qt5Qml" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/lib/cmake/Qt5Widgets" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/lib/cmake/Qt5Gui" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/lib/cmake/Qt5LinguistTools" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/bin/archdatadir/bin" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/lib/cmake/Qt5Core" "C:/Users/user/.conan2/p/b/opens769fd176b006d/p/lib/cmake")
# The Conan local "generators" folder, where this toolchain is saved.
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR} )
list(PREPEND CMAKE_LIBRARY_PATH "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/lib" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/bin/archdatadir/plugins/styles" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/bin/archdatadir/plugins/platforms" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/bin/archdatadir/plugins/audio" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/bin/archdatadir/plugins/mediaservice" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/bin/archdatadir/plugins/playlistformats" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/bin/archdatadir/plugins/sqldrivers" "C:/Users/user/.conan2/p/b/opens769fd176b006d/p/lib" "C:/Users/user/.conan2/p/b/pcre23012e7355d789/p/lib" "C:/Users/user/.conan2/p/b/doubl939b7f123f641/p/lib" "C:/Users/user/.conan2/p/b/freetfdd35eef06d56/p/lib" "C:/Users/user/.conan2/p/b/bzip2827565812739f/p/lib" "C:/Users/user/.conan2/p/b/brotl6d7426260b727/p/lib" "C:/Users/user/.conan2/p/b/libjp043311aae795c/p/lib" "C:/Users/user/.conan2/p/b/libpna37919b28b92d/p/lib" "C:/Users/user/.conan2/p/b/zliba252c37263f92/p/lib" "C:/Users/user/.conan2/p/b/sqlite216284357a5b/p/lib" "C:/Users/user/.conan2/p/b/libpq7b477c5efd65a/p/lib" "C:/Users/user/.conan2/p/b/opena7a3b519efd52d/p/lib" "C:/Users/user/.conan2/p/b/zstdf9734e9ec0a3a/p/lib" "C:/Users/user/.conan2/p/b/md4c5671ffc7b79cd/p/lib")
list(PREPEND CMAKE_INCLUDE_PATH "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtMultimediaQuick" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtQuickTemplates2" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtQuickControls2" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtQuickShapes" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtQuickWidgets" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtDesigner" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtUiTools" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtQuick" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtMultimediaWidgets" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtHelp" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtUiPlugin" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtQmlWorkerScript" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtQmlModels" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtPrintSupport" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtMultimedia" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtQuickTest" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtQml" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtOpenGLExtensions" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtOpenGL" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtWindowsUIAutomationSupport" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtWidgets" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtAccessibilitySupport" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtThemeSupport" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtFontDatabaseSupport" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtEventDispatcherSupport" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtXml" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtConcurrent" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtTest" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtSql" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtNetwork" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtGui" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/include/QtCore" "C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/bin/archdatadir/mkspecs/win32-msvc" "C:/Users/user/.conan2/p/b/opens769fd176b006d/p/include" "C:/Users/user/.conan2/p/b/pcre23012e7355d789/p/include" "C:/Users/user/.conan2/p/b/doubl939b7f123f641/p/include" "C:/Users/user/.conan2/p/b/freetfdd35eef06d56/p/include" "C:/Users/user/.conan2/p/b/freetfdd35eef06d56/p/include/freetype2" "C:/Users/user/.conan2/p/b/bzip2827565812739f/p/include" "C:/Users/user/.conan2/p/b/brotl6d7426260b727/p/include" "C:/Users/user/.conan2/p/b/brotl6d7426260b727/p/include/brotli" "C:/Users/user/.conan2/p/b/libjp043311aae795c/p/include" "C:/Users/user/.conan2/p/b/libpna37919b28b92d/p/include" "C:/Users/user/.conan2/p/b/zliba252c37263f92/p/include" "C:/Users/user/.conan2/p/b/sqlite216284357a5b/p/include" "C:/Users/user/.conan2/p/b/libpq7b477c5efd65a/p/include" "C:/Users/user/.conan2/p/b/opena7a3b519efd52d/p/include" "C:/Users/user/.conan2/p/b/opena7a3b519efd52d/p/include/AL" "C:/Users/user/.conan2/p/b/zstdf9734e9ec0a3a/p/include" "C:/Users/user/.conan2/p/b/md4c5671ffc7b79cd/p/include")
set(CONAN_RUNTIME_LIB_DIRS "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/qt09bc3566bb965/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/opens769fd176b006d/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/pcre23012e7355d789/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/doubl939b7f123f641/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/freetfdd35eef06d56/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/bzip2827565812739f/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/brotl6d7426260b727/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/libjp043311aae795c/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/libpna37919b28b92d/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/zliba252c37263f92/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/sqlite216284357a5b/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/libpq7b477c5efd65a/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/opena7a3b519efd52d/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/zstdf9734e9ec0a3a/p/bin>" "$<$<CONFIG:Debug>:C:/Users/user/.conan2/p/b/md4c5671ffc7b79cd/p/bin>" )



########## 'pkg_config' block #############
# Define pkg-config from 'tools.gnu:pkg_config' executable and paths

if (DEFINED ENV{PKG_CONFIG_PATH})
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};$ENV{PKG_CONFIG_PATH}")
else()
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};")
endif()


########## 'rpath' block #############
# Defining CMAKE_SKIP_RPATH



########## 'output_dirs' block #############
# Definition of CMAKE_INSTALL_XXX folders

set(CMAKE_INSTALL_BINDIR "bin")
set(CMAKE_INSTALL_SBINDIR "bin")
set(CMAKE_INSTALL_LIBEXECDIR "bin")
set(CMAKE_INSTALL_LIBDIR "lib")
set(CMAKE_INSTALL_INCLUDEDIR "include")
set(CMAKE_INSTALL_OLDINCLUDEDIR "include")


########## 'variables' block #############
# Definition of CMake variables from CMakeToolchain.variables values

# Variables
# Variables  per configuration



########## 'preprocessor' block #############
# Preprocessor definitions from CMakeToolchain.preprocessor_definitions values

# Preprocessor definitions per configuration



if(CMAKE_POLICY_DEFAULT_CMP0091)  # Avoid unused and not-initialized warnings
endif()
