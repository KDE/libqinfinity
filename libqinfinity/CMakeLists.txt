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

QT4_AUTOMOC(${QInfinity_SRCS})

include_directories(${LIBINFINITY_INCLUDES})

ADD_LIBRARY(qinfinity SHARED ${QInfinity_SRCS})
TARGET_LINK_LIBRARIES(qinfinity ${LIBS})
