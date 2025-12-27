#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

const int MAX_TEACHERS = 10;
const int MAX_STUDENTS = 30;
const int MAX_SUBJECTS = 5;
const int MAX_EVALUATIONS = 7;
int student_count = 0;
int teacher_count = 0;

// Arrays for student and teacher data
int student_ids[MAX_STUDENTS];
string student_names[MAX_STUDENTS];
string student_classes[MAX_STUDENTS];
float student_marks[MAX_STUDENTS][MAX_SUBJECTS][MAX_EVALUATIONS];
float student_cgpa[MAX_STUDENTS];

int teacher_ids[MAX_TEACHERS];
int subject_assignment_index;
int student_assignment_index;
string teacher_names[MAX_TEACHERS];
string teacher_subjects[MAX_TEACHERS];
string teacher_passwords[MAX_TEACHERS]; 
int students_passwords[MAX_STUDENTS];

// Function Prototypes
void admin_menu();
void main_menu();
void teacher_menu();
void student_menu();
bool login_admin();
bool login_teacher();
bool login_student();
void add_teacher();
void delete_teacher();
void add_student();
void delete_student();
void assign_marks();
void calculate_cgpa();
void list_passed_students();
void list_failed_students();
void list_students_sorted(bool ascending);
void view_grades();
void view_cgpa();
void load_teachers();
void load_students();
void save_teachers();
void save_students();

// Function Definitions

void load_teachers() {
    ifstream in_file("teachers.txt");
    if (!in_file) {
        cout << "Unable to open teacher file.\n";
        return;
    }
    string line;
    while (getline(in_file, line)) {
        stringstream ss(line);
        int id;
        string name, subject, password;
        ss >> id >> ws;
        getline(ss, name, ',');
        getline(ss, subject, ',');
        getline(ss, password);

        teacher_ids[teacher_count] = id;
        teacher_names[teacher_count] = name;
        teacher_subjects[teacher_count] = subject;
        teacher_passwords[teacher_count] = password;
        teacher_count++;
    }
    in_file.close();
}

void save_teachers() {
    ofstream out_file("teachers.txt", ios::trunc);
    if (!out_file) {
        cout << "Unable to open teacher file for writing.\n";
        return;
    }
    for (int i = 0; i < teacher_count; i++) {
        out_file << teacher_ids[i] << " " << teacher_names[i] << "," << teacher_subjects[i] << "," << teacher_passwords[i] << endl;
    }
    out_file.close();
}

void load_students() {
    ifstream in_file("students.txt");
    if (!in_file) {
        cout << "Unable to open student file.\n";
        return;
    }
    string line;
    while (getline(in_file, line)) {
        stringstream ss(line);
        int id;
        string name, class_name;

        ss >> id >> ws;
        getline(ss, name, ',');
        getline(ss, class_name, ',');

        student_ids[student_count] = id;
        student_names[student_count] = name;
        student_classes[student_count] = class_name;

        for (int i = 0; i < MAX_SUBJECTS; i++) {
            for (int j = 0; j < MAX_EVALUATIONS; j++) {
                ss >> student_marks[student_count][i][j];
            }
        }

        student_count++;
    }
    in_file.close();
}

void save_students() {
    ofstream out_file("students.txt", ios::trunc);
    if (!out_file) {
        cout << "Unable to open student file for writing.\n";
        return;
    }
    for (int i = 0; i < student_count; i++) {
        out_file << student_ids[i] << " " << student_names[i] << "," << student_classes[i] << ",";
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            if (j != MAX_SUBJECTS - 1) out_file << " ";
            for (int k = 0; k < MAX_EVALUATIONS; k++) {
                out_file << student_marks[i][j][k] << " ";
            }
        }
        out_file << endl;
    }
    out_file.close();
}

bool login_admin() {
    string username, password;
    cout << "Enter Admin Username: ";
    cin >> username;
    cin.ignore();
    cout << "Enter Admin Password: ";
    getline(cin, password);

    if (username == "admin" && password == "admin123") {
        return true;
    }
    cout << "Invalid credentials. Exiting.\n";
    return false;
}

