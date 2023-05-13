#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "manual.h"
#include "about.h"
#include "worker.h"
#include "doctor.h"
#include "security.h"
#include "cashier.h"
#include "med_center.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QtGui>
#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>
#include <iostream>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private slots:

    void on_pushButton_clicked();

    void setWidgetsToAddOrEdit();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_comboBox_2_activated(int index);

    void on_pushButton_6_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_5_activated(int index);

    void on_comboBox_6_activated(int index);

    void Show(Worker *, Med_Center *, const int&);

    int on_action_triggered();

    void on_action_2_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    int on_action_7_triggered();

    void on_pushButton_17_clicked();

    void on_action_8_triggered();

    void on_action_9_triggered();

    void CheckCorrectData(const QString&, const QString&, const QString&, \
                         const QString&,const QString&, const QString&, \
                         const QString&, const QString&, const QString&, \
                         const QString&, const QString&, const QString&, \
                         const QString&, const QString&, const QString&, int *);

    void on_pushButton_18_clicked();

    void on_comboBox_7_activated(int index);

private:
    Ui::MainWindow *ui;
    Manual *Man;
    About *Ab;
};
#endif // MAINWINDOW_H
