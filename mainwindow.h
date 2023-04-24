
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include <QPushButton>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void paintEvent(QPaintEvent *event);

private slots:
    void handleButton(int i);
    void handleIns();
    void handlePoints(int i);
    void handleMenu();
    void handleReset();

private:
    Ui::MainWindow *ui;
    QPushButton *m_button;
};

#endif // MAINWINDOW_H
