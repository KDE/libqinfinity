find_package(Qt4 REQUIRED)
find_package(Libinfinity REQUIRED)

set(QT_USE_QTNETWORK true)
INCLUDE(${QT_USE_FILE})

include_directories(${LIBINFINITY_INCLUDES} ${CMAKE_SOURCE_DIR}/libqinfinity ${CMAKE_CURRENT_BINARY_DIR})

QT4_AUTOMOC(guibrowser.cpp
	connection.cpp
	createitemdialog.cpp)

set(guibrowser_UI
	newconnectionwidget.ui)

QT4_WRAP_UI(guibrowser_UI_HDRS
	${guibrowser_UI})

add_executable(guibrowser guibrowser.cpp connection.cpp createitemdialog.cpp ${guibrowser_UI_HDRS})
target_link_libraries(guibrowser ${QT_LIBRARIES} ${LIBINFINITY_LIBRARIES} qinfinity)

