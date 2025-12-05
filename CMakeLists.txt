cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 1.0.${PATCH_VERSION})

project(lab3 VERSION ${PROJECT_VERSION})

#
# Основная программа
#
add_executable(lab3
    main.cpp
)

target_compile_features(lab3 PRIVATE cxx_std_20)

if (MSVC)
    target_compile_options(lab3 PRIVATE /W4)
else()
    target_compile_options(lab3 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS lab3 RUNTIME DESTINATION bin)


#
# Пакетирование
#
if(UNIX)
    set(CPACK_GENERATOR "DEB")
else()
    set(CPACK_GENERATOR "ZIP")
endif()

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT "example@example.com")

include(CPack)


#
# Тесты
#
enable_testing()

add_test(NAME test_func COMMAND lab3)

