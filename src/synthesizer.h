#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QFile>
#include <QHash>
#include <QProcess>
#include <QStandardPaths>
#include <QMessageBox>
#include <QStandardPaths>


class Synthesizer : public QObject {
    Q_OBJECT
public:
    explicit Synthesizer(QObject *parent = nullptr);
    void speak(const QString &text);  
    bool isTalking();
    void stop();
    QString getDatePhrase(const QDate &date);
    QString getTimePhrase(int hour, int minute, bool isAllDay);
    //file checks
    bool directoryExists(QString path);
    bool fileExists(QString path);

private:

    QProcess *speechProcess;
    QString speechProcessName;    
    QString getOrdinal(int day);

};

#endif
