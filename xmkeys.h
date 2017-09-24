#ifndef XMKEYS_H
#define XMKEYS_H

#include <QMainWindow>

namespace Ui {
class xmkeys;
}

class xmkeys : public QMainWindow
{
    Q_OBJECT

public:
    explicit xmkeys(QWidget *parent = 0);
    ~xmkeys();

private:
    Ui::xmkeys *ui;
};

#endif // XMKEYS_H
