//
// Created by domen on 05/11/18.
//

#ifndef POMODOROTIMER_LOGGER_H
#define POMODOROTIMER_LOGGER_H


#include <QObject>
#include <QPlainTextEdit>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

class Logger : public QObject
{
Q_OBJECT
public:
    explicit Logger(QObject *parent, QString fileName, QPlainTextEdit *editor = nullptr);
    ~Logger();
    void setShowDateTime(bool value);

    static const Logger &getDefaultLogger();

    static void createDefaultLogger(QObject *parent, QString fileName, QPlainTextEdit *editor = nullptr);

private:
    QFile *file;
    QPlainTextEdit *m_editor;
    bool m_showDate;

    static Logger * defaultLogger;

signals:

public slots:
    void write(const QString &value) const;
};



#endif //POMODOROTIMER_LOGGER_H
