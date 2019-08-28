#include "ui/mainwindow.h"
#include <QApplication>
#include <QVTKOpenGLWidget.h>
#include <QFontDatabase>
#include <QFont>

#include <iostream>
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

int main(int argc, char *argv[])
{

    //QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());
    //vtkOpenGLRenderWindow::SetGlobalMaximumNumberOfMultiSamples(8);

    QApplication a(argc, argv);
    MainWindow w;
//    w.show();
    w.showMaximized();

    return a.exec();
}
