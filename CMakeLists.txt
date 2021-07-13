#
# Qt RHI QQuickPaintedItem memory leak
#
cmake_minimum_required(VERSION 3.14)

set(APPNAME RHI_QQuickPaintedItemBug)
project(${APPNAME})

#
# define SW_APP_ROOT == Projects root directory
get_filename_component(SW_APP_ROOT . ABSOLUTE)


# expand cmake search path to check for project settings
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${SW_APP_ROOT}/cmake
)

#set(QT_VERSION "6.2.0")

include(QtSettings)


# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Whether to handle rcc automatically for Qt targets.
set(CMAKE_AUTORCC ON)

if (${QT_VERSION} VERSION_LESS  "6.0.0")
  find_package(Qt5Core REQUIRED)
  find_package(Qt5Quick)
  find_package(Qt5Widgets)
else()
  find_package(Qt6Core REQUIRED)
  find_package(Qt6Quick)
  find_package(Qt6Widgets)
endif()

include_directories(
  inc
  ${CMAKE_CURRENT_BINARY_DIR}
)


add_subdirectory(qml)

set(RHI_HEADER_FILES
  inc/rhi_application.h 
  inc/qline_item.h
  inc/qml_reloader.h
)

set(RHI_SOURCE_FILES
  src/rhi_bug.cpp
  src/rhi_application.cpp
  src/qline_item.cpp
  src/qml_reloader.cpp
)

set(RHI_RESOURCE_FILES
  rhi_resources.qrc
)
if (${QT_VERSION} VERSION_LESS  "6.0.0")
  qt5_add_resources(RESOURCE_ADDED ${RHI_RESOURCE_FILES})
else()
endif()

add_executable(${APPNAME} WIN32
  ${RHI_SOURCE_FILES}
  ${RHI_HEADER_FILES}
  ${RHI_RESOURCE_FILES}
  ${QT_HEADER_FILES}
  ${QT_SOURCE_FILES}
  ${RESOURCE_ADDED}
)

if (${QT_VERSION} VERSION_LESS  "6.0.0")
  target_link_libraries(${APPNAME} Qt5::Widgets Qt5::Quick)
else()
  target_link_libraries(${APPNAME} Qt6::Widgets Qt6::Quick)
endif()

