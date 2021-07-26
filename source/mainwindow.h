#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QShortcut>

#include "appmodel.h"
#include "appcontroller.h"
#include "my_label.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_cancel_clicked();

    void on_open_clicked();
    void slotShortcutF11();  //полный экран
    void slotShortcutS();   //сохранить
    void slotShortcutO();  //открыть
    void slotShortcutZ();   //отменить
    void slotWheel_Roll();
    void Mouse_Release();
    void on_save_clicked();

    void slotCustomMenuRequested(QPoint pos);
    void slotmale();
    void slotfemale();
    void slotyoung();
    void sltdeletePoint();

    void on_comboBox_currentIndexChanged(int index);

    void on_apply_clicked();

    void on_segmentation_clicked();

    void on_binarization_clicked();

    void on_source_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
    void Graph_view();

    void on_pushButton_7_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_12_clicked();

    void on_manual_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;

    AppModel a_model;
    AppController* a_controller;
    QShortcut       *keyF11;
    QShortcut       *keyCtrlD;
    QShortcut       *keyCtrlS;
    QShortcut       *keyCtrlO;
    QShortcut       *keyCtrlZ;
    QShortcut       *keySM;
    QShortcut       *keySF;
    QShortcut       *keySY;

    int State=0;
    int ImgViev=0;
    QString folder;
};
#endif // MAINWINDOW_H
