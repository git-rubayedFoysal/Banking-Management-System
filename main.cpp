#include <bits/stdc++.h>
#include <dirent.h>

#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Hash_Function for Pin
long long hash_pin(long long pin) {
    return (pin * 3700 * 13 + 99) ^ (pin >> 21);
}
// Clear terminal
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// verify account number & pin
bool verifyLogin(long long acc_no, long long enteredPIN) {
    long long storedPIN;
    ifstream fin("./accounts/" + to_string(acc_no) + ".txt");
    if (!fin) {
        return 0;
    }

    string line;
    while (getline(fin, line)) {
        if (line.find("PIN: ") != string ::npos) {
            storedPIN = stoll(line.substr(5));
            break;
        }
    }
    fin.close();

    if (storedPIN != hash_pin(enteredPIN)) {
        return 0;
    }
    return 1;
}

// Function to get current date & time
string currentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    char buffer[25];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", ltm);
    return string(buffer);
}

// Show Account Data.
void showAcc(long long acc_no) {
    clearScreen();
    ifstream fin("./accounts/" + to_string(acc_no) + ".txt");
    string line;

    while (getline(fin, line)) {
        if (line.find("PIN: ") != string ::npos) {
            continue;
        }
        cout << line << endl;
    }
    fin.close();
}

// Deposit Money
void deposit(long long acc_no) {
    clearScreen();
    cout << "=============================================================================" << endl;
    cout << "                        DEPOSIT MONEY" << endl;
    cout << "=============================================================================" << endl;
    double amount;
    cout << "Enter The Amount To Deposit: ";
    cin >> amount;
    if (amount < 0) {
        clearScreen();
        cout << "❌ Invalid Amount, Please Try Again." << endl;
        return;
    }

    ifstream fin("./accounts/" + to_string(acc_no) + ".txt");
    double balance = 0;
    vector<string> lines;
    string line;

    // update balance
    while (getline(fin, line)) {
        if (line.find("Balance: ") != string::npos) {
            balance = stod(line.substr(9));           // read current balance
            balance += amount;                        // add deposit
            line = "Balance: " + to_string(balance);  // update line
        }
        lines.push_back(line);  // store all lines for rewriting
    }
    fin.close();

    // rewrite the files
    ofstream fout;
    fout.open("./accounts/" + to_string(acc_no) + ".txt");
    for (auto& l : lines) {
        fout << l << endl;
    }
    fout.close();

    fout.open("./transactions/" + to_string(acc_no) + "_history" + ".txt", ios::app);
    fout << "[" << currentDateTime() << "]" << " Deposit: +" << amount << " | New Balance: " << balance << endl;
    fout.close();

    clearScreen();
    cout << "৳ " << amount << " Successfully Credited To Your Account! Your New Balance is ৳ " << balance << "." << endl;
}

// withdraw money
void withdraw(long long acc_no) {
    clearScreen();
    cout << "=============================================================================" << endl;
    cout << "                        WITHDRAW MONEY" << endl;
    cout << "=============================================================================" << endl;
    double amount;
    cout << "Enter The Amount To Withdraw: ";
    cin >> amount;
    if (amount < 0) {
        clearScreen();
        cout << "❌ Invalid Amount, Please Try Again." << endl;
        return;
    }

    ifstream fin;
    ofstream fout;
    vector<string> lines;
    string line;
    double balance = 0;

    // update balance
    fin.open("./accounts/" + to_string(acc_no) + ".txt");
    while (getline(fin, line)) {
        if (line.find("Balance: ") != string ::npos) {
            balance = stod(line.substr(9));
            if (balance < amount) {
                clearScreen();
                cout << "❌ Insufficent Balance!" << endl;
                return;
            }
            balance -= amount;
            line = "Balance: " + to_string(balance);
        }
        lines.push_back(line);
    }
    fin.close();

    // rewrite file;
    fout.open("./accounts/" + to_string(acc_no) + ".txt");
    for (auto& l : lines) {
        fout << l << endl;
    }
    fout.close();

    fout.open("./transactions/" + to_string(acc_no) + "_history" + ".txt", ios::app);
    fout << "[" << currentDateTime() << "]" << " Withdraw: -" << amount << " | New Balance: " << balance << endl;
    fout.close();

    clearScreen();
    cout << "৳ " << amount << " Successfully Debited From Your Account! Your New Balance is ৳ " << balance << "." << endl;
}

