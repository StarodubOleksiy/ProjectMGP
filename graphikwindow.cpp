#include "graphikwindow.h"
#include "ui_graphikwindow.h"

GraphikWindow::GraphikWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphikWindow),leftBorder(0),rightBorder(0)
{
    ui->setupUi(this);
    plot = NULL;
    this->setWindowTitle("Графік  глубини");
    connect(this, SIGNAL(showDepth()),this, SLOT(show()));
    curve = new QwtPlotCurve();
    symbol = new QwtSymbol( QwtSymbol::Ellipse,
    QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    grid = new QwtPlotGrid();
    button1 = new QPushButton("Вивести новий графік на екран");
    spinBoxLeftBorder = new QSpinBox();
    spinBoxRightBorder = new QSpinBox();
    spinBoxLeftBorder->setPrefix("Нижня межа графіку: ");
    spinBoxRightBorder->setPrefix("Верхня межа графіку: ");

    statusBar()->addWidget(spinBoxLeftBorder);
    statusBar()->addWidget(spinBoxRightBorder);
    statusBar()->addWidget(button1);
    connect(button1, SIGNAL(clicked()),this, SLOT(onClicked()));

}

void GraphikWindow::setDepthPonts(QVector<double> points)
{
  rightBorder = points.size();
    depthPoints = points;
    spinBoxLeftBorder->setRange(1, rightBorder);
    spinBoxRightBorder->setRange(1, rightBorder);
    spinBoxLeftBorder->setValue(1);
    spinBoxRightBorder->setValue(18);
}

void GraphikWindow::showGraphik(int zoom)
{
    graphicZoom = zoom;
    plot = new QwtPlot(this);
    plot->setTitle( "Графік глубини" );
    plot->setCanvasBackground( Qt::white );
    // plot->setAxisScale( QwtPlot::yLeft, 0.0, 3.0 );
    plot->setAxisScale(0, 0.0, graphicZoom );

    qDebug()<<"Zoom = "<<zoom;
    if(depthPoints.size()<20)
    plot->setAxisMaxMajor(2, depthPoints.size());
    else
    plot->setAxisMaxMajor(2, 10);
    plot->insertLegend( new QwtLegend() );
    plot->setAxisTitle(2,"Номер виміру");
    plot->setAxisTitle(0,"Рельєф, м");
    grid->attach(plot);


    curve->setTitle( "Глубина" );
    curve->setPen( Qt::blue, 4 ),
            curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    curve->setCurveAttribute(QwtPlotCurve::Fitted);

    curve->setSymbol( symbol );



    for(int i = leftBorder; i < rightBorder; ++i)
    {
        int temp = i;
        temp++;
        points << QPointF(temp,depthPoints[i] );
    }

    curve->setSamples( points );

    curve->attach(plot);

    plot->resize( 600, 400 );
    setCentralWidget(plot);
    emit showDepth();

}
void GraphikWindow::onClicked()
{
    if(spinBoxRightBorder->value() < spinBoxLeftBorder->value())
    {
       leftBorder = spinBoxRightBorder->value()-1;
       rightBorder = spinBoxLeftBorder->value();

    }else
    {
   leftBorder = spinBoxLeftBorder->value()-1;
   rightBorder = spinBoxRightBorder->value();
    }
   curve->detach();
   plot->detachItems();
   delete plot;
   plot = new QwtPlot(this);
   plot->setTitle( "Графік глубини" );
   plot->setCanvasBackground( Qt::white );
   plot->setAxisScale( /*QwtPlot::yLeft*/0, 0.0, graphicZoom );
   if(depthPoints.size()<100)
   plot->setAxisMaxMajor(2, rightBorder-leftBorder+1);
   else
   plot->setAxisMaxMajor(2, 10);
   plot->insertLegend( new QwtLegend() );
   plot->setAxisTitle(2,"Номер виміру");
   plot->setAxisTitle(0,"Рельєф, м");
   //delete grid; Звернути увагу!!!!
   grid = new QwtPlotGrid();
   grid->attach(plot );
   curve->setTitle( "Глубина" );
   curve->setPen( Qt::blue, 4 ),
           curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
   curve->setCurveAttribute(QwtPlotCurve::Fitted);

   curve->setSymbol( symbol );
   curve->attach(plot );
   setCentralWidget(plot);
   points.clear();

   for(int i = leftBorder; i < rightBorder; ++i)
   {
       int temp = i;
       temp++;
            points << QPointF(temp,depthPoints[i] );
   }
    curve->setSamples( points );
}

GraphikWindow::~GraphikWindow()
{
    points.clear();
    depthPoints.clear();
    curve->detach();
    plot->detachItems();
    delete grid;
    delete curve;
    delete symbol;
    delete button1;
    delete spinBoxLeftBorder;
    delete spinBoxRightBorder;
    delete plot;
    delete ui;
}
