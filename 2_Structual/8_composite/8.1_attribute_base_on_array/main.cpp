#include <iostream>
#include <array>      // std::array
#include <numeric>    // std::accumulate
#include <algorithm>  // max_element


// 문제가 있는 방법.
class Creature
{
    int strength, agility, intelligence;

public:
    int get_strength() const
    {
        return strength;
    }

    void set_strength(int strength)
    {
        Creature::strength = strength;
    }

    int get_agility() const
    {
        return agility;
    }

    void set_agility(int agility)
    {
        Creature::agility = agility;
    }

    int get_intelligence() const
    {
        return intelligence;
    }

    void set_intelligence(int intelligence)
    {
        Creature::intelligence = intelligence;
    }


    // 예를 들어 속성들의 통계 내고자 한다면 다음 처럼해야 하지만 몇가지 문제가 존재
    // * 전체 합계를 계산할 때 필드 중 하나를 빠뜨리기 쉬움
    // * 평균을 계산할 때 상수 3.0이 사용됨, 속성의 개수가 바뀔때마다 수정해야하므로
    //  의도하지 않은 종속성을 야기
    // * 최대 값을 구할때 모든 필드 값 쌍마다 std::max를 반복호출 해야함.
    int sum() const
    {
        return strength + agility + intelligence;
    }

    double avg() const
    {
        return sum() / 3.0;
    }

    int max() const
    {
        return std::max(std::max(strength, agility), intelligence);
    }
};


// 개선 방법

class CreatureV2
{
    // count는 enum의 항목 수
    enum Abilities {str, agl, intl, count};
    std::array<int, count> abilities;

public:
    int get_strength() const
    {
        return abilities[str];
    }

    void set_strength(int value){
        abilities[str] = value;
    }

    int get_agility() const
    {
        return abilities[agl];
    }

    void set_agility(int value){
        abilities[agl] = value;
    }

    int get_intelligence() const
    {
        return abilities[str];
    }

    void set_intelligence(int value){
        abilities[intl] = value;
    }

    int sum() const
    {
        return std::accumulate(abilities.begin(), abilities.end(), 0);
    }

    int avg() const
    {
        return sum() / (double) count;
    }

    int max()const
    {
        return *std::max_element(abilities.begin(), abilities.end());
    }
};

int main()
{
    CreatureV2 zombie;

    zombie.set_strength(10);
    zombie.set_agility(1);
    zombie.set_intelligence(1);

    std::cout << "Zombie Max: " << zombie.max() << std::endl;
    std::cout << "Zombie Avg: " << zombie.avg() << std::endl;
}



