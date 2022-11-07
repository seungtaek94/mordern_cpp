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

    void withdraw(int amount)
    {
        if (balance - amount >= overdraft_limit)
        {
            balance -= amount;
            std::cout << "withdrew " << amount << ", balance is now " << balance << std::endl;
        }
    }
};

struct Command
{
    virtual void call() const = 0;
};


struct BankAccountCommnad : Command
{
    BankAccount& account;
    enum Action { deposit, withdraw } action;
    int amount;

    BankAccountCommnad(BankAccount& account, const Action action, const int amount)
    :account(account), action(action), amount(amount){ }

    void call() const override
    {
        switch (action)
        {
            case deposit:
                account.deposit(amount);
                break;
            case withdraw:
                account.withdraw(amount);
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