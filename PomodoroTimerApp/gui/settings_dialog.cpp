//
// Created by domen on 29.11.2018.
//

#include <QtWidgets/QVBoxLayout>
#include <QLabel>
#include "settings_dialog.h"

SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent) {
    auto* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    auto one = new QLabel("test");
    auto q2 = new QLabel("test");

    mainLayout->addWidget(one);
    mainLayout->addWidget(q2);
}
