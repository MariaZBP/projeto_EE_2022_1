#include "mainwindow.h"
#include "ui_mainwindow.h"

//declara como banco de dados global
static QSqlDatabase bancoDados = QSqlDatabase::addDatabase("QSQLITE");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //cria a conexão com o banco de dados
    bancoDados.setDatabaseName("C:/Users/Ceiça/Documents/projeto_EE/projeto_banco_de_dados/banco.db");

    //verifica se o banco de dados foi conectado
    if(bancoDados.open()){
        ui->statusBar->showMessage("Banco de dados conectado com sucesso!");
    }else{
        ui->statusBar->showMessage("Erro ao conectar com o banco de dados!");
    }

    //mensagem de aviso para o usuário
    ui->txtNome->setPlaceholderText("Digite seu nome");
    ui->txtSenha->setPlaceholderText("Digite sua senha");
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
