#include <iostream>
#include <vector>

using namespace std;

// hp, attack, and defense
// HP less than or equal to 0, the character will die

// damage equals the attack minus the enemy’s defense
// damage less than 0, the enemy will not be harmed

// player’s hp will not recover 
// fight the monsters one by one

class Character
{
public:
    Character(int hp, int attack, int defense);
    void Attacked(Character &enemy);
    bool Dead();
    int hp();
    int attack();
    int defense();
private:
    int _hp;
    int _attack;
    int _defense;
};

Character::Character(int hp, int attack, int defense)
: _hp(hp), _attack(attack), _defense(defense)
{
    ;
}

void Character::Attacked(Character &enemy)
{
    int demage = enemy.attack() - _defense;
    if(demage > 0)
        _hp -= demage;
}

bool Character::Dead()
{
    if(_hp <= 0)
        return 1;
    return 0;
}

void ShowStatus(Character &hero, Character &enemy)
{
    cout << "Player:" << hero.hp() << " Enemy:" << enemy.hp() << endl;
}

inline int Character::hp() { return _hp;}
inline int Character::attack() { return _attack;}
inline int Character::defense() { return _defense;}

int main(void)
{
    int hp, attack, defense;
    vector<Character> enemys;

    cin >> hp >> attack >> defense;
    Character hero(hp, attack, defense);

    while(cin >> hp >> attack >> defense)
    {
        enemys.push_back({hp, attack, defense});
    }

    for(auto each: enemys)
    {
        while(true)
        {
            each.Attacked(hero);
            ShowStatus(hero, each);

            if(each.Dead()) break;

            hero.Attacked(each);
            ShowStatus(hero, each);

            if(hero.Dead()) break;
        }

        if(hero.Dead())
        {
            cout << "Player Dead" << endl;
            break;
        }
        else
        {
            cout << "Player Win" << endl;
        }
    }
}