#include <stack>
#include "..\C++_libraries\consInteraction.cpp"
#include "..\C++_libraries\map.cpp"
#include "..\C++_libraries\player.cpp"
#include "..\C++_libraries\game.cpp"
#include "..\C++_libraries\door.cpp"
#include "..\C++_libraries\enemy.cpp"
using namespace std;

int main() {
stack<Map> expr_map;
stack<Player> expr_plr;
stack<Game> expr_game;
stack<Door> expr_door;
stack<Enemy> expr_enemy;
Map x2;
Map x5;
Map x9;
Player x0;
Player x1;
Game x14;
Door x3;
Door x4;
Door x8;
Door x13;
Enemy x6;
Enemy x7;
Enemy x10;
Enemy x11;
Enemy x12;

{Player p = Player(0, 0, 'P', 'W', 'D', 'S', 'A');
expr_plr.push(p);}
/*Assign Player*/
x0 = expr_plr.top(); expr_plr.pop();
{Player p = Player(5, 5, 'Q', 'I', 'L', 'K', 'J');
expr_plr.push(p);}
/*Assign Player*/
x1 = expr_plr.top(); expr_plr.pop();
{Map m = Map(10, 10, '.', '*');
expr_map.push(m);}
/*Assign Map*/
x2 = expr_map.top(); expr_map.pop();
{Door d = Door(9, 1, '#');
expr_door.push(d);}
/*Assign Door*/
x3 = expr_door.top(); expr_door.pop();
{Door d = Door(2, 6, '#');
expr_door.push(d);}
/*Assign Door*/
x4 = expr_door.top(); expr_door.pop();
/*Push map id*/
expr_map.push(x2);
/*Push door id*/
expr_door.push(x3);
{/*Get Map*/
 Map left = expr_map.top(); expr_map.pop();
/*Get Door*/
 Door right = expr_door.top(); expr_door.pop();
/*Add Door to Map*/
 left.addDoor(right);
/*Push Door onto stack*/
 expr_map.push(left);
}/*Assign Map*/
x2 = expr_map.top(); expr_map.pop();
/*Push map id*/
expr_map.push(x2);
/*Push door id*/
expr_door.push(x4);
{/*Get Map*/
 Map left = expr_map.top(); expr_map.pop();
/*Get Door*/
 Door right = expr_door.top(); expr_door.pop();
/*Add Door to Map*/
 left.addDoor(right);
/*Push Door onto stack*/
 expr_map.push(left);
}/*Assign Map*/
x2 = expr_map.top(); expr_map.pop();
{Map m = Map(20, 20, '-', '|');
expr_map.push(m);}
/*Assign Map*/
x5 = expr_map.top(); expr_map.pop();
{Enemy e = Enemy(13, 14, 'E', 20);
expr_enemy.push(e);}
/*Assign Enemy*/
x6 = expr_enemy.top(); expr_enemy.pop();
{Enemy e = Enemy(18, 19, 'A', 20);
expr_enemy.push(e);}
/*Assign Enemy*/
x7 = expr_enemy.top(); expr_enemy.pop();
{Door d = Door(17, 17, '#');
expr_door.push(d);}
/*Assign Door*/
x8 = expr_door.top(); expr_door.pop();
/*Push map id*/
expr_map.push(x5);
/*Push enemy id*/
expr_enemy.push(x6);
{/*Get Map*/
 Map left = expr_map.top(); expr_map.pop();
/*Get Enemy*/
 Enemy right = expr_enemy.top(); expr_enemy.pop();
/*Add Enemy to Map*/
 left.addEnemy(right);
/*Push Enemy onto stack*/
 expr_map.push(left);
}/*Assign Map*/
x5 = expr_map.top(); expr_map.pop();
/*Push map id*/
expr_map.push(x5);
/*Push enemy id*/
expr_enemy.push(x7);
{/*Get Map*/
 Map left = expr_map.top(); expr_map.pop();
/*Get Enemy*/
 Enemy right = expr_enemy.top(); expr_enemy.pop();
/*Add Enemy to Map*/
 left.addEnemy(right);
/*Push Enemy onto stack*/
 expr_map.push(left);
}/*Assign Map*/
x5 = expr_map.top(); expr_map.pop();
/*Push map id*/
expr_map.push(x5);
/*Push door id*/
expr_door.push(x8);
{/*Get Map*/
 Map left = expr_map.top(); expr_map.pop();
/*Get Door*/
 Door right = expr_door.top(); expr_door.pop();
/*Add Door to Map*/
 left.addDoor(right);
/*Push Door onto stack*/
 expr_map.push(left);
}/*Assign Map*/
x5 = expr_map.top(); expr_map.pop();
{Map m = Map(18, 18, '^', '+');
expr_map.push(m);}
/*Assign Map*/
x9 = expr_map.top(); expr_map.pop();
{Enemy e = Enemy(1, 1, 'B', 20);
expr_enemy.push(e);}
/*Assign Enemy*/
x10 = expr_enemy.top(); expr_enemy.pop();
{Enemy e = Enemy(1, 9, 'C', 20);
expr_enemy.push(e);}
/*Assign Enemy*/
x11 = expr_enemy.top(); expr_enemy.pop();
{Enemy e = Enemy(9, 1, 'D', 20);
expr_enemy.push(e);}
/*Assign Enemy*/
x12 = expr_enemy.top(); expr_enemy.pop();
{Door d = Door(5, 5, '#');
expr_door.push(d);}
/*Assign Door*/
x13 = expr_door.top(); expr_door.pop();
/*Push map id*/
expr_map.push(x9);
/*Push enemy id*/
expr_enemy.push(x10);
{/*Get Map*/
 Map left = expr_map.top(); expr_map.pop();
/*Get Enemy*/
 Enemy right = expr_enemy.top(); expr_enemy.pop();
/*Add Enemy to Map*/
 left.addEnemy(right);
/*Push Enemy onto stack*/
 expr_map.push(left);
}/*Assign Map*/
x9 = expr_map.top(); expr_map.pop();
/*Push map id*/
expr_map.push(x9);
/*Push enemy id*/
expr_enemy.push(x11);
{/*Get Map*/
 Map left = expr_map.top(); expr_map.pop();
/*Get Enemy*/
 Enemy right = expr_enemy.top(); expr_enemy.pop();
/*Add Enemy to Map*/
 left.addEnemy(right);
/*Push Enemy onto stack*/
 expr_map.push(left);
}/*Assign Map*/
x9 = expr_map.top(); expr_map.pop();
/*Push map id*/
expr_map.push(x9);
/*Push enemy id*/
expr_enemy.push(x12);
{/*Get Map*/
 Map left = expr_map.top(); expr_map.pop();
/*Get Enemy*/
 Enemy right = expr_enemy.top(); expr_enemy.pop();
/*Add Enemy to Map*/
 left.addEnemy(right);
/*Push Enemy onto stack*/
 expr_map.push(left);
}/*Assign Map*/
x9 = expr_map.top(); expr_map.pop();
/*Push map id*/
expr_map.push(x9);
/*Push door id*/
expr_door.push(x13);
{/*Get Map*/
 Map left = expr_map.top(); expr_map.pop();
/*Get Door*/
 Door right = expr_door.top(); expr_door.pop();
/*Add Door to Map*/
 left.addDoor(right);
/*Push Door onto stack*/
 expr_map.push(left);
}/*Assign Map*/
x9 = expr_map.top(); expr_map.pop();
{Game g = Game(30);
expr_game.push(g);}
/*Assign Game*/
x14 = expr_game.top(); expr_game.pop();
/*Push game id*/
expr_game.push(x14);
/*Push map id*/
expr_map.push(x2);
{/*Get Game*/
 Game left = expr_game.top(); expr_game.pop();
/*Get Map*/
 Map right = expr_map.top(); expr_map.pop();
/*Add Map to Game*/
 left.addMap(right);
/*Push Map onto stack*/
 expr_game.push(left);
}/*Assign Game*/
x14 = expr_game.top(); expr_game.pop();
/*Push game id*/
expr_game.push(x14);
/*Push map id*/
expr_map.push(x5);
{/*Get Game*/
 Game left = expr_game.top(); expr_game.pop();
/*Get Map*/
 Map right = expr_map.top(); expr_map.pop();
/*Add Map to Game*/
 left.addMap(right);
/*Push Map onto stack*/
 expr_game.push(left);
}/*Assign Game*/
x14 = expr_game.top(); expr_game.pop();
/*Push game id*/
expr_game.push(x14);
/*Push map id*/
expr_map.push(x9);
{/*Get Game*/
 Game left = expr_game.top(); expr_game.pop();
/*Get Map*/
 Map right = expr_map.top(); expr_map.pop();
/*Add Map to Game*/
 left.addMap(right);
/*Push Map onto stack*/
 expr_game.push(left);
}/*Assign Game*/
x14 = expr_game.top(); expr_game.pop();
/*Push game id*/
expr_game.push(x14);
/*Push player id*/
expr_plr.push(x0);
{/*Get Game*/
 Game left = expr_game.top(); expr_game.pop();
/*Get Player*/
 Player right = expr_plr.top(); expr_plr.pop();
/*Add Player to Game*/
 left.addPlayer(right);
/*Push Player onto stack*/
 expr_game.push(left);
}/*Assign Game*/
x14 = expr_game.top(); expr_game.pop();
/*Push game id*/
expr_game.push(x14);
/*Push player id*/
expr_plr.push(x1);
{/*Get Game*/
 Game left = expr_game.top(); expr_game.pop();
/*Get Player*/
 Player right = expr_plr.top(); expr_plr.pop();
/*Add Player to Game*/
 left.addPlayer(right);
/*Push Player onto stack*/
 expr_game.push(left);
}/*Assign Game*/
x14 = expr_game.top(); expr_game.pop();
/*Push game id*/
expr_game.push(x14);
{/*Get Game*/
 Game left = expr_game.top(); expr_game.pop();
/*Run Game*/
 left.gameLoop();
}}
