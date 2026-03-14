#pragma once
#include "Animal.h"
#include "Program.h"
#include "Data.h"
#include "AnimalRepository.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <fstream>

#pragma execution_character_set("utf-8")

// Клас основного вікна програми
class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);  // Конструктор вікна
	std::vector<Animal> animals;
private:
	// Обробники подій для кнопок
	void OnButtonAddClicked(wxCommandEvent& evt);
	void OnButtonDeleteClicked(wxCommandEvent& evt);
	void OnButtonChangeClicked(wxCommandEvent& evt);
	void OnButtonCleanClicked(wxCommandEvent& evt);

	// Обробник зміни виду тварини
	void OnKindChanged(wxCommandEvent& evt);

	// Дані для кожної тварини
	wxString name;
	wxString kind;
	wxString allergy;
	wxString food;
	int days;
	double price;

	// Списки для відображення на UI
	wxArrayString KindsUI;
	wxArrayString AllergiesUI;
	wxArrayString FoodUI;

	// Елементи інтерфейсу
	wxPanel* panel;
	wxButton* buttonAdd;
	wxButton* buttonChange;
	wxButton* buttonDelete;
	wxButton* buttonClean;

	// Компоненти для введення даних
	wxSpinCtrl* chooseDays;
	wxTextCtrl* chooseName;
	wxChoice* chooseKind;
	wxChoice* chooseAllergy;
	wxChoice* chooseFood;
	wxListBox* listAnimals;
};