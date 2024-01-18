#include "cluster.h"
#include "ui_cluster.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QStringList>
#include <QImage>
    #include <QDebug>
cluster::cluster(QString account, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::cluster)
{
  ui->setupUi(this);
  ui->label_14->setText(account);
  ui->label_13->setAlignment(Qt::AlignCenter);
  ui->label_14->setAlignment(Qt::AlignCenter);
  QGridLayout *gridlayout = new QGridLayout();
  ui->widget->setLayout(gridlayout);
  setWindowFlags(Qt::FramelessWindowHint | windowFlags());

  DataBase.connData();

  //  int role = clustersql.getUserRole(account);
  QStringList memberlist;
  memberlist = DataBase.getUserGroup(account);
  for (int i = 0; i < memberlist.size(); i++) {
    QString namestr    = DataBase.getNameByAccount(memberlist[i]);
    QLabel *namelabel  = new QLabel();
    QLabel *pictulabel = new QLabel();
    QPixmap pictu(DataBase.getPhotoUrlByAccount(memberlist[i]));
    namelabel->setText(namestr);
    pictu = pictu.scaled(40, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pictulabel->setPixmap(pictu);

    QString photos = DataBase.getPhotoUrlByAccount(account);
    ui->frame_2->setStyleSheet("border-image: url(" + photos + ");");

    // pictulabel->setScaledContents(true);
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setSpacing(0);
    hlayout->addWidget(pictulabel);
    hlayout->addWidget(namelabel, 0, Qt::AlignLeft);
    QLabel *templabel  = new QLabel();
    QLabel *emptylabel = new QLabel();
    emptylabel->setText("2022/03/23");
    templabel->setText(memberlist[i]);
    if (i == 0) {
      gridlayout->addLayout(hlayout, 0, 0, 1, 1);
      gridlayout->addWidget(templabel,  0, 1, 1, 1);
      gridlayout->addWidget(emptylabel, 0, 2, 1, 1);
    } else if (i == 1) {
      gridlayout->addLayout(hlayout, 1, 0, 1, 1);
      gridlayout->addWidget(templabel,  1, 1, 1, 1);
      gridlayout->addWidget(emptylabel, 1, 2, 1, 1);
    } else if (i == 2) {
      gridlayout->addLayout(hlayout, 2, 0, 1, 1);
      gridlayout->addWidget(templabel,  2, 1, 1, 1);
      gridlayout->addWidget(emptylabel, 2, 2, 1, 1);
    }
  }

  //  if (role > 2) {
  //    ui->pushButton_2->hide();
  //    ui->pushButton->hide();
  //  }
}

cluster::~cluster()
{
  delete ui;
}

void cluster::on_pushButton_clicked()
{
  //    clusterAddmember *newAddmember = new clusterAddmember(this);
  //    newAddmember->setWindowTitle(QString("newmember"));
  //    newAddmember->show();
}

void cluster::on_pushButton_3_clicked()
{
  this->close();
}
