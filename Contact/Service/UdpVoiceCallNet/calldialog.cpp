#include "calldialog.h"
#include "ui_calldialog.h"
#include <QColor>
#include <QPalette>

CallDialog::CallDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CallDialog)
{
  ui->setupUi(this);

  // connect
  connect(ui->cancelBtn, &QPushButton::clicked,
          this, &CallDialog::signalCancelCall);
  connect(this,          &CallDialog::signalCancelCall,
          this, &QDialog::deleteLater);

  this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
  QPalette pal{ this->palette() };
  pal.setColor(QPalette::Background, QColor(255, 255, 255));

  DataBase.connData();

  this->setPalette(pal);
}

CallDialog::~CallDialog()
{
  delete ui;
}

void CallDialog::on_smallest_Button_clicked()
{
  this->showMinimized();
}

void CallDialog::on_close_button_clicked()
{
  this->close();
}

void CallDialog::mousePressEvent(QMouseEvent *event)
{
  m_isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
  m_last            = event->globalPos();
}

void CallDialog::mouseMoveEvent(QMouseEvent *event)
{
  if (m_isPressedWidget)
  {
    int dx = event->globalX() - m_last.x();
    int dy = event->globalY() - m_last.y();
    m_last = event->globalPos();
    move(x() + dx, y() + dy);
  }
}

void CallDialog::mouseReleaseEvent(QMouseEvent *event)
{
  int dx = event->globalX() - m_last.x();
  int dy = event->globalY() - m_last.y();
  move(x() + dx, y() + dy);

  //  should_move     = false;
  m_isPressedWidget = false; // 鼠标松开时，置为false
}

void CallDialog::setNickname(const QString& nickname)
{
  ui->nicknameLabel->setText(nickname);
}
