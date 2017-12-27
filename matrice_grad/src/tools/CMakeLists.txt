set(LIB_SOURCES
  arrayUtils.c
  errorHandling.c
  inputOutput.c
  matrixUtils.c
  customMath.c
  utils.c
)

set(BSD_LIB_PATH
        /usr/include/bsd)

set(HEADERS 
  ${CONFIG_HEADER}
  arrayUtils.h
  errorHandling.h
  inputOutput.h
  matrixUtils.h
  customMath.h
  utils.h
  timer.h
)

project(matriceGrad)

add_library(tools STATIC ${LIB_SOURCES} ${HEADERS})
add_library(libbsd SHARED IMPORTED GLOBAL)

set_target_properties(libbsd PROPERTIES IMPORTED_LOCATION ${BSD_LIB_PATH})

find_package(Threads REQUIRED)
target_link_libraries(tools ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} libbsd.a)

install(TARGETS tools
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/arrayUtils.h ${CMAKE_CURRENT_SOURCE_DIR}/matrixUtils.h DESTINATION include)

# install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/matrixUtils.h DESTINATION include)
