PROJECT(libqinfinity)

find_package(Libinfinity REQUIRED)

set(LIBS ${LIBS} ${LIBINFINITY_LIBRARIES})
set(QInfinity_SRCS
	init.cpp)

include_directories(${LIBINFINITY_INCLUDES})

ADD_LIBRARY(qinfinity SHARED ${QInfinity_SRCS})
TARGET_LINK_LIBRARIES(qinfinity ${LIBS})
