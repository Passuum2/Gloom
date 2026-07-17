#ifndef CHAR_H
#define CHAR_H
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../lib/SDL2/include/SDL2/SDL.h"

typedef struct{
    char* Name;
    char Class;
    int Health;
    int Damage;
    int Speed;
    int Luck;
} Character;

typedef struct{
    char* sAttack1; int nAttack1;
    char* sAttack2; int nAttack2;
    char* sAttack3; int nAttack3;
    char* sAttack4; int nAttack4;
} Attack;

typedef struct{
    Character character;
    Attack attacks;
    double x, y;
    double angle;
} Player;

Player createPlayer(int selected);
Player movePlayer(const Uint8 *key, Player player, double pSpeed, double rotSpeed);
Character createCharacter(char class, int health, int damage, int speed, int luck);
Attack createAttack(char* sAttack1, int nAttack1, char* sAttack2, int nAttack2, char* sAttack3, int nAttack3, char* sAttack4, int nAttack4);
#endif