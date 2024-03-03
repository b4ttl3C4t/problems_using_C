#include <iostream>
#include <vector>

using namespace std;

class Character
{
public:
    int hp;
    int atk;
    int def;
public:
    Character()
    : hp(0), atk(0), def(0)
    {
        ;
    }
    bool hp_less_than_zero()
    {
        if(hp <= 0) return 1;
        return 0;
    }
    void attack(Character &enemy)
    {
        int damage = (*this).atk - enemy.def;
        if(damage > 0) enemy.hp -= damage;
    }
};

int main(void)
{
    Character hero;
    vector<Character> mosters;

    cin >> hero.hp >> hero.atk >> hero.def;

    Character moster;
    while(cin >> moster.hp >> moster.atk >> moster.def)
    {
        mosters.push_back(moster);
    }

    for(auto &moster: mosters)
    {
        while(!hero.hp_less_than_zero() && !moster.hp_less_than_zero())
        {
            hero.attack(moster);
            cout << "Player:" << hero.hp 
                 << " Enemy:" << moster.hp << endl;
            
            if(moster.hp_less_than_zero())
            {
                break;
            }

            moster.attack(hero);
            cout << "Player:" << hero.hp 
                 << " Enemy:" << moster.hp << endl;
        }

        if(hero.hp_less_than_zero())
        {
            cout << "Player Dead" << endl;
            return 0;
        }
        else
        {
            cout << "Player Win" << endl;;
        }
    }
}