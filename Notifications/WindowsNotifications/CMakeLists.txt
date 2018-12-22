
add_definitions(-DWIN_N_SHARED_LIB)

add_library(win_libtoast SHARED simple_display.cpp wintoastlib.cpp ../notifications_api.h wintoastlib.h)