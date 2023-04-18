#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    QPushButton  *Play =  new QPushButton("Play", this);
    Play->setGeometry(QRect(350,400,100,60));
    connect(Play, &QPushButton::released, this, &Menu::handlePlay);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::handlePlay()
{
    MainWindow = new class MainWindow(this);
    MainWindow->setGeometry(QRect(0,0,800,600));
    MainWindow -> show();
    hide();
}
