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

// Liste des types à tester.
typedef Types<MyLibIterative, MyLibRecursive> Implementations;

// Utilisation de TYPED_TEST au lieu de TEST.
// Cela permet d'exécuter les mêmes tests sur plusieurs implémentations de MyLib.
TYPED_TEST_SUITE(MyLibTest, Implementations);

// Test du cas où le vecteur est vide
TYPED_TEST(MyLibTest, FindMaxHandlesEmpty) {
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
