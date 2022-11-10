cmake_minimum_required(VERSION 3.15)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(gcc_lik_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
set(DEBUG 0)

project(homework-3 VERSION ${PROJECT_VERSION})
option(WITH_CATCH_TEST "Whether to build Catch2 test" ON)

add_executable(main main.cpp allocator.hpp)

set_target_properties(main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)

if(WITH_CATCH_TEST)
    find_package(Catch2 REQUIRED)

    add_executable(tests test_list.cpp test_allocator.cpp)

    target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

    set_target_properties(tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

    target_compile_options(tests PUBLIC
        $<$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>:-Wall -Wextra -pedantic -Werror -DDEBUG=${DEBUG}>
        $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:-W4>)

    enable_testing()

    add_test(tests tests)


endif()

target_compile_options(main PUBLIC
    $<$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>:-Wall -Wextra -pedantic -Werror -g -DDEBUG=${DEBUG}>
    $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:-W4>)


install(TARGETS main RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT dusk-comes@email.com)
include(CPack)