// Check Balance
void checkBalance(long long acc_no) {
    double balance = 0;
    ifstream fin;
    ofstream fout;
    string line;

    fin.open("./accounts/" + to_string(acc_no) + ".txt");
    while (getline(fin, line)) {
        if (line.find("Balance: ") != string ::npos) {
            balance = stod(line.substr(9));
        }
    }
    fin.close();

    fout.open("./transactions/" + to_string(acc_no) + "_history" + ".txt", ios::app);
    fout << "[" << currentDateTime() << "] Balance Checked." << endl;
    fout.close();

    clearScreen();
    cout << "Current Balance: ৳ " << balance << endl;
}

// View Transaction History
void viewHistory(long long acc_no) {
    ifstream fin;
    string line;

    clearScreen();
    cout << "Transaction History: " << endl;
    cout << "---------------------------------------------------------------" << endl;
    fin.open("./transactions/" + to_string(acc_no) + "_history" + ".txt");
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
}

// delete account
void deleteAcc(long long acc_no) {
    clearScreen();
    cout << "=============================================================================" << endl;
    cout << "                       DELETE ACCOUNT" << endl;
    cout << "=============================================================================" << endl;
    long long enteredPIN;
    cout << "Enter PIN For Delete Account: ";
    cin >> enteredPIN;

    if (!verifyLogin(acc_no, enteredPIN)) {
        clearScreen();
        cout << "❌ PIN Verification Failed. Account Not Deleted." << endl;
        return;
    }

    string accPath = "./accounts/" + to_string(acc_no) + ".txt";
    string tranPath = "./transactions/" + to_string(acc_no) + "_history.txt";

    bool status0 = (remove(accPath.c_str()) == 0);
    bool status1 = (remove(tranPath.c_str()) == 0);

    clearScreen();
    if (status0 && status1) {
        cout << "✅ Account Closed Successfully." << endl;
    } else {
        cout << "⚠️ Error Deleting Account Files." << endl;
    }
}

// Main Menu
void mainMenu() {
    cout << endl;
    cout << "=============================================================================" << endl;
    cout << u8"                   \U0001F3E2 BANKING MANAGEMENT SYSTEM" << endl;
    cout << "=============================================================================" << endl;
    cout << "1. Create New Account." << endl;
    cout << "2. Login To Existing Account." << endl;
    cout << "3. Admin Mode." << endl;
    cout << "4. Exit." << endl;
    cout << "--------------------------------------------------" << endl;
}

// User Menu
void userMenu() {
    clearScreen();
    long long acc_no;
    long long enteredPIN;
    cout << "=============================================================================" << endl;
    cout << "                           USER MENU" << endl;
    cout << "=============================================================================" << endl;
    cout << "Enter Account Number: ";
    cin >> acc_no;
    cout << "Enter PIN: ";
    cin >> enteredPIN;
    if (!verifyLogin(acc_no, enteredPIN)) {
        clearScreen();
        cout << "❌ Incorrect Account Number or PIN. Please Try Again." << endl;
        return;
    }
    string name;
    ifstream fin("./accounts/" + to_string(acc_no) + ".txt");

    while (getline(fin, name)) {
        if (name.find("Name: ") != string ::npos) {
            name = name.substr(6);
            break;
        }
    }
    fin.close();

    clearScreen();
    bool flag = 1;
    while (flag) {
        cout << endl;
        cout << "=============================================================================" << endl;
        cout << "                   Welcome, [" << name << "]" << endl;
        cout << "=============================================================================" << endl;
        cout << "1. Show Account Details." << endl;
        cout << "2. Deposit Money." << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Check Balance." << endl;
        cout << "5. View Transaction History." << endl;
        cout << "6. Delete Account." << endl;
        cout << "7. Logout." << endl;
        cout << "--------------------------------------------------" << endl;

        int opt;
        cout << "Enter Your Choice_";
        cin >> opt;
        cin.ignore();
        switch (opt) {
            case 1:
                showAcc(acc_no);
                break;

            case 2:
                deposit(acc_no);
                break;

            case 3:
                withdraw(acc_no);
                break;

            case 4:
                checkBalance(acc_no);
                break;
            case 5:
                viewHistory(acc_no);
                break;
            case 6:
                deleteAcc(acc_no);
                flag = 0;
                break;
            case 7:
                flag = 0;
                clearScreen();
                break;

            default:
                cout << "Invalid Choice!" << endl;
                break;
        }
    }
}

