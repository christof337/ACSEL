include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tools)

project(matriceGrad)

set(MPFR_LIB_PATH
	/usr/local/lib)

set(GMP_LIB_PATH
	/usr/local/lib)

set(LIB_SOURCES
  main.c
  matrice_grad.c
  parameters.c
  log.c
  help.c
)

set(MAIN_SOURCES
  main.c
)

set(HEADERS 
  ${CONFIG_HEADER}
  matrice_grad.h
  parameters.h
  log.h
  help.h
)


add_library(libmpfr SHARED IMPORTED GLOBAL)
add_library(libgmp SHARED IMPORTED GLOBAL)

set_target_properties(libmpfr PROPERTIES IMPORTED_LOCATION ${MPFR_LIB_PATH})
set_target_properties(libgmp PROPERTIES IMPORTED_LOCATION ${GMP_LIB_PATH})

add_library(matrice_grad STATIC ${LIB_SOURCES} ${HEADERS})

add_executable(main ${HEADERS} ${MAIN_SOURCES})
target_link_libraries(main matrice_grad
                        tools
                        libmpfr.a
                        libgmp.a
                        ${CHECK_LIBRARIES})

install(TARGETS matrice_grad
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

#install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/matrice_grad.h DESTINATION include)

#find_package(FindThreads)
#if ( CMAKE_USE_PTHREADS_INIT )
#        target_include_directories(main PUBLIC ${Fin
