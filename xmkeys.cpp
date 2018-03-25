#include "xmkeys.h"
#include "ui_xmkeys.h"

#include <QProcess>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>

#include <QCloseEvent>

volatile int active;
QString err;
QString err1;
QString err2;
QString err3;
QString modkey1;
QString modkey2;
QString modkey3;


QString keyCode()
{

    qDebug() << "xevcrop";
    QProcess process4;
    QString xevcrop2 = "./xev";
    process4.start(xevcrop2);
    process4.waitForFinished();
    err = process4.readAllStandardOutput();
    qDebug() << err;
    return err;
}


xmkeys::xmkeys(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::xmkeys)
{
    ui->setupUi(this);
}

xmkeys::~xmkeys()
{
    qDebug() << "Cleaning up!";
    qDebug() << "unbinding!";
//        QString restoreMap = "xmodmap -e ";
//        QString result = restoreMap + "\"" + err.remove(QRegExp("[\\n\\t\\r]")) + "\"";


    qDebug() << "xmodmap -e " << err1.remove(QRegExp("[\\n\\t\\r]"));
    qDebug() << "xmodmap -e " << err2.remove(QRegExp("[\\n\\t\\r]"));
    qDebug() << "xmodmap -e " << err3.remove(QRegExp("[\\n\\t\\r]"));
    QProcess::execute("xmodmap -e \"" + err1.remove(QRegExp("[\\n\\t\\r]")) + "\"");
    QProcess::execute("xmodmap -e \"" + err2.remove(QRegExp("[\\n\\t\\r]")) + "\"");
    QProcess::execute("xmodmap -e \"" + err3.remove(QRegExp("[\\n\\t\\r]")));


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


        QProcess process2;
        QProcess process2h;
        modkey1 = ui->leftMouseKey->text();
        qDebug() << modkey1;

        process2.start("sh", QStringList() << "-c" << "xmodmap -pke | grep \" " + modkey1 + " \"");
        process2.waitForFinished();
        err1 = process2.readAllStandardOutput();

        modkey2 = ui->middleMouseKey->text();
        process2.start("sh", QStringList() << "-c" << "xmodmap -pke | grep \" " + modkey2 + " \"");
        process2.waitForFinished();
        err2 = process2.readAllStandardOutput();

        modkey3 = ui->rightMouseKey->text();
        process2.start("sh", QStringList() << "-c" << "xmodmap -pke | grep \" " + modkey3 + " \"");
        process2.waitForFinished();
        err3 = process2.readAllStandardOutput();

                qDebug() << err1;
                        qDebug() << err2;
                                qDebug() << err3;
       qDebug() << "xmodmap -e " << err1.remove(QRegExp("[\\n\\t\\r]"));
       qDebug() << "xmodmap -e " << err2.remove(QRegExp("[\\n\\t\\r]"));
       qDebug() << "xmodmap -e " << err3.remove(QRegExp("[\\n\\t\\r]"));

       QProcess::execute("xmodmap -e \"keycode " + modkey1 + " = Pointer_Button1 Pointer_Button1 Pointer_Button1\"");
       QProcess::execute("xmodmap -e \"keycode " + modkey2 + " = Pointer_Button2 Pointer_Button2 Pointer_Button2\"");
       QProcess::execute("xmodmap -e \"keycode " + modkey3 + " = Pointer_Button3 Pointer_Button3 Pointer_Button3\"");
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
//        QString restoreMap = "xmodmap -e ";
//        QString result = restoreMap + "\"" + err.remove(QRegExp("[\\n\\t\\r]")) + "\"";


        qDebug() << "xmodmap -e " << err1.remove(QRegExp("[\\n\\t\\r]"));
        qDebug() << "xmodmap -e " << err2.remove(QRegExp("[\\n\\t\\r]"));
        qDebug() << "xmodmap -e " << err3.remove(QRegExp("[\\n\\t\\r]"));
        QProcess::execute("xmodmap -e \"" + err1.remove(QRegExp("[\\n\\t\\r]")) + "\"");
        QProcess::execute("xmodmap -e \"" + err2.remove(QRegExp("[\\n\\t\\r]")) + "\"");
        QProcess::execute("xmodmap -e \"" + err3.remove(QRegExp("[\\n\\t\\r]")));

//        qDebug() << result;
//        QProcess::execute(result);


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
    keyCode();
    ui->leftMouseKey->setText(err);
}


void xmkeys::on_middleMouseKey_clicked()
{
    keyCode();
    ui->middleMouseKey->setText(err);
}


void xmkeys::on_rightMouseKey_clicked()
{
    keyCode();
    ui->rightMouseKey->setText(err);
}



void xmkeys::on_activationComboBox_activated(const QString &arg1)
{
    QMessageBox::information(
        this,
        tr("Maping"),
        tr("CapsLock not yet implemented.") );

}
