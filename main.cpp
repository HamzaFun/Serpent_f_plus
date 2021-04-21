#include "jeu.h"
#include "murpart.h"

#include <QApplication>

Jeu* jeu;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    jeu = new Jeu();
    jeu->show();
    jeu->afficherMenu("Jeu Serpent ", "Jouer");

    return a.exec();
}
