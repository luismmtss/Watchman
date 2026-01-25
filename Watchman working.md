# Watchman – Technical Documentation

## Overview
Watchman is a **system-level CLI utility** written in C++ that continuously monitors a directory for filesystem changes. It detects when files or folders are **created, modified, or deleted**, records these events in a log file, and displays them in real time on the console.

The project focuses on **operating-system interaction**, not UI or business logic. It is designed to demonstrate how user-space programs can observe and react to OS-level filesystem events.

---

## System Interaction (How Watchman Talks to the OS)

Watchman operates in **user space** and interacts with the operating system through native filesystem APIs.

### Key Characteristics
- Uses **OS-provided directory monitoring mechanisms** (polling or event-based, depending on implementation)
- Continuously queries the filesystem state
- Compares snapshots to detect changes
- Reacts immediately when the OS reports a change

This makes Watchman a **system utility**, similar in nature to tools like `tail -f` or filesystem watchers.

---

## How Folder Watching Works

1. **Initial Scan**
   - Watchman scans the target directory at startup
   - Stores metadata for each file (name, last modified time, size, etc.)

2. **Monitoring Loop**
   - The program enters a continuous loop
   - At regular intervals, the directory is re-checked

3. **Change Detection**
   - New file → **Created event**
   - Missing file → **Deleted event**
   - Modified timestamp/size → **Updated event**

4. **Event Trigger**
   - Once a change is detected, Watchman immediately:
     - Writes the event to a log file
     - Prints the event to the console

The watcher must remain in the **root directory** to maintain correct relative paths and logging behavior.

---

## Logging System

### Where Logs Are Stored
- All logs are stored in a file named:

```
watchman.log
```

- The log file is created automatically if it does not exist
- Logs are appended, not overwritten

### Log Format
Each entry contains:
- Timestamp
- Event type (CREATED / MODIFIED / DELETED)
- File or folder name

Example:
```
[2026-01-25 18:42:11] CREATED  → notes.txt
[2026-01-25 18:43:02] MODIFIED → notes.txt
[2026-01-25 18:45:10] DELETED  → old_data.csv
```

---

## How Logs Are Displayed

Watchman provides **real-time console output** while running:

- Every detected change is printed instantly
- Console output mirrors what is written to `watchman.log`
- This allows Watchman to be used both as:
  - A background monitoring tool
  - A real-time activity viewer

The program does not require restarting to see new events.

---

## Execution Model

- Watchman is a **long-running process**
- It keeps executing until manually stopped
- Designed for terminal usage
- No GUI dependencies

---

## Directory Structure Requirement

For Watchman to function correctly, the executable must remain in the root directory being monitored:

```
Watchman/
├── watchman.exe
├── watchman.log
├── monitored_files/
```

This ensures:
- Correct path resolution
- Consistent logging
- Predictable behavior across systems

---

## Why This Is a System Application

Watchman qualifies as a system-level application because it:
- Interacts directly with OS filesystem services
- Monitors system resources
- Runs continuously
- Operates without user-facing UI layers

It demonstrates core **system programming concepts** using C++.

---

## Intended Use Cases

- File activity monitoring
- Debugging file changes
- Learning OS-level programming
- Understanding filesystem behavior

---

## Limitations

- Runs in user space (not kernel-level)
- Designed for learning and demonstration purposes
- No advanced filtering or configuration (by design)

---

## Summary

Watchman is a lightweight, focused system utility that showcases how a C++ program can observe and react to filesystem changes using operating system facilities. It emphasizes clarity, simplicity, and direct OS interaction over complexity.