// verify admin
bool verifyAdmin(string adminId, long long enteredPin) {
    ifstream fin("./admin/admins.txt");
    string line;
    while (getline(fin, line)) {
        int pos = line.find('|');
        string fileID = line.substr(0, pos);
        long long filePIN = stoll(line.substr(pos + 1));

        if (adminId == fileID && hash_pin(enteredPin) == filePIN) {
            fin.close();
            return 1;
        }
    }
    fin.close();
    return 0;
}

// verify admin
bool verifyAdmin(long long enteredPin) {
    ifstream fin("./admin/admins.txt");
    string line;
    while (getline(fin, line)) {
        int pos = line.find('|');
        long long filePIN = stoll(line.substr(pos + 1));

        if (hash_pin(enteredPin) == filePIN) {
            fin.close();
            return 1;
        }
    }
    fin.close();
    return 0;
}

// View All Account
void viewAllAccounts() {
    clearScreen();
    cout << "Account Number\t\t\tName\t\t\tBalance\n";
    cout << "---------------------------------------------------------------\n";

    DIR* dir = opendir("./accounts");
    if (!dir) {
        cout << "❌ Cannot open accounts directory\n";
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        string filename = entry->d_name;

        if (filename == "." || filename == "..") continue;
        if (filename.find(".txt") == string::npos) continue;

        ifstream fin("./accounts/" + filename);
        if (!fin) continue;

        string line, accNo, name;
        double balance = 0;

        while (getline(fin, line)) {
            if (line.find("Account Number: ") != string::npos)
                accNo = line.substr(16);
            else if (line.find("Name: ") != string::npos)
                name = line.substr(6);
            else if (line.find("Balance: ") != string::npos)
                balance = stod(line.substr(9));
        }
        fin.close();

        cout << accNo << "\t\t\t" << name << "\t\t৳ " << balance << endl;
    }
    closedir(dir);
}

// Search Account
void SearchAcc() {
    clearScreen();
    cout << "=============================================================================" << endl;
    cout << "                        SEARCH ACCOUNT" << endl;
    cout << "=============================================================================" << endl;
    long long acc_no;
    cout << "Enter Account Number: ";
    cin >> acc_no;

    vector<string> lines;
    string line;

    ifstream fin("./accounts/" + to_string(acc_no) + ".txt");
    if (!fin) {
        clearScreen();
        cout << "❌ Account Not Found" << endl;
        return;
    }

    while (getline(fin, line)) {
        if (line.find("PIN: ") != string ::npos) {
            continue;
        }
        lines.push_back(line);
    }

    clearScreen();
    for (auto& l : lines) {
        cout << l << endl;
    }
    fin.close();
}

// Delete Account for admin
void deleteAccAdmin() {
    clearScreen();
    cout << "=============================================================================" << endl;
    cout << "                       DELETE ACCOUNT" << endl;
    cout << "=============================================================================" << endl;
    long long enteredPIN, acc_no;
    cout << "Enter Account Number: ";
    cin >> acc_no;

    ifstream fin("./accounts/" + to_string(acc_no) + ".txt");
    if (!fin) {
        clearScreen();
        cout << "❌ Invalid Account Number. Please Try Again" << endl;
        return;
    }
    fin.close();

    cout << "Enter Admin PIN For Delete Account: ";
    cin >> enteredPIN;

    if (!verifyAdmin(enteredPIN)) {
        clearScreen();
        cout << "❌ PIN Verification Failed. Account Not Deleted." << endl;
        return;
    }

    string accPath = "./accounts/" + to_string(acc_no) + ".txt";
    string tranPath = "./transactions/" + to_string(acc_no) + "_history.txt";

    bool status0 = (remove(accPath.c_str()) == 0);
    bool status1 = (remove(tranPath.c_str()) == 0);

    clearScreen();
    if (status0 && status1) {
        cout << "✅ Account Closed Successfully." << endl;
    } else {
        cout << "⚠️ Error Deleting Account Files." << endl;
    }
}

