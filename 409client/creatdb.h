#ifndef CREATDB_H
#define CREATDB_H

#include <QDialog>

namespace Ui {
class creatDb;
}

class creatDb : public QDialog
{
    Q_OBJECT

public:
    explicit creatDb(QWidget *parent = 0);
    ~creatDb();

private:
    Ui::creatDb *ui;
};

#endif // CREATDB_H
