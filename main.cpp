#include <QCoreApplication>
#include <QProcess>
#include <QFile>
#include <QDir>
#include <iostream>
#include <QDebug>
#include <QStringList>
#include <string>

using std::cin;
using std::cout;
using std::boolalpha;
using std::endl;

void proccesState(QProcess* pr)
{
    QString str;
    QProcess::ProcessState state = pr->state();
    switch (state) {
    case QProcess::NotRunning:
        str = "Not running";
        break;
    case QProcess::Running:
        str = "Running";
        break;
    case QProcess::Starting:
        str = "Starting";
        break;
    }
    qDebug() << "QProccesState: " << str;
}

void showState(QProcess* pr)
{
    bool write = pr->waitForBytesWritten(100);
    bool read = pr->waitForReadyRead(100);
    bool finish = pr->waitForFinished(100);
    bool start = pr->waitForStarted(100);
    qDebug() << "Process: waitForBytesWritten: " << write << " waitForReadyRead: " << read <<
               " waitForFinished: " << finish << " waitForStarted " << start;
}

void writeTo(QProcess* pr, QString str)
{
    bool alpha = pr->waitForBytesWritten();
    qDebug() << "waitForBytesWritten returned " << alpha;
    QByteArray arr(str.append("\n").toStdString().c_str());
    pr->write(arr);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString gdb = qApp->applicationDirPath().append("/gdb/interactConsole.exe");
    QFile gdbFile(gdb);
    qDebug() << "gdb path: " << gdb;
    qDebug() << "gdb file: " << gdbFile.exists();

    QProcess pr;
    QObject::connect(&pr, &QProcess::readyReadStandardOutput, [&]()
    {
        qDebug() << pr.readAll() << "\n";
    });
    proccesState(&pr);
    pr.start(gdb);
    QString str = "fffks;dfjdskjflkdjflkd";
    for(int i=0;i<20;++i)
    {
        pr.waitForReadyRead();
        std::string s;
    std::cin >> s;
    str = s.c_str();
    pr.write(str.append("\n").toStdString().c_str());
    }
//    showState(&pr);
//    qDebug() << pr.readAll();
//    showState(&pr);
//    pr.write("run\n");
//    showState(&pr);

//    pr.waitForReadyRead(100);
//    qDebug() << pr.readAll();

    qDebug() << "*Finished main*\n\n\n\n";
    return 0;
}
