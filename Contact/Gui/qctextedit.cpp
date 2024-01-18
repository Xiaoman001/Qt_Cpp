#include "qctextedit.h"
#include <QTextEdit>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QMimeData>
#include <QFileInfo>
#include <QImageReader>
#include <QTextCursor>
#include <QtDebug>
#include "ui_qctextedit.h"
QcTextEdit::QcTextEdit(QWidget *parent) : QTextEdit(parent)
  , ui(new Ui::QcTextEdit)
{
  ui->setupUi(this);
}

bool QcTextEdit::canInsertFromMimeData(const QMimeData *source) const
{
  return source->hasImage() || source->hasUrls() ||
         QTextEdit::canInsertFromMimeData(source);
}

void QcTextEdit::insertFromMimeData(const QMimeData *source)
{
  if (source->hasImage()) {
    static int i = 1;
    QUrl url(QString("dropped_image_%1").arg(i++));
    qDebug() << "URL!!!!!" << url;
    qDebug() << "URL!!!!!" << url;
    dropImage(url, qvariant_cast<QImage>(source->imageData()));
  }
  else if (source->hasUrls()) {
    foreach(QUrl url, source->urls()) {
      QFileInfo info(url.toLocalFile());
      if (QImageReader::supportedImageFormats().contains(info.suffix().toLower().toLatin1())) dropImage(url,
                                                                                                        QImage(info.
                                                                                                               filePath()));
      else dropTextFile(url);
    }
  }
  else {
    QTextEdit::insertFromMimeData(source);
  }
}

void QcTextEdit::dropImage(const QUrl& url, const QImage& image)
{
  if (!image.isNull()) {
    image.save("C:/Users/Dell/Desktop/Contact/Gui/photos/test.jpg", "JPG", 100);
    qDebug() << "URL2222!!!!!" << url;
    document()->addResource(QTextDocument::ImageResource, url, image);
    textCursor().insertImage(url.toString());
  }
}

void QcTextEdit::dropTextFile(const QUrl& url)
{
  qDebug() << "URL!!!!!" << url;
  QFile file(url.toLocalFile());
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) textCursor().insertText(file.readAll());
}
