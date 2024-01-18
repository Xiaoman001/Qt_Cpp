#ifndef MESSAGEOBJ_H
#define MESSAGEOBJ_H

#include <QWidget>

namespace Ui {
class messageObj;
}

class messageObj : public QWidget
{
    Q_OBJECT

public:
    explicit messageObj(QString  photoPath,
                        QString  name,
                        QString  hua,
                        QWidget *parent = nullptr);
    ~messageObj();

private:
    Ui::messageObj *ui;
};

#endif // MESSAGEOBJ_H
