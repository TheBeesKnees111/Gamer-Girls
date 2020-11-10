#ifndef DISPLAYINFO_H
#define DISPLAYINFO_H

#include "Header.h"
#include "mainwindow.h"

namespace Ui {
class DisplayInfo;
}

class DisplayInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayInfo(QWidget *parent = nullptr);
    ~DisplayInfo();

private slots:

    ///This function will create a pointer to the MainWindow UI. The DisplayInfo
    /// page will be hidden before showing the Main Window
	void on_Home_PushButton_clicked();

private:
    Ui::DisplayInfo *ui;
};

#endif // DISPLAYINFO_H
