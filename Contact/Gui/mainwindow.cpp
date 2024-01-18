#include "Gui/mainwindow.h"
#include "ui_mainwindow.h"

#if _MSC_VER >= 1600
# pragma execution_character_set("utf-8")
#endif // if _MSC_VER >= 1600

MainWindow::MainWindow(QString  account,
                       QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  myAccount = account;

  myuesercenter = new usercenter(this);
  myuesercenter->hide();
  isPressedWidget = false;

  // 单人聊天界面
  //  singalchat = new chatdemo(myAccount, this);
  //  ui->centerStackedWidget->addWidget(singalchat);

  //  邮件功能界面
  Frmemailtool = new  frmEmailTool(this);
  ui->centerStackedWidget->addWidget(Frmemailtool);

  //  通讯录功能界面
  contactDirectory = new  contactdirectory(myAccount, this);
  ui->centerStackedWidget->addWidget(contactDirectory);

  // 主页界面
  Home = new home();
  ui->centerStackedWidget->addWidget(Home);

  // 设置界面
  setting = new settings();
  ui->centerStackedWidget->addWidget(setting);

  // 压入vector
  isShowVector.push_back("Frmemailtool");
  isShowVector.push_back("singalchat");
  isShowVector.push_back("contactDirectory");
  isShowVector.push_back("Home");
  isShowVector.push_back("setting");
  setWindowFlags(Qt::FramelessWindowHint | windowFlags());
  ui->centerStackedWidget->setCurrentWidget(Home);
  nowShow["Home"] = 1;
  ui->home_Button->setStyleSheet("image: url(:/pic/home_press.png); border:0px solid blue");
  modifymode(0);
  DataBase.connData();
  if (DataBase.getIpAndPort(account).split('|')[0] != account) {
    qDebug() << "异地登录";
  }

  //  图标url
  QString photos = DataBase.getPhotoUrlByAccount(myAccount);
  ui->photo->setStyleSheet("image: url(" + photos + ");background-color: rgb(255, 255, 255);border-radius:7px;");

  connect(setting, SIGNAL(sendMode(int)), this, SLOT(modifymode(int)));
}

MainWindow::~MainWindow() {}

void MainWindow::on_chat_Button_clicked()
{
  if (nowShow["contactDirectory"] == 1) contactDirectory->hide();
  if (nowShow["Frmemailtool"] == 1) Frmemailtool->hide();
  if (nowShow["Home"] == 1) Home->hide();
  if (nowShow["setting"] == 1) setting->hide();
  ui->centerStackedWidget->setCurrentWidget(singalchat);
  nowShow["singalchat"] = 1;
  ui->chat_Button->setStyleSheet("image: url(:/pic/chat_press.png); border:0px solid blue");
  ui->book_Button->setStyleSheet("image: url(:/pic/book.png); border:0px solid blue");
  ui->home_Button->setStyleSheet("image: url(:/pic/home.png); border:0px solid blue");
  ui->settings_Button->setStyleSheet("image: url(:/pic/settings.png); border:0px solid blue");
  ui->add_Button->setStyleSheet("image: url(:/pic/add_friend.png); border:0px solid blue");
  ui->email_Button->setStyleSheet("image: url(:/pic/email.png); border:0px solid blue");
}

void MainWindow::on_smallest_Button_clicked()
{
  this->showMinimized();
}

void MainWindow::on_biggest_Button_clicked()
{
  this->showFullScreen();
}

void MainWindow::on_close_button_clicked()
{
  this->close();
}

