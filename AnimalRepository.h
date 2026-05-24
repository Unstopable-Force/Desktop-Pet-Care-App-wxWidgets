#pragma once

#include "Animal.h"
#include <vector>
#include <string>

namespace AnimalRepository
{
    // Overwrites fileName with all animal records; shows an error dialog on failure.
    void SaveAnimalsToFile(const std::vector<Animal>& animals,
        const std::string& fileName);

    // Loads animal records from fileName; returns an empty vector if the file is missing.
    std::vector<Animal> LoadAnimalsFromFile(const std::string& fileName);
}
