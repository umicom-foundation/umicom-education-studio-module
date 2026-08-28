#-----------------------------------------------------------------------------
# Umicom Education Studio Module
# File: CMakeLists.txt
#
# PURPOSE:
#   Build a thin C23 product composition over Framework-owned application
#   experience, runtime and workbench contracts.
#
# Created by: Sammy Hegab
# Organisation: Umicom Foundation
# Licence: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)

project(
    EducationStudioModule
    VERSION 0.1.0
    DESCRIPTION "Thin Umicom Education Studio composition over Umicom Framework"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(UMICOM_EDUCATION_BUILD_CONSOLE
       "Build the native Umicom Education Studio verification console"
       ON)

include(CTest)
include(GNUInstallDirs)

if(NOT TARGET Umicom::Framework)
    find_package(UmicomFramework CONFIG REQUIRED)
endif()

if(NOT TARGET Umicom::application)
    message(FATAL_ERROR
        "Umicom Education Studio requires Framework target Umicom::application")
endif()

if(NOT COMMAND umicom_apply_warnings)
    function(umicom_apply_warnings target)
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4)
        else()
            target_compile_options(${target} PRIVATE
                -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
        endif()
    endfunction()
endif()

if(NOT COMMAND umicom_apply_sanitizers)
    function(umicom_apply_sanitizers target)
    endfunction()
endif()

add_library(umicom_education_module STATIC
    src/application.c
    src/workspace.c
)
add_library(Umicom::education_module ALIAS umicom_education_module)

target_include_directories(umicom_education_module PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(umicom_education_module PUBLIC
    Umicom::Framework
    Umicom::application
)
umicom_apply_warnings(umicom_education_module)
umicom_apply_sanitizers(umicom_education_module)

include(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../framework/cmake/UmicomThinApplicationRuntime.cmake")
umicom_extend_thin_application_runtime(
    NAME "education"
    TARGET "umicom_education_module")

if(UMICOM_EDUCATION_BUILD_CONSOLE)
    add_executable(umicom-education-console
        src/console/main.c)
    target_link_libraries(umicom-education-console PRIVATE Umicom::education_module)
    umicom_apply_warnings(umicom-education-console)
    umicom_apply_sanitizers(umicom-education-console)
endif()

if(BUILD_TESTING)
    add_executable(education-application-test
        tests/test_application.c)
    target_link_libraries(education-application-test PRIVATE Umicom::education_module)
    umicom_apply_warnings(education-application-test)
    umicom_apply_sanitizers(education-application-test)
    add_test(NAME education.module.application
             COMMAND education-application-test)

    add_executable(education-workspace-test
        tests/test_workspace.c)
    target_link_libraries(education-workspace-test PRIVATE Umicom::education_module)
    umicom_apply_warnings(education-workspace-test)
    umicom_apply_sanitizers(education-workspace-test)
    add_test(NAME education.module.workspace
             COMMAND education-workspace-test)
endif()

install(TARGETS umicom_education_module
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
if(TARGET umicom-education-console)
    install(TARGETS umicom-education-console
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES application.umicom.yaml
    DESTINATION ${CMAKE_INSTALL_DATADIR}/umicom/applications/education)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    install(FILES LICENSE
        DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/education)
endif()

message(STATUS "Umicom Education Studio Module version: ${PROJECT_VERSION}")
message(STATUS "Umicom Education Studio uses Framework-owned application experience")

include(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../framework/cmake/UmicomApplicationProductisationContribution.cmake")
umicom_add_application_productisation_contribution(
    NAME "education"
    TARGET umicom_education_productisation
    SOURCE "src/productisation_contribution.c"
    TEST_SOURCE "tests/test_productisation_contribution.c")
