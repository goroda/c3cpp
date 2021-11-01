cmake_minimum_required(VERSION 3.10)

set(header approx_opts.h
  c3_cpp.h
  core.h
  function_train.h
  functions.h
  sobol.h
  optimize.h
  utils.h)


set(SRC approx_opts.cpp
  function_train.cpp
  functions.cpp
  optimize.cpp
  sobol.cpp
  utils.cpp)


#create a libray containing everything!
# file(GLOB SRC_FILES */*.c)
add_library(c3cpp SHARED ${SRC})
target_link_libraries(c3cpp
  ${blas_lapack}
  -lm
  ${c3lib}
  )

install(TARGETS c3cpp DESTINATION lib)
install(FILES ${header} DESTINATION include/c3sc)
