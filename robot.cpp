#include <bits/stdc++.h>
#include <conio.h>
#include "robot.hpp"

using namespace std;

int button;
int turn;
bool attacking = false;
bool attacked = false;
bool kill = false;

Robot::Robot() {
    this->health = 100;
    this->power = 5;
    this->range = 5;
    this->position[0] = 0;
    this->position[1] = 0;
}

MechaKurama::MechaKurama() {
    this->health = 100;
    this->power = 10;
    this->range = 3;
    this->bunshinNumber = 1;
}

bool Robot::isAlive() {
    return health > 0;
}

bool MechaKurama::isAlive() {
    return health > 0;
}

Robot r;
MechaKurama k;

void gameOver() {
	cout << endl;
	cout << "--------------------------" << endl;
	cout << "-------- Game Over -------" << endl;
	cout << "--------------------------" << endl << endl;
	cout << "Press any key to go back to exit";
	button = getch();
    exit(0);
}

void randomMechaKuramaPosition(int size) {
    srand(time(NULL));
    k.position[0] = rand() % size;
    k.position[1] = rand() % size;
}

void plot(int size, int rPosition[2], int kPosition[2]) {
    int i; int j;
    float distance = sqrt(pow(rPosition[0] - kPosition[0], 2) + pow(rPosition[1] - kPosition[1], 2));

    if(attacked) {
        if(r.isAlive()) {
            r.health -= k.power;
        }
    }

    system("cls");
    cout << "Robot statuses: " << r.health;
    if(attacked) { cout << "(-" << k.power << ")"; }
    cout << " HP; " << r.power << " damage; " << r.range << " attack range" << endl;
    cout << "Robot's coordinate (" << rPosition[0] << "," << rPosition[1] << ")" << endl << endl;
    cout << "Mecha Kurama (" << k.bunshinNumber << ") statuses: " << k.health;
    if(attacking && kill == false) { cout << "(-" << r.power << ")"; }
    cout << " HP; " << k.power << " damage; " << k.range << " attack range" << endl;
    cout << "Mecha Kurama (" << k.bunshinNumber << ")'s coordinate (" << kPosition[0] << "," << kPosition[1] << ")" << endl << endl;
    cout << "The distance between Robot and Mecha Kurama is " << distance << " unit" << endl;

    for(i = size-1; i >= 0; i--) {
        for(j = 0; j < size; j++) {
            if(i == rPosition[1] && j == rPosition[0]) {
                cout << "  R";
            } else if(i == kPosition[1] && j == kPosition[0]) {
                cout << "  K";
            } else {
                cout << "  *";
            }
        }
        cout << endl;
    }
    cout << endl;

    if(distance > r.range && button == 32) {       //Space
        cout << "Too far away, get closer!" << endl;
    }

    if(k.isAlive()) {
        if(kill == false) {
            if(distance <= k.range) {
                if(distance <= r.range) {
                    cout << "You and Mecha Kurama can attack each other" << endl;
                } else {
                    cout << "You are standing too close to the Mecha Kurama" << endl;
                }
            } else if(distance <= r.range) {
                cout << "You can attack Mecha Kurama from here" << endl;
            }
            if(attacking) {
                cout << "You are dealing " << r.power << " damage to Mecha Kurama" << endl;
                attacking = false;
            }
            if(attacked) {
                cout << "You've been hit " << k.power << " damage by Mecha Kurama" << endl;
                attacked = false;
            }
        }
    } else {
        if(attacking) {
            kill = true;
            turn = 0;
            k.health = 100;
            k.bunshinNumber += 1;
            randomMechaKuramaPosition(size);
            plot(size, r.position, k.position);
            cout << "You killed 1 Mecha Kurama" << endl;
            cout << "Another bunshin has come to revenge" << endl;
            kill = false;
            attacking = false;
        }
    }

    if(r.isAlive() == false) {
        if(k.bunshinNumber > 1) {
            cout << endl << "Successfully destroyed " << (k.bunshinNumber - 1) << " Mecha Kurama" << endl;
        } else {
            cout << endl << "None of Mecha Kurama has been destroyed. Play better next time!" << endl;
        }
        gameOver();
    }

    turn += 1;
}

void play() {
    int size;

    while(true) {
        cout << "Enter the size of battlefield [8 .. 16]: "; 
        cin >> size;
        if(8 <= size && size <= 16) {
            break;
        }
    }

    randomMechaKuramaPosition(size);

    if(k.position[0] == 0) { k.position[0] = 1; } 
    if(k.position[1] == 0) { k.position[1] = 1; }

    plot(size, r.position, k.position);

    while(r.isAlive()) {
        button = getch();
        float distance = sqrt(pow(r.position[0] - k.position[0], 2) + pow(r.position[1] - k.position[1], 2));

        if(turn > 0) {
            if(distance <= k.range) {
                attacked = true;
            }
        }

        if(button == 119) {         //W
            int w = r.position[1] + 1;
            if(w != size) {
                if(w != k.position[1] || r.position[0] != k.position[0]) {
                    r.position[1] += 1;
                } else { attacked = false; }
            } else { attacked = false; }
        } else if(button == 97) {   //A
            int a = r.position[0] - 1;
            if(a != -1) {
                if(a != k.position[0] || r.position[1] != k.position[1]) {
                    r.position[0] -= 1;
                } else { attacked = false; }
            } else { attacked = false; }
        } else if(button == 115) {  //S
            int s = r.position[1] - 1;
            if(s != -1) {
                if(s != k.position[1] || r.position[0] != k.position[0]) {
                    r.position[1] -= 1;
                } else { attacked = false; }
            } else { attacked = false; }
        } else if(button == 100) {  //D
            int d = r.position[0] + 1;
            if(d != size) {
                if(d != k.position[0] || r.position[1] != k.position[1]) {
                    r.position[0] += 1;
                } else { attacked = false; }
            } else { attacked = false; }
        } else if(button == 32) {   //Space
            if(distance <= r.range) {
                k.health -= r.power;
                attacking = true;
            }
        } else if(button == 27) {   //ESC
            exit(0);
        }

        system("cls");
        plot(size, r.position, k.position);
    }
}

void instructions() {
	cout << "Instructions" << endl;
	cout << "----------------" << endl;
	cout << "Avoid Mecha Kurama's attack by moving" << endl << endl;
	cout << "Press 'A' to move left" << endl;
	cout << "Press 'D' to move right" << endl;
	cout << "Press 'W' to move up" << endl;
	cout << "Press 'S' to move down" << endl;
    cout << "Press 'Space' to attack" << endl;
	cout << "Press 'ESC' to exit" << endl << endl;
	cout << "Press any key to go back to main menu";
	button = getch();
}

int main() {
    do {
        system("cls");
        cout << "--------------------------  " << endl;
        cout << "|        Robot War       |  " << endl;
        cout << "--------------------------  " << endl;
        cout << "1. Start game" << endl;
        cout << "2. Instruction" << endl;
        cout << "Use ESC to quit the game" << endl << endl;
        cout << "Select option: ";
        button = getch();

        if(button == 49) {              //1
            system("cls");
            play();
        } else if(button == 50) {       //2
            system("cls");
            instructions();
        } else if(button == 27) {       //ESC
            exit(0);
        }
    } while(1);
    
    system("pause");
    return 0;
}
