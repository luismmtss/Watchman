# 🕵️ Watchman – Directory Change Monitor & Viewer

Watchman is a simple command-line utility that helps you **track and visualize file changes** inside a directory.

It is designed to be easy to use, transparent, and practical — with no background services or GUI overhead.

---

## 📦 Project Overview

Watchman works in **two parts**:

- **Watcher**  
  Monitors a directory and records file changes.

- **Watchman**  
  Reads those records and displays them in a clean, readable format.

---

## ✅ What Can You Use It For?

- Monitoring project folders  
- Tracking file activity  
- Reviewing *what changed* and *when*  
- Learning how file-system monitoring works in practice  

---

## ⚙️ How Watchman Works (High Level)

1. You run the **watcher** and choose a directory to monitor  
2. File changes (create, modify, delete, rename) are saved to a log file  
3. You run **`watchman.exe`** to view those changes  
4. Events are displayed with timestamps and optional colored output  

---

## 📁 Final Directory Structure (IMPORTANT)

For Watchman to work correctly, the directory structure **must look exactly like this**:

```
├── config/
│   └── watchman.ini
│
├── watcher/
│   └── (watcher source + build files)
│
├── watchman/
│   └── (watchman source files)
│
├── README.md
├── watchman.exe
```

### ⚠️ Important Note

`watchman.exe` **must stay in the projectely root directory**.

If you move it, configuration loading and log reading **will break**.

---

## 🛠 Installation & Setup

### Prerequisites
- Windows 10 / Windows 11  
- g++ compiler (MinGW or MSYS2 recommended)

---

## 🔨 Building Watchman

From the project root directory:

```
g++ watchman/src/main.cpp watchman/src/config.cpp watchman/src/console.cpp -Iwatchman/include -o watchman.exe
```

### Optional build script (`build_watchman.bat`)
```
@echo off
g++ watchman/src/main.cpp watchman/src/config.cpp watchman/src/console.cpp -Iwatchman/include -o watchman.exe
pause
```

---

## ▶️ Running Watchman

```
watchman.exe
```

### Example Output
```
[2026-01-25 18:12:40] [CREATED]  notes.txt
[2026-01-25 18:13:01] [MODIFIED] notes.txt
[2026-01-25 18:13:45] [DELETED]  notes.txt
```

---

## 📄 License

Free to use for learning and experimentation.
