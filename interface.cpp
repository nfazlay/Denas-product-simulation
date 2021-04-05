#include "interface.h"
#include "ui_interface.h"



Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
    setWindowTitle("SIMULATION");

    connect(&control, &Control::showDisplay, this, &Interface::putDisplay);
    connect(this, &Interface::set, &control, &Control::buttonPressed);
}

Interface::~Interface()
{
    delete ui;
}

void Interface::putDisplay(QString s){
    ui->display->setText(s);
}


void Interface::on_powerButton_clicked()
{

    QFuture<void> next = QtConcurrent::run(&this->control, &Control::start);

}

void Interface::on_selectButton_clicked()
{
    emit set(SELECT);
}

void Interface::on_upButton_clicked()
{
    emit set(UP);
}

void Interface::on_downButton_clicked()
{
    //QString selection = ui->display->toPlainText();
    emit set(DOWN);
}

void Interface::on_skinOn_clicked()
{
    emit set(SKINON);
}

void Interface::on_skinOn_2_clicked()
{
    emit set(SKINOFF);
}
