#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include<QVector>
#include<QStringList>
namespace Ui {
class PlotWindow;
}

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = 0);
    ~PlotWindow();
    QVector<QStringList> getData();

    void dataWrite( QVector<QStringList> fileData );

    void plot(QVector<double>,QVector<double>);

private slots:
    void on_pushButton_clicked();

private:
    Ui::PlotWindow *ui;
    QVector<QStringList> plotData;
};

QVector<double> Auto_Range(QVector<double> xData,QVector<double> yData);
#endif // PLOTWINDOW_H
