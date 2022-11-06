#include <iostream>

struct Creature
{
    std::string name;
    int attack, defense;

    Creature(const std::string& name, const int attack, const int defense)
    : name(name), attack(attack), defense(defense)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const Creature& obj)
    {
        return os
                << "name: " << obj.name
                << " attack: " << obj.attack
                << " defense: " << obj.defense;
    }
};


class CreatureModifier
{
    // 현재 작업뒤에 뒤따르는 또다른 CreatureModifier를 가르킴
    CreatureModifier* next{nullptr};

protected:
    Creature& creature; //참조 대신 포인터나 shared_ptr 사용 가능

public:
    explicit CreatureModifier(Creature& creature)
    :creature(creature){}

    void add(CreatureModifier* cm)
    {
        if (next) next->add(cm);
        else next = cm;
    }

    // 사슬의 다음항목을 처리
    virtual void handle()
    {
        if (next) next->handle();
    }
};

class DoubleAttackModifier : public CreatureModifier
{
public:
    explicit DoubleAttackModifier(Creature& creature)
    : CreatureModifier(creature) {}

    void handle() override
    {
        creature.attack *= 2;
        CreatureModifier::handle();
    }
};

class IncreaseDefenseModifier : public CreatureModifier
{
public:
    explicit IncreaseDefenseModifier(Creature& creature)
            : CreatureModifier(creature) {}

    void handle() override
    {
        if(creature.attack <= 2)
            creature.defense += 1;
        CreatureModifier::handle();
    }
};

int main()
{
    Creature goblin{"Goblin", 1, 1};
    CreatureModifier root{goblin};
    DoubleAttackModifier r1{goblin};
    DoubleAttackModifier r1_2{goblin};

    IncreaseDefenseModifier r2{goblin};

    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);
    root.handle();

    std::cout << goblin << std::endl;
}