#include <iostream>

using namespace std;

// Dimensions de l'échiquier
const int nLignes = 8;
const int nColonnes = 8;

// Affiche l'échiquier avec les déplacements possibles
void afficherEchiquier(char echiquier[nLignes][nColonnes]) {
    cout << "  a b c d e f g h\n";
    for (int i = 0; i < nLignes; i++) {
        cout << nLignes - i << " "; // Numérotation des lignes
        for (int j = 0; j < nColonnes; j++) {
            cout << echiquier[i][j] << " ";
        }
        cout << nLignes - i << endl;
    }
    cout << "  a b c d e f g h\n";
}

// Calcule les déplacements possibles d'un pion
void deplacementsPion(int ligne, int colonne, char echiquier[nLignes][nColonnes]) {
    if (ligne > 0 && echiquier[ligne-1][colonne] == '.') {
        echiquier[ligne-1][colonne] = '*'; // Avance d'une case
        if (ligne == 6 && echiquier[ligne-2][colonne] == '.') {
            echiquier[ligne-2][colonne] = '*'; // Avance de deux cases si sur la 2e rangée
        }
    }
}

// Calcule les déplacements possibles d'un cavalier
void deplacementsCavalier(int ligne, int colonne, char echiquier[nLignes][nColonnes]) {
    int deplacements[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
    for (int i = 0; i < 8; i++) {
        int nouvelleLigne = ligne + deplacements[i][0];
        int nouvelleColonne = colonne + deplacements[i][1];
        if (nouvelleLigne >= 0 && nouvelleLigne < nLignes && nouvelleColonne >= 0 && nouvelleColonne < nColonnes) {
            echiquier[nouvelleLigne][nouvelleColonne] = '*';
        }
    }
}

// Calcule les déplacements possibles d'un fou
void deplacementsFou(int ligne, int colonne, char echiquier[nLignes][nColonnes]) {
    for (int i = 1; i < nLignes; i++) {
        // Diagonale Haut-Gauche
        if (ligne - i >= 0 && colonne - i >= 0) echiquier[ligne - i][colonne - i] = '*';
        // Diagonale Haut-Droite
        if (ligne - i >= 0 && colonne + i < nColonnes) echiquier[ligne - i][colonne + i] = '*';
        // Diagonale Bas-Gauche
        if (ligne + i < nLignes && colonne - i >= 0) echiquier[ligne + i][colonne - i] = '*';
        // Diagonale Bas-Droite
        if (ligne + i < nLignes && colonne + i < nColonnes) echiquier[ligne + i][colonne + i] = '*';
    }
}

// Calcule les déplacements possibles d'une tour
void deplacementsTour(int ligne, int colonne, char echiquier[nLignes][nColonnes]) {
    // Mouvement vertical
    for (int i = 0; i < nLignes; i++) {
        if (i != ligne) {
            echiquier[i][colonne] = '*';
        }
    }
    // Mouvement horizontal
    for (int j = 0; j < nColonnes; j++) {
        if (j != colonne) {
            echiquier[ligne][j] = '*';
        }
    }
}

// Calcule les déplacements possibles d'une reine
void deplacementsReine(int ligne, int colonne, char echiquier[nLignes][nColonnes]) {
    // Déplacements de la tour (ligne droite et colonnes)
    for (int i = 0; i < nLignes; i++) {
        if (i != ligne) {
            echiquier[i][colonne] = '*';
        }
    }
    for (int j = 0; j < nColonnes; j++) {
        if (j != colonne) {
            echiquier[ligne][j] = '*';
        }
    }

    // Déplacements du fou (diagonales)
    for (int i = 1; i < nLignes; i++) {
        // Diagonale Haut-Gauche
        if (ligne - i >= 0 && colonne - i >= 0) echiquier[ligne - i][colonne - i] = '*';
        // Diagonale Haut-Droite
        if (ligne - i >= 0 && colonne + i < nColonnes) echiquier[ligne - i][colonne + i] = '*';
        // Diagonale Bas-Gauche
        if (ligne + i < nLignes && colonne - i >= 0) echiquier[ligne + i][colonne - i] = '*';
        // Diagonale Bas-Droite
        if (ligne + i < nLignes && colonne + i < nColonnes) echiquier[ligne + i][colonne + i] = '*';
    }
}

// Calcule les déplacements possibles d'un roi
void deplacementsRoi(int ligne, int colonne, char echiquier[nLignes][nColonnes]) {
    // Le roi peut se déplacer d'une case dans toutes les directions
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Ne pas rester sur place
            int nouvelleLigne = ligne + i;
            int nouvelleColonne = colonne + j;
            if (nouvelleLigne >= 0 && nouvelleLigne < nLignes && nouvelleColonne >= 0 && nouvelleColonne < nColonnes) {
                echiquier[nouvelleLigne][nouvelleColonne] = '*';
            }
        }
    }
}

int main() {
    // Création d'un échiquier vide avec un tableau classique
    char echiquier[nLignes][nColonnes];

    // Initialisation de l'échiquier avec des '.'
    for (int i = 0; i < nLignes; i++) {
        for (int j = 0; j < nColonnes; j++) {
            echiquier[i][j] = '.';
        }
    }

    // Demande de la pièce à déplacer
    char piece;
    cout << "Choisissez une pièce à déplacer (P = Pion, C = Cavalier, F = Fou, T = Tour, Q = Reine, R = Roi): ";
    cin >> piece;

    // Demande des coordonnées de la pièce
    int ligne, colonne;
    cout << "Entrez la ligne (de 1 à 8) : ";
    cin >> ligne;
    cout << "Entrez la colonne (de 1 à 8, où a = 1, b = 2, ..., h = 8) : ";
    cin >> colonne;

    // Ajuster les indices pour les utiliser dans le tableau (l'échiquier commence à 0)
    ligne = nLignes - ligne;
    colonne = colonne - 1;

    // Vérifier que les coordonnées sont valides
    if (ligne < 0 || ligne >= nLignes || colonne < 0 || colonne >= nColonnes) {
        cout << "Coordonnées invalides !" << endl;
        return 1;
    }

    // Placer la pièce sur l'échiquier
    echiquier[ligne][colonne] = piece;

    // Calculer les déplacements possibles selon la pièce choisie
    switch (piece) {
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
        case 'Q':
        case 'q':
            deplacementsReine(ligne, colonne, echiquier);
            break;
        case 'R':
        case 'r':
            deplacementsRoi(ligne, colonne, echiquier);
            break;
        default:
            cout << "Pièce non reconnue !" << endl;
            return 1;
    }

    // Afficher l'échiquier avec les déplacements possibles
    afficherEchiquier(echiquier);

    return 0;
}
