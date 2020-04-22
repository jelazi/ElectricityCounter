include "edituser.h"
#include "ui_edituser.h"

EditUser::EditUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditUser)
{
    ui->setupUi(this);
}

EditUser::~EditUser()
{
    delete ui;
}
