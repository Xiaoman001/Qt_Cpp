#include "widget.h"

#include <QApplication>
#include "voicereceiver.h"
#include "voicesender.h"
#include "igtools.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Widget w;
  w.show();
  return a.exec();
}
