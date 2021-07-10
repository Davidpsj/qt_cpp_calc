#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define NUM1  0
#define OPER  1
#define NUM2  2

#include <QMainWindow>

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
    void on_pb_clean_clicked();
    void on_pb_equal_clicked();
    void on_pb_0_clicked();
    void on_pb_1_clicked();
    void on_pb_2_clicked();
    void on_pb_3_clicked();
    void on_pb_4_clicked();
    void on_pb_5_clicked();
    void on_pb_6_clicked();
    void on_pb_7_clicked();
    void on_pb_8_clicked();
    void on_pb_9_clicked();
    void on_pb_dot_clicked();
    void on_pb_sum_clicked();
    void on_pb_sub_clicked();
    void on_pb_div_clicked();
    void on_pb_mult_clicked();
    void on_pb_percent_clicked();

private:
    Ui::MainWindow *ui;
    QString result = "";
    QString tmpData = "";
    QString data[3] = { "", "", "" };
    void manageTmpData(QString _data);
    void writeInLcd(void);
    void makeOperations(bool percent);
};
#endif // MAINWINDOW_H
