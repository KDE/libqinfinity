PROJECT(libqinfinity)

find_package(Libinfinity REQUIRED)
find_package(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})

set(LIBS ${LIBS} ${LIBINFINITY_LIBRARIES} ${QT_LIBRARIES})
set(QInfinity_SRCS
	init.cpp
	qgobject.cpp
	qtio.cpp
	qtiowatch.cpp
	ipaddress.cpp
	tcpconnection.cpp
	xmlconnection.cpp
	xmppconnection.cpp
	communicationmanager.cpp
	browser.cpp
	browseriter.cpp
	sessionproxy.cpp
	session.cpp)

set(QInfinity_HDRS
	init.h
	qgobject.h
	qtio.h
	qtiowatch.h
	ipaddress.h
	tcpconnection.h
	tcpconnection.h
	xmlconnection.h
	xmppconnection.h
	communicationmanager.h
	browser.h
	sessionproxy.h
	session.h)

QT4_AUTOMOC(${QInfinity_SRCS})

include_directories(${LIBINFINITY_INCLUDES})

ADD_LIBRARY(qinfinity SHARED ${QInfinity_SRCS})

SET_TARGET_PROPERTIES(qinfinity
	PROPERTIES
	VERSION 0.1
	SOVERSION 1)

TARGET_LINK_LIBRARIES(qinfinity ${LIBS})

INSTALL(TARGETS qinfinity
	DESTINATION lib)

INSTALL(FILES ${QInfinity_HDRS}
	DESTINATION include/libqinfinity-1.0/libqinfinity)

