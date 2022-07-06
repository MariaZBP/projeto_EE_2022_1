#ifndef TELAPRINCIPAL_H
#define TELAPRINCIPAL_H

#include <QDialog>

#include <QtSql>
#include <QMessageBox>

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

private:
    Ui::TelaPrincipal *ui;
};

#endif // TELAPRINCIPAL_H
