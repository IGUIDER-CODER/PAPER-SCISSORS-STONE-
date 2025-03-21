#include <string>
//#include<math.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
enum enChoice { ePaper = 1, eStone = 2, eScisore = 3 };
enum enWinner { eComputer = 1, ePlayer = 2, eDraw = 3 };
struct stRoundInfo {
	enChoice PlayerChoice;
	enChoice ComputerChoice;
	enWinner RoundWinner;
};
struct stGameInfo {
	short RounsNumber = 0;
	short CumputerWinsTimes = 0;
	short PlayerWinsTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner = eDraw;
};
stGameInfo GameInfo;
short ReadHouManyRoundsToPlay() {
	short Rounds = 0;
	do
	{
		cout << "\nEnter hou many rounds to play  ?";
		cin >> Rounds;
	} while (Rounds <= 0);
	return Rounds;
}
enChoice ReadPlayerChoice() {
	short Choice = 0;
	do
	{
		cout << "\nEnter your choice [1]:Paper,[2]:Stone,[3]Scisore ";
		cin >> Choice;
	} while (Choice < 0 || Choice > 3);
	return (enChoice)Choice;
}
int RandomNumber(int From, int To)
{
	// Generate a random number between 0 and (To - From) using rand(),
	// then add From to shift the range to [From, To].
	int randNum = rand() % (To - From + 1) + From;
	return randNum;  // Return the generated random number.
}
enChoice GetComputerChoice() {
	return (enChoice)RandomNumber(1, 3);
}
void ComputerWonSituation() {
	system("color 4f");
	GameInfo.CumputerWinsTimes++;
}
void PlayerWonSituation() {
	system("color 9f");
	GameInfo.PlayerWinsTimes++;
}
void DrawSituation() {
	system("color 6f");
	GameInfo.DrawTimes++;
}
enWinner GetRoundWinner(enChoice& Playerchoice, enChoice& ComputerChoice) {
	if (Playerchoice == ComputerChoice)
	{
		DrawSituation();
		return enWinner::eDraw;
	}
	switch (Playerchoice) {
	case ePaper:
		if (ComputerChoice == eStone)
		{
			PlayerWonSituation();
			return ePlayer;
		}
		break;
	case eScisore:
		if (ComputerChoice == ePaper)
		{
			PlayerWonSituation();
			return ePlayer;
		}
		break;
	case eStone:
		if (ComputerChoice == eScisore)
		{
			PlayerWonSituation();
			return ePlayer;
		}
		break;
	}
	ComputerWonSituation();
	return eComputer;
}
string ChoiceString(enChoice& ComptChoice) {
	string Choice[] = { "Paper","Stone","Scisore" };
	return Choice[ComptChoice - 1];
}
string WinnerString(enWinner Winner) {
	string Result[] = { "Computer","Player","No Winner" };
	return Result[Winner - 1];
}
void DisplayRoundResults(short& RoundNumber, enWinner& RoundWinner, enChoice& ComptChoice, enChoice& PlyChoice) {
	cout << "_____________________________Round[" << RoundNumber << "]_____________________________" << endl;
	cout << "Computer Choice      : " << ChoiceString(ComptChoice) << endl;
	cout << "Player Choice        : " << ChoiceString(PlyChoice) << endl;
	cout << "Round Winner         : " << WinnerString(RoundWinner) << endl;
	cout << "________________________________________________________" << endl;
}
void StartRound(short& RoundNumber) {
	stRoundInfo RoundInfo;
	RoundInfo.PlayerChoice = ReadPlayerChoice();
	RoundInfo.ComputerChoice = GetComputerChoice();
	RoundInfo.RoundWinner = GetRoundWinner(RoundInfo.PlayerChoice, RoundInfo.ComputerChoice);
	DisplayRoundResults(RoundNumber, RoundInfo.RoundWinner, RoundInfo.ComputerChoice, RoundInfo.PlayerChoice);


}
enWinner GetFinalWinner() {
	if (GameInfo.CumputerWinsTimes > GameInfo.PlayerWinsTimes)
		return eComputer;
	if (GameInfo.CumputerWinsTimes < GameInfo.PlayerWinsTimes)
		return ePlayer;
	else
		return eDraw;

}
void GameOver() {
	system("color 0f");
	cout << "\t\t______________________________________________________________________________" << endl;
	cout << "\t\t                           + + + Game Over + + + " << endl;
	cout << "\t\t______________________________________________________________________________" << endl;
	cout << "\n\t\t___________________________ [ Game Results ] ________________________________" << endl;
	cout << "\t\tGame Rounds        : " << GameInfo.RounsNumber << endl;
	cout << "\t\tPlayer Won Times   : " << GameInfo.PlayerWinsTimes << endl;
	cout << "\t\tComputer Won Times : " << GameInfo.CumputerWinsTimes << endl;
	cout << "\t\tDraw Times         : " << GameInfo.DrawTimes << endl;
	cout << "\t\tFinal Winner       : " << WinnerString(GetFinalWinner()) << endl;
	cout << "\t\t______________________________________________________________________________" << endl;

}
void ResetGameInfo() {
	short RounsNumber = 0;
	short CumputerWinsTimes = 0;
	short PlayerWinsTimes = 0;
	short DrawTimes = 0;
}
void Start() {
	short Round = 1;
	GameInfo.RounsNumber = ReadHouManyRoundsToPlay();
	while (Round <= GameInfo.RounsNumber)
	{
		cout << "\nRound [" << Round << "] begins : ";
		StartRound(Round);
		Round++;
	}
	GameOver();
	ResetGameInfo();
}
void StartGame() {
	char Yes = 'Y';
	do
	{
		system("cls");
		Start();
		cout << "\nDo you wanna play new game ? [Y/N] ";
		cin >> Yes;
	} while (toupper(Yes) == 'Y');
}
int main()
{

	srand((unsigned)time(NULL));
	StartGame();
}