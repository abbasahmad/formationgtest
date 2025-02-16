### 📚 Formation aux Tests Unitaires avec Google Test


##### Reamme non complet. Suivre la formation pour mener a bien les exercices.

## 📌 Introduction

Ce projet est une introduction aux tests unitaires avec **Google Test**. Il est conçu pour accompagner la formation de 3 jours sur les concepts fondamentaux des tests logiciels, la mise en place de l’environnement, et la pratique des tests unitaires avec Google Test et Google Mock.

## 🎯 Objectifs de la formation

- Comprendre l'importance des tests unitaires dans l’assurance qualité logicielle.
- Mettre en place un environnement de test avec Google Test et Bazel.
- Rédiger et exécuter des tests unitaires avec Google Test.
- Découvrir les concepts avancés comme les **fixtures**, les **matchers** et les **mocks** avec Google Mock.
- Appliquer les bonnes pratiques pour des tests efficaces.

---

## 🛠️ Configuration de l’Environnement

### 📌 Prérequis
- **Système d’exploitation** : Ubuntu 24.04 LTS recommandé
- **IDE** : Visual Studio Code


### 👥 Clonage du projet
```sh
git clone https://github.com/abbasahmad/formationgtest.git
cd formationgtest
```

### 🔨 Compilation et Exécution des Tests
L'exécution des tests se fait avec **Bazel** :
```sh
bazel test test:premiers_test    # Exécute un seul test
bazel test test:all              # Exécute tous les tests
```
Pour afficher les résultats des tests :
```sh
nano ~/.bazelrc
```
Ajouter :
```
test --test_output=all
test --test_arg=--gtest_color=yes
```

---

## 📚 Contenu du Projet

📺 **src/lib/** → Code source de l'application.  
📺 **test/** → Scripts de tests unitaires utilisant Google Test.  
📝 **MODULE.bazel** → Fichier de configuration pour Bazel.  
📝 **.gitignore** → Fichiers et dossiers à ignorer dans le contrôle de version.  

---

## 🧪 Concepts Abordés

- **Assertions communes** (`ASSERT_*`, `EXPECT_*`).
- **Gestion des tests unitaires** (`TEST`, `TEST_F`, `TEST_P`).
- **Tests paramétriques et typés** (`TYPED_TEST`).
- **Tests de mort et de crash** (`EXPECT_DEATH`).
- **Mocking avec Google Mock** (`EXPECT_CALL`, `ON_CALL`).
- **Couverture des tests** et **bonnes pratiques**.

---

## 🎯 Exercice Pratique

Un cas d’étude basé sur une application MQTT est inclus dans la formation. Vous pourrez :
- Développer une application MQTT.
- Tester les interactions en utilisant Google Mock.
- Expérimenter les **assertions avancées** et les **fixtures de test**.

---

## 🔗 Ressources

- [Documentation officielle de Google Test](https://google.github.io/googletest/)
- [Bazel - Google’s Build Tool](https://bazel.build/)
- [GitHub du projet](https://github.com/abbasahmad/formationgtest)

---

## 💜 Contact

📧 **Dr. Abbas AHMAD**  
📩 abbas.ahmad@certilog.ae  

Si vous avez des questions ou des remarques, n'hésitez pas à **poser des questions**, **faire des commentaires** et **partager vos expériences** ! 🚀

