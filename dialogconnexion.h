#ifndef DIALOGCONNEXION_H
#define DIALOGCONNEXION_H

#include <QDialog>

namespace Ui {
class DialogConnexion;
}

class DialogConnexion : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogConnexion(QWidget *parent = 0);
    ~DialogConnexion();

    /**
     * @brief getLogin
     * @return
     */
    QString getLogin();

    /**
     * @brief getPassword
     * @return
     */
    QString getPassword();

    /**
     * @brief getErreur
     * @return
     */
    QString getErreur();
    
private:
    Ui::DialogConnexion *ui;
};

#endif // DIALOGCONNEXION_H
