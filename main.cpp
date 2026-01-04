#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class registation {
    string name, number, illness, hospital, username, usernumber;
    string room, speciality, time, fee, date, certificate;
    fstream file;
public:
    void login();
    void signup();
    void addHospital();
    void showAppointments();
    void search_doctor_by_hospital();
} obj;
int main() {
    cout << "\n================ WELCOME TO HEALTH CARE SYSTEM ================\n";
    int choose;
    cout << "1. Sign Up" << endl;
    cout << "2. Login" << endl;
    cout << "Enter your choice: ";
    cin >> choose;
    cin.ignore();
    switch (choose) {
    case 1:
        obj.signup();
        break;
    case 2:
        obj.login();
        break;
    default:
       cout << "Invalid choice! Exiting...\n";
    }
    cout << "\n================ THANK YOU =================\n";
    return 0;
}
// ------------ SIGNUP ------------
void registation::signup() {
    cout << "\n================ SIGN UP =================\n";
    int option;
    cout << "1: Are you a doctor?\n";
    cout << "2: Are you a patient?\n";
    cout << "Enter any option: ";
    cin >> option;
    cin.ignore();
    if(option == 1) {
        cout << "\n======= Doctor Sign-up=======\n";
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your number: ";
        getline(cin, number);
        cout << "Enter your hospital/address: ";
        getline(cin, hospital);
        cout << "Enter your certificate info: ";
        getline(cin, certificate);
        time = "";
        date = "";
        fee = "";
        file.open("doctor.txt", ios::app);
        file << name << "|" << number << "|" << hospital << "|" << certificate
             << "|" << time << "|" << date << "|" << fee << endl;
        file.close();
        cout << "\n✅ Doctor account created successfully!\n";
    }
    else if(option == 2) {
        cout << "\n==== Patient Sign-up ====\n";
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your number: ";
        getline(cin, number);
        cout << "Enter your illness: ";
        getline(cin, illness);

        file.open("patient.txt", ios::app);
        file << name << "|" << number << "|" << illness << endl;
        file.close();
        cout << "\n✅Patient account created successfully!\n";
    }
    else {
        cout << "Invalid choice!\n";
    }
}
// ------------ LOGIN ------------
void registation::login() {
    cout << "\n================ LOGIN =================\n";
    int option;
    cout << "\n1: Are you a doctor?\n";
    cout << "2: Are you a patient?\n";
    cout << "Enter your option: ";
    cin >> option;
    cin.ignore();
    if(option == 1) {
        cout << "\n====Doctor Login====\n";
        cout << "Enter your name: ";
        getline(cin, username);
        cout << "Enter your number: ";
        getline(cin, usernumber);
        file.open("doctor.txt", ios::in);
        string line;
        bool found = false;
        while(getline(file, line)) {
            stringstream ss(line);
            string name, number, hospital, cert;
            getline(ss, name, '|');
            getline(ss, number, '|');
            getline(ss, hospital, '|');
            getline(ss, cert, '|');

            if(name == username && number == usernumber) {
                cout << "\nLogin successful...!\n";
                cout << "Doctor: " << name << endl;
                cout << "Number: " << number << endl;
                cout << "Hospital: " << hospital << endl;
                cout << "Certificate: " << cert << endl;
                found = true;
                break;
            }
        }
        file.close();
        if(!found) {
            cout << "❌ Incorrect name or number!\n";
            return;
        }
        int opt;
        cout << "\n1. Add Hospital Details\n2. View Today's Appointments\nEnter your choice: ";
        cin >> opt;
        cin.ignore();
        if(opt == 1)
            addHospital();
        else if(opt == 2)
            showAppointments();
        else
            cout << "Invalid option!\n";
    }
    else if(option == 2) {
        cout << "\n====Patient Login====\n";
        cout << "Enter your name: ";
        getline(cin, username);
        cout << "Enter your number: ";
        getline(cin, usernumber);
        file.open("patient.txt", ios::in);
        string line;
        bool found = false;
        while(getline(file, line)) {
            stringstream ss(line);
            string n, num, ill;
            getline(ss, n, '|');
            getline(ss, num, '|');
            getline(ss, ill, '|');
            if(n == username && num == usernumber) {
                cout << "\n✅ Login Successful!\n";
                cout << "Patient: " << n << endl;
                cout << "Number: " << num << endl;
                cout << "Illness: " << ill << endl;
                found = true;
            }
        }
        if(!found) cout << "❌ Incorrect name or number!\n";
        file.close();
        search_doctor_by_hospital();
    }
}
// ------------ ADD HOSPITAL ------------
void registation::addHospital() {
    cout << "\n====Add Hospital Details====\n";
    cout << "Enter Hospital Name: ";
    getline(cin, hospital);
    cout << "Enter Room Number: ";
    getline(cin, room);
    cout << "Enter Speciality (e.g., Heart, Eye): ";
    getline(cin, speciality);
    cout << "Enter Available Time: ";
    getline(cin, time);
    cout << "Enter Available Date: ";
    getline(cin, date);
    cout << "Enter Visiting Fee: ";
    getline(cin, fee);
    file.open("hospital.txt", ios::app);
    file << username << "|" << usernumber << "|" << hospital << "|" << room << "|" << speciality << "|" << time << "|" << date << "|" << fee << endl;
    file.close();
   cout << "\n✅ Hospital details added successfully!\n";
}
// ------------ SHOW APPOINTMENTS ------------
void registation::showAppointments() {
    cout << "\n======Today's Appointments =======\n";
    file.open("appointment.txt", ios::in);
    string line;
    bool found = false;
    while(getline(file, line)) {
        stringstream ss(line);
        string patientName, patientNumber, doctorName, hospitalName, Time, Date, Fee;
        getline(ss, patientName, '|');
        getline(ss, patientNumber, '|');
        getline(ss, doctorName, '|');
        getline(ss, hospitalName, '|');
        getline(ss, Time, '|');
        getline(ss, Date, '|');
        getline(ss, Fee, '|');
        if(doctorName == username) {
            cout << "Patient: " << patientName
                 << " | Number: " << patientNumber
                 << " | Hospital: " << hospitalName
                 << " | Time: " << Time
                 << " | Date: " << Date
                 << " | Fee: " << Fee << endl;
            found = true;
        }
    }
    if(!found) cout << "No appointments yet!\n";
    file.close();
}
// ---------------- SEARCH DOCTOR BY HOSPITAL + BOOKING ----------------
void registation::search_doctor_by_hospital() {
    cout << "\nDo you want to search doctor by hospital? (y/n): ";
    char ch;
    cin >> ch;
    cin.ignore();
    if(ch != 'y' && ch != 'Y') return;
    string searchHospital;
    cout << "Enter Hospital Name to search: ";
    getline(cin, searchHospital);
    file.open("doctor.txt", ios::in);
    bool doctorFound = false;
    string doctorLine;
    while(getline(file, doctorLine)) {
        stringstream ss(doctorLine);
        string dname, dnumber, hospitalname, certificate, dtime, ddate, dfee;
        getline(ss, dname, '|');
        getline(ss, dnumber, '|');
        getline(ss, hospitalname, '|');
        getline(ss, certificate, '|');
        getline(ss, dtime, '|');
        getline(ss, ddate, '|');
        getline(ss, dfee, '|');
        if(hospitalname == searchHospital) {
            doctorFound = true;
            cout << "\nDoctor Name: " << dname
                 << "\nNumber: " << dnumber
                 << "\nHospital: " << hospitalname
                 << "\nCertificate: " << certificate
                 << "\nTime: " << dtime
                 << "\nDate: " << ddate
                 << "\nFee: " << dfee << endl;
            cout << "\nDo you want to book this doctor? (y/n): ";
            char book;
            cin >> book;
            cin.ignore();
            if(book == 'y' || book == 'Y') {
                string bkash;
                cout << "Enter your Bkash number for payment: ";
                getline(cin, bkash);
                cout << "Processing payment...";
                cout << "\nPayment Successful!\n";
                fstream serialFile;
                serialFile.open("appointment.txt", ios::app);
                int serial = rand() % 20 + 1;
                serialFile << username << "|" << usernumber << "|" << dname
                           << "|" << hospitalname << "|" << dtime << "|" << ddate << "|" << dfee << endl;
                serialFile.close();
                cout << "\n✅ Your appointment booked successfully! Serial: " << serial << endl;
                file.close();
                return;
            }
        }
    }
    file.close();
    cout << "\nDo you want to see available doctors? (y/n): ";
    char seeAvailable;
    cin >> seeAvailable;
    cin.ignore();
    if(seeAvailable == 'y' || seeAvailable == 'Y') {
        cout << "\n================ Available Doctors ================\n";
        file.open("doctor.txt", ios::in);
        while(getline(file, doctorLine)) {
            stringstream ss(doctorLine);
            string dname, dnumber, hospitalname, certificate, dtime, ddate, dfee;
            getline(ss, dname, '|');
            getline(ss, dnumber, '|');
            getline(ss, hospitalname, '|');
            getline(ss, certificate, '|');
            getline(ss, dtime, '|');
            getline(ss, ddate, '|');
            getline(ss, dfee, '|');
            if(dtime.empty()) dtime = "Not Available";
            if(ddate.empty()) ddate = "Not Available";
            if(dfee.empty()) dfee = "Not Set";
            cout << "Doctor Name: " << dname << endl;
            cout << "Number: " << dnumber << endl;
            cout << "Hospital: " << hospitalname << endl;
            cout << "Certificate: " << certificate << endl;
            cout << "Time: " << dtime << endl;
            cout << "Date: " << ddate << endl;
            cout << "Fee: " << dfee << endl;
            cout << "-----------------------------\n";
        }
        file.close();
        cout << "\nDo you want to book an appointment from available doctors? (y/n): ";
        char bookAll;
        cin >> bookAll;
        cin.ignore();
        if(bookAll == 'y' || bookAll == 'Y') {
            string selectedDoctor;
            cout << "Enter Doctor Name you want to book: ";
            getline(cin, selectedDoctor);
            string bkash;
            cout << "Enter your Bkash number for payment: ";
            getline(cin, bkash);
            cout << "Processing payment...";
            cout << "\nPayment Successful!\n";
            fstream serialFile;
            serialFile.open("appointment.txt", ios::app);
            int serial = rand() % 20 + 1;
            file.open("doctor.txt", ios::in);
            string line;
            string selHospital, selTime, selDate, selFee;
            while(getline(file, line)) {
                stringstream ss(line);
                string dname, dnumber, hospitalname, certificate, dtime, ddate, dfee;
                getline(ss, dname, '|');
                getline(ss, dnumber, '|');
                getline(ss, hospitalname, '|');
                getline(ss, certificate, '|');
                getline(ss, dtime, '|');
                getline(ss, ddate, '|');
                getline(ss, dfee, '|');

                if(dname == selectedDoctor) {
                    selHospital = hospitalname;
                    selTime = dtime;
                    selDate = ddate;
                    selFee = dfee;
                    break;
                }
            }
            file.close();

            serialFile << username << "|" << usernumber << "|" << selectedDoctor
                       << "|" << selHospital << "|" << selTime << "|" << selDate << "|" << selFee << endl;
            serialFile.close();
            cout << "Your appointment booked successfully!" << endl;
            cout << "Your Serial Number: " << serial << endl;
        }
    } else {
        cout << "\nOkay, returning to menu...\n";
    }
}

