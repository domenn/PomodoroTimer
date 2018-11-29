//
// Created by domen on 29.11.2018.
//

#pragma once

#include <QtWidgets/QDialog>

class QLabel;
class QComboBox;

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

private:
    QLabel *formatLabel;
    QLabel *scopeLabel;
    QLabel *organizationLabel;
    QLabel *applicationLabel;
    QComboBox *formatComboBox;
    QComboBox *scopeComboBox;
    QComboBox *organizationComboBox;
    QComboBox *applicationComboBox;
};


