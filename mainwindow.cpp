#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <telaprincipal.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLogin_clicked()
{

    TelaPrincipal abrirTelaPrincipal;
    abrirTelaPrincipal.setModal(true);
    abrirTelaPrincipal.exec();
}
