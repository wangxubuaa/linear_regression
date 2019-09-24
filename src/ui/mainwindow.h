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

#include <vtkRendererCollection.h>



#include <vtkChartXY.h>
#include <vtkTable.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkPlotPoints.h>
#include <vtkDoubleArray.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum ViewState
    {
        ThreeD_View,
        TwoD_ImageView,
        TwoD_GraphView
    };

    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
    void initialize();
    void initUIInterface();
    void modelDisplay();
    void twoDImageShow();
    void imageVectorShow();
    void twoDVectorWrite2Image();
    void stlData2ImageVector();


    void imageEncryption();
    void imageDecryption();



private slots:
    void on_openSTLFile_triggered();
    void on_open2DImage_triggered();

    void on_showSTL2TwoDImage_triggered();
    void on_stlEncrption_triggered();
    void on_stlDecrption_triggered();




private:
    int viewState_;
    void renderWindowInitialize();

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

    struct Point3D
    {
        double x;
        double y;
        double z;
    };

    struct Point2D
    {
        double x;
        double y;
    };

    std::vector<Point3D> pointData_;
    std::vector<Point2D> imagePixelVector_;

    int dimension_[3];
    double spacing_[3];
    double bound_[6];








};

#endif // MAINWINDOW_H
