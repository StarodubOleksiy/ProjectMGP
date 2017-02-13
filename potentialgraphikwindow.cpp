#include "potentialgraphikwindow.h"
#include "ui_potentialgraphikwindow.h"

PotentialGraphikWindow::PotentialGraphikWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PotentialGraphikWindow)
{//off
    ui->setupUi(this);
    this->setWindowTitle("Графік  потенціалу");
    connect(this, SIGNAL(showPotential()),this, SLOT(show()));
    curve = new QwtPlotCurve();
    symbol = new QwtSymbol( QwtSymbol::Ellipse,
     QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    grid = new QwtPlotGrid();
}
void PotentialGraphikWindow::setPotentialPoints(QVector<double> points)
{
    potentialPoints = points;
}//fggh

void PotentialGraphikWindow::showGraphik(int zoom)
{
    QwtPlot *plot = new QwtPlot(this);
    plot->setTitle( "Графік потенціалу" );
    plot->setCanvasBackground( Qt::white );
    int lessBorder = zoom*(-1);
    qDebug()<<"lessBorder"<<lessBorder;
    //plot->setAxisScale( QwtPlot::yLeft,lessBorder, zoom );
    plot->setAxisScale(0, lessBorder, zoom );
    plot->insertLegend( new QwtLegend() );
    plot->setAxisTitle(2,"Номер виміру");
    plot->setAxisTitle(0,"U, в");
    if(potentialPoints.size()<20)
    plot->setAxisMaxMajor(2,potentialPoints.size());
    else
    plot->setAxisMaxMajor(2, 10);
    grid->attach(plot);
    curve->setTitle( "Потенціал" );
    curve->setPen( Qt::blue, 4 ),
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    curve->setCurveAttribute(QwtPlotCurve::Fitted);
    curve->setSymbol( symbol );
    QPolygonF points;
    for(int i = 0; i < potentialPoints.size(); ++i)
    {
        int temp = i;
        temp++;
        points << QPointF(temp,potentialPoints[i] );
    }
    curve->setSamples( points );
    curve->attach(plot);
    plot->resize( 600, 400 );
    setCentralWidget(plot);
    emit showPotential();
}

PotentialGraphikWindow::~PotentialGraphikWindow()
{
    delete grid;
    delete curve;
    delete symbol;
    delete ui;
}
