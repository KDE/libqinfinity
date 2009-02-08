find_package(Qt4 REQUIRED)
find_package(Libinfinity REQUIRED)

INCLUDE(${QT_USE_FILE})

include_directories(${LIBINFINITY_INCLUDES} ${CMAKE_SOURCE_DIR}/libqinfinity)

QT4_AUTOMOC(shellbrowser.cpp)

add_executable(shellbrowser shellbrowser.cpp)
target_link_libraries(shellbrowser ${QT_LIBRARIES} ${LIBINFINITY_LIBRARIES} qinfinity)

