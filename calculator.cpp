#include "calculator.h"
#include "ui_calculator.h"

#include <QString>
#include <QDebug>
#include <cmath>

Calculator::Calculator(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Calculator),
    input(""),
    output(""),
    op(Eq),
    err(None)
{
    ui->setupUi(this);
    setInput(0);
}

Calculator::~Calculator() {
    delete ui;
}

double Calculator::getInput()
{
    bool ok;
    double value = ui->labelExpression->text().toDouble(&ok);
    if (!ok) qDebug() << "Conversion should never fail";
    return value;
}

void Calculator::setInput(QString value)
{
    input = value == "0" ? "" : value;
    displayInput();
}

void Calculator::enterInput(QString in)
{
    // if (input.length() > 12) return;
    setInput(input + in);
    if (op == Eq) {
        prev = Eq;
        lValue = getInput();
        ui->labelResult->setText("");
    }
}

void Calculator::enterDigit(int d)
{
    enterInput(QString::number(d));
}

void Calculator::enterUnaryOp(UnaryOp op)
{
    if (output == "") output = QString::number(lValue);
    if (op != Neg && this->op != Eq) enterBinaryOp(Eq);
    switch (op) {
        case Neg:
            lValue = -lValue; break;
        case Inv:
            if (lValue == 0.0) {
                displayError(DivBy0);
                return;
            }
            output = "1 / (" + output + ")";
            lValue = 1.0 / lValue; break;
        case Square:
            output = "sqr(" + output + ")";
            lValue *= lValue; break;
        case Sqrt:
            if (lValue < 0) {
                displayError(NegSqrt);
                return;
            }
            output = "sqrt(" + output + ")";
            lValue = sqrt(lValue); break;
    }

    setInput(lValue);
    displayResult();
    clearInput();
}

void Calculator::enterBinaryOp(BinaryOp op)
{
    bool ok;
    double expr = input.toDouble(&ok);
    if (!ok) {
        if (op == prev) {
            performCalculation();
            output = QString::number(lValue);
        }
        else this->op = op;
        displayResult();
        return;
    }

    rValue = expr;
    prev = this->op;
    performCalculation();
    this->op = op;
    prev = op;
    output = QString::number(lValue);

    displayResult();
    clearInput();
}

void Calculator::performCalculation()
{
    switch (prev) {
        case Eq:
            return;
        case Add:
            lValue += rValue; break;
        case Sub:
            lValue -= rValue; break;
        case Mul:
            lValue *= rValue; break;
        case Div:
            if (rValue == 0.0) {
                displayError(DivBy0);
                return;
            }
            lValue /= rValue; break;
        case Mod:
            lValue = fmod(lValue, rValue); break;
    }
}

void Calculator::clearInput()
{
    input = "";
}

void Calculator::displayResult()
{
    ui->labelResult->setText((output == "" ? "0" : output) + " " + op);
}

void Calculator::displayInput()
{
    QString msg = input == "" ? "0" : input;
    // lead with a zero
    if (msg.startsWith(".", Qt::CaseInsensitive)) msg = "0" + msg;
    ui->labelExpression->setText(msg);
}

void Calculator::displayError(Error err)
{
    this->err = err;
    QString msg;
    switch (err) {
        case None: return;
        case NegSqrt: msg = "Negative sqrt"; break;
        case DivBy0: msg = "Division by 0"; break;
    };
    ui->labelExpression->setText(msg);
    enableButtons(false);
}

void Calculator::enableButtons(bool enabled)
{
    for (auto button : {
         ui->buttonOpDot,
         ui->buttonDigit0,
         ui->buttonDigit1,
         ui->buttonDigit2,
         ui->buttonDigit3,
         ui->buttonDigit4,
         ui->buttonDigit5,
         ui->buttonDigit6,
         ui->buttonDigit7,
         ui->buttonDigit8,
         ui->buttonDigit9,
         ui->buttonOpEq,
         ui->buttonOpAdd,
         ui->buttonOpSub,
         ui->buttonOpMul,
         ui->buttonOpDiv,
         ui->buttonOpMod,
         ui->buttonOpNeg,
         ui->buttonOpInv,
         ui->buttonOpSquare,
         ui->buttonOpSqrt,
    }) {
        button->setEnabled(enabled);
    }
}

bool Calculator::hasError()
{
    return this->err != None;
}

void Calculator::clearAll()
{
    output = "";
    op = Eq;
    prev = Eq;
    lValue = 0.0;
    rValue = 0.0;
    ui->labelResult->setText("");
    on_buttonOpCe_clicked();
}

void Calculator::on_buttonOpDel_clicked()
{
    if (hasError()) return;
    input.remove(input.length() - 1, 1);
    if (input.endsWith("."))
        input.remove(input.length() - 1, 1);
    enterInput("");
}

void Calculator::on_buttonOpDot_clicked()
{
   if (input.contains(".", Qt::CaseInsensitive)) return;
   enterInput(".");
}

void Calculator::on_buttonOpC_clicked()
{
    clearAll();
}

void Calculator::on_buttonOpCe_clicked()
{
    err = None;
    clearInput();
    displayInput();
    enableButtons(true);
}

void Calculator::on_buttonDigit1_clicked()
{
    enterDigit(1);
}

void Calculator::on_buttonDigit2_clicked()
{
    enterDigit(2);
}

void Calculator::on_buttonDigit3_clicked()
{
    enterDigit(3);
}

void Calculator::on_buttonDigit4_clicked()
{
    enterDigit(4);
}

void Calculator::on_buttonDigit5_clicked()
{
    enterDigit(5);
}

void Calculator::on_buttonDigit6_clicked()
{
    enterDigit(6);
}

void Calculator::on_buttonDigit7_clicked()
{
    enterDigit(7);
}

void Calculator::on_buttonDigit8_clicked()
{
    enterDigit(8);
}

void Calculator::on_buttonDigit9_clicked()
{
    enterDigit(9);
}

void Calculator::on_buttonDigit0_clicked()
{
    if (input == "") return;
    if (input.startsWith("0", Qt::CaseInsensitive)) return;
    enterDigit(0);
}

void Calculator::on_buttonOpEq_clicked()
{
    if (prev == Eq) return;

    double old = lValue;
    if (op == Eq) {
        performCalculation();
    } else {
        bool ok;
        double expr = input.toDouble(&ok);
        if (ok) rValue = expr;
        prev = this->op;
        performCalculation();
        op = Eq;
    }
    setInput(lValue);
    clearInput();

    output = QString::number(old) + " " + prev + " " + QString::number(rValue);
    displayResult();
}

void Calculator::on_buttonOpAdd_clicked()
{
    enterBinaryOp(Add);
}

void Calculator::on_buttonOpSub_clicked()
{
    enterBinaryOp(Sub);
}

void Calculator::on_buttonOpMul_clicked()
{
    enterBinaryOp(Mul);
}

void Calculator::on_buttonOpDiv_clicked()
{
    enterBinaryOp(Div);
}

void Calculator::on_buttonOpMod_clicked()
{
    enterBinaryOp(Mod);
}

void Calculator::on_buttonOpNeg_clicked()
{
    enterUnaryOp(Neg);
}

void Calculator::on_buttonOpInv_clicked()
{
    enterUnaryOp(Inv);
}

void Calculator::on_buttonOpSquare_clicked()
{
    enterUnaryOp(Square);
}

void Calculator::on_buttonOpSqrt_clicked()
{
    enterUnaryOp(Sqrt);
}
