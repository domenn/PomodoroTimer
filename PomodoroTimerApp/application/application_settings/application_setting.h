//
// Created by domen on 30.11.2018.
//

#pragma once
#include <QtCore>
#include <map>

class ApplicationSetting;

typedef std::vector<std::shared_ptr<ApplicationSetting>> array_of_settings;

class ApplicationSetting {

    constexpr static char const * const SETTINGS_KEY_APP = "app_settings/";

protected:
    qint64 value{};
    // REFACTOR_IDEA: Not nice that this object owns GUI item. Would be better for it to have create method and return the pointer ..
    // Or simply make seperate classes for handling conversion between setting type and GUI item
    QWidget* widget{};

public:
    constexpr static char const* const KEY_S_WORK_TIME = "work_time";
    constexpr static char const* const KEY_S_PAUSE_TIME = "pause_time";
    constexpr static char const* const KEY_S_LONG_PAUSE_TIME = "lpause_time";
    constexpr static char const* const KEY_S_LONG_PAUSE_WHICH = "lp_after";

    static const std::map<QString const, qint64> MAP_DEFAULT_SETTINGS;

    const QString gui_text;
    const QString options_key;


    virtual qint64 get_value() const { return value; }
    virtual qint64 widget_to_value() = 0;
    virtual QWidget* const create_widget(qint64 time_str) = 0;
    virtual QWidget* const create_widget(QString const &) = 0;

    ApplicationSetting(QString gui_text, QString options_key)
            :gui_text(std::move(gui_text)), options_key(std::move(options_key)) { }

    ApplicationSetting() = default;

    static QSettings application_settings();
    static void load_settings(array_of_settings const & container);
    static qint64 get_setting_by_key(array_of_settings const& container, char const* key);
    static array_of_settings make_default_settings_container();
    static void persist_settings(array_of_settings const & vector);
};
