# C++ Tic-Tac-Toe with a WebAssembly AI

A fully playable Tic-Tac-Toe game that runs in any modern web browser. The game features a clean, responsive UI and an unbeatable AI opponent. The core game logic and the Minimax AI are written entirely in C++ and compiled to WebAssembly (Wasm) using Emscripten.

![game](game.png)
---

## Features

* **C++ Core Engine:** All game logic, state management, and AI are written in modern C++.
* **Unbeatable AI:** The AI opponent uses the recursive Minimax algorithm to find the optimal move, making it impossible to defeat.
* **WebAssembly Powered:** The C++ engine is compiled to a highly efficient WebAssembly module, allowing it to run in the browser at near-native speed.
* **Responsive UI:** The HTML/CSS frontend is fully responsive and provides a clean, playable experience on both desktop and mobile devices.
* **Player Symbol Choice:** Players can choose to play as 'X' or 'O' at the start of each game.

---

## Tech Stack

* **Core:** C++17
* **Compiler/Toolchain:** Emscripten (Clang/LLVM)
* **Target:** WebAssembly (Wasm)
* **Frontend:** HTML5, CSS3, Vanilla JavaScript

---

## Setup and Build Instructions

To build and run this project yourself, you will need **Git** and the **Emscripten SDK**.

### 1. Clone the Repository
```bash
git clone <your-repo-url>
cd <your-repo-folder>
```

### 2\. Configure the Build Script

This project uses a batch file (`build.bat`) to automate compilation. You will need to edit this file to point to your local Emscripten SDK installation.

  * Open **`build.bat`** in a text editor.
  * Find the following line:
    ```batch
    call C:\Users\krish\emsdk\emsdk_env.bat
    ```
  * **IMPORTANT:** Change `C:\Users\krish\emsdk` to the correct path where you installed the `emsdk`.

### 3\. Build the Wasm Module

Run the build script from your terminal.

```bash
build.bat
```

This will compile the C++ source files (`main.cpp`, `game.cpp`) into `game.js` and `game.wasm` in the project's root directory.

### 4\. Run the Local Server

Modern browsers do not allow web pages to load Wasm modules directly from the local file system due to security policies (CORS). You must use a local web server. This project is configured to work well with Python's built-in server.

  * In your terminal, run:
    ```bash
    python -m http.server
    ```
  * Open your web browser and navigate to:
    **`http://localhost:8000`**

-----