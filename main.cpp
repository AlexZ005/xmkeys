#include "xmkeys.h"
#include <QApplication>

#include <QProcess>
#include <QHotkey>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    xmkeys w;
    w.show();


    QHotkey hotkey(QKeySequence("ctrl+alt+Q"), true);//The hotkey will be automatically registered
        qDebug() << "Is Registered: " << hotkey.isRegistered();

        QObject::connect(&hotkey, &QHotkey::activated, qApp, [&](){
            qDebug() << "Hotkey Activated - the application will quit now";
            //qApp->quit();

            w.activateWindow();

        });


        QHotkey hotkeyActivate(QKeySequence("alt+Q"), true);//The hotkey will be automatically registered
            qDebug() << "Is Registered: " << hotkeyActivate.isRegistered();

            QObject::connect(&hotkeyActivate, &QHotkey::activated, qApp, [&](){
                qDebug() << "Hotkey Activated - the application will activate shortcuts only if the keys were set!";
                //qApp->quit();

                if (err1 != NULL)
                if (active == 1) {
                    active = 0;
                    qDebug() << "xmodmap -e " << err1.remove(QRegExp("[\\n\\t\\r]"));
                    qDebug() << "xmodmap -e " << err2.remove(QRegExp("[\\n\\t\\r]"));
                    qDebug() << "xmodmap -e " << err3.remove(QRegExp("[\\n\\t\\r]"));
                    QProcess::execute("xmodmap -e \"" + err1.remove(QRegExp("[\\n\\t\\r]")) + "\"");
                    QProcess::execute("xmodmap -e \"" + err2.remove(QRegExp("[\\n\\t\\r]")) + "\"");
                    QProcess::execute("xmodmap -e \"" + err3.remove(QRegExp("[\\n\\t\\r]")));

                }
                else {

                    active = 1;
                    qDebug() << "xmodmap -e " << err1.remove(QRegExp("[\\n\\t\\r]"));
                    qDebug() << "xmodmap -e " << err2.remove(QRegExp("[\\n\\t\\r]"));
                    qDebug() << "xmodmap -e " << err3.remove(QRegExp("[\\n\\t\\r]"));

                    QProcess::execute("xmodmap -e \"keycode " + modkey1 + " = Pointer_Button1\"");
                    QProcess::execute("xmodmap -e \"keycode " + modkey2 + " = Pointer_Button2\"");
                    QProcess::execute("xmodmap -e \"keycode " + modkey3 + " = Pointer_Button3\"");


                }

            });


    return a.exec();
}
