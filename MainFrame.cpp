#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    wxFont mainFont(wxFontInfo(wxSize(0, 12)).Light());

    panel = new wxPanel(this);
    panel->SetFont(mainFont);

    // Buttons
    buttonAdd = new wxButton(panel, wxID_ANY, "Add", wxPoint(30, 20), wxSize(90, 35));
    buttonChange = new wxButton(panel, wxID_ANY, "Edit", wxPoint(130, 20), wxSize(90, 35));
    buttonDelete = new wxButton(panel, wxID_ANY, "Delete", wxPoint(230, 20), wxSize(90, 35));
    buttonClean = new wxButton(panel, wxID_ANY, "Clear", wxPoint(330, 20), wxSize(90, 35));

    // Labels
    new wxStaticText(panel, wxID_ANY, "Name", wxPoint(45, 70));
    new wxStaticText(panel, wxID_ANY, "Kind", wxPoint(130, 70));
    new wxStaticText(panel, wxID_ANY, "Allergy", wxPoint(213, 70));
    new wxStaticText(panel, wxID_ANY, "Food", wxPoint(327, 70));
    new wxStaticText(panel, wxID_ANY, "Calculate food cost by days",
        wxPoint(390, 60), wxSize(160, 40));

    // Input controls
    chooseName = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(35, 100), wxSize(60, -1));

    for (const auto& [kindName, _] : FoodMap)
        kindsUI.Add(kindName);

    chooseKind = new wxChoice(panel, wxID_ANY, wxPoint(105, 100), wxSize(90, -1), kindsUI);
    chooseAllergy = new wxChoice(panel, wxID_ANY, wxPoint(200, 100), wxSize(100, -1), allergiesUI);
    chooseFood = new wxChoice(panel, wxID_ANY, wxPoint(310, 100), wxSize(100, -1), foodUI);

    chooseDays = new wxSpinCtrl(panel, wxID_ANY, "1", wxPoint(420, 100), wxSize(70, -1), wxSP_WRAP);
    chooseDays->SetRange(1, 365);

    buttonAdd->Bind(wxEVT_BUTTON, &MainFrame::OnButtonAddClicked, this);
    buttonChange->Bind(wxEVT_BUTTON, &MainFrame::OnButtonChangeClicked, this);
    buttonDelete->Bind(wxEVT_BUTTON, &MainFrame::OnButtonDeleteClicked, this);
    buttonClean->Bind(wxEVT_BUTTON, &MainFrame::OnButtonCleanClicked, this);
    chooseKind->Bind(wxEVT_CHOICE, &MainFrame::OnKindChanged, this);

    listAnimals = new wxListBox(panel, wxID_ANY, wxPoint(37, 140), wxSize(700, 400));

    animals = AnimalRepository::LoadAnimalsFromFile("animals.txt");
    for (const auto& a : animals)
        listAnimals->Append(FormatAnimalEntry(a));
}

wxString MainFrame::FormatAnimalEntry(const Animal& a) const
{
    wxString entry = a.kind + " " + a.name +
        ".   Selected food: " + a.food;

    if (a.allergy != "None" && !a.allergy.empty())
        entry += ".   Allergy: " + a.allergy;

    entry += wxString::Format(".   Food cost: %.2f UAH for %d days", a.price, a.days);
    return entry;
}

bool MainFrame::ReadFormFields(wxString& outName, wxString& outKind,
    wxString& outAllergy, wxString& outFood, int& outDays)
{
    outName = chooseName->GetValue().Trim(true);
    if (outName.IsEmpty()) {
        wxMessageBox("Please enter an animal name.", "Error", wxICON_WARNING);
        return false;
    }

    if (chooseKind->GetSelection() == wxNOT_FOUND) {
        wxMessageBox("Please select an animal kind.", "Error", wxICON_WARNING);
        return false;
    }
    outKind = chooseKind->GetString(chooseKind->GetSelection());

    if (chooseFood->GetSelection() == wxNOT_FOUND) {
        wxMessageBox("Please select a food type.", "Error", wxICON_WARNING);
        return false;
    }
    outFood = chooseFood->GetString(chooseFood->GetSelection());

    // Allergy is optional; wxString() explicit cast required to avoid C2445
    outAllergy = (chooseAllergy->GetSelection() != wxNOT_FOUND)
        ? chooseAllergy->GetString(chooseAllergy->GetSelection())
        : wxString("None");

    if (outAllergy != "None" && outAllergy == outFood) {
        wxMessageBox("Selected food causes an allergy!", "Warning", wxICON_WARNING);
        return false;
    }

    outDays = chooseDays->GetValue();
    return true;
}

void MainFrame::OnButtonAddClicked(wxCommandEvent& /*evt*/)
{
    if (!ReadFormFields(name, kind, allergy, food, days))
        return;

    price = FoodScaleMap.at(kind) * FoodPriceMap.at(food) * days;

    Animal a{ std::string(name.mb_str()),
              std::string(kind.mb_str()),
              std::string(allergy.mb_str()),
              std::string(food.mb_str()),
              days, price };

    animals.push_back(a);
    listAnimals->Append(FormatAnimalEntry(a));
    AnimalRepository::SaveAnimalsToFile(animals, "animals.txt");
}

void MainFrame::OnButtonDeleteClicked(wxCommandEvent& /*evt*/)
{
    const int selection = listAnimals->GetSelection();

    if (selection == wxNOT_FOUND) {
        wxMessageBox("Please select an animal to delete.", "Warning", wxICON_INFORMATION);
        return;
    }

    listAnimals->Delete(selection);
    animals.erase(animals.begin() + selection);
    AnimalRepository::SaveAnimalsToFile(animals, "animals.txt");
}

void MainFrame::OnButtonChangeClicked(wxCommandEvent& /*evt*/)
{
    const int selected = listAnimals->GetSelection();

    if (selected == wxNOT_FOUND) {
        wxMessageBox("Please select an animal to edit.", "Error", wxICON_WARNING);
        return;
    }

    if (!ReadFormFields(name, kind, allergy, food, days))
        return;

    price = FoodScaleMap.at(kind) * FoodPriceMap.at(food) * days;

    animals[selected] = { std::string(name.mb_str()),
                          std::string(kind.mb_str()),
                          std::string(allergy.mb_str()),
                          std::string(food.mb_str()),
                          days, price };

    listAnimals->SetString(selected, FormatAnimalEntry(animals[selected]));
    AnimalRepository::SaveAnimalsToFile(animals, "animals.txt");
}

void MainFrame::OnButtonCleanClicked(wxCommandEvent& /*evt*/)
{
    listAnimals->Clear();
    animals.clear();
    AnimalRepository::SaveAnimalsToFile(animals, "animals.txt");
}

void MainFrame::OnKindChanged(wxCommandEvent& /*evt*/)
{
    chooseFood->Clear();
    chooseAllergy->Clear();
    food.clear();
    allergy.clear();

    kind = chooseKind->GetString(chooseKind->GetSelection());

    for (const auto& product : FoodMap.at(kind))
        chooseFood->Append(product);

    for (const auto& item : AllergyMap.at(kind))
        chooseAllergy->Append(item);
}