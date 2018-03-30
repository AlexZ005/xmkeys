#ifndef XMKEYS_H
#define XMKEYS_H

#include <QMainWindow>

extern volatile int active;
extern QString err;
extern QString err1;
extern QString err2;
extern QString err3;
extern QString modkey1;
extern QString modkey2;
extern QString modkey3;

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

    void on_activationComboBox_activated(const QString &arg1);

    void on_advancedButton_clicked();

    void advancedButtonClicked();

private:
    Ui::xmkeys *ui;
};

#endif // XMKEYS_H
