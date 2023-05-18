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

class CheckingAccount : public Account {
public:
	CheckingAccount(const string& owner, double balance)
		: Account(owner, balance) {}
};

class IndividualAccount : public CheckingAccount {
private:
	static const double MAX_WITHDRAWAL_LIMIT;

public:
	void withdraw(double amount) override {
		if (amount <= MAX_WITHDRAWAL_LIMIT) {
			Account::withdraw(amount);
		}
		else {
			cout << "Withdrawal limit exceeded for " << owner << "'s individual checking account. Withdrawal failed. " << endl;
		}
	}
};

class MoneyMarketAccount : public CheckingAccount {
public:
	MoneyMarketAccount(const string& owner, double balance)
		: CheckingAccount(owner, balance) {}
};


const double IndividualAccount::MAX_WITHDRAWAL_LIMIT = 1000.0;

class Bank {
private:
	string name;
	vector < Account* accounts;

public:
	Bank(const string& name)
		: name(name) {}

	~Bank() {
		for (Account* account : accounts) {
			delete account;
		}
	}

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

int main() {



	return 0;
}

