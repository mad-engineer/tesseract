/********************************************************************************
** Form generated from reading UI file 'newprojectdialog.ui'
**
** Created: Mon 10. Oct 18:13:35 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJECTDIALOG_H
#define UI_NEWPROJECTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewProjectDialog
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QLineEdit *name_lineEdit;
    QLabel *label_2;
    QTextEdit *description_textEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewProjectDialog)
    {
        if (NewProjectDialog->objectName().isEmpty())
            NewProjectDialog->setObjectName(QString::fromUtf8("NewProjectDialog"));
        NewProjectDialog->resize(400, 300);
        vboxLayout = new QVBoxLayout(NewProjectDialog);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        label = new QLabel(NewProjectDialog);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout->addWidget(label);

        name_lineEdit = new QLineEdit(NewProjectDialog);
        name_lineEdit->setObjectName(QString::fromUtf8("name_lineEdit"));

        hboxLayout->addWidget(name_lineEdit);


        vboxLayout->addLayout(hboxLayout);

        label_2 = new QLabel(NewProjectDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        vboxLayout->addWidget(label_2);

        description_textEdit = new QTextEdit(NewProjectDialog);
        description_textEdit->setObjectName(QString::fromUtf8("description_textEdit"));
        description_textEdit->setAcceptRichText(false);

        vboxLayout->addWidget(description_textEdit);

        buttonBox = new QDialogButtonBox(NewProjectDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(NewProjectDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewProjectDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewProjectDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewProjectDialog);
    } // setupUi

    void retranslateUi(QDialog *NewProjectDialog)
    {
        NewProjectDialog->setWindowTitle(QApplication::translate("NewProjectDialog", "New Project", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewProjectDialog", "Name: ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewProjectDialog", "Description:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewProjectDialog: public Ui_NewProjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJECTDIALOG_H
