#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include <QDialog>

namespace Ui {
class DialogAbout;
}

class DialogAbout : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAbout(QWidget *parent = 0);
    ~DialogAbout();
    
private slots:
    /**
     * @brief on_pushButton_clicked
     * @param Quit the window
     */
    void on_pushButton_clicked();

private:
    Ui::DialogAbout *ui;
};

#endif // DIALOGABOUT_H
