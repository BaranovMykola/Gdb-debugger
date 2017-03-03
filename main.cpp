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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString gdb = qApp->applicationDirPath().append("/gdb/test.exe");
    QFile gdbFile(gdb);
    qDebug() << "gdb path: " << gdb;
    qDebug() << "gdb file: " << gdbFile.exists();

    QProcess* dbProcces = new QProcess();
    //dbProcces->start(gdb, QStringList() << "");
    dbProcces->setProgram(gdb);
    dbProcces->execute(gdb, QStringList() << "111");
    QString firstRead = dbProcces->readAllStandardOutput();

    qDebug() << "firstRead: " << firstRead;

    return a.exec();
}
