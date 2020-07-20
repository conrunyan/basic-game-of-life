cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

set (SRC_DIR src)
set (INC_DIR ${SRC_DIR}/include)

set (SOURCE_FILES
    ${SRC_DIR}/LifeSimulator.cpp
    ${SRC_DIR}/PatternAcorn.cpp
    ${SRC_DIR}/PatternBlinker.cpp
    ${SRC_DIR}/PatternBlock.cpp
    ${SRC_DIR}/PatternGlider.cpp
    ${SRC_DIR}/PatternGosperGliderGun.cpp
    ${SRC_DIR}/RendererConsole.cpp 
)

set (HEADER_FILES
    ${INC_DIR}/LifeSimulator.hpp
    ${INC_DIR}/Pattern.hpp
    ${INC_DIR}/PatternAcorn.hpp
    ${INC_DIR}/PatternBlinker.hpp
    ${INC_DIR}/PatternBlock.hpp
    ${INC_DIR}/PatternGlider.hpp
    ${INC_DIR}/PatternGosperGliderGun.hpp
    ${INC_DIR}/Renderer.hpp
    ${INC_DIR}/RendererConsole.hpp
)

set (UNIT_TEST_FILES
    ${SRC_DIR}/TestGameOfLife.cpp
)

add_executable(ConwaysLife ${SOURCE_FILES} ${HEADER_FILES} ${INC_DIR}/rlutil.h main.cpp)
add_executable(UnitTestRunner ${SOURCE_FILES} ${HEADER_FILES} ${UNIT_TEST_FILES})

target_include_directories(ConwaysLife PUBLIC ${INC_DIR})
target_include_directories(UnitTestRunner PUBLIC ${INC_DIR})

set_property(TARGET ConwaysLife PROPERTY CXX_STANDARD 17)

# Call Clang Format on build, if it is present on the system
find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    unset(SOURCE_FILE_PATHS)
	unset(HEADER_FILE_PATHS)
	unset(TESTING_FILE_PATHS)
	unset(MAIN_PATH)

	# format source files
    foreach(SOURCE_FILE ${SOURCE_FILES})
		get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
		set(SOURCE_FILE_PATHS ${SOURCE_FILE_PATHS} ${WHERE})
    endforeach()
	# format header files
	foreach(HEADER_FILE ${HEADER_FILES})
		get_source_file_property(WHERE ${HEADER_FILE} LOCATION)
		set(HEADER_FILE_PATHS ${HEADER_FILE_PATHS} ${WHERE})
    endforeach()
	# format test files
	foreach(TEST_FILE ${UNIT_TEST_FILES})
		get_source_file_property(WHERE ${TEST_FILE} LOCATION)
		set(TESTING_FILE_PATHS ${TESTING_FILE_PATHS} ${WHERE})
    endforeach()
	# get main path
	get_source_file_property(WHERE main.cpp LOCATION)
	set(MAIN_PATH ${MAIN_PATH} ${WHERE})

    add_custom_target(
        ClangFormat
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${SOURCE_FILE_PATHS}
		${HEADER_FILE_PATHS}
		${TESTING_FILE_PATHS}
		${MAIN_PATH}
    )
    add_dependencies(ConwaysLife ClangFormat)
	add_dependencies(UnitTestRunner ClangFormat)
endif()

set_property(TARGET ConwaysLife PROPERTY CXX_STANDARD 17)

# Project Build step
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(ConwaysLife PRIVATE /W4 /permissive-)
	target_compile_options(UnitTestRunner PRIVATE /W4 /permissive-)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(ConwaysLife PRIVATE -Wall -Wextra -pedantic -g3)
	target_compile_options(UnitTestRunner PRIVATE -Wall -Wextra -pedantic)
endif()

#
# Add GoogleTest
#
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Now simply link against gtest or gtest_main as needed. Eg
target_link_libraries(UnitTestRunner gtest_main)
