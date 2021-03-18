#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>

namespace Ui {
class Interface;
}

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();

private slots:
    void on_powerButton_clicked();

private:
    Ui::Interface *ui;
    bool powerOn = false;
};

#endif // INTERFACE_H
