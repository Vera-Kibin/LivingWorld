# 🌍 LivingWorld

LivingWorld is an interactive desktop simulation built in **C++ with Qt Widgets**, focused on applying **object-oriented programming principles** in a real, visual environment.

The project represents a **tile-based ecosystem**, where the user can design terrain, place organisms, and observe how the world evolves over time through a **turn-based simulation**.

Unlike traditional console implementations, this version introduces a **fully interactive GUI**, making the simulation dynamic and intuitive.

---

## 🎯 Project Purpose

This project was created to explore:

- practical OOP in C++ (not just theory),
- class hierarchy design,
- polymorphism in real systems,
- GUI programming with Qt,
- simulation logic and state updates.

The goal was to **combine architecture + interaction**, not just write static code.

---

## ✨ Key Features

- Interactive tile-based world editor
- Multiple terrain types (Grass, Desert, Water)
- Manual and automatic environment configuration
- Turn-based ecosystem simulation
- Dynamic organism behavior (movement, reproduction, survival)
- Object-oriented architecture with polymorphism

---

## 🌱 Terrain System

The world consists of a grid of tiles that can represent different environments.

<p align="center">
  <img src="https://github.com/user-attachments/assets/84cc1568-f9e3-496a-b036-c9333f63201f" width="48%" />
  <img src="https://github.com/user-attachments/assets/a5f36b0d-dd8e-4f29-ac09-b0388a85ddaf" width="48%" />
</p>

<p align="center"><i>Grass 🌿 vs Desert 🏜️ environments</i></p>

### 🌿 Grass

- default ecosystem,
- supports organism life,
- allows reproduction,
- higher water availability (~10%).

### 🏜️ Desert

- harsher environment,
- reduced water (~8%),
- limits expansion potential,
- designed as a base for future survival mechanics.

---

## 💧 Water System

Water dynamically changes the environment.

### Demo

[▶️ Watch demo](https://github.com/user-attachments/assets/fe399c12-f533-4d93-b364-464850f21415)

### Features

- automatic generation,
- manual placement,
- toggle on click (add/remove),
- limited quantity based on terrain.

### Influence

- blocks movement,
- affects plant growth,
- limits organism placement.

---

## 🐑 Organisms

Organisms are divided into two categories:

### 🐾 Animals

- Sheep (`S`)
- Wolf (`W`)

### 🌼 Plants

- Dandelion (`D`)
- Toadstool (`T`)

Currently represented as symbols for simplicity (can be replaced with icons later).

---

## Behavior System

### 🐑 Sheep

- moves randomly,
- gains power each turn,
- loses life over time,
- reproduces only if:
  - another sheep is nearby,
  - enough power is reached,
  - free tile exists.

👉 Example:
[▶️ Watch demo](https://github.com/user-attachments/assets/fb9d2b63-a021-48c3-ac29-7afe329780fe)

---

### 🐺 Wolf

- hunts sheep,
- prioritizes eating over movement,
- gains power after eating,
- replaces prey on tile,
- dies from aging.

---

### 🌼 Dandelion

- spreads passively to nearby tiles,
- simple expansion logic,
- does not depend on power.

---

### 🍄 Toadstool

- spreads conditionally,
- grows only every few turns,
- avoids water proximity,
- checks environment before spawning.

👉 More complex environmental behavior than dandelion.

---

## Simulation Engine

The world evolves in discrete turns.

Each turn:

1. organisms act,
2. movement / spreading happens,
3. dead organisms are removed.

👉 Example state:

### Demo

[▶️ Watch demo](https://github.com/user-attachments/assets/ebe4c728-c701-4ccf-9317-9b6ca20415bc)

---

## Debug Output

<p align="center">
  <img src="https://github.com/user-attachments/assets/958165a0-fa99-414b-871f-3f7bc14e9795" width="40%" />
</p>

<p align="center"><i>Console logs showing simulation steps</i></p>

---

## 🧩 Architecture

```text
Organism
├── Animal
│   ├── Sheep
│   └── Wolf
└── Plant
    ├── Dandelion
    └── Toadstool

Components
	•	MainWindow → GUI, interaction, simulation control
	•	Tile → single cell (terrain + organism)
	•	Organism → base abstract class
	•	Animal / Plant → abstraction layers
```

---

### 🧠 OOP Concepts

#### Abstraction

General organism logic defined in base classes.

#### Inheritance

Concrete organisms extend shared behavior.

#### Polymorphism

```cpp
std::vector<Organism*> organisms;
org->performTurn();
```

#### Encapsulation

Each class manages its own state and logic.

---

### Key Design Decision

Turn execution is done on a copy of organism list, which prevents crashes and invalid memory access during iteration.

This is a critical detail for simulation stability.

---

## 🛠️ Tools and Technologies Used

- **C++**: Core programming language.
- **Qt Widgets**: GUI framework for building the interactive interface.
- **CMake**: Build system for project configuration.
- **Object-Oriented Programming (OOP)**: Core design principle.
- **Git**: Version control for project management.

---

## 🚀 Future Improvements

### 🌦️ Environment

- Weather system (rain, drought).
- Biome zones (forest, farm, desert).
- Terrain-based survival rules.

### 🧬 Biology

- Diseases / infection system.
- More species.
- Food chains.
- Advanced reproduction logic.

### 🎨 Visuals

- Replace symbols with icons / emojis.
- Animations.
- Better UI.

### 🧠 Architecture

- Separation of simulation engine from GUI.
- Smart pointers (memory safety).
- Save/load system.
- Serialization.

---

## Running the Project

### Recommended Steps:

1. Open the project in **Qt Creator**.
2. Configure the **Qt kit**.
3. Build the project using **CMake**.
4. Run the application.

---

## 👩‍💻 Author

Vera Kibin

---

## 📄 License & Attribution

- **Code**: [MIT License](LICENSE)
- **UI demo assets**: Short screen recordings by the author.
