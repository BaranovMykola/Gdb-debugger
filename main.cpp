#include <QCoreApplication>
#include <QProcess>
#include <QFile>
#include <QDir>
#include <iostream>
#include <QDebug>
#include <QStringList>

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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString gdb = qApp->applicationDirPath().append("/gdb/a2.exe");
    QFile gdbFile(gdb);
    qDebug() << "gdb path: " << gdb;
    qDebug() << "gdb file: " << gdbFile.exists();

    QProcess pr;
    proccesState(&pr);
    pr.start(gdb);
    pr.waitForBytesWritten();
    qDebug() << "write ready";
    pr.write("5\n");
    pr.waitForFinished();
    qDebug() << pr.readAllStandardOutput();
//    dbProcces->start(gdb, QStringList() << "arg");


//    QString firstRead = dbProcces->readAllStandardOutput();
//    proccesState(dbProcces);
//    qDebug() << "firstRead: " << firstRead;

//    dbProcces->write("s");
//    proccesState(dbProcces);
    qDebug() << "*Finished main*";
    return 0;
}
