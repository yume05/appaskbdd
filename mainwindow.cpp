#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QInputDialog>
#include <QTableWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include <QMessageBox>
#include <QColor>
#include <QSqlRecord>
#include <QSqlError>
#include <QFileDialog>
#include "dialogabout.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //appel de la méthode chargeLesContacts dés l'ouverture de l'application
    chargeLesBDD();
    ui->pushButtonHist->setEnabled(false);


}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::chargeLesBDD
 */
void MainWindow::chargeLesBDD()
{
    qDebug()<<"void MainWindow::chargeLesBDD()";
    QSqlQuery req ("SHOW DATABASES");
            while (req.next())
            {
                QString nomBDD = req.value(0).toString();
                ui->comboBoxBDD->addItem(nomBDD);
             }
}

/**
 * @brief MainWindow::on_comboBoxBDD_currentIndexChanged
 * @param arg1
 */
void MainWindow::on_comboBoxBDD_currentIndexChanged(const QString &arg1)
{
    qDebug()<<"void MainWindow::on_comboBoxBDD_currentIndexChanged(const QString &arg1)";
    ui->comboBoxTables->clear();
    int nbreDeLigne = ui->comboBoxBDD->count();
    if(nbreDeLigne>0){
            //Récupère le numéro de la ligne sélectionner
                QString nomBDD = ui->comboBoxBDD->currentText();
                QSqlQuery reqBDD ("USE "+nomBDD);
                reqBDD.exec();
                QSqlQuery reqTables ("show tables");
                        while (reqTables.next())
                        {
                            QString nomTables = reqTables.value(0).toString();
                            ui->comboBoxTables->addItem(nomTables);
                        }
               }
}

/**
 * @brief MainWindow::on_comboBoxTables_currentIndexChanged
 * @param arg1
 */
void MainWindow::on_comboBoxTables_currentIndexChanged(const QString &arg1)
{
    qDebug()<<"void MainWindow::on_comboBoxTables_currentIndexChanged(const QString &arg1)";
    ui->listWidgetChamps->clear();
   //Récupère le numéro de la ligne sélectionner
        QString nomTable = ui->comboBoxTables->currentText();
        QSqlQuery reqChamps ("show fields from "+nomTable);

                while (reqChamps.next())
                {
                    QString nomChamps = reqChamps.value(0).toString();
                    ui->listWidgetChamps->addItem(nomChamps);
                }

}

/**
 * @brief MainWindow::on_textEditRequete_textChanged
 */
void MainWindow::on_textEditRequete_textChanged()
{
    qDebug()<<"void MainWindow::on_textEditRequete_textChanged()";
    //Récupérer le nom de la base de donnée sélectionné
    QString nomBDD = ui->comboBoxBDD->currentText();
    QSqlQuery reqBDD ("USE "+nomBDD);
    reqBDD.exec();
    requete = ui->textEditRequete->toPlainText();
    QSqlQuery req (requete);
    // Executer la requête
    if(req.exec()){
        if(!requete.endsWith(";"))
            requete = requete+";";
        //Si la requête est vrai, afficher le résultat
        ui->pushButtonHist->setEnabled(true);
        ui->pushButtonVerif->setStyleSheet("color: green;");
        couleur = "green";


        QSqlRecord nbreDeColonne = req.record();
        ui->tableWidgetResultat->setRowCount(0);
        int row =0;
        while (req.next())
        {
            ui->tableWidgetResultat->setColumnCount(nbreDeColonne.count());
            row++;
            ui->tableWidgetResultat->setRowCount(row);
            for(int colonne=0;colonne<nbreDeColonne.count();colonne++){
                QString champs = req.value(colonne).toString();

                ui->tableWidgetResultat->setItem(row-1, colonne, new QTableWidgetItem(champs));
            }
          }
    // Si la requête est fausse, afficher l'erreur
    }else{

        errorText = req.lastError().text();
        errorNumber = QString::number( req.lastError().number() );
        couleur = "red";
        ui->pushButtonVerif->setStyleSheet("color: red;");
        ui->pushButtonHist->setEnabled(false);
    }
}

/**
 * @brief MainWindow::on_pushButtonVerif_clicked
 */
void MainWindow::on_pushButtonVerif_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonVerif_clicked()";
    // Si le bouton "?" est vert, alors la requête est bonne
    if(couleur == "green") {
        QMessageBox::about(this, tr("About"), tr("Query ok !"));
    // Si le bouton "?" est rouge, alors la requête n'est pas bonne, afficher l'erreur
    }else if(couleur == "red"){
        QMessageBox::critical(this, tr("Error code : ")+errorNumber, errorText);
    }
}

/**
 * @brief MainWindow::on_listWidgetSelectReq_currentRowChanged
 * @param currentRow
 */
