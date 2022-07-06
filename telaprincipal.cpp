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

    carregarDadosFuncionarios();
}

TelaPrincipal::~TelaPrincipal()
{
    delete ui;
}

void TelaPrincipal::carregarDadosFuncionarios(){

    //limpa a tableWidgetFuncionario
    limparTableWidGet(ui->tableWidgetFuncionario);

    //pega os dados do BD e exibe na tableWidgetFuncionario
    QSqlQuery pegaDados;
    pegaDados.prepare("SELECT * FROM Funcionarios");
    if(pegaDados.exec()){
        int linha = 0;
        ui->tableWidgetFuncionario->setColumnCount(8);
        while(pegaDados.next()){
            ui->tableWidgetFuncionario->insertRow(linha);
            for(int i = 0; i < 8; i++){
                ui->tableWidgetFuncionario->setItem(linha, i, new QTableWidgetItem(pegaDados.value(i).toString()));
            }
            ui->tableWidgetFuncionario->setRowHeight(linha, 40);
            linha++;

            //exibe o somatório dos salários
            QString salarioTexto;
            //formato tipo moeda
            auto formato = QLocale("de_DE");
            double valorMoeda = somarSalarios(ui->tableWidgetFuncionario, 3);
            //mostrar com uma máscara de moeda na tela de cadastro
            //f = double - moeda com 2 casas decimais
            salarioTexto = formato.toString(valorMoeda, 'f', 2);
            ui->lblTotalSalario->setText("Somatório dos Salários = R$ " + salarioTexto);

            //exibe maior salário
            QString salarioTexto2;
            double valorMoeda2 = maiorSalario(ui->tableWidgetFuncionario, 3);
            salarioTexto2 = formato.toString(valorMoeda2, 'f', 2);
            ui->lblMaiorSalario->setText("Maior Salário = R$ " + salarioTexto2);
        }

        //títulos da tableWidgetFuncionario
        QStringList titulos = {"ID", "CPF", "Nome", "Salário", "Departamento", "Data Nascimento", "Telefone", "Email"};
        ui->tableWidgetFuncionario->setHorizontalHeaderLabels(titulos);

        //oculta os números das linhas que ficaram na esquerda
        ui->tableWidgetFuncionario->verticalHeader()->setVisible(false);

        //ajusta a largura das colunas da tableWidgetFuncionario
        ui->tableWidgetFuncionario->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
        ui->tableWidgetFuncionario->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);

        //desabilita a edição dos dados direto na tableWidgetFuncionario
        ui->tableWidgetFuncionario->setEditTriggers(QAbstractItemView::NoEditTriggers);

        //seleciona a linha inteira da tableWidgetFuncionario
        ui->tableWidgetFuncionario->setSelectionBehavior(QAbstractItemView::SelectRows);

        //mudar a cor dos títulos da tableWidgetFuncionario
        ui->tableWidgetFuncionario->setStyleSheet("QHeaderView::section {color: white; background-color: #55aa7f}");

    }else{
        QMessageBox::information(this,"Atenção","Erro ao carregar os dados dos funcionários!");
    }
}

void TelaPrincipal::limparTableWidGet(QTableWidget *limpaTW){
    while(limpaTW->rowCount() > 0){
        //remove até não haver mais nenhuma linha
        limpaTW->removeRow(0);
    }
}

