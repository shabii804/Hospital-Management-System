#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <map>
using namespace std;

/* ================= SAFE INPUT ================= */
// Read line from user safely (prints prompt if provided)
string readLine(const string& p = "") {
    if (!p.empty()) cout << p;
    string s;
    getline(cin, s);
    return s;
}

// Read integer safely
int readInt(const string& p = "") {
    while (true) {
        try {
            string s = readLine(p);
            return stoi(s);
        } catch (...) {
            cout << "Enter valid integer!\n";
        }
    }
}

// Read double safely
double readDouble(const string& p = "") {
    while (true) {
        try {
            string s = readLine(p);
            return stod(s);
        } catch (...) {
            cout << "Enter valid number!\n";
        }
    }
}

/* ================= LOGIN SYSTEM ================= */
// Role enumeration for different types of users
enum class Role { ADMIN, DOCTOR, PATIENT, EXIT };

// Login system function
Role loginSystem() {
    int attempts = 0;
    // Allow maximum 3 attempts
    while (attempts < 3) {
        cout << "\n===== LOGIN =====\n";
        cout << "1. Admin\n2. Doctor\n3. Patient\n0. Exit\nChoose: ";
        int ch; 
        if (!(cin >> ch)) { // handle non-int input
            cin.clear();
            string dummy; getline(cin, dummy);
            cout << "Invalid choice\n";
            attempts++;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (ch == 0) return Role::EXIT; // Exit system

        string pass;
        cout << "Enter Password: ";
        getline(cin, pass);

        // Check password for each role
        if (ch == 1 && pass == "admin123") return Role::ADMIN;
        if (ch == 2 && pass == "doctor123") return Role::DOCTOR;
        if (ch == 3 && pass == "patient123") return Role::PATIENT;

        attempts++;
        cout << "Wrong Password! Attempts left: " << (3 - attempts) << "\n";
    }

    cout << "System Locked!\n"; // Too many failed attempts
    return Role::EXIT;
}

/* ================= MEDICAL RECORD ================= */
// Single MedicalRecord definition (date & note)
struct MedicalRecord {
    string date;
    string note;
    MedicalRecord* next;
    MedicalRecord(const string& d = "", const string& n = "")
        : date(d), note(n), next(nullptr) {}
};

/* ================= PATIENT MODEL ================= */
struct Patient {
    int id;
    int age;
    string name;
    string gender;
    string disease;
    MedicalRecord* head; // Pointer to linked list of medical history
    double bill;

    // Constructor
    Patient(int i = 0, const string& n = "", int a = 0, const string& g = "",
            const string& d = "", double b = 0.0)
        : id(i), age(a), name(n), gender(g), disease(d), head(nullptr), bill(b) {}

    // Add medical history (insert at head)
    void addHistory(const string& date, const string& note) {
        MedicalRecord* node = new MedicalRecord(date, note);
        node->next = head;
        head = node;
    }

    // Display medical history
    void showHistory() {
        if (!head) { cout << "No Medical History\n"; return; }
        cout << "\n--- Medical History ---\n";
        for (MedicalRecord* p = head; p; p = p->next)
            cout << p->date << " -> " << p->note << '\n';
    }

    // Update patient information
    void updateInfo() {
        cout << "\n--- Update Patient Info ---\n";
        name = readLine("New Name: ");
        age = readInt("New Age: ");
        gender = readLine("New Gender: ");
        disease = readLine("New Disease: ");
        cout << "Patient Updated Successfully!\n";
    }

    // Pay outstanding bill
    void payBill() {
        if (bill <= 0) { cout << "No outstanding bill.\n"; return; }
        double amount = readDouble("Enter amount to pay: $");
        if (amount >= bill) {
            cout << "Full payment received. Bill cleared.\n";
            bill = 0;
        } else {
            bill -= amount;
            cout << "Payment successful! Remaining bill: $" << bill << "\n";
        }
    }

    // View current bill
    void viewBill() {
        cout << "------------------------\n";
        cout << "Patient: " << name << " | ID: " << id << '\n';
        cout << "Current Bill: $" << bill << '\n';
        cout << "------------------------\n";
    }
};

/* ================= DOCTOR MODEL ================= */
struct Doctor {
    int id;
    string name;
    string specialization;

    Doctor(int i = 0, const string& n = "", const string& s = "") : id(i), name(n), specialization(s) {}
};

/* ================= AVL TREE ================= */
// AVL tree node for storing patients
struct AVLNode {
    Patient data;
    AVLNode* left;
    AVLNode* right;
    int h; // height of node
    AVLNode(const Patient& p) : data(p), left(nullptr), right(nullptr), h(1) {}
};

// Get height of node
int height(AVLNode* n) { return n ? n->h : 0; }

// Right rotation
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T = x->right;
    x->right = y;
    y->left = T;
    y->h = 1 + max(height(y->left), height(y->right));
    x->h = 1 + max(height(x->left), height(x->right));
    return x;
}