bool login_teacher() {
    string username, password;
    cout << "Enter Teacher Username: ";
    cin >> username;
    cin.ignore();
    cout << "Enter Teacher Password: ";
    getline(cin, password);

    for (int i = 0; i < teacher_count; i++) {
        if (teacher_names[i] == username && teacher_passwords[i] == password) {
            subject_assignment_index = i;
            return true;
        }
    }
    cout << "Invalid credentials. Exiting.\n";
    return false;
}

bool login_student() {
    string username;
    int pass;
    cout << "Enter Student Name: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> pass;

    for (int i = 0; i < student_count; i++) {
        if (student_names[i] == username && students_passwords[i]==pass) { 
            student_assignment_index = i;
            return true;
        }
    }
    cout << "Student not found. Exiting.\n";
    return false;
}

void admin_menu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Teacher\n";
        cout << "2. Delete Teacher\n";
        cout << "3. Main Page\n";
        cout << "4. Logout\n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
        case 1: add_teacher(); break;
        case 2: delete_teacher(); break;
        case 3: main_menu(); break;
        case 4: cout << "logging out...."; break;
        default: cout << "Invalid choice. Try again.\n"; break;
        }
    } while (choice != 3);
}

void teacher_menu() {
    int choice;
    do {
        cout << "\n--- Teacher Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Assign Marks\n";
        cout << "4. Calculate CGPA\n";
        cout << "5. List Passed Students\n";
        cout << "6. List Failed Students\n";
        cout << "7. List Students Sorted\n";
        cout << "8. Main Menu \n";
        cout << "9. Logout\n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
        case 1: add_student(); break;
        case 2: delete_student(); break;
        case 3: assign_marks(); break;
        case 4: calculate_cgpa(); break;
        case 5: list_passed_students(); break;
        case 6: list_failed_students(); break;
        case 7: {
            bool ascending;
            cout << "Enter 1 for ascending order, 0 for descending: ";
            cin >> ascending;
            list_students_sorted(ascending);
            break;
        }
        case 8: main_menu(); break;
        case 9: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice. Try again.\n"; break;
        }
    } while (choice != 8);
}

void student_menu() {
    int choice;
    do {
        cout << "\n--- Student Menu ---\n";
        cout << "1. View Grades\n";
        cout << "2. View CGPA\n";
        cout << "3. Main Menu \n";
        cout << "4. Logout\n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
        case 1: view_grades(); break;
        case 2: view_cgpa(); break;
        case 3: main_menu(); break;
        case 4: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice. Try again.\n"; break;
        }
    } while (choice != 3);
}

void add_teacher() {
    if (teacher_count < MAX_TEACHERS) {
        int id;
        string name, subject, password;
        cout << "Enter Teacher ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Teacher Name: ";
        getline(cin, name);
        cout << "Enter Teacher Subject: ";
        getline(cin, subject);
        cout << "Enter Teacher Password: ";
        getline(cin, password);

        teacher_ids[teacher_count] = id;
        teacher_names[teacher_count] = name;
        teacher_subjects[teacher_count] = subject;
        teacher_passwords[teacher_count] = password;
        teacher_count++;
        save_teachers();
        cout << "Teacher added successfully.\n";
    }
    else {
        cout << "Maximum number of teachers reached.\n";
    }
}

void delete_teacher() {
    int id;
    cout << "Enter Teacher ID to delete: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < teacher_count; i++) {
        if (teacher_ids[i] == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < teacher_count - 1; i++) {
            teacher_ids[i] = teacher_ids[i + 1];
            teacher_names[i] = teacher_names[i + 1];
            teacher_subjects[i] = teacher_subjects[i + 1];
            teacher_passwords[i] = teacher_passwords[i + 1];
        }
        teacher_count--;
        save_teachers();
        cout << "Teacher deleted successfully.\n";
    }
    else {
        cout << "Teacher not found.\n";
    }
}

