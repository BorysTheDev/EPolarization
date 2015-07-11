#include "mainwindow.h"
//#include "QsLog.h "

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    // init the logging mechanism
//    QsLogging::Logger& logger = QsLogging::Logger::instance();

//    // set minimum log level and file name
//    logger.setLoggingLevel(QsLogging::DebugLevel );
//    const QString sLogPath(QDir(a.applicationDirPath()).filePath("log.txt"));

//    // Create log destinations
//    QsLogging::DestinationPtr fileDestination(
//     QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );
//    QsLogging::DestinationPtr debugDestination(
//     QsLogging::DestinationFactory::MakeDebugOutputDestination() );

//    // set log destinations on the logger
//    logger.addDestination(debugDestination);
//    logger.addDestination(fileDestination);

//    QObject::connect(&Gui,SIGNAL(sigClose()),&r,SLOT(close()));

    //QLOG_INFO() << "Program start";


    MainWindow w;
    w.show();

    return a.exec();
}
