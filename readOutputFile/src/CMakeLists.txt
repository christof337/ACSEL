set(MATRIX_GRAD_DIRECTORY
        /home/kito/Dev/Sources/ACSEL/matrice_grad)

include_directories(${MATRIX_GRAD_DIRECTORY}/src/tools)

project(readOutputFile)

set(MPFR_LIB_PATH
        /usr/local/lib)

set(GMP_LIB_PATH
        /usr/local/lib)

set(LIB_SOURCES
  readOutputFile.c
# ${MATRIX_GRAD_DIRECTORY}/src/tools/utils.c
)

set(MAIN_SOURCES
  readOutputFile.c
#  ${MATRIX_GRAD_DIRECTORY}/src/tools/utils.c
)

set(HEADERS 
  ${CONFIG_HEADER}
  ${MATRIX_GRAD_DIRECTORY}/src/tools/utils.h
  readOutputFile.h
)

add_library(libmpfr SHARED IMPORTED GLOBAL)
add_library(libgmp SHARED IMPORTED GLOBAL)

set_target_properties(libmpfr PROPERTIES IMPORTED_LOCATION ${MPFR_LIB_PATH})
set_target_properties(libgmp PROPERTIES IMPORTED_LOCATION ${GMP_LIB_PATH})

add_library(readOutputFile STATIC ${LIB_SOURCES} ${HEADERS})

add_executable(main ${HEADERS} ${MAIN_SOURCES})
target_link_libraries(main readOutputFile
                        tools
                        libmpfr.a
                        libgmp.a
                        )
                       
                        
install(TARGETS readOutputFile
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

#install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/matrice_grad.h DESTINATION include)

#find_package(FindThreads)
#if ( CMAKE_USE_PTHREADS_INIT )
#        target_include_directories(main PUBLIC ${Fin
