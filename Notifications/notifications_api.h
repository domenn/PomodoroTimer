//
// Created by domen on 4.12.2018.
//

#pragma once

struct LibnNotificationButton{
    char const * const text;
    LibnNotificationButton * next;
    void (*libn_cb_function) ();
};

#ifdef __cplusplus
extern "C" {
#endif
    void libn_init(char const* app_name);

    void libn_show(char const* title, char const* text, LibnNotificationButton* buttons);
#ifdef __cplusplus
}
#endif
