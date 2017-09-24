#include "xmkeys.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    xmkeys w;
    w.show();
    qDebug() << "Widget";



    return a.exec();
}
