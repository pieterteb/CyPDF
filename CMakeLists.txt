cmake_minimum_required(VERSION 3.10)

project(CyPDF 
    VERSION 0.0 
    LANGUAGES C
)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE c_std_11)

set(gcc_like_c "$<COMPILE_LANG_AND_ID:C,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_c "$<COMPILE_LANG_AND_ID:C,MSVC>")

target_compile_options(compiler_flags INTERFACE
    "$<${gcc_like_c}:$<BUILD_INTERFACE:-fdiagnostics-color=always;-Wall;-Wextra;-Wpedantic;-Werror;-Wshadow;-Wformat=2;-Wconversion;-Wunused-parameter>>"
    "$<${msvc_c}:$<BUILD_INTERFACE:-W3>>"
)

add_executable(CyPDF 
    src/main.c
    src/cypdf_array.c
    src/cypdf_bool.c
    src/cypdf_catalog.c
    src/cypdf_dict.c
    src/cypdf_doc.c
    src/cypdf_header.c
    src/cypdf_info.c
    src/cypdf_list.c
    src/cypdf_name.c
    src/cypdf_null.c
    src/cypdf_number.c
    src/cypdf_object.c
    src/cypdf_pages.c
    src/cypdf_print.c
    src/cypdf_real.c
    src/cypdf_stream.c
    src/cypdf_string.c
    src/cypdf_trailer.c
    src/cypdf_utils.c
    src/cypdf_xref.c
    src/md5.c
)

target_link_libraries(CyPDF PUBLIC compiler_flags)

target_include_directories(CyPDF PUBLIC "${PROJECT_SOURCE_DIR}/include")
