#include "MainFrame.h"

// Конструктор основного вікна
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) 
{
	wxFont mainFont(wxFontInfo(wxSize(0, 12)).Light());
	
	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	buttonAdd = new wxButton(panel, wxID_ANY, wxString::FromUTF8("Додати"), wxPoint(30, 20), wxSize(90, 35));
	buttonChange = new wxButton(panel, wxID_ANY, wxString::FromUTF8("Змінити"), wxPoint(130, 20), wxSize(90, 35));
	buttonDelete = new wxButton(panel, wxID_ANY, wxString::FromUTF8("Видалити"), wxPoint(230, 20), wxSize(90, 35));
	buttonClean = new wxButton(panel, wxID_ANY, wxString::FromUTF8("Очистити"), wxPoint(330, 20), wxSize(90, 35));

	wxStaticText* staticName = new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("Кличка"), wxPoint(45, 70));
	wxStaticText* staticKind = new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("Вид"), wxPoint(130, 70));
	wxStaticText* staticAllergy = new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("Алергія"), wxPoint(213, 70));
	wxStaticText* staticFood = new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("Їжа"), wxPoint(327, 70));
	wxStaticText* staticPrice = new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("Розрахувати ціну їжі за кількість днів"), wxPoint(390, 60), wxSize(120,40));
	
	chooseName = new wxTextCtrl(panel, wxID_ANY, wxString::FromUTF8(""), wxPoint(35, 100), wxSize(60, -1));

	//Узупевнення списку тварин для вибору користувачем
	for (const auto& i : FoodMap) {
		KindsUI.Add(i.first);		
	}

	chooseKind = new wxChoice(panel, wxID_ANY, wxPoint(105, 100), wxSize(70, -1), KindsUI);
	chooseAllergy = new wxChoice(panel, wxID_ANY, wxPoint(185, 100), wxSize(95, -1), AllergiesUI);
	chooseFood = new wxChoice(panel, wxID_ANY, wxPoint(291, 100), wxSize(95, -1), FoodUI);
	chooseDays = new wxSpinCtrl(panel, wxID_ANY, "1", wxPoint(410, 100), wxSize(70, -1), wxSP_WRAP);
	chooseDays->SetRange(1, 365);	

	buttonAdd->Bind(wxEVT_BUTTON, &MainFrame::OnButtonAddClicked, this);
	buttonChange->Bind(wxEVT_BUTTON, &MainFrame::OnButtonChangeClicked, this);
	buttonDelete->Bind(wxEVT_BUTTON, &MainFrame::OnButtonDeleteClicked, this);
	buttonClean->Bind(wxEVT_BUTTON, &MainFrame::OnButtonCleanClicked, this);

	chooseKind->Bind(wxEVT_CHOICE, &MainFrame::OnKindChanged, this);

	listAnimals = new wxListBox(panel, wxID_ANY, wxPoint(37, 140), wxSize(700, 400));
	animals = AnimalRepository::LoadAnimalsFromFile("animals.txt");

	for (const auto& a : animals) {
		wxString line = wxString::FromUTF8(a.kind) + " " + wxString::FromUTF8(a.name) +
		wxString::FromUTF8(".   Вибрана їжа: ") + wxString::FromUTF8(a.food) +
		(a.allergy != "Немає" ? wxString::FromUTF8(".   Продукт на який має алергію: ") + wxString::FromUTF8(a.allergy) : wxString("")) +
		wxString::FromUTF8(".   Ціна харчування: ") +
		wxString::Format(wxString::FromUTF8("%.2f грн за %.d дн."), a.price, a.days);
		listAnimals->Append(line);
	}
}

void MainFrame::OnButtonAddClicked(wxCommandEvent& evt)
{
	name = chooseName->GetValue().Trim(TRUE); // Отримуємо кличку

	if (chooseKind->GetSelection() != -1)
		kind = chooseKind->GetString(chooseKind->GetSelection()); // Отримуємо вид тварини

	if (chooseAllergy->GetSelection() != -1)
		allergy = chooseAllergy->GetString(chooseAllergy->GetSelection()); // Отримуємо алергію

	if (chooseFood->GetSelection() != -1)
		food = chooseFood->GetString(chooseFood->GetSelection()); // Отримуємо їжу

	days = chooseDays->GetValue();

	// Перевірка обов'язкових полів
	if (name.IsEmpty())
	{
		wxMessageBox(wxString::FromUTF8("Будь ласка, введіть кличку тварини."), wxString::FromUTF8("Помилка"), wxICON_WARNING);
		return;
	}

	if (kind.IsEmpty())
	{
		wxMessageBox(wxString::FromUTF8("Будь ласка, оберіть вид тварини."), wxString::FromUTF8("Помилка"), wxICON_WARNING);
		return;
	}

	if (food.IsEmpty())
	{
		wxMessageBox(wxString::FromUTF8("Будь ласка, оберіть їжу для тварини."), wxString::FromUTF8("Помилка"), wxICON_WARNING);
		return;
	}

	// Перевірка алергії
	if (!allergy.IsEmpty() && allergy != wxString::FromUTF8("Немає"))
	{
		if (food == allergy)
		{
			wxMessageBox(wxString::FromUTF8("Обрана їжа викликає алергію! Будь ласка, оберіть іншу."), wxString::FromUTF8("Увага"), wxICON_WARNING);
			return;
		}
	}

	// Розрахунок ціни
	price = FoodScaleMap.at(kind) * FoodPriceMap.at(food) * days;

	// Вивід у список напряму
	listAnimals->Insert(
		kind + " " + name +
		wxString::FromUTF8(".   Вибрана їжа: ") + food +
		((!allergy.IsEmpty() && allergy != wxString::FromUTF8("Немає")) ? (wxString::FromUTF8(".   Продукт на який має алергію: ") + allergy) : wxString("")) +
		wxString::FromUTF8(".   Ціна харчування: ") +
		wxString::Format(wxString::FromUTF8("%.2f грн за %.d дн."), price, days),
		listAnimals->GetCount()
	);

	// Збереження в вектор і файл
	animals.push_back(Animal{
		std::string(name.ToUTF8().data()),
		std::string(kind.ToUTF8().data()),
		std::string(allergy.ToUTF8().data()),
		std::string(food.ToUTF8().data()),
		days,
		price });

	AnimalRepository::SaveAnimalsToFile(animals, "animals.txt");
}

