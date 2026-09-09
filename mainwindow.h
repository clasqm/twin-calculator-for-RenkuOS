#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonL2R_clicked();

    void on_buttonR2L_clicked();

    void on_buttonClear_clicked();

private:
    Ui::MainWindow *ui;
};
