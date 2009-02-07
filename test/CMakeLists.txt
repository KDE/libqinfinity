find_package(Qt4 REQUIRED)
find_package(Libinfinity REQUIRED)

INCLUDE(${QT_USE_FILE})

include_directories(${LIBINFINITY_INCLUDES} ${CMAKE_SOURCE_DIR}/libqinfinity)
add_executable(clientbrowser clientbrowser.cpp)
target_link_libraries(clientbrowser ${QT_LIBRARIES} ${LIBINFINITY_LIBRARIES} qinfinity)

