#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    //Creating Play button
    QPushButton  *Play =  new QPushButton("Play", this);
    Play->setGeometry(QRect(240,238,60,40));
    Play->setStyleSheet("font: bold 12px;");
    connect(Play, &QPushButton::released, this, &Menu::handlePlay);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::handlePlay()
{
    //Closing the menu and opening game
    m = new class MainWindow(this);
    m->showMaximized();
    hide();
}
