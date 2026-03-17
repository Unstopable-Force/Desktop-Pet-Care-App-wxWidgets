#include "AnimalRepository.h"
#include <fstream>
#include <sstream>
#include <wx/wx.h>

// Funkcja zapisująca dane zwierząt do pliku
void AnimalRepository::SaveAnimalsToFile(const std::vector<Animal>& animals, const std::string& fileName)
{
    std::ofstream file(fileName);  // Otwieramy plik do zapisu

    if (!file.is_open()) {
        wxMessageBox("Failed to open file for writing.", "Error", wxICON_ERROR); // Komunikat błędu
        return;
    }

    // Zapisujemy dane zwierząt do pliku
    for (const auto& animal : animals) {
        file << animal.name << "|"
            << animal.kind << "|"
            << animal.allergy << "|"
            << animal.food << "|"
            << animal.days << "|"
            << animal.price << "\n";
    }

    file.close();
}

// Funkcja wczytująca dane zwierząt z pliku
std::vector<Animal> AnimalRepository::LoadAnimalsFromFile(const std::string& fileName)
{
    std::vector<Animal> result;
    std::ifstream file(fileName);  // Otwieramy plik do odczytu

    if (!file.is_open())
        return result;  // Jeśli nie udało się otworzyć, zwracamy pusty wektor

    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);  // Dzielimy linię na części

        Animal animal;
        std::string daysStr, priceStr;

        if (getline(ss, animal.name, '|') &&
            getline(ss, animal.kind, '|') &&
            getline(ss, animal.allergy, '|') &&
            getline(ss, animal.food, '|') &&
            getline(ss, daysStr, '|') &&
            getline(ss, priceStr))
        {
            animal.days = stoi(daysStr);     // Konwersja dni na int
            animal.price = stod(priceStr);   // Konwersja ceny na double
            result.push_back(animal);        // Dodanie do listy wynikowej
        }
    }

    file.close();
    return result;
}