// Reset Pin
void resetPin() {
    clearScreen();
    cout << "=============================================================================" << endl;
    cout << "                       RESET ACCOUNT PIN" << endl;
    cout << "=============================================================================" << endl;
    long long enteredPIN, acc_no;
    cout << "Enter Account Number: ";
    cin >> acc_no;
    long long newPin;
    cout << "Enter New PIN: ";
    cin >> newPin;

    if (newPin < 1000 || newPin > 9999) {
        clearScreen();
        cout << "❌ PIN must be 4 digits\n";
        return;
    }

    ifstream fin("./accounts/" + to_string(acc_no) + ".txt");
    if (!fin) {
        clearScreen();
        cout << "❌ Invalid Account Number. Please Try Again" << endl;
        return;
    }

    // update pin
    string line;
    vector<string> lines;
    while (getline(fin, line)) {
        if (line.find("PIN: ") != string ::npos) {
            line = "PIN: " + to_string(hash_pin(newPin));
        }
        lines.push_back(line);
    }
    fin.close();
    // rewrite pin
    ofstream fout("./accounts/" + to_string(acc_no) + ".txt");
    for (auto& l : lines) {
        fout << l << endl;
    }
    fout.close();
    clearScreen();
    cout << "✅ PIN Reset Successful" << endl;
}

// Total Balance
void totalBalance() {
    clearScreen();
    double total = 0;
    DIR* dir = opendir("./accounts");
    if (!dir) {
        cout << "❌ Cannot open accounts directory\n";
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        string filename = entry->d_name;

        if (filename == "." || filename == "..") continue;
        if (filename.find(".txt") == string::npos) continue;

        ifstream fin("./accounts/" + filename);
        if (!fin) continue;

        string line;

        while (getline(fin, line)) {
            if (line.find("Balance: ") != string::npos)
                total += stod(line.substr(9));
        }
        fin.close();
    }
    closedir(dir);

    cout << "🏦 Total Bank Balance: ৳ " << total << endl;
}

// Admin Menu
void adminMenu() {
    clearScreen();
    bool flag = 1;
    while (flag) {
        cout << endl;
        cout << "=============================================================================" << endl;
        cout << "                        🛠️ ADMIN CONTROL PANEL" << endl;
        cout << "=============================================================================" << endl;
        cout << endl;
        cout << "1. View All Accounts" << endl;
        cout << "2. Search Account" << endl;
        cout << "3. Delete Account" << endl;
        cout << "4. Reset PIN" << endl;
        cout << "5. Total Bank Balance" << endl;
        cout << "6. Exit" << endl;
        cout << "--------------------------------------------------" << endl;

        int opt;
        cout << "Enter Your Choice_";
        cin >> opt;
        cin.ignore();
        switch (opt) {
            case 1:
                viewAllAccounts();
                break;

            case 2:
                SearchAcc();
                break;

            case 3:
                deleteAccAdmin();
                break;

            case 4:
                resetPin();
                break;
            case 5:
                totalBalance();
                break;
            case 6:
                flag = 0;
                clearScreen();
                break;

            default:
                cout << "Invalid Choice!" << endl;
                break;
        }
    }
}

// Admin Login
void adminLogin() {
    clearScreen();
    cout << "=============================================================================" << endl;
    cout << "                         ADMIN  LOGIN" << endl;
    cout << "=============================================================================" << endl;
    string adminId;
    long long PIN;
    cout << "Enter Admin Id: ";
    getline(cin, adminId);
    cout << "Enter Admin PIN: ";
    cin >> PIN;
    if (verifyAdmin(adminId, PIN)) {
        adminMenu();
    } else {
        clearScreen();
        cout << "❌ Access Denied." << endl;
    }
}

