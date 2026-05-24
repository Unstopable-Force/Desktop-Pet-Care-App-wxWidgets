# Animal Care

A desktop application for managing animals and calculating their food costs, built with **C++17** and **wxWidgets**.

---

## Features

- Add, edit, and delete animal records
- Select animal kind, food type, and allergy information
- Automatic food cost calculation based on kind, food, and number of days
- Allergy conflict detection — warns if the selected food matches a known allergen
- Persistent storage — records are saved to and loaded from a local file automatically

---

## Requirements

| Dependency | Version       |
|------------|---------------|
| C++        | 17 or later   |
| wxWidgets  | 3.2+          |
| Compiler   | MSVC / GCC / Clang |

---

## Building

### Windows (Visual Studio)

1. Install [wxWidgets](https://www.wxwidgets.org/downloads/) and set the `WXWIN` environment variable.
2. Open the `.sln` file in Visual Studio.
3. Select `Release` or `Debug` configuration.
4. Build the solution (`Ctrl+Shift+B`).

### Linux / macOS

```bash
sudo apt install libwxgtk3.2-dev   # Ubuntu/Debian

mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

---

## Project Structure

```
AnimalCare/
├── Animal.h                 # Animal data structure (aggregate, no .cpp needed)
├── AnimalRepository.h/.cpp  # File I/O — save and load records (namespace)
├── Data.h/.cpp              # Static data: food, allergy, and price tables
├── MainFrame.h/.cpp         # Main application window
├── Program.h/.cpp           # wxApp entry point
└── animals.txt              # Auto-generated on first save
```

---

## Data File Format

Records are stored in `animals.txt` using pipe-delimited fields:

```
name|kind|allergy|food|days|price
```

Example:
```
Buddy|Dog|None|Meat|7|262.50
Whiskers|Cat|Fish|Dry food|14|280.00
```

Lines with missing or malformed fields are silently skipped on load.

---

## Cost Calculation

```
Total Cost (UAH) = FoodScaleMap[kind] × FoodPriceMap[food] × days
```

`FoodScaleMap` is a per-animal daily consumption multiplier; `FoodPriceMap` is the unit price in UAH.

| Animal  | Scale | Example food  | Unit price |
|---------|-------|---------------|------------|
| Dog     | 3     | Meat          | 12.50 UAH  |
| Cat     | 2     | Fish          | 11.25 UAH  |
| Horse   | 5     | Hay           | 6.25 UAH   |
| Hamster | 1     | Seeds         | 6.25 UAH   |

Full tables are defined in `Data.cpp`.

---

## License

This project is licensed under the **MIT License** — see [LICENSE](LICENSE) for details.
