#include "synthesizer.h"
#include <QTextStream>
#include <QtConcurrent> // For async playback
#include <qregularexpression.h>

Synthesizer::Synthesizer(QObject *parent) : QObject(parent) {
    // Constructor
    speechProcess = new QProcess();
    speechProcessName = "espeak";

}

bool Synthesizer::directoryExists(QString path)
{
    const QFileInfo outputDir(path);
    if ((!outputDir.exists()) || (!outputDir.isDir()) || (!outputDir.isReadable())) {
        //qWarning() << "output directory does not exist, is not a directory, or is not readable"
        //<< outputDir.absoluteFilePath();
        return false;
    }
    else {
        return true;
    }
}

bool Synthesizer::fileExists(QString path)
{
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and not directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

void Synthesizer::stop() {

    if (speechProcess->state() == QProcess::Running ) {

        speechProcess->terminate();
        qDebug()<<"speechProcess terminated with exit code = "<< speechProcess->exitCode();
    }
}

void Synthesizer::speak(const QString &text) {

    stop(); // Always stop current speech before starting new speech

    //On many modern systems (especially Fedora), the binary is actually `/usr/bin/espeak-ng`.
    //To make your code and README more robust, you might want to use `QStandardPaths` or simply check for both paths
    //in your code to ensure the "espeak not installed" error doesn't trigger falsely.

    // if(!fileExists("/usr/bin/espeak")) {
    //     qDebug()<<"espeak not installed";
    //     return;
    // }

    // Look for espeak-ng first, then fall back to espeak
    QString executable = QStandardPaths::findExecutable("espeak-ng");
    if (executable.isEmpty()) {
        executable = QStandardPaths::findExecutable("espeak");
    }

    if (executable.isEmpty()) {
        qDebug() << "Speech engine (espeak or espeak-ng) not found in PATH";
        return;
    }

    int amplitude=80;
    int pitch=50;
    int capStress =20;
    int speed =180;
    int wordgap =4;
    QString voiceName="-ven+m7";


    QStringList arguments;
    arguments<<voiceName<<"-s"<<QString::number(speed)
              <<"-g"<<QString::number(wordgap)<<"-k"<<QString::number(capStress)
              <<"-p"<<QString::number(pitch)<<"-a"<<QString::number(amplitude);

    arguments << text;    
    // use start() to run the process without blocking
    // execute() is a static method running the process and blocking until it's done
    speechProcess->start(speechProcessName, arguments); //espeak

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
