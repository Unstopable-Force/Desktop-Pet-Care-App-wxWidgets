#include "AnimalRepository.h"

#include <fstream>
#include <sstream>
#include <wx/wx.h>

namespace AnimalRepository
{

    // File format per line: name|kind|allergy|food|days|price
    void SaveAnimalsToFile(const std::vector<Animal>& animals, const std::string& fileName)
    {
        std::ofstream file(fileName);

        if (!file.is_open()) {
            wxMessageBox("Failed to open file for writing.", "Error", wxICON_ERROR);
            return;
        }

        for (const auto& animal : animals) {
            file << animal.name << '|'
                << animal.kind << '|'
                << animal.allergy << '|'
                << animal.food << '|'
                << animal.days << '|'
                << animal.price << '\n';
        }
    }

    // Lines that cannot be parsed (wrong field count, bad number format) are skipped.
    std::vector<Animal> LoadAnimalsFromFile(const std::string& fileName)
    {
        std::vector<Animal> result;
        std::ifstream file(fileName);

        if (!file.is_open())
            return result;

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty())
                continue;

            std::istringstream ss(line);
            Animal animal;
            std::string daysStr, priceStr;

            if (std::getline(ss, animal.name, '|') &&
                std::getline(ss, animal.kind, '|') &&
                std::getline(ss, animal.allergy, '|') &&
                std::getline(ss, animal.food, '|') &&
                std::getline(ss, daysStr, '|') &&
                std::getline(ss, priceStr))
            {
                animal.days = std::stoi(daysStr);
                animal.price = std::stod(priceStr);
                result.push_back(std::move(animal));
            }
        }

        return result;
    }

} // namespace AnimalRepository