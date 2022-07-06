#include "editarfuncionario.h"
#include "ui_editarfuncionario.h"

static int idSelecionado;

EditarFuncionario::EditarFuncionario(QWidget *parent, int alterarFuncionario_ID) :
    QDialog(parent),
    ui(new Ui::EditarFuncionario)
{
    ui->setupUi(this);

    QSqlQuery dados;
    idSelecionado = alterarFuncionario_ID;
    QString id = QString::number(alterarFuncionario_ID);
    dados.prepare("Select * from Funcionarios where idFuncionario="+id);

    if(dados.exec()){
        dados.first();
        ui->txtEditarFuncionario_CPF->setText(dados.value(1).toString());
        ui->txtEditarFuncionario_Nome->setText(dados.value(2).toString());
        ui->txtEditarFuncionario_Salario->setText(dados.value(3).toString());
        ui->cmbEditarFuncionario_Departamento->setCurrentText(dados.value(4).toString());
        ui->txtEditarFuncionario_DataNascimento->setText(dados.value(5).toString());
        ui->txtEditarFuncionario_Telefone->setText(dados.value(6).toString());
        ui->txtEditarFuncionario_Email->setText(dados.value(7).toString());
    }else{
        QMessageBox::information(this,"Atenção!","Erro ao carregar informações do funcionário!");
    }
}

EditarFuncionario::~EditarFuncionario()
{
    delete ui;
}
