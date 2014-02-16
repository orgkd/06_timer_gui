#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
    setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_NoSystemBackground, false);
    ui->timeEdit->setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setContentsMargins(0,0,0,0);

    QPalette pal = QPalette(this->palette());
    pal.setColor(QPalette::Base, QColor(255,255,255));
    pal.setColor(QPalette::Highlight, QColor(0,0,0,0));
    pal.setColor(QPalette::HighlightedText, QColor(0,0,0));
    this->setPalette(pal);
    ui->timeEdit->setPalette(pal);

    // TIMERS
    timer = new mytimer();
    oneSecond = new QTimer(this);

    playImage = new QIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    stopImage = new QIcon(style()->standardIcon(QStyle::SP_MediaStop));
    pauseImage = new QIcon(style()->standardIcon(QStyle::SP_MediaPause));
    timerIcon = new QIcon("images/timer.ico");
    alarm = new QSound("sound/alarm.wav");

    ui->startButton->setIcon(*playImage);
    ui->resetButton->setIcon(*stopImage);
    ui->stopButton->setIcon(*pauseImage);

    ui->startButton->setIconSize(QSize(32,32));
    ui->resetButton->setIconSize(QSize(16, 16));
    ui->stopButton->setIconSize(QSize(16, 16));

    this->setWindowIcon(*timerIcon);
    this->setWindowTitle("Timer");
    trayIcon = new QSystemTrayIcon(*timerIcon);
    trayIcon->show();

    /*****************  CONNECTIONS   ***************************/
    connect(this->oneSecond, SIGNAL(timeout()),
            this, SLOT(onesecond_timer_expired()));
    connect(this->timer, SIGNAL(timeout()),
            this, SLOT(timer_expired()));
    connect(this, SIGNAL(resumeTimer()),
            this, SLOT(on_startButton_clicked()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_stopButton_clicked()
{
    // PAUSE
    if (timer->running){

        oneSecond->stop();
        timer->stop();
        timer->running = false;
        ui->timeEdit->setEnabled(true);
        ui->stopButton->setIcon(*this->playImage);
        ui->startButton->setEnabled(true);
    }else{

        ui->startButton->setEnabled(false);
        ui->stopButton->setIcon(*this->pauseImage);
        emit resumeTimer();
    }
}

void Dialog::on_resetButton_clicked()
{
    // STOP
    this->timer->running = false;
    oneSecond->stop();
    timer->stop();
    ui->timeEdit->setTime(QTime(0,0));
    qDebug() << "Timer stopped.";
    ui->timeEdit->setEnabled(true);
    ui->startButton->setEnabled(true);
    this->alarm->stop();
}


void Dialog::on_startButton_clicked()
{
    // START
    QTime time = ui->timeEdit->time();
    int mseconds = (time.hour()*60*60 + time.minute()*60 + time.second())*1000;
    qDebug() << mseconds << "ms";
    if (mseconds!=0){
        ui->startButton->setDisabled(true);
        this->timer->running = true;
        oneSecond->start(1000);
        timer->start(mseconds);
        ui->timeEdit->setDisabled(true);
    }
}


void Dialog::timer_expired()
{
    this->timer->running = false;
    oneSecond->stop();
    ui->timeEdit->setTime(ui->timeEdit->time().addSecs(-1));
    ui->startButton->setDisabled(false);

    // мигание кнопки для привлечения внимания пользователя
    qDebug() << "expired";
    QApplication::alert(this, 20000);

    trayIcon->showMessage("Information", \
                          "Timer expired", \
                          QSystemTrayIcon::Information,
                          1000);
    ui->timeEdit->setEnabled(true);
    this->alarm->play();

}


void Dialog::onesecond_timer_expired()
{
    ui->timeEdit->setTime(ui->timeEdit->time().addSecs(-1));
}
