#include "Data.h"

const std::map<wxString, std::vector<wxString>> FoodMap = {
    { "Dog",     { "Meat", "Dry food", "Fish" }              },
    { "Cat",     { "Fish", "Dry food", "Meat" }              },
    { "Hamster", { "Seeds", "Fruits", "Vegetables" }         },
    { "Pig",     { "Vegetables", "Compound feed", "Fruits" } },
    { "Cow",     { "Hay", "Grass", "Oats" }                  },
    { "Horse",   { "Hay", "Oats", "Grass" }                  },
    { "Goat",    { "Grass", "Hay", "Oats" }                  },
    { "Sheep",   { "Grass", "Compound feed", "Hay" }         },
    { "Chicken", { "Grain", "Compound feed", "Vegetables" }  },
    { "Rabbit",  { "Carrot", "Hay", "Vegetables" }           },
};

const std::map<wxString, std::vector<wxString>> AllergyMap = {
    { "Dog",     { "None", "Chicken", "Beef", "Corn" }       },
    { "Cat",     { "None", "Chicken", "Fish", "Milk" }       },
    { "Hamster", { "None", "Nuts", "Oranges", "Chocolate" }  },
    { "Pig",     { "None", "Potato", "Salt", "Chocolate" }   },
    { "Cow",     { "None", "Garlic", "Onion", "Wheat" }      },
    { "Horse",   { "None", "Oats", "Hay", "Garlic" }         },
    { "Goat",    { "None", "Onion", "Garlic", "Cabbage" }    },
    { "Sheep",   { "None", "Onion", "Potato", "Chocolate" }  },
    { "Chicken", { "None", "Oranges", "Milk", "Salt" }       },
    { "Rabbit",  { "None", "Cabbage", "Potato", "Sugar" }    },
};

const std::map<wxString, int> FoodScaleMap = {
    { "Dog",     3 },
    { "Cat",     2 },
    { "Hamster", 1 },
    { "Pig",     4 },
    { "Cow",     6 },
    { "Horse",   5 },
    { "Goat",    3 },
    { "Sheep",   3 },
    { "Chicken", 2 },
    { "Rabbit",  2 },
};

const std::map<wxString, double> FoodPriceMap = {
    { "Meat",          12.50 },
    { "Dry food",      10.00 },
    { "Fish",          11.25 },
    { "Seeds",          6.25 },
    { "Fruits",         7.50 },
    { "Vegetables",     5.00 },
    { "Compound feed",  8.75 },
    { "Hay",            6.25 },
    { "Grass",          3.75 },
    { "Oats",           5.00 },
    { "Grain",          6.25 },
    { "Carrot",         5.00 },
};