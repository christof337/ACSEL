include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tools)

set(LIB_SOURCES
  main.c
  matrice_grad.c
)

set(MAIN_SOURCES
  main.c
  matrice_grad.c
)

set(HEADERS 
  ${CONFIG_HEADER}
  matrice_grad.h
)

add_library(matrice_grad STATIC ${LIB_SOURCES} ${HEADERS})

add_executable(main ${HEADERS} ${MAIN_SOURCES})
target_link_libraries(main matrice_grad)
target_link_libraries(main tools ${CHECK_LIBRARIES})

install(TARGETS matrice_grad
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/matrice_grad.h DESTINATION include)
