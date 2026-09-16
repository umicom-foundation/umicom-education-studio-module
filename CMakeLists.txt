#-----------------------------------------------------------------------------
# Umicom Education Studio Module
# File: CMakeLists.txt
#
# PURPOSE:
#   Build a thin C23 product composition over Framework-owned application
#   experience, runtime and workbench contracts.
#
# AUTHOR AND ORGANISATION:
#   Sammy Hegab
#   Umicom Foundation
#
# LICENCE:
#   MIT
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

# Load the dependency only when the parent build has not already provided its target.
if(NOT TARGET Umicom::Framework)
    find_package(UmicomFramework CONFIG REQUIRED)
endif()

# Load the dependency only when the parent build has not already provided its target.
if(NOT TARGET Umicom::application)
    message(FATAL_ERROR
        "Umicom Education Studio requires Framework target Umicom::application")
endif()

# Define the local fallback only when the parent build did not provide the shared helper.
if(NOT COMMAND umicom_apply_warnings)
    # Define the apply warnings build helper so parent and application projects apply one
    # consistent rule.
    function(umicom_apply_warnings target)
        # Select the warning options understood by the active compiler.
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4)
        # Use this fallback path when the earlier condition does not apply.
        else()
            target_compile_options(${target} PRIVATE
                -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
        endif()
    endfunction()
endif()

# Define the local fallback only when the parent build did not provide the shared helper.
if(NOT COMMAND umicom_apply_sanitizers)
    # Define the apply sanitizers build helper so parent and application projects apply one
    # consistent rule.
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

# Create this optional product surface only when its build option is enabled.
if(UMICOM_EDUCATION_BUILD_CONSOLE)
    add_executable(umicom-education-console
        src/console/main.c)
    target_link_libraries(umicom-education-console PRIVATE Umicom::education_module)
    umicom_apply_warnings(umicom-education-console)
    umicom_apply_sanitizers(umicom-education-console)
endif()

# Register verification targets only when the developer has enabled testing.
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
# Configure the optional target only when its feature has created it.
if(TARGET umicom-education-console)
    install(TARGETS umicom-education-console
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES application.umicom.yaml
    DESTINATION ${CMAKE_INSTALL_DATADIR}/umicom/applications/education)
# Use the optional file only when it is present in this checkout.
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

# The lessons frontend is presentation only. Framework remains the sole
# catalogue, lesson resource and learning-plan owner; no local lesson table.
if(UMICOM_EDUCATION_BUILD_CONSOLE)
    if(NOT TARGET Umicom::developer)
        message(FATAL_ERROR "Education lessons require Framework target Umicom::developer")
    endif()
    add_executable(umicom-education-lessons src/console/lessons.c)
    target_link_libraries(umicom-education-lessons PRIVATE Umicom::developer)
    umicom_apply_warnings(umicom-education-lessons)
    umicom_apply_sanitizers(umicom-education-lessons)
    install(TARGETS umicom-education-lessons
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Learning)
    if(BUILD_TESTING)
        add_test(NAME education.learning.list COMMAND umicom-education-lessons --list)
        add_test(NAME education.learning.git COMMAND umicom-education-lessons --lesson foundations.git-workflow)
        add_test(NAME education.learning.c COMMAND umicom-education-lessons --lesson foundations.bounded-strings)
        add_test(NAME education.learning.assembly COMMAND umicom-education-lessons --lesson foundations.assembly-loops)
        add_test(NAME education.learning.unknown COMMAND umicom-education-lessons --lesson missing.lesson)
        set_tests_properties(education.learning.unknown PROPERTIES WILL_FAIL TRUE)
        add_test(NAME education.learning.arguments COMMAND umicom-education-lessons --lesson)
        set_tests_properties(education.learning.arguments PROPERTIES WILL_FAIL TRUE)
        set_tests_properties(education.learning.list education.learning.git education.learning.c
            education.learning.assembly education.learning.unknown education.learning.arguments
            PROPERTIES LABELS "education;learning;framework;regression" TIMEOUT 15)
        if(COMMAND umicom_register_validation_target)
            umicom_register_validation_target(umicom-education-lessons)
        endif()
    endif()
endif()
