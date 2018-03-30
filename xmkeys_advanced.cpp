#include "xmkeys_advanced.h"
#include "ui_xmkeys_advanced.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QProcess>

QString adverr;
xmkeys_advanced::xmkeys_advanced(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::xmkeys_advanced)
{
    ui->setupUi(this);
    qDebug() << "advanced window is here";

    ///proces
    QProcess process3;
    process3.start("sh", QStringList() << "-c" << "xmodmap -pke");
    process3.waitForFinished();
    adverr = process3.readAllStandardOutput();

    QVBoxLayout * lay = new QVBoxLayout(this);
    QRegularExpression re("(\\w+)");
    QRegularExpressionMatchIterator i = re.globalMatch(adverr);
    QStringList words;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString word = match.captured(1);
        words << word;
        qDebug() << "matched " << word;
        QPushButton* panelButton = new QPushButton();
        panelButton->setText(word);
        panelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//            ui.PanelButtonGridLayout->addWidget(panelButton,i,j);
        lay->addWidget(panelButton);
    }

    ui->scrollAreaWidgetContents->setLayout(lay);

}

xmkeys_advanced::~xmkeys_advanced()
{
    delete ui;
}
