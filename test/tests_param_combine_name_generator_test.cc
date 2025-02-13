#include "gtest/gtest.h"

using ::testing::Combine;
using ::testing::ValuesIn;

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
// Méthode 4 (Avec génération de nom) : Tests paramétrés avec des tuples pour évaluer plusieurs algorithmes de tri
// Chaque test est exécuté avec une combinaison d'un algorithme de tri et d'un ensemble de données
//-----------------------------------------------------------------------------

// Création d'une map associant des noms aux jeux de données de test
std::map<std::string, std::vector<int>> input_map = {
  {"Vide", {}}, // Cas d'un tableau vide
  {"UnSeulElement", {1}}, // Cas d'un seul élément
  {"Inverse", {5, 4, 3, 2, 1}}, // Cas d'un tableau trié en ordre inverse
  {"PetitVecteur", {5, 3, 1, 77}}, // Cas d'un petit tableau non trié
  {"Duplication", {4, 122, 1000, 4, 122, 1000}} // Cas d'un tableau avec valeurs dupliquées
};

// Création d'une map associant des noms aux fonctions de tri
std::map<std::string, std::function<void(std::vector<int>&)>> function_map = {
  {"BubbleSort", BubbleSort},
  {"SelectionSort", SelectionSort},
};

// Définition de la classe de test paramétrée
class SortTest
  : public testing::TestWithParam<std::tuple<
      std::pair<const std::string, std::function<void(std::vector<int>&)>>, // Index 0 : Fonction de tri 
      std::pair<const std::string, std::vector<int>> // Index 1 : Données d'entrée
    >> {};

// Instanciation de la suite de tests avec génération automatique des noms
INSTANTIATE_TEST_SUITE_P(
  SortCustomNames, SortTest,
  Combine(ValuesIn(function_map), ValuesIn(input_map)),
  [](const testing::TestParamInfo<SortTest::ParamType>& info) {
    return std::get<0>(info.param).first + "_" + // Récupère le nom de l'algorithme de tri
           std::get<1>(info.param).first; // Récupère le nom du jeu de données
  });

// Test paramétré qui applique chaque fonction de tri à chaque jeu de données
TEST_P(SortTest, WorksForVariousInputs) {
    //A vous de jouer
    // on récupere le premier element d'un tuple abec std::get<0>(p)
    // On récupere le premier element d'une pair avec paire.first et le second avec pair.second
    //...
}
