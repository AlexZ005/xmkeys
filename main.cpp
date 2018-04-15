#include "xmkeys.h"
#include <QApplication>

#include <QProcess>
#include <QHotkey>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    xmkeys w;
    w.show();
    bool hold3 = false;
    xmkeys xkk;

    QHotkey hotkeyMeta(QKeySequence("Ctrl+Shift+F"), true);//The hotkey will be automatically registered
        qDebug() << "Meta Is Registered: " << hotkeyMeta.isRegistered();

        QObject::connect(&hotkeyMeta, &QHotkey::activated, qApp, [&](){
            qDebug() << "Meta Hotkey Activated - enabling mouse hold";
            //qApp->quit();
            if (!hold3)
            {
                hold3 = true;
                QProcess::execute("sleep 0.2");
                QProcess::execute("xdotool mousedown 3");
                qDebug() << "mousedown";
            }
            else
            {
                hold3 = false;
                QProcess::execute("xdotool mouseup 3");
                qDebug() << "mouseup";
            }

        });

    QHotkey hotkey(QKeySequence("ctrl+alt+Q"), true);//The hotkey will be automatically registered
        qDebug() << "CtrlAltQ Is Registered: " << hotkey.isRegistered();

        QObject::connect(&hotkey, &QHotkey::activated, qApp, [&](){
            qDebug() << "Hotkey Activated - the application will quit now";
            //qApp->quit();

            w.activateWindow();

        });


        QHotkey hotkeyActivate(QKeySequence("alt+Q"), true);//The hotkey will be automatically registered
            qDebug() << "AltQ Is Registered: " << hotkeyActivate.isRegistered();

            QObject::connect(&hotkeyActivate, &QHotkey::activated, qApp, [&](){
                qDebug() << "Hotkey Activated - the application will activate shortcuts only if the keys were set!";
                //qApp->quit();



                if (err1 != NULL)
                if (active == 1) {
                    active = 0;
//                    qDebug() << "xmodmap -e " << err1.remove(QRegExp("[\\n\\t\\r]"));
//                    qDebug() << "xmodmap -e " << err2.remove(QRegExp("[\\n\\t\\r]"));
//                    qDebug() << "xmodmap -e " << err3.remove(QRegExp("[\\n\\t\\r]"));
//                    QProcess::execute("xmodmap -e \"" + err1.remove(QRegExp("[\\n\\t\\r]")) + "\"");
//                    QProcess::execute("xmodmap -e \"" + err2.remove(QRegExp("[\\n\\t\\r]")) + "\"");
//                    QProcess::execute("xmodmap -e \"" + err3.remove(QRegExp("[\\n\\t\\r]")));


//                    QProcess *process = new QProcess();
//                    QString file = "xkbset";
//                    QStringList arguments;
//                    arguments << "-m";
//                    qDebug() << "xkbset -m";
//                    process->start(file, arguments);

                    w.on_applyButton_clicked();
                }
                else {

                    active = 1;
//                    qDebug() << "xmodmap -e " << err1.remove(QRegExp("[\\n\\t\\r]"));
//                    qDebug() << "xmodmap -e " << err2.remove(QRegExp("[\\n\\t\\r]"));
//                    qDebug() << "xmodmap -e " << err3.remove(QRegExp("[\\n\\t\\r]"));

//                    QProcess::execute("xmodmap -e \"keycode " + modkey1 + " = Pointer_Button1 Pointer_Button1 Pointer_Button1\"");
//                    QProcess::execute("xmodmap -e \"keycode " + modkey2 + " = Pointer_Button2 Pointer_Button2 Pointer_Button2\"");
//                    QProcess::execute("xmodmap -e \"keycode " + modkey3 + " = Pointer_Button3 Pointer_Button3 Pointer_Button3\"");

//                    QProcess *process = new QProcess();
//                    QString file = "xkbset";
//                    QStringList arguments;
//                    arguments << "m";
//                    qDebug() << "xkbset m";
//                    process->start(file, arguments);

                    w.on_applyButton_clicked();
                }

            });


    return a.exec();
}
