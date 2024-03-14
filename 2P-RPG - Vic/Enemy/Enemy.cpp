//
// Created by Victor Navarro on 15/02/24.
//

#include "Enemy.h"
#include "../Utils.h"
#include "../Combat/Action.h"
#include <iostream>


using namespace std;
using namespace combat_utils;

Enemy::Enemy(string _name, int _health, int _max_health , int _attack, int _defense, int _original_defense, int _speed, int _experience, bool _isPlayer) : Character(_name, _health, _max_health, _attack, _defense, _original_defense, _speed, _isPlayer) {
    experience = _experience;
}

void Enemy::doAttack(Character *target) {
    target->takeDamage(getRolledAttack(attack));
}

void Enemy::takeDamage(int damage) {
    int trueDamage = damage - defense;
    health-= trueDamage;

    cout << name << " took " << trueDamage << " damage!" << endl;
    if(health <= 0) {
        cout << name << " has been defeated!" << endl;
    }
}

int Enemy::getExperience() {
    return experience;
}

Character* Enemy::selectTarget(vector<Player*> possibleTargets) {
    //target with less health
    int lessHealth = 9999999;
    Character* target = nullptr;
    for(auto character : possibleTargets) {
        if(character->getHealth() < lessHealth) {
            lessHealth = character->getHealth();
            target = character;
        }
    }
    return target;
}

Action Enemy::takeAction(vector<Player*> partyMembers) {
    const int Speed_defense = 999999999;
    Action currentAction;
    currentAction.speed = getSpeed();

    Character *target = selectTarget(partyMembers);
    currentAction.target = target;
    currentAction.action = [this, target]() {
        doAttack(target);
        resetDefense();
    };

 if(getHealth() <= getMaxHealth() * 0.8 && rand() %100 < 70){
     currentAction.target = this;
      currentAction.action = [this](){
        cout << "----Enemigo defensa----" << endl;
         boostDefense();
       };
     currentAction.speed = Speed_defense;
     }

    return currentAction;
}