
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
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
std::vector<QPushButton *> Options(4);
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

    // Reset Button
    Options[3] = new QPushButton("Reset", this);
    Options[3]->setGeometry(QRect(490,240,60,40));
    Options[3]->setText("Reset");
    Options[3]->setStyleSheet("font: bold 8px;");
    Options[3]->setVisible(true);
    connect(Options[3],&QPushButton::released, this, &::MainWindow::handleReset);

    // Gameover Button
    Options[2] = new QPushButton("Gameover", this);
    Options_toggle[2] = false;
    Options[2]->setGeometry(QRect(0,0,555,280));
    Options[2]->setVisible(false);
    connect(Options[2],&QPushButton::released, this, &::MainWindow::handleMenu);

    //Menu Button
    Options[1] = new QPushButton("Menu", this);
    Options_toggle[1] = false;
    Options[1]->setGeometry(QRect(0,240,60,40));
    Options[1]->setText("Menu");
    Options[1]->setStyleSheet("font: bold 8px;");
    Options[1]->setVisible(true);
    connect(Options[1],&QPushButton::released, this, &::MainWindow::handleMenu);

    // Instruction Button
    Options[0] = new QPushButton("Instructions", this);
    Options_toggle[0] = false;
    Options[0]->setGeometry(QRect(0,0,60,40));
    Options[0]->setText("Instructions");
    Options[0]->setStyleSheet("font: bold 8px;");
    Options[0]->setVisible(true);
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
    if(Deck.size() == 63){
        for(int i  = 0; i < 63; i++){
            Deck[i] = i+1;
        }
        qInfo() << Deck << " " << Deck.size();
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(Deck.begin(), Deck.end(), g);
        qInfo() << Deck << " " << Deck.size();
        for(int i = 0; i < NUM_CARDS; i++){
            Card_Values[i] = Deck.back();
            Deck.pop_back();
        }
        qInfo() << Deck << " " << Deck.size();
        for(int i = 1; i < 127; i++){
            int xorv = 0;
            int init = i;
            for(int j = 0; j < 7; j++){
                if(init%2 == 1){
                    xorv^=Card_Values[j];
                }
                init/=2;
            }
            if(xorv == 0){
                init = i;
                for(int j = 0; j < 7; j++){
                    if(init%2 == 1){
                        qInfo() << j+1;
                    }
                    init/=2;
                }
                break;
            }
        }
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

    painter.setBrush(Qt::darkGreen);
    pen.setColor(Qt::darkGreen);
    pen.setWidth(3);
    painter.setPen(pen);

    //Background
    painter.drawRect(QRect(0,0,555,280));

    pen.setColor(Qt::black);
    painter.setPen(pen);
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
    //Score
    QRect ScoreBox = QRect(400,25,150,230);
    QFont font = painter.font();
    font.setPixelSize(18);
    painter.setFont(font);
    std::string ScoreText = "Deck Size: " + std::to_string(Deck.size()) + "\n\n\n\n";
    for(int i = 0; i < 4; i++){
        ScoreText += "Player " + std::to_string(i+1) + ": " + std::to_string(Points[i]) + "\n";
    }
    const char* ScoreT = ScoreText.c_str();
    painter.drawText(ScoreBox,tr(ScoreT));
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
        qInfo() << "proset!";
        for(int i = 0; i < 4; i++){
            Point_Buttons[i]->setVisible(true);
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
            if(Deck.size() == 0){
                Card_Values[i] = 0;
            }
            else{
                Card_Values[i] = Deck.back();
                Deck.pop_back();
            }
            Card_Button[i]->setStyleSheet("background-color: transparent");
        }
    }

    for(int i = 1; i < 127; i++){
        int xorv = 0;
        int init = i;
        for(int j = 0; j < 7; j++){
            if(init%2 == 1){
                xorv^=Card_Values[j];
            }
            init/=2;
        }
        if(xorv == 0){
            init = i;
            for(int j = 0; j < 7; j++){
                if(init%2 == 1){
                    qInfo() << j+1;
                }
                init/=2;
            }
            break;
        }
    }

    Points[idx]+=Num_Cards_Selected; //can change to Num_Cards_Selected
    qInfo() << Points;
    qInfo() << Deck << " " << Deck.size();
    this->update();
    for(int i = 0; i < 4; i++){
        Point_Buttons[i]->setVisible(false);
    }
    assert(Deck.size() >= 0);
    if(Deck.size() == 0){
        // GAME OVER
        qInfo() << "Game should end here, cards left in deck " << Deck.size();
        int wpoints = Points[0];
        int winner = 1;
        char s_winner[20];
        Points[0] = 0;
        for(int i = 1; i < 4; i++){
            if(wpoints<Points[i]){
                wpoints = Points[i];
                winner = i+1;
            }
            Points[i] = 0;
        }
        sprintf(s_winner,"Player %d Wins!", winner);
        Options[2]->setText(s_winner);
        Options[2]->setStyleSheet("font: bold 18px;");
        Options[3]->setVisible(false);
        Options[2] -> setVisible(true);
        Options[1] -> setVisible(false);
        Options[0] -> setVisible(false);
        for(int i  = 0; i < 63; i++){
            Deck.push_back(i+1);
        }
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

void MainWindow::handleReset()
{
    qInfo() << "Starting size";
    int x = Deck.size(), i;
    qInfo() << x;
    for(i = 0; i < x; i++){
        Deck.pop_back();
        qInfo() << i;
    }
    for(i  = 0; i < 63; i++){
        Deck.push_back(i+1);
    }
    qInfo() << "Pushed size";
    qInfo() << Deck.size();
    for(i = 1; i < 4; i++){
        Points[i] = 0;
    }
    this->close();
    ((QWidget*)parent())->show();
}
