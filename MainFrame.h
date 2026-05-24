#pragma once

#include "Animal.h"
#include "Program.h"
#include "Data.h"
#include "AnimalRepository.h"

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <fstream>

#pragma execution_character_set("utf-8")

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    void OnButtonAddClicked(wxCommandEvent& evt);
    void OnButtonDeleteClicked(wxCommandEvent& evt);
    void OnButtonChangeClicked(wxCommandEvent& evt);
    void OnButtonCleanClicked(wxCommandEvent& evt);
    void OnKindChanged(wxCommandEvent& evt);

    // Reads and validates form fields; shows an error dialog on failure.
    // Returns true only when all fields are valid.
    bool ReadFormFields(wxString& outName, wxString& outKind,
        wxString& outAllergy, wxString& outFood, int& outDays);

    wxString FormatAnimalEntry(const Animal& a) const;

    // Data
    std::vector<Animal> animals;

    wxString name;
    wxString kind;
    wxString allergy;
    wxString food;
    int      days = 1;
    double   price = 0.0;

    wxArrayString kindsUI;
    wxArrayString allergiesUI;
    wxArrayString foodUI;

    // UI elements
    wxPanel* panel;
    wxButton* buttonAdd;
    wxButton* buttonChange;
    wxButton* buttonDelete;
    wxButton* buttonClean;

    wxTextCtrl* chooseName;
    wxChoice* chooseKind;
    wxChoice* chooseAllergy;
    wxChoice* chooseFood;
    wxSpinCtrl* chooseDays;

    wxListBox* listAnimals;
};