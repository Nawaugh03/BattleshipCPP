//Nicholas Waugh's Battleship game ver 1.0.1.
#include "Player.h"
#include <Windows.h>
using namespace std;

void instruction();
void GameStart();
void Attack(Player&, AI&);
Player::Player()
{
	Clear();
	setShips();
	ships = 1;
}


void Player::Clear()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Pgraph[i][j] = 'O';
			Ograph[i][j] = 'O';
		}
	}

}

void Player::Show_Main()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)	
			cout << "|" << Pgraph[i][j] << "|";
		cout << endl;
	}
	system("pause");
	system("cls");
}

void Player::Show_Radar()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << "|" << Ograph[i][j] << "|";
		cout << endl;
	}
	system("pause");
	system("cls");
}

void Player::setShips()
{
	bool shipset = false;
	char ships ='D';
	do
	{

		switch (ships)
		{
		case 'D':
			setPosition(ships);
			ships = 'c';
			break;
		case 'c':
			setPosition(ships);
			ships = 'S';
			break;
		case 'S':
			setPosition(ships);
			ships = 'B';
			break;
		case 'B':
			setPosition(ships);
			ships = 'C';
			break;
		case 'C':
			setPosition(ships);
			shipset = true;
			break;
		}

	} while (shipset == false);
}

void Player::setPosition(char ship)
{
	int PosX = rand() % 10;
	int PosY = rand() % 10;
	int tries;
	int retry=0;
	switch (ship)
	{
	case 'D':
		retry = 2;
		break;
	case 'c':
		retry = 3;
		break;
	case 'S':
		retry = 3;
		break;
	case 'B':
		retry = 4;
		break;
	case 'C':
		retry = 5;
		break;
	}
	tries = retry;
	Pgraph[PosX][PosY] = ship;
	int posA = 0;
	int posB = 0;
	
	do
	{
		srand(time(NULL));

		int HV = rand() % 2;//Horizonal=0 or Vertical=1?
		int LRUD = rand() % 2;//Left or down=0? / Right or Up=1?


		if (HV == 0 && LRUD == 0) { posA = -1; }//horizontal left
		else if (HV == 0 && LRUD == 1) { posA = 1; }//horizontal right
		else if (HV == 1 && LRUD == 0) { posB = 1; }//vertical down
		else if (HV == 1 && LRUD == 1) { posB = -1; }//vertical up

		if (HV == 0&&(PosX<10||PosX>=0))
		{
			PosX += posA;
			if (((PosX>=10||PosX<0)||(PosY>=10||PosY<0))||(Pgraph[PosX][PosY]!='O'))
			{
				Erase_Ship(ship);
				PosX = rand() % 10;
				PosY = rand() % 10;
				Pgraph[PosX][PosY] = ship;
				tries = retry;
			}
			else
			{
				Pgraph[PosX][PosY] = ship;
				tries--;
			}
		}
		else if (HV == 1 && (PosY < 10 || PosY>=0))
		{
			PosY += posB;
			if (((PosX >= 10 || PosX < 0) || (PosY >= 10 || PosY < 0)) || (Pgraph[PosX][PosY] != 'O'))
			{
				Erase_Ship(ship);
				PosX = rand() % 10;
				PosY = rand() % 10;
				Pgraph[PosX][PosY] = ship;
				tries = retry;
			}
			else
			{
				Pgraph[PosX][PosY] = ship;
				tries--;
			}
		}
		
	
	} while (tries!=0);

}


void Player::Erase_Ship(char ship)
{
	bool All_Clear = false;
	do
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (Pgraph[i][j] == ship)
					Pgraph[i][j] = 'O';
				else
					All_Clear = true;
			}
		}


	} while (All_Clear == false);
}

bool Player::Lose()
{
	if (ships == 0)
		return true;
	else
		return false;
}

