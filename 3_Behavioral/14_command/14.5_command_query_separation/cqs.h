#pragma once

enum class CreatureAbility { strength, agility };

struct CreatureCommand {
    enum Action { set, increaseBy, decreaseBy } action;
    CreatureAbility ability;
    int amount;
};

struct CreatureQuery {
    CreatureAbility ability;
};

class Creature {
    int strength, agility;

public:
    Creature(int strength, int agility)
            : strength{strength}, agility{agility} {}

    // no getters and setters
    void process_command(const CreatureCommand &cc);
    int process_query(const CreatureQuery& q) const;
    void set_strength(int value);
    void set_agility(int value);
    int get_strength() const;
    int get_agility() const;
};

void Creature::process_command(const CreatureCommand &cc) {
    int *ability;
    switch (cc.ability) {
        case CreatureAbility::strength:
            ability = &strength;
            break;
        case CreatureAbility::agility:
            ability = &agility;
            break;
    }

    switch (cc.action) {
        case CreatureCommand::set:
            *ability = cc.amount;
            break;
        case CreatureCommand::increaseBy:
            *ability += cc.amount;
            break;
        case CreatureCommand::decreaseBy:
            *ability -= cc.amount;
            break;
    }
}

int Creature::process_query(const CreatureQuery &q) const {
    switch (q.ability) {
        case CreatureAbility::strength:	return strength;
        case CreatureAbility::agility:	return agility;
    }
    return 0;
}

// Make getter/setter 
void Creature::set_strength(int value) {
    process_command(CreatureCommand{
            CreatureCommand::set, CreatureAbility::strength, value});
}

void Creature::set_agility(int value) {
    process_command(CreatureCommand{
            CreatureCommand::set, CreatureAbility::agility, value});
}

int Creature::get_strength() const {
    return process_query(CreatureQuery{CreatureAbility::strength});
}

int Creature::get_agility() const {
    return process_query(CreatureQuery{CreatureAbility::agility});
}