void MainWindow::on_book_Button_clicked()
{
  if (nowShow["contactDirectory"] == 1) contactDirectory->hide();
  if (nowShow["Frmemailtool"] == 1) Frmemailtool->hide();
  if (nowShow["singalchat"] == 1) singalchat->hide();
  if (nowShow["Home"] == 1) Home->hide();
  if (nowShow["setting"] == 1) setting->hide();
  ui->centerStackedWidget->setCurrentWidget(contactDirectory);
  nowShow["contactDirectory"] = 1;
  ui->book_Button->setStyleSheet("image: url(:/pic/people_press.png); border:0px solid blue");
  ui->chat_Button->setStyleSheet("image: url(:/pic/chat.png); border:0px solid blue");
  ui->home_Button->setStyleSheet("image: url(:/pic/home.png); border:0px solid blue");
  ui->settings_Button->setStyleSheet("image: url(:/pic/settings.png); border:0px solid blue");
  ui->add_Button->setStyleSheet("image: url(:/pic/add_friend.png); border:0px solid blue");
  ui->email_Button->setStyleSheet("image: url(:/pic/email.png); border:0px solid blue");
}

void MainWindow::on_home_Button_clicked()
{
  if (nowShow["contactDirectory"] == 1) contactDirectory->hide();
  if (nowShow["Frmemailtool"] == 1) Frmemailtool->hide();
  if (nowShow["singalchat"] == 1) singalchat->hide();
  if (nowShow["setting"] == 1) setting->hide();
  ui->centerStackedWidget->setCurrentWidget(Home);
  nowShow["Home"] = 1;
  ui->home_Button->setStyleSheet("image: url(:/pic/home_press.png); border:0px solid blue");
  ui->chat_Button->setStyleSheet("image: url(:/pic/chat.png); border:0px solid blue");
  ui->book_Button->setStyleSheet("image: url(:/pic/book.png); border:0px solid blue");
  ui->settings_Button->setStyleSheet("image: url(:/pic/settings.png); border:0px solid blue");
  ui->add_Button->setStyleSheet("image: url(:/pic/add_friend.png); border:0px solid blue");
  ui->email_Button->setStyleSheet("image: url(:/pic/email.png); border:0px solid blue");
}

void MainWindow::on_email_Button_clicked()
{
  if (nowShow["contactDirectory"] == 1) contactDirectory->hide();
  if (nowShow["Frmemailtool"] == 1) Frmemailtool->hide();
  if (nowShow["Home"] == 1) Home->hide();
  if (nowShow["setting"] == 1) setting->hide();
  ui->centerStackedWidget->setCurrentWidget(Frmemailtool);
  nowShow["Frmemailtool"] = 1;
  ui->home_Button->setStyleSheet("image: url(:/pic/home.png); border:0px solid blue");
  ui->chat_Button->setStyleSheet("image: url(:/pic/chat.png); border:0px solid blue");
  ui->book_Button->setStyleSheet("image: url(:/pic/book.png); border:0px solid blue");
  ui->settings_Button->setStyleSheet("image: url(:/pic/settings.png); border:0px solid blue");
  ui->add_Button->setStyleSheet("image: url(:/pic/add_friend.png); border:0px solid blue");
  ui->email_Button->setStyleSheet("image: url(:/pic/email_press.png); border:0px solid blue");
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
  isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
  last            = event->globalPos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
  if (isPressedWidget)
  {
    qDebug() << "isPressedWidget:" << isPressedWidget;
    int dx = event->globalX() - last.x();
    int dy = event->globalY() - last.y();
    last = event->globalPos();
    move(x() + dx, y() + dy);
  }

  //  if (should_move == true) {
  //    int dx = event->globalX() - last.x();
  //    int dy = event->globalY() - last.y();
  //    last = event->globalPos();

  //    //      move(x() - dx, y() - dy);
  //    move(0, 0);
  //  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
  int dx = event->globalX() - last.x();
  int dy = event->globalY() - last.y();

  move(x() + dx, y() + dy);

  //  should_move     = false;
  isPressedWidget = false; // 鼠标松开时，置为false
}

