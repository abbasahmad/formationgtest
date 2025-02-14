#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::Address;
using ::testing::AllOf;
using ::testing::AnyOf;
using ::testing::ContainerEq;
using ::testing::Contains;
using ::testing::Each;
using ::testing::ElementsAre;
using ::testing::ElementsAreArray;
using ::testing::Eq;
using ::testing::Field;
using ::testing::FieldsAre;
using ::testing::Ge;
using ::testing::Gt;
using ::testing::HasSubstr;
using ::testing::IsNull;
using ::testing::IsSubsetOf;
using ::testing::Key;
using ::testing::Lt;
using ::testing::Matcher;
using ::testing::Not;
using ::testing::Pair;
using ::testing::Pointee;
using ::testing::Pointer;
using ::testing::Pointwise;
using ::testing::PrintToString;
using ::testing::Property;
using ::testing::Truly;
using ::testing::UnorderedElementsAre;
using ::testing::UnorderedElementsAreArray;
using ::testing::WhenDynamicCastTo;
using ::testing::WhenSorted;


//DEMO AVEC LE FORMATEUR 

//-----------------------------------------------------------------------------
// Fonction de test pour illustrer les pointeurs
void Test() {
  int a = 1;
  int *a_ptr = &a; // a_ptr pointe vers a

  // Pointeur unique contenant la valeur 10
  std::unique_ptr<int> u_ptr(new int(10));
  int *pointer = u_ptr.get(); // Récupération du pointeur brut
}

//-----------------------------------------------------------------------------
// Test des pointeurs bruts avec Pointee()
TEST(PointerTest, PointeeRawPointerSimple) {
  int *n_ptr = new int(10);
  EXPECT_THAT(*n_ptr, Ge(9));  // Vérifie que la valeur du pointeur est >= 9
  EXPECT_THAT(n_ptr, Pointee(Ge(9)));  // Vérifie que le pointeur pointe vers une valeur >= 9
}

//-----------------------------------------------------------------------------
// Test des conteneurs contenant des pointeurs bruts
TEST(PointerTest, PointeeRawPointerContainer) {
  int a = 1, b = 2;
  std::vector<int *> my_pointers = {&a, &b};

  EXPECT_THAT(my_pointers, Each(Pointee(Ge(0)))); // Vérifie que chaque pointeur pointe vers une valeur >= 0
  EXPECT_THAT(my_pointers, UnorderedElementsAre(Pointee(b), Pointee(a))); // Vérifie les valeurs pointées
}

//-----------------------------------------------------------------------------
// Test des pointeurs intelligents (smart pointers) avec Pointee()
TEST(PointerTest, PointeeSmartPointerSimple) {
  std::unique_ptr<int> n_ptr(new int(10));
  EXPECT_THAT(*n_ptr, Ge(9));  // Vérifie que la valeur pointée est >= 9
  EXPECT_THAT(n_ptr, Pointee(Ge(0))); // Vérifie que le pointeur contient une valeur >= 0
}

//-----------------------------------------------------------------------------
// Test des conteneurs contenant des pointeurs intelligents
TEST(PointerTest, PointeeSmartPointerContainer) {
  std::vector<std::unique_ptr<int>> my_pointers;
  my_pointers.push_back(std::unique_ptr<int>(new int(1)));
  my_pointers.push_back(std::unique_ptr<int>(new int(2)));

  EXPECT_THAT(my_pointers, Each(Pointee(Ge(0)))); // Vérifie que chaque pointeur pointe vers une valeur >= 0
  EXPECT_THAT(my_pointers, UnorderedElementsAre(Pointee(2), Pointee(1))); // Vérifie les valeurs pointées
}

//-----------------------------------------------------------------------------
// Test de l'adresse mémoire avec Address()
TEST(PointerTest, Address) {
  int n = 10;
  int *n_ptr1 = &n, *n_ptr2 = &n;

  EXPECT_THAT(n, Address(n_ptr1));  // Vérifie que l'adresse de n est bien n_ptr1
  EXPECT_THAT(n, Address(AllOf(n_ptr1, n_ptr2))); // Vérifie plusieurs adresses
}

