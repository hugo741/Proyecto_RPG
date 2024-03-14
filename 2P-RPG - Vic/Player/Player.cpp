//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(string _name, int _health, int _max_health, int _attack, int _defense, int _original_defense, int _speed, bool _isPlayer) : Character(_name, _health, _max_health, _attack, _defense, _original_defense, _speed, _isPlayer) {
    level = 1;
    experience = 0;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;
    health-= trueDamage;
    cout << name << " took " << trueDamage << " damage!" << endl;
    if(health <= 0) {
        cout << name << " has been defeated!" << endl;
    }

}

void Player::levelUp() {
    level++;
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 100-experience;
    }
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Select a target: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}
Action Player::takeAction(vector<Enemy*> enemies) {
    int aux_player = 0;
    int option = 0;
    int action = 0;
    const int SpeedLight = 13433211;
    cout << "Select an action: " << endl << "1. Attack" << endl;
    cout << "2. Defend" << endl;

    //TODO: Validate input
    cin >> action;
    Action currentAction;
    Character *target = nullptr;

    switch (action) {
        case 1:
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target]() {
                doAttack(target);
            };
            currentAction.speed = getSpeed();
            break;
        case 2:
            currentAction.target = this;
            currentAction.action = [this](){
                cout << "----Defensa----" << endl;
                boostDefense();
            };
            aux_player = 1;
            currentAction.speed = SpeedLight;
            break;
        default:
            cout << "Invalid action" << endl;
            break;
    }

    return currentAction;
}