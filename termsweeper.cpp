#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cstring> // Added for strcmp

// Platform-specific includes
#ifdef _WIN32
#include <conio.h> // Windows-specific header for keyboard input
#elif __linux__ || __APPLE__
#include <ncurses.h> // Linux/macOS-specific header for keyboard input
#endif

using namespace std;

enum Cell { Empty, Bomb };
enum State { Closed, Open, Flagged };

class Minefield {
public:
    Minefield(int rows, int cols, int bombPercentage) : Rows(rows), Cols(cols), BombPercentage(bombPercentage), Generated(false), CurrentRow(0), CurrentCol(0) {
        grid = vector<vector<Cell>>(rows, vector<Cell>(cols, Empty));
        cellStates = vector<vector<State>>(rows, vector<State>(cols, Closed));
    }

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
    string GetDisplayString() const;
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Redisplay() const;

    int GetCurrentRow() const { return CurrentRow; }
    int GetCurrentCol() const { return CurrentCol; }

private:
    bool Generated;
    vector<vector<Cell>> grid;
    vector<vector<State>> cellStates;
    int Rows;
    int Cols;
    int BombPercentage;
    int CurrentRow;
    int CurrentCol;
};

bool PromptYesNo(string question, int keep);
int PromptGridSize(string prompt);
int PromptBombPercentage(string prompt);

void PrintHelp();

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    int rows = 10; // Default value
    int cols = 10; // Default value
    int bombPercentage = 15; // Default value

    // Check for command-line parameters
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "--h") == 0) {
            PrintHelp();
            return 0;
        } else if (strcmp(argv[i], "-r") == 0 && i + 1 < argc) {
            rows = atoi(argv[i + 1]);
            ++i;
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            cols = atoi(argv[i + 1]);
            ++i;
        } else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            bombPercentage = atoi(argv[i + 1]);
            ++i;
        }
    }

    Minefield mainMinefield(rows, cols, bombPercentage);
    mainMinefield.Redisplay(); // Initial display

    bool exitGame = false;
    char userInput;
    while (!exitGame) {
        // Platform-specific keyboard input check
        #ifdef _WIN32
        if (_kbhit()) {
            userInput = _getch();
        #elif __linux__ || __APPLE__
        if (getch()) {
            userInput = getch();
        #endif

            switch (userInput) {
                case 'w':
                    mainMinefield.MoveUp();
                    mainMinefield.Redisplay();
                    break;
                case 's':
                    mainMinefield.MoveDown();
                    mainMinefield.Redisplay();
                    break;
                case 'a':
                    mainMinefield.MoveLeft();
                    mainMinefield.Redisplay();
                    break;
                case 'd':
                    mainMinefield.MoveRight();
                    mainMinefield.Redisplay();
                    break;
                case 'f':
                    mainMinefield.ToggleFlagAtCursor();
                    mainMinefield.Redisplay();
                    break;
                case 'r':
                    if (PromptYesNo("Again?", 1)) {
                        mainMinefield.Reset(rows, cols, bombPercentage);
                        mainMinefield.Redisplay();
                    }
                    break;
                case 'q':
                case 27:
                    exitGame = PromptYesNo("Exit?", 1);
                    break;
                case ' ':
                    if (mainMinefield.IsAtCursor(mainMinefield.GetCurrentRow(), mainMinefield.GetCurrentCol())) {
                        if (mainMinefield.OpenCellAtCursor()) {
                            mainMinefield.OpenAllBombs();
                            mainMinefield.Redisplay();
                            if (PromptYesNo("Bomb hit! Again?", 3)) {
                                mainMinefield.Reset(rows, cols, bombPercentage);
                                mainMinefield.Redisplay();
                            } else {
                                exitGame = true;
                            }
                        } else {
                            if (mainMinefield.CheckForVictory()) {
                                mainMinefield.FlagAllBombs();
                                mainMinefield.Redisplay();
                                if (PromptYesNo("Success! Again?", 3)) {
                                    mainMinefield.Reset(rows, cols, bombPercentage);
                                    mainMinefield.Redisplay();
                                } else {
                                    exitGame = true;
                                }
                            } else {
                                mainMinefield.Redisplay();
                            }
                        }
                    }
                    break;
            }
        }
    }

    return 0;
}

