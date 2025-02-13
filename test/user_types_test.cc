#include "gtest/gtest.h"
using ::testing::Lt;
using ::testing::PrintToString;

struct Person {

    Person(std::string_view name, int age) : name(name), age(age) {}

    // Surcharge de l'operateur "==" pour EXPECT_EQ et ASSERT_EQ afin de pouvoir comparer des objet directement dans nos test ==> regarder le test "CanDirectlyAssertEquality".
    bool operator==(const Person& rhs) const {
        return (name == rhs.name && age == rhs.age);
    }


    //APRES UNE PREMIERE EXECUTION et discution avec le formateur, Decommenter les fonctions ci-dessous pour voir la difference.
    //Une fonction "friend" est une fonction qui n'est pas membre d'une classe mais qui a accès aux membres privés et protégés de la classe.
    // Le test Google appellera les fonctions operator<< ou PrintTo pour afficher votre objet.
    // objet. Si les deux sont définies, il utilisera PrintTo.
    /*friend std::ostream& operator<<(std::ostream& os, const Person& person) {
      return os << person.DebugString();
    }

    friend void PrintTo(const Person& person, std::ostream* os) {
      *os << person.DebugString();
    }*/

    //Cette fonction sera appelée par testing::PrintToString.
    std::string DebugString() const {
        std::string result;
        return result + "NOM: " + name + ", Age: " + std::to_string(age) + "\n";
    }

    std::string name;
    int age;
};

TEST(PersonTest, CanAssertEqualitySimple) {
    Person p_davey("Davey", 25);
    Person p_bickford("Bickford", 21);

    EXPECT_EQ(p_davey.name, p_bickford.name);
    EXPECT_EQ(p_davey.age, p_bickford.age);
}

TEST(PersonTest, CanDirectlyAssertEquality) {
    Person p_davey("Davey", 25);
    Person p_bickford("Bickford", 21);

    EXPECT_EQ(p_davey, p_davey);
    EXPECT_EQ(p_davey, p_bickford);
}

TEST(PersonTest, CanDirectlyAssertEqualityAndPrint) {
    Person p_davey("Davey", 25);
    Person p_bickford("Bickford", 21);

    EXPECT_EQ(p_davey, p_bickford) << PrintToString(p_davey) << p_bickford;
}
