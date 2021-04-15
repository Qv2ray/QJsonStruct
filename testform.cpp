#include "testform.hpp"

#include "header.hpp"

#include <QMessageBox>

TestForm::TestForm(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    QJS_RWBINDING(object.child->childString, lineEdit, "text", &QLineEdit::textChanged);
    QJS_RWBINDING(object.string, lineEdit, "text", &QLineEdit::textChanged);
    QJS_RBINDING(object.child->childString, label, "text");
    const auto t = object.staticMetaObject;
    t.property(1);
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
    QMessageBox::information(this, "Values", "UI: " + lineEdit->text() + "\n" + "Object: " + object.string);
}

void TestForm::on_pushButton_2_clicked()
{
    object.string = "????";
    object.child->childString = "val";
}
