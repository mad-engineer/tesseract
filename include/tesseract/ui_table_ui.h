/********************************************************************************
** Form generated from reading UI file 'table_ui.ui'
**
** Created: Mon 10. Oct 18:13:35 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLE_UI_H
#define UI_TABLE_UI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TableForm
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QPushButton *reloadButton;
    QLabel *label;
    QSpinBox *cols_spinbox;
    QLabel *label_2;
    QSpinBox *rows_spinbox;
    QPushButton *changeOrderButton;
    QTableView *table_widget;
    QHBoxLayout *hboxLayout1;
    QWidget *spinbox_widget;

    void setupUi(QWidget *TableForm)
    {
        if (TableForm->objectName().isEmpty())
            TableForm->setObjectName(QString::fromUtf8("TableForm"));
        TableForm->resize(495, 297);
        const QIcon icon = QIcon(QString::fromUtf8("images/table.png"));
        TableForm->setWindowIcon(icon);
        vboxLayout = new QVBoxLayout(TableForm);
        vboxLayout->setSpacing(0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        reloadButton = new QPushButton(TableForm);
        reloadButton->setObjectName(QString::fromUtf8("reloadButton"));
        const QIcon icon1 = QIcon(QString::fromUtf8("images/reload.png"));
        reloadButton->setIcon(icon1);
        reloadButton->setIconSize(QSize(22, 22));

        hboxLayout->addWidget(reloadButton);

        label = new QLabel(TableForm);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout->addWidget(label);

        cols_spinbox = new QSpinBox(TableForm);
        cols_spinbox->setObjectName(QString::fromUtf8("cols_spinbox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cols_spinbox->sizePolicy().hasHeightForWidth());
        cols_spinbox->setSizePolicy(sizePolicy);
        cols_spinbox->setMinimum(1);
        cols_spinbox->setMaximum(1000000);

        hboxLayout->addWidget(cols_spinbox);

        label_2 = new QLabel(TableForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        hboxLayout->addWidget(label_2);

        rows_spinbox = new QSpinBox(TableForm);
        rows_spinbox->setObjectName(QString::fromUtf8("rows_spinbox"));
        sizePolicy.setHeightForWidth(rows_spinbox->sizePolicy().hasHeightForWidth());
        rows_spinbox->setSizePolicy(sizePolicy);
        rows_spinbox->setMinimum(1);
        rows_spinbox->setMaximum(1000000);

        hboxLayout->addWidget(rows_spinbox);

        changeOrderButton = new QPushButton(TableForm);
        changeOrderButton->setObjectName(QString::fromUtf8("changeOrderButton"));

        hboxLayout->addWidget(changeOrderButton);


        vboxLayout->addLayout(hboxLayout);

        table_widget = new QTableView(TableForm);
        table_widget->setObjectName(QString::fromUtf8("table_widget"));

        vboxLayout->addWidget(table_widget);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spinbox_widget = new QWidget(TableForm);
        spinbox_widget->setObjectName(QString::fromUtf8("spinbox_widget"));

        hboxLayout1->addWidget(spinbox_widget);


        vboxLayout->addLayout(hboxLayout1);


        retranslateUi(TableForm);

        QMetaObject::connectSlotsByName(TableForm);
    } // setupUi

    void retranslateUi(QWidget *TableForm)
    {
        TableForm->setWindowTitle(QApplication::translate("TableForm", "Table", 0, QApplication::UnicodeUTF8));
        reloadButton->setText(QString());
        label->setText(QApplication::translate("TableForm", "Cols", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TableForm", "Rows", 0, QApplication::UnicodeUTF8));
        changeOrderButton->setText(QApplication::translate("TableForm", "Change Order", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TableForm: public Ui_TableForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLE_UI_H
