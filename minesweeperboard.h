//
// Created by irena on 16.03.2020.
//
//czym się rozni rozszerzeni .h od .hpp
//czy warto uzytwac konwencji z _ lub m_
//spyatj o tablice
#ifndef PROJECT_MINESWEEPERBOARD_H
#define PROJECT_MINESWEEPERBOARD_H
struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};
enum GameMode  { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };
class MinesweeperBoard
{
    Field board_[100][100];
    int width_;
    int height_;
    int number_of_mines_;
public:
    MinesweeperBoard(int width=10, int height=10, GameMode mode=EASY);
    ~MinesweeperBoard();
    void debug_display() const;
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;

};
#endif //PROJECT_MINESWEEPERBOARD_H
