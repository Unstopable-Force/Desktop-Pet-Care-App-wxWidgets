#include "Data.h"

const std::map<wxString, std::vector<wxString>> FoodMap = {
	{wxString::FromUTF8("Пес"), {wxString::FromUTF8("М'ясо"), wxString::FromUTF8("Сухий корм"), wxString::FromUTF8("Риба")}},
	{wxString::FromUTF8("Кішка"), {wxString::FromUTF8("Риба"), wxString::FromUTF8("Сухий корм"), wxString::FromUTF8("М'ясо")}},
	{wxString::FromUTF8("Хом'як"), {wxString::FromUTF8("Насіння"), wxString::FromUTF8("Фрукти"), wxString::FromUTF8("Овочі")}},
	{wxString::FromUTF8("Свиня"), {wxString::FromUTF8("Овочі"), wxString::FromUTF8("Комбікорм"), wxString::FromUTF8("Фрукти")}},
	{wxString::FromUTF8("Корова"), {wxString::FromUTF8("Сіно"), wxString::FromUTF8("Трава"), wxString::FromUTF8("Овес")}},
	{wxString::FromUTF8("Кінь"), {wxString::FromUTF8("Сіно"), wxString::FromUTF8("Овес"), wxString::FromUTF8("Трава")}},
	{wxString::FromUTF8("Коза"), {wxString::FromUTF8("Трава"), wxString::FromUTF8("Сіно"), wxString::FromUTF8("Овес")}},
	{wxString::FromUTF8("Вівця"), {wxString::FromUTF8("Трава"), wxString::FromUTF8("Комбікорм"), wxString::FromUTF8("Сіно")}},
	{wxString::FromUTF8("Куриця"), {wxString::FromUTF8("Зерно"), wxString::FromUTF8("Комбікорм"), wxString::FromUTF8("Овочі")}},
	{wxString::FromUTF8("Кролик"), {wxString::FromUTF8("Морква"), wxString::FromUTF8("Сіно"), wxString::FromUTF8("Овочі")}}
};

const std::map<wxString, std::vector<wxString>> AllergyMap = {
	{wxString::FromUTF8("Пес"), {wxString::FromUTF8("Немає"), wxString::FromUTF8("Курка"), wxString::FromUTF8("Яловичина"), wxString::FromUTF8("Кукурудза")}},
	{wxString::FromUTF8("Кішка"), {wxString::FromUTF8("Немає"), wxString::FromUTF8("Курка"), wxString::FromUTF8("Риба"), wxString::FromUTF8("Молоко")}},
	{wxString::FromUTF8("Хом'як"), {wxString::FromUTF8("Немає"), wxString::FromUTF8("Горіхи"), wxString::FromUTF8("Апельсини"), wxString::FromUTF8("Шоколад")}},
	{wxString::FromUTF8("Свиня"), {wxString::FromUTF8("Немає"), wxString::FromUTF8("Картопля"), wxString::FromUTF8("Сіль"), wxString::FromUTF8("Шоколад")}},
	{wxString::FromUTF8("Корова"), {wxString::FromUTF8("Немає"), wxString::FromUTF8("Часник"), wxString::FromUTF8("Цибуля"), wxString::FromUTF8("Пшениця")}},
	{wxString::FromUTF8("Кінь"), {wxString::FromUTF8("Немає"), wxString::FromUTF8("Овес"), wxString::FromUTF8("Сіно"), wxString::FromUTF8("Часник")}},
	{wxString::FromUTF8("Коза"), {wxString::FromUTF8("Немає"), wxString::FromUTF8("Цибуля"), wxString::FromUTF8("Часник"), wxString::FromUTF8("Капуста")}},
	{wxString::FromUTF8("Вівця"), {wxString::FromUTF8("Немає"), wxString::FromUTF8("Цибуля"), wxString::FromUTF8("Картопля"), wxString::FromUTF8("Шоколад")}},
	{wxString::FromUTF8("Куриця"), {wxString::FromUTF8("Немає"), wxString::FromUTF8("Апельсини"), wxString::FromUTF8("Молоко"), wxString::FromUTF8("Сіль")}},
	{wxString::FromUTF8("Кролик"), {wxString::FromUTF8("Немає"), wxString::FromUTF8("Капуста"), wxString::FromUTF8("Картопля"), wxString::FromUTF8("Цукор")}}
};

const std::map<wxString, int> FoodScaleMap = {
	{wxString::FromUTF8("Пес"), 3},
	{wxString::FromUTF8("Кішка"), 2},
	{wxString::FromUTF8("Хом'як"), 1},
	{wxString::FromUTF8("Свиня"), 4},
	{wxString::FromUTF8("Корова"), 6},
	{wxString::FromUTF8("Кінь"), 5},
	{wxString::FromUTF8("Коза"), 3},
	{wxString::FromUTF8("Вівця"), 3},
	{wxString::FromUTF8("Куриця"), 2},
	{wxString::FromUTF8("Кролик"), 2}
};

const std::map<wxString, double> FoodPriceMap = {
	{wxString::FromUTF8("М'ясо"), 12.5},
	{wxString::FromUTF8("Сухий корм"), 10.0},
	{wxString::FromUTF8("Риба"), 11.25},
	{wxString::FromUTF8("Насіння"), 6.25},
	{wxString::FromUTF8("Фрукти"), 7.5},
	{wxString::FromUTF8("Овочі"), 5.0},
	{wxString::FromUTF8("Комбікорм"), 8.75},
	{wxString::FromUTF8("Сіно"), 6.25},
	{wxString::FromUTF8("Трава"), 3.75},
	{wxString::FromUTF8("Овес"), 5.0},
	{wxString::FromUTF8("Зерно"), 6.25},
	{wxString::FromUTF8("Морква"), 5.0}
};
