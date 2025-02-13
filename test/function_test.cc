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
// Méthode 1 : Utilisation d'un pointeur de fonction pour tester des algorithmes de tri
// Cette méthode prend une fonction de tri en paramètre et la teste avec divers cas
//-----------------------------------------------------------------------------
template <class T>
void TestSort(T sort_func) {
    std::vector<int> in;
    std::vector<int> expected;

    // Test avec une liste de nombres désordonnés
    in = { 1, 11, 2, 5, 12, 9, 4, 10 };
    sort_func(in);
    expected = { 1, 2, 4, 5, 9, 10, 11, 12 };
    EXPECT_EQ(expected, in);
    EXPECT_EQ(expected.size(), in.size());

    // Vérification avec un tableau vide
    in = {};
    sort_func(in);
    expected = {};
    EXPECT_EQ(expected, in);
    EXPECT_EQ(expected.size(), in.size());

    // Vérification avec un seul élément
    in = { 3 };
    sort_func(in);
    expected = { 3 };
    EXPECT_EQ(expected, in);
    EXPECT_EQ(expected.size(), in.size());

    // Test avec une petite liste
    in = { 5, 3, 1, 77, -1 };
    sort_func(in);
    expected = { -1, 1, 3, 5, 77 };
    EXPECT_EQ(expected, in);
    EXPECT_EQ(expected.size(), in.size());

    // Vérification d'un tableau trié en ordre inverse
    in = { 5, 4, 3, 2, 1 };
    sort_func(in);
    expected = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(expected, in);
    EXPECT_EQ(expected.size(), in.size());

    in = { 5, 4, 3, 2, 1, 0 };
    sort_func(in);
    expected = { 0, 1, 2, 3, 4, 5 };
    EXPECT_EQ(expected, in);
    EXPECT_EQ(expected.size(), in.size());

    // Test avec des valeurs dupliquées
    in = { -4, 122, -1000, 222, 45, 66, 97, 1, 23, 44, 23, 100, 244, 456, -1000, 22 };
    sort_func(in);
    expected = { -1000, -1000, -4, 1, 22, 23, 23, 44, 45, 66, 97, 100, 122, 222, 244, 456 };
    EXPECT_EQ(expected, in);
    EXPECT_EQ(expected.size(), in.size());

    // Test sur un grand vecteur généré aléatoirement
    // Ici, on génère un vecteur de 1000 éléments avec des valeurs aléatoires
    for (size_t i = 0; i < 50; i++) {
        std::srand(i * 2);  // Utilisation d'une graine constante pour assurer la reproductibilité
        in.resize(1000);
        std::generate(in.begin(), in.end(), std::rand);
        expected = in;
        std::sort(expected.begin(), expected.end()); // Trie le vecteur attendu pour comparaison
        sort_func(in);
        EXPECT_EQ(expected, in);
        EXPECT_EQ(expected.size(), in.size());
    }

    // Test avec un grand vecteur trié en ordre inverse
    // Ici, on génère un vecteur aléatoire et on le trie en ordre décroissant avec std::greater<int>()
    for (size_t i = 0; i < 50; i++) {
        std::srand(i * 2);
        in.resize(1000);
        std::generate(in.begin(), in.end(), std::rand);
        std::sort(in.begin(), in.end(), std::greater<int>()); // Trie le vecteur en ordre décroissant
        expected = in;
        std::sort(expected.begin(), expected.end()); // Trie ensuite le vecteur attendu en ordre croissant
        sort_func(in);
        EXPECT_EQ(expected, in);
        EXPECT_EQ(expected.size(), in.size());
    }

    // Test avec un vecteur encore plus grand (5000 éléments)
    for (size_t i = 0; i < 5; i++) {
        std::srand(i);
        in.resize(5000);
        std::generate(in.begin(), in.end(), std::rand);
        expected = in;
        std::sort(expected.begin(), expected.end());
        sort_func(in);
        EXPECT_EQ(expected, in);
        EXPECT_EQ(expected.size(), in.size());
    }
}

//----------------------------------------------------------------------------- 
// Déclaration des tests unitaires avec différentes implémentations de tri
// Ces tests valident que les algorithmes de tri fonctionnent correctement
//-----------------------------------------------------------------------------
TEST(SortTest, SelectionSort) { 
    TestSort(SelectionSort);
}
TEST(SortTest, BubbleSort) {
     TestSort(BubbleSort); 
}



//-----------------------------------------------------------------------------
// Méthode 2 : Exécution de tous les tests en une seule fois
// Cette méthode applique différents algorithmes de tri sur plusieurs jeux de données
//-----------------------------------------------------------------------------
TEST(SortTestAllAtOnce, WorksOnAllFunctionsWithAllInputs) {
    std::vector<int> in;
    std::vector<std::vector<int>> ins = {
        {},                         // Tableau vide
        {1},                        // Un seul élément
        {5, 3, 1, 77},              // Petit tableau avec valeurs aléatoires
        {5, 4, 3, 2, 1},            // Tableau trié en ordre inverse
        {-4, 122, -1000, -4, 122},  // Tableau avec valeurs dupliquées
        {-4, 122, -1000, 222, 45, 66, 97, 1, 23, 44, 23, 100, 244, 456, -1000, 22} };

    // Test sur un grand vecteur généré aléatoirement
    // Ajoute 50 vecteurs de 1000 éléments remplis de valeurs aléatoires
    for (size_t i = 0; i < 50; i++) {
        std::srand(i * 2);
        in.resize(1000);
        std::generate(in.begin(), in.end(), std::rand);
        ins.push_back(in);
    }

    // Test avec un grand vecteur déjà trié
    // Génère 50 vecteurs et les trie avant de les ajouter
    for (size_t i = 0; i < 50; i++) {
        std::srand(i * 2);
        in.resize(1000);
        std::generate(in.begin(), in.end(), std::rand);
        std::sort(in.begin(), in.end()); // Trie le vecteur avant de l'ajouter
        ins.push_back(in);
    }

    // Test avec un grand vecteur trié en ordre inverse
    // Génère 50 vecteurs et les trie en ordre décroissant avant de les ajouter
    for (size_t i = 0; i < 50; i++) {
        std::srand(i * 2);
        in.resize(1000);
        std::generate(in.begin(), in.end(), std::rand);
        std::sort(in.begin(), in.end(), std::greater<int>()); // Trie en ordre décroissant
        ins.push_back(in);
    }

    // Test avec un vecteur encore plus grand (5000 éléments)
    // Génère 5 vecteurs de 5000 éléments avec des valeurs aléatoires
    for (size_t i = 0; i < 5; i++) {
        std::srand(i);
        in.resize(5000);
        std::generate(in.begin(), in.end(), std::rand);
        ins.push_back(in);
    }

    // Test avec un grand vecteur trié en ordre inverse (5000 éléments)
    // Génère 5 vecteurs, les trie en ordre décroissant avant de les ajouter
    for (size_t i = 0; i < 5; i++) {
        std::srand(i * 2);
        in.resize(5000);
        std::generate(in.begin(), in.end(), std::rand);
        std::sort(in.begin(), in.end(), std::greater<int>());
        ins.push_back(in);
    }

    // Liste des fonctions de tri à tester
    std::vector<std::function<void(std::vector<int>&)>> functions = {
        SelectionSort,
        BubbleSort
    };

    // Application de chaque fonction de tri sur chaque jeu de données
    for (auto f : functions) {
        for (auto& in : ins) {
            auto expected = in;
            f(in);
            std::sort(expected.begin(), expected.end()); // Trie attendu en ordre croissant
            EXPECT_EQ(expected, in);
        }
    }
}

