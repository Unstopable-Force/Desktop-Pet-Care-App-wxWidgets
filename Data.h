#pragma once
#include <map>
#include <vector>
#include <wx/string.h>

extern const std::map<wxString, std::vector<wxString>> FoodMap;
extern const std::map<wxString, std::vector<wxString>> AllergyMap;
extern const std::map<wxString, int> FoodScaleMap;
extern const std::map<wxString, double> FoodPriceMap;