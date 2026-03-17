#include "MainFrame.h"

// Konstruktor głównego okna
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    wxFont mainFont(wxFontInfo(wxSize(0, 12)).Light());

    panel = new wxPanel(this);
    panel->SetFont(mainFont);

    // Przyciski
    buttonAdd = new wxButton(panel, wxID_ANY, "Add", wxPoint(30, 20), wxSize(90, 35));
    buttonChange = new wxButton(panel, wxID_ANY, "Edit", wxPoint(130, 20), wxSize(90, 35));
    buttonDelete = new wxButton(panel, wxID_ANY, "Delete", wxPoint(230, 20), wxSize(90, 35));
    buttonClean = new wxButton(panel, wxID_ANY, "Clear", wxPoint(330, 20), wxSize(90, 35));

    // Etykiety
    wxStaticText* staticName = new wxStaticText(panel, wxID_ANY, "Name", wxPoint(45, 70));
    wxStaticText* staticKind = new wxStaticText(panel, wxID_ANY, "Kind", wxPoint(130, 70));
    wxStaticText* staticAllergy = new wxStaticText(panel, wxID_ANY, "Allergy", wxPoint(213, 70));
    wxStaticText* staticFood = new wxStaticText(panel, wxID_ANY, "Food", wxPoint(327, 70));
    wxStaticText* staticPrice = new wxStaticText(panel, wxID_ANY,
        "Calculate food cost by days", wxPoint(390, 60), wxSize(160, 40));

    chooseName = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(35, 100), wxSize(60, -1));

    // Tworzenie listy typów zwierząt
    for (const auto& i : FoodMap) {
        KindsUI.Add(i.first);
    }

    chooseKind = new wxChoice(panel, wxID_ANY, wxPoint(105, 100), wxSize(90, -1), KindsUI);
    chooseAllergy = new wxChoice(panel, wxID_ANY, wxPoint(200, 100), wxSize(100, -1), AllergiesUI);
    chooseFood = new wxChoice(panel, wxID_ANY, wxPoint(310, 100), wxSize(100, -1), FoodUI);

    chooseDays = new wxSpinCtrl(panel, wxID_ANY, "1", wxPoint(420, 100), wxSize(70, -1), wxSP_WRAP);
    chooseDays->SetRange(1, 365);

    // Bindowanie zdarzeń
    buttonAdd->Bind(wxEVT_BUTTON, &MainFrame::OnButtonAddClicked, this);
    buttonChange->Bind(wxEVT_BUTTON, &MainFrame::OnButtonChangeClicked, this);
    buttonDelete->Bind(wxEVT_BUTTON, &MainFrame::OnButtonDeleteClicked, this);
    buttonClean->Bind(wxEVT_BUTTON, &MainFrame::OnButtonCleanClicked, this);

    chooseKind->Bind(wxEVT_CHOICE, &MainFrame::OnKindChanged, this);

    listAnimals = new wxListBox(panel, wxID_ANY, wxPoint(37, 140), wxSize(700, 400));

    // Wczytanie danych z pliku
    animals = AnimalRepository::LoadAnimalsFromFile("animals.txt");

    for (const auto& a : animals) {
        wxString line = a.kind + " " + a.name +
            ".   Selected food: " + a.food +
            (a.allergy != "None" ? ".   Allergy: " + a.allergy : "") +
            ".   Food cost: " +
            wxString::Format("%.2f UAH for %d days", a.price, a.days);

        listAnimals->Append(line);
    }
}

