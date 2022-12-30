#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Public/appsignal.h"

#include <QDir>
#include <QDateTime>
#include <QFileDialog>
#include <QStandardPaths>
#include <QListView>
#include <regex>
#include <QTimer>

// test
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();

    setWindowTitle("Mundum");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    ui->btnMin->setID(ButtonDesigned::Button_Min);
    ui->btnClose->setID(ButtonDesigned::Button_Close);

    connect(ui->btnMin, &QPushButton::clicked, this, [this]{ showMinimized(); });
    connect(ui->btnClose, &QPushButton::clicked, this, [this] { this->close(); });

    // 随机变色
//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, [this]{ ui->widgetPlayer->changeColor(); });
//    timer->start(100);

    // 加载图片
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->pos().x() > ui->widgetTitle->width() + ui->widgetTitle->x()
            || event->pos().y() > ui->widgetTitle->height() + layout()->contentsMargins().top() + ui->widgetTitle->y()) return;
    if (event->button() == Qt::LeftButton)
    {
        mLastMousePosition = event->globalPos();
        mMousePressed = true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mMousePressed = false;
    event->accept();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!mMousePressed) return;
    if (!event->buttons().testFlag(Qt::LeftButton)) return;
    const QPointF position = pos() + event->globalPos() - mLastMousePosition; //the position of mainfrmae + (current_mouse_position - last_mouse_position)
    move(position.x(), position.y());
    mLastMousePosition = event->globalPos();
}
