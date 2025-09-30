# CSOPESY-MCO1  

## Authors  
### Group 8  
- Diane Panganiban  
- Gian Carlos  
- Kenzo De Vera  
- Yesha Joes  

## Description  
This repository contains the source code for a **Marquee Console Application**, developed for CSOPESY MCO1.  
The application simulates a console-based marquee display with interactive controls and multithreading support.  

You can access available commands and usage instructions inside the program by typing:  
`help`  

**Entry File:**  
`src/main.cpp`  

## Features  
- Console-based marquee text display.  
- Adjustable speed using commands.  
- Start/stop marquee functionality.  
- Command-based interface (`help` for full list of instructions).  
- Multithreaded implementation using `<thread>`, `<mutex>`, and `<atomic>`.  

## Instructions  

### Windows  
1. Make sure you have **MinGW** or any compiler that supports C++11 (or higher) installed.  
2. From the project **root**, you can either:  
   - Run the provided batch file:  
     ```
     run.bat
     ```  
   - Or manually compile and run in your cmd using:  
     ```
     g++ src/main.cpp -o program -lpthread && program.exe
     ```  

### Linux / macOS  
> Not supported due to Windows-specific libraries (e.g. `<conio.h>`).  

## Notes  
- This project is built specifically for Windows.  
