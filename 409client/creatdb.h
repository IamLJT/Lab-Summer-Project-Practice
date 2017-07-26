#ifndef CREATDB_H
#define CREATDB_H

#include <QDialog>
#include<QString>

namespace Ui {
class creatDb;
}

class creatDb : public QDialog
{
    Q_OBJECT

public:
    explicit creatDb(QWidget *parent = 0);
    ~creatDb();
    QString getDbName();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::creatDb *ui;
    QString dbName;
};

#endif // CREATDB_H
