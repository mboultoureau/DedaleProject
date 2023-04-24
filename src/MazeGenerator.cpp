#include "MazeGenerator.h"
#include <iostream>
#include <bitset>

//debug
#include <thread>
#include <chrono>

// Constructor
MazeGenerator::MazeGenerator(unsigned int largeur, unsigned int longueur, unsigned int hauteur)
{
    srand(time(NULL)); // initialisation de la fonction random

    m_LargeurX = largeur;
    m_LongueurY = longueur;
    m_HauteurZ = hauteur;
    m_NbCellules = m_LargeurX * m_LongueurY * m_HauteurZ;
    // matrice 3D
    m_Matrice.resize(m_LargeurX, std::vector<std::vector<unsigned int>>(m_LongueurY, std::vector<unsigned int>(m_HauteurZ)));
    // tableau des zones
    tableauDesZones.resize(m_NbCellules);

    for (unsigned int i = 0; i < m_NbCellules; i++)
    {
        tableauDesZones[i] = i;
    }

    std::cout << "Largeur : ";
    afficherAvecCouleur(largeur);
    std::cout << " Longueur : " << longueur << " Hauteur : " << hauteur << " Nombre de cellules : " << m_NbCellules << std::endl;

    remplisageMatrice(15);

    // je prend une cellule au hasard et une direction au hasard et je casse le mur
    // casserUnMurAleatoire();

    // casse 100 murs au hasard
    /* for (int i = 0; i < 100; i++)
    {
        casserUnMurAleatoire();
        affichageMatriceTerminal();
    } */
    // print memeZonePartout()
    // std::cout << "memeZonePartout() : " << memeZonePartout() << std::endl;

    // cassage de murs jusqu'à ce que toutes les cellules soient dans la même zone
    //kruskal algorithm
    while (!memeZonePartout())
    {
        casserUnMurAleatoire();
        //affichageMatriceTerminal();
        //pause de 1 seconde
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));//debug
    }
    affichageMatriceTerminal();
    //enregistrement de la matrice dans un fichier //TODO faire mieux mdr la c'est nul
    enregistrementMatriceDansFichier();

    
}

unsigned int MazeGenerator::randomVar(unsigned int min, unsigned int max)
{
    return rand() % (max - min) + min;
}

void MazeGenerator::remplisageMatrice(unsigned int valeurAremplir)
{
    for (unsigned int z = 0; z < m_HauteurZ; z++)
    {
        for (unsigned int y = 0; y < m_LongueurY; y++)
        {
            for (unsigned int x = 0; x < m_LargeurX; x++)
            {
                if (x == 0 || y == 0 || z == 0 || x == m_LargeurX - 1 || y == m_LongueurY - 1 || z == m_HauteurZ - 1)
                {
                    m_Matrice[x][y][z] = valeurAremplir;
                }
            }
        }
    }
}

