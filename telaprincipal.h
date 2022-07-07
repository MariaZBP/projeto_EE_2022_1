#ifndef TELAPRINCIPAL_H
#define TELAPRINCIPAL_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QTableWidget>
#include "cadastrofuncionario.h"
#include "editarfuncionario.h"
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include "cadastrocliente.h"
#include "editarcliente.h"

namespace Ui {
class TelaPrincipal;
}

class TelaPrincipal : public QDialog
{
    Q_OBJECT

public:
    explicit TelaPrincipal(QWidget *parent = nullptr);
    ~TelaPrincipal();
    void carregarDadosFuncionarios();
    void limparTableWidGet(QTableWidget *limpaTW);
    double somarSalarios(QTableWidget *tabela, int coluna);
    double maiorSalario(QTableWidget *tabela, int coluna);
    void carregarDadosClientes();

private slots:
    void on_txtPesquisarFuncionario_textChanged(const QString &arg1);
    void on_btnCadastrarFuncionario_clicked();
    void on_btnExcluirFuncionario_clicked();
    void on_tableWidgetFuncionario_cellDoubleClicked(int row, int column);
    void on_btnExportarExcelFuncionario_clicked();
    void on_txtPesquisarCliente_textChanged(const QString &arg1);
    void on_btnCadastrarCliente_clicked();
    void on_btnExcluirCliente_clicked();
    void on_tableWidgetCliente_cellDoubleClicked(int row, int column);

private:
    QString getValueAt(int linha, int coluna);
    Ui::TelaPrincipal *ui;
};

#endif // TELAPRINCIPAL_H
