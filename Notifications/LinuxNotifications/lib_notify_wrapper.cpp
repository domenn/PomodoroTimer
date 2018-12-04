//
// Created by domen on 4.12.2018.
//

#include "Notifications/notifications_api.h"

#include <iostream>
#include <libnotify/notify.h>
#include <Notifications/notifications_api.h>

#include <string>

LibnNotificationButton libn_private_global_buttons[]{{}, {}, {}, {}};

void libn_private_cb(NotifyNotification* notification,
        char* action,
        gpointer user_data) {
    auto* struct_ptr = static_cast<LibnNotificationButton*>(user_data);
    struct_ptr->libn_cb_function();
}

void libn_show(const char* title, const char* text, LibnNotificationButton* buttons) {
    std::cout << "Sent notification: " << title << " with content: " << text << std::endl;

    NotifyNotification* n = notify_notification_new(title, text, nullptr);
    notify_notification_set_timeout(n, NOTIFY_EXPIRES_NEVER); // 10 seconds


    char action_number = '0';
    int index = 0;
    while (buttons) {
        libn_private_global_buttons[index].libn_cb_function = buttons->libn_cb_function;
        notify_notification_add_action(n, (std::string("n_a") + action_number).c_str(), buttons->text, &libn_private_cb,
                (gpointer*) (libn_private_global_buttons + index), nullptr);
        ++action_number;
        ++index;
        buttons = buttons->next;
    }

    notify_notification_set_urgency(n, NOTIFY_URGENCY_NORMAL);

    if (!notify_notification_show(n, 0)) {
        std::cerr << "show has failed" << std::endl;
    }
}

void libn_init(char const* app_name) {
    if (!notify_is_initted()) {
        notify_init(app_name);
    }
}