void add_student() {
    if (student_count < MAX_STUDENTS) {
        int id,pass; 
        string name, class_name;
        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Student Class: ";
        getline(cin, class_name);
        cout << "Enter Password: ";
        cin >> pass; 

        student_ids[student_count] = id;
        student_names[student_count] = name;
        student_classes[student_count] = class_name;
        students_passwords[student_count] = pass;   

        for (int i = 0; i < MAX_SUBJECTS; i++) {
            for (int j = 0; j < MAX_EVALUATIONS; j++) {
                student_marks[student_count][i][j] = 0.0;
            }
        }

        student_count++;
        save_students();
        cout << "Student added successfully.\n";
    }
    else {
        cout << "Maximum number of students reached.\n";
    }
}

void delete_student() {
    int id;
    cout << "Enter Student ID to delete: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < student_count; i++) {
        if (student_ids[i] == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < student_count - 1; i++) {
            student_ids[i] = student_ids[i + 1];
            student_names[i] = student_names[i + 1];
            student_classes[i] = student_classes[i + 1];

            for (int j = 0; j < MAX_SUBJECTS; j++) {
                for (int k = 0; k < MAX_EVALUATIONS; k++) {
                    student_marks[i][j][k] = student_marks[i + 1][j][k];
                }
            }
        }
        student_count--;
        save_students();
        cout << "Student deleted successfully.\n";
    }
    else {
        cout << "Student not found.\n";
    }
}

void assign_marks() {
    int id;
    cout << "Enter Student ID to assign marks: ";
    cin >> id;

    // Find student index
    int student_index = -1;
    for (int i = 0; i < student_count; i++) {
        if (student_ids[i] == id) {
            student_index = i;
            break;
        }
    }

    if (student_index == -1) {
        cout << "Student not found.\n";
        return;
    }

    // Use teacher's assigned subject index
    int subject_index = subject_assignment_index;

    if (subject_index < 0 || subject_index >= MAX_SUBJECTS) {
        cout << "Error: Invalid subject for this teacher.\n";
        return;
    }

    // Assign marks 
    cout << "Assigning marks for  (Student ID: " << id << "\n";

    // Assign quizzes
    for (int i = 0; i < 2; i++) {
        cout << "Enter marks for Quiz " << i + 1 << " (Out of 10): ";
        cin >> student_marks[student_index][subject_index][i];
        if (student_marks[student_index][subject_index][i] < 0 || student_marks[student_index][subject_index][i] > 10) {
            cout << "Invalid marks! Please enter marks between 0 and 10.\n";
            i--; // Repeat input for invalid entry
        }
    }

    // Assign assignments
    for (int i = 2; i < 4; i++) {
        cout << "Enter marks for Assignment " << i - 1 << " (Out of 10): ";
        cin >> student_marks[student_index][subject_index][i];
        if (student_marks[student_index][subject_index][i] < 0 || student_marks[student_index][subject_index][i] > 10) {
            cout << "Invalid marks! Please enter marks between 0 and 10.\n";
            i--; // Repeat input for invalid entry
        }
    }

    // Assign midterms
    for (int i = 4; i < 6; i++) {
        cout << "Enter marks for Midterm " << i - 3 << " (Out of 50): ";
        cin >> student_marks[student_index][subject_index][i];
        if (student_marks[student_index][subject_index][i] < 0 || student_marks[student_index][subject_index][i] > 50) {
            cout << "Invalid marks! Please enter marks between 0 and 50.\n";
            i--; // Repeat input for invalid entry
        }
    }

    // Assign final exam
    cout << "Enter marks for Final Exam (Out of 100): ";
    cin >> student_marks[student_index][subject_index][6];
    if (student_marks[student_index][subject_index][6] < 0 || student_marks[student_index][subject_index][6] > 100) {
        cout << "Invalid marks! Please enter marks between 0 and 100.\n";
        cin >> student_marks[student_index][subject_index][6]; // Repeat input for invalid entry
    }

    // Save changes
    save_students();
    calculate_cgpa();
    cout << "Marks assigned successfully.\n";
}



