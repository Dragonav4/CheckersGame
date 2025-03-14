# Checkers Game ♟️
## Overview
This project is a Checkers game that provides an intuitive **Java Swing GUI** for the graphical interface, 
while the core gameplay mechanics are implemented in **C++**. 
The interaction between Java and **C++** is facilitated using **Java Native Interface** (**JNI**). The game supports two players, allowing them to engage in a classic checkers match on the same device, following standard rules.
---
## **Features** 🚀

### **🔹 Interactive GUI**
- 🖱️ Click-based and keyboard controls for moving pieces.
- 🔍 Visual indicators for valid moves.

### **🔹 Standard Checkers Rules**
- ✅ Enforces legal piece movements.
- ♟️ Supports mandatory captures.
- 👑 Promotes pieces to kings when reaching the opponent’s side.

### **🔹 Highlights**
- 🔄 Displays the current player's turn.
- ✨ Highlights valid moves for the selected piece.

### **🔹 Performance**
- ⚡ Core game logic optimized in **C++** for better performance.

### **🔹 Error Handling**
- 🚫 Prevents illegal moves and provides on-screen feedback.

### **🔹 Unit Testing**
- ✅ Comprehensive tests using **JUnit** to ensure correctness of Java components.  

---
## Gameplay
![Gameplay GIF](UTP_s31722_Eng_Java/src/checkers.gif)

### **Programming Language**
- Java (GUI and application logic)
- C++ (gameplay rules and logic)

### **GUI Framework**
- Java Swing

### **Integration**
- Java Native Interface (JNI)

### **Testing**
- JUnit

### **Development Environment**
- IntelliJ IDEA
- IntelliJ CLion

---

## **How to Play**
1. Launch the application.
2. Player 1 starts the game.
3. Choose a piece and select a valid tile for its destination. Invalid moves will be blocked.
4. The game ends when a player has no valid moves left or all their pieces are captured.

---
## **Project Structure**

- `Main.java` - Entry point of the game
- `src/Main/java/Main/` - General classes for the Java side
- `src/Board/` - Providing main logic of board and boardState
- `src/GameWindow/` - Providing instructions for gameWindow
- `src/JUnit5_Tests/` - Directory with unit tests for the game
- `UTP_s31722_ENG_Cpp/` - Directory containing all C++ code
- `README.md` - Project documentation
- `LICENSE` - Project license  
---
## License
This project is licensed under the MIT License

---
## Acknowledgments
Inspired by the ukrainian type checkers game