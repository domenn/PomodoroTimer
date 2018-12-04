
find_package(PkgConfig)

pkg_check_modules(GLIB2 glib-2.0)
pkg_check_modules(GTK2 gtk+-2.0)

include_directories(${GLIB2_INCLUDE_DIRS} ${GTK2_INCLUDE_DIRS})



add_library(linux_notification STATIC lib_notify_wrapper.cpp)

target_link_libraries(linux_notification notify)