#include "gtest/gtest.h"

using ::testing::Combine;
using ::testing::Values;

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
// Méthode 4 : Tests paramétrés avec des tuples pour évaluer plusieurs algorithmes de tri
// Chaque test est exécuté avec une combinaison d'un algorithme de tri et d'un ensemble de données
//-----------------------------------------------------------------------------
class SortTest
  : public testing::TestWithParam<std::tuple<
      std::function<void(std::vector<int>&)>,  // Index 0 : Fonction de tri
      std::vector<int>                         // Index 1 : Données d'entrée
    >
  > {};

// Instancie la suite de tests pour tester plusieurs algorithmes avec plusieurs jeux de données
INSTANTIATE_TEST_SUITE_P(SelectionSortBubbleSort, SortTest,
  Combine(Values(SelectionSort, BubbleSort), // Index 0 : Algorithmes de tri
    Values(std::vector<int>{},              // Index 1 : Données d'entrée vides
        std::vector<int>{1},               // Un seul élément
        std::vector<int>{5, 3, 1, 77},     // Petit tableau de nombres aléatoires
        std::vector<int>{5, 4, 3, 2, 1},   // Tableau en ordre inverse
        std::vector<int>{-4, 122, -1000, -4, 122, -1000} // Avec des doublons
    )
  )
);


// Test paramétré qui fonctionne avec différentes combinaisons de tri et d'entrées
TEST_P(SortTest, WorksForVariousInputs) {
    //A vous de jouer
    // on récupere le premier element d'un tuple abec std::get<0>(p)
    //...
}


//Encore une foi regarder les nom des test dans les log. Vous etes satisfait ?
//Allons changer cela