#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeySequence>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::NoFocus);
    ui->right->shortcutPrefix(QString("Ctrl"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonL2R_clicked()
{
    if (ui->left->hasError()) return;
    ui->right->updateInput(ui->left->getInput());
}

void MainWindow::on_buttonR2L_clicked()
{
    if (ui->right->hasError()) return;
    ui->left->updateInput(ui->right->getInput());
}

void MainWindow::on_buttonClear_clicked()
{
    ui->left->clearAll();
    ui->right->clearAll();
}
