#include "emojipick.h"
#include "ui_emojipick.h"
#include <QDebug>
emojipick::emojipick(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::emojipick)
{
    ui->setupUi(this);
    emojisize = 36;
    initemoji();
}

emojipick::~emojipick()
{
    delete ui;
}
void emojipick::addemoji(int i,char32_t emojitext[]){
    emojitext[0]=emojitext[0]+i;
    int row = i/ui->tableWidget->rowCount();
    int column = i % ui->tableWidget->rowCount();
    QTableWidgetItem * emojiItem = new QTableWidgetItem();
    ui->tableWidget->setItem(row,column,emojiItem);
    QLabel *emojiIcon = new QLabel;
    emojiIcon->setMargin(4);
    emojiIcon->setText(QString::fromUcs4(emojitext));
    ui->tableWidget->setCellWidget(row,column,emojiIcon);
}
void emojipick::initemoji(){
    char32_t emojitext[] = {0x1F601,0x0};
    for(int i=0;i<36;i++){
        addemoji(i,emojitext);
    }
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void emojipick::on_tableWidget_cellClicked(int row, int column)
{
    QLabel *resultlabel = (QLabel *)ui->tableWidget->cellWidget(row,column);
    resulttext = resultlabel->text();
    emit back();
    this->hide();
}
QString emojipick::getemoji(QString resultext){
    qDebug() << resultext;
    return resultext;
}
