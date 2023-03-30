file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "*.c" "*.C" "*.cc" "*.CC" "*.cpp" "*.CPP" "*.c++")

add_library(fota_main SHARED ${SOURCES})

target_include_directories(fota_main
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        )

target_link_libraries(fota_main PRIVATE fota_server)

target_compile_options(fota_main PUBLIC -fPIC)
