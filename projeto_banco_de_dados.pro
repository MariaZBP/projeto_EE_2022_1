#-------------------------------------------------
#
# Project created by QtCreator 2022-07-06T09:53:43
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projeto_banco_de_dados
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    telaprincipal.cpp \
    cadastrofuncionario.cpp \
    editarfuncionario.cpp \
    cadastrocliente.cpp

HEADERS += \
        mainwindow.h \
    telaprincipal.h \
    cadastrofuncionario.h \
    editarfuncionario.h \
    cadastrocliente.h

FORMS += \
        mainwindow.ui \
    telaprincipal.ui \
    cadastrofuncionario.ui \
    editarfuncionario.ui \
    cadastrocliente.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imagens.qrc

DISTFILES += \
    ../Imagens/banco_de_dados.jpg \
    ../Imagens/imagem3.jpg \
    ../Imagens/images (1).jpg \
    ../Imagens/telaLogin.jpg \
    ../Imagens/cancelar.png \
    ../Imagens/excel.png \
    ../Imagens/excluir.png \
    ../Imagens/novo.png \
    ../Imagens/salvar.png \
    ../Imagens/banco_de_dados.jpg \
    ../Imagens/imagem3.jpg \
    ../Imagens/images (1).jpg \
    ../Imagens/telaLogin.jpg \
    ../Imagens/cancelar.png \
    ../Imagens/excel.png \
    ../Imagens/excluir.png \
    ../Imagens/novo.png \
    ../Imagens/salvar.png