// Create Admin
void createAdmin() {
    clearScreen();
    cout << "=============================================================================" << endl;
    cout << "                          ADD NEW ADMIN\n";
    cout << "=============================================================================" << endl;

    bool firstAdmin = false;
    ifstream fin("./admin/admins.txt");
    if (!fin) firstAdmin = true;
    fin.close();

    // Verify existing admin
    if (!firstAdmin) {
        long long currPin;
        cout << "Enter Current Admin PIN: ";
        cin >> currPin;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!verifyAdmin(currPin)) {
            clearScreen();
            cout << "❌ Authorization Failed\n";
            return;
        }
    }

    string newAdminId;
    long long newAdminPin;
    cout << "Enter New Admin ID: ";
    getline(cin, newAdminId);

    cout << "Enter New Admin PIN: ";
    cin >> newAdminPin;

    if (newAdminPin < 1000 || newAdminPin > 9999) {
        clearScreen();
        cout << "❌ PIN must be 4 digits\n";
        return;
    }

    // Check duplicate ID
    fin.open("./admin/admins.txt");
    string line;
    while (getline(fin, line)) {
        if (line.substr(0, line.find('|')) == newAdminId) {
            cout << "❌ Admin ID already exists\n";
            fin.close();
            return;
        }
    }
    fin.close();

    ofstream fout("./admin/admins.txt", ios::app);
    fout << newAdminId << "|" << hash_pin(newAdminPin) << endl;
    fout.close();

    clearScreen();
    cout << "✅ New Admin Created Successfully\n";
}

// Admin Panel
void adminPanel() {
    bool flag = 1;
    clearScreen();
    while (flag) {
        cout << "=============================================================================" << endl;
        cout << "                         ADMIN PANEL" << endl;
        cout << "=============================================================================" << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. Create New Admin" << endl;
        cout << "3. Back" << endl;
        cout << "--------------------------------------------------" << endl;
        int opt;
        cout << "Enter Your Choice_";
        cin >> opt;
        cin.ignore();

        switch (opt) {
            case 1:
                adminLogin();
                break;
            case 2:
                createAdmin();
                break;
            case 3:
                flag = 0;
                clearScreen();
                break;

            default:
                cout << "Invalid Choice!" << endl;
                break;
        }
    }
}

// Create Account
void createAccount() {
    clearScreen();
    string name;
    long long pin;
    double deposit;
    long long acc_no;
    string currDate = currentDateTime();
    ifstream fin;
    ofstream fout;

    cout << "Enter Full Name: ";
    getline(cin, name);

    cout << "Enter PIN: ";
    cin >> pin;

    if (pin < 1000 || pin > 9999) {
        clearScreen();
        cout << "❌ PIN must be 4 digits\n";
        return;
    }

    cout << "Enter Initial Deposit: ";
    cin >> deposit;

    // Read account counter
    fin.open("./data/acc_counter.txt");
    fin >> acc_no;
    fin.close();

    // write new account counter
    fout.open("./data/acc_counter.txt");
    fout << acc_no + 1;
    fout.close();

    // Generate Account
    fout.open("./accounts/" + to_string(acc_no) + ".txt");
    fout << "Account Number: " << acc_no << endl;
    fout << "Name: " << name << endl;
    fout << "PIN: " << hash_pin(pin) << endl;
    fout << "Balance: " << deposit << endl;
    fout << "Date Created: " << currDate << endl;
    fout.close();

    // generate transactions log
    fout.open("./transactions/" + to_string(acc_no) + "_history" + ".txt");
    fout << "[" << currDate << "]";
    fout << " Account Created.";
    fout << " - Initial Deposit: " << deposit << endl;
    fout.close();

    clearScreen();
    cout << "✅ Account Created Successfully!" << endl;
    cout << "Your Account Number: " << acc_no << endl;
    cout << "Keep It Safe For Login." << endl;
    cout << endl;
}

// main function
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    bool flag = 1;
    while (flag) {
        mainMenu();
        int opt;
        cout << "Enter Your Choice_";
        cin >> opt;
        cin.ignore();  // Ignore the newline character left in the input buffer

        switch (opt) {
            case 1:
                createAccount();
                break;

            case 2:
                userMenu();
                break;

            case 3:
                adminPanel();
                break;

            case 4:
                flag = 0;
                clearScreen();
                cout << endl;
                cout << "=============================================================================" << endl;
                cout << "                   Thank You For Using The Banking System!" << endl;
                cout << "                     Your Trust Is Our Responsibility.💰" << endl;
                cout << "=============================================================================" << endl;
                cout << endl;
                break;

            default:
                cout << "Invalid Choice!" << endl;
                break;
        }
    }
    return 0;
}
