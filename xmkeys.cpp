#include "xmkeys.h"
#include "ui_xmkeys.h"
#include <QProcess>
#include <QDir>
#include <QDebug>
#include <QMessageBox>

volatile int active;

xmkeys::xmkeys(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::xmkeys)
{
    ui->setupUi(this);
}

xmkeys::~xmkeys()
{
    delete ui;
}

void xmkeys::on_closeButton_clicked()
{
    QCoreApplication::quit();
}

void xmkeys::on_applyButton_clicked()
{

    int result = system("xkbset");
     if(result!=0) {
         QMessageBox::information(
             this,
             tr("xkbset"),
             tr("Please install xkbset.") );

         QCoreApplication::quit();
     }

    if(active == 1 && result == 0)
    {
//        qDebug() << "activated!";

        QProcess *process = new QProcess(this);
        QString file = "xkbset";
        QStringList arguments;
        arguments << "m";
//        qDebug() << "xkbset m";

        process->start(file, arguments);

        qDebug() << "binding!";
        QProcess::execute("xmodmap -e \"keycode 133 = Pointer_Button1\"");

    }
    else if (result == 0)
    {
        qDebug() << "disactivated!";

        QProcess *process = new QProcess(this);
        QString file = "xkbset";
        QStringList arguments;
        arguments << "-m";
        qDebug() << "xkbset -m";
        process->start(file, arguments);

        qDebug() << "unbinding!";
        QProcess::execute("xmodmap -e \"keycode 133 = Super_L NoSymbol Super_L\"");


    }

}

void xmkeys::on_checkBox_toggled(bool checked)
{
    qDebug() << "activation state changed, state: " << checked;

    if (checked == true)
    {
        active = 1;
    }
    else
        active = 0;

}
