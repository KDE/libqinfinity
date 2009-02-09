find_package(Qt4 REQUIRED)
find_package(Libinfinity REQUIRED)

set(QT_USE_QTNETWORK true)
INCLUDE(${QT_USE_FILE})

include_directories(${LIBINFINITY_INCLUDES} ${CMAKE_SOURCE_DIR}/libqinfinity)

QT4_AUTOMOC(shellbrowser.cpp
	guibrowser.cpp)

add_executable(shellbrowser shellbrowser.cpp)
target_link_libraries(shellbrowser ${QT_LIBRARIES} ${LIBINFINITY_LIBRARIES} qinfinity)

add_executable(guibrowser guibrowser.cpp)
target_link_libraries(guibrowser ${QT_LIBRARIES} ${LIBINFINITY_LIBRARIES} qinfinity)

