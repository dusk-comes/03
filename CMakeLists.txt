cmake_minimum_required(VERSION 3.15)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(gcc_lik_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

project(homework-3 VERSION ${PROJECT_VERSION})
option(WITH_CATCH_TEST "Whether to build Catch2 test" ON)

add_executable(main main.cpp allocator.hpp)

set_target_properties(main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)

if(WITH_CATCH2_TEST)
    add_executable(test_alloc test_allocator.cpp)

    set_target_properties(test_alloc PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

    add_library(Catch INTERFACE)

    enable_testing()
    add_test(test_alloc test_alloc)

endif()

target_compile_options(main PUBLIC
    $<$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>:-Wall -Wextra -pedantic -Werror -g>
    $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:-W4>)

target_compile_options(test_alloc PUBLIC
    $<$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>:-Wall -Wextra -pedantic -Werror>
    $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:-W4>)

install(TARGETS main RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT dusk-comes@email.com)
include(CPack)
