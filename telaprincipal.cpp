#include "telaprincipal.h"
#include "ui_telaprincipal.h"

TelaPrincipal::TelaPrincipal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaPrincipal)
{
    ui->setupUi(this);

    //personalização da aba funcionários
    ui->txtPesquisarFuncionario->setStyleSheet("color: black;"
                                 "background-color: #aaff7f;"
                                 "selection-color: black;"
                                 "selection-background-color: #aaff7f;");

    ui->btnCadastrarFuncionario->setStyleSheet("color: black;"
                                 "background-color: #00ff7f;"
                                 "border-style: outset;"
                                 "border-width: 2px;"
                                 "border-radius: 10px;"
                                 "border-color: white;"
                                 "font: bold 16px;");

    ui->btnExcluirFuncionario->setStyleSheet("color: black;"
                               "background-color: #00ff7f;"
                               "border-style: outset;"
                               "border-width: 2px;"
                               "border-radius: 10px;"
                               "border-color: white;"
                               "font: bold 16px;");

    //marcando e desmarcando o radio button
    ui->rdNome->setChecked(true);
    ui->rdCPF->setChecked(false);
    ui->rdDepartamento->setChecked(false);

    carregarDados();
}

TelaPrincipal::~TelaPrincipal()
{
    delete ui;
}

void TelaPrincipal::carregarDados(){
    QSqlQuery pegaDados;
    pegaDados.prepare("SELECT * FROM Funcionarios");
    if(pegaDados.exec()){

    }else{
        QMessageBox::information(this,"Atenção","Erro ao carregar os dados dos funcionários!");
    }
}
