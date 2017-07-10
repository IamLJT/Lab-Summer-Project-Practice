#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <ActiveQt/QAxObject>
#include<QFileDialog>
#include<QString>
#include<QtGui>
#include<QVariant>
#include<QStringList>
#include <QMessageBox>
#include <QTextStream>
#include<qDebug>
#include<QFileInfo>
#include<QVector>
#include "myclient.h"
#include "tabnamedialog.h"

namespace Ui {
class download;
}

class download : public QDialog
{
    Q_OBJECT

public:
    explicit download(QWidget *parent = 0);
    ~download();

void currentUser(QString username);
bool getChangFile();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();
    
    void on_pushButton_clicked();

private:
    Ui::download *ui;
    QString current_user;
    bool changFile=false;
    QString fileName;
    QVector<QStringList> fileDate;
};

#endif // DOWNLOAD_H
