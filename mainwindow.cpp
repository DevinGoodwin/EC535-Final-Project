
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector>
#include <string>


std::vector<int> Card_XPos = {300,400,250,350,450,300,400}; //Card 1-7 X coord
std::vector<int> Card_YPos = {100,100,250,250,250,400,400}; //Card 1-7 Y coord
std::vector<int> Color_XOffset = {5,45,5,45,5,45}; //Color 1-6 X offset from card X coord
std::vector<int> Color_YOffset = {10,10,50,50,90,90}; //Color 1-6 Y offset from card Y coord
std::vector<QColor> Colors = {Qt::red,QColorConstants::Svg::orange,Qt::yellow,Qt::green,Qt::cyan,QColorConstants::Svg::purple}; //Colors 1-6
std::vector<QPushButton *> Card_Button(7);
std::vector<int> Card_Values(7,0); // 1-63, values of cards on the board
std::vector<int> Card_Selected(7,0); //0 or 1 for if card is selected or not
std::vector<QPushButton *> Options(3);
std::vector<bool> Options_toggle(3);

int Num_Cards_Selected = 0; //number of cards selected in the game
int Running_XOR = 0;

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
        Card_Button[i] = new QPushButton(s, this);
        Card_Button[i]->setGeometry(QRect(Card_XPos[i],Card_YPos[i],80,130));
        // Make the Buttons and their text transparent
        Card_Button[i]->setStyleSheet("background-color: transparent");
        Card_Button[i]->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
        //connect(Card_Button[i], &QPushButton::released, this, &::MainWindow::handleButton);
        connect(Card_Button[i], &QPushButton::released, [this, i] { MainWindow::handleButton(i); });
    }

    // Instruction Button
    Options[0] = new QPushButton("Instructions", this);
    Options[0]->setGeometry(QRect(0,0,80,80));
    Options_toggle[0] = false;
    connect(Options[0],&QPushButton::released, this, &::MainWindow::handleIns);


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

    //Dots
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 6; j++){
            myellip.setBrush(Colors[j]);
            myellip.drawEllipse(QRect(Card_XPos[i]+Color_XOffset[j],Card_YPos[i]+Color_YOffset[j],30,30));
        }
    }
}

void MainWindow::handleButton(int i)
{
    if(!Card_Selected[i]){ //card getting selected
        Card_Selected[i] = 1;
        Num_Cards_Selected++;
        Card_Button[i]->setStyleSheet("border:4px solid #ff0000;");
    }
    else{ //card getting deselected
        Card_Selected[i] = 0;
        Num_Cards_Selected--;
        Card_Button[i]->setStyleSheet("background-color: transparent");
    }

    Running_XOR ^= Card_Values[i];

    if(Running_XOR == 0 && Num_Cards_Selected != 0){ //proset found
        //TODO
    }

}

void MainWindow::handleIns()
{
    Options_toggle[0] = !Options_toggle[0];
    if(Options_toggle[0]){
        Options[0]->setGeometry(QRect(0,0,800,600));
        Options[0]->setText("Three or more cards form a proset if the total number of dots of each color is even.");
    }else{
        Options[0]->setGeometry(QRect(0,0,80,80));
        Options[0]->setText("Instructions");
    }
}

