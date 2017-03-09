#include <QApplication>
#include "mainwindow.h"
#include "dialogconnexion.h"
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QInputDialog>
#include <QTableWidget>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDebug>
#include <QTextCodec>

/**
 * @brief main
 * @param argc
 * @param argv
 * @param This is connection of this application
 * @param With translations
 * @return
 */
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);
    QTranslator myappTranslator;
    QString nomFichier="AppQuestBDD_" + QLocale::system().name()+".qm";
    //qDebug()<<nomFichier;
    QString baseName;
    #ifdef Q_OS_LINUX
            baseName="/usr/share/applications/appQuestBDD/translations/";
    #endif
    #ifdef Q_OS_MACOS
            baseName=QApplication::applicationDirPath()+QLatin1String("/../Resources/translations/"); // path defaults to app dir.
    #endif
    #ifdef Q_OS_DARWIN
            baseName=QApplication::applicationDirPath()+QLatin1String("/translations/"); // path defaults to app dir.
    #endif
    #ifdef Q_OS_WIN
            baseName=QApplication::applicationDirPath();
    #endif
    myappTranslator.load(baseName+nomFichier);
    //myappTranslator.load("/usr/share/applications/gapmea/translations/gapMea_" + QLocale::system().name()+".qm");
    a.installTranslator(&myappTranslator);
    //qDebug()<<QLibraryInfo::location(QLibraryInfo::TranslationsPath);


    DialogConnexion diagConnexion;
    //ouverture du dialogue connexion
    while(diagConnexion.exec()==QDialog::Accepted)
    {
        //récupération des valeurs de login et password
        QString login = diagConnexion.getLogin();
        QString password = diagConnexion.getPassword();

        //utilisation des variables login et password pour la connexion à mysql
        QSqlDatabase maBase=QSqlDatabase::addDatabase("QMYSQL");
        maBase.setHostName("localhost");
        maBase.setUserName(login);
        maBase.setPassword(password);
        //si la connexion marche, le programme se dirige sur MainWindow
        if(maBase.open()){
            MainWindow w;
            w.show();
            return a.exec();
        }else{
            //Si non il affiche un message d'erreur
            QMessageBox msgBox;
            msgBox.setText("Error, Restart");
            msgBox.exec();
            //QMessageBox::critical(this, "Erreur", "Erreur dans la connexion");
        }
    }
}
