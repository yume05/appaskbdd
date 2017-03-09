#include "dialogconnexion.h"
#include "ui_dialogconnexion.h"

DialogConnexion::DialogConnexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnexion)
{
    ui->setupUi(this);
}

DialogConnexion::~DialogConnexion()
{
    delete ui;
}

QString DialogConnexion::getLogin()
{
    return ui->lineEditLogin->text();
}

QString DialogConnexion::getPassword()
{
    return ui->lineEditPassword->text();
}

QString DialogConnexion::getErreur()
{
    return ui->labelErreur->text();
}

