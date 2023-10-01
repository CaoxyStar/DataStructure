#include "calculator.h"
#include "ui_calculator.h"
#include "my_calculator.h"
#include "iostream"


calculator::calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);
}

calculator::~calculator()
{
    delete ui;
}


void calculator::on_pushButton_clicked()
{
    ui->textBrowser->insertPlainText("1");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_2_clicked()
{
    ui->textBrowser->insertPlainText("2");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_3_clicked()
{
    ui->textBrowser->insertPlainText("3");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_4_clicked()
{
    ui->textBrowser->insertPlainText("4");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_5_clicked()
{
    ui->textBrowser->insertPlainText("5");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_6_clicked()
{
    ui->textBrowser->insertPlainText("6");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_7_clicked()
{
    ui->textBrowser->insertPlainText("7");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_8_clicked()
{
    ui->textBrowser->insertPlainText("8");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_9_clicked()
{
    ui->textBrowser->insertPlainText("9");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_10_clicked()
{
    ui->textBrowser->insertPlainText("0");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_11_clicked()
{
    ui->textBrowser->insertPlainText(".");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_12_clicked()
{
    QString str=ui->textBrowser->toPlainText();
    std::string formula=str.toStdString().data();
    formula.push_back(';');
    double res=main_func(formula);
    ui->textBrowser->insertPlainText("=");
    ui->textBrowser->insertPlainText(QString::number(res));
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_13_clicked()
{
    ui->textBrowser->insertPlainText("+");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_14_clicked()
{
    ui->textBrowser->insertPlainText("-");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_15_clicked()
{
    ui->textBrowser->insertPlainText("x");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_16_clicked()
{
    ui->textBrowser->insertPlainText("/");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_17_clicked()
{
    ui->textBrowser->insertPlainText("^");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_18_clicked()
{
    ui->textBrowser->setPlainText("");
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void calculator::on_pushButton_19_clicked()
{
    ui->textBrowser->textCursor().deletePreviousChar();
    ui->textBrowser->moveCursor(QTextCursor::End);
}


