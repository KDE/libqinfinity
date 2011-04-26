PROJECT(libqinfinity)

find_package(Libinfinity REQUIRED)
find_package(Libinftext REQUIRED)
find_package(Qt4 REQUIRED)

set(QT_USE_QTNETWORK true)
INCLUDE(${QT_USE_FILE})

set(LIBS ${LIBS} ${LIBINFINITY_LIBRARIES} ${LIBINFTEXT_LIBRARIES} ${QT_LIBRARIES})
set(QInfinity_SRCS
	init.cpp
	qgobject.cpp
	qgsignal.cpp
	wrapperstore.cpp
	qtio.cpp
	qtiowatch.cpp
	certificatecredentials.cpp
	ipaddress.cpp
	tcpconnection.cpp
	xmlconnection.cpp
	xmppconnection.cpp
	communicationmanager.cpp
	communicationjoinedgroup.cpp
	user.cpp
	adopteduser.cpp
	usertable.cpp
	request.cpp
	userrequest.cpp
	explorerequest.cpp
	browser.cpp
	browseriter.cpp
	sessionproxy.cpp
	session.cpp
	adoptedsession.cpp
	textsession.cpp
	browsermodel.cpp
	browseritemfactory.cpp
	usersmodel.cpp
	buffer.cpp
	textchunk.cpp
	textbuffer.cpp
	abstracttextbuffer.cpp
	textdefaultbuffer.cpp
	noteplugin.cpp
	defaulttextplugin.cpp)

set(QInfinity_HDRS
	init.h
	qgobject.h
	qgsignal.h
	wrapperstore.h
	qtio.h
	qtiowatch.h
	certificatecredentials.h
	ipaddress.h
	tcpconnection.h
	tcpconnection.h
	xmlconnection.h
	xmppconnection.h
	communicationmanager.h
	communicationjoinedgroup.h
	user.h
	adopteduser.h
	usertable.h
	request.h
	userrequest.h
	explorerequest.h
	browser.h
	browseriter.h
	sessionproxy.h
	session.h
	adoptedsession.h
	textsession.h
	browsermodel.h
	browseritemfactory.h
	usersmodel.h
	buffer.h
	textchunk.h
	textbuffer.h
	abstracttextbuffer.h
	textdefaultbuffer.h
	noteplugin.h
	defaulttextplugin.h)

QT4_AUTOMOC(${QInfinity_SRCS})

include_directories(${LIBINFINITY_INCLUDES} ${LIBINFTEXT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

ADD_LIBRARY(qinfinity SHARED ${QInfinity_SRCS})

SET_TARGET_PROPERTIES(qinfinity
	PROPERTIES
	VERSION 3.0.0
	SOVERSION 3)

TARGET_LINK_LIBRARIES(qinfinity ${LIBS})

INSTALL(TARGETS qinfinity
	DESTINATION lib${LIB_SUFFIX})

INSTALL(FILES ${QInfinity_HDRS}
	DESTINATION include/libqinfinity-1.0/libqinfinity)

