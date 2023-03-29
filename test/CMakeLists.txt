file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "*.c" "*.C" "*.cc" "*.CC" "*.cpp" "*.CPP" "*.c++")

add_executable(fota_test ${SOURCES})

target_include_directories(fota_test PUBLIC
        include)

target_link_libraries(fota_test fota_server gtest gtest_main)