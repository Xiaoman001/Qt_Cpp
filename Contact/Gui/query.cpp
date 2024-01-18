#include "Gui/query.h"
#include "ui_query.h"
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QBitmap>
#include "Gui/addfriend.h"
#if _MSC_VER >= 1600
# pragma execution_character_set("utf-8")
#endif // if _MSC_VER >= 1600

Query::Query(QString account, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Query)
{
  ui->setupUi(this);
  this->account = account;
  setWindowFlags(Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground);
  ui->pushButton_3->setIcon(QIcon(":/lib/add.png"));

  QAction *searchAction = new QAction(ui->lineEdit);
  searchAction->setIcon(QIcon(":/lib/find.png"));
  ui->lineEdit->addAction(searchAction, QLineEdit::LeadingPosition); // 添加搜索图标

  ui->pushButton_3->hide();
  on_addFriend_clicked();
}

Query::~Query()
{
  delete ui;
}

void Query::paintEvent(QPaintEvent *e)
{
  Q_UNUSED(e)
  QPainter painter(this);
  QPixmap  pixmap(":/lib/background.png"); // 做好的图
  qDrawBorderPixmap(&painter, this->rect(), QMargins(0, 0, 0, 0), pixmap);
  QRect rect(this->rect().x() + 8, this->rect().y() + 8, this->rect().width() - 16, this->rect().height() - 16);
  painter.fillRect(rect, QColor(255, 255, 255));
}

void Query::mousePressEvent(QMouseEvent *event)
{
  isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
  last            = event->globalPos();
}

void Query::mouseMoveEvent(QMouseEvent *event)
{
  if (isPressedWidget)
  {
    int dx = event->globalX() - last.x();
    int dy = event->globalY() - last.y();
    last = event->globalPos();
    move(x() + dx, y() + dy);
  }
}

void Query::mouseReleaseEvent(QMouseEvent *event)
{
  int dx = event->globalX() - last.x();
  int dy = event->globalY() - last.y();
  move(x() + dx, y() + dy);
  isPressedWidget = false; // 鼠标松开时，置为false
}

void Query::on_pushButton_clicked()
{
  QString otheraccount = ui->lineEdit->text();
  ui->pushButton_3->show();

  // this->account = account;
  // qDebug()<<"输入的账号是："<<ui->lineEdit->text();
  // 链接数据库
  this->sqconn.connData();

  // 获取头像
  this->icon = sqconn.getPixmapIcon(otheraccount);
  this->icon = this->icon.scaled(QSize(this->icon.width(), this->icon.height()), Qt::IgnoreAspectRatio);
  this->icon = Globalobserver::PixmapToRound(this->icon, this->icon.width() / 2);
  ui->pushButton_4->setIcon(QIcon(this->icon));

  // 获取昵称
  ui->label_2->setText(sqconn.getOtherAccountName(otheraccount));
  ui->label_3->setText(sqconn.getOtherAccountAge(otheraccount) + "岁");
}

void Query::on_pushButton_3_clicked()
{
  // 头像, 搜索账号,名字，本身账号，性别，年龄职业
  // this->account 被搜索账号
  Addfriend *a = new Addfriend(this->icon,
                               ui->lineEdit->text(),
                               ui->label_2->text(),
                               this->account,
                               sqconn.getOtherAccountSex(this->account),
                               ui->label_3->text(),
                               sqconn.getOtherAccountProfession(this->account));
  connect(Globalobserver::getAddfriendp(), SIGNAL(sendaddinfo(QString)), Globalobserver::getMainwindowp(),
          SLOT(MainSendAddData(QString)));
  a->show();
}

void Query::on_toolButton_4_clicked()
{
  this->hide();
}

void Query::MainSendAddData(QString)
{
  qDebug() << "查找窗口接收到信号";
}

void Query::on_addFriend_clicked()
{
  addType = "+好友";
  ui->addFriend->setStyleSheet(
    "border-width:5px;background-color: rgb(191, 191, 249);\
                                border-radius:5px;min-width:100px;min-height:50px;");
  ui->addGroup->setStyleSheet(
    "border-width:5px;\
                                background-color: rgb(240, 239, 253);\
                                border-radius:5px;\
                                min-width:100px;\
                                min-height:50px;\
                                color: rgb(180, 177, 184);");
  ui->label_4->setText("你可能认识的人：");
  ui->lineEdit->setPlaceholderText("请输入用户账号进行查询");

  ui->pushButton_3->setText("好友");
}

void Query::on_addGroup_clicked()
{
  addType = "+群组";
  ui->addGroup->setStyleSheet(
    "border-width:5px;background-color: rgb(191, 191, 249);\
                                border-radius:5px;min-width:100px;min-height:50px;");
  ui->addFriend->setStyleSheet(
    "border-width:5px;\
                                background-color: rgb(240, 239, 253);\
                                border-radius:5px;\
                                min-width:100px;\
                                min-height:50px;\
                                color: rgb(180, 177, 184);");
  ui->label_4->setText("你可能感兴趣的群组：");
  ui->lineEdit->setPlaceholderText("请输入群组账号进行查询");
  ui->pushButton_3->setText("+群组");
}
