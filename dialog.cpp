#include "dialog.h"
#include "ui_dialog.h"
#include <iostream>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <stdio.h>
#include "fonction.h"
#include <string.h>

using namespace std;
extern Meteo * m ;


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{


    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView_2->setScene(&scene2);
    ui->lineEditVille_2->setText("Paris");
    ui->lineEditVille_3->setText("France");

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonTaille_clicked()
{
    ui->graphicsView->hide();
}

void Dialog::on_pushButtonTaille_2_clicked()
{
    ui->graphicsView->show();
}

void Dialog::afficherMeteo()
{
    if(m->getEtat() == Meteo::OK_XML_FORECAST)
    {
        cout << "Tout s'est bien passé lors de la recherche..."  << endl << endl;
    }

    cout << "Le vent : " << m->getConditionActuelle().vent  << endl << endl;

    cout << "Nombre de jours : " << m->getNombrePrevision() << endl << endl;

    QFont f = QFont("Tahoma");
    f.setBold(1);

    QFont f2 = QFont("Tahoma");
    f2.setWeight(2);

    QString actu = QString::fromUtf8("Actuellement");
    QGraphicsSimpleTextItem * textItem1 = scene2.addSimpleText(actu, f);
    textItem1->translate(0,10);

    QPixmap pixmap(m->getConditionActuelle().iconeLocale.c_str());
    //QPixmap pixmap("images/chancerain.gif");
    cout << "Hauteur de l'image : " << pixmap.height();
    QGraphicsPixmapItem * gpi = scene2.addPixmap(pixmap);
    gpi->translate(30,50);

    QGraphicsSimpleTextItem * textItem3 = scene2.addSimpleText(QString::fromUtf8(m->getConditionActuelle().description.c_str()));
    textItem3->translate(20,120);

    QString temp = QString::number(m->getConditionActuelle().temperature) + QString::fromUtf8("°C");
    QGraphicsSimpleTextItem * textItem4 = scene2.addSimpleText(temp);
    textItem4->translate(35,150);

    QString desc = "Vent " + QString::fromUtf8(m->getConditionActuelle().vent.c_str());
    QGraphicsSimpleTextItem * textItem5 = scene2.addSimpleText(desc, f2);
    textItem5->translate(0,180);

    QString hum = QString::fromUtf8("Humidité ") + QString::fromUtf8(m->getConditionActuelle().humidite.c_str());
    QGraphicsSimpleTextItem * textItem6 = scene2.addSimpleText(hum, f2);
    textItem6->translate(0,210);

    int nbJour = m->getNombrePrevision();
    for( int i=0 ; i<nbJour ; i++)
    {
        ConditionAVenir cav = m->getConditionAVenir(i);
        cout << "Date de la prévision : " << cav.jour << endl;
        cout << "Température MAX : " << cav.temperatureMax << endl;
        cout << cav.description << endl << endl;

        QGraphicsSimpleTextItem * textItem3 = scene.addSimpleText(cav.jour.c_str());
        textItem3->translate(40*3*i,10);

        //cout << "Icone : " << cav.iconeLocale.c_str() << endl;
        QPixmap pixmap(cav.iconeLocale.c_str());
        QGraphicsPixmapItem * gpi = scene.addPixmap(pixmap);
        gpi->translate(50*2.5*i,50);

        QString Temp = QString::number(cav.temperatureMin) + QString::fromUtf8("°C") + " | " + QString::number(cav.temperatureMax) + QString::fromUtf8("°C");
        QGraphicsSimpleTextItem * textItem4 = scene.addSimpleText(Temp);
        textItem4->translate(40*3*i,100);

    }


}

void Dialog::on_pushButtonRechercher_clicked()
{ 
    scene.clear();
    scene2.clear();

    string desti = ui->lineEditVille_3->text().toStdString() + '/' + ui->lineEditVille_2->text().toStdString();
    m->setVilleDemandee(desti);

    int res = pthread_create( &tRecherche, NULL, (void *(*)(void *))threadRecherche, NULL);

    if(res != 0) { cout << "erreur de thread"<< endl; }

}
