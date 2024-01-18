#include "Gui/mainwindow.h"
#include <QApplication>
#include "Gui/login.h"
#include "Service/globalobserver.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Login n;
  n.show();
  return a.exec();
}
