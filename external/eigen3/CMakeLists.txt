cmake_minimum_required(VERSION 3.0)
project(eigen3_builder CXX)
include(ExternalProject)
find_package(Hg REQUIRED)

ExternalProject_Add(
    eigen3
    PREFIX ${CMAKE_BINARY_DIR}/eigen3
    HG_REPOSITORY https://bitbucket.org/eigen/eigen/
    TIMEOUT 10
    UPDATE_COMMAND ""
    HG_TAG a67d661
    #HG_TAG 138971d # works with linear solver error
    # HG_TAG 03bb4ad
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
   )

ExternalProject_Get_Property(eigen3 source_dir)
set(EIGEN_INCLUDE_DIR ${source_dir} CACHE INTERNAL "Path to include folder for Eigen 3")
