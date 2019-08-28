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


    qDebug()<<"initialize end"<<endl;
}

void MainWindow::initUIInterface()
{
    qDebug()<<"initializeUIInterface start"<<endl;
    renderer_ = vtkSmartPointer<vtkRenderer>::New();
    renderWindow_ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    main3DOpenGLWidget_ = new QVTKOpenGLWidget;

    main3DOpenGLWidget_->setFixedSize(QSize(800,ui->model3D->height()));
    qDebug()<<"************"<<endl;
    main3DOpenGLWidget_->SetRenderWindow(renderWindow_);




    vLayout_ = new QVBoxLayout;
    vLayout_->addWidget(main3DOpenGLWidget_);

    ui->model3D->setLayout(vLayout_);

    qDebug()<<"initializeUIInterface end"<<endl;
}


void MainWindow::on_openFile_triggered()
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

void MainWindow::modelDisplay()
{
    qDebug()<<"stl render start"<<endl;
#if 1
    stlReader_->SetFileName(STLPath_.toUtf8().constData());
    polyDataMapper_->SetInputConnection(stlReader_->GetOutputPort());
    stlActor_->SetMapper(polyDataMapper_);
    stlActor_->GetProperty()->SetColor(1,1,1);

    renderer_->AddActor(stlActor_);
    renderWindow_->AddRenderer(renderer_);
    renderWindow_->Render();

#endif


}