// Left rotation
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T = y->left;
    y->left = x;
    x->right = T;
    x->h = 1 + max(height(x->left), height(x->right));
    y->h = 1 + max(height(y->left), height(y->right));
    return y;
}

// Balance factor
int balance(AVLNode* n) { return n ? height(n->left) - height(n->right) : 0; }

// Insert patient in AVL tree
AVLNode* insertAVL(AVLNode* node, const Patient& p) {
    if (!node) return new AVLNode(p);
    if (p.id < node->data.id) node->left = insertAVL(node->left, p);
    else if (p.id > node->data.id) node->right = insertAVL(node->right, p);
    else return node; // duplicate ID
    node->h = 1 + max(height(node->left), height(node->right));
    int b = balance(node);

    // Balance the tree
    if (b > 1 && p.id < node->left->data.id) return rightRotate(node);
    if (b < -1 && p.id > node->right->data.id) return leftRotate(node);
    if (b > 1 && p.id > node->left->data.id) { node->left = leftRotate(node->left); return rightRotate(node); }
    if (b < -1 && p.id < node->right->data.id) { node->right = rightRotate(node->right); return leftRotate(node); }
    return node;
}

// Search patient by ID
Patient* searchAVL(AVLNode* r, int id) {
    if (!r) return nullptr;
    if (id == r->data.id) return &r->data;
    if (id < r->data.id) return searchAVL(r->left, id);
    return searchAVL(r->right, id);
}

// Display all patients in-order
void displayAVL(AVLNode* r) {
    if (!r) return;
    displayAVL(r->left);
    cout << "ID:" << r->data.id << " | Name:" << r->data.name << " | Age:" << r->data.age
         << " | Gender:" << r->data.gender << " | Disease:" << r->data.disease
         << " | Bill:$" << r->data.bill << '\n';
    displayAVL(r->right);
}

/* ================= APPOINTMENT QUEUE ================= */
struct Appointment { int pid; string time; };
queue<Appointment> apptQ; // FIFO queue for appointments
map<int, vector<string>> doctorSchedule; // Doctor schedules

/* ================= EMERGENCY QUEUE ================= */
priority_queue<pair<int, int>> emgPQ; // Max-heap priority queue: (severity, patientID)

/* ================= DOCTOR ASSIGNMENT MAP ================= */
unordered_map<int, vector<int>> docMap; // Doctor -> Patients
unordered_map<int, Doctor> doctors;     // Doctor ID -> Doctor info

