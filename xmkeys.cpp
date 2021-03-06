#include "xmkeys.h"
#include "ui_xmkeys.h"
#include <iostream>
#include <string>
#include <regex>
#include <QStandardItemModel>
#include "xmkeys_advanced.h"
//#include <QApplication>

#include <QProcess>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QSettings>
#include <QCloseEvent>

#include <QFile>



volatile int active;
QString err;
QString err1;
QString err2;
QString err3;
QString modkey1;
QString modkey2;
QString modkey3;
QString adverr;

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
    connect(ui->advancedButton, SIGNAL(clicked()), this, SLOT(advancedButtonClicked()));

    m_sSettingsFile = QDir::currentPath() + "/xmkeys.ini";
    loadSettings();
}


void xmkeys::loadSettings()
{
 QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
 QString s_leftText = settings.value("mleft", "").toString();
 QString s_rightText = settings.value("mright", "").toString();
 QString s_middleText = settings.value("mmiddle", "").toString();
 if (ui->leftMouseKey)
 {
  ui->leftMouseKey->setText(s_leftText);
 }
 if (ui->middleMouseKey)
 {
  ui->middleMouseKey->setText(s_middleText);
 }
 if (ui->rightMouseKey)
 {
  ui->rightMouseKey->setText(s_rightText);
 }
}

void xmkeys::saveSettings()
{
 QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
 QString s_leftText = ui->leftMouseKey->text();
 QString s_rightText = ui->rightMouseKey->text();
 QString s_middleText = ui->middleMouseKey->text();
 settings.setValue("mleft", s_leftText);
 settings.setValue("mright", s_rightText);
 settings.setValue("mmiddle", s_middleText);
 if (ui->leftMouseKey)
 {
  ui->leftMouseKey->setText(s_leftText);
 }
 if (ui->middleMouseKey)
 {
  ui->middleMouseKey->setText(s_middleText);
 }
 if (ui->rightMouseKey)
 {
  ui->rightMouseKey->setText(s_rightText);
 }

}


void xmkeys::advancedButtonClicked()
{
    qDebug() << "tset";
//    //    exampleDialog->show();
//        xmkeys_advanced w;
////        w.show();
//        w.exec();


    QStandardItemModel *model=new QStandardItemModel();


    QStringList list;
    list << "keycode" << "Eng" << "EngSh" << "Sp" << "SpSh" << "SpAlt" << "SpAltSh" << "Cy" << "CySh";
            model->setHorizontalHeaderLabels(list);

    QProcess process3;
    process3.start("sh", QStringList() << "-c" << "xmodmap -pke | grep \" " + modkey1 + " \"");
    process3.waitForFinished();
    adverr = process3.readAllStandardOutput();

    QRegularExpression re("(\\w+)");
    QRegularExpressionMatchIterator i = re.globalMatch(adverr);
    QStringList words;
                int row = 0;
                int col =0;
    while (i.hasNext()) {
        QStandardItem *newItem = 0;
        QRegularExpressionMatch match = i.next();
        QString word = match.captured(1);
        words << word;
        if (word == "keycode")
        { qDebug() << "CODE ACCETER"; row++; col=0; }
        else {
        qDebug() << "matched " << word;
        newItem = new QStandardItem(word);
        model->setItem(row, col, newItem);
        col++;
        }
    }


    xmkeys_advanced *tableView = new xmkeys_advanced(model);
    tableView->verticalHeader()->hide();
    tableView->setWindowTitle(QObject::tr("Frozen Column Example"));
    tableView->resize(560, 680);
    tableView->show();
   // return app.exec();


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

    saveSettings();

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
        modkey1 = ui->leftMouseKey->text();
        qDebug() << "mod1 is " << modkey1;

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

       QProcess::execute("xmodmap -e \"keycode " + modkey1 + " = Pointer_Button1 Pointer_Button1 Pointer_Button1 Pointer_Button1\"");
       QProcess::execute("xmodmap -e \"keycode " + modkey2 + " = Pointer_Button2 Pointer_Button2 Pointer_Button2 Pointer_Button2\"");
       QProcess::execute("xmodmap -e \"keycode " + modkey3 + " = Pointer_Button3 Pointer_Button3 Pointer_Button3 Pointer_Button3\"");
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

    QProcess process3;
    modkey1 = ui->leftMouseKey->text();


    process3.start("sh", QStringList() << "-c" << "xmodmap -pke | grep \" " + modkey1 + " \"");
    process3.waitForFinished();
    err1 = process3.readAllStandardOutput();

//    std::string str(err1);
//    std::regex r("^keycode (\\d)\\d"); // entire match will be 2 numbers
//    std::smatch m;
//    std::regex_search(str, m, r);
//    for(auto v: m) std::cout << v << std::endl;


    QRegularExpression re("(\\w+)");
    QRegularExpressionMatchIterator i = re.globalMatch(err1);
    QStringList words;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString word = match.captured(1);
        words << word;
        qDebug() << "matched " << word;
    }
//    qDebug() << matched.captured(0);
  //  ui->leftMouseKey->setText(matched.captured(2));
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

void xmkeys::on_advancedButton_clicked()
{
//    xmkeys_advanced w;
//    w.show();
}
