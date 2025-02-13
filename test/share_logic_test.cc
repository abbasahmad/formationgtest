#include "gtest/gtest.h"


//Fonction qui affiche un vecteur de type generique T (int, double, String, ...)
//Le mot-clé template indique que cette fonction est un modèle et que T est un type qui sera déterminé lors de l’appel de la fonction.
template <class T>
void PrintVector(std::vector<T> input) {
    std::cout << "{ ";
    unsigned int count = 0;
    for (auto n : input) {
        count++;
        std::cout << n;
        if (count < input.size()) std::cout << ", ";
    }
    std::cout << " }" << std::endl;
}

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

//Cette fonction tri un vecteur en utilisant le tri par sélection (Selection Sort) en trouvant successivement le plus petit élément et en l'échangeant avec l'élément en cours.
void SelectionSort(std::vector<int>& input) {
    for (int i = 0; i < int(input.size() - 1); i++) {
        int min_index = FindMinIndex(input, i);
        Swap(input[i], input[min_index]);
    }
}



/*
Immaginer vous voulez  que vous voulez trier different vecteurs:

    {},                        // Vide
    {1},                       // Taille 1
    {5, 3, 1, 42},             // Petite taille, valeurs aléatoires
    {5, 4, 3, 2, 1},           // Inverse
    {-4, 122, -1000, -4, 122}  // Contien des duplications
*/




//-----------------------------------------------------------------------------
// Method 1: Ecrire un test par vecteur (A COMPLETER)
//-----------------------------------------------------------------------------
//Ce test vérifie que SelectionSort fonctionne correctement pour un vecteur vide en comparant son résultat avec std::sort
TEST(SortTestSimple, SortsWorkForEmptyVector) {
    auto in = std::vector<int>{};
    auto expected = in;
    SelectionSort(in);
    std::sort(expected.begin(), expected.end());
    EXPECT_EQ(expected, in);
}

//...


//-----------------------------------------------------------------------------
// Method 2: Faire une fixture et deplacer la logique dans le ...teardown
// A FAIRE: CREE LES TESTS avec TEST_F(...)
//-----------------------------------------------------------------------------

class SortTestSimpleFixture : public ::testing::Test {
    void TearDown() override {
        expected_ = in_;
        SelectionSort(in_);
        std::sort(expected_.begin(), expected_.end());
        EXPECT_EQ(expected_, in_);
    }

public:
    std::vector<int> in_;
    std::vector<int> expected_;
};

//...


//-----------------------------------------------------------------------------
// Method 3: Utiliser une boucle "for" afin d'iterer sur tout les vecteurs
//-----------------------------------------------------------------------------
TEST(SortTestAllInputs, WorksForAllInputs) {
    std::vector<std::vector<int>> ins = {
        {},                        // Vide
        {1},                       // Taille 1
        {5, 3, 1, 77},             // Petite taille, valeurs aléatoires
        {5, 4, 3, 2, 1},           // Inverse
        {-4, 122, -1000, -4, 122}  // Contien des dupplliccations
    };

    for (auto& in : ins) {
       // CODE DU TEST
       //...
    }
}


//################   DEMO  avec le FORMATEUR    ################
//-----------------------------------------------------------------------------
// Method 4: Test Parametrisées
//-----------------------------------------------------------------------------
/*
//On ne fait plus d'heritage a partir de "::Testing::Test" mais avec "testing::TestWithParam"

class SortTest : public ::testing::TestWithParam<std::vector<int>> {}; // Ici on declare que notre test a un parametre de type vecteur d'entiers

TEST_P(SortTest, WorksForVariousInputs) {  // Notre test parametrisé utilise la declaration TEST_P

  auto in = GetParam();  // Le parametre est récupéré avec cette fonction de google test "GetParam()"
  // Le reste du test est identique aux autre
  auto expected = in;
  SelectionSort(in);
  std::sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, in);
}

//Cette macro "INSTANTIATE_TEST_SUITE_P" permet de tester la fonction de tri avec plusieurs listes de nombres différentes.
//Elle crée automatiquement plusieurs tests en utilisant chaque liste donnée, évitant ainsi d’écrire un test pour chaque cas manuellement.
INSTANTIATE_TEST_SUITE_P(
  SelectionSortVariousInputs, SortTest,
  testing::Values(
    std::vector<int>{},                 // Vide
    std::vector<int>{1},                // Taille 1
    std::vector<int>{5, 3, 1, 42},      // Petite taille, valeurs aléatoires
    std::vector<int>{5, 4, 3, 2, 1},    // ESREVNi
    std::vector<int>{-4, 122, -1000, -4, 122, -1000} // Contiens des dupplliccations
  ));
*/


//-----------------------------------------------------------------------------
// Method 4 BIS (Enhanced): Test Parametrisées Avec Nommage de test
//-----------------------------------------------------------------------------
/*
// MAP: Chaque clé représente un cas de test et chaque valeur est une liste d'entiers à trier.
std::map<std::string, std::vector<int>> input_map = {
  {"Vide", {}},
  {"ElementUnique", {1}},
  {"Inverse", {5, 4, 3, 2, 1}},
  {"PetiteTaille", {5, 3, 1, 77}},
  {"Duplications", {-4, 122, -1000, -4, 122, -1000}}
};

// Définition d'une classe de test paramétrée qui utilise une paire (nom du test, liste d'entiers).
class SortTestNameGenerator : public testing::TestWithParam<std::pair<const std::string, std::vector<int>>> {};

// Test paramétré : trie la liste d'entrée avec SelectionSort et la compare à un tri standard.
TEST_P(SortTestNameGenerator, WorksForVariousInputs) {
  auto in = GetParam().second; // Récupération de la liste à trier
  auto expected = in;          // Copie pour comparaison
  SelectionSort(in);           // Tri avec l'algorithme à tester
  std::sort(expected.begin(), expected.end()); // Tri de référence
  EXPECT_EQ(expected, in);      // Vérification du résultat
}

// Instanciation du test paramétré en utilisant les données de input_map.
// Chaque cas de test est identifié par son nom (clé de input_map).
INSTANTIATE_TEST_SUITE_P(
  SelectionSortVariousInputsNameGenerator, SortTestNameGenerator, testing::ValuesIn(input_map),

   [](const testing::TestParamInfo<SortTestNameGenerator::ParamType>& info) { //Fonction Lambda
    return info.param.first; // Utilisation du nom comme identifiant du test
  }
);

*/