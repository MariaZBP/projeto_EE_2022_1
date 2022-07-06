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
        ui->lblEditarFuncionario_ID->setText(dados.value(0).toString());
        ui->txtEditarFuncionario_CPF->setText(dados.value(1).toString());
        ui->txtEditarFuncionario_Nome->setText(dados.value(2).toString());

        QString salarioTexto;
        //formato tipo moeda
        auto formato = QLocale("de_DE");
        double valorMoeda = dados.value(3).toDouble();
        //mostrar com uma máscara de moeda na tela de cadastro
        //f = double - moeda com 2 casas decimais
        salarioTexto = formato.toString(valorMoeda, 'f', 2);
        ui->txtEditarFuncionario_Salario->setText("R$ " + salarioTexto);

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

void EditarFuncionario::on_txtEditarFuncionario_Salario_editingFinished()
{
    QString salarioTexto;

    //formato tipo moeda
    auto formato = QLocale("de_DE");
    double valorMoeda = ui->txtEditarFuncionario_Salario->text().toDouble();

    //mostrar com uma máscara de moeda na tela de cadastro
    //f = double - moeda com 2 casas decimais
    salarioTexto = formato.toString(valorMoeda, 'f', 2);
    ui->txtEditarFuncionario_Salario->setText("R$ " + salarioTexto);
}

void EditarFuncionario::on_btnSalvarEdicaoFuncionario_clicked()
{
    QString id = ui->lblEditarFuncionario_ID->text();
    QString cpf = ui->txtEditarFuncionario_CPF->text();
    QString nome = ui->txtEditarFuncionario_Nome->text();

    QString salarioSemVirgula;
    salarioSemVirgula = ui->txtEditarFuncionario_Salario->text();
    //antes = R$ 1.235,10
    //depois = 1235.10
    salarioSemVirgula.replace(0, 3, "");
    salarioSemVirgula.replace(".", "");
    salarioSemVirgula.replace(",", ".");
    QString salario = salarioSemVirgula;

    QString departamento = ui->cmbEditarFuncionario_Departamento->currentText();
    QString dataNascimento = ui->txtEditarFuncionario_DataNascimento->text();
    QString telefone = ui->txtEditarFuncionario_Telefone->text();
    QString email = ui->txtEditarFuncionario_Email->text();

    //grava os dados da alteração no BD
    QSqlQuery dados;
    dados.prepare("Update Funcionarios set idFuncionario='"+id+"',"
                                           "cpfFuncionario='"+cpf+"',"
                                           "nomeFuncionario='"+nome+"',"
                                           "salarioFuncionario='"+salario+"',"
                                           "dataNascimentoFuncionario='"+dataNascimento+"',"
                                           "departamentoFuncionario='"+departamento+"',"
                                           "telefoneFuncionario='"+telefone+"',"
                                           "emailFuncionario='"+email+"' where idFuncionario="+QString::number(idSelecionado));

    if(dados.exec()){
        this->close();
    }else{
        QMessageBox::critical(this, "Atenção", "Erro ao salvar as alterações!");
    }
}

void EditarFuncionario::on_btnCancelarEdicaoFuncionario_clicked()
{
    close();
}