void AI::C_Attack(Player& p)
{
	bool confirm = false;
	static int real_x;
	static int real_y;
	static int direction=0;
	int x=0;
	int y=0;

	do
	{
		if (p.Lose())
			break;
		else if (real_x == NULL && real_y == NULL)
		{
			srand(time(NULL));
				x = rand() % 10;
				y = rand() % 10;
		}

		if (p.Pgraph[x][y] != 'O'&&Ograph[x][y]=='O')
		{
			cout << "You got hit"<<endl;
			p.Pgraph[x][y] = 'X';
			Ograph[x][y] = 'X';
			real_x = x=0;
			real_y = y=0;
			confirm = true;
		}
		else if (p.Pgraph[x][y] != 'O' && Ograph[x][y] != 'O')
		{
			system("cls");
			cout << "Fred is thinking..." << endl;
		}
		else
		{
			system("cls");
			cout << "Fred missed " << endl;
			Ograph[x][y] = '/';
			real_x = NULL;
			real_y = NULL;
			confirm = true;
		}
		if (real_x != NULL && real_y != NULL)
		{
			switch (direction)
			{
			case 1: //left
				x -= 1;
				if (x>1&&(p.Pgraph[x][y] != 'O' && Ograph[x][y] == 'O'))
				{
					cout << "You got hit" << endl;
					p.Pgraph[x][y] = 'X';
					Ograph[x][y] = 'X';
					real_x = x;
					real_y = y;
					confirm = true;
					break;
				}
				else if (x>1&&(p.Pgraph[x][y] != 'O' && Ograph[x][y] != 'O'))
				{
					system("cls");
					cout << "Fred is thinking..." << endl;
				}
				else if (x < 1)
				{

					cout << "Fred is making its move" << endl;
					x = real_x;
					direction++;
				}
				else
				{
					system("cls");
					cout << "Fred Missed" << endl;
				}
				
			case 2: //up-
				y -= 1;
				if (y>1&&(p.Pgraph[x][y] != 'O' && Ograph[x][y] == 'O'))
				{
					cout << "You got hit" << endl;
					p.Pgraph[x][y] = 'X';
					Ograph[x][y] = 'X';
					real_x = x;
					real_y = y;
					confirm = true;
					break;
				}
				else if (y>1&&p.Pgraph[x][y] != 'O' && Ograph[x][y] != 'O')
				{
					system("cls");
					cout << "Fred is thinking..." << endl;
				}
				else if (y < 1)
				{
					y = real_y;
					direction++;
				}
				else
				{
					system("cls");
					cout << "Fred Missed" << endl;
					confirm = true;
				}
			case 3://right
				x += 1;
				if (x<=9&&(p.Pgraph[x][y] != 'O' && Ograph[x][y] == 'O'))
				{
					cout << "You got hit" << endl;
					p.Pgraph[x][y] = 'X';
					Ograph[x][y] = 'X';
					real_x = x;
					real_y = y;
					confirm = true;
					break;
				}
				else if (x<=9&&(p.Pgraph[x][y] != 'O' && Ograph[x][y] != 'O'))
				{
					system("cls");
					cout << "Fred is thinking..." << endl;
				}
				else if (x > 9)
				{
					x = real_x;
					direction++;
				}
				else
				{
					system("cls");
					cout << "Fred Missed" << endl;
					confirm = true;
				}
			case 4: //down+
				y += 1;
				if (y<=9&&(p.Pgraph[x][y] != 'O' && Ograph[x][y] == 'O'))
				{
					cout << "You got hit" << endl;
					p.Pgraph[x][y] = 'X';
					Ograph[x][y] = 'X';
					real_x = x;
					real_y = y;
					confirm = true;
					break;
				}
				else if (y<=9&&(p.Pgraph[x][y] != 'O' && Ograph[x][y] != 'O'))
				{
					system("cls");
					cout << "Fred is thinking..." << endl;
				}
				else if (y > 9)
				{
					y = real_x;
					direction++;
				}
				else
				{
					system("cls");
					cout << "Fred Missed" << endl;
					confirm = true;
				}
			default:
				system("cls");
				cout << "Fred is Thinking..."<<endl;
				real_x = NULL;
				real_y = NULL;
				break;
			}
		}
	} while (confirm == false);
}




int main()
{
	int choice;

	cout << "\t\t\t---------------------\t\t" << endl;
	cout << "\t\t\tWelcome to Battleship\t\t" << endl;
	cout << "\t\t\t1.) -->  Play Game " << endl;
	cout << "\t\t\t2.) --> How to play " << endl;
	cout << "\t\t\t3.) -->    Quit " << endl;
	cout << "\t\t\tChoice: ";
	cin >> choice;

	do {
		switch (choice)
		{
		case 1:
			system("cls");
			GameStart();
			cout << "\t\t\t---------------------" << endl;
			cout << "\t\t\tWelcome to Battleship" << endl;
			cout << "\t\t\t1.) -->  Play Game " << endl;
			cout << "\t\t\t2.) --> How to play " << endl;
			cout << "\t\t\t3.) -->    Quit " << endl;
			cout << "\t\t\tChoice: ";
			cin >> choice;
			break;
		case 2:
			system("cls");
			instruction();
			cout << "\t\t\t---------------------\t\t" << endl;
			cout << "\t\t\tWelcome to Battleship\t\t" << endl;
			cout << "\t\t\t1.) -->  Play Game " << endl;
			cout << "\t\t\t2.) --> How to play " << endl;
			cout << "\t\t\t3.) -->    Quit " << endl;
			cout << "\t\t\tChoice: ";
			cin >> choice;
			break;
		case 3:
			system("cls");
			cout << "Have a good day." << endl;
			break;
		default:
			system("cls");
			cout << "\t\t\tInvalid choice choose again." << endl;
			cout << "\t\t\t---------------------" << endl;
			cout << "\t\t\t1.) -->  Play Game " << endl;
			cout << "\t\t\t2.) --> How to play " << endl;
			cout << "\t\t\t3.) -->    Quit " << endl;
			cout << "\t\t\tChoice: ";
			cin >> choice;
			break;
		}
	} while (choice != 3);

	system("pause");
	return 0;
}

