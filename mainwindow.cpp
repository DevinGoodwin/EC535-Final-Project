
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector>
#include <string>


std::vector<int> Card_XPos = {300,400,250,350,450,300,400}; //Card 1-7 X coord
std::vector<int> Card_YPos = {100,100,250,250,250,400,400}; //Card 1-7 Y coord
std::vector<int> Color_XOffset = {5,45,5,45,5,45}; //Color 1-6 X offset from card X coord
std::vector<int> Color_YOffset = {10,10,50,50,90,90}; //Color 1-6 Y offset from card Y coord
std::vector<QColor> Colors = {Qt::red,QColorConstants::Svg::orange,Qt::yellow,Qt::green,Qt::cyan,QColorConstants::Svg::purple}; //Colors 1-6
std::vector<QPushButton *> Buttons(7);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    char s[15];

    // Make the button "invisible"
    QBrush tb(Qt::transparent); // Transparent brush, solid pattern

    // Create the buttons
    for(int i = 0; i < 7; i++){
        sprintf_s(s,"Button %d",i);
        Buttons[i] = new QPushButton(s, this);
        Buttons[i]->setGeometry(QRect(Card_XPos[i],Card_YPos[i],80,130));
        // Make the Buttons and their text transparent
        Buttons[i]->setStyleSheet("background-color: transparent");
        Buttons[i]->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
        connect(Buttons[i], &QPushButton::released, this, &MainWindow::handleButton);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QPen pen;

    painter.setBrush(Qt::green);
    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);

    //Background
    painter.drawRect(QRect(0,0,800,600));

    painter.setBrush(Qt::white);

    //Card outlines
    for(int i = 0; i < 7; i++){
        painter.drawRect(QRect(Card_XPos[i],Card_YPos[i],80,130));
    }

    QPainter myellip(this);
    myellip.setPen(pen);
    pen.setWidth(2);

    //First 4 cards
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 6; j++){
            myellip.setBrush(Colors[j]);
            myellip.drawEllipse(QRect(Card_XPos[i]+Color_XOffset[j],Card_YPos[i]+Color_YOffset[j],30,30));
        }
    }

}

void MainWindow::handleButton()
{
    // Make the button "visible"
    Buttons[0]->setPalette(QPalette()); // Back to the default palette
}
