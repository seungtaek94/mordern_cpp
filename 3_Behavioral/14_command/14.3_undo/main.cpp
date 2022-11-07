#include <iostream>

struct BankAccount
{
    int balance = 0;
    int overdraft_limit = -500;

    void deposit(int amount)
    {
        balance += amount;
        std::cout << "deposited " << amount << ", balance is now " << balance << std::endl;
    }

    bool withdraw(int amount)
    {
        if (balance - amount >= overdraft_limit)
        {
            balance -= amount;
            std::cout << "withdrew " << amount << ", balance is now " << balance << std::endl;
            return true;
        }
        return false;
    }
};

struct Command
{
    virtual void call() = 0;
    virtual void undo() = 0;
};


struct BankAccountCommnad : Command
{
    BankAccount& account;
    enum Action { deposit, withdraw } action;
    int amount;
    bool withddrawal_succeeded;

    BankAccountCommnad(BankAccount& account, const Action action, const int amount)
    :account(account), action(action), amount(amount), withddrawal_succeeded(false) { }

    void call() override
    {
        switch (action)
        {
            case deposit:
                account.deposit(amount);
                break;
            case withdraw:
                withddrawal_succeeded = account.withdraw(amount);
                break;
        }
    }

    void undo() override
    {
        switch (action)
        {
            case withdraw:
                if(withddrawal_succeeded)
                    account.deposit(amount);
                break;
            case deposit:
                withddrawal_succeeded = account.withdraw(amount);
                break;
        }
    }
};


int main()
{
    BankAccount ba;
    BankAccountCommnad cmd{ba, BankAccountCommnad::deposit, 100};
    cmd.call();
}