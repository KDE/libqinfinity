# Find libinfinitymm
#
# This script will define:
#	LIBQINFINITYMM_FOUND
#	LIBQINFINITYMM_INCLUDES
#	LIBQINFINITYMM_LIBRARY
#	LIBQINFINITYMM_LIBRARIES
#
# Copyright (c) 2008 Gregory Haynes <greg@greghaynes.net>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

if( LIBQINFINITYMM_LIBRARIES AND LIBQINFINITYMM_INCLUDES )
	
	set( LIBQINFINITYMM_FOUND true )

else( LIBQINFINITYMM_LIBRARIES AND LIBQINFINITYMM_INCLUDES )
	
	set( LIBQINFINITYMM_FOUND false )
	
# dependancies
	FIND_PACKAGE(Libinfinitymm REQUIRED)
	
	if( ${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} EQUAL 4 )
		include(UsePkgConfig)
		pkgconfig(libinfinitymm-1.0
			_LIBINFINITYMM_INCLUDE_DIR
			_LIBINFINITYMM_LIBRARY_DIR
			_LIBINFINITYMM_LINKER_FLAGS
			_LIBINFINITYMM_COMPILER_FLAGS
		)
	endif( ${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} EQUAL 4 )
	
	find_path( LIBINFINITYMM_INCLUDE_DIR
		NAMES
			libinfinitymm/init.h
		PATHS
			${_LIBINFINITYMM_INCLUDE_DIR}
			/usr/include
			/usr/local/include
			/opt/local/include
		PATH_SUFFIXES
			libinfinitymm-1.0
	)
	
	find_library( LIBINFINITYMM_LIBRARY
		NAMES
			infinitymm-1.0
		PATHS
			${_LIBINFINITYMM_LIBRARY_DIR}
			/usr/lib
			/usr/local/lib
	)
	
	set( LIBQINFINITYMM_INCLUDES
		${LIBINFINITYMM_INCLUDE_DIR}
		${LIBINFINITY_INCLUDES}
	)
	
	set( LIBQINFINITYMM_LIBRARIES
		${LIBINFINITYMM_LIBRARY}
	)

endif( LIBQINFINITYMM_LIBRARIES AND LIBQINFINITYMM_INCLUDES )