// Dodawanie zwierzęcia
void MainFrame::OnButtonAddClicked(wxCommandEvent& evt)
{
    name = chooseName->GetValue().Trim(true);

    if (chooseKind->GetSelection() != -1)
        kind = chooseKind->GetString(chooseKind->GetSelection());

    if (chooseAllergy->GetSelection() != -1)
        allergy = chooseAllergy->GetString(chooseAllergy->GetSelection());

    if (chooseFood->GetSelection() != -1)
        food = chooseFood->GetString(chooseFood->GetSelection());

    days = chooseDays->GetValue();

    // Walidacja
    if (name.IsEmpty()) {
        wxMessageBox("Please enter animal name.", "Error", wxICON_WARNING);
        return;
    }

    if (kind.IsEmpty()) {
        wxMessageBox("Please select animal type.", "Error", wxICON_WARNING);
        return;
    }

    if (food.IsEmpty()) {
        wxMessageBox("Please select food.", "Error", wxICON_WARNING);
        return;
    }

    if (!allergy.IsEmpty() && allergy != "None" && food == allergy) {
        wxMessageBox("Selected food causes allergy!", "Warning", wxICON_WARNING);
        return;
    }

    // Obliczanie ceny
    price = FoodScaleMap.at(kind) * FoodPriceMap.at(food) * days;

    // Dodanie do listy
    listAnimals->Append(
        kind + " " + name +
        ".   Selected food: " + food +
        ((!allergy.IsEmpty() && allergy != "None") ? wxString(".   Allergy: ") + allergy : wxString("")) +
        ".   Food cost: " +
        wxString::Format("%.2f UAH for %d days", price, days)
    );

    // Dodanie do wektora
    animals.push_back(Animal{
        std::string(name.mb_str()),
        std::string(kind.mb_str()),
        std::string(allergy.mb_str()),
        std::string(food.mb_str()),
        days,
        price
        });

    AnimalRepository::SaveAnimalsToFile(animals, "animals.txt");
}

// Usuwanie
void MainFrame::OnButtonDeleteClicked(wxCommandEvent& evt)
{
    int selection = listAnimals->GetSelection();

    if (selection != wxNOT_FOUND) {
        listAnimals->Delete(selection);
        animals.erase(animals.begin() + selection);
        AnimalRepository::SaveAnimalsToFile(animals, "animals.txt");
    }
    else {
        wxMessageBox("Please select an animal to delete.", "Warning", wxICON_INFORMATION);
    }
}

// Edycja
void MainFrame::OnButtonChangeClicked(wxCommandEvent& evt)
{
    int selected = listAnimals->GetSelection();

    if (selected == wxNOT_FOUND) {
        wxMessageBox("Please select an animal to edit.", "Error", wxICON_WARNING);
        return;
    }

    name = chooseName->GetValue().Trim(true);

    if (name.IsEmpty()) {
        wxMessageBox("Please enter animal name.", "Error", wxICON_WARNING);
        return;
    }

    if (chooseKind->GetSelection() != -1)
        kind = chooseKind->GetString(chooseKind->GetSelection());

    if (chooseAllergy->GetSelection() != -1)
        allergy = chooseAllergy->GetString(chooseAllergy->GetSelection());

    if (chooseFood->GetSelection() != -1)
        food = chooseFood->GetString(chooseFood->GetSelection());

    days = chooseDays->GetValue();

    if (kind.IsEmpty()) {
        wxMessageBox("Please select animal kind.", "Error", wxICON_WARNING);
        return;
    }

    if (food.IsEmpty()) {
        wxMessageBox("Please select food.", "Error", wxICON_WARNING);
        return;
    }

    if (!allergy.IsEmpty() && allergy != "None" && food == allergy) {
        wxMessageBox("Selected food causes allergy!", "Warning", wxICON_WARNING);
        return;
    }

    price = FoodScaleMap.at(kind) * FoodPriceMap.at(food) * days;

    animals[selected] = Animal{
        std::string(name.mb_str()),
        std::string(kind.mb_str()),
        std::string(allergy.mb_str()),
        std::string(food.mb_str()),
        days,
        price
    };

    listAnimals->SetString(selected,
        kind + " " + name +
        ".   Selected food: " + food +
        ((!allergy.IsEmpty() && allergy != "None") ? wxString(".   Allergy: ") + allergy : wxString("")) +
        ".   Food cost: " +
        wxString::Format("%.2f UAH for %d days", price, days)
    );

    AnimalRepository::SaveAnimalsToFile(animals, "animals.txt");
}

// Czyszczenie listy
void MainFrame::OnButtonCleanClicked(wxCommandEvent& evt)
{
    listAnimals->Clear();

    // Czyszczenie wektora
    animals.clear();

    // Nadpisanie pliku pustym
    std::ofstream file("animals.txt", std::ios::trunc);
    file.close();
}

// Zmiana typu zwierzęcia
void MainFrame::OnKindChanged(wxCommandEvent& evt)
{
    chooseFood->Clear();
    chooseAllergy->Clear();

    food = "";
    allergy = "";

    kind = chooseKind->GetString(chooseKind->GetSelection());

    auto foodIterator = FoodMap.find(kind);
    for (const auto& product : foodIterator->second) {
        chooseFood->Append(product);
    }

    auto allergyIterator = AllergyMap.find(kind);
    for (const auto& item : allergyIterator->second) {
        chooseAllergy->Append(item);
    }
}