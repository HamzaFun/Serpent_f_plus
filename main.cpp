#include "jeu.h"

#include <QApplication>

Jeu* jeu;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    jeu = new Jeu();
    jeu->show();
    jeu->afficherMenu("Serpent Pro", "Jouer");

    return a.exec();
}
