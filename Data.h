#pragma once

#include <map>
#include <vector>
#include <wx/string.h>

// Available food options per animal kind
extern const std::map<wxString, std::vector<wxString>> FoodMap;

// Known allergens per animal kind; first entry is always "None"
extern const std::map<wxString, std::vector<wxString>> AllergyMap;

// Daily food consumption multiplier per animal kind
// Cost formula: FoodScaleMap[kind] * FoodPriceMap[food] * days
extern const std::map<wxString, int> FoodScaleMap;

// Base price per food unit in UAH
extern const std::map<wxString, double> FoodPriceMap;