# Student Management System (C++)

A console-based application designed to manage university records. This system features a role-based login mechanism (Admin, Teacher, Student) and uses file handling to ensure data persistence between sessions.

## 🚀 Features

### 🔒 Admin Module
* **Manage Teachers:** Add or delete teacher records securely.
* **System Maintenance:** full control over the primary user data.

### 👨‍🏫 Teacher Module
* **Student Management:** Add or delete students from the class list.
* **Grading System:** Assign marks for Quizzes, Assignments, Midterms, and Finals.
* **Automated Calculations:** Automatically calculates CGPA based on input marks.
* **Reports:** View lists of passed/failed students and sort students by academic performance.

### 👨‍🎓 Student Module
* **Gradebook:** View detailed marks for all subjects.
* **Performance:** Check current CGPA status.

## 🛠️ Technical Implementation
This project demonstrates proficiency in core C++ concepts:
* **File Handling (`fstream`):** Uses `.txt` files to store and retrieve student/teacher data so records aren't lost when the program closes.
* **Multi-dimensional Arrays:** Manages complex data structures for storing marks across different subjects and evaluation types.
* **Sorting Algorithms:** Implements custom sorting logic to rank students by CGPA.
* **Authentication:** specialized login logic for three different user roles.
* **Input Validation:** Ensures marks are entered within valid ranges (e.g., 0-100).

## 💻 How to Run
1.  Clone the repository or download the source code.
2.  Compile the program using a C++ compiler (like GCC or Visual Studio).
    ```bash
    g++ main.cpp -o student_system
    ```
3.  Run the executable.
    ```bash
    ./student_system
    ```
4.  **Default Admin Credentials:**
    * Username: `admin`
    * Password: `admin123`

## 📂 File Structure
* `main.cpp`: The source code containing all logic.
* `teachers.txt`: Database file for teacher credentials.
* `students.txt`: Database file for student records and marks.
## 👨‍💻 About the Author
**Ahmad Nasir**
*Computer Science Student*

Hi there! 👋 I am a CS student passionate about learning low-level programming and system design.

I built this **Student Management System** as a semester project to challenge myself with C++ logic and file handling. While it is a console-based application, it represents a significant milestone in my coding journey.

## 🤝 Connect & Feedback
Since I am just starting out, I would love your feedback!
* If you see ways to optimize my code (especially the sorting algorithms or memory management), please open an **Issue** or let me know.
* I am constantly learning, so any advice from experienced developers is highly approximated.

🌟 **If you find this code helpful for your own studies, please give the repo a star!**
