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
