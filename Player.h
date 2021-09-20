#ifndef Player_H
#define Player_H
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
class Player
{
public:
	Player();
	int ships;
	int choiceX, choiceY;//players have the access to choose which area to declare
	char Pgraph[10][10];//both players have their own individual graph to place their battle 
	char Ograph[10][10];//graph of previous declared attacks
	void LoseShip() { ships = ships - 1; }//lose a ship
	bool Lose();//returns game false if player loses
	void Clear();//clear the board
	void setShips();//ships are set for the indiviual.
	void setPosition(char);//set the ships on depending on the the randomizer
	void Show_Main();//Players are allowed to show their board
	void Show_Radar();//player are allowed to show their radar
	void Erase_Ship(char);
};
class AI :public Player
{
private:
	int edu_guess = 4;
public:
	void C_Attack(Player&);
};
#endif