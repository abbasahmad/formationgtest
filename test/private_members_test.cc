#include "gtest/gtest.h"

// Dans le fichier car.h par example mais ici on simplifie
class Car {
public:
  // Méthode publique pour obtenir la consommation de carburant
  double GetFuelConsumption(double distance, double fuelUsed) {
    return CalculateFuelEfficiency(distance, fuelUsed);
  }

private:
  //Decration methode AMI
  FRIEND_TEST(CarTest, CalculateFuelEfficiencyTest);

  // Méthode privée pour calculer l'efficacité énergétique
  double CalculateFuelEfficiency(double distance, double fuelUsed) {
    if (distance <= 0 || fuelUsed <= 0) {
      return 0;
    }
    return distance / fuelUsed; // Efficacité en km par litre
  }
};

//VERIFIER LES 3 cas suivant:

    // 10 km/L
    // Distance nulle
    // Carburant nul

//...