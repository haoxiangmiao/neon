# Remove the main file to make a library
file(GLOB_RECURSE NEON_SOURCES "*.cpp")
list(REMOVE_ITEM NEON_SOURCES "neon.cpp")

add_library(neon ${NEON_SOURCES})

target_compile_options(neon PUBLIC $<$<CONFIG:RELEASE>:-O3>)

set_target_properties(neon
                      PROPERTIES CXX_STANDARD
                                 17
                                 CXX_STANDARD_REQUIRED
                                 YES
                                 CXX_EXTENSIONS
                                 NO
                                 COMPILE_FLAGS
                                 "-Wall -Wunused-parameter")

if(ENABLE_LTO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT is_ipo_supported)
  if(is_ipo_supported)
    set_target_properties(neon PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()
endif()

if(ENABLE_NATIVE)
  target_compile_options(neon
                         PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-march=native
                                -mtune=native>)
endif()

if(ENABLE_FAST_MATH)
  target_compile_options(neon
                         PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-fassociative-math
                                -fno-signed-zeros
                                -fno-trapping-math
                                -fno-math-errno>)
endif()

if(ENABLE_COVERAGE)
  set_target_properties(neon PROPERTIES COMPILE_FLAGS "--coverage")
  target_link_libraries(neon PRIVATE --coverage)
endif()

if(ENABLE_PROFILE)
  set_target_properties(neon PROPERTIES COMPILE_FLAGS "-fno-omit-frame-pointer")
endif()

target_include_directories(neon
                           PUBLIC ${CMAKE_SOURCE_DIR}/src
                                  ${Boost_INCLUDE_DIR}
                                  ${JSON_INCLUDE_DIR}
                                  ${MUMPS_INCLUDE_DIR}
                                  ${EIGEN_INCLUDE_DIR}
                                  ${VTK_INCLUDE_DIRS}
                                  ${RV3_INCLUDE_DIR}
                                  ${TERMCOLOR_INCLUDE_DIR})

add_dependencies(neon eigen3 range-v3 termcolor json)

if(ENABLE_CUDA)
  add_library(dmatvec
              ${CMAKE_SOURCE_DIR}/src/solver/linear/dmatrix_vector_product.cu)

  add_dependencies(neon dmatvec)

  target_link_libraries(neon
                        PRIVATE dmatvec
                                ${CUDA_cusparse_LIBRARY}
                                ${CUDA_cublas_LIBRARY}
                                ${CUDA_cusolver_LIBRARY})
  target_include_directories(neon PUBLIC ${CUDA_INCLUDE_DIRS})
endif()

if(ENABLE_OPENCL)
  target_link_libraries(neon PRIVATE OpenCL::OpenCL)
  target_include_directories(neon PUBLIC ${VIENNACL_INCLUDE_DIRS})
endif()

target_link_libraries(neon
                      PUBLIC OpenMP::OpenMP_CXX
                      PRIVATE Boost::filesystem
                              ${MUMPS_LIBRARY}
                              ${BLAS_LIBRARIES}
                              ${VTK_LIBRARIES}
                              ${TBB_LIBRARIES}
                              ${PASTIX_LIBRARIES}
                              ${ARPACK_LIBRARY})
