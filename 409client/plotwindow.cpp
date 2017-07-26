#include "plotwindow.h"
#include "ui_plotwindow.h"
#include<QDebug>
PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
}

PlotWindow::~PlotWindow()
{
    delete ui;
}

QVector<QStringList> PlotWindow::getData(){
     return plotData;
}
void PlotWindow::dataWrite( QVector<QStringList> fileData ){
    plotData=fileData;
}
void PlotWindow::plot(QVector<double> xData,QVector<double> yData){
    ui->customPlot->xAxis->setLabel("X");
    ui->customPlot->yAxis->setLabel("Y");
    ui->customPlot->addGraph();//每一个曲线相当于一个图层
    ui->customPlot->graph(0)->setData(xData, yData);
    QVector<double> range=Auto_Range(xData,yData);
    ui->customPlot->xAxis->setRange(range[0],range[1]);
    ui->customPlot->yAxis->setRange(range[2],range[3]);
    ui->customPlot->replot();
}
//绘图
void PlotWindow::on_pushButton_clicked()
{
    QVector<QStringList> fileData=getData();
    int size=fileData[0].size();
    QVector<double>xData,yData;
    for(int index=0;index<size;++index){
        if(!fileData[0].isEmpty()){
        xData.push_back(fileData[0][index].toDouble());
        yData.push_back(fileData[1][index].toDouble());
        }
    }
    plot(xData,yData);
}

QVector<double> Auto_Range(QVector<double> xData,QVector<double> yData){
    QVector<double> range(4);
    double xMin=xData[0],xMax=xData[0];
    double yMin=yData[0],yMax=yData[0];
    for(int index=0;index<xData.size();++index){
        if(xData[index]>xMax)
            xMax=xData[index];
        else if(xData[index]<xMin)
            xMin=xData[index];
        if(yData[index]>yMax)
            yMax=yData[index];
        else if(yData[index]<yMin)
            yMin=yData[index];
    }
    range[0]=xMin-(xMax-xMin)*0.1;
    range[1]=xMax+(xMax-xMin)*0.1;
    range[2]=yMin-(yMax-yMin)*0.1;
    range[3]=yMax+(yMax-yMin)*0.1;
    return range;
}






















