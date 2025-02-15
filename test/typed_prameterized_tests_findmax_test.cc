#include "gtest/gtest.h"

// Interface abstraite définissant la fonction FindMax
class MyLib {
public:
  virtual ~MyLib() {}
  // Trouve l'élément maximal dans un vecteur
  virtual int FindMax(const std::vector<int>& inputs) const = 0;
};

//-----------------------------------------------------------------------------
// Implémentation itérative de la recherche du maximum.
class MyLibIterative : public MyLib {
public:
  // Trouve l'élément maximal dans un vecteur
  virtual int FindMax(const std::vector<int>& inputs) const override {
    if (inputs.size() == 0) {
      return -1;  // Retourne -1 si le vecteur est vide
    }

    int result = std::numeric_limits<int>::min();
    for (auto n : inputs) {
      if (n > result) {
        result = n;
      }
    }
    return result;
  }
};
//-----------------------------------------------------------------------------
// Implémentation récursive de la recherche du maximum.
class MyLibRecursive : public MyLib {
public:
  // Trouve l'élément maximal dans un vecteur
  virtual int FindMax(const std::vector<int>& inputs) const override {
    if (inputs.size() == 0) {
      return -1;  // Retourne -1 si le vecteur est vide
    }
    return FindMaxRecursiveAux(inputs, 0, inputs.size() - 1);
  }

private:
  // Fonction auxiliaire pour la recherche récursive
  int FindMaxRecursiveAux(const std::vector<int>& inputs, int left,
    int right) const {
    if (left >= right) {
      return inputs[left];
    }
    int mid = (right + left) / 2;
    return std::max(FindMaxRecursiveAux(inputs, left, mid),
      FindMaxRecursiveAux(inputs, mid + 1, right));
  }
};

//-----------------------------------------------------------------------------
// Classe de test générique utilisant un template.
template <class T>
class MyLibTest : public testing::Test {
public:
  T lib_; // Instance de la classe testée (peut être MyLibIterative ou MyLibRecursive)
};

using testing::Types;

// Utilisation de TYPED_TEST_SUITE_P pour définir une suite de tests paramétrée
TYPED_TEST_SUITE_P(MyLibTest);

// Test du cas où le vecteur est vide NOTE: On utilise TYPED_TEST_P 
TYPED_TEST_P(MyLibTest, FindMaxHandlesEmpty) {
  std::vector<int> inputs = {};
  EXPECT_EQ(this->lib_.FindMax(inputs), -1);
}

// Test du cas où le vecteur contient un seul élément
//...

// Test du cas où le vecteur contient des nombres consécutifs
//...

// Test du cas où le vecteur contient des nombres non consécutifs
//...

// Test du cas où le vecteur contient uniquement des nombres identiques
//...

// Enregistrement des tests définis avec TYPED_TEST_P
// L'enregistrement est nécessaire pour associer les tests paramétrés
// à la suite de tests et leur permettre d'être instanciés plus tard avec
// différentes implémentations. Sans cette étape, GoogleTest ne pourrait pas
// lier les tests définis via TYPED_TEST_P avec les types spécifiques.
REGISTER_TYPED_TEST_SUITE_P(MyLibTest, FindMaxHandlesEmpty
    //Ajouter vos nom de test ici
    //...
);

// Liste des types à tester (on peut la définir après l'écriture des tests paramétrés)
typedef Types<MyLibIterative, MyLibRecursive> Implementations;

// Instanciation de la suite de tests paramétrés pour chaque implémentation
// Cette étape permet de concrétiser les tests pour chaque type donné
// en utilisant les tests enregistrés précédemment.
INSTANTIATE_TYPED_TEST_SUITE_P(IterativeAndRecursive,  // Nom de l'instance
  MyLibTest,              // Nom du test
  Implementations);       // Liste des types