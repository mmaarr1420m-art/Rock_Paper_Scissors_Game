#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoice {Rock = 1, Paper = 2, Scissors = 3};
enum enWinner {Player = 1, Computer = 2, Draw = 3};

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName = "";
};

struct stGameResult
{
	short GameRound = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

short ReadHowManyRounds()
{
	short GameRounds = 0;

	do
	{
		cout << "How Many Rounds ? From 1 to 10 ?\n";
		cin >> GameRounds;

	} while (GameRounds < 1 || GameRounds > 10);

	return GameRounds;
}

int Random(int From, int To)
{
    // To Generate Random Number in Range [From, To]
	return rand() % (To - From + 1) + From;
}

enGameChoice ReadPlayerChoice()
{
	short Choice;
	do
	{
		cout << "\nYour Choice: [1]:Rock, [2]:Paper, [3]:Scissors? ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}

enGameChoice ReadComputerChoice()
{
	return (enGameChoice)Random(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::Rock:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
        break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Rock)
		{
			return enWinner::Computer;
		}
		break;
	}
    // If none of the above conditions are met, the player wins
	return enWinner::Player;
}

string WinnerName(enWinner Winner)
{
	string arrNameWinner[3] = { "Player","Computer","Draw" };
	return arrNameWinner[Winner - 1];
}

string ChoiceName(enGameChoice Choice)
{
	string arrGameChoice[3] = { "Rock", "Paper", "Scissors" };
	return arrGameChoice[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player:
		system("color 2F"); // Turn screen to Green 
		break;

	case enWinner::Computer:
		system("color 4F"); // Turn screen to Red and make a bell sound
		cout << "\a";
		break;

	case enWinner::Draw:
		system("color 6F"); // Turn screen to Yellow
		break;
	}
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] _______________\n\n";
	cout << "Player Choice  : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
	cout << "______________________________________\n" << endl;

	SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWinTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::Player;
	else if (PlayerWinTimes < ComputerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResult FillGameResult(int GameRound, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResult GameResult;

    GameResult.GameRound = GameRound;
	GameResult.ComputerWinTimes = ComputerWinTimes;
	GameResult.DrawTimes = DrawTimes;
    GameResult.PlayerWinTimes = PlayerWinTimes;
	GameResult.GameWinner = WhoWinTheGame(PlayerWinTimes, ComputerWinTimes);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);

    return GameResult;
}

stGameResult PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = ReadComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        // Increase Win/Draw Counter
		if (RoundInfo.Winner == enWinner::Player)
			PlayerWinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResult(RoundInfo);
	}

	return FillGameResult(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
    string t = "";

    for (short i = 1; i <= NumberOfTabs; i++)
    {
        t += "\t";
    }

    return t;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "_________________________________________________________\n\n";
	cout << Tabs(4) << " +++ G a m e  O v e r +++\n";
    cout << Tabs(2)<< "__________________________________________________________\n\n";
}

void ResetScreen()
{
	system("cls"); 
	system("color 0F");
}

void PrintFinalGameResult(stGameResult GameResult)
{
	cout << Tabs(2) << "___________________ [Final Game Results] _________________\n\n";

	cout << Tabs(2) << "Total Rounds   : " << GameResult.GameRound << endl;
	cout << Tabs(2) << "Player Won     : " << GameResult.PlayerWinTimes << endl;
	cout << Tabs(2) << "Computer Won   : " << GameResult.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draws          : " << GameResult.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner   : " << GameResult.WinnerName << endl;
			
	cout << Tabs(2) << "____________________________________________________________\n";

	SetWinnerScreenColor(GameResult.GameWinner);
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResult GameResult = PlayGame(ReadHowManyRounds()); // Fill stGameResult GameResult
		ShowGameOverScreen();
		PrintFinalGameResult(GameResult);

		cout << endl;
        cout << Tabs(2) << "Do you want to play again? Y/N ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL)); // Seed the random generator in C++, call only once

	StartGame();  

	return 0;
}
