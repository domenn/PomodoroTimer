cmake_minimum_required(VERSION 3.12)
project(PomodoroTimer)

set(CMAKE_CXX_STANDARD 17)

option(ALWAYS_USE_QT_NOTIFICATION "If off, the software can use Windows or Linux notification systems" ON)
include_directories(. External/cpplogger/include)
if ( MSVC )
    add_definitions(-DUNICODE -D_UNICODE)
    endif()
set(CMAKE_AUTOMOC ON)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

# for MSVC
if(MSVC)
  add_definitions("/MP")
  add_definitions("/MDd")
  set(variables
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
	CMAKE_CXX_FLAGS_RELWITHDEBINFO
	CMAKE_CXX_FLAGS_MINSIZEREL
  )
  foreach(variable ${variables})
	if(${variable} MATCHES "/MD")
	  string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
	endif()
  endforeach()

  #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

endif()

# Find the QtWidgets library

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_PREFIX_PATH "C:\\Qt\\5.11.3\\msvc2017_64\\")
endif ()

#set(Qt5Widgets_DIR C:/msys64/mingw64/qt5-static/lib/cmake/Qt5Widgets)
#set(CMAKE_PREFIX_PATH C:/msys64/mingw64/qt5-static/)
# link_directories(C:/msys64/mingw64/qt5-static/share/qt5/plugins/platforms)
find_package(Qt5Widgets CONFIG REQUIRED)

# Populate a CMake variable with the sources
file(GLOB_RECURSE SOURCE_FILES
        ./PomodoroTimerApp/*.cpp
        ./PomodoroTimerApp/*.h
        )

#message(WARNING "${SOURCE_FILES}")

list(FILTER SOURCE_FILES EXCLUDE REGEX ".*main.cpp$")
#message(WARNING "${SOURCE_FILES}")

if (${ALWAYS_USE_QT_NOTIFICATION})
    add_library(qt_toast_notification STATIC Notifications/qt_notification_item.cpp)
    target_link_libraries(qt_toast_notification Qt5::Widgets)
    set(NOTIFICATION_IMPLEMENTATION qt_toast_notification)
elseif (UNIX)
    add_subdirectory(./Notifications/LinuxNotifications)
    set(NOTIFICATION_IMPLEMENTATION linux_notification)
endif ()

add_subdirectory(./PomodoroTimerAppTest)

if(MSVC)
    add_subdirectory(./Notifications/WindowsNotificationsTestApp)
    add_subdirectory(./Notifications/WindowsNotifications)
endif()

add_executable(PomodoroTimer PomodoroTimerApp/main.cpp ${SOURCE_FILES})
target_link_libraries(PomodoroTimer Qt5::Widgets ${NOTIFICATION_IMPLEMENTATION})
