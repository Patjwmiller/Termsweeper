#ifndef TERMSWEEPER_H
#define TERMSWEEPER_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cstring>

enum Cell { Empty, Bomb };
enum State { Closed, Open, Flagged };

class Minefield {
public:
    Minefield(int rows, int cols, int bombPercentage);
    bool CheckForVictory() const;
    void ToggleFlagAtCursor();
    void GetRandomEmptyCell(int &row, int &col) const;
    bool IsAdjacentToCursor(int row, int col) const;
    void RandomizeMinefield();
    bool IsInsideMinefield(int row, int col) const;
    int CountNeighborBombs(int row, int col) const;
    int CountNeighborFlags(int row, int col) const;
    bool OpenCellAtCursor();
    bool OpenCellAt(int row, int col);
    void FlagAllBombs();
    void OpenAllBombs();
    void Reset(int rows, int cols, int bombPercentage);
    bool IsAtCursor(int row, int col) const;
    std::string GetDisplayString() const;
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Redisplay() const;

    int GetCurrentRow() const { return CurrentRow; }
    int GetCurrentCol() const { return CurrentCol; }

private:
    bool Generated;
    std::vector<std::vector<Cell>> grid;
    std::vector<std::vector<State>> cellStates;
    int Rows;
    int Cols;
    int BombPercentage;
    int CurrentRow;
    int CurrentCol;
};

bool PromptYesNo(std::string question, int keep);
int PromptGridSize(std::string prompt);
int PromptBombPercentage(std::string prompt);

void PrintHelp();

#endif  // TERMSWEEPER_H