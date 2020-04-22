#ifndef EDITUSER_H
#define EDITUSER_H

#include <QWidget>

namespace Ui {
class EditUser;
}

class EditUser : public QWidget
{
    Q_OBJECT

public:
    explicit EditUser(QWidget *parent = nullptr);
    ~EditUser();

private:
    Ui::EditUser *ui;
};

#endif // EDITUSER_H
