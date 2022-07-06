#ifndef TELAPRINCIPAL_H
#define TELAPRINCIPAL_H

#include <QDialog>

#include <QtSql>
#include <QMessageBox>
#include <QTableWidget>

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

private slots:
    void on_txtPesquisarFuncionario_textChanged(const QString &arg1);

private:
    Ui::TelaPrincipal *ui;
};

#endif // TELAPRINCIPAL_H
