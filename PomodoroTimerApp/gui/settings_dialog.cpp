//
// Created by domen on 29.11.2018.
//

#include <QtWidgets/QVBoxLayout>
#include <QLabel>
#include "settings_dialog.h"
#include <QFormLayout>
#include <QtWidgets/QDialogButtonBox>
#include <External/cpplogger/include/plog/Log.h>
#include <QtWidgets/QMessageBox>

SettingsDialog::~SettingsDialog() {
    LOG_DEBUG << "SettingsDialog destructor";
}

void SettingsDialog::accept() {
    LOG_DEBUG << "Settings accept button enter";

    for (auto& s : *settings) {
        s->widget_to_value();
    }
    ApplicationSetting::persist_settings(*settings);

    QDialog::accept();
    LOG_DEBUG << "Settings accept button end";
}

//const array_of_settings& SettingsDialog::get_settings() const {
//    return settings;
//}

SettingsDialog::SettingsDialog(const array_of_settings* const arr_of_settings, QWidget* parent,
        const Qt::WindowFlags& f)
        :QDialog(parent, f), settings(arr_of_settings) {
    auto* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    auto* form = new QFormLayout;
    mainLayout->addLayout(form, 1);

    for (auto& s : *settings) {
        QWidget* new_widget = s->create_widget(s->get_value());
        QWidget* label = new QLabel(s->gui_text);
        if (!s->tooltip_text.isEmpty()) {
            label->setToolTip(s->tooltip_text);
        }
        form->addRow(label, new_widget);
    }

    auto button_box = new QDialogButtonBox(QDialogButtonBox::Help | QDialogButtonBox::Ok
            | QDialogButtonBox::Cancel);

    connect(button_box, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(button_box, &QDialogButtonBox::helpRequested, this, &SettingsDialog::show_help);

    mainLayout->addWidget(button_box);
}

void SettingsDialog::show_help() {
    auto message = tr("Supported formats: \n\n mm\n mm:ss\n mm:ss:zzz\n hh:mm:ss\n hh:mm:ss:zzz\n h:m:s:z\n\n"
                      "By inputting single number (any number), minutes are assumed. Fractions (like 4.13) are not supported.");
    QMessageBox::information(this, tr("Date time formats"), message);
}



