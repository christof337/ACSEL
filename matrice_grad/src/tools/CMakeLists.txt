set(LIB_SOURCES
  arrayUtils.c
  errorHandling.c
  inputOutput.c
  matrixUtils.c
)

set(MAIN_SOURCES
  arrayUtils.c
  errorHandling.c
  inputOutput.c
  matrixUtils.c
)

set(HEADERS 
  ${CONFIG_HEADER}
  arrayUtils.h
  errorHandling.h
  inputOutput.h
  matrixUtils.h
)

add_library(tools STATIC ${LIB_SOURCES} ${HEADERS})

find_package(Threads REQUIRED)
target_link_libraries(tools ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

#add_executable(main ${HEADERS} ${MAIN_SOURCES})
#target_link_libraries(main tools)

install(TARGETS tools
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/arrayUtils.h ${CMAKE_CURRENT_SOURCE_DIR}/matrixUtils.h DESTINATION include)

# install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/matrixUtils.h DESTINATION include)