/* ================= MAIN FUNCTION ================= */
int main() {
    AVLNode* root = nullptr;
    int nextPatientId = 1001;
    int nextDoctorId = 201;

    while (true) {
        // User login
        Role role = loginSystem();
        if (role == Role::EXIT) { cout << "System Closed\n"; break; }

        Patient* currentPatient = nullptr;

        // Patient registration/login
        if (role == Role::PATIENT) {
            cout << "Do you want to (1) Login or (2) Register as new patient? ";
            int choice = readInt();
            if (choice == 2) {
                double bill = readDouble("Enter initial bill amount: $");
                Patient p(nextPatientId++, readLine("Name: "), readInt("Age: "), readLine("Gender: "), readLine("Disease: "), bill);
                root = insertAVL(root, p);
                cout << "Registered successfully! Your Patient ID is: " << p.id << endl;
                currentPatient = searchAVL(root, p.id);
            } else {
                int patientID = readInt("Enter your Patient ID: ");
                currentPatient = searchAVL(root, patientID);
                if (!currentPatient) { cout << "Invalid Patient ID!\n"; continue; }
            }
        }

        // Role-based menu loop
        while (true) {
            cout << "\n==============================\n";

            // Display menus
            if (role == Role::ADMIN) {
                cout << "--- ADMIN MENU ---\n";
                cout << "1. Add Patient\n2. View Patient\n3. Add History\n4. Display All Patients\n";
                cout << "5. Schedule Appointment\n6. View Appointments\n7. Update Patient\n";
                cout << "8. Add Emergency\n9. View Emergency\n11. Assign Doctor\n12. View Doctor Assignments\n";
                cout << "13. Add Doctor\n14. View Doctors & Timetable\n0. Logout\n";
            }
            else if (role == Role::DOCTOR) {
                cout << "--- DOCTOR MENU ---\n";
                cout << "2. View Patient\n6. View Appointments\n9. View Emergency\n0. Logout\n";
            }
            else if (role == Role::PATIENT) {
                cout << "--- PATIENT MENU ---\n";
                cout << "1. View Self Info\n2. View Medical History\n3. Add Medical History\n";
                cout << "4. View Appointments\n5. Pay Bill\n6. See Bill\n0. Logout\n";
            }

            int ch = readInt("Choose: ");
            if (ch == 0) { cout << "Logging out...\n"; break; }

            // ===== ADMIN ACTIONS =====
            if (role == Role::ADMIN) {
                if (ch == 1) { // Add patient
                    double bill = readDouble("Enter initial bill amount: $");
                    Patient p(nextPatientId++, readLine("Name: "), readInt("Age: "),
                              readLine("Gender: "), readLine("Disease: "), bill);
                    root = insertAVL(root, p);
                    cout << "Patient Added! Patient ID: " << p.id << "\n";
                }
                if (ch == 2) { // View patient
                    int pid = readInt("Patient ID: ");
                    Patient* p = searchAVL(root, pid);
                    if (!p) cout << "Patient not found!\n";
                    else {
                        cout << "ID:" << p->id << " | Name:" << p->name << " | Age:" << p->age
                            << " | Gender:" << p->gender << " | Disease:" << p->disease
                            << " | Bill:$" << p->bill << endl;
                        p->showHistory();
                    }
                }
                // Add medical history
                if (ch == 3) {
                    int pid = readInt("Patient ID: ");
                    Patient* p = searchAVL(root, pid);
                    if (p) {
                        string date = readLine("Date: ");
                        string note = readLine("Note: ");
                        p->addHistory(date, note);
                        cout << "History added.\n";
                    } else cout << "Patient not found!\n";
                }
                // Display all patients
                if (ch == 4) displayAVL(root);
                // Schedule appointment
                if (ch == 5) {
                    int pid = readInt("Patient ID: ");
                    string t = readLine("Enter Appointment Time: ");
                    apptQ.push({pid, t});
                    for (auto& d : docMap) {
                        for (int p : d.second) {
                            if (p == pid) doctorSchedule[d.first].push_back(t);
                        }
                    }
                    cout << "Appointment Added\n";
                }
                // View all appointments (doctor schedules)
                if (ch == 6) {
                    cout << "\n--- All Doctor Schedules ---\n";
                    for (auto& d : doctorSchedule) {
                        cout << "Doctor " << d.first << " schedule: ";
                        for (auto& time : d.second) cout << time << " ";
                        cout << endl;
                    }
                }
                // Update patient info
                if (ch == 7) {
                    int pid = readInt("Patient ID: "); Patient* p = searchAVL(root, pid);
                    if (p) p->updateInfo();
                    else cout << "Patient not found!\n";
                }
                // Add emergency patient
                if (ch == 8) {
                    int sev = readInt("Severity: ");
                    int pid = readInt("Patient ID: ");
                    emgPQ.push({sev, pid});
                    cout << "Emergency added.\n";
                }
                // View emergency patients
                if (ch == 9) {
                    cout << "\n--- Emergency Patients ---\n";
                    priority_queue<pair<int, int>> temp = emgPQ;
                    while (!temp.empty()) {
                        cout << "Patient ID: " << temp.top().second << " | Severity: " << temp.top().first << endl;
                        temp.pop();
                    }
                }
                // Assign doctor to patient
                if (ch == 11) {
                    int did = readInt("Doctor ID: ");
                    int pid = readInt("Patient ID: ");
                    docMap[did].push_back(pid);
                    cout << "Assigned.\n";
                }
                // View doctor assignments
                if (ch == 12) {
                    cout << "\n--- Doctor Assignments ---\n";
                    for (auto& d : docMap) {
                        cout << "Doctor " << d.first << " -> ";
                        for (int p : d.second) cout << p << " ";
                        cout << endl;
                    }
                }
                // Add doctor
                if (ch == 13) {
                    string name = readLine("Doctor Name: ");
                    string spec = readLine("Specialization: ");
                    doctors[nextDoctorId] = Doctor(nextDoctorId, name, spec);
                    cout << "Doctor added with ID: " << nextDoctorId << endl;
                    nextDoctorId++;
                }
                // View doctors and their timetable
                if (ch == 14) {
                    cout << "\n--- Doctors & Schedules ---\n";
                    for (auto& d : doctors) {
                        cout << "ID:" << d.second.id << " | Name:" << d.second.name
                             << " | Specialization:" << d.second.specialization << " | Schedule: ";
                        for (auto& t : doctorSchedule[d.second.id]) cout << t << " ";
                        cout << endl;
                    }
                }
            }

            // ===== DOCTOR ACTIONS =====
            if (role == Role::DOCTOR) {
                if (ch == 6) {
                    int did = readInt("Enter your Doctor ID: ");
                    cout << "Your Schedule: ";
                    for (auto& t : doctorSchedule[did]) cout << t << " ";
                    cout << endl;
                }
                if (ch == 2) {
                    int pid = readInt("Patient ID: ");
                    Patient* p = searchAVL(root, pid);
                    if (p) {
                        cout << "ID:" << p->id << " | Name:" << p->name << " | Age:" << p->age
                             << " | Gender:" << p->gender << " | Disease:" << p->disease
                             << " | Bill:$" << p->bill << endl;
                        p->showHistory();
                    } else cout << "Patient not found!\n";
                }
                if (ch == 9) {
                    cout << "\n--- Emergency Patients ---\n";
                    priority_queue<pair<int, int>> temp = emgPQ;
                    while (!temp.empty()) {
                        cout << "Patient ID: " << temp.top().second << " | Severity: " << temp.top().first << endl;
                        temp.pop();
                    }
                }
            }

            // ===== PATIENT ACTIONS =====
            if (role == Role::PATIENT && currentPatient) {
                switch (ch) {
                    case 1: // View self info
                        cout << "ID:" << currentPatient->id << " | Name:" << currentPatient->name
                             << " | Age:" << currentPatient->age << " | Gender:" << currentPatient->gender
                             << " | Disease:" << currentPatient->disease << endl;
                        break;
                    case 2: // View medical history
                        currentPatient->showHistory();
                        break;
                    case 3: // Add medical history
                        currentPatient->addHistory(readLine("Date: "), readLine("Note: "));
                        cout << "Medical History Added.\n";
                        break;
                    case 4: { // View appointments
                        cout << "Your Appointments: ";
                        queue<Appointment> temp = apptQ;
                        while (!temp.empty()) {
                            if (temp.front().pid == currentPatient->id) cout << temp.front().time << " ";
                            temp.pop();
                        }
                        cout << endl;
                        break;
                    }
                    case 5: // Pay bill
                        currentPatient->payBill(); break;
                    case 6: // See bill
                        currentPatient->viewBill(); break;
                    default: cout << "Invalid Choice!\n";
                }
            } else if (role == Role::PATIENT && !currentPatient) {
                cout << "No logged-in patient.\n";
            }
        }
        // role loop
    }
    // main loop
    return 0;
}
