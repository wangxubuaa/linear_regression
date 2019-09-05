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
#include <vtkImageActor.h>
#include <vtkActor2D.h>
#include <vtkImageMapper.h>
#include <vtkJPEGReader.h>
#include <vtkJPEGWriter.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindowInteractor3D.h>
#include <vtkCamera.h>
#include <vtkRenderWidget.h>
#include <vtkSmartPointer.h>
#include <vtkNew.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkMath.h>

#include <vtkImageInterpolator.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
    void initialize();
    void initUIInterface();
    void modelDisplay();
    void twoDImageShow();


private slots:
    void on_openSTLFile_triggered();
    void on_open2DImage_triggered();

private:
    Ui::MainWindow *ui;
    QVTKOpenGLWidget* main3DOpenGLWidget_;
    QVBoxLayout* vLayout_;

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow_;


    vtkSmartPointer<vtkRenderer> renderer_;
    vtkSmartPointer<vtkRenderer> imgRenderer_;
    vtkSmartPointer<vtkJPEGReader>jpgReader_;
    vtkSmartPointer<vtkSTLReader>stlReader_;
    vtkSmartPointer<vtkJPEGWriter>jpgWriter_;
    vtkSmartPointer<vtkPolyData> polyData_;

    vtkSmartPointer<vtkPolyDataMapper> polyDataMapper_;
    vtkSmartPointer<vtkActor> stlActor_;
    vtkSmartPointer<vtkImageActor> imageActor_;
    vtkSmartPointer<vtkImageMapper> imgMapper_;
    vtkSmartPointer<vtkImageInterpolator>imgInterActor_;
    vtkSmartPointer<vtkCamera>tmpCamera_;



    QString STLPath_;
    QString imgPath_;
    QString outPutPath_;






};

#endif // MAINWINDOW_H
