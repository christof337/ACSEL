include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/tools)

# If pkg-config is not installed on the system, then the
# CHECK_INSTALL_DIR variable must be set to the install
# location of Check. For example, on Windows, this may
# be: C:/Program Files/check
# set(CHECK_INSTALL_DIR "C:/Program Files/check")

find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})

set(ARRAY_UTILS_TEST_SOURCES
  check_array_utils.c
)

add_executable(check_array_utils ${ARRAY_UTILS_TEST_SOURCES})
target_link_libraries(check_array_utils tools ${CHECK_LIBRARIES})


set(MATRIX_UTILS_TEST_SOURCES
  check_matrix_utils.c
)

add_executable(check_matrix_utils ${MATRIX_UTILS_TEST_SOURCES})
target_link_libraries(check_matrix_utils tools ${CHECK_LIBRARIES})