void MazeGenerator::affichageMatriceTerminal()
{
    std::cout << "----------------------------------------------------" << std::endl;
    for (unsigned int z = 0; z < m_HauteurZ; z++)
    {
        std::cout << "__ Etage : " << z << " __" << std::endl;
        for (unsigned int y = 0; y < m_LongueurY; y++)
        {
            for (unsigned int x = 0; x < m_LargeurX; x++)
            {
                if (m_Matrice[x][y][z] < 10) // plus de 2 chiffres indentation
                {
                    std::cout << " ";
                }
                else if (tableauDesZones[(x + (m_LargeurX * y) + (m_LargeurX * m_LongueurY * z))] < 10) // plus de 2 chiffres indentation
                {
                    std::cout << " ";
                }
                std::cout << "";
                afficherAvecCouleur(m_Matrice[x][y][z]);
                std::cout << " , ";
                afficherAvecCouleur(tableauDesZones[(x + (m_LargeurX * y) + (m_LargeurX * m_LongueurY * z))]);
                std::cout << " | ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------------------" << std::endl;
}

void MazeGenerator::suprimeMur(unsigned int x, unsigned int y, unsigned int z, char direction)
{

    if (x > m_LargeurX - 1 || y > m_LongueurY - 1 || z > m_HauteurZ - 1) // x y z pas superieur taille de la matrice et pas inferieur a 0 (unsigned)
    {
        std::cout << "Erreur suprimeMur DEPASSEMENT XYZ -- x : " << x << " -- y : " << y << " -- z : " << z << std::endl;
        return;
    }
    if (direction == 'N')
    {
        // Suprime le mur north
        if (y != 0)
        {
            // si mur nord deja suprimer
            if (murExiste(m_Matrice[x][y][z], 0) == false)
            {
                //std::cout << "deja suprimée" << std::endl;
                return;
            }
            //TODO ajouter l'imposibiliter d'une case avec 1 seul mur ?
            if ((m_Matrice[x][y][z] - 1) == 0 || (m_Matrice[x][y - 1][z] - 2) == 0)
            {
                //std::cout << "supression donne case = a 0, anulation" << std::endl;
                return;
            }
            m_Matrice[x][y][z] -= 1;
            // Suprime le mur du sud de la cellule du dessus
            m_Matrice[x][y - 1][z] -= 2;
            // met a jour le tableau des zones
            unsigned int zone1 = (x + (m_LargeurX * y) + (m_LargeurX * m_LongueurY * z));
            unsigned int zone2 = (x + (m_LargeurX * (y - 1)) + (m_LargeurX * m_LongueurY * z));
            changeValeurZone(zone1, zone2);
            // print debug zone
            //std::cout << "zone1 : " << zone1 << " -- zone2 : " << zone2 << std::endl;
        }
        else
        {
            //std::cout << "Erreur suprimeMur impossible -- x : " << x << " -- y : " << y << " -- z : " << z << std::endl;
        }
    }
    else if (direction == 'S')
    {
        // Suprime le mur du sud
        if (!(y >= m_LongueurY - 1))
        {
            // si mur nord deja suprimer
            if (murExiste(m_Matrice[x][y][z], 1) == false)
            {
                //std::cout << "deja suprimée" << std::endl;
                return;
            }
            if ((m_Matrice[x][y][z] - 2) == 0 || (m_Matrice[x][y + 1][z] - 1) == 0)
            {
                //std::cout << "supression donne case = a 0, anulation" << std::endl;
                return;
            }
            m_Matrice[x][y][z] -= 2;
            // Suprime le mur du nord de la cellule du dessous
            m_Matrice[x][y + 1][z] -= 1;
            unsigned int zone1 = (x + (m_LargeurX * y) + (m_LargeurX * m_LongueurY * z));
            unsigned int zone2 = (x + (m_LargeurX * (y + 1)) + (m_LargeurX * m_LongueurY * z));
            changeValeurZone(zone1, zone2);
            // print debug zone
            //std::cout << "zone1 : " << zone1 << " -- zone2 : " << zone2 << std::endl;
        }
        else
        {
            //std::cout << "Erreur suprimeMur impossible -- x : " << x << " -- y : " << y << " -- z : " << z << std::endl;
        }
    }
    else if (direction == 'E')
    {
        // Suprime le mur de droite
        if (!(x >= m_LargeurX - 1))
        {
            if (murExiste(m_Matrice[x][y][z], 2) == false)
            {
                //std::cout << "deja suprimée" << std::endl;
                return;
            }
            if ((m_Matrice[x][y][z] - 4) == 0 || (m_Matrice[x + 1][y][z] - 8) == 0)
            {
                //std::cout << "supression donne case = a 0, anulation" << std::endl;
                return;
            }
            m_Matrice[x][y][z] -= 4;
            // Suprime le mur de droite de la cellule de gauche
            m_Matrice[x + 1][y][z] -= 8;
            unsigned int zone1 = (x + (m_LargeurX * y) + (m_LargeurX * m_LongueurY * z));
            unsigned int zone2 = ((x + 1) + (m_LargeurX * y) + (m_LargeurX * m_LongueurY * z));
            changeValeurZone(zone1, zone2);
            // print debug zone
            //std::cout << "zone1 : " << zone1 << " -- zone2 : " << zone2 << std::endl;
        }
        else
        {
            //std::cout << "Erreur suprimeMur impossible -- x : " << x << " -- y : " << y << " -- z : " << z << std::endl;
        }
    }
    else if (direction == 'W')
    {
        // Suprime le mur de gauche
        if (x != 0)
        {
            if (murExiste(m_Matrice[x][y][z], 3) == false)
            {
                //std::cout << "deja suprimée" << std::endl;
                return;
            }
            if ((m_Matrice[x][y][z] - 8) == 0 || (m_Matrice[x - 1][y][z] - 4) == 0)
            {
                //std::cout << "supression donne case = a 0, anulation" << std::endl;
                return;
            }
            m_Matrice[x][y][z] -= 8;
            // Suprime le mur de gauche de la cellule de droite
            m_Matrice[x - 1][y][z] -= 4;
            unsigned int zone1 = (x + (m_LargeurX * y) + (m_LargeurX * m_LongueurY * z));
            unsigned int zone2 = ((x - 1) + (m_LargeurX * y) + (m_LargeurX * m_LongueurY * z));
            changeValeurZone(zone1, zone2);
            // print debug zone
            //std::cout << "zone1 : " << zone1 << " -- zone2 : " << zone2 << std::endl;
        }
        else
        {
            //std::cout << "Erreur suprimeMur impossible -- x : " << x << " -- y : " << y << " -- z : " << z << std::endl;
        }
    }
}

bool MazeGenerator::murExiste(int num, int bitPos)
{
    // Vérifie que le numéro est entre 1 et 15
    if (num < 1 || num > 15)
    {
        return false;
    }
    // Vérifie que la position du bit est valide
    if (bitPos < 0 || bitPos > 3)
    {
        return false;
    }
    // Convertit le numéro en binaire sur 4 bits
    std::bitset<4> numBits(num);
    // Renvoie true si le bit correspondant est à 1
    return numBits[bitPos];
}

void MazeGenerator::casserUnMurAleatoire()
{
    //TODO casser en priorité les murs qui sont dans la même zone
    unsigned int x = randomVar(0, m_LargeurX);
    unsigned int y = randomVar(0, m_LongueurY);
    unsigned int z = randomVar(0, m_HauteurZ);
    unsigned int direction = randomVar(0, 4);

    if (direction == 0)
    {
        suprimeMur(x, y, z, 'N');
    }
    else if (direction == 1)
    {
        suprimeMur(x, y, z, 'S');
    }
    else if (direction == 2)
    {
        suprimeMur(x, y, z, 'E');
    }
    else if (direction == 3)
    {
        suprimeMur(x, y, z, 'W');
    }
}

void MazeGenerator::changeValeurZone(unsigned int positionIndexAncienneValeur, unsigned int positionIndexvaleurAremplir)
{
    // affichage des valeurs
    // std::cout << "ancienneValeur : " << ancienneValeur << " -- valeurAremplir : " << valeurAremplir << std::endl;
    // tableauDesZones tableau
    unsigned int ancienneValeur = tableauDesZones[positionIndexAncienneValeur];
    unsigned int valeurAremplir = tableauDesZones[positionIndexvaleurAremplir];
    for (unsigned int i = 0; i < m_NbCellules; i++)
    {
        if (tableauDesZones[i] == ancienneValeur)
        {
            tableauDesZones[i] = valeurAremplir;
        }
    }
}

bool MazeGenerator::memeZonePartout()
{
    unsigned int zoneIndex0 = tableauDesZones[0];
    for (unsigned int i = 0; i < m_NbCellules; i++)
    {
        if (!(tableauDesZones[i] == zoneIndex0))
        {
            return false;
        }
    }
    return true;
}

void MazeGenerator::afficherAvecCouleur(int chiffre)
{
    if (chiffre < 0 || chiffre > 100)
    {
        std::cout << "AFFICHAGE COULEUR Le chiffre doit être compris entre 0 et 100." << std::endl;
        return;
    }

    // Tableau de couleurs
    const std::string couleurs[] = {"\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m"};

    // Attribuer une couleur unique en fonction du chiffre
    std::string couleur = couleurs[chiffre % 6];

    // Afficher le chiffre avec la couleur correspondante
    std::cout << couleur << chiffre << "\033[0m";
}

void MazeGenerator::enregistrementMatriceDansFichier(){
    //utilisation d'une commande systeme pour enregistrer la matrice dans un fichier
    std::string commande = "echo \"";

    for (unsigned int z = 0; z < m_HauteurZ; z++)
    {
        for (unsigned int y = 0; y < m_LongueurY; y++)
        {
            for (unsigned int x = 0; x < m_LargeurX; x++)
            {
                //affichage de la valeur de la cellule
                std::cout << m_Matrice[x][y][z] << " ";
                //ajout de la valeur de la cellule dans la commande
                commande += std::to_string(m_Matrice[x][y][z]);
                //ajout d'un espace dans la commande
                commande += " ";
            }
            //ajout d'un retour a la ligne dans la commande
            commande += "\n";
        }
        commande += "\n";
        commande += "\n";
    }
    commande += "\" > matrice.txt";
    system(commande.c_str());

}
