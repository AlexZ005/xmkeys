#include "xmkeys_advanced.h"
#include "ui_xmkeys_advanced.h"

xmkeys_advanced::xmkeys_advanced(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::xmkeys_advanced)
{
    ui->setupUi(this);
}

xmkeys_advanced::~xmkeys_advanced()
{
    delete ui;
}
