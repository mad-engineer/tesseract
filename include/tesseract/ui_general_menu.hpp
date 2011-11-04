/********************************************************************************
** Form generated from reading UI file 'general_menu.ui'
**
** Created: Mon 10. Oct 18:13:36 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERAL_MENU_H
#define UI_GENERAL_MENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GeneralMenu
{
public:
    QVBoxLayout *vboxLayout;
    QToolBox *toolBox;
    QWidget *terminal_page;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *font_text_label;
    QLabel *font_label;
    QPushButton *font_button;
    QHBoxLayout *hboxLayout1;
    QLabel *color_text_label;
    QPushButton *color_label;
    QPushButton *error_example_label;
    QPushButton *error_button;
    QPushButton *background_button;
    QPushButton *foreground_button;
    QHBoxLayout *hboxLayout2;
    QLabel *max_line_label;
    QLineEdit *max_line_num_lineEdit;
    QHBoxLayout *hboxLayout3;
    QLabel *max_col_label;
    QLineEdit *max_col_in_terminal_lineEdit;
    QCheckBox *show_ide_commands_checkBox;
    QSpacerItem *spacerItem;
    QWidget *command_list_page;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lines_in_history_lineEdit;
    QSpacerItem *verticalSpacer;
    QWidget *editor_page;
    QVBoxLayout *vboxLayout2;
    QCheckBox *use_external_editor;
    QHBoxLayout *hboxLayout4;
    QLabel *editor_label;
    QLineEdit *editor_lineEdit;
    QHBoxLayout *hboxLayout5;
    QSpacerItem *spacerItem1;
    QPushButton *editor_select_button;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout3;
    QGroupBox *groupBox_3;
    QVBoxLayout *vboxLayout4;
    QLabel *textEditFont_label;
    QHBoxLayout *hboxLayout6;
    QSpacerItem *spacerItem2;
    QPushButton *textEditFont_pushButton;
    QGroupBox *aautoindent_groupBox;
    QVBoxLayout *vboxLayout5;
    QRadioButton *no_autoindent_radioButton;
    QRadioButton *autoindent_radioButton;
    QRadioButton *autoindent_statements_radioButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *vboxLayout6;
    QCheckBox *syntaxHighlighting_checkBox;
    QCheckBox *bracketsMatch_checkBox;
    QCheckBox *autoCompletion_checkBox;
    QCheckBox *simple_rcs_checkBox;
    QSpacerItem *spacerItem3;
    QWidget *octave;
    QVBoxLayout *vboxLayout7;
    QHBoxLayout *hboxLayout7;
    QLabel *octave_path_label;
    QLineEdit *octave_path_lineEdit;
    QPushButton *octave_path_pushButton;
    QHBoxLayout *hboxLayout8;
    QHBoxLayout *hboxLayout9;
    QLabel *octaveArgs_lbl;
    QLineEdit *octaveArgs_lineEdit;
    QVBoxLayout *vboxLayout8;
    QLabel *octaveDir_label;
    QListWidget *octaveDir_list;
    QHBoxLayout *hboxLayout10;
    QPushButton *octaveDirAdd_button;
    QPushButton *octaveDirRem_button;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout;
    QCheckBox *easy_plot_checkBox;
    QLabel *label;
    QLineEdit *easy_plot_path_lineEdit;
    QPushButton *easy_plot_path_pushButton;
    QWidget *help_page;
    QVBoxLayout *vboxLayout9;
    QCheckBox *qtinfo_ok_checkBox;
    QHBoxLayout *hboxLayout11;
    QLabel *help_path_label;
    QLineEdit *help_path_lineEdit;
    QHBoxLayout *hboxLayout12;
    QSpacerItem *spacerItem4;
    QPushButton *help_path_select_pushButton;
    QSpacerItem *spacerItem5;
    QHBoxLayout *hboxLayout13;
    QSpacerItem *spacerItem6;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *GeneralMenu)
    {
        if (GeneralMenu->objectName().isEmpty())
            GeneralMenu->setObjectName(QString::fromUtf8("GeneralMenu"));
        GeneralMenu->resize(574, 550);
        QIcon icon;
        icon.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        GeneralMenu->setWindowIcon(icon);
        vboxLayout = new QVBoxLayout(GeneralMenu);
        vboxLayout->setSpacing(0);
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        toolBox = new QToolBox(GeneralMenu);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        terminal_page = new QWidget();
        terminal_page->setObjectName(QString::fromUtf8("terminal_page"));
        terminal_page->setGeometry(QRect(0, 0, 710, 168));
        vboxLayout1 = new QVBoxLayout(terminal_page);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        font_text_label = new QLabel(terminal_page);
        font_text_label->setObjectName(QString::fromUtf8("font_text_label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(font_text_label->sizePolicy().hasHeightForWidth());
        font_text_label->setSizePolicy(sizePolicy);

        hboxLayout->addWidget(font_text_label);

        font_label = new QLabel(terminal_page);
        font_label->setObjectName(QString::fromUtf8("font_label"));
        sizePolicy.setHeightForWidth(font_label->sizePolicy().hasHeightForWidth());
        font_label->setSizePolicy(sizePolicy);

        hboxLayout->addWidget(font_label);

        font_button = new QPushButton(terminal_page);
        font_button->setObjectName(QString::fromUtf8("font_button"));

        hboxLayout->addWidget(font_button);


        vboxLayout1->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        color_text_label = new QLabel(terminal_page);
        color_text_label->setObjectName(QString::fromUtf8("color_text_label"));

        hboxLayout1->addWidget(color_text_label);

        color_label = new QPushButton(terminal_page);
        color_label->setObjectName(QString::fromUtf8("color_label"));
        sizePolicy.setHeightForWidth(color_label->sizePolicy().hasHeightForWidth());
        color_label->setSizePolicy(sizePolicy);

        hboxLayout1->addWidget(color_label);

        error_example_label = new QPushButton(terminal_page);
        error_example_label->setObjectName(QString::fromUtf8("error_example_label"));

        hboxLayout1->addWidget(error_example_label);

        error_button = new QPushButton(terminal_page);
        error_button->setObjectName(QString::fromUtf8("error_button"));

        hboxLayout1->addWidget(error_button);

        background_button = new QPushButton(terminal_page);
        background_button->setObjectName(QString::fromUtf8("background_button"));

        hboxLayout1->addWidget(background_button);

        foreground_button = new QPushButton(terminal_page);
        foreground_button->setObjectName(QString::fromUtf8("foreground_button"));

        hboxLayout1->addWidget(foreground_button);


        vboxLayout1->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout2->setSpacing(6);
#endif
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        max_line_label = new QLabel(terminal_page);
        max_line_label->setObjectName(QString::fromUtf8("max_line_label"));

        hboxLayout2->addWidget(max_line_label);

        max_line_num_lineEdit = new QLineEdit(terminal_page);
        max_line_num_lineEdit->setObjectName(QString::fromUtf8("max_line_num_lineEdit"));

        hboxLayout2->addWidget(max_line_num_lineEdit);


        vboxLayout1->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout3->setSpacing(6);
#endif
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        max_col_label = new QLabel(terminal_page);
        max_col_label->setObjectName(QString::fromUtf8("max_col_label"));

        hboxLayout3->addWidget(max_col_label);

        max_col_in_terminal_lineEdit = new QLineEdit(terminal_page);
        max_col_in_terminal_lineEdit->setObjectName(QString::fromUtf8("max_col_in_terminal_lineEdit"));

        hboxLayout3->addWidget(max_col_in_terminal_lineEdit);


        vboxLayout1->addLayout(hboxLayout3);

        show_ide_commands_checkBox = new QCheckBox(terminal_page);
        show_ide_commands_checkBox->setObjectName(QString::fromUtf8("show_ide_commands_checkBox"));

        vboxLayout1->addWidget(show_ide_commands_checkBox);

        spacerItem = new QSpacerItem(692, 77, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem);

        toolBox->addItem(terminal_page, QString::fromUtf8("Terminal"));
        command_list_page = new QWidget();
        command_list_page->setObjectName(QString::fromUtf8("command_list_page"));
        command_list_page->setGeometry(QRect(0, 0, 206, 46));
        verticalLayout = new QVBoxLayout(command_list_page);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(command_list_page);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lines_in_history_lineEdit = new QLineEdit(command_list_page);
        lines_in_history_lineEdit->setObjectName(QString::fromUtf8("lines_in_history_lineEdit"));

        horizontalLayout->addWidget(lines_in_history_lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 355, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        toolBox->addItem(command_list_page, QString::fromUtf8("Command List"));
        editor_page = new QWidget();
        editor_page->setObjectName(QString::fromUtf8("editor_page"));
        editor_page->setGeometry(QRect(0, 0, 315, 488));
        vboxLayout2 = new QVBoxLayout(editor_page);
#ifndef Q_OS_MAC
        vboxLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout2->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        use_external_editor = new QCheckBox(editor_page);
        use_external_editor->setObjectName(QString::fromUtf8("use_external_editor"));

        vboxLayout2->addWidget(use_external_editor);

        hboxLayout4 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout4->setSpacing(6);
#endif
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        editor_label = new QLabel(editor_page);
        editor_label->setObjectName(QString::fromUtf8("editor_label"));

        hboxLayout4->addWidget(editor_label);

        editor_lineEdit = new QLineEdit(editor_page);
        editor_lineEdit->setObjectName(QString::fromUtf8("editor_lineEdit"));

        hboxLayout4->addWidget(editor_lineEdit);


        vboxLayout2->addLayout(hboxLayout4);

        hboxLayout5 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout5->setSpacing(6);
#endif
        hboxLayout5->setContentsMargins(0, 0, 0, 0);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout5->addItem(spacerItem1);

        editor_select_button = new QPushButton(editor_page);
        editor_select_button->setObjectName(QString::fromUtf8("editor_select_button"));

        hboxLayout5->addWidget(editor_select_button);


        vboxLayout2->addLayout(hboxLayout5);

        groupBox = new QGroupBox(editor_page);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        vboxLayout3 = new QVBoxLayout(groupBox);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        vboxLayout4 = new QVBoxLayout(groupBox_3);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        textEditFont_label = new QLabel(groupBox_3);
        textEditFont_label->setObjectName(QString::fromUtf8("textEditFont_label"));

        vboxLayout4->addWidget(textEditFont_label);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout6->addItem(spacerItem2);

        textEditFont_pushButton = new QPushButton(groupBox_3);
        textEditFont_pushButton->setObjectName(QString::fromUtf8("textEditFont_pushButton"));

        hboxLayout6->addWidget(textEditFont_pushButton);


        vboxLayout4->addLayout(hboxLayout6);


        vboxLayout3->addWidget(groupBox_3);

        aautoindent_groupBox = new QGroupBox(groupBox);
        aautoindent_groupBox->setObjectName(QString::fromUtf8("aautoindent_groupBox"));
        vboxLayout5 = new QVBoxLayout(aautoindent_groupBox);
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        no_autoindent_radioButton = new QRadioButton(aautoindent_groupBox);
        no_autoindent_radioButton->setObjectName(QString::fromUtf8("no_autoindent_radioButton"));

        vboxLayout5->addWidget(no_autoindent_radioButton);

        autoindent_radioButton = new QRadioButton(aautoindent_groupBox);
        autoindent_radioButton->setObjectName(QString::fromUtf8("autoindent_radioButton"));
        autoindent_radioButton->setChecked(true);

        vboxLayout5->addWidget(autoindent_radioButton);

        autoindent_statements_radioButton = new QRadioButton(aautoindent_groupBox);
        autoindent_statements_radioButton->setObjectName(QString::fromUtf8("autoindent_statements_radioButton"));

        vboxLayout5->addWidget(autoindent_statements_radioButton);


        vboxLayout3->addWidget(aautoindent_groupBox);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        vboxLayout6 = new QVBoxLayout(groupBox_2);
        vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
        syntaxHighlighting_checkBox = new QCheckBox(groupBox_2);
        syntaxHighlighting_checkBox->setObjectName(QString::fromUtf8("syntaxHighlighting_checkBox"));
        syntaxHighlighting_checkBox->setChecked(true);

        vboxLayout6->addWidget(syntaxHighlighting_checkBox);

        bracketsMatch_checkBox = new QCheckBox(groupBox_2);
        bracketsMatch_checkBox->setObjectName(QString::fromUtf8("bracketsMatch_checkBox"));
        bracketsMatch_checkBox->setChecked(true);

        vboxLayout6->addWidget(bracketsMatch_checkBox);

        autoCompletion_checkBox = new QCheckBox(groupBox_2);
        autoCompletion_checkBox->setObjectName(QString::fromUtf8("autoCompletion_checkBox"));
        autoCompletion_checkBox->setChecked(true);

        vboxLayout6->addWidget(autoCompletion_checkBox);

        simple_rcs_checkBox = new QCheckBox(groupBox_2);
        simple_rcs_checkBox->setObjectName(QString::fromUtf8("simple_rcs_checkBox"));
        simple_rcs_checkBox->setChecked(true);
        simple_rcs_checkBox->setTristate(false);

        vboxLayout6->addWidget(simple_rcs_checkBox);


        vboxLayout3->addWidget(groupBox_2);


        vboxLayout2->addWidget(groupBox);

        spacerItem3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout2->addItem(spacerItem3);

        toolBox->addItem(editor_page, QString::fromUtf8("Editor"));
        octave = new QWidget();
        octave->setObjectName(QString::fromUtf8("octave"));
        octave->setGeometry(QRect(0, 0, 556, 349));
        vboxLayout7 = new QVBoxLayout(octave);
#ifndef Q_OS_MAC
        vboxLayout7->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout7->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout7->setObjectName(QString::fromUtf8("vboxLayout7"));
        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        octave_path_label = new QLabel(octave);
        octave_path_label->setObjectName(QString::fromUtf8("octave_path_label"));

        hboxLayout7->addWidget(octave_path_label);

        octave_path_lineEdit = new QLineEdit(octave);
        octave_path_lineEdit->setObjectName(QString::fromUtf8("octave_path_lineEdit"));

        hboxLayout7->addWidget(octave_path_lineEdit);

        octave_path_pushButton = new QPushButton(octave);
        octave_path_pushButton->setObjectName(QString::fromUtf8("octave_path_pushButton"));

        hboxLayout7->addWidget(octave_path_pushButton);


        vboxLayout7->addLayout(hboxLayout7);

        hboxLayout8 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout8->setSpacing(6);
#endif
        hboxLayout8->setContentsMargins(0, 0, 0, 0);
        hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
        hboxLayout9 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout9->setSpacing(6);
#endif
        hboxLayout9->setContentsMargins(9, 9, 9, 9);
        hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
        octaveArgs_lbl = new QLabel(octave);
        octaveArgs_lbl->setObjectName(QString::fromUtf8("octaveArgs_lbl"));

        hboxLayout9->addWidget(octaveArgs_lbl);

        octaveArgs_lineEdit = new QLineEdit(octave);
        octaveArgs_lineEdit->setObjectName(QString::fromUtf8("octaveArgs_lineEdit"));

        hboxLayout9->addWidget(octaveArgs_lineEdit);


        hboxLayout8->addLayout(hboxLayout9);


        vboxLayout7->addLayout(hboxLayout8);

        vboxLayout8 = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout8->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout8->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout8->setObjectName(QString::fromUtf8("vboxLayout8"));
        octaveDir_label = new QLabel(octave);
        octaveDir_label->setObjectName(QString::fromUtf8("octaveDir_label"));

        vboxLayout8->addWidget(octaveDir_label);

        octaveDir_list = new QListWidget(octave);
        octaveDir_list->setObjectName(QString::fromUtf8("octaveDir_list"));

        vboxLayout8->addWidget(octaveDir_list);

        hboxLayout10 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout10->setSpacing(6);
#endif
        hboxLayout10->setContentsMargins(0, 0, 0, 0);
        hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
        octaveDirAdd_button = new QPushButton(octave);
        octaveDirAdd_button->setObjectName(QString::fromUtf8("octaveDirAdd_button"));

        hboxLayout10->addWidget(octaveDirAdd_button);

        octaveDirRem_button = new QPushButton(octave);
        octaveDirRem_button->setObjectName(QString::fromUtf8("octaveDirRem_button"));

        hboxLayout10->addWidget(octaveDirRem_button);


        vboxLayout8->addLayout(hboxLayout10);


        vboxLayout7->addLayout(vboxLayout8);

        groupBox_4 = new QGroupBox(octave);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout = new QGridLayout(groupBox_4);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        easy_plot_checkBox = new QCheckBox(groupBox_4);
        easy_plot_checkBox->setObjectName(QString::fromUtf8("easy_plot_checkBox"));

        gridLayout->addWidget(easy_plot_checkBox, 0, 0, 1, 1);

        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        easy_plot_path_lineEdit = new QLineEdit(groupBox_4);
        easy_plot_path_lineEdit->setObjectName(QString::fromUtf8("easy_plot_path_lineEdit"));

        gridLayout->addWidget(easy_plot_path_lineEdit, 1, 1, 1, 1);

        easy_plot_path_pushButton = new QPushButton(groupBox_4);
        easy_plot_path_pushButton->setObjectName(QString::fromUtf8("easy_plot_path_pushButton"));

        gridLayout->addWidget(easy_plot_path_pushButton, 1, 2, 1, 1);


        vboxLayout7->addWidget(groupBox_4);

        toolBox->addItem(octave, QString::fromUtf8("Octave"));
        help_page = new QWidget();
        help_page->setObjectName(QString::fromUtf8("help_page"));
        help_page->setGeometry(QRect(0, 0, 556, 349));
        vboxLayout9 = new QVBoxLayout(help_page);
#ifndef Q_OS_MAC
        vboxLayout9->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout9->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout9->setObjectName(QString::fromUtf8("vboxLayout9"));
        qtinfo_ok_checkBox = new QCheckBox(help_page);
        qtinfo_ok_checkBox->setObjectName(QString::fromUtf8("qtinfo_ok_checkBox"));

        vboxLayout9->addWidget(qtinfo_ok_checkBox);

        hboxLayout11 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout11->setSpacing(6);
#endif
        hboxLayout11->setContentsMargins(0, 0, 0, 0);
        hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
        help_path_label = new QLabel(help_page);
        help_path_label->setObjectName(QString::fromUtf8("help_path_label"));

        hboxLayout11->addWidget(help_path_label);

        help_path_lineEdit = new QLineEdit(help_page);
        help_path_lineEdit->setObjectName(QString::fromUtf8("help_path_lineEdit"));

        hboxLayout11->addWidget(help_path_lineEdit);


        vboxLayout9->addLayout(hboxLayout11);

        hboxLayout12 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout12->setSpacing(6);
#endif
        hboxLayout12->setContentsMargins(0, 0, 0, 0);
        hboxLayout12->setObjectName(QString::fromUtf8("hboxLayout12"));
        spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout12->addItem(spacerItem4);

        help_path_select_pushButton = new QPushButton(help_page);
        help_path_select_pushButton->setObjectName(QString::fromUtf8("help_path_select_pushButton"));

        hboxLayout12->addWidget(help_path_select_pushButton);


        vboxLayout9->addLayout(hboxLayout12);

        spacerItem5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout9->addItem(spacerItem5);

        toolBox->addItem(help_page, QString::fromUtf8("Help"));

        vboxLayout->addWidget(toolBox);

        hboxLayout13 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout13->setSpacing(6);
#endif
        hboxLayout13->setContentsMargins(0, 0, 0, 0);
        hboxLayout13->setObjectName(QString::fromUtf8("hboxLayout13"));
        spacerItem6 = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout13->addItem(spacerItem6);

        okButton = new QPushButton(GeneralMenu);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout13->addWidget(okButton);

        cancelButton = new QPushButton(GeneralMenu);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout13->addWidget(cancelButton);


        vboxLayout->addLayout(hboxLayout13);


        retranslateUi(GeneralMenu);
        QObject::connect(okButton, SIGNAL(clicked()), GeneralMenu, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), GeneralMenu, SLOT(reject()));

        toolBox->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(GeneralMenu);
    } // setupUi

    void retranslateUi(QDialog *GeneralMenu)
    {
        GeneralMenu->setWindowTitle(QApplication::translate("GeneralMenu", "General Menu", 0, QApplication::UnicodeUTF8));
        font_text_label->setText(QApplication::translate("GeneralMenu", "Font:", 0, QApplication::UnicodeUTF8));
        font_label->setText(QApplication::translate("GeneralMenu", "TextLabel", 0, QApplication::UnicodeUTF8));
        font_button->setText(QApplication::translate("GeneralMenu", "Select Font", 0, QApplication::UnicodeUTF8));
        color_text_label->setText(QApplication::translate("GeneralMenu", "Color:", 0, QApplication::UnicodeUTF8));
        color_label->setText(QApplication::translate("GeneralMenu", "QtOctave Terminal example", 0, QApplication::UnicodeUTF8));
        error_example_label->setText(QApplication::translate("GeneralMenu", "Error example", 0, QApplication::UnicodeUTF8));
        error_button->setText(QApplication::translate("GeneralMenu", "Error", 0, QApplication::UnicodeUTF8));
        background_button->setText(QApplication::translate("GeneralMenu", "Background", 0, QApplication::UnicodeUTF8));
        foreground_button->setText(QApplication::translate("GeneralMenu", "Foreground", 0, QApplication::UnicodeUTF8));
        max_line_label->setText(QApplication::translate("GeneralMenu", "Maximum number of lines in terminal:", 0, QApplication::UnicodeUTF8));
        max_col_label->setText(QApplication::translate("GeneralMenu", "Max number of columns in terminal:", 0, QApplication::UnicodeUTF8));
        show_ide_commands_checkBox->setText(QApplication::translate("GeneralMenu", "Show QtOctave IDE commands", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(terminal_page), QApplication::translate("GeneralMenu", "Terminal", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GeneralMenu", "Max. number of commands", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(command_list_page), QApplication::translate("GeneralMenu", "Command List", 0, QApplication::UnicodeUTF8));
        use_external_editor->setText(QApplication::translate("GeneralMenu", "Use external editor", 0, QApplication::UnicodeUTF8));
        editor_label->setText(QApplication::translate("GeneralMenu", "External editor", 0, QApplication::UnicodeUTF8));
        editor_select_button->setText(QApplication::translate("GeneralMenu", "Select...", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("GeneralMenu", "Internal Editor", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("GeneralMenu", "Font", 0, QApplication::UnicodeUTF8));
        textEditFont_label->setText(QApplication::translate("GeneralMenu", "Font:", 0, QApplication::UnicodeUTF8));
        textEditFont_pushButton->setText(QApplication::translate("GeneralMenu", "Select Font", 0, QApplication::UnicodeUTF8));
        aautoindent_groupBox->setTitle(QApplication::translate("GeneralMenu", "Automatic indention", 0, QApplication::UnicodeUTF8));
        no_autoindent_radioButton->setText(QApplication::translate("GeneralMenu", "No indention", 0, QApplication::UnicodeUTF8));
        autoindent_radioButton->setText(QApplication::translate("GeneralMenu", "Automatic indention", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        autoindent_statements_radioButton->setToolTip(QApplication::translate("GeneralMenu", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Automatic indention for while, if, for, switch, do and try statements.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        autoindent_statements_radioButton->setText(QApplication::translate("GeneralMenu", "Automatic indention for statements", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("GeneralMenu", "Other features", 0, QApplication::UnicodeUTF8));
        syntaxHighlighting_checkBox->setText(QApplication::translate("GeneralMenu", "Syntax highlighting", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        bracketsMatch_checkBox->setToolTip(QApplication::translate("GeneralMenu", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Brackets pair are iluminated when cursor is over one of them.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bracketsMatch_checkBox->setText(QApplication::translate("GeneralMenu", "Brackets match", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        autoCompletion_checkBox->setToolTip(QApplication::translate("GeneralMenu", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">When the user starts typing a word, it suggests possible ways of completing the word.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        autoCompletion_checkBox->setText(QApplication::translate("GeneralMenu", "Auto-completion", 0, QApplication::UnicodeUTF8));
        simple_rcs_checkBox->setText(QApplication::translate("GeneralMenu", "Simple RCS (Revision Control System)", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(editor_page), QApplication::translate("GeneralMenu", "Editor", 0, QApplication::UnicodeUTF8));
        octave_path_label->setText(QApplication::translate("GeneralMenu", "Octave Path", 0, QApplication::UnicodeUTF8));
        octave_path_pushButton->setText(QApplication::translate("GeneralMenu", "Select...", 0, QApplication::UnicodeUTF8));
        octaveArgs_lbl->setText(QApplication::translate("GeneralMenu", "Octave arguments", 0, QApplication::UnicodeUTF8));
        octaveDir_label->setText(QApplication::translate("GeneralMenu", "Folders:", 0, QApplication::UnicodeUTF8));
        octaveDirAdd_button->setText(QApplication::translate("GeneralMenu", "Add", 0, QApplication::UnicodeUTF8));
        octaveDirRem_button->setText(QApplication::translate("GeneralMenu", "Delete", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("GeneralMenu", "Easy Plot", 0, QApplication::UnicodeUTF8));
        easy_plot_checkBox->setText(QApplication::translate("GeneralMenu", "Use Easy Plot", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GeneralMenu", "Easy Plot Path:", 0, QApplication::UnicodeUTF8));
        easy_plot_path_pushButton->setText(QApplication::translate("GeneralMenu", "Select...", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(octave), QApplication::translate("GeneralMenu", "Octave", 0, QApplication::UnicodeUTF8));
        qtinfo_ok_checkBox->setText(QApplication::translate("GeneralMenu", "Use internal help instead qtinfo", 0, QApplication::UnicodeUTF8));
        help_path_label->setText(QApplication::translate("GeneralMenu", "Help path", 0, QApplication::UnicodeUTF8));
        help_path_select_pushButton->setText(QApplication::translate("GeneralMenu", "Select...", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(help_page), QApplication::translate("GeneralMenu", "Help", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("GeneralMenu", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("GeneralMenu", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GeneralMenu: public Ui_GeneralMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERAL_MENU_H
