#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Choice { ROCK = 1, PAPER = 2, SCISSORS = 3 };

class Player {
public:
    virtual Choice makeChoice() = 0;  // pure virtual function
    virtual ~Player() {}
};

class HumanPlayer : public Player {
public:
    Choice makeChoice() override {
        int choice;
        do {
            cout << "Choose: 1 = Rock, 2 = Paper, 3 = Scissors : ";
            cin >> choice;
            if (choice < 1 || choice > 3)
                cout << "Invalid choice. Try again.\n";
        } while (choice < 1 || choice > 3);
        return static_cast<Choice>(choice);
    }
};

class ComputerPlayer : public Player {
public:
    Choice makeChoice() override {
        return static_cast<Choice>(rand() % 3 + 1);
    }
};

class Game {
private:
    Player* player1;
    Player* player2;

    string choiceToString(Choice c) {
        switch (c) {
            case ROCK: return "Rock";
            case PAPER: return "Paper";
            case SCISSORS: return "Scissors";
            default: return "";
        }
    }

    int determineWinner(Choice c1, Choice c2) {
        if (c1 == c2) return 0; // tie
        if ((c1 == ROCK && c2 == SCISSORS) ||
            (c1 == PAPER && c2 == ROCK) ||
            (c1 == SCISSORS && c2 == PAPER))
            return 1;
        else
            return 2;
    }

public:
    Game(Player* p1, Player* p2) : player1(p1), player2(p2) {}

    void playRound() {
        Choice c1 = player1->makeChoice();
        Choice c2 = player2->makeChoice();

        cout << "Player 1 chose " << choiceToString(c1) << "\n";
        cout << "Player 2 chose " << choiceToString(c2) << "\n";

        int winner = determineWinner(c1, c2);
        if (winner == 0) {
            cout << "It's a tie!\n";
        } else {
            cout << "Player " << winner << " wins this round!\n";
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "Welcome to Rock Paper Scissors Game!\n";
    cout << "Select game mode:\n1. Human vs Computer\n2. Computer vs Computer\nChoose option: ";
    int mode;
    cin >> mode;

    Player* p1;
    Player* p2;

    if (mode == 1) {
        p1 = new HumanPlayer();
        p2 = new ComputerPlayer();
    } else {
        p1 = new ComputerPlayer();
        p2 = new ComputerPlayer();
    }

    Game game(p1, p2);

    char again;
    do {
        game.playRound();
        cout << "Play again? (y/n): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');

    delete p1;
    delete p2;

    cout << "Thanks for playing!\n";
    return 0;
}
