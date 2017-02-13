#ifndef GRAPHIKWINDOW_H
#define GRAPHIKWINDOW_H

#include <QMainWindow>
#include <qwt_plot.h>
#include <qapplication.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <QPushButton>
#include <QSpinBox>

namespace Ui {
class GraphikWindow;
}

class GraphikWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphikWindow(QWidget *parent = 0);
    ~GraphikWindow();
    void setDepthPonts(QVector<double> points);
    void showGraphik(int zoom);
public slots:
void onClicked();
signals:
   void showDepth();
private:
    Ui::GraphikWindow *ui;
    QVector<double> depthPoints;
    QwtPlotGrid *grid;
    QwtPlotCurve *curve;
    QwtSymbol *symbol;
    QSpinBox * spinBoxLeftBorder;
    QSpinBox * spinBoxRightBorder;
    QPushButton *button1;
    QPolygonF points;
    QwtPlot *plot;
    int leftBorder;
    int rightBorder;
    int graphicZoom;
};
#endif // GRAPHIKWINDOW_H
