#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeOperations(bool percent = false)
{
    const QString msg = "Não é possível realizar divisão por 0!";
    if(!percent) {
        if(data[OPER] == "+")
            // Sum
            result = QString::number(data[NUM1].toDouble() + data[NUM2].toDouble());
        else if (data[OPER] == "-")
            // Sub
            result = QString::number(data[NUM1].toDouble() - data[NUM2].toDouble());
        else if (data[OPER] == "x" && !percent)
            // Mult
            result = QString::number(data[NUM1].toDouble() * data[NUM2].toDouble());
        else if (data[OPER] == ":" && data[NUM2] != "0")
            // Div
            result = QString::number(data[NUM1].toDouble() / data[NUM2].toDouble());
        else if (data[OPER] == ":" && data[NUM2] == "0") {
            QMessageBox msgBox;
            msgBox.setInformativeText(msg);
            msgBox.exec();
            data[NUM2] = "";
            return;
        }
    } else {
        if (data[OPER] == "x")
            // Percent
            result = QString::number(data[NUM1].toDouble() * data[NUM2].toDouble() / 100);
        else if (data[OPER] == "+")
            result = QString::number(data[NUM1].toDouble() * data[NUM2].toDouble() / 100 + data[NUM1].toDouble());
        else if (data[OPER] == "-")
            result = QString::number((data[NUM1].toDouble() * data[NUM2].toDouble() / 100 - data[NUM1].toDouble()) * -1);
        else if (data[OPER] == ":")
            result = QString::number(data[NUM1].toDouble() / (data[NUM1].toDouble() * data[NUM2].toDouble() / 100));
    }

    // writeLcd
    writeInLcd();
}

void MainWindow::writeInLcd()
{
    if(data[OPER] == "")
        ui->lcdNumber->display(data[NUM1]);
    else if(data[OPER] != "" && result == "")
        ui->lcdNumber->display(data[NUM2]);
    else
        ui->lcdNumber->display(result);
}

void MainWindow::manageTmpData(QString _data)
{
    if(result != "") {
        result = "";
        data[NUM1] = "";
        data[OPER] = "";
        data[NUM2] = "";
    }

    // Regex to check operator.
    QRegularExpression oper("^\\+|\\-|x|\\:$");

    // Match regex to operator data.
    QRegularExpressionMatch operMatch = oper.match(_data);

    if(operMatch.hasMatch() && data[NUM1] != "") {
        data[OPER] = _data;
        tmpData = "";
        return;
    }

    // Regex to check digit values.
    QRegularExpression digit("^\\d$");

    // Match regex to digit data.
    QRegularExpressionMatch mdig = digit.match(_data);

    // If matched append the _data value into tmpData.
    if(mdig.hasMatch()){
        tmpData += _data;
    } else {
        // Regex to find dot into tmpData.
        QRegularExpression dot("^\\d+\\.\\d{0,}$");
        // Match regex to dot data.
        QRegularExpressionMatch mdot = dot.match(tmpData);

        // If dot not found then add the dot value into tmpData.
        if(!mdot.hasMatch() && !operMatch.hasMatch() && _data != "=" && _data != "%") {
            tmpData += _data;
        }
    }

    // If operator space in data array is empty.
    if(data[OPER] == "") {
        // Clean data position 0
        data[NUM1] = "";
        // attribute tmpData into data position 0 as number.
        data[NUM1] = tmpData;
    } else if(!operMatch.hasMatch() && _data != "=" && _data != "%") { // if operator space was setted.
        data[NUM2] = "";
        data[NUM2] = tmpData;
    }

    if(_data == "=") {
        makeOperations(false);
        data[NUM1] = result;
        result = "";
        data[OPER] = "";
        data[NUM2] = "";
        tmpData = "";
    } else if(_data == "%") {
         makeOperations(true);
         data[NUM1] = result;
         result = "";
         data[OPER] = "";
         data[NUM2] = "";
         tmpData = "";
    } else {
        writeInLcd();
    }
}


void MainWindow::on_pb_clean_clicked()
{
    result = "";
    data[NUM1] = "";
    data[OPER] = "";
    data[NUM2] = "";
    tmpData = "";
    ui->lcdNumber->display("0");
}

void MainWindow::on_pb_equal_clicked()
{
    manageTmpData("=");
}

void MainWindow::on_pb_dot_clicked()
{
//    tmpData += ".";
    manageTmpData(".");
}

void MainWindow::on_pb_0_clicked()
{
//    tmpData += "0";
    manageTmpData("0");
}

void MainWindow::on_pb_1_clicked()
{
//    tmpData += "1";
    manageTmpData("1");
}

void MainWindow::on_pb_2_clicked()
{
//    tmpData += "2";
    manageTmpData("2");
}

void MainWindow::on_pb_3_clicked()
{
//    tmpData += "3";
    manageTmpData("3");
}

void MainWindow::on_pb_4_clicked()
{
//    tmpData += "4";
    manageTmpData("4");
}

void MainWindow::on_pb_5_clicked()
{
//    tmpData += "5";
    manageTmpData("5");
}

void MainWindow::on_pb_6_clicked()
{
//    tmpData += "6";
    manageTmpData("6");
}

void MainWindow::on_pb_7_clicked()
{
//    tmpData += "7";
    manageTmpData("7");
}

void MainWindow::on_pb_8_clicked()
{
//    tmpData += "8";
    manageTmpData("8");
}

void MainWindow::on_pb_9_clicked()
{
//    tmpData += "9";
    manageTmpData("9");
}

void MainWindow::on_pb_sum_clicked()
{
    manageTmpData("+");
}

void MainWindow::on_pb_sub_clicked()
{
    manageTmpData("-");
}

void MainWindow::on_pb_mult_clicked()
{
    manageTmpData("x");
}

void MainWindow::on_pb_div_clicked()
{
    manageTmpData(":");
}

void MainWindow::on_pb_percent_clicked()
{
    manageTmpData("%");
}
