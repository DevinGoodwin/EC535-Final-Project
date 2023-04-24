
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <QDebug>

int NUM_COLORS = 6;
int NUM_CARDS = 7;
int CARD_WIDTH = 50;
int CARD_HEIGHT = 75;

std::vector<int> Card_XPos = {100,160,70,130,190,100,160}; //Card 1-7 X coord
std::vector<int> Card_YPos = {25,25,110,110,110,195,195}; //Card 1-7 Y coord
std::vector<int> Color_XOffset = {5,27,5,27,5,27}; //Color 1-6 X offset from card X coord
std::vector<int> Color_YOffset = {6,6,28,28,50,50}; //Color 1-6 Y offset from card Y coord
std::vector<QColor> Colors = {Qt::red,QColorConstants::Svg::orange,Qt::yellow,Qt::green,Qt::cyan,QColorConstants::Svg::purple}; //Colors 1-6
std::vector<QPushButton *> Card_Button(7);
std::vector<int> Card_Values(7,0); // 1-63, values of cards on the board
std::vector<int> Card_Selected(7,0); //0 or 1 for if card is selected or not
std::vector<QPushButton *> Options(3);
std::vector<bool> Options_toggle(3);
std::vector<QPushButton *> Point_Buttons(4);
std::vector<int> Points_XPos = {300,300,300,300};
std::vector<int> Points_YPos = {40,90,140,190};
std::vector<int> Points(4,0);

int Num_Cards_Selected = 0; //number of cards selected in the game
int Running_XOR = 0; //cards selected correctness check
std::vector<int> Deck(63,0);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    char s[15];

    // Make the button "invisible"
    QBrush tb(Qt::transparent); // Transparent brush, solid pattern

    // Create the buttons
    for(int i = 0; i < NUM_CARDS; i++){
        sprintf(s,"Button %d",i);
        Card_Button[i] = new QPushButton(s, this);
        Card_Button[i]->setGeometry(QRect(Card_XPos[i],Card_YPos[i],CARD_WIDTH,CARD_HEIGHT));
        // Make the Buttons and their text transparent
        Card_Button[i]->setStyleSheet("background-color: transparent");
        Card_Button[i]->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
        //connect(Card_Button[i], &QPushButton::released, this, &::MainWindow::handleButton);
        connect(Card_Button[i], &QPushButton::released, [this, i] { MainWindow::handleButton(i); });
    }



    //Menu Button
    Options[1] = new QPushButton("Menu", this);
    Options_toggle[1] = false;
    Options[1]->setGeometry(QRect(490,240,60,40));
    Options[1]->setText("Menu");
    Options[1]->setStyleSheet("font: bold 8px;");
    connect(Options[1],&QPushButton::released, this, &::MainWindow::handleMenu);

    // Instruction Button
    Options[0] = new QPushButton("Instructions", this);
    Options_toggle[0] = false;
    Options[0]->setGeometry(QRect(0,0,60,40));
    Options[0]->setText("Instructions");
    Options[0]->setStyleSheet("font: bold 8px;");
    connect(Options[0],&QPushButton::released, this, &::MainWindow::handleIns);

    // Score Buttons
    for(int i = 0; i < 4; i++){
        sprintf(s,"Player %d",i+1);
        Point_Buttons[i] = new QPushButton(s, this);
        Point_Buttons[i]->setGeometry(QRect(Points_XPos[i],Points_YPos[i],60,40));
        // Make the Buttons and their text transparent
        //Point_Buttons[i]->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
        //connect(Card_Button[i], &QPushButton::released, this, &::MainWindow::handleButton);
        connect(Point_Buttons[i], &QPushButton::released, [this, i] { MainWindow::handlePoints(i); });
        Point_Buttons[i]->setVisible(false);
    }

    for(int i  = 0; i < 63; i++){
        Deck[i] = i+1;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(Deck.begin(), Deck.end(), g);
    qInfo() << Deck;
    for(int i = 0; i < NUM_CARDS; i++){
        Card_Values[i] = Deck.back();
        Deck.pop_back();
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

    painter.setBrush(Qt::black);
    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);

    //Background
    painter.drawRect(QRect(0,0,555,280));

    painter.setBrush(Qt::white);

    //Card outlines
    for(int i = 0; i < NUM_CARDS; i++){
        painter.drawRect(QRect(Card_XPos[i],Card_YPos[i],CARD_WIDTH,CARD_HEIGHT));
    }

    QPainter myellip(this);
    myellip.setPen(pen);
    pen.setWidth(2);


    //Dots
    for(int i = 0; i < NUM_CARDS; i++){
        int value = Card_Values[i];
        for(int j = NUM_COLORS-1; j >= 0; j--){
            if(value % 2 == 1){
                myellip.setBrush(Colors[j]);
                myellip.drawEllipse(QRect(Card_XPos[i]+Color_XOffset[j],Card_YPos[i]+Color_YOffset[j],18,18));
            }
            value/=2;
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

    qInfo() << Running_XOR;
    if(Running_XOR == 0 && Num_Cards_Selected != 0){ //proset found
        for(int i = 0; i < NUM_CARDS; i++){
            Card_Button[i]->disconnect();
        }
        if(Deck.size() - Num_Cards_Selected <= 0){  //GAME OVER
            //TODO: handle game over
        }
        else{
            qInfo() << "proset!";
            for(int i = 0; i < 4; i++){
                Point_Buttons[i]->setVisible(true);
            }
        }
    }
}

void MainWindow::handleIns()
{
    Options_toggle[0] = !Options_toggle[0];
    if(Options_toggle[0]){
        Options[0]->setGeometry(QRect(0,0,555,280));
        Options[0]->setText("Three or more cards form a proset if the total number of dots of each color is even.");
        Options[0]->setStyleSheet("font: bold 10px;");
    }else{
        Options[0]->setGeometry(QRect(0,0,60,40));
        Options[0]->setText("Instructions");
        Options[0]->setStyleSheet("font: bold 8px;");
    }
}

void MainWindow::handlePoints(int idx)
{
    for(int i = 0; i < NUM_CARDS; i++){
        if(Card_Selected[i]){
            Card_Selected[i] = 0;
            Card_Values[i] = Deck.back();
            Deck.pop_back();
            Card_Button[i]->setStyleSheet("background-color: transparent");
        }
    }
    Points[idx]+=1; //can change to Num_Cards_Selected
    for(int i = 0; i < 4; i++){
        Point_Buttons[i]->setVisible(false);
    }
    for(int i = 0; i < NUM_CARDS; i++){
        connect(Card_Button[i], &QPushButton::released, [this, i] { MainWindow::handleButton(i); });
    }
    Num_Cards_Selected = 0;
}

void MainWindow::handleMenu()
{
    ((QWidget*)parent())->show();
    this->close();
}
