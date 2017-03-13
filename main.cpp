#include <QCoreApplication>
#include <QProcess>
#include <QFile>
#include <QDir>
#include <iostream>
#include <QDebug>
#include <QStringList>
#include <string>
#include <QDataStream>
#include <QBuffer>
#include <iostream>

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

class SetOpenMode : QProcess
{
public:
    void setOpenMode(QIODevice::OpenMode m)
    {
        QProcess::setOpenMode(m);
    }
    qint64 writeData(const char * data, qint64 maxSize)
    {
        QProcess::writeData(data, maxSize);
    }
};

static QProcess pr;
static QTextStream qtin(stdin);

void write();

void read()
{
    qDebug() << "Process is ready for read: " << pr.waitForReadyRead(500);
//    QByteArray stdOut = pr.readAllStandardOutput();
//    stdOut[92] = '\n';
//    qDebug() << "Standart output: " << (QString)stdOut;
    QTextStream stream(&pr);
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        //line.replace('\\', ' ');
        qDebug()<<line;
    }
    QByteArray errOut = pr.readAllStandardError();
    qDebug() << "Error output: " << (QString)errOut;
    qDebug() << "\n";
    write();
}

void write()
{
    qDebug() << "Write command to process";
    std::string command;
    std::getline(std::cin, command);
    pr.write(command.c_str());
    pr.write("\n");
    qDebug() << "Process is waiting for bytes written: " << pr.waitForBytesWritten(500);
    read();
}

void inerprete(QString str)
{
    if(str == "read")
    {
        read();
    }
    else if(str == "write")
    {
        write();
    }
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString gdb = qApp->applicationDirPath().append("/gdb/gdb.exe");
    QFile gdbFile(gdb);
    qDebug() << "Process path: " << gdb;
    qDebug() << "Process file exist: " << gdbFile.exists();
    qDebug() << "Creating process...";

    pr.start(gdb, QStringList() << "--interpreter=mi");

    QString command;

    do
    {
        qtin >> command;
        inerprete(command);
    }
    while(command != "exit");


    qDebug() << "\n\n*Finished main*\n\n";
    return 0;
}