void TelaPrincipal::on_txtPesquisarFuncionario_textChanged(const QString &arg1)
{
    QString pesquisa;
    limparTableWidGet(ui->tableWidgetFuncionario);
    QString textoPesquisa = ui->txtPesquisarFuncionario->text();

    //filtra o tipo da pesquisa: cpf, nome ou departamento
    if(textoPesquisa == ""){
        if(ui->rdCPF->isChecked()){
            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios order by cpfFuncionario";
        }else if(ui->rdNome->isChecked()){
            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios order by nomeFuncionario";
        }else{
            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios order by departamentoFuncionario";
        }
    }else{
        if(ui->rdCPF->isChecked()){
            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios where cpfFuncionario="+textoPesquisa+" order by cpfFuncionario";
        }else if(ui->rdNome->isChecked()){
            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios where nomeFuncionario like '%"+textoPesquisa+"%' order by nomeFuncionario";
        }else{
            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios where departamentoFuncionario like '%"+textoPesquisa+"%' order by departamentoFuncionario";
        }
    }

    //pesquisar os dados na tabela
    int linha = 0;
    QSqlQuery pegaDados;
    pegaDados.prepare(pesquisa);
    if(pegaDados.exec()){
        while(pegaDados.next()){
            ui->tableWidgetFuncionario->insertRow(linha);
            for(int i = 0; i < 8; i++){
                ui->tableWidgetFuncionario->setItem(linha, i, new QTableWidgetItem(pegaDados.value(i).toString()));
            }
            ui->tableWidgetFuncionario->setRowHeight(linha, 40);
            linha++;

            //exibe o somatório dos salários
            QString salarioTexto;
            //formato tipo moeda
            auto formato = QLocale("de_DE");
            double valorMoeda = somarSalarios(ui->tableWidgetFuncionario, 3);
            //mostrar com uma máscara de moeda na tela de cadastro
            //f = double - moeda com 2 casas decimais
            salarioTexto = formato.toString(valorMoeda, 'f', 2);
            ui->lblTotalSalario->setText("Somatório dos Salários = R$ " + salarioTexto);

            //exibe maior salário
            QString salarioTexto2;
            double valorMoeda2 = maiorSalario(ui->tableWidgetFuncionario, 3);
            salarioTexto2 = formato.toString(valorMoeda2, 'f', 2);
            ui->lblMaiorSalario->setText("Maior Salário = R$ " + salarioTexto2);
        }
    }else{
        QMessageBox::information(this,"Atenção!", "Erro ao pesquisar funcionário!");
    }
}

void TelaPrincipal::on_btnCadastrarFuncionario_clicked()
{
    CadastroFuncionario abreFormularioCadastro;
    abreFormularioCadastro.exec();

    //depois que cadastrar um funcionário, carrega os dados novamente
    carregarDadosFuncionarios();
}

void TelaPrincipal::on_btnExcluirFuncionario_clicked()
{
    //começa da linha onde está selecionada
    int linhaAtual = ui->tableWidgetFuncionario->currentRow();
    QString idSelecionado = ui->tableWidgetFuncionario->item(linhaAtual, 0)->text();
    QSqlQuery bancoDados;
    bancoDados.prepare("Delete from Funcionarios where idFuncionario="+idSelecionado);
    if(bancoDados.exec()){
        ui->tableWidgetFuncionario->removeRow(linhaAtual);
        QMessageBox::information(this,"Aviso!","Funcionário excluído com sucesso!");
    }else{
        QMessageBox::information(this,"Atenção!","Erro ao excluir o funcionário!");
    }
}

void TelaPrincipal::on_tableWidgetFuncionario_cellDoubleClicked(int row, int column)
{
    int linhaAtual = ui->tableWidgetFuncionario->currentRow();
    int idFuncionario = ui->tableWidgetFuncionario->item(linhaAtual, 0)->text().toInt();
    EditarFuncionario dadosFuncionario(this, idFuncionario);
    dadosFuncionario.exec();
    carregarDadosFuncionarios();

}

double TelaPrincipal::somarSalarios(QTableWidget *tabela, int coluna){
    int totalLinhas;
    double total = 0;
    totalLinhas = tabela->rowCount();
    for(int linha = 0; linha < totalLinhas; linha++){
        total += tabela->item(linha, coluna)->text().toDouble();
    }
    return total;
}

double TelaPrincipal::maiorSalario(QTableWidget *tabela, int coluna){
    int totalLinhas;
    QVector<double> salario;
    totalLinhas = tabela->rowCount();
    for(int linha = 0; linha < totalLinhas; linha++){
        salario.push_back(tabela->item(linha, coluna)->text().toDouble());
    }
    double maiorSalario = salario[0];
    for(int i = 1; i < salario.size(); i++){
        if(salario.at(i) > maiorSalario){
            maiorSalario = salario.at(i);
        }
    }
    return maiorSalario;
}
