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


/**
*remove renderers in renderwindow
*/
void MainWindow::renderWindowInitialize()
{
    qDebug()<<"renderers number:"<<renderWindow_->GetRenderers()->GetNumberOfItems()<<endl;

    while(renderWindow_->GetRenderers()->GetNumberOfItems() != 0)
    {
        auto renderPtr = renderWindow_->GetRenderers()->GetFirstRenderer();
        renderWindow_->RemoveRenderer(renderPtr);
    }
    qDebug()<<renderWindow_->GetRenderers()->GetNumberOfItems()<<endl;
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
    viewState_ = 0;

    try
    {
        renderWindowInitialize();
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
        renderWindowInitialize();
        twoDImageShow();
    }
    catch(const std::exception &error)
    {
        qDebug() << error.what() << endl;
    }
}


/**
  @func:stl mapping to 2DImage,(x,z)→(x0,y0),y→(0,255)
  @remarks:enalble after stl loading
*/
void MainWindow::on_showSTL2TwoDImage_triggered()
{
    renderWindowInitialize();
    stlData2ImageVector();
    imageVectorShow();
}
/**
  @func:stl decrpt and show
  @input:load image path
*/
void MainWindow::on_stlDecrption_triggered()
{
    imageDecryption();
    //2d to 3d and show stl
}

/**
  @func:stl encrpt
  @remarks:enalble after stl loading and transfer to 2dVector
*/
void MainWindow::on_stlEncrption_triggered()
{
    imageEncryption();
    twoDVectorWrite2Image();

}

void MainWindow::modelDisplay()
{
    qDebug()<<"stl render start"<<endl;
#if 1


    stlReader_->SetFileName(STLPath_.toUtf8().constData());
    qDebug()<<"*********"<<endl;
    stlReader_->Update();


    polyDataMapper_->SetInputConnection(stlReader_->GetOutputPort());
    stlActor_->SetMapper(polyDataMapper_);
    stlActor_->GetProperty()->SetColor(1,1,1);

    stlActor_->GetBounds(bound_);


    qDebug()<<"stl geometry bounds is:"<<
              bound_[0]<<" "<<bound_[1]<<" "<<
              bound_[2]<<" "<<bound_[3]<<" "<<
              bound_[4]<<" "<<bound_[5]<<endl;

    renderer_->AddActor(stlActor_);
    renderer_->ResetCamera();

    renderWindow_->AddRenderer(renderer_);
    vtkSmartPointer<vtkRenderWindowInteractor>threeDInteractor
            = vtkSmartPointer<vtkRenderWindowInteractor>::New();
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
//    double bounds[6];
//    imageActor_->GetBounds(bounds);
    imgRenderer_->AddActor(imageActor_);
    renderWindow_->AddRenderer(imgRenderer_);
    imgRenderer_->SetBackground(1,1,1);
    imgRenderer_->ResetCamera();
    vtkSmartPointer<vtkInteractorStyleImage>interactorImage =
            vtkSmartPointer<vtkInteractorStyleImage>::New();
    renderWindow_->GetInteractor()->SetInteractorStyle(interactorImage);
    renderWindow_->Render();
    qDebug()<<"image render end"<<endl;
}


void MainWindow::twoDVectorWrite2Image()
{

}
void MainWindow::stlData2ImageVector()
{
    vtkPolyData* polyData = vtkPolyData::New();
    polyData = stlReader_->GetOutput();

//convert point data from poly to vector
#if 1
    double tmpPoint[3] = {0,0,0};
    Point3D  tmp3DPoint;
    for(vtkIdType i=0;i<polyData->GetNumberOfPoints();i++)
    {
        polyData->GetPoint(i,tmpPoint);
        tmp3DPoint.x = tmpPoint[0];
        tmp3DPoint.y = tmpPoint[1];
        tmp3DPoint.z = tmpPoint[2];
        pointData_.push_back(tmp3DPoint);
    }
    qDebug()<<"3Dpiont data load success"<<endl;
#endif

#if 1
    //y-->pixel x,z-->location
    std::vector<double> pixelValueContainer;
    Point2D tmpPoint2D;
    for(int i=0;i<pointData_.size();i++)
    {
        tmpPoint2D.x = pointData_[i].x;
        tmpPoint2D.y = pointData_[i].z;
        pixelValueContainer.push_back(pointData_[i].y);
        imagePixelVector_.push_back(tmpPoint2D);
       // std::cout<<tmpPoint2D.x<<" "<<tmpPoint2D.y<<endl;
    }
    qDebug()<<"2DPoint data load success"<<endl;
#endif
    polyData->Delete();
    polyData = nullptr;
}

void MainWindow::imageVectorShow()
{
    vtkSmartPointer<vtkContextView> view =
        vtkSmartPointer<vtkContextView>::New();
    vtkSmartPointer<vtkChartXY> chart =
        vtkSmartPointer<vtkChartXY>::New();
    view->GetScene()->AddItem(chart);
    chart->SetShowLegend(true);

      // Create a table with some points in it...
    vtkSmartPointer<vtkTable> table =
        vtkSmartPointer<vtkTable>::New();
    vtkSmartPointer<vtkDoubleArray> arrX =
            vtkSmartPointer<vtkDoubleArray>::New();
    vtkSmartPointer<vtkDoubleArray> arry =
            vtkSmartPointer<vtkDoubleArray>::New();
    table->AddColumn(arrX);
    table->AddColumn(arry);
    table->GetColumn(0)->SetName("X");
    table->GetColumn(1)->SetName("Y");

    qDebug()<<"table initialize"<<endl;

    int pointNum = imagePixelVector_.size();
    table->SetNumberOfRows(pointNum);

    for(int i=0;i<pointNum;i++)
    {
        table->SetValue(i,0,(imagePixelVector_[i].x));
        table->SetValue(i,1,(imagePixelVector_[i].y));

    }
    qDebug()<<"table data load success"<<
              "     total num is:"<<pointNum<<endl;
    vtkPlot *points = chart->AddPlot(vtkChart::POINTS);

    points->SetInputData(table, 0, 1);
    points->SetColor(0, 0, 0, 255);
    points->SetWidth(1.0);
    qDebug()<<"point load success"<<endl;
    vtkPlotPoints::SafeDownCast(points)->SetMarkerStyle(vtkPlotPoints::CROSS);


    view->SetRenderWindow(renderWindow_);
    view->SetInteractor(renderWindow_->GetInteractor());

    renderWindow_->AddRenderer(view->GetRenderer());
    renderWindow_->SetInteractor(view->GetInteractor());
    renderWindow_->Render();


}


void MainWindow::imageEncryption()
{

}
void MainWindow::imageDecryption()
{


}


