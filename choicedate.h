#ifndef CHOICEDATE_H
#define CHOICEDATE_H

#include <QDialog>
#include "structures.h"

namespace Ui {
  class choiceDate;
}

class choiceDate : public QDialog {
    Q_OBJECT

  public:
    explicit choiceDate(QWidget *parent = nullptr);
    ~choiceDate();
    void setParentChoiceDate (TypeParentChoiceDate type);

  private slots:
    void on_cancelBtn_clicked();

    void on_okBtn_clicked();

    void on_month_currentIndexChanged(int index);

    void on_year_currentIndexChanged(int index);
    void slotChangeData();


signals:
    void signalChangeData();

  private:
    Ui::choiceDate *ui;
    void fillYearsList ();


};

#endif // CHOICEDATE_H