bool Minefield::CheckForVictory() const {
    for (int row = 0; row < Rows; ++row) {
        for (int col = 0; col < Cols; ++col) {
            switch (cellStates[row][col]) {
                case Open:
                    if (grid[row][col] != Empty)
                        return false;
                    break;
                case Closed:
                case Flagged:
                    if (grid[row][col] != Bomb)
                        return false;
                    break;
            }
        }
    }
    return true;
}

void Minefield::ToggleFlagAtCursor() {
    switch (cellStates[CurrentRow][CurrentCol]) {
        case Closed:
            cellStates[CurrentRow][CurrentCol] = Flagged;
            break;
        case Flagged:
            cellStates[CurrentRow][CurrentCol] = Closed;
            break;
    }
}

void Minefield::GetRandomEmptyCell(int &row, int &col) const {
    row = rand() % Rows;
    col = rand() % Cols;
}

bool Minefield::IsAdjacentToCursor(int row, int col) const {
    for (int dRow = -1; dRow <= 1; ++dRow) {
        for (int dCol = -1; dCol <= 1; ++dCol) {
            if (CurrentRow + dRow == row && CurrentCol + dCol == col)
                return true;
        }
    }
    return false;
}

void Minefield::RandomizeMinefield() {
    grid = vector<vector<Cell>>(Rows, vector<Cell>(Cols, Empty));

    if (BombPercentage > 100)
        BombPercentage = 100;

    int bombCount = (Rows * Cols * BombPercentage + 99) / 100;
    for (int index = 1; index <= bombCount; ++index) {
        int row, col;
        do {
            GetRandomEmptyCell(row, col);
        } while (grid[row][col] == Bomb || IsAdjacentToCursor(row, col));
        grid[row][col] = Bomb;
    }
}

bool Minefield::IsInsideMinefield(int row, int col) const {
    return row >= 0 && row < Rows && col >= 0 && col < Cols;
}

int Minefield::CountNeighborBombs(int row, int col) const {
    int count = 0;
    for (int dRow = -1; dRow <= 1; ++dRow) {
        for (int dCol = -1; dCol <= 1; ++dCol) {
            if (dRow != 0 || dCol != 0) {
                if (IsInsideMinefield(row + dRow, col + dCol)) {
                    if (grid[row + dRow][col + dCol] == Bomb) {
                        ++count;
                    }
                }
            }
        }
    }
    return count;
}

int Minefield::CountNeighborFlags(int row, int col) const {
    int count = 0;
    for (int dRow = -1; dRow <= 1; ++dRow) {
        for (int dCol = -1; dCol <= 1; ++dCol) {
            if (dRow != 0 || dCol != 0) {
                if (IsInsideMinefield(row + dRow, col + dCol)) {
                    if (cellStates[row + dRow][col + dCol] == Flagged) {
                        ++count;
                    }
                }
            }
        }
    }
    return count;
}

bool Minefield::OpenCellAtCursor() {
    return OpenCellAt(CurrentRow, CurrentCol);
}

