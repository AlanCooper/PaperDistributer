#include <QApplication>
#include "mainwindow.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator tran(0);
    tran.load("./PaperDistributer_zh.qm");
    app.installTranslator(&tran);
    MainWindow mainWindows(0);
    mainWindows.show();

    return app.exec();
}
