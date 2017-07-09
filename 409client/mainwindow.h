#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSettings>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void iniWidget(QString user);
    void flushWidget(QString user);

    ~MainWindow();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();

public:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
