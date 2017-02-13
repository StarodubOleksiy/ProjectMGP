#ifndef POTENTIALGRAPHIKWINDOW_H
#define POTENTIALGRAPHIKWINDOW_H

#include <QMainWindow>
#include <qwt_plot.h>
#include <qapplication.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qframe.h>

namespace Ui {
class PotentialGraphikWindow;
}

class PotentialGraphikWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PotentialGraphikWindow(QWidget *parent = 0);
    ~PotentialGraphikWindow();
    void setPotentialPoints(QVector<double> points);
    void showGraphik(int zoom);
signals:
   void showPotential();

private:
    Ui::PotentialGraphikWindow *ui;
    QVector<double> potentialPoints;
    QwtPlotGrid *grid;
    QwtPlotCurve *curve;
    QwtSymbol *symbol;
};


#endif // POTENTIALGRAPHIKWINDOW_H
