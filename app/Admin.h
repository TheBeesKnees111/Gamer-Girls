#ifndef ADMIN_H
#define ADMIN_H

#include "mainwindow.h"

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private slots:

    ///This function will create a pointer to the MainWindow UI. The admin page will be
    /// hidden before showing the Main Window
	void on_Home_PushButton_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
