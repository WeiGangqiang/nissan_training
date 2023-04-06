cmake_minimum_required (VERSION 3.4)
project (fotaTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-invalid-offsetof -g -std=c++14 -D_GLIBCXX_USE_CXX11_ABI=0")

include(cmake/gtest.cmake)
include(cmake/gbenchmark.cmake)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(main)

# 配置 CPack
set(CPACK_GENERATOR "RPM")
set(CPACK_PACKAGE_NAME "fota_server")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_RELEASE "1")
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")
install(FILES build/test/fota_test DESTINATION /usr/local)
install(FILES ./output/gtest/lib/libgtest.so ./output/gtest/lib/libgtest_main.so DESTINATION /code/Turing/nissan_training/output/gtest/lib)

include(CPack)


