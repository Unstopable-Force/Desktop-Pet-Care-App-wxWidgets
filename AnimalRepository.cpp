#include "AnimalRepository.h"
#include <fstream>
#include <sstream>
#include <wx/wx.h>

// Функція для збереження тварин в файл
void AnimalRepository::SaveAnimalsToFile(std::vector<Animal>& animals, const std::string& fileName)
{
    ofstream file(fileName);  // Відкриваємо файл для запису
    if (!file.is_open()) {
        wxMessageBox(wxString::FromUTF8("Не вдалося відкрити файл для запису."), wxString::FromUTF8("Помилка"), wxICON_ERROR); //Повідомлення
        return;
    }
    // Записуємо тварин у файл
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

// Функція для завантаження тварин з файлу
std::vector<Animal> AnimalRepository::LoadAnimalsFromFile(const std::string& fileName)
{
    std::vector<Animal> result;
    ifstream file(fileName);  // Відкриваємо файл для читання
    if (!file.is_open())
        return result;  // Якщо не вдалося відкрити, повертаємо порожній вектор

    std::string line;
    while (getline(file, line)) {
        stringstream ss(line);  // Розбиваємо рядок на частини
        Animal animal;
        std::string daysStr, priceStr;

        if (getline(ss, animal.name, '|') &&
            getline(ss, animal.kind, '|') &&
            getline(ss, animal.allergy, '|') &&
            getline(ss, animal.food, '|') &&
            getline(ss, daysStr, '|') &&
            getline(ss, priceStr))
        {
            animal.days = stoi(daysStr);  // Перетворюємо дні в int
            animal.price = stod(priceStr);  // Перетворюємо ціну в double
            result.push_back(animal);  // Додаємо тварину в результат
        }
    }

    file.close();
    return result;
}