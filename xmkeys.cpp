#include "xmkeys.h"
#include "ui_xmkeys.h"
#include <QProcess>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>

volatile int active;
QString err;



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
        QProcess process2;
        QString modkey = "133";
        QString xmodmapgrep = "./xmodmapgrep.sh ";
        QString xmodmapgrepkey = xmodmapgrep + modkey;
        process2.start(xmodmapgrepkey);
        process2.waitForFinished();
        err = process2.readAllStandardOutput();
        qDebug() << err;

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
        QString restoreMap = "xmodmap -e ";
        QString result = restoreMap + "\"" + err.remove(QRegExp("[\\n\\t\\r]")) + "\"";
        qDebug() << result;
        QProcess::execute(result);


    }

}

void xmkeys::on_checkBox_toggled(bool checked)
{
    qDebug() << "activation state changed, state: " << checked;

//    qDebug() << QKeySequence::fromString("SPACE")[0]; // 1




    if (checked == true)
    {
        active = 1;
    }
    else
        active = 0;

}

void xmkeys::on_leftMouseKey_clicked()
{
    qDebug() << "ouch!";

    qDebug() << "xevcrop";
    QProcess process3;
    QString xevcrop = "./xev";
    process3.start(xevcrop);
    process3.waitForFinished();
    err = process3.readAllStandardOutput();
    qDebug() << err;

    ui->leftMouseKey->setText(err);

}


void xmkeys::on_middleMouseKey_clicked()
{
    qDebug() << "ouch!";

    qDebug() << "xevcrop";
    QProcess process4;
    QString xevcrop2 = "./xev";
    process4.start(xevcrop2);
    process4.waitForFinished();
    err = process4.readAllStandardOutput();
    qDebug() << err;

    ui->middleMouseKey->setText(err);

}


void xmkeys::on_rightMouseKey_clicked()
{
    qDebug() << "ouch!";

    qDebug() << "xevcrop";
    QProcess process5;
    QString xevcrop3 = "./xev";
    process5.start(xevcrop3);
    process5.waitForFinished();
    err = process5.readAllStandardOutput();
    qDebug() << err;

    ui->rightMouseKey->setText(err);

}
