/********************************************************************************
** Form generated from reading UI file 'export_to_dialog.ui'
**
** Created: Mon 10. Oct 18:13:36 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORT_TO_DIALOG_H
#define UI_EXPORT_TO_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ExportToDialog
{
public:
    QVBoxLayout *vboxLayout;
    QLabel *label;
    QListWidget *formats_listWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *ExportToDialog)
    {
        if (ExportToDialog->objectName().isEmpty())
            ExportToDialog->setObjectName(QString::fromUtf8("ExportToDialog"));
        ExportToDialog->resize(289, 300);
        vboxLayout = new QVBoxLayout(ExportToDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        label = new QLabel(ExportToDialog);
        label->setObjectName(QString::fromUtf8("label"));

        vboxLayout->addWidget(label);

        formats_listWidget = new QListWidget(ExportToDialog);
        formats_listWidget->setObjectName(QString::fromUtf8("formats_listWidget"));

        vboxLayout->addWidget(formats_listWidget);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(ExportToDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(ExportToDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        vboxLayout->addLayout(hboxLayout);


        retranslateUi(ExportToDialog);
        QObject::connect(okButton, SIGNAL(clicked()), ExportToDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), ExportToDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ExportToDialog);
    } // setupUi

    void retranslateUi(QDialog *ExportToDialog)
    {
        ExportToDialog->setWindowTitle(QApplication::translate("ExportToDialog", "Export to...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ExportToDialog", "Select format:", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("ExportToDialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("ExportToDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExportToDialog: public Ui_ExportToDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORT_TO_DIALOG_H
