#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Transaction Class
class Transaction {
private:
    string type;       // transaction type: deposit or withdraw or transfer
    double amount;     // transaction amount
    string date;       // transaction date

public:
    // default constructor
    Transaction() {
        type = "";
        amount = 0;
        date = "";
    }

    // parameter constructor
    Transaction(string t, double a, string d) {
        type = t;
        amount = a;
        date = d;
    }

    // display transaction info
    void display() {
        cout << "Type: " << type << ", Amount: " << amount << ", Date: " << date << endl;
    }

    // getter & setter
    string getType() { return type; }      
    double getAmount() { return amount; }   
    string getDate() { return date; }     
    void setType(string t) { type = t; }   
    void setAmount(double a) { amount = a; } 
    void setDate(string d) { date = d; }    
};

//  Account Class (base class)
class Account {
protected:
    int accountNumber;                   // account number
    string ownerName;                    // owner's name
    double balance;                      // account balance
    vector<Transaction> history;         // transaction history

public:
    // default constructor
    Account() {
        accountNumber = 0;
        ownerName = "";
        balance = 0;
    }

    // parameter constructor
    Account(int num, string owner, double bal) {
        accountNumber = num;
        ownerName = owner;
        balance = bal;
    }

    // deposit money
    virtual void deposit(double amount, string date) {
        balance += amount;
        Transaction t("Deposit", amount, date);
        history.push_back(t);
    }

    // withdraw money
    virtual void withdraw(double amount, string date) {
        if (amount > balance) {
            cout << "Not enough balance" << endl;
        } else {
            balance -= amount;
            Transaction t("Withdraw", amount, date);
            history.push_back(t);
        }
    }

    // display account info
    void displayInfo() {
        cout << "Account Number: " << accountNumber
             << ", Owner: " << ownerName
             << ", Balance: " << balance << endl;
    }

    // Overload operator += to add transaction
    Account operator+=(Transaction t) {
        if (t.getType() == "Deposit") {
            balance += t.getAmount();
        } else if (t.getType() == "Withdraw") {
            if (t.getAmount() > balance) {
                cout << "Not enough balance!" << endl;
            } else {
                balance -= t.getAmount();
            }
        }
        history.push_back(t);

        // return a new Account object with updated info (no * or & used)
        return Account(accountNumber, ownerName, balance);
    }

    // Overload operator == to compare accounts by balance
    bool operator==(Account other) {
        return balance == other.balance;
    }

    // getter & setter
    int getAccountNumber() { return accountNumber; }  
    string getOwnerName() { return ownerName; }      
    double getBalance() { return balance; }          
    vector<Transaction> getHistory() { return history; } 
    void setAccountNumber(int num) { accountNumber = num; } 
    void setOwnerName(string owner) { ownerName = owner; }  
    void setBalance(double bal) { balance = bal; }     
};

// SavingsAccount Class (derived)
class SavingsAccount : public Account {
private:
    double interestRate;   // interest rate for savings account

public:
    // default constructor
    SavingsAccount() : Account() {
        interestRate = 0.01;
    }

    // parameter constructor
    SavingsAccount(int num, string owner, double bal, double rate)
        : Account(num, owner, bal) {
        interestRate = rate;
    }

    // override withdraw with limit rule
    void withdraw(double amount, string date) {
        if (amount > balance) {
            cout << "Not enough balance in savings account" << endl;
        } else if (amount > 1000) {
            cout << "Cannot withdraw more than 1000 at once" << endl;
        } else {
            balance -= amount;
            Transaction t("Withdraw", amount, date);
            history.push_back(t);
        }
    }

    // apply interest to savings account
    void applyInterest(string date) {
        double interest = balance * interestRate;
        balance += interest;
        Transaction t("Interest", interest, date);
        history.push_back(t);
    }

    // getter & setter
    double getInterestRate() { return interestRate; } 
    void setInterestRate(double rate) { interestRate = rate; } 
};

// Customer Class
class Customer {
private:
    string name;                     // customer name
    int id;                          // customer id
    vector<Account> accounts;        // list of accounts 

public:
    // default constructor
    Customer() {
        name = "";
        id = 0;
    }

    // parameter constructor
    Customer(string n, int i) {
        name = n;
        id = i;
    }

    // add new account
    void addAccount(Account acc) {
        accounts.push_back(acc);
    }

    // display all accounts
    void displayAccounts() {
        cout << "Customer: " << name << ", ID: " << id << endl;
        for (int i = 0; i < accounts.size(); i++) {
            accounts[i].displayInfo();
        }
    }

    // calculate total balance
    double totalBalance() {
        double sum = 0;
        for (int i = 0; i < accounts.size(); i++) {
            sum += accounts[i].getBalance();
        }
        return sum;
    }

    // getter & setter
    string getName() { return name; }             
    int getId() { return id; }                   
    vector<Account> getAccounts() { return accounts; } 
    void setName(string n) { name = n; }          
    void setId(int i) { id = i; }            
};

// Main Function
int main() {
    // Create customers
    Customer c1("Truong", 1);
    Customer c2("Hien", 2);

    // Create accounts
    Account acc1(101, "Truong", 500);
    SavingsAccount acc2(102, "Truong", 1000, 0.05);
    Account acc3(201, "Hien", 700);

    // Add accounts to customers 
    c1.addAccount(acc1);
    c1.addAccount(acc2);
    c2.addAccount(acc3);

    // Perform some transactions
    acc1.deposit(200, "2025-09-22");
    acc1.withdraw(100, "2025-09-22");

    acc2.deposit(500, "2025-09-22");
    acc2.withdraw(1500, "2025-09-22"); 
    acc2.withdraw(500, "2025-09-22");  
    acc2.applyInterest("2025-09-22");

    // Operator overloading
    Transaction t1("Deposit", 300, "2025-09-22");
    acc3 = acc3 += t1; // use overloaded +=

    if (acc1 == acc3) {
        cout << "Have the same balance" << endl;
    } else {
        cout << "Don't have the same balance" << endl;
    }

    // Display info
    c1.displayAccounts();
    cout << "Total balance for Truong: " << c1.totalBalance() << endl;

    c2.displayAccounts();
    cout << "Total balance for Hien: " << c2.totalBalance() << endl;

    return 0;
}
