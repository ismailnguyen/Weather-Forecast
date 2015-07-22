#ifndef DIALOG_H
#define DIALOG_H
#include "dialog.h"
#include "meteo.h"
#include "condition.h"
#include "xml.h"
#include <QDialog>
#include <QGraphicsScene>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    void afficherMeteo() ;
    ~Dialog();
    

private slots:
    void on_pushButtonRechercher_clicked();

    void on_pushButtonTaille_clicked();

    void on_pushButtonTaille_2_clicked();

private:
    Ui::Dialog *ui;
    QGraphicsScene scene, scene2;
    pthread_t tRecherche;

};

#endif // DIALOG_H
