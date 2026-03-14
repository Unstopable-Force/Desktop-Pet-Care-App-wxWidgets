#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include "Animal.h"

class AnimalRepository
{
public:

    static void SaveAnimalsToFile(
        const std::vector<Animal>& animals,
        const std::string& fileName
    );

    static std::vector<Animal> LoadAnimalsFromFile(
        const std::string& fileName
    );
};