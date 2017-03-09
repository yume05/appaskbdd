#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @param parent
     * @param chargeLesBDD : Load Databases of user
     * @param couleur : This is color of button "?"
     * @param requete : This is request
     * @param errorText : This is error text of request
     * @param errorNumber : This is error number of request
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void chargeLesBDD();

    QString couleur;
    QString requete;
    QString errorText;
    QString errorNumber;
    

private slots:

    /**
     * @brief on_comboBoxBDD_currentIndexChanged
     * Combo box with all databases of user
     * @param arg1
     */
    void on_comboBoxBDD_currentIndexChanged(const QString &arg1);

    /**
     * @brief on_comboBoxTables_currentIndexChanged
     * Combo box with all tables of database selected
     * @param arg1
     */
    void on_comboBoxTables_currentIndexChanged(const QString &arg1);

    /**
     * @brief on_textEditRequete_textChanged
     * Enter Request and execute
     */
    void on_textEditRequete_textChanged();

    /**
     * @brief on_pushButtonVerif_clicked
     * If button "?" it's green, so query it's true,
     * Or if false, button it's red
     */
    void on_pushButtonVerif_clicked();

    /**
     * @brief on_listWidgetSelectReq_currentRowChanged
     * Execute the query select
     * @param currentRow
     */
    void on_listWidgetSelectReq_currentRowChanged(int currentRow);

    /**
     * @brief on_pushButtonHist_clicked
     */
    void on_pushButtonHist_clicked();

    /**
     * @brief on_pushButtonSave_clicked
     * Save query in the historic
     */
    void on_pushButtonSave_clicked();

    /**
     * @brief on_pushButtonExport_clicked
     * Export the result of query in file csv format
     */
    void on_pushButtonExport_clicked();

    /**
     * @brief on_action_Load_triggered
     * Load file in query history
     */
    void on_action_Load_triggered();

    /**
     * @brief on_action_Quit_triggered
     * Quit application
     */
    void on_action_Quit_triggered();

    /**
     * @brief on_action_About_triggered
     * About autor of application
     */
    void on_action_About_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
