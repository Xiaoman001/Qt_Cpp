#ifndef EMOJIPICK_H
#define EMOJIPICK_H

#include <QWidget>
#include <QTableWidget>
#include <QChar>
#include <QLabel>
namespace Ui {
class emojipick;
}

class emojipick : public QWidget
{
    Q_OBJECT

public:
    explicit emojipick(QWidget *parent = 0);
    ~emojipick();
    void initemoji();
    void addemoji(int i,char32_t[]);
    QString getemoji(QString);
    QString resulttext;
signals:
  void back();

private slots:
    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::emojipick *ui;
    int emojisize;

};

#endif // EMOJIPICK_H
