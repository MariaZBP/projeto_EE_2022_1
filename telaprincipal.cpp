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
}
