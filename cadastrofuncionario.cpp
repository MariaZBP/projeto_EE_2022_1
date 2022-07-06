#include "cadastrofuncionario.h"
#include "ui_cadastrofuncionario.h"

CadastroFuncionario::CadastroFuncionario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CadastroFuncionario)
{
    ui->setupUi(this);

    //inserindo máscaras nos campos
    ui->txtCadastroFuncionario_CPF->setInputMask("000.000.000-00");
    ui->txtCadastroFuncionario_Telefone->setInputMask("(99) 99999-9999");
    ui->txtCadastroFuncionario_DataNascimento->setInputMask("99/99/9999");

}

CadastroFuncionario::~CadastroFuncionario()
{
    delete ui;
}

void CadastroFuncionario::on_btnSalvarFuncionario_clicked()
{
    //pega os valores digitados nos campos e grava nas variáveis criadas
    QString cpf = ui->txtCadastroFuncionario_CPF->text();
    QString nome = ui->txtCadastroFuncionario_Nome->text();

    QString salarioSemVirgula = ui->txtCadastroFuncionario_Salario->text();

    //tratamento da variável salário para poder gravar corretamente no BD
    //antes = R$ 1.235,10
    //depois = 1235.10
    salarioSemVirgula.replace(0, 3, ""); //remove os 3 primeiros caracteres R$espaço
    salarioSemVirgula.replace(".", ""); //substitui o ponto pelo vazio
    salarioSemVirgula.replace(",", "."); //substitui a vírgula por ponto

    QString salario = salarioSemVirgula;
    QString departamento = ui->cmbCadastroFuncionario_Departamento->currentText();
    QString dataNascimento = ui->txtCadastroFuncionario_DataNascimento->text();
    QString telefone = ui->txtCadastroFuncionario_Telefone->text();
    QString email = ui->txtCadastroFuncionario_Email->text();

    //estrutura para gravar os valores gerados acima no Banco de Dados
    QSqlQuery dados;
    dados.prepare("Insert into Funcionarios (cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, "
                  "dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario) values ('"+cpf+"', '"+nome+"','"+salario+"',"
                                                          "'"+departamento+"', '"+dataNascimento+"', '"+telefone+"', '"+email+"')");
    if(dados.exec()){
        QMessageBox::information(this, "Aviso","Registro salvo com sucesso!");
        this->close();
    }else{
        QMessageBox::information(this, "Atenção!","Não foi possível salvar as informações no Banco de Dados!");
    }
}

void CadastroFuncionario::on_txtCadastroFuncionario_Salario_editingFinished()
{
    QString salarioTexto;

    //formato tipo moeda
    auto formato = QLocale("de_DE");
    double valorMoeda = ui->txtCadastroFuncionario_Salario->text().toDouble();

    //mostrar com uma máscara de moeda na tela de cadastro
    //f = double - moeda com 2 casas decimais
    salarioTexto = formato.toString(valorMoeda, 'f', 2);
    ui->txtCadastroFuncionario_Salario->setText("R$ " + salarioTexto);
}
