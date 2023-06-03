// Made by Yvan Allioux

#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <vector>

class MazeGenerator {
public:
    MazeGenerator(unsigned int largeur, unsigned int longueur, unsigned int hauteur);
    void remplisageMatrice(unsigned int valeurAremplir);
    void affichageMatriceTerminal();
    unsigned int randomVar(unsigned int min, unsigned int max);
    void suprimeMur(unsigned int x, unsigned int y, unsigned int z, char direction);
    bool murExiste(int num, int bitPos);
    void casserUnMurAleatoire();
    void changeValeurZone(unsigned int ancienneValeur, unsigned int valeurAremplir);
    bool memeZonePartout();
    void afficherAvecCouleur(int chiffre);
    void enregistrementMatriceDansFichier();
    

private:
    unsigned int m_LargeurX;
    unsigned int m_LongueurY;
    unsigned int m_HauteurZ;
    unsigned int m_NbCellules;
    std::vector<std::vector<std::vector<unsigned int>>> m_Matrice;
    std::vector<unsigned int> tableauDesZones;
};

#endif // MAZEGENERATOR_H
