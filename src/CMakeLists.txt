file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "*.c" "*.C" "*.cc" "*.CC" "*.cpp" "*.CPP" "*.c++")

add_library(fota_server STATIC ${SOURCES})

target_include_directories(fota_server
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        )
