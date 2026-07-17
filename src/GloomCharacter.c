#include "Character.h"
#include "Display.h"
#include "../lib/SDL2/include/SDL2/SDL.h"

#define CLASS_AMOUNT 5

Player createPlayer(int selected){
    Player player;
    switch (selected){
        case 0:
            //Warrior Class
            player.character = createCharacter('W', 100, 3, 1, 1);
            player.attacks = createAttack("Slash", 2, "Stab", 3, "Punch", 1, "Bash", 4); 
            break;
        case 1:
            //Mage Class
            player.character = createCharacter('M', 85, 7, 3, 2);
            player.attacks = createAttack("Fireball", 3, "Magic Bolt", 2, "Spark", 2, "Blizzard", 2);
            break;
        case 2:
            //Hunter Class
            player.character = createCharacter('H', 85, 3, 3, 5);
            player.attacks = createAttack("Crit Shot", 4, "Shoot", 2, "Smack", 1, "Punch", 1);
            break;  
        case 3:
            //Theif Class
            player.character = createCharacter('T', 85, 3, 5, 2);
            player.attacks = createAttack("Sneak Attack", 4, "Stab", 3, "Pick Pocket", 0, "Slash", 2);
            break;
        case 4:
            //Goblin Class
            player.character = createCharacter('G', 10, 1, 1, -1);
            player.attacks = createAttack("Slash", 1, "Pick Pocket", 0, "Punch", 100, "Heal", -100); 
            break;
        }
    return player;
}

Player movePlayer(const Uint8 *key, Player player, double pSpeed, double rotSpeed){
    double x = 0.0;
    double y = 0.0;
    //Rotation Theta
    if(key[SDL_SCANCODE_LEFT]){player.angle += rotSpeed;}
    if(key[SDL_SCANCODE_RIGHT]){player.angle -= rotSpeed;}
    //Movement x,y
    if(key[SDL_SCANCODE_W]){
        x += cos(player.angle);
        y += sin(player.angle);
    }
    if(key[SDL_SCANCODE_S]){
        x -= cos(player.angle);
        y -= sin(player.angle);
    }
    if(key[SDL_SCANCODE_A]){
        x -= sin(player.angle);
        y += cos(player.angle);
    }
    if(key[SDL_SCANCODE_D]){
        x += sin(player.angle);
        y -= cos(player.angle);
    }
    double length = sqrt(x * x + y * y);
    if(length > 0){
        x = x / length * pSpeed;
        y = y / length * pSpeed;
    }
    if(worldMap[(int)floor(player.y)][(int)floor(player.x + x)] == 0){player.x += x;}
    if(worldMap[(int)floor(player.y + y)][(int)floor(player.x)] == 0){player.y += y;}
    return player;
}

Character createCharacter(char class, int health, int damage, int speed, int luck){
    Character c;
    c.Class = class;
    c.Health = health;
    c.Damage = damage;
    c.Speed = speed;
    c.Luck = luck;
    return c;
}

Attack createAttack(char* sAttack1, int nAttack1, char* sAttack2, int nAttack2, char* sAttack3, int nAttack3, char* sAttack4, int nAttack4) {
    Attack a;
    a.sAttack1 = sAttack1;
    a.nAttack1 = nAttack1;
    a.sAttack2 = sAttack2;
    a.nAttack2 = nAttack2;
    a.sAttack3 = sAttack3;
    a.nAttack3 = nAttack3;
    a.sAttack4 = sAttack4;
    a.nAttack4 = nAttack4;
    return a;
}

void displayCMenu(unsigned int nSelected) {

}