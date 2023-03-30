file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "*.c" "*.C" "*.cc" "*.CC" "*.cpp" "*.CPP" "*.c++")

add_library(fota_server STATIC ${SOURCES})

target_include_directories(fota_server
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        )

target_link_libraries(fota_server PUBLIC pthread)

target_compile_options(fota_server PUBLIC -fPIC)
