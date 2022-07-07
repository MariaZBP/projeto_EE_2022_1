#ifndef EDITARCLIENTE_H
#define EDITARCLIENTE_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class EditarCliente;
}

class EditarCliente : public QDialog
{
    Q_OBJECT

public:
    explicit EditarCliente(QWidget *parent = nullptr, int alterarCliente_ID = 0);
    ~EditarCliente();

private slots:
    void on_btnSalvarEdicaoCliente_clicked();

    void on_btnCancelarEdicaoCliente_clicked();

private:
    Ui::EditarCliente *ui;
};

#endif // EDITARCLIENTE_H
