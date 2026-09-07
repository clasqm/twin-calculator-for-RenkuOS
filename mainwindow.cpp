#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::NoFocus);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonL2R_clicked()
{
    if (ui->left->hasError()) return;
    ui->right->clearAll();
    ui->right->updateInput(ui->left->getInput());
}

void MainWindow::on_buttonR2L_clicked()
{
    if (ui->right->hasError()) return;
    ui->left->clearAll();
    ui->left->updateInput(ui->right->getInput());
}

void MainWindow::on_buttonClear_clicked()
{
    ui->left->clearAll();
    ui->right->clearAll();
}
