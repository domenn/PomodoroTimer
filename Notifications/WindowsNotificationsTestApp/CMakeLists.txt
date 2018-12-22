
add_executable(WindowsNotificationTestApp qt_testing.cpp)
target_link_libraries(WindowsNotificationTestApp Qt5::Widgets win_libtoast)

set_property(TARGET WindowsNotificationTestApp PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${QT5_BINARY_DIRECTORY}")

# message(WARNING ${CMAKE_BINARY_DIR})

#add_custom_command(TARGET WindowsNotificationTestApp POST_BUILD        # Adds a post-build event to MyTest
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
#        # ${CMAKE_CURRENT_SOURCE_DIR}/../x64/Release/SimpleDisplay.dll     # <--this is in-file
#        # ${CMAKE_BINARY_DIR}/
#        ${CMAKE_BINARY_DIR}/Notifications/WindowsNotifications/Debug/win_libtoast.dll
#        $<TARGET_FILE_DIR:WindowsNotificationTestApp>)                 # <--this is out