project(libqinfinity)

find_package(Libinfinity REQUIRED)
find_package(Libinftext REQUIRED)
find_package(Qt5 REQUIRED Core Widgets Network)

set(CMAKE_AUTOMOC ON)

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
	communicationgroup.cpp
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
	defaulttextplugin.cpp
	noderequest.cpp
	undogrouping.cpp
)

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
	communicationgroup.h
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
	defaulttextplugin.h
	noderequest.h
	undogrouping.h
)

include_directories(${LIBINFINITY_INCLUDES} ${LIBINFTEXT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

add_library(qinfinity SHARED ${QInfinity_SRCS})

set_target_properties(qinfinity
	PROPERTIES
	VERSION 3.1.0
	SOVERSION 5)

target_link_libraries(qinfinity
    PUBLIC
    ${LIBINFINITY_LIBRARIES}
    ${LIBINFTEXT_LIBRARIES}
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
)

install(TARGETS qinfinity
	DESTINATION lib${LIB_SUFFIX})

install(FILES ${QInfinity_HDRS}
	DESTINATION include/libqinfinity)

