#ifndef XMKEYS_H
#define XMKEYS_H

#include <QMainWindow>

extern volatile int active;

namespace Ui {
class xmkeys;
}

class xmkeys : public QMainWindow
{
    Q_OBJECT

public:
    explicit xmkeys(QWidget *parent = 0);
    ~xmkeys();

private slots:
    void on_closeButton_clicked();

    void on_applyButton_clicked();

    void on_checkBox_toggled(bool checked);

    void on_leftMouseKey_clicked();

    void on_middleMouseKey_clicked();

    void on_rightMouseKey_clicked();

private:
    Ui::xmkeys *ui;
};

#endif // XMKEYS_H
