#pragma once

#include <QWidget>
#include <QList>

namespace Ui {
class Calculator;
}

enum BinaryOp: char {
    Eq = '=',
    Add = '+',
    Sub = '-',
    Mul = 'x',
    Div = '/',
    Mod = '%'
};

enum UnaryOp {
    Neg,
    Inv,
    Square,
    Sqrt
};

enum Error {
    None,
    NegSqrt,
    DivBy0
};

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

    double getInput();

    void setInput(QString);

    inline void setInput(double value) { setInput(QString::number(value)); }

    inline void updateInput(double value) { setInput(value); lValue = value; }

    bool hasError();

    void clearAll();

private:
    void enterInput(QString);

    void enterDigit(int);

    void enterUnaryOp(UnaryOp);

    void enterBinaryOp(BinaryOp);

    void performCalculation();

    void displayInput();

    void displayResult();

    void displayError(Error);

    void clearInput();

    void enableButtons(bool);

private slots:
    void on_buttonDigit1_clicked();

    void on_buttonDigit2_clicked();

    void on_buttonDigit3_clicked();

    void on_buttonDigit4_clicked();

    void on_buttonDigit5_clicked();

    void on_buttonDigit6_clicked();

    void on_buttonDigit7_clicked();

    void on_buttonDigit8_clicked();

    void on_buttonDigit9_clicked();

    void on_buttonDigit0_clicked();

    void on_buttonOpMul_clicked();

    void on_buttonOpSub_clicked();

    void on_buttonOpAdd_clicked();

    void on_buttonOpNeg_clicked();

    void on_buttonOpDot_clicked();

    void on_buttonOpEq_clicked();

    void on_buttonOpMod_clicked();

    void on_buttonOpDel_clicked();

    void on_buttonOpCe_clicked();

    void on_buttonOpC_clicked();

    void on_buttonOpInv_clicked();

    void on_buttonOpSquare_clicked();

    void on_buttonOpSqrt_clicked();

    void on_buttonOpDiv_clicked();

private:
    Ui::Calculator *ui;
    // user entered input
    QString input;
    // the output to display
    QString output;
    BinaryOp op;
    BinaryOp prev;
    double rValue = 0.0;
    double lValue = 0.0;
    Error err;
};
