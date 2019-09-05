#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug()<<"mainwindow construction start"<<endl;

    auto defaultFormat = QVTKOpenGLWidget::defaultFormat();
    defaultFormat.setSamples(0);
    QSurfaceFormat::setDefaultFormat(defaultFormat);

    ui->setupUi(this);
    initialize();

    qDebug()<<"mainwindow construction end"<<endl;
}

MainWindow::~MainWindow()
{
    qDebug()<<"destruction start"<<endl;
    delete vLayout_;
    delete main3DOpenGLWidget_;
    delete ui;
    qDebug()<<"destruction end"<<endl;
}


void MainWindow::initialize()
{
    qDebug()<<"initialize start"<<endl;
    initUIInterface();
    stlReader_ = vtkSmartPointer<vtkSTLReader>::New();
    stlActor_ = vtkSmartPointer<vtkActor>::New();
    polyDataMapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();

    jpgReader_ = vtkSmartPointer<vtkJPEGReader>::New();
    jpgWriter_ = vtkSmartPointer<vtkJPEGWriter>::New();
    imageActor_ = vtkSmartPointer<vtkImageActor>::New();
    imgMapper_ = vtkSmartPointer<vtkImageMapper>::New();

    qDebug()<<"initialize end"<<endl;
}

void MainWindow::initUIInterface()
{
    qDebug()<<"initializeUIInterface start"<<endl;
    renderer_ = vtkSmartPointer<vtkRenderer>::New();
    imgRenderer_ = vtkSmartPointer<vtkRenderer>::New();
    renderWindow_ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    main3DOpenGLWidget_ = new QVTKOpenGLWidget;
    this->ui->model3D->setFixedHeight(600);
    this->ui->model3D->setFixedWidth(1200);
    main3DOpenGLWidget_->setFixedSize(QSize(800,600));
    qDebug()<<"************"<<endl;

    main3DOpenGLWidget_->SetRenderWindow(renderWindow_);
    main3DOpenGLWidget_->update();
    vLayout_ = new QVBoxLayout;
    vLayout_->addWidget(main3DOpenGLWidget_);
    ui->model3D->setLayout(vLayout_);

    qDebug()<<"initializeUIInterface end"<<endl;
}


void MainWindow::on_openSTLFile_triggered()
{
    qDebug()<<"open file trigger start"<<endl;





    const auto file_to_open = QFileDialog::getOpenFileName(this,tr("Open STL file"),"",tr("STL Files(*.stl)"));

    qDebug()<<file_to_open<<endl;

    if(file_to_open.isNull())
    {
          return;
    }

    STLPath_ = file_to_open;

    try
    {
        modelDisplay();
    }
    catch(const std::exception &error)
    {
        qDebug() << error.what() << endl;
    }
}

void MainWindow::on_open2DImage_triggered()
{
    qDebug()<<"open 2d image trigger start"<<endl;


    QString file_to_open = QFileDialog::getOpenFileName(this,tr("Open 2d image"),"",tr("JPEG Files(*.jpg);;JPEG Files(*.jpeg)"));
    qDebug()<<file_to_open<<endl;
    if(file_to_open.isNull())
    {
          return;
    }
    imgPath_ = file_to_open;
    try
    {
        twoDImageShow();
    }
    catch(const std::exception &error)
    {
        qDebug() << error.what() << endl;
    }




}

void MainWindow::modelDisplay()
{
    qDebug()<<"stl render start"<<endl;
#if 1
    stlReader_->SetFileName(STLPath_.toUtf8().constData());
    stlReader_->Update();
    polyDataMapper_->SetInputConnection(stlReader_->GetOutputPort());
    stlActor_->SetMapper(polyDataMapper_);
    stlActor_->GetProperty()->SetColor(1,1,1);

    renderer_->AddActor(stlActor_);
    renderer_->ResetCamera();

    renderWindow_->RemoveRenderer(imgRenderer_);
    renderWindow_->AddRenderer(renderer_);

    vtkSmartPointer<vtkRenderWindowInteractor>threeDInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    threeDInteractor->SetRenderWindow(renderWindow_);
    threeDInteractor->Start();
    renderWindow_->Render();
#endif


}

void MainWindow::twoDImageShow()
{
    qDebug()<<"image render start"<<endl;

    jpgReader_->SetFileName(imgPath_.toUtf8().constData());
    jpgReader_->Update();
    imageActor_->SetInputData(jpgReader_->GetOutput());
    double bounds[6];
    imageActor_->GetBounds(bounds);



    imgRenderer_->AddActor(imageActor_);
    renderWindow_->RemoveRenderer(renderer_);
    renderWindow_->AddRenderer(imgRenderer_);
    imgRenderer_->SetBackground(1,1,1);
    imgRenderer_->ResetCamera();
    vtkSmartPointer<vtkInteractorStyleImage>interactorImage =
            vtkSmartPointer<vtkInteractorStyleImage>::New();

    renderWindow_->GetInteractor()->SetInteractorStyle(interactorImage);

    renderWindow_->Render();
    qDebug()<<"image render end"<<endl;


}
