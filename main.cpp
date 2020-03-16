#include <iostream>
#include "minesweeperboard.h"
#include <stdlib.h>
using std::cout, std::endl;

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode) {
    if(width>0 && width<100)
    {
        width_=width;
        height_=height;
    } else{
        cout<<"Incorrect value. I set width to 10"<<endl;
        width=10;
    }
    if(height>0 && height<100)
    {
        width_=width;
        height_=height;
    } else{
        cout<<"Incorrect value. I set height to 10"<<endl;
        height=10;
    }
    board_[height][width];
    for(int j=0; j<height; j++) {
        for (int i = 0; i < width; i++) {
            board_[i][j].hasFlag=0;
            board_[i][j].hasMine=0;
            board_[i][j].isRevealed=0;
        }
    }
 number_of_mines_=0;
    if (mode==EASY)
    {
        number_of_mines_=(width*height*0.1);
    }
    if(mode==NORMAL)
    {
        number_of_mines_=(width*height*0.2);
    }
    if(mode==HARD)
    {
        number_of_mines_=(width*height*0.3);
    }
    if(mode==DEBUG)
    {

        for(int j=0; j<height; j++) {
            for (int i = 0; i < width; i++) {
                if(i==j || i==0 && j%2==0 || j==0 )
                {
                    board_[i][j].hasMine=1;
                    number_of_mines_+=1;
                }

            }
        }

    }
    if(mode!=DEBUG) {
        for (int j = 0; j < number_of_mines_; j++) {
            board_[rand() % width][rand() % height].hasMine = 1;
        }
    }
}
int MinesweeperBoard::getBoardWidth() const
{
    return width_;
}
int MinesweeperBoard::getBoardHeight() const
{
    return height_;
}
int MinesweeperBoard::getMineCount() const
{
    return number_of_mines_;
}
MinesweeperBoard::~MinesweeperBoard()
{}
void MinesweeperBoard::debug_display() const {
    for(int j=0; j<height_; j++) {
        for (int i = 0; i <width_; i++) {
            cout<<"[";
            if(board_[i][j].hasMine==0)
            {
                cout<<".";
            } else{
                cout<<"M";
            }
            if(board_[i][j].isRevealed==0)
            {
                cout<<".";
            } else{
                cout<<"o";
            }
            if(board_[i][j].hasFlag==0)
            {
                cout<<".";
            } else{
                cout<<"f";
            }
            cout<<"]";

        }
        cout<<endl;
    }
}
int main() {
    MinesweeperBoard Board1(4, 7, DEBUG);
    Board1.debug_display();
    cout<<Board1.getMineCount()<<endl;
    cout<<Board1.getBoardHeight()<<endl;
    cout<<Board1.getBoardWidth()<<endl;
    return 0;
}
