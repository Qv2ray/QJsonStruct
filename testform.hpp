#pragma once

#include "header.hpp"
#include "ui_testform.h"

#include <QMutex>

class TestForm
    : public QWidget
    , private Ui::TestForm
{
    Q_OBJECT

  public:
    explicit TestForm(QWidget *parent = nullptr);

  protected:
    void changeEvent(QEvent *e);
    myStruct object;
  private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

#define prop_decl                                                                                                                                    \
  private:                                                                                                                                           \
    typedef QPropertyChangeHandler<std::function<void()>> PCH;                                                                                       \
    QMutex x;                                                                                                                                        \
    std::list<PCH> pch;

    prop_decl
};
