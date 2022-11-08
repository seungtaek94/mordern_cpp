#include <iostream>
#include <vector>

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


struct BankAccountCommand : Command
{
    BankAccount& account;
    enum Action { deposit, withdraw } action;
    int amount;
    bool withddrawal_succeeded;

    BankAccountCommand(BankAccount& account, const Action action, const int amount)
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


struct CompositeBankAccountCommand : std::vector<BankAccountCommand>, Command
{
    CompositeBankAccountCommand(const std::initializer_list<value_type>& items)
    :std::vector<BankAccountCommand>(items){ }

    void call() override
    {
        for(auto & cmd : *this)
            cmd.call();
    }

    void undo() override
    {
        for (auto it = rbegin(); it != rend(); ++it)
        {
            it->undo();
        }
    }
};


struct  MoneyTransferCommand : CompositeBankAccountCommand
{
    MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
    : CompositeBankAccountCommand
              {
                      BankAccountCommand{from ,BankAccountCommand::withdraw, amount},
                      BankAccountCommand{to ,BankAccountCommand::deposit, amount}
              } {}

    void call() override
    {
        bool ok = true;
        for(auto& cmd : *this)
        {
            if(ok)
            {
                cmd.call();
                ok = cmd.withddrawal_succeeded;
            }
            else
            {
                cmd.withddrawal_succeeded = false;
            }
        }
    }
};


int main()
{
    BankAccount ba;
    /*vector<BankAccountCommand> commands{*/
    CompositeBankAccountCommand commands{
            BankAccountCommand{ ba, BankAccountCommand::deposit, 100 },
            BankAccountCommand{ ba, BankAccountCommand::withdraw, 200 }
    };

    std::cout << ba.balance << std::endl;

    // apply all the commands
    /*for (auto& cmd : commands)
    {
    cmd.call();
    }*/
    commands.call();

    std::cout << ba.balance << std::endl;

    /*for_each(commands.rbegin(), commands.rend(),
    [](const BankAccountCommand& cmd) { cmd.undo(); });*/
    commands.undo();

    std::cout << ba.balance << std::endl;

    getchar();
    return 0;
}