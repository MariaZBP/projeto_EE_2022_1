#ifndef CADASTROFUNCIONARIO_H
#define CADASTROFUNCIONARIO_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class CadastroFuncionario;
}

class CadastroFuncionario : public QDialog
{
    Q_OBJECT

public:
    explicit CadastroFuncionario(QWidget *parent = nullptr);
    ~CadastroFuncionario();

private slots:
    void on_btnSalvarFuncionario_clicked();
    void on_txtCadastroFuncionario_Salario_editingFinished();
    void on_btnCancelarFuncionario_clicked();

private:
    Ui::CadastroFuncionario *ui;
};

#endif // CADASTROFUNCIONARIO_H
