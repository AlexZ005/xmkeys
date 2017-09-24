#include "xmkeys.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    xmkeys w;
    w.show();

    return a.exec();
}
