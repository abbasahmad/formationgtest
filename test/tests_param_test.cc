#include "gtest/gtest.h"

/*
Cette fonction Swap est un template générique qui échange (swap) deux variables de type T en utilisant une variable temporaire.
Elle fonctionne avec n'importe quel type (int, double, std::string, etc.) grâce au template.
*/
template <class T>
void Swap(T& i, T& j) {
    T temp = i;
    i = j;
    j = temp;
}

//Cette fonction trouve l'index du plus petit élément dans un vecteur input à partir de start_index.
int FindMinIndex(const std::vector<int>& input, int start_index) {
    int min_index = start_index;
    int cur_min = input[start_index];
    for (size_t i = start_index; i < input.size(); i++) {
        if (input[i] < cur_min) {
            cur_min = input[i];
            min_index = i;
        }
    }
    return min_index;
}

//Cette fonction tri un vecteur en utilisant le tri par sélection (Selection Sort)
//en trouvant successivement le plus petit élément et en l'échangeant avec l'élément en cours.
void SelectionSort(std::vector<int>& input) {
    for (int i = 0; i < int(input.size() - 1); i++) {
        int min_index = FindMinIndex(input, i);
        Swap(input[i], input[min_index]);
    }
}

//Cette fonction implémente le tri à bulles (Bubble Sort) en parcourant le vecteur et en échangeant les éléments adjacents mal triés
//jusqu'à ce que la liste soit ordonnée.
void BubbleSort(std::vector<int>& input) {
    bool go;
    do {
        go = false;
        for (int i = 0; i < int(input.size() - 1); i++) {
            if (input[i] > input[i + 1]) {
                Swap(input[i], input[i + 1]);
                go = true;
            }
        }
    } while (go);
}


//-----------------------------------------------------------------------------
// Méthode 3 : Tests paramétrés pour évaluer plusieurs algorithmes de tri
// Utilisation de Google Test pour exécuter les tests sur différentes fonctions de tri
//-----------------------------------------------------------------------------

//CREER : Classe "SortTest" de test paramétrée pour tester différentes fonctions de tri


// Instancier la suite de tests pour les algorithmes SelectionSort et BubbleSort
//INSTANTIATE_TEST_SUITE_P(...);


//CREER, Oui avec beaucoup de copier coller mais on verra dans la suite comment eviter cela! 
// Test avec un petit nombre d'éléments
//...

// Test avec une collection vide
//...

// Test avec un seul élément
//...

// Test avec des valeurs en ordre inverse
//...

// Test avec des valeurs dupliquées
//...

// Test sur un grand vecteur aléatoire
//...

// Test sur un grand vecteur déjà trié
//...

// Test sur un grand vecteur trié en ordre inverse
//...

// Test avec un grand vecteur et différentes graines aléatoires
//...


//MODIFIER "INSTANTIATE_TEST_SUITE_P" afin d'affichier l'algorithme de tri dans les log du rapport de test (regarder share_logic_test.cc pour inspiration)