void calculate_cgpa() {
    for (int i = 0; i < student_count; i++) {
        float total_marks = 0.0;
        int count = 0;

        for (int j = 0; j < MAX_SUBJECTS; j++) {
            for (int k = 0; k < MAX_EVALUATIONS; k++) {
                total_marks += student_marks[i][j][k];
                count++;
            }
        }

        student_cgpa[i] = total_marks / count;
    }
    save_students();
    cout << "CGPA calculated for all students.\n";
}

void list_passed_students() {
    cout << "Passed Students:\n";
    for (int i = 0; i < student_count; i++) {
        if (student_cgpa[i] >= 2.0) {  // Assuming CGPA >= 2.0 is passing
            cout << "ID: " << student_ids[i] << ", Name: " << student_names[i] << ", CGPA: " << student_cgpa[i] << "\n";
        }
    }
}

void list_failed_students() {
    cout << "Failed Students:\n";
    for (int i = 0; i < student_count; i++) {
        if (student_cgpa[i] < 2.0) {
            cout << "ID: " << student_ids[i] << ", Name: " << student_names[i] << ", CGPA: " << student_cgpa[i] << "\n";
        }
    }
}

void list_students_sorted(bool ascending) {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - i - 1; j++) {
            if ((ascending && student_cgpa[j] > student_cgpa[j + 1]) || (!ascending && student_cgpa[j] < student_cgpa[j + 1])) {
                swap(student_ids[j], student_ids[j + 1]);
                swap(student_names[j], student_names[j + 1]);
                swap(student_classes[j], student_classes[j + 1]);
                swap(student_cgpa[j], student_cgpa[j + 1]);
            }
        }
    }
    cout << "Students sorted by CGPA:\n";
    for (int i = 0; i < student_count; i++) {
        cout << "ID: " << student_ids[i] << ", Name: " << student_names[i] << ", CGPA: " << student_cgpa[i] << "\n";
    }
}

void view_grades() {
    int index = student_assignment_index;
    cout << "Grades for " << student_names[index] << ":\n";
    cout << "\t  Q1 Q2 A1 A2  M1  M2   F\n";
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        cout << "Subject " << i + 1 << ": ";
        for (int j = 0; j < MAX_EVALUATIONS; j++) {
            cout << student_marks[index][i][j] << "  ";
        }
        cout << "\n";
    }
}

void view_cgpa() {
    int index = student_assignment_index;
    calculate_cgpa();
    cout << "CGPA for " << student_names[index] << ": " << student_cgpa[index] << "\n";
}
void main_menu()
{
    load_teachers();
    load_students();

    int role;
    cout << "------Select role------\n\n1. Admin \n2. Teacher  \n3. Student\n\nSelect Role : ";
    cin >> role;

    switch (role) {
    case 1:
        if (login_admin()) {
            admin_menu();
        }
        break;
    case 2:
        if (login_teacher()) {
            teacher_menu();
        }
        break;
    case 3:
        if (login_student()) {
            student_menu();
        }
        break;
    default:
        cout << "Invalid role selected. Exiting.\n";
        break;
    }

    save_teachers();
    save_students();
}

int main() {
    load_teachers();
    load_students();

    int role;
    cout << "------Select role------\n\n1. Admin \n2. Teacher  \n3. Student\n\nSelect Role : ";
    cin >> role;

    switch (role) {
    case 1:
        if (login_admin()) {
            admin_menu();
        }
        break;
    case 2:
        if (login_teacher()) {
            teacher_menu();
        }
        break;
    case 3:
        if (login_student()) {
            student_menu();
        }
        break;
    default:
        cout << "Invalid role selected. Exiting.\n";
        break;
    }

    save_teachers();
    save_students();
    return 0;
}
