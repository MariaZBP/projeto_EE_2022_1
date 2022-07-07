#include "telaprincipal.h"
#include "ui_telaprincipal.h"

TelaPrincipal::TelaPrincipal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaPrincipal)
{
    ui->setupUi(this);

    //-------------------personalização da aba funcionários--------------------------------
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

    ui->btnExportarExcelFuncionario->setStyleSheet("color: black;"
                                             "background-color: #00aaff;"
                                             "border-style: outset;"
                                             "border-width: 2px;"
                                             "border-radius: 10px;"
                                             "border-color: white;"
                                             "font: bold 16px;");

    ui->comboBoxColunaFiltro->setStyleSheet("color: black;"
                                            "background-color: #aaff7f;"
                                            "selection-color: black;"
                                            "selection-background-color: #aaff7f;");

    //-------------------personalização da aba clientes--------------------------------
    ui->txtPesquisarCliente->setStyleSheet("color: black;"
                                               "background-color: #aaff7f;"
                                               "selection-color: black;"
                                               "selection-background-color: #aaff7f;");

    ui->btnCadastrarCliente->setStyleSheet("color: black;"
                                               "background-color: #00ff7f;"
                                               "border-style: outset;"
                                               "border-width: 2px;"
                                               "border-radius: 10px;"
                                               "border-color: white;"
                                               "font: bold 16px;");

    ui->btnExcluirCliente->setStyleSheet("color: black;"
                                             "background-color: #00ff7f;"
                                             "border-style: outset;"
                                             "border-width: 2px;"
                                             "border-radius: 10px;"
                                             "border-color: white;"
                                             "font: bold 16px;");

    ui->btnExportarExcelCliente->setStyleSheet("color: black;"
                                             "background-color: #00aaff;"
                                             "border-style: outset;"
                                             "border-width: 2px;"
                                             "border-radius: 10px;"
                                             "border-color: white;"
                                             "font: bold 16px;");

    ui->comboBoxColunaFiltroCliente->setStyleSheet("color: black;"
                                            "background-color: #aaff7f;"
                                            "selection-color: black;"
                                            "selection-background-color: #aaff7f;");

    //mudar a cor do texto
    QPalette paleta = ui->lblTotalSalario->palette();
    paleta.setColor(ui->lblTotalSalario->foregroundRole(), Qt::blue);
    ui->lblTotalSalario->setPalette(paleta);
    ui->lblMaiorSalario->setPalette(paleta);
    ui->lblTotalRegistrosFuncionarios->setPalette(paleta);
    ui->lblTotalRegistrosClientes->setPalette(paleta);

    carregarDadosFuncionarios();
    carregarDadosClientes();
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

        //exibe o total de registros
        ui->lblTotalRegistrosFuncionarios->setText("Registros encontrados: " + QString::number(linha));

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
    QString colunaFiltro = ui->comboBoxColunaFiltro->currentText();
    QString textoPesquisa = ui->txtPesquisarFuncionario->text();

    //filtro para todas as colunas
    if(colunaFiltro == "ID"){
        pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios where idFuncionario like '%"+textoPesquisa+"%'";
    }else if(colunaFiltro == "CPF"){
        pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios where cpfFuncionario like '%"+textoPesquisa+"%'";
    }else if(colunaFiltro == "Nome"){
        pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios where nomeFuncionario like '%"+textoPesquisa+"%'";
    }else if(colunaFiltro == "Salário"){
        pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios where salarioFuncionario like '%"+textoPesquisa+"%'";
    }else if(colunaFiltro == "Departamento"){
        pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios where departamentoFuncionario like '%"+textoPesquisa+"%'";
    }else if(colunaFiltro == "Data de Nascimento"){
        pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios where dataNascimentoFuncionario like '%"+textoPesquisa+"%'";
    }else if(colunaFiltro == "Telefone"){
        pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios where telefoneFuncionario like '%"+textoPesquisa+"%'";
    }else if(colunaFiltro == "Email"){
        pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios where emailFuncionario like '%"+textoPesquisa+"%'";
    }else{
        pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario from Funcionarios where idFuncionario like '%"+textoPesquisa+"%'";
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

        //exibe o total de registros
        ui->lblTotalRegistrosFuncionarios->setText("Registros encontrados: " + QString::number(linha));

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

void TelaPrincipal::on_btnExportarExcelFuncionario_clicked()
{
    //caminha arquivo para salvar
    auto nomeArquivo = QFileDialog::getSaveFileName(this, "Salvar", QDir::rootPath(), "CSV File (*.csv)");
    if(nomeArquivo.isEmpty()){
        //fecha se não estiver selecionado o caminho
        return;
    }
    //QIODevice::WriteOnly = o arquivo está aberto para escrita
    //QIODevice::Text = ao ler e escrever pula sempre para próxima linha
    QFile file(nomeArquivo);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    //a classe QTextStream cria uma interface amigável para leitura e escrita dos dados
    QTextStream arquivoExcel(&file);
    //contagem de linhas e colunas preenchidas
    const int quantidadeLinhas = ui->tableWidgetFuncionario->rowCount();
    const int quantidadeColunas= ui->tableWidgetFuncionario->columnCount();
    for(int linha = 0; linha < quantidadeLinhas; linha++){
        //pega as informações
        arquivoExcel << getValueAt(linha, 0);
        for(int coluna = 1; coluna < quantidadeColunas; coluna++){
            //inserindo as informações no excel
            arquivoExcel << "," << getValueAt(linha, coluna);
        }
        arquivoExcel << "\n";
    }
    //limpa
    file.flush();
    //fecha o arquivoExcel
    file.close();
    QMessageBox::information(this, "Aviso", "Relatório exportado com sucesso!");

}

//método para pegar os dados da tableWidgetFuncionario
QString TelaPrincipal::getValueAt(int linha, int coluna){
    if(!ui->tableWidgetFuncionario->item(linha, coluna)){
        //se estiver limpa a tableWidgetFuncionario salva o arquivo em branco
        return "";
    }else{
        //retorna as informações da posição da linha e da coluna
        return  ui->tableWidgetFuncionario->item(linha, coluna)->text();
    }
}

void TelaPrincipal::carregarDadosClientes(){

    //limpa a tableWidgetCliente
    limparTableWidGet(ui->tableWidgetCliente);

    //pega os dados do BD e exibe na tableWidgetCliente
    QSqlQuery pegaDados;
    pegaDados.prepare("SELECT * FROM Clientes");
    if(pegaDados.exec()){
        int linha = 0;
        ui->tableWidgetCliente->setColumnCount(7);
        while(pegaDados.next()){
            ui->tableWidgetCliente->insertRow(linha);
            for(int i = 0; i < 7; i++){
                ui->tableWidgetCliente->setItem(linha, i, new QTableWidgetItem(pegaDados.value(i).toString()));
            }
            ui->tableWidgetCliente->setRowHeight(linha, 40);
            linha++;
        }

        ui->lblTotalRegistrosClientes->setText("Registros encontrados: " + QString::number(linha));

        //coloca os títulos na tabela
        QStringList titulos = {"ID", "CPF", "Nome", "Endereço", "Data Nascimento", "Telefone", "E-mail"};

        ui->tableWidgetCliente->setHorizontalHeaderLabels(titulos);

        //oculta os números das linhas que ficaram a esquerda
        ui->tableWidgetCliente->verticalHeader()->setVisible(false);

        //ajusta a largura das colunas
        ui->tableWidgetCliente->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
        ui->tableWidgetCliente->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);

        //desabilita a edição dos dados direto na tableWidgetClientes
        ui->tableWidgetCliente->setEditTriggers(QAbstractItemView::NoEditTriggers);

        //seleciona a linha inteira da tableWidgetClientes
        ui->tableWidgetCliente->setSelectionBehavior(QAbstractItemView::SelectRows);

        //mudar a cor dos títulos da tabela
        ui->tableWidgetCliente->setStyleSheet("QHeaderView::section {color: white; background-color: #55aa7f}");
    }else{
        QMessageBox::information(this, "Atenção", "Erro ao carregar os dados dos clientes!");
    }
}

void TelaPrincipal::on_txtPesquisarCliente_textChanged(const QString &arg1)
{
    QString pesquisa;
    limparTableWidGet(ui->tableWidgetCliente);
    QString colunaFiltro = ui->comboBoxColunaFiltroCliente->currentText();
    QString textoPesquisa = ui->txtPesquisarCliente->text();

    if(colunaFiltro == "ID"){
        //digitando parte do nome o like já trás ele
        //%-> começa em qualquer valor e termina em qualquer valor
        pesquisa = "Select idCliente, cpfCliente, nomeCliente, EnderecoCliente, dataNascimentoCliente, telefoneCliente, emailCliente From Clientes where idCliente like '%"+textoPesquisa+"%'";
    }else if(colunaFiltro == "CPF"){
        pesquisa = "Select idCliente, cpfCliente, nomeCliente, EnderecoCliente, dataNascimentoCliente, telefoneCliente, emailCliente From Clientes where cpfCliente like '%"+textoPesquisa+"%'";
    }else if(colunaFiltro == "Nome"){
        pesquisa = "Select idCliente, cpfCliente, nomeCliente, EnderecoCliente, dataNascimentoCliente, telefoneCliente, emailCliente From Clientes where nomeCliente like '%"+textoPesquisa+"%'";
    }else if(colunaFiltro == "Endereço"){
        pesquisa = "Select idCliente, cpfCliente, nomeCliente, EnderecoCliente, dataNascimentoCliente, telefoneCliente, emailCliente From Clientes where EnderecoCliente like '%"+textoPesquisa+"%'";
    }else if(colunaFiltro == "Data de Nascimento"){
        pesquisa = "Select idCliente, cpfCliente, nomeCliente, EnderecoCliente, dataNascimentoCliente, telefoneCliente, emailCliente From Clientes where dataNascimentoCliente like '%"+textoPesquisa+"%'";
    }else if(colunaFiltro == "Telefone"){
        pesquisa = "Select idCliente, cpfCliente, nomeCliente, EnderecoCliente, dataNascimentoCliente, telefoneCliente, emailCliente From Clientes where telefoneCliente like '%"+textoPesquisa+"%'";
    }else if(colunaFiltro == "Email"){
        pesquisa = "Select idCliente, cpfCliente, nomeCliente, EnderecoCliente, dataNascimentoCliente, telefoneCliente, emailCliente From Clientes where emailCliente like '%"+textoPesquisa+"%'";
    }else{
        pesquisa = "Select idCliente, cpfCliente, nomeCliente, EnderecoCliente, dataNascimentoCliente, telefoneCliente, emailCliente From Clientes where idCliente like '%"+textoPesquisa+"%'";
    }

    //pesquisar os dados na tabela
    int linha = 0;
    QSqlQuery pegaDados;
    pegaDados.prepare(pesquisa);
    if(pegaDados.exec()){
        while(pegaDados.next()){
            //insere a linha de acordo com a variável linha
            ui->tableWidgetCliente->insertRow(linha);
            //passa os itens (linha, coluna, item QTableWidgetItem)
            for(int i = 0; i < 7; i++){
                ui->tableWidgetCliente->setItem(linha, i, new QTableWidgetItem(pegaDados.value(i).toString()));
            }
            ui->tableWidgetCliente->setRowHeight(linha, 40);
            linha++;
        }
        ui->lblTotalRegistrosClientes->setText("Registros encontrados: " + QString::number(linha));
    }else{
        QMessageBox::information(this, "Atenção", "Erro ao encontrar dados dos clientes!");
    }
}

void TelaPrincipal::on_btnCadastrarCliente_clicked()
{
    CadastroCliente abreFormularioCadastro;
    abreFormularioCadastro.exec();

    //depois que cadastrar um cliente, carrega os dados novamente
    carregarDadosClientes();
}

void TelaPrincipal::on_btnExcluirCliente_clicked()
{
    //começa da linha onde está selecionada
    int linhaAtual = ui->tableWidgetCliente->currentRow();
    QString idSelecionado = ui->tableWidgetCliente->item(linhaAtual, 0)->text();
    QSqlQuery bancoDados;
    bancoDados.prepare("Delete from Clientes where idCliente="+idSelecionado);
    if(bancoDados.exec()){
        ui->tableWidgetCliente->removeRow(linhaAtual);
        QMessageBox::information(this,"Aviso!","Cliente excluído com sucesso!");
    }else{
        QMessageBox::information(this,"Atenção!","Erro ao excluir os dados do cliente selecionado!");
    }
}
