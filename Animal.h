#pragma once
#include <string>

// Структура даних для зберігання інформації про тварину
struct Animal
{
    std::string name;
    std::string kind;
    std::string allergy;
    std::string food;
    int days;
    double price;

    Animal() = default; // Конструктор з пустими значеннями змінних
    
    // Конструктор користувача
    Animal(
        const std::string& n,
        const std::string& k,
        const std::string& a,
        const std::string& f,
        int d,
        double p
    );
};
