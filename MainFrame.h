#pragma once
#include "Animal.h"
#include "Program.h"
#include "Data.h"
#include "AnimalRepository.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <fstream>

#pragma execution_character_set("utf-8")

// Klasa głównego okna aplikacji
class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);  // Konstruktor okna

    std::vector<Animal> animals; // Lista zwierząt

private:
    // Obsługa kliknięć przycisków
    void OnButtonAddClicked(wxCommandEvent& evt);
    void OnButtonDeleteClicked(wxCommandEvent& evt);
    void OnButtonChangeClicked(wxCommandEvent& evt);
    void OnButtonCleanClicked(wxCommandEvent& evt);

    // Obsługa zmiany typu zwierzęcia
    void OnKindChanged(wxCommandEvent& evt);

    // Dane aktualnie wprowadzane przez użytkownika
    wxString name;
    wxString kind;
    wxString allergy;
    wxString food;
    int days;
    double price;

    // Dane do UI
    wxArrayString KindsUI;
    wxArrayString AllergiesUI;
    wxArrayString FoodUI;

    // Elementy interfejsu
    wxPanel* panel;

    wxButton* buttonAdd;
    wxButton* buttonChange;
    wxButton* buttonDelete;
    wxButton* buttonClean;

    // Pola wejściowe
    wxSpinCtrl* chooseDays;
    wxTextCtrl* chooseName;
    wxChoice* chooseKind;
    wxChoice* chooseAllergy;
    wxChoice* chooseFood;

    // Lista zwierząt
    wxListBox* listAnimals;
};