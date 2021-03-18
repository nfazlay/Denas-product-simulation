#include "interface.h"
#include "ui_interface.h"

Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
}

Interface::~Interface()
{
    delete ui;
}

void Interface::on_powerButton_clicked()
{
    if(powerOn == false){
        ui->display->setText("Welcome");
        powerOn = true;
    }
    else if(powerOn == true){
        ui->display->setText("");
        powerOn = false;
    }
}
