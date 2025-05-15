# 🎸 AllGuitarScales

**AllGuitarScales** is a simple desktop app that shows guitar scales on a virtual fretboard. You can pick a note, scale, and tuning, and see how the scale lays out across all 24 frets.

![image](https://github.com/user-attachments/assets/548dc189-4bd0-4787-a595-2e72ff06138f)


---

## 📦 Download & Run

A prebuilt Windows `.exe` file is available in the `release/` folder of this repository. To run it:

1. Download the latest `AllGuitarScales.exe` from the [`release`](./GuitarScales/build/Desktop_Qt_6_10_0_MinGW_64_bit-Release) folder.
2. Make sure all `.dll` files are included in the same folder (use [windeployqt](https://doc.qt.io/qt-6/windows-deployment.html) if you're building yourself).
3. Double-click the `.exe` to launch the app — no install needed!

---

## 🔧 Requirements (for building)

If you want to build it yourself:

- Qt 6 (tested with Qt 6.10)
- CMake 3.16 or newer
- C++17 compiler (like MinGW)

### 🔨 Build Instructions

1. Clone this repository.
2. Open the project in **Qt Creator** (recommended), or use:

   ```bash
   cmake -B build -S .
   cmake --build build
