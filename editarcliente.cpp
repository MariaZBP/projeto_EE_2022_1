#include "editarcliente.h"
#include "ui_editarcliente.h"

static int idSelecionado;

EditarCliente::EditarCliente(QWidget *parent, int alterarCliente_ID) :
    QDialog(parent),
    ui(new Ui::EditarCliente)
{
    ui->setupUi(this);

    //inserindo máscaras nos campos
    ui->txtEditarCliente_CPF->setInputMask("000.000.000-00");
    ui->txtEditarCliente_Telefone->setInputMask("(99) 99999-9999");
    ui->txtEditarCliente_DataNascimento->setInputMask("99/99/9999");


    //personalização dos botões
    ui->btnSalvarEdicaoCliente->setStyleSheet("color: black;"
                                               "background-color: #00ff7f;"
                                               "border-style: outset;"
                                               "border-width: 2px;"
                                               "border-radius: 10px;"
                                               "border-color: white;"
                                               "font: bold 16px;");

    ui->btnCancelarEdicaoCliente->setStyleSheet("color: black;"
                                               "background-color: #00ff7f;"
                                               "border-style: outset;"
                                               "border-width: 2px;"
                                               "border-radius: 10px;"
                                               "border-color: white;"
                                               "font: bold 16px;");

    QSqlQuery dados;
    idSelecionado = alterarCliente_ID;
    QString id = QString::number(alterarCliente_ID);
    dados.prepare("Select * from Clientes where idCliente="+id);

    if(dados.exec()){
        dados.first();
        ui->lblEditarCliente_ID->setText(dados.value(0).toString());
        ui->txtEditarCliente_CPF->setText(dados.value(1).toString());
        ui->txtEditarCliente_Nome->setText(dados.value(2).toString());
        ui->txtEditarCliente_Endereco->setText(dados.value(3).toString());
        ui->txtEditarCliente_DataNascimento->setText(dados.value(4).toString());
        ui->txtEditarCliente_Telefone->setText(dados.value(5).toString());
        ui->txtEditarCliente_Email->setText(dados.value(6).toString());
    }else{
        QMessageBox::information(this,"Atenção!","Erro ao carregar informações do cliente!");
    }
}

EditarCliente::~EditarCliente()
{
    delete ui;
}

void EditarCliente::on_btnSalvarEdicaoCliente_clicked()
{
    QString id = ui->lblEditarCliente_ID->text();
    QString cpf = ui->txtEditarCliente_CPF->text();
    QString nome = ui->txtEditarCliente_Nome->text();
    QString endereco = ui->txtEditarCliente_Endereco->text();
    QString dataNascimento = ui->txtEditarCliente_DataNascimento->text();
    QString telefone = ui->txtEditarCliente_Telefone->text();
    QString email = ui->txtEditarCliente_Email->text();

    //grava os dados da alteração no BD
    QSqlQuery dados;
    dados.prepare("Update Clientes set idCliente='"+id+"',"
                                           "cpfCliente='"+cpf+"',"
                                           "nomeCliente='"+nome+"',"
                                           "enderecoCliente='"+endereco+"',"
                                           "dataNascimentoCliente='"+dataNascimento+"',"
                                           "telefoneCliente='"+telefone+"',"
                                           "emailCliente='"+email+"' where idCliente="+QString::number(idSelecionado));

    if(dados.exec()){
        this->close();
    }else{
        QMessageBox::critical(this, "Atenção", "Erro ao salvar as alterações!");
    }
}

void EditarCliente::on_btnCancelarEdicaoCliente_clicked()
{
    close();
}
