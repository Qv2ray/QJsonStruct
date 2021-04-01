#include "testform.hpp"

#include "header.hpp"

#include <QMessageBox>

TestForm::TestForm(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    myStruct f = object;
    QJS_RWBINDING(object.child(), childString, lineEdit, text, &QLineEdit::textChanged);
    QJS_RWBINDING(object, string, lineEdit, text, &QLineEdit::textChanged);
    QJS_RBINDING(object.child(), childString, label, text);
}

void TestForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange: retranslateUi(this); break;
        default: break;
    }
}

void TestForm::on_pushButton_clicked()
{
    QMessageBox::information(this, "Values", "UI: " + lineEdit->text() + "\n" + "Object: " + object.pstring);
}

void TestForm::on_pushButton_2_clicked()
{
    object.set_string("????");
    object.child().set_childString("val");
}
