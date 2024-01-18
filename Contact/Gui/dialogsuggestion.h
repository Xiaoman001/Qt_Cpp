#ifndef DIALOGSUGGESTION_H
#define DIALOGSUGGESTION_H

#include <QDialog>

namespace Ui {
class DialogSuggestion;
}

class DialogSuggestion : public QDialog {
  Q_OBJECT

public:

  explicit DialogSuggestion(QWidget *parent = nullptr);
  ~DialogSuggestion();

  void dialogDark();

  void dialogLight();

private slots:

  void on_submit1_clicked();

  void on_cancel1_clicked();

private:

  Ui::DialogSuggestion *ui;
};

#endif // DIALOGSUGGESTION_H