//-----------------------------------------------------------------------------
// Test des pointeurs avec Pointer()
TEST(PointerTest, PointerRawPointer) {
  int n = 10;
  int *n_ptr1 = &n, *n_ptr2 = &n;

  EXPECT_THAT(&n, Pointer(&n)); // Vérifie que l'adresse de n est bien celle attendue
  EXPECT_THAT(n_ptr1, Pointer(&n)); // Vérifie que le pointeur est correct
  EXPECT_THAT(&n, AllOf(Pointer(n_ptr1), Pointer(n_ptr2))); // Vérifie plusieurs pointeurs
}

//-----------------------------------------------------------------------------
// Test des pointeurs intelligents (smart pointers) avec Pointer()
TEST(PointerTest, PointerSmartPointerSimple) {
  std::unique_ptr<int> n(new int(10));
  EXPECT_THAT(n, Pointer(n.get())); // Vérifie que le smart pointer pointe bien vers l'objet
}

//-----------------------------------------------------------------------------
// Test de comparaison de smart pointers différents
TEST(PointerTest, Pointer_SmartPointer_Simple2) {
  std::unique_ptr<int> a(new int(1));
  std::unique_ptr<int> b(new int(1));

  EXPECT_THAT(a, Pointer(a.get())); // Vérifie que le smart pointer a pointe bien vers l'objet
  EXPECT_THAT(a, Not(Pointer(b.get()))); // Vérifie que a et b ne pointent pas vers la même adresse
}

//-----------------------------------------------------------------------------
// Test des conteneurs contenant des smart pointers avec Pointer()
TEST(PointerTest, PointerSmartPointerContainer) {
  std::unique_ptr<int> n(new int(10));
  EXPECT_THAT(n, Pointer(n.get()));

  std::vector<std::unique_ptr<int>> my_pointers;
  my_pointers.push_back(std::unique_ptr<int>(new int(1)));
  my_pointers.push_back(std::unique_ptr<int>(new int(2)));

  EXPECT_THAT(my_pointers, UnorderedElementsAre(
      Pointer(my_pointers[1].get()), Pointer(my_pointers[0].get())));
}

//-----------------------------------------------------------------------------
// Test des pointeurs partagés (shared_ptr)
TEST(PointerTest, PointerSharedPointer) {
  auto a_ptr = std::make_shared<int>(1);
  auto b_ptr = a_ptr; // b_ptr partage le même objet que a_ptr

  std::vector<std::shared_ptr<int>> my_pointers = {a_ptr, b_ptr};

  EXPECT_THAT(my_pointers, UnorderedElementsAre(a_ptr, b_ptr)); // Vérifie que les objets sont les mêmes
}

//-----------------------------------------------------------------------------
// Classes pour tester le cast dynamique avec WhenDynamicCastTo()
class Base {
 public:
  Base() { std::cout << "BASE" << std::endl; }
  virtual ~Base() {}
};

class Derived : public Base {
 public:
  Derived() { std::cout << "DERIVED" << std::endl; }
  int i;
};

//-----------------------------------------------------------------------------
// Test de cast dynamique avec WhenDynamicCastTo()
TEST(WhenDynamicCastToTest, SimpleTest) {
  Derived derived;
  derived.i = 4;

  Base *base_ptr_derived = &derived;
  Base *base_ptr = new Base();

  // Vérifie que base_ptr_derived peut être converti en Derived* (donc non nul)
  EXPECT_THAT(dynamic_cast<Derived *>(base_ptr_derived), Not(IsNull()));
  
  // Vérifie que le champ i du cast est égal à 4
  EXPECT_THAT(dynamic_cast<Derived *>(base_ptr_derived), Field(&Derived::i, 4));

  // Vérifie que base_ptr ne peut pas être casté en Derived* (donc est nul)
  EXPECT_THAT(dynamic_cast<Derived *>(base_ptr), IsNull());

  // Vérifie la conversion dynamique avec WhenDynamicCastTo()
  EXPECT_THAT(base_ptr_derived, WhenDynamicCastTo<Derived *>(Not(IsNull())));
  EXPECT_THAT(base_ptr_derived, WhenDynamicCastTo<Derived *>(Field(&Derived::i, 4)));
}
