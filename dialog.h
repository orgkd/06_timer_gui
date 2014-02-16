#ifndef DIALOG_H
#define DIALOG_H

#include "commonimport.h"
#include "mytimer.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_stopButton_clicked();
    void on_resetButton_clicked();
    void on_startButton_clicked();
    void timer_expired();
    void onesecond_timer_expired();

private:
    Ui::Dialog *ui;
    mytimer *timer;
    QTimer *oneSecond;
    QIcon *playImage;
    QIcon *stopImage;
    QIcon *pauseImage;
    bool runnig;

signals:
    void resumeTimer();
};

#endif // DIALOG_H
