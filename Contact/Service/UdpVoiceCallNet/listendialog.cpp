#include "listendialog.h"
#include "ui_listendialog.h"

ListenDialog::ListenDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ListenDialog)
{
  ui->setupUi(this);
  connect(ui->hangUpBtn, &QPushButton::clicked,
          this, &ListenDialog::hangUpSelfSignal);
  connect(this,          &ListenDialog::hangUpSelfSignal,
          this, &QDialog::deleteLater);

  // 自定义窗口
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
  QPalette pal{ this->palette() };
  pal.setColor(QPalette::Background, QColor(255, 255, 255));
  this->setPalette(pal);
  this->setStyleSheet(
    ".QPushButton{\
      background-color: rgb(105, 104, 253);\
      color: rgb(255, 255, 255);\
      border-radius: 10px;\
      }\
      .QPushButton:hover{\
      background-color: rgb(91, 90, 219);\
      color: rgb(255, 255, 255);\
      border-radius: 10px;\
      \
      }\
      .QPushButton:pressed{\
      background-color: rgb(91, 90, 219);\
      color: rgb(255, 255, 255);\
      border-radius: 10px;\
      padding-left:2px;\
      padding-top:2px;\
      }");
}

ListenDialog::~ListenDialog()
{
  delete ui;
}

void ListenDialog::on_smallest_Button_clicked()
{
  this->showMinimized();
}

void ListenDialog::on_close_button_clicked()
{
  this->close();
}

void ListenDialog::mousePressEvent(QMouseEvent *event)
{
  m_isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
  m_last            = event->globalPos();
}

void ListenDialog::mouseMoveEvent(QMouseEvent *event)
{
  if (m_isPressedWidget)
  {
    int dx = event->globalX() - m_last.x();
    int dy = event->globalY() - m_last.y();
    m_last = event->globalPos();
    move(x() + dx, y() + dy);
  }
}

void ListenDialog::mouseReleaseEvent(QMouseEvent *event)
{
  int dx = event->globalX() - m_last.x();
  int dy = event->globalY() - m_last.y();
  move(x() + dx, y() + dy);

  //  should_move     = false;
  m_isPressedWidget = false; // 鼠标松开时，置为false
}

void ListenDialog::setNickname(const QString &nickname)
{
  ui->nicknameLabel->setText(nickname);
}
