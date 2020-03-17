//
// Created by irena on 16.03.2020.
//

#ifndef PROJECT_MINESWEEPERBOARD_H
#define PROJECT_MINESWEEPERBOARD_H
#include "field.h"
enum GameMode  { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };
class MinesweeperBoard
{
    Field board_[100][100];
    int width_;
    int height_;
    int number_of_mines_;
    GameState game_status;
public:
    MinesweeperBoard(int width=10, int height=10, GameMode mode=EASY);
    ~MinesweeperBoard();
    void debug_display() const;
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;
    int countMines(int x, int y) const;
    bool hasFlag(int x, int y) const;
    void toggleFlag(int x, int y);
    void revealField(int x, int y);
    bool isRevealed(int x, int y) const;
    char getFieldInfo(int x, int y) const;
    GameState getGameState() const;
    bool isFirstMove();
    bool whenWin() const;


};
#endif //PROJECT_MINESWEEPERBOARD_H
