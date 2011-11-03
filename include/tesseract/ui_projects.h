/********************************************************************************
** Form generated from reading UI file 'projects.ui'
**
** Created: Mon 10. Oct 18:13:35 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTS_H
#define UI_PROJECTS_H

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
#include <QtGui/QSplitter>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ui_Projects
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QWidget *menu_widget;
    QLabel *label;
    QSplitter *splitter;
    QListWidget *projects_listWidget;
    QTextEdit *description_textEdit;
    QHBoxLayout *hboxLayout1;
    QPushButton *open_pushButton;
    QPushButton *cancel_pushButton;

    void setupUi(QDialog *Ui_Projects)
    {
        if (Ui_Projects->objectName().isEmpty())
            Ui_Projects->setObjectName(QString::fromUtf8("Ui_Projects"));
        Ui_Projects->resize(468, 346);
        vboxLayout = new QVBoxLayout(Ui_Projects);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        menu_widget = new QWidget(Ui_Projects);
        menu_widget->setObjectName(QString::fromUtf8("menu_widget"));

        hboxLayout->addWidget(menu_widget);


        vboxLayout->addLayout(hboxLayout);

        label = new QLabel(Ui_Projects);
        label->setObjectName(QString::fromUtf8("label"));

        vboxLayout->addWidget(label);

        splitter = new QSplitter(Ui_Projects);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        projects_listWidget = new QListWidget(splitter);
        projects_listWidget->setObjectName(QString::fromUtf8("projects_listWidget"));
        splitter->addWidget(projects_listWidget);
        description_textEdit = new QTextEdit(splitter);
        description_textEdit->setObjectName(QString::fromUtf8("description_textEdit"));
        description_textEdit->setTabChangesFocus(true);
        description_textEdit->setUndoRedoEnabled(false);
        description_textEdit->setReadOnly(true);
        splitter->addWidget(description_textEdit);

        vboxLayout->addWidget(splitter);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        open_pushButton = new QPushButton(Ui_Projects);
        open_pushButton->setObjectName(QString::fromUtf8("open_pushButton"));

        hboxLayout1->addWidget(open_pushButton);

        cancel_pushButton = new QPushButton(Ui_Projects);
        cancel_pushButton->setObjectName(QString::fromUtf8("cancel_pushButton"));

        hboxLayout1->addWidget(cancel_pushButton);


        vboxLayout->addLayout(hboxLayout1);


        retranslateUi(Ui_Projects);
        QObject::connect(cancel_pushButton, SIGNAL(clicked()), Ui_Projects, SLOT(reject()));

        QMetaObject::connectSlotsByName(Ui_Projects);
    } // setupUi

    void retranslateUi(QDialog *Ui_Projects)
    {
        Ui_Projects->setWindowTitle(QApplication::translate("Ui_Projects", "Projects", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Ui_Projects", "Available Projects:", 0, QApplication::UnicodeUTF8));
        open_pushButton->setText(QApplication::translate("Ui_Projects", "Open", 0, QApplication::UnicodeUTF8));
        cancel_pushButton->setText(QApplication::translate("Ui_Projects", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Ui_Projects: public Ui_Ui_Projects {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTS_H
