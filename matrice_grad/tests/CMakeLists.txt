cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/tools)

project(matriceGrad)

set(MPFR_LIB_PATH
	/usr/local/lib)

set(GMP_LIB_PATH
        /usr/local/lib)
        
set(CHECK_LIB_PATH
        /usr/local/lib/libcheck.so.0)

# If pkg-config is not installed on the system, then the
# CHECK_INSTALL_DIR variable must be set to the install
# location of Check. For example, on Windows, this may
# be: C:/Program Files/check
set(CHECK_INSTALL_DIR "/usr/local/lib")

find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})


#add_library(libmpfr SHARED IMPORTED GLOBAL)
#add_library(libgmp SHARED IMPORTED GLOBAL)

set_target_properties(libmpfr PROPERTIES IMPORTED_LOCATION ${MPFR_LIB_PATH})
set_target_properties(libgmp PROPERTIES IMPORTED_LOCATION ${GMP_LIB_PATH})


# Array utils
set(ARRAY_UTILS_TEST_SOURCES
  check_array_utils.c
)

add_executable(check_array_utils ${ARRAY_UTILS_TEST_SOURCES})
target_link_libraries(check_array_utils tools 
                                        ${CHECK_LIB_PATH}
					${CHECK_LIBRARIES}
					libmpfr.a
                                        libgmp.a)


# Matrix utils
set(MATRIX_UTILS_TEST_SOURCES
  check_matrix_utils.c
)

add_executable(check_matrix_utils ${MATRIX_UTILS_TEST_SOURCES})
target_link_libraries(check_matrix_utils tools 
                                        ${CHECK_LIB_PATH}
                                        ${CHECK_LIBRARIES}
                                        libmpfr.a
                                        libgmp.a)

                                        
# Custom math
set(CUSTOM_MATH_TEST_SOURCES
  check_custom_math.c
)

add_executable(check_custom_math ${CUSTOM_MATH_TEST_SOURCES})
target_link_libraries(check_custom_math tools 
                                        ${CHECK_LIB_PATH}
                                        ${CHECK_LIBRARIES}
                                        libmpfr.a
                                        libgmp.a)
                                        