bool Minefield::OpenCellAt(int row, int col) {
    if (!Generated) {
        RandomizeMinefield();
        Generated = true;
    }

    cellStates[row][col] = Open;

    if (CountNeighborBombs(row, col) == CountNeighborFlags(row, col)) {
        for (int dRow = -1; dRow <= 1; ++dRow) {
            for (int dCol = -1; dCol <= 1; ++dCol) {
                if (IsInsideMinefield(row + dRow, col + dCol)) {
                    if (cellStates[row + dRow][col + dCol] == Closed) {
                        if (OpenCellAt(row + dRow, col + dCol)) {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return grid[row][col] == Bomb;
}

void Minefield::FlagAllBombs() {
    for (int row = 0; row < Rows; ++row) {
        for (int col = 0; col < Cols; ++col) {
            if (grid[row][col] == Bomb) {
                cellStates[row][col] = Flagged;
            }
        }
    }
}

void Minefield::OpenAllBombs() {
    for (int row = 0; row < Rows; ++row) {
        for (int col = 0; col < Cols; ++col) {
            if (grid[row][col] == Bomb) {
                cellStates[row][col] = Open;
            }
        }
    }
}

void Minefield::Reset(int rows, int cols, int bombPercentage) {
    Generated = false;
    CurrentRow = 0;
    CurrentCol = 0;
    Rows = rows;
    Cols = cols;
    BombPercentage = bombPercentage;
    grid = vector<vector<Cell>>(rows, vector<Cell>(cols, Empty));
    cellStates = vector<vector<State>>(rows, vector<State>(cols, Closed));
}

bool Minefield::IsAtCursor(int row, int col) const {
    return CurrentRow == row && CurrentCol == col;
}

string Minefield::GetDisplayString() const {
    stringstream ss;
    for (int row = 0; row < Rows; ++row) {
        for (int col = 0; col < Cols; ++col) {
            if (IsAtCursor(row, col)) {
                ss << '[';
            } else {
                ss << ' ';
            }

            switch (cellStates[row][col]) {
                case Open:
                    switch (grid[row][col]) {
                        case Bomb:
                            ss << '*';
                            break;
                        case Empty:
                            int neighbors = CountNeighborBombs(row, col);
                            if (neighbors > 0)
                                ss << neighbors;
                            else
                                ss << ' ';
                            break;
                    }
                    break;
                case Closed:
                    ss << '.';
                    break;
                case Flagged:
                    ss << '$';
                    break;
            }

            if (IsAtCursor(row, col)) {
                ss << ']';
            } else {
                ss << ' ';
            }
        }
        ss << '\n';
    }
    return ss.str();
}

void Minefield::MoveUp() {
    if (CurrentRow > 0)
        --CurrentRow;
}

void Minefield::MoveDown() {
    if (CurrentRow < Rows - 1)
        ++CurrentRow;
}

void Minefield::MoveLeft() {
    if (CurrentCol > 0)
        --CurrentCol;
}

void Minefield::MoveRight() {
    if (CurrentCol < Cols - 1)
        ++CurrentCol;
}

void Minefield::Redisplay() const {
    system("cls"); // Clear screen on Windows
    cout << GetDisplayString();
}

bool PromptYesNo(string question, int keep) {
    char answer;
    cout << question << " [y/n] ";
    while (true) {
        cin >> answer;
        switch (answer) {
            case 'y':
            case 'Y':
            case ' ':
            case '\n':
                if (keep & 1)
                    cout << "y" << endl;
                else
                    system("cls");
                return true;
            case 'n':
            case 'N':
            case 27:
                if (keep & 2)
                    cout << "n" << endl;
                else
                    system("cls");
                return false;
        }
    }
}

int PromptGridSize(string prompt) {
    int size;
    cout << prompt;
    cin >> size;
    return size;
}

int PromptBombPercentage(string prompt) {
    int percentage;
    cout << prompt;
    cin >> percentage;
    return percentage;
}

void PrintHelp() {
    cout << "Minesweeper Game" << endl;
    cout << "Usage: minesweeper [-r ROWS] [-c COLS] [-b BOMBS]" << endl;
    cout << "Options:" << endl;
    cout << "  --help, -h      Display this help message" << endl;
    cout << "  -r ROWS         Number of rows in the grid (default: 10)" << endl;
    cout << "  -c COLS         Number of columns in the grid (default: 10)" << endl;
    cout << "  -b BOMBS        Percentage of bombs in the grid (default: 15)" << endl;
}
