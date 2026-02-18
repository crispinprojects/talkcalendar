#include "synthesizer.h"
#include <QTextStream>
#include <QtConcurrent> // For async playback
#include <qregularexpression.h>

Synthesizer::Synthesizer(QObject *parent) : QObject(parent) {
    // Constructor
    speechProcess = new QProcess();
    speechProcessName = "espeak";

}

void Synthesizer::stop() {

    if (speechProcess->state() == QProcess::Running ) {

        speechProcess->terminate();
        qDebug()<<"speechProcess terminated with exit code = "<< speechProcess->exitCode();
    }
}

void Synthesizer::speak(const QString &text) {
    stop();

    // Find whichever engine the user has installed
    QString executable = QStandardPaths::findExecutable("espeak-ng");
    if (executable.isEmpty()) {
        executable = QStandardPaths::findExecutable("espeak");
    }

    if (executable.isEmpty()) {
        qDebug() << "Speech engine (espeak or espeak-ng) not found.";
        return;
    }

    // espeak arguments
    int amplitude = 80;
    int pitch = 50;
    int speed = 180;
    int wordgap = 4;
    QString voiceName = "-ven+m7";

    QStringList arguments;
    arguments << voiceName
              << "-s" << QString::number(speed)
              << "-g" << QString::number(wordgap)
              << "-p" << QString::number(pitch)
              << "-a" << QString::number(amplitude)
              << text;

    speechProcessName = executable;
    speechProcess->start(speechProcessName, arguments);
}

//Helpers
QString Synthesizer::getDatePhrase(const QDate &date) {
    QString dayName = date.toString("dddd").toLower();
    QString monthName = date.toString("MMMM").toLower();
    int day = date.day();

    // Use your ordinals list from before
    QString ordinal = getOrdinal(day);

    return QString("%1 %2 %3").arg(dayName, monthName, ordinal);
}


QString Synthesizer::getTimePhrase(int hour, int minute, bool isAllDay) {
    if (isAllDay) return "all day";

    int h12 = (hour == 0 || hour == 12) ? 12 : hour % 12;
    QString ampm = (hour < 12) ? "am" : "pm";

    if (minute == 0)
        //return QString("%1 oclock %2").arg(QString::number(h12), ampm);
        return QString("%1 %2").arg(QString::number(h12), ampm);
    else if (minute < 10)
        return QString("%1 o %2 %3").arg(QString::number(h12), QString::number(minute), ampm);
    else
        return QString("%1 %2 %3").arg(QString::number(h12), QString::number(minute), ampm);
}


QString Synthesizer::getOrdinal(int day) {
    // These strings must match the keys you have in your 'voice_map'
    static const QStringList ordinals = {
        "", // 0 (ignored)
        "first", "second", "third", "fourth", "fifth",
        "sixth", "seventh", "eighth", "ninth", "tenth",
        "eleventh", "twelfth", "thirteenth", "fourteenth", "fifteenth",
        "sixteenth", "seventeenth", "eighteenth", "nineteenth", "twentieth",
        "twenty first", "twenty second", "twenty third", "twenty fourth", "twenty fifth",
        "twenty sixth", "twenty seventh", "twenty eighth", "twenty ninth", "thirtieth",
        "thirty first"
    };

    if (day >= 1 && day <= 31) {
        return ordinals[day];
    }

    return ""; // Return empty if date is invalid
}