void MainWindow::on_listWidgetSelectReq_currentRowChanged(int currentRow)
{
    qDebug()<< "void MainWindow::on_listWidgetSelectReq_currentRowChanged(int currentRow)";
    // Récuperer la requête sélectionnée et l'executer dans la saisie
    ui->textEditRequete->setPlainText(ui->listWidgetSelectReq->currentItem()->text());

}

/**
 * @brief MainWindow::on_pushButtonHist_clicked
 */
void MainWindow::on_pushButtonHist_clicked()
{
    qDebug()<< "void MainWindow::on_pushButtonHist_clicked()";

    // Si la requête n'existe pas dans l'historique on peut l'ajouter
    if(ui->listWidgetSelectReq->findItems(requete , Qt::MatchExactly).count() == 0){
        qDebug()<< requete;
                ui->listWidgetSelectReq->addItem(requete);

        }
   }

/**
 * @brief MainWindow::on_pushButtonSave_clicked
 */
void MainWindow::on_pushButtonSave_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonSave_clicked()";
    // Enregistrement dans un fichier texte de l'historique des requetes
    // Obtention du nom complet du fichier où sauvegarder l'historique
    QString nameFile = QFileDialog::getSaveFileName(this, tr("Save File"), "",  tr("Sql File (*.sql *.txt *.qcl)"));
    // Création du fichier avec le nom complet
    QFile monFichier(nameFile);
    // Ouverture du fichier en création
    monFichier.open(QIODevice::WriteOnly);
    // Création d'un text stream associé au fichier
    QTextStream tsHistoric(&monFichier);
    // Pour chaque ligne de l'historique, l'ecrire dans le fichier avec un saut de ligne à la fin
    for(int row = 0; row<ui->listWidgetSelectReq->count(); row++){
        tsHistoric << ui->listWidgetSelectReq->item(row)->text()<<endl;
    }
    // Fermeture du fichier
    monFichier.close();
    // Fichier enregistré
    ui->statusBar->showMessage(tr("File successfuly saved !"));
}

/**
 * @brief MainWindow::on_pushButtonExport_clicked
 */
void MainWindow::on_pushButtonExport_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonExport_clicked()";
    // Enregistrement dans un fichier texte du résultat de la requête
    // Obtention du nom complet du fichier où sauvegarder le résultat
    QString nomFichier=QFileDialog::getSaveFileName(this, tr("Save"),"",tr("Text(*.csv)"));
    // Création du fichier avec le nom complet
    QFile monFichier(nomFichier);
    if (!monFichier.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    // Création d'un text stream associé au fichier
    QTextStream tsExport(&monFichier);
    int nbrRow = ui->tableWidgetResultat->rowCount();
    int nbrColumn = ui->tableWidgetResultat->columnCount();
    for(int noLigne=0;noLigne<nbrRow;noLigne++)
    {
        for(int noCol=0;noCol<nbrColumn;noCol++)
        {
            //Pour chaque colonne de chaque ligne, ecrire le texte dans le fichier
            tsExport << ui->tableWidgetResultat->item(noLigne,noCol)->text() <<";";
        }
        tsExport << "\n";
    }
}

/**
 * @brief MainWindow::on_action_Load_triggered
 */
void MainWindow::on_action_Load_triggered()
{
    qDebug()<<"void MainWindow::on_action_Load_triggered()";

    // Obtenir le nom complet du fichier texte que l'on va charger
    QString nameFile = QFileDialog::getOpenFileName(this, tr("Open File"), "", "Text files (*.sql *.qcl *.txt)");
    QFile monFichier(nameFile);
    // Ouvrir le fichier en lecture uniquement
    monFichier.open(QIODevice::ReadOnly);
    // Créataion d'un text stream associé au fichier
    QTextStream tsHistoric(&monFichier);
    //ui->listWidgetSelectReq->clear();
    QString line = "";
     while (!tsHistoric.atEnd()) {
         //Récuperer ligne par ligne du text stream
         line = line+" "+tsHistoric.readLine();
         if(line.endsWith(";")){
             qDebug()<<line;//Et inserer la ligne dans l'historique
             ui->listWidgetSelectReq->addItem(line);
             line = "";
         }
     }
     ui->statusBar->showMessage(tr("File successfuly Load!"));
}

/**
 * @brief MainWindow::on_action_Quit_triggered
 */
void MainWindow::on_action_Quit_triggered()
{
    qDebug()<<"void MainWindow::on_action_Quit_triggered()";
    //demander la confirmation par une question.
    int ret = (QMessageBox::question(this, tr("AppQuestBDD"), tr("Are you sur to quit this application ?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes));

    //Si la réponse à la question est positive, sortir de l'application
    if (ret == QMessageBox::Yes) { close(); }
}

/**
 * @brief MainWindow::on_action_About_triggered
 */
void MainWindow::on_action_About_triggered()
{
    qDebug()<<"void MainWindow::on_action_About_triggered()";
    DialogAbout info;
    info.exec();
}
