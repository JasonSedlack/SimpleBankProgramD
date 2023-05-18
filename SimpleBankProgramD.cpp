#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Account {
protected:
	string owner;
	double balance;

public:
	Account(const string& owner, double balance)
		: owner(owner), balance(balance) {}

	virtual ~Account() {};

	double getBalance() const {
		return balance;
	}

	virtual void deposit(double amount) {
		balance += amount;
		cout << "Deposit: $" << amount << " to " << owner << "'s account. New balance $" << balance << endl;
	}

	virtual bool withdraw(double amount) {
		if (amount <= balance) {
			balance -= amount;
			cout << "Withdrawal: $" << amount << " from " << owner << "'s account. New balance: $" << balance << endl;
			return true;
		}
		else {
			cout << "Insufficient funds in " << owner << "'s account. Withdrawal failed." << endl;
			return false;
		}
	}

	virtual bool transfer(Account& destination, double amount) {
		if (withdraw(amount)) {
			destination.deposit(amount);
			cout << "Transfer: $" << amount << " from " << owner << "'s account to " << destination.owner << "'s account." << endl;
			return true;
		}
		else {
			cout << "Transfer failed. Insuffieint funds in " << owner << "'s account." << endl;
			return false;
		}
	}
};

class SavingsAccount : public Account {
private:
	static const double INTEREST_RATE;

public:
	SavingsAccount(const string& owner, double balance)
		: Account(owner, balance) {}

	void applyInterest() {
		double interest = balance * INTEREST_RATE;
		deposit(interest);
	}
};

class CheckingAccount : public Account {
public:
	CheckingAccount(const string& owner, double balance)
		: Account(owner, balance) {}
};

class IndividualAccount : public CheckingAccount {
private:
	static const double MAX_WITHDRAWAL_LIMIT;

public:
	IndividualAccount(const string& owner, double balance)
		: CheckingAccount(owner, balance) {}

	bool withdraw(double amount) override {
		if (amount <= MAX_WITHDRAWAL_LIMIT) {
			return Account::withdraw(amount);
		}
		else {
			cout << "Withdrawal limit exceeded for " << owner << "'s individual checking account. Withdrawal failed. " << endl;
			return false;
		}
	}
};

class MoneyMarketAccount : public CheckingAccount {
public:
	MoneyMarketAccount(const string& owner, double balance)
		: CheckingAccount(owner, balance) {}
};

class Bank {
private:
	string name;
	vector <Account*> accounts;

public:
	Bank(const string& name)
		: name(name) {}
	/*
	~Bank() {
		for (Account* account : accounts) {
			delete account;
		}
	}*/

	void addAccount(Account* account) {
		accounts.push_back(account);
	}

	void depositToAccount(int accountIndex, double amount) {
		if (accountIndex >= 0 && accountIndex < accounts.size()) {
			accounts[accountIndex]->deposit(amount);
		}
		else {
			cout << "Account Index out of bounds." << endl;
		}
	}

	void withdrawFromAccount(int accountIndex, double amount) {
		if (accountIndex >= 0 && accountIndex < accounts.size()) {
			accounts[accountIndex]->withdraw(amount);
		}
		else {
			cout << "Account Index out of bounds." << endl;
		}
	}

	void transferBetweenAccounts(int sourceIndex, int destinationIndex, double amount) {
		if (sourceIndex >= 0 && sourceIndex < accounts.size() &&
			destinationIndex >= 0 && destinationIndex < accounts.size()) {
			Account* source = accounts[sourceIndex];
			Account* destination = accounts[destinationIndex];
		}
		else {
			cout << "Account Index out of bounds" << endl;
		}
	}
};

const double IndividualAccount::MAX_WITHDRAWAL_LIMIT = 1000.0;
const double SavingsAccount::INTEREST_RATE = 0.05;

int main() {

	// create my bank
	Bank bank("Jason's Bank");

	// create accounts
	Account* account1 = new Account("Superman", 1000);
	Account* account2 = new CheckingAccount("The Flash", 2000);
	Account* account3 = new SavingsAccount("Batman", 3000);
	Account* account4 = new IndividualAccount("Hulk", 4000);
	Account* account5 = new MoneyMarketAccount("Aquaman", 5000);

	bank.addAccount(account1);
	bank.addAccount(account2);
	bank.addAccount(account3);
	bank.addAccount(account4);
	bank.addAccount(account5);

	bool allTestsPassed = true;

	// deposit, withdrawal, transfer

	bank.depositToAccount(0, 5);
	if (account1->getBalance() != 1005) {
		cout << "Test failed on account 1 deposit" << endl;
		allTestsPassed = false;
	}


	bank.withdrawFromAccount(0, 5);
	if (account1->getBalance() != 1000) {
		cout << "Test failed on account 1 withdrawal" << endl;
		allTestsPassed = false;
	}

	// needs debug
	bank.transferBetweenAccounts(0, 1, 5);
	if (account1->getBalance() != 995 || account2->getBalance() != 2005) {
		cout << account1->getBalance() << account2->getBalance();
		cout << "Test transfer failed on account 1 to account 2" << endl;
		allTestsPassed = false;
	}


	// clean up
	delete account1;
	delete account2;
	delete account3;
	delete account4;
	delete account5;


	return 0;
}

