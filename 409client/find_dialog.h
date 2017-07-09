#ifndef FIND_DIALOG_H
#define FIND_DIALOG_H

#include <QDialog>

namespace Ui {
class find_dialog;
}

class find_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit find_dialog(QWidget *parent = 0);
    ~find_dialog();

private:
    Ui::find_dialog *ui;
};

#endif // FIND_DIALOG_H