void instruction()//explain the game
{
	cout << "Rules are simple. You will be up against Fred the AI." << endl;
	cout << "You will have two graphs, one will keep track of your ships and the other will scan the position of opponent ships." << endl;
	cout << "Both you and Fred's ships are randomly set on your respective fields." << endl;
	cout << "You will have a prompt that will allow you to input the location of the ship" << endl;
	cout << "Both inputs will be numbers between 1-10 for both x and y coordinate in order (X,Y)." << endl;
	cout << "If you input the correct ship coordinate the ship will be 'sunk' else it's a 'miss'" << endl;
	cout << "Win condition--First person who sunk all of the opponent's ships wins." << endl;
	cout << "\t\t\t*Legend*"<<endl;
	cout << "'O' --> Free Space.\n'X' --> ship has been hit.\n'/' --> missed shots." << endl;
	cout << "\t\t\t*Ships*" << endl;
	cout << "'D D' --> Destroyer '2' characters.\n'c c c' --> Cruiser '3' characters.\n'S S S' --> Submarine '3' characters.\n'B B B B' --> BattleShip '4' characters.\n'C C C C C' --> Carrier '5' characters.\n";
	system("pause");
	system("cls");
}
void GameStart()
{
	Player P;
	AI Fred;
	int c;
	for (int t = 5; t >= 1; t--)
	{
		cout << "Game Begins in : " << t;
		Sleep(1000);
		system("cls");
	}
	bool Gameover = false;
	cout << "You are first." << endl;
	do {
		bool turn;
		cout << "Select choice:" << endl;
		cout << "1.) Show my ships\n2.) Show my radar\n3.) Attack\n4.) Surrender\nChoice: ";
		cin >> c;
		do
		{
			turn = false;
			switch (c)
			{
			case 1:
				system("cls");
				P.Show_Main();
				cout << "Select choice:" << endl;
				cout << "1.) Show my ships\n2.) Show my radar\n3.) Attack\n4.) Surrender\nChoice: ";
				cin >> c;
				break;
			case 2:
				system("cls");
				P.Show_Radar();
				cout << "Select choice:" << endl;
				cout << "1.) Show my ships\n2.) Show my radar\n3.) Attack\n4.) Surrender\nChoice: ";
				cin >> c;
				break;
			case 3:
				system("cls");
				Attack(P,Fred);
				turn = true;
				break;
			case 4:
				system("cls");
				char sure;
				cout << "Are you sure you want to surrender(y/n) :" << endl;
				cin >> sure;
				if (tolower(sure)=='y')
				{
					P.ships = 0;
					turn = true;
				}
				break;
			default:
				system("cls");
				cout << "invalid choice try again"<<endl;
				cout << "Select choice:" << endl;
				cout << "1.) Show my ships\n2.) Show my radar\n3.) Attack\n4.) Surrender\nChoice: ";
				cin >> c;
				break;
			}
			
		} while (turn==false);

		Fred.C_Attack(P);
		system("pause");
		if (P.Lose())
		{
			cout << "You lost to fred fair and square." << endl;
			cout << "Better luck next time." << endl;
			Gameover = true;
			system("pause");
		}
		else if (Fred.Lose())
		{
			cout << "You win fair and square" << endl;
			cout << "Fred will try to learn from this game." << endl;
			Gameover = true;
			system("pause");
		}
		system("cls");
	} while (Gameover == false);
	char sure;
	cout << "Do you wish to see both Fred's radar and ships.(y/n): " << endl;
	cin >> sure;
	sure = tolower(sure);
	while (tolower(sure) != 'y'&&tolower(sure)!='n')
	{
		cout << "Invalid answer try again (y/n):" << endl;
		cin >> sure;
		sure = tolower(sure);
	}
	if (tolower(sure) == 'y')
	{
		system("cls");
		cout << "This is both Fred's Radar and Ships:"<<endl;
		cout << "\nFred Ships:"<<endl;
		Fred.Show_Main();
		cout << "\n Fred Radar:" << endl;
		Fred.Show_Radar();
		system("pause");
		system("cls");
	}
	cout << "Now leaving placing you back to the main menu." << endl;
	system("pause");
	system("cls");
}

void Attack(Player& p, AI& F)
{
	cout << "Pick the location between 1-10 (X Y)" << endl;
	cin >> p.choiceX >> p.choiceY;
	
	while (p.choiceX > 10||p.choiceY>10||p.choiceX<1||p.choiceY<1)
	{
		cout << "Invalid location" << endl;
		cout << "Pick the location between 1-10 (X Y)" << endl;
		cin >> p.choiceX >> p.choiceY;
	}
	int x = p.choiceX-1;
	int y = p.choiceY-1;

	if (F.Pgraph[x][y] != 'O')
	{
		p.Ograph[x][y] = 'X';
		F.Pgraph[x][y] = 'X';
		F.LoseShip();
		cout << "You hit Fred's ship." << endl;
	}
	else if (F.Pgraph[x][y] == 'O')
	{
		p.Ograph[x][y] = '/';
		cout << "You missed Fred." << endl;
	}
}