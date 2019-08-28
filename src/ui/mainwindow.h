#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QFileDialog>
#include <QWidget>
#include <QVTKOpenGLWidget.h>
#include <QVTKWidget.h>
#include <QVBoxLayout>
#include <QLayoutItem>
#include <QDebug>
#include <QString>
#include <QSize>

#include <vtkRenderer.h>

#include <vtkSTLReader.h>
#include <vtkPolyData.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkImageData.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderWidget.h>
#include <vtkSmartPointer.h>
#include <vtkNew.h>
#include <vtkProperty.h>
#include <vtkMath.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initialize();
    void initUIInterface();
    void modelDisplay();


private slots:
    void on_openFile_triggered();

private:
    Ui::MainWindow *ui;
    QVTKOpenGLWidget* main3DOpenGLWidget_;
    QVBoxLayout* vLayout_;

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow_;

    vtkSmartPointer<vtkRenderer> renderer_;
    vtkSmartPointer<vtkSTLReader> stlReader_;
    vtkSmartPointer<vtkPolyData> polyData_;

    vtkSmartPointer<vtkPolyDataMapper> polyDataMapper_;
    vtkSmartPointer<vtkActor> stlActor_;


    QString STLPath_;
    QString outPutPath_;






};

#endif // MAINWINDOW_H
