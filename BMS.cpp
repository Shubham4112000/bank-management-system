#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User {
public:
    User(const string& name, const string& password, int accountNumber)
        : name(name), password(password), accountNumber(accountNumber), balance(0.0), loanAmount(0.0) {}

    string GetName() const {
        return name;
    }

    bool CheckPassword(const string& inputPassword) const {
        return password == inputPassword;
    }

    double GetBalance() const {
        return balance;
    }

    int GetAccountNumber() const {
        return accountNumber;
    }

    void Deposit(double amount) {
        balance += amount;
        cout << "Amount deposited successfully. New balance: " << balance << endl;
    }

    void Withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Amount withdrawn successfully. New balance: " << balance << endl;
        } else {
            cout << "Insufficient balance." << endl;
        }
    }

    void TakeLoan(double amount) {
        loanAmount += amount;
        balance += amount;
        cout << "Loan taken successfully. New balance: " << balance << endl;
    }

    void Transfer(User& recipient, double amount) {
        if (balance >= amount) {
            balance -= amount;
            recipient.balance += amount;
            cout << "Amount transferred successfully. New balance: " << balance << endl;
        } else {
            cout << "Insufficient balance." << endl;
        }
    }

private:
    string name;
    string password;
    int accountNumber;
    double balance;
    double loanAmount;
};

class Bank {
public:
    void SignUp() {
        string name, password;
        int accountNumber;

        // Gather user information for sign up
        cout << "Enter your name: ";
        cin >> name;
        cout << "Create a password: ";
        cin >> password;
        cout << "Enter your account number: ";
        cin >> accountNumber;

        // Create a new user and add to the users vector
        User newUser(name, password, accountNumber);
        users.push_back(newUser);

        cout << "Sign up successful. Please remember your name, password, and account number for login." << endl;
    }

    void LogIn() {
        string name, password;

        // Gather user information for login
        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your password: ";
        cin >> password;

        // Check if the user exists and password is correct
        for (User& user : users) {
            if (user.GetName() == name && user.CheckPassword(password)) {
                loggedInUser = &user;
                cout << "Login successful. Welcome, " << loggedInUser->GetName() << "!" << endl;
                return;
            }
        }

        cout << "Invalid name or password." << endl;
    }

    void ShowBalance() const {
        if (loggedInUser) {
            cout << "Account number: " << loggedInUser->GetAccountNumber() << endl;
            cout << "Current balance: " << loggedInUser->GetBalance() << endl;
        } else {
            cout << "Please log in first." << endl;
        }
    }

    void Deposit() {
        if (loggedInUser) {
            double amount;

            // Gather deposit amount
            cout << "Enter amount to deposit: ";
            cin >> amount;

            // Deposit the amount for the logged-in user
            loggedInUser->Deposit(amount);
        } else {
            cout << "Please log in first." << endl;
        }
    }

    void Withdraw() {
        if (loggedInUser) {
            double amount;

            // Gather withdrawal amount
            cout << "Enter amount to withdraw: ";
            cin >> amount;

            // Withdraw the amount for the logged-in user
            loggedInUser->Withdraw(amount);
        } else {
            cout << "Please log in first." << endl;
        }
    }

    void TakeLoan() {
        if (loggedInUser) {
            double amount;

            // Gather loan amount
            cout << "Enter loan amount: ";
            cin >> amount;

            // Take a loan for the logged-in user
            loggedInUser->TakeLoan(amount);
        } else {
            cout << "Please log in first." << endl;
        }
    }

    void Transfer() {
        if (loggedInUser) {
            int recipientAccountNumber;
            double amount;

            // Gather recipient's account number and transfer amount
            cout << "Enter recipient's account number: ";
            cin >> recipientAccountNumber;

            User* recipient = nullptr;

            // Find the recipient user based on the account number
            for (User& user : users) {
                if (user.GetAccountNumber() == recipientAccountNumber) {
                    recipient = &user;
                    break;
                }
            }

            if (recipient) {
                // Transfer the amount to the recipient
                cout << "Enter amount to transfer: ";
                cin >> amount;

                loggedInUser->Transfer(*recipient, amount);
            } else {
                cout << "Recipient user does not exist." << endl;
            }
        } else {
            cout << "Please log in first." << endl;
        }
    }

    bool IsUserLoggedIn() const {
        return loggedInUser != nullptr;
    }

private:
    vector<User> users;
    User* loggedInUser = nullptr;
};

int DisplayInitialMenu() {
    int choice;

    // Display the initial menu options
    cout << endl;
    cout << "===== Bank Management System =====" << endl;
    cout << "1. Log In" << endl;
    cout << "2. Sign Up" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cout << endl;

    return choice;
}

int DisplayBankMenu() {
    int choice;

    // Display the bank menu options
    cout << endl;
    cout << "===== Bank Menu =====" << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Take Loan" << endl;
    cout << "5. Transfer Money" << endl;
    cout << "6. Log Out" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cout << endl;

    return choice;
}

int main() {
    Bank bank;
    int choice;

    // Display the initial menu and perform actions based on user choice
    do {
        choice = DisplayInitialMenu();

        switch (choice) {
            case 1:
                bank.LogIn();
                break;
            case 2:
                bank.SignUp();
                break;
            case 3:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        // If the user successfully logs in or signs up, display the bank menu and perform actions based on user choice
        while (bank.IsUserLoggedIn()) {
            choice = DisplayBankMenu();

            switch (choice) {
                case 1:
                    bank.ShowBalance();
                    break;
                case 2:
                    bank.Deposit();
                    break;
                case 3:
                    bank.Withdraw();
                    break;
                case 4:
                    bank.TakeLoan();
                    break;
                case 5:
                    bank.Transfer();
                    break;
                case 6:
                    bank = Bank();  // Reset the bank object to log out the user
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        }
    } while (true);

    return 0;
}
