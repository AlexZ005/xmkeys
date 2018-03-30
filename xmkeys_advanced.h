#ifndef XMKEYS_ADVANCED_H
#define XMKEYS_ADVANCED_H

#include <QDialog>

namespace Ui {
class xmkeys_advanced;
}

class xmkeys_advanced : public QDialog
{
    Q_OBJECT

public:
    explicit xmkeys_advanced(QWidget *parent = 0);
    ~xmkeys_advanced();

private:
    Ui::xmkeys_advanced *ui;
};

#endif // XMKEYS_ADVANCED_H
