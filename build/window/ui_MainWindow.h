/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *port_name_Comb;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *data_bits_Comb;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *baud_rate_Comb;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QComboBox *stop_bits_Comb;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *parity_Comb;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QSpinBox *timeout_spinBox;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *is_Open_Btn;
    QPushButton *open_port_Btn;
    QPushButton *close_port_Btn;
    QWidget *horizontalWidget_2;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_7;
    QTextBrowser *info_Panel;
    QRadioButton *save_data_Btn;
    QPushButton *screen_shot_Btn;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QPlainTextEdit *send_Panel;
    QPushButton *send_Btn;
    QWidget *plot_widget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_11;
    QwtPlot *qwtPlot;
    QWidget *verticalWidget1;
    QVBoxLayout *verticalLayout_5;
    QSlider *y_pos_Scope;
    QSlider *y_neg_Scope;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QSlider *num_points_Slider;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *refresh_Time;
    QHBoxLayout *horizontalLayout_12;
    QRadioButton *en_filter_Btn;
    QComboBox *filter_Combo;
    QLabel *label_11;
    QSpinBox *leve_In;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1151, 771);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalWidget = new QWidget(centralwidget);
        verticalWidget->setObjectName(QString::fromUtf8("verticalWidget"));
        verticalWidget->setMaximumSize(QSize(300, 16777215));
        verticalLayout = new QVBoxLayout(verticalWidget);
        verticalLayout->setSpacing(9);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 11);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(verticalWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        port_name_Comb = new QComboBox(verticalWidget);
        port_name_Comb->setObjectName(QString::fromUtf8("port_name_Comb"));

        horizontalLayout_2->addWidget(port_name_Comb);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(verticalWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        data_bits_Comb = new QComboBox(verticalWidget);
        data_bits_Comb->setObjectName(QString::fromUtf8("data_bits_Comb"));

        horizontalLayout_4->addWidget(data_bits_Comb);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(verticalWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        baud_rate_Comb = new QComboBox(verticalWidget);
        baud_rate_Comb->setObjectName(QString::fromUtf8("baud_rate_Comb"));

        horizontalLayout->addWidget(baud_rate_Comb);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(verticalWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        stop_bits_Comb = new QComboBox(verticalWidget);
        stop_bits_Comb->setObjectName(QString::fromUtf8("stop_bits_Comb"));

        horizontalLayout_6->addWidget(stop_bits_Comb);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(verticalWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        parity_Comb = new QComboBox(verticalWidget);
        parity_Comb->setObjectName(QString::fromUtf8("parity_Comb"));

        horizontalLayout_5->addWidget(parity_Comb);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_9 = new QLabel(verticalWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_9->addWidget(label_9);

        timeout_spinBox = new QSpinBox(verticalWidget);
        timeout_spinBox->setObjectName(QString::fromUtf8("timeout_spinBox"));

        horizontalLayout_9->addWidget(timeout_spinBox);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        is_Open_Btn = new QRadioButton(verticalWidget);
        is_Open_Btn->setObjectName(QString::fromUtf8("is_Open_Btn"));

        horizontalLayout_7->addWidget(is_Open_Btn);

        open_port_Btn = new QPushButton(verticalWidget);
        open_port_Btn->setObjectName(QString::fromUtf8("open_port_Btn"));

        horizontalLayout_7->addWidget(open_port_Btn);

        close_port_Btn = new QPushButton(verticalWidget);
        close_port_Btn->setObjectName(QString::fromUtf8("close_port_Btn"));

        horizontalLayout_7->addWidget(close_port_Btn);


        verticalLayout->addLayout(horizontalLayout_7);


        gridLayout->addWidget(verticalWidget, 0, 1, 1, 1);

        horizontalWidget_2 = new QWidget(centralwidget);
        horizontalWidget_2->setObjectName(QString::fromUtf8("horizontalWidget_2"));
        horizontalWidget_2->setMaximumSize(QSize(300, 16777215));
        horizontalLayout_8 = new QHBoxLayout(horizontalWidget_2);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_7 = new QLabel(horizontalWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_2->addWidget(label_7);

        info_Panel = new QTextBrowser(horizontalWidget_2);
        info_Panel->setObjectName(QString::fromUtf8("info_Panel"));

        verticalLayout_2->addWidget(info_Panel);

        save_data_Btn = new QRadioButton(horizontalWidget_2);
        save_data_Btn->setObjectName(QString::fromUtf8("save_data_Btn"));

        verticalLayout_2->addWidget(save_data_Btn);

        screen_shot_Btn = new QPushButton(horizontalWidget_2);
        screen_shot_Btn->setObjectName(QString::fromUtf8("screen_shot_Btn"));

        verticalLayout_2->addWidget(screen_shot_Btn);


        horizontalLayout_8->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_8 = new QLabel(horizontalWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_3->addWidget(label_8);

        send_Panel = new QPlainTextEdit(horizontalWidget_2);
        send_Panel->setObjectName(QString::fromUtf8("send_Panel"));

        verticalLayout_3->addWidget(send_Panel);

        send_Btn = new QPushButton(horizontalWidget_2);
        send_Btn->setObjectName(QString::fromUtf8("send_Btn"));

        verticalLayout_3->addWidget(send_Btn);


        horizontalLayout_8->addLayout(verticalLayout_3);


        gridLayout->addWidget(horizontalWidget_2, 1, 1, 1, 1);

        plot_widget = new QWidget(centralwidget);
        plot_widget->setObjectName(QString::fromUtf8("plot_widget"));
        verticalLayout_4 = new QVBoxLayout(plot_widget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        qwtPlot = new QwtPlot(plot_widget);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));

        horizontalLayout_11->addWidget(qwtPlot);

        verticalWidget1 = new QWidget(plot_widget);
        verticalWidget1->setObjectName(QString::fromUtf8("verticalWidget1"));
        verticalWidget1->setMaximumSize(QSize(30, 16777215));
        verticalLayout_5 = new QVBoxLayout(verticalWidget1);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetMaximumSize);
        y_pos_Scope = new QSlider(verticalWidget1);
        y_pos_Scope->setObjectName(QString::fromUtf8("y_pos_Scope"));
        y_pos_Scope->setOrientation(Qt::Vertical);

        verticalLayout_5->addWidget(y_pos_Scope);

        y_neg_Scope = new QSlider(verticalWidget1);
        y_neg_Scope->setObjectName(QString::fromUtf8("y_neg_Scope"));
        y_neg_Scope->setOrientation(Qt::Vertical);

        verticalLayout_5->addWidget(y_neg_Scope);


        horizontalLayout_11->addWidget(verticalWidget1);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_10 = new QLabel(plot_widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_10->addWidget(label_10);

        num_points_Slider = new QSlider(plot_widget);
        num_points_Slider->setObjectName(QString::fromUtf8("num_points_Slider"));
        num_points_Slider->setOrientation(Qt::Horizontal);

        horizontalLayout_10->addWidget(num_points_Slider);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(plot_widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        refresh_Time = new QSpinBox(plot_widget);
        refresh_Time->setObjectName(QString::fromUtf8("refresh_Time"));

        horizontalLayout_3->addWidget(refresh_Time);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        en_filter_Btn = new QRadioButton(plot_widget);
        en_filter_Btn->setObjectName(QString::fromUtf8("en_filter_Btn"));

        horizontalLayout_12->addWidget(en_filter_Btn);

        filter_Combo = new QComboBox(plot_widget);
        filter_Combo->setObjectName(QString::fromUtf8("filter_Combo"));

        horizontalLayout_12->addWidget(filter_Combo);

        label_11 = new QLabel(plot_widget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_12->addWidget(label_11);

        leve_In = new QSpinBox(plot_widget);
        leve_In->setObjectName(QString::fromUtf8("leve_In"));

        horizontalLayout_12->addWidget(leve_In);


        verticalLayout_4->addLayout(horizontalLayout_12);


        gridLayout->addWidget(plot_widget, 0, 0, 2, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1151, 31));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Port Name", 0, QApplication::UnicodeUTF8));
        port_name_Comb->clear();
        port_name_Comb->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "com1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "com2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "com3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "com4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "com5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "com6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "com7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "com8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "com9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "com10", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("MainWindow", "Data Bits", 0, QApplication::UnicodeUTF8));
        data_bits_Comb->clear();
        data_bits_Comb->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("MainWindow", "Baud Rate", 0, QApplication::UnicodeUTF8));
        baud_rate_Comb->clear();
        baud_rate_Comb->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "115200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "300", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "4800", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("MainWindow", "Stop Bits", 0, QApplication::UnicodeUTF8));
        stop_bits_Comb->clear();
        stop_bits_Comb->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1.5", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("MainWindow", "Parity", 0, QApplication::UnicodeUTF8));
        parity_Comb->clear();
        parity_Comb->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Odd", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Even", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "MARK", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "SPACE", 0, QApplication::UnicodeUTF8)
        );
        label_9->setText(QApplication::translate("MainWindow", "Timeout", 0, QApplication::UnicodeUTF8));
        is_Open_Btn->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        open_port_Btn->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        close_port_Btn->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Info Panel", 0, QApplication::UnicodeUTF8));
        save_data_Btn->setText(QApplication::translate("MainWindow", "Save Data", 0, QApplication::UnicodeUTF8));
        screen_shot_Btn->setText(QApplication::translate("MainWindow", "Print Screen", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Send", 0, QApplication::UnicodeUTF8));
        send_Btn->setText(QApplication::translate("MainWindow", "Send", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Number of Points to display                       ", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Refresh Time", 0, QApplication::UnicodeUTF8));
        en_filter_Btn->setText(QApplication::translate("MainWindow", "Enable filter", 0, QApplication::UnicodeUTF8));
        filter_Combo->clear();
        filter_Combo->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "db4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "db5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "db6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "sym4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "sym5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "sym6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "coif4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "coif5", 0, QApplication::UnicodeUTF8)
        );
        label_11->setText(QApplication::translate("MainWindow", "           Level", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
