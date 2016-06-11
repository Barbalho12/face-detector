#include <QApplication>
#include "mainwindow.h"
#include "images.h"

int main(int argc, char *argv[]) {
    create_directory();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
