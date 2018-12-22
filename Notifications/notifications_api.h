//
// Created by domen on 4.12.2018.
//

#pragma once

#ifdef WIN_N_SHARED_LIB
#define N_DLL_EXPORT __declspec(dllexport)
#else
#define N_DLL_EXPORT
#endif

struct LibnNotificationButton{
    char const * const text;
    LibnNotificationButton * next;
    void (*libn_cb_function) ();
};

#ifdef __cplusplus
extern "C" {
#endif
	N_DLL_EXPORT void libn_init(char const* app_name);

	N_DLL_EXPORT void libn_show(char const* title, char const* text, LibnNotificationButton* buttons);
#ifdef __cplusplus
}
#endif
