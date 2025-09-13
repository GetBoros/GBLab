# C++ Learning Plan for Linux Environment

### Our Official Progress Plan

## I. Environment & Workflow Fundamentals

- [x] **Environment Setup**: Installed `g++`, `gdb`, `cmake`, and `git`.
- [x] **VS Code Configuration**: Set up C/C++, CMake Tools extensions, `launch.json`, and `tasks.json`.
- [x] **Build & Run Process**: Mastered the build (`F7`), run (`Ctrl+F5`), and debug (`F5`) cycle.
- [x] **Debugging**: Used breakpoints, variable inspection, and the call stack.
- [x] **Multi-file Projects**: Structured the project with `src/`, `tests/`, and configured `CMakeLists.txt` accordingly.
- [x] **Code Formatting**: Set up `.clang-format` for consistent style and enabled `formatOnSave` in VS Code.

## II. C++ Ecosystem & Tooling

- [x] **Dependency Management**:
  - [x] **Using `FetchContent`**: Automatically downloading and building `raylib`, `googletest`, and `nlohmann/json`.
  - [ ] **Linking System Libraries**: (To be covered when needed).
- [x] **Data Serialization**:
  - [x] **JSON Integration**: Added `nlohmann/json` to handle saving/loading structured data (`.sav` files).
- [x] **Unit Testing**:
  - [x] Introduced GoogleTest framework.
  - [x] Wrote first unit tests.
  - [x] Integrated tests into CMake for execution.
- [x] **Version Control (Git)**:
  - [x] **Core Commands**: `git init`, `add`, `commit`, `push`.
  - [x] **Remote Repositories**: `git remote`, PAT authentication.
  - [x] **History Management**: `git log`, `restore`, `revert`.
  - [x] **Committing Standards**: Adopted the "Conventional Commits" standard (`feat:`, `refactor:`, etc.).

## III. Application Architecture & UI Development

- [x] **Core Architecture**:
  - [x] **State Machine Pattern**: Implemented a `StateManager` to handle different application screens (`HubState`, `ClickerState`, etc.).
- [x] **Component-Based UI**:
  - [x] **Reusable Components**: Created a component system for UI elements (`Icon`, `Button`, `Label`) to enforce DRY principles.
- [x] **Code Reusability**:
  - [x] **Utility Class**: Refactored common functions (like `ColorLerp`) into a static `AsTools` class for project-wide use.
- [x] **UI Polish & Animation**:
  - [x] **Animated Buttons**: Implemented smooth color transitions on hover using linear interpolation.
  - [x] **Animated Icons**: Applied the same animation principles to icons using texture tinting for a consistent and responsive feel.

## IV. Advanced Topics & Future Goals

- [ ] **Complex Modules**:
  - [ ] Develop more interactive states like a "Notes" app (handling text input).
  - [ ] Implement a "Timer/Stopwatch" module.
- [ ] **Analysis & Debugging Tools**:
  - [ ] Memory leak detection using `Valgrind`.
  - [ ] Static code analysis with `clang-tidy` (revisit).
- [ ] ... (More to be added as we progress)
