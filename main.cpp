////////////////////////////////////////////////////////////////////////////////////
// Programme qui calcule les déplacements possibles d'une pièce sur un échiquier. //
////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;
//--------------------------------------------------------------------------------//
// Dimensions de l'échiquier (on évite les constantes globales...)
#define nLignes 8
#define nColonnes 8
//--------------------------------------------------------------------------------//
void afficherEchiquier(char ech[nLignes][nColonnes])
// Affiche l'échiquier avec les déplacements possibles
{
    cout << "  a b c d e f g h\n";
    for (int i = 0; i < nLignes; i++)
    {
        cout << nLignes - i << " "; // Numérotation des lignes
        for (int j = 0; j < nColonnes; j++)
        {
            cout << ech[i][j] << " ";
        }
        cout << nLignes - i << endl;
    }
    cout << "  a b c d e f g h\n";
}
//--------------------------------------------------------------------------------//
void deplacementsPion(int lig, int col, char ech[nLignes][nColonnes])
// Calcule les déplacements possibles d'un pion
{
    if (lig > 0 && ech[lig-1][col] == '.')
    {
        ech[lig-1][col] = '*'; // Avance d'une case
        if (lig == 6 && ech[lig-2][col] == '.')
        {
            ech[lig-2][col] = '*'; // Avance de deux cases si sur la 2e rangée
        }
    }
}
//--------------------------------------------------------------------------------//
void deplacementsCavalier(int lig, int col, char ech[nLignes][nColonnes])
// Calcule les déplacements possibles d'un cavalier
{
    int dep[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
    for (int i = 0; i < 8; i++) {
        int nouvelleLigne = lig + dep[i][0];
        int nouvelleColonne = col + dep[i][1];
        if (nouvelleLigne >= 0 && nouvelleLigne < nLignes && nouvelleColonne >= 0 && nouvelleColonne < nColonnes)
        {
            ech[nouvelleLigne][nouvelleColonne] = '*';
        }
    }
}
//--------------------------------------------------------------------------------//
void deplacementsFou(int lig, int col, char ech[nLignes][nColonnes])
// Calcule les déplacements possibles d'un fou
{
    for (int i = 1; i < nLignes; i++)
    {
        // Diagonale Haut-Gauche
        if (lig - i >= 0 && col - i >= 0)
        {
            ech[lig - i][col - i] = '*';
        }
        // Diagonale Haut-Droite
        if (lig - i >= 0 && col + i < nColonnes)
        {
            ech[lig - i][col + i] = '*';
        }
        // Diagonale Bas-Gauche
        if (lig + i < nLignes && col - i >= 0)
        {
            ech[lig + i][col - i] = '*';
        }
        // Diagonale Bas-Droite
        if (lig + i < nLignes && col + i < nColonnes)
        {
            ech[lig + i][col + i] = '*';
        }
    }
}
//--------------------------------------------------------------------------------//
void deplacementsTour(int lig, int col, char ech[nLignes][nColonnes])
// Calcule les déplacements possibles d'une tour
{
    // Mouvement vertical
    for (int i = 0; i < nLignes; i++)
    {
        if (i != lig)
        {
            ech[i][col] = '*';
        }
    }
    // Mouvement horizontal
    for (int j = 0; j < nColonnes; j++)
    {
        if (j != col)
        {
            ech[lig][j] = '*';
        }
    }
}
//--------------------------------------------------------------------------------//
void deplacementsReine(int lig, int col, char ech[nLignes][nColonnes])
// Calcule les déplacements possibles d'une reine
{
    // Déplacements de la tour (ligne droite et colonnes)
    for (int i = 0; i < nLignes; i++)
    {
        if (i != lig)
        {
            ech[i][col] = '*';
        }
    }
    for (int j = 0; j < nColonnes; j++)
    {
        if (j != col)
        {
            ech[lig][j] = '*';
        }
    }
    // Déplacements du fou (diagonales)
    for (int i = 1; i < nLignes; i++)
    {
        // Diagonale Haut-Gauche
        if (lig - i >= 0 && col - i >= 0)
        {
            ech[lig - i][col - i] = '*';
        }
        // Diagonale Haut-Droite
        if (lig - i >= 0 && col + i < nColonnes)
        {
            ech[lig - i][col + i] = '*';
        }
        // Diagonale Bas-Gauche
        if (lig + i < nLignes && col - i >= 0)
        {
            ech[lig + i][col - i] = '*';
        }
        // Diagonale Bas-Droite
        if (lig + i < nLignes && col + i < nColonnes)
        {
            ech[lig + i][col + i] = '*';
        }
    }
}
//--------------------------------------------------------------------------------//
void deplacementsRoi(int lig, int col, char ech[nLignes][nColonnes])
// Calcule les déplacements possibles d'un roi
{
    // Variables locales :
    int nouvelleLigne;
    int nouvelleColonne;
    // Le roi peut se déplacer d'une case dans toutes les directions
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue; // Ne pas rester sur place
            }
            nouvelleLigne = lig + i;
            nouvelleColonne = col + j;
            if (nouvelleLigne >= 0 && nouvelleLigne < nLignes && nouvelleColonne >= 0 && nouvelleColonne < nColonnes)
            {
                ech[nouvelleLigne][nouvelleColonne] = '*';
            }
        }
    }
}
//--------------------------------------------------------------------------------//
int main()
{
    // Création d'un échiquier vide avec un tableau classique
    char echiquier[nLignes][nColonnes];
    // Choix de l'utilisateur :
    char piece;
    //----------------------------------------------------------------------------//
    // Initialisation de l'échiquier avec des '.'
    for (int i = 0; i < nLignes; i++)
    {
        for (int j = 0; j < nColonnes; j++)
        {
            echiquier[i][j] = '.';
        }
    }
    //----------------------------------------------------------------------------//
    // Demande de la pièce à déplacer
    cout << "(P = Pion, C = Cavalier, F = Fou, T = Tour, R = Reine, K = Roi)" << endl;
    cout << "Choisissez une pièce à déplacer : ";
    cin >> piece;
    // Demande des coordonnées de la pièce
    int ligne, colonne;
    cout << "Entrez la ligne (de 1, votre cote ; a 8, cote adversaire) : ";
    cin >> ligne;
    cout << "Entrez la colonne (de 1 à 8, où a = 1, b = 2, ..., h = 8) : ";
    cin >> colonne;
    //----------------------------------------------------------------------------//
    // Ajuster les indices pour les utiliser dans le tableau (l'échiquier commence à 0)
    ligne = nLignes - ligne;
    colonne = colonne - 1;
    //----------------------------------------------------------------------------//
    // Vérifier que les coordonnées sont valides
    if (ligne < 0 || ligne >= nLignes || colonne < 0 || colonne >= nColonnes)
    {
        cout << "Coordonnées invalides !" << endl;
        return 1;
    }
    //----------------------------------------------------------------------------//
    // Placer la pièce sur l'échiquier
    echiquier[ligne][colonne] = piece;
    //----------------------------------------------------------------------------//
    // Calculer les déplacements possibles selon la pièce choisie
    switch (piece)
    {
        case 'P':
        case 'p':
            deplacementsPion(ligne, colonne, echiquier);
            break;
        case 'C':
        case 'c':
            deplacementsCavalier(ligne, colonne, echiquier);
            break;
        case 'F':
        case 'f':
            deplacementsFou(ligne, colonne, echiquier);
            break;
        case 'T':
        case 't':
            deplacementsTour(ligne, colonne, echiquier);
            break;
        case 'R':
        case 'r':
            deplacementsReine(ligne, colonne, echiquier);
            break;
        case 'K':
        case 'k':
            deplacementsRoi(ligne, colonne, echiquier);
            break;
        default:
            cout << "Pièce non reconnue !" << endl;
            return 1;
    }
    //----------------------------------------------------------------------------//
    // Afficher l'échiquier avec les déplacements possibles
    afficherEchiquier(echiquier);
    //----------------------------------------------------------------------------//
    return 0;
}
