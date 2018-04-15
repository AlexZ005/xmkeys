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

    //Popup main window
    QHotkey hotkey(QKeySequence("ctrl+alt+Q"), true);//The hotkey will be automatically registered
    qDebug() << "CtrlAltQ Is Registered: " << hotkey.isRegistered();

    QObject::connect(&hotkey, &QHotkey::activated, qApp, [&](){
        //qDebug() << "Hotkey Activated - the application will quit now";
        //qApp->quit();
        w.activateWindow();
    });

    //register temp hotkey for binding activation
    QHotkey hotkeyActivate(QKeySequence("alt+Q"), true);//The hotkey will be automatically registered
    qDebug() << "AltQ Is Registered: " << hotkeyActivate.isRegistered();

    QObject::connect(&hotkeyActivate, &QHotkey::activated, qApp, [&](){
        qDebug() << "Hotkey Activated - the application will activate shortcuts only if the keys were set!";
        //qApp->quit();

        if (err1 != NULL)
            if (active == 1) {
                active = 0;
                w.on_applyButton_clicked(); //access xmkeys public function
            }
            else {
                active = 1;
                w.on_applyButton_clicked();
            }

    });


    return a.exec();
}
