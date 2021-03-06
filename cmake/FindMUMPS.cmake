
# Find MUMPS
#
# Find the MUMPS includes and library
#
# if you need to add a custom library search path, do it via via CMAKE_PREFIX_PATH
#
# This module defines
#  MUMPS_INCLUDE_DIRS, where to find header, etc.
#  MUMPS_LIBRARIES, the libraries needed to use MUMPS.
#  MUMPS_FOUND, If false, do not try to use MUMPS.
#  MUMPS_INCLUDE_PREFIX, include prefix for MUMPS

# only look in default directories
find_path(
	MUMPS_INCLUDE_DIR
	NAMES MUMPS/dmumps_c.h dmumps_c.h
	DOC "MUMPS include dir"
)

find_library(
	MUMPS_LIBRARY
	NAMES dmumps_seq dmumps
	DOC "MUMPS library"
)

set(MUMPS_INCLUDE_DIRS ${MUMPS_INCLUDE_DIR})
set(MUMPS_LIBRARIES ${MUMPS_LIBRARY})

# find MUMPS_INCLUDE_PREFIX
find_path(
	MUMPS_INCLUDE_PREFIX
	NAMES dmumps_c.h
	PATH_SUFFIXES MUMPS
)

if (${MUMPS_INCLUDE_PREFIX} MATCHES "MUMPS")
	set(MUMPS_INCLUDE_DIR "${MUMPS_INCLUDE_DIR}/MUMPS")
endif()

# handle the QUIETLY and REQUIRED arguments and set MUMPS_FOUND to TRUE
# if all listed variables are TRUE, hide their existence from configuration view
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MUMPS DEFAULT_MSG MUMPS_INCLUDE_DIR MUMPS_LIBRARY)
mark_as_advanced (MUMPS_INCLUDE_DIR MUMPS_LIBRARY)
