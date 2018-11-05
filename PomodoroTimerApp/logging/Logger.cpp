#include <utility>

//
// Created by domen on 05/11/18.
//

#include "Logger.h"

Logger * Logger::defaultLogger;

Logger::Logger(QObject *parent, QString fileName, QPlainTextEdit *editor) : QObject(parent) {
    m_editor = editor;
    m_showDate = true;
    if (!fileName.isEmpty()) {
        file = new QFile;
        file->setFileName(fileName);
        file->open(QIODevice::Append | QIODevice::Text);
    }
}

void Logger::write(const QString &value) const {
    QString text = value;// + "";
    if (m_showDate)
        text = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz ") + text;
    QTextStream out(file);
    out.setCodec("UTF-8");
    if (file != 0) {
        out << text << endl;
    }
    if (m_editor != 0)
        m_editor->appendPlainText(text);
}

void Logger::setShowDateTime(bool value) {
    m_showDate = value;
}

Logger::~Logger() {
    if (file != 0)
        file->close();
}

const Logger &Logger::getDefaultLogger() {
    return *defaultLogger;
}

void Logger::createDefaultLogger(QObject *parent, QString fileName, QPlainTextEdit *editor) {
    Logger *logger = new Logger(parent, std::move(fileName), editor);
    defaultLogger = logger;
}
