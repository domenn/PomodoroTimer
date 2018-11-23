//
// Created by domen on 23. 11. 2018.
//
#pragma once


#include <QtCore/QString>
#include <QtCore/QStandardPaths>
#include <QtCore/QDir>

namespace app_directories {

    inline QString getDefaultLogFilePath() {
        QString application_folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
        QDir dir(application_folder);
        if (!dir.exists())
            dir.mkpath(application_folder);

        auto filename = dir.absoluteFilePath("log.txt");
        return filename;
    }
}