void MainFrame::OnButtonDeleteClicked(wxCommandEvent& evt)
{
	int selection = listAnimals->GetSelection();
	if (selection != wxNOT_FOUND) {
		listAnimals->Delete(selection);              // Удаляем из списка
		animals.erase(animals.begin() + selection);  // Удаляем из вектора
		AnimalRepository::SaveAnimalsToFile(animals, "animals.txt");   // Перезаписываем файл без удалённой строки
	}
	else {
		wxMessageBox(wxString::FromUTF8("Будь ласка, виберіть тварину для видалення."), wxString::FromUTF8("Увага"), wxICON_INFORMATION);
	}
}

void MainFrame::OnButtonChangeClicked(wxCommandEvent& evt)
{
	int selected = listAnimals->GetSelection();
	if (selected == wxNOT_FOUND)
	{
		wxMessageBox(wxString::FromUTF8("Будь ласка, виберіть тварину для редагування."), wxString::FromUTF8("Помилка"), wxICON_WARNING);
		return;
	}

	name = chooseName->GetValue().Trim(TRUE);

	if (name.IsEmpty())
	{
		wxMessageBox(wxString::FromUTF8("Будь ласка, введіть ім’я тварини."), wxString::FromUTF8("Помилка"), wxICON_WARNING);
		return;
	}

	if (chooseKind->GetSelection() != -1)
		kind = chooseKind->GetString(chooseKind->GetSelection());

	if (chooseAllergy->GetSelection() != -1)
		allergy = chooseAllergy->GetString(chooseAllergy->GetSelection());

	if (chooseFood->GetSelection() != -1)
		food = chooseFood->GetString(chooseFood->GetSelection());

	days = chooseDays->GetValue();

	if (kind.IsEmpty())
	{
		wxMessageBox(wxString::FromUTF8("Будь ласка, оберіть вид тварини."), wxString::FromUTF8("Помилка"), wxICON_WARNING);
		return;
	}

	if (food.IsEmpty())
	{
		wxMessageBox(wxString::FromUTF8("Будь ласка, оберіть їжу."), wxString::FromUTF8("Помилка"), wxICON_WARNING);
		return;
	}

	if (!allergy.IsEmpty() && allergy != wxString::FromUTF8("Немає") && food == allergy)
	{
		wxMessageBox(wxString::FromUTF8("Обрана їжа викликає алергію! Будь ласка, оберіть іншу."), wxString::FromUTF8("Увага"), wxICON_WARNING);
		return;
	}

	price = FoodScaleMap.at(kind) * FoodPriceMap.at(food) * days;

	animals[selected] = Animal{
		std::string(wxString(name).ToUTF8().data()),
		std::string(wxString(kind).ToUTF8().data()),
		std::string(wxString(allergy).ToUTF8().data()),
		std::string(wxString(food).ToUTF8().data()),
		days,
		price
	};

	listAnimals->SetString(selected,
		kind + " " + name +
		wxString::FromUTF8(".   Вибрана їжа: ") + food +
		((!allergy.IsEmpty() && allergy != wxString::FromUTF8("Немає")) ? wxString::FromUTF8(".   Продукт на який має алергію: ") + allergy : wxString("")) +
		wxString::FromUTF8(".   Ціна харчування: ") +
		wxString::Format(wxString::FromUTF8("%.2f грн за %d дн."), price, days)
	);

	AnimalRepository::SaveAnimalsToFile(animals, "animals.txt");
}

void MainFrame::OnButtonCleanClicked(wxCommandEvent& evt)
{
	listAnimals->Clear();

	// Очищаем вектор животных
	animals.clear();

	// Перезаписываем файл пустым
	ofstream file("animals.txt", ios::trunc);
	file.close();
}

void MainFrame::OnKindChanged(wxCommandEvent& evt)
{
	chooseFood->Clear();
	chooseAllergy->Clear();

	food = "";
	allergy = "";

	kind = chooseKind->GetString(chooseKind->GetSelection());

	auto foodIteretaor = FoodMap.find(kind);
	for (const auto& product : foodIteretaor->second) {
		chooseFood->Append(product);
	}

	auto allergyIteretor = AllergyMap.find(kind);
	for (const auto& allergicProduct : allergyIteretor->second) {
		chooseAllergy->Append(allergicProduct);
	}
	


}
