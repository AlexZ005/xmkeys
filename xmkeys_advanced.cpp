#include "xmkeys_advanced.h"
#include "ui_xmkeys_advanced.h"
#include <QDebug>
#include <QVBoxLayout>

xmkeys_advanced::xmkeys_advanced(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::xmkeys_advanced)
{
    ui->setupUi(this);
    qDebug() << "advanced window is here";

    QVBoxLayout * lay = new QVBoxLayout(this);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            QPushButton* panelButton = new QPushButton();
            panelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//            ui.PanelButtonGridLayout->addWidget(panelButton,i,j);
            lay->addWidget(panelButton,i);
        }
    }
    ui->scrollAreaWidgetContents->setLayout(lay);

}

xmkeys_advanced::~xmkeys_advanced()
{
    delete ui;
}