void MainWindow::on_add_Button_clicked()
{
  //  加好友界面
  query = new  Query(myAccount);
  query->show();
  ui->home_Button->setStyleSheet("image: url(:/pic/home.png); border:0px solid blue");
  ui->chat_Button->setStyleSheet("image: url(:/pic/chat.png); border:0px solid blue");
  ui->book_Button->setStyleSheet("image: url(:/pic/book.png); border:0px solid blue");
  ui->settings_Button->setStyleSheet("image: url(:/pic/settings.png); border:0px solid blue");
  ui->add_Button->setStyleSheet("image: url(:/pic/add_friend_press.png); border:0px solid blue");
  ui->email_Button->setStyleSheet("image: url(:/pic/email.png); border:0px solid blue");
}

void MainWindow::on_photo_clicked()
{
  myuesercenter->move(2, 70);
  if (myuesercenter->isHidden()) {
    myuesercenter->show();
  } else {
    myuesercenter->hide();
  }
}

void MainWindow::on_settings_Button_clicked()
{
  if (nowShow["contactDirectory"] == 1) contactDirectory->hide();
  if (nowShow["Frmemailtool"] == 1) Frmemailtool->hide();
  if (nowShow["Home"] == 1) Home->hide();
  if (nowShow["singalchat"] == 1) singalchat->hide();
  ui->centerStackedWidget->setCurrentWidget(setting);
  nowShow["setting"] = 1;
  ui->settings_Button->setStyleSheet("image: url(:/pic/settings_press.png); border:0px solid blue");
  ui->chat_Button->setStyleSheet("image: url(:/pic/chat.png); border:0px solid blue");
  ui->book_Button->setStyleSheet("image: url(:/pic/book.png); border:0px solid blue");
  ui->home_Button->setStyleSheet("image: url(:/pic/home.png); border:0px solid blue");
  ui->add_Button->setStyleSheet("image: url(:/pic/add_friend.png); border:0px solid blue");
  ui->email_Button->setStyleSheet("image: url(:/pic/email.png); border:0px solid blue");
}

void MainWindow::modifymode(int mode)
{
  qDebug() << "mode" << mode;
  if (mode == 1) {
    ui->widget->setStyleSheet("background:rgb(0,0,0)");
    ui->settings_Button->setStyleSheet("image: url(:/pic/settings_press.png); border:0px solid blue");
    ui->chat_Button->setStyleSheet("image: url(:/pic/chat_light.png); border:0px solid blue");
    ui->book_Button->setStyleSheet("image: url(:/pic/book_light.png); border:0px solid blue");
    ui->home_Button->setStyleSheet("image: url(:/pic/home_light.png); border:0px solid blue");
    ui->add_Button->setStyleSheet("image: url(:/pic/add_friend_light.png); border:0px solid blue");
    ui->email_Button->setStyleSheet("image: url(:/pic/email_light.png); border:0px solid blue");
  }
  else if (mode == 0) {
    ui->widget->setStyleSheet("background:rgb(255,255,255)");
    if (nowShow["Home"] == 1) {
      ui->chat_Button->setStyleSheet("image: url(:/pic/chat.png); border:0px solid blue");
      ui->book_Button->setStyleSheet("image: url(:/pic/book.png); border:0px solid blue");
      ui->home_Button->setStyleSheet("image: url(:/pic/home_press.png); border:0px solid blue");
      ui->add_Button->setStyleSheet("image: url(:/pic/add_friend.png); border:0px solid blue");
      ui->email_Button->setStyleSheet("image: url(:/pic/email.png); border:0px solid blue");
      ui->settings_Button->setStyleSheet("image: url(:/pic/settings.png); border:0px solid blue");
    }
    else {
      ui->settings_Button->setStyleSheet("image: url(:/pic/settings_press.png); border:0px solid blue");
      ui->chat_Button->setStyleSheet("image: url(:/pic/chat.png); border:0px solid blue");
      ui->book_Button->setStyleSheet("image: url(:/pic/book.png); border:0px solid blue");
      ui->home_Button->setStyleSheet("image: url(:/pic/home.png); border:0px solid blue");
      ui->add_Button->setStyleSheet("image: url(:/pic/add_friend.png); border:0px solid blue");
      ui->email_Button->setStyleSheet("image: url(:/pic/email.png); border:0px solid blue");
    }
  }
}
