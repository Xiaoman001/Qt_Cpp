#ifndef QCTEXTEDIT_H
#define QCTEXTEDIT_H
#include <QTextEdit>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QMimeData>
#include <QWidget>

namespace Ui {
class QcTextEdit;
}
class QcTextEdit : public QTextEdit {
  Q_OBJECT

public:

  QcTextEdit(QWidget *parent = nullptr);

  bool canInsertFromMimeData(const QMimeData *source) const;
  void insertFromMimeData(const QMimeData *source);
  void dropImage(const QUrl  & url,
                 const QImage& image);
  void dropTextFile(const QUrl& url);

private:

  Ui::QcTextEdit *ui;

signals:
};

#endif // QCTEXTEDIT_H
