#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Account {
protected:
    int acc_number;
    static int account_count;
    static int next_acc_number; 

public:
    double balance;
    string name;
    Account(string n = "", double bal = 0.0) {
        name = n;
        acc_number = next_acc_number++;
        balance = bal;
        account_count++;
    }

    virtual void display() {
        cout << "Account Holder: " << name << endl;
        cout << "Account Number: " << acc_number << endl;
        cout << "Balance: $" << balance << endl;
    }

    Account* deposit(double amount) {
        this->balance += amount;
        return this;
    }

    void deposit(int amount) {
        cout <<"Deposited successfully!" << endl;
        balance += amount;
    }

    void withdraw(double amount) {
        if(amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful." << endl;
        } else {
            cout << "Insufficient balance!" << endl;
        }
    }

    double operator+(Account &other) {
        return this->balance + other.balance;
    }

    static void show_account_count() {
        cout << "Total Accounts: " << account_count << endl;
    }

    int get_acc_number() const { return acc_number; }

    friend void show_details(Account &a);
    friend class BankManager;
};
int Account::account_count = 0;
int Account::next_acc_number = 1001; // Start from 1001

void show_details(Account &a) {
    cout << "Name: " << a.name << ", Balance: $" << a.balance << endl;
}

class savings_account : public Account {
public:
    savings_account(string n="", double bal=0.0) : Account(n, bal) {}
    void display() override {
        cout << "[Savings Account]" << endl;
        Account::display();
    }
};

class current_account : public Account {
public:
    current_account(string n="", double bal=0.0) : Account(n, bal) {}
    void display() override {
        cout << "[Current Account]" << endl;
        Account::display();
    }
};


int main() {
    vector<savings_account> savings_accounts;
    vector<current_account> current_accounts;

    int choice;
    do {
        cout << "\n===== BANK MENU =====\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Current Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Display Accounts\n";
        cout << "6. Show Details\n";
        cout << "7. Show Combined Balance\n";
        cout << "8. Show Total Accounts\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                string name; double bal;
                cout << "Enter Name: "; 
                cin.ignore(); 
                getline(cin, name);
                cout << "Enter Initial Balance: "; cin >> bal;
                savings_account acc(name, bal);
                cout << "Account created! Account Number: " << acc.get_acc_number() << endl;
                savings_accounts.push_back(acc);
                break;
            }
            case 2: {
                string name; double bal;
                cout << "Enter Name: "; 
                cin.ignore(); 
                getline(cin, name);
                cout << "Enter Initial Balance: "; cin >> bal;
                current_account acc(name, bal);
                cout << "Account created! Account Number: " << acc.get_acc_number() << endl;
                current_accounts.push_back(acc);
                break;
            }
            case 3: {
                int type, amt;
                string input_name;
                cout << "1. Savings  2. Current : ";
                cin >> type;
                cout << "Enter account name: ";
                cin.ignore(); 
                getline(cin, input_name);
                cout << "Enter amount: "; cin >> amt;
                bool found = false;
                if(type == 1) {
                    for(auto& acc : savings_accounts) {
                        if(acc.name == input_name) {
                            acc.deposit(amt);
                            found = true;
                            break;
                        }
                    }
                } else {
                    for(auto& acc : current_accounts) {
                        if(acc.name == input_name) {
                            acc.deposit(amt);
                            found = true;
                            break;
                        }
                    }
                }
                if(!found) {
                    cout << "Account name not found or does not match account type!" << endl;
                }
                break;
            }
            case 4: {
                int type;
                double amt;
                string input_name;
                cout << "1. Savings  2. Current : ";
                cin >> type;
                cout << "Enter account holder name: ";
                cin.ignore(); 
                getline(cin, input_name);
                cout << "Enter amount: "; cin >> amt;
                bool found = false;
                if(type == 1) {
                    for(auto& acc : savings_accounts) {
                        if(acc.name == input_name) {
                            acc.withdraw(amt);
                            found = true;
                            break;
                        }
                    }
                } else {
                    for(auto& acc : current_accounts) {
                        if(acc.name == input_name) {
                            acc.withdraw(amt);
                            found = true;
                            break;
                        }
                    }
                }
                if(!found) {
                    cout << "Account name not found or does not match account type!" << endl;
                }
                break;
            }
            case 5: {
                cout << "--- Savings Accounts ---\n";
                for(auto& acc : savings_accounts) acc.display();
                cout << "--- Current Accounts ---\n";
                for(auto& acc : current_accounts) acc.display();
                break;
            }
            case 6: {
                for(auto& acc : savings_accounts) show_details(acc);
                for(auto& acc : current_accounts) show_details(acc);
                break;
            }
            case 7: {
                double total = 0;
                for(auto& acc : savings_accounts) total += acc.balance;
                for(auto& acc : current_accounts) total += acc.balance;
                cout << "Combined Balance: $" << total << endl;
                break;
            }
            case 8: {
                Account::show_account_count();
                break;
            }
            case 0:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while(choice != 0);

    return 0;
}