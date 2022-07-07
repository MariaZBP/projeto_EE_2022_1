#ifndef CADASTROCLIENTE_H
#define CADASTROCLIENTE_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class CadastroCliente;
}

class CadastroCliente : public QDialog
{
    Q_OBJECT

public:
    explicit CadastroCliente(QWidget *parent = nullptr);
    ~CadastroCliente();

private slots:
    void on_btnSalvarCliente_clicked();
    void on_btnCancelarCliente_clicked();

private:
    Ui::CadastroCliente *ui;
};

#endif // CADASTROCLIENTE_H
