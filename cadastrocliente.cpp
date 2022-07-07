#include "cadastrocliente.h"
#include "ui_cadastrocliente.h"

CadastroCliente::CadastroCliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CadastroCliente)
{
    ui->setupUi(this);

    //inserindo máscaras nos campos
    ui->txtCadastroCliente_CPF->setInputMask("000.000.000-00");
    ui->txtCadastroCliente_Telefone->setInputMask("(99) 99999-9999");
    ui->txtCadastroCliente_DataNascimento->setInputMask("99/99/9999");

    //personalização dos botões
    ui->btnSalvarCliente->setStyleSheet("color: black;"
                                               "background-color: #00ff7f;"
                                               "border-style: outset;"
                                               "border-width: 2px;"
                                               "border-radius: 10px;"
                                               "border-color: white;"
                                               "font: bold 16px;");

    ui->btnCancelarCliente->setStyleSheet("color: black;"
                                               "background-color: #00ff7f;"
                                               "border-style: outset;"
                                               "border-width: 2px;"
                                               "border-radius: 10px;"
                                               "border-color: white;"
                                               "font: bold 16px;");
}

CadastroCliente::~CadastroCliente()
{
    delete ui;
}



void CadastroCliente::on_btnSalvarCliente_clicked()
{
    //pega os valores digitados nos campos e grava nas variáveis criadas
    QString cpf = ui->txtCadastroCliente_CPF->text();
    QString nome = ui->txtCadastroCliente_Nome->text();
    QString endereco = ui->txtCadastroCliente_Endereco->text();
    QString dataNascimento = ui->txtCadastroCliente_DataNascimento->text();
    QString telefone = ui->txtCadastroCliente_Telefone->text();
    QString email = ui->txtCadastroCliente_Email->text();

    //estrutura para gravar os valores gerados acima no Banco de Dados
    QSqlQuery dados;
    dados.prepare("Insert into Clientes (cpfCliente, nomeCliente, enderecoCliente, "
                  "dataNascimentoCliente, telefoneCliente, emailCliente) values ('"+cpf+"', '"+nome+"',"
                                                          "'"+endereco+"', '"+dataNascimento+"', '"+telefone+"', '"+email+"')");
    if(dados.exec()){
        QMessageBox::information(this, "Aviso","Registro salvo com sucesso!");
        this->close();
    }else{
        QMessageBox::information(this, "Atenção!","Não foi possível salvar as informações no Banco de Dados!");
    }
}

void CadastroCliente::on_btnCancelarCliente_clicked()
{
    close();
}
