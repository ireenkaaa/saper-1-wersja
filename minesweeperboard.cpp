//
// Created by irena on 16.03.2020.
//
using std::cout, std::endl;
MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode) {
    game_status=RUNNING;
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
int MinesweeperBoard::countMines(int x, int y) const
{
    if(x>width_ || y>height_ || board_[x][y].isRevealed==0)
    {
        return -1;
    }
    else{
        int temp_mine_counter=0;
        for(int i=(x+1); i>(x-2); i--)
        {
            for(int j=(y+1); j>(y-2);j--)
            {
                if (i>=0 && j>=0) {
                    if (board_[i][j].hasMine == 1) {
                        temp_mine_counter += 1;
                    }
                }
            }
        }
        return temp_mine_counter;
    }
}
bool MinesweeperBoard::hasFlag(int x, int y) const
{
    if(x>width_ || y>height_ || board_[x][y].hasFlag==0 || board_[x][y].isRevealed==1)
    {
        return false;
    }
    if(board_[x][y].hasFlag==1)
    {
        return true;
    }
}
void MinesweeperBoard::toggleFlag(int x, int y)
{
    if(board_[x][y].isRevealed==0)
    {
        board_[x][y].hasFlag=1;
    }
     else if(board_[x][y].isRevealed==1 || x>width_ || y>height_ || game_status!=RUNNING)
    {}
}
void MinesweeperBoard::revealField(int x, int y)
{
    if(board_[x][y].isRevealed==1 || x>width_ || y>height_ || board_[x][y].hasFlag==1 || game_status!=RUNNING )
    {}
    else if(board_[x][y].isRevealed==0 && board_[x][y].hasMine==0)
    {
        board_[x][y].isRevealed=1;
    }
    else if(board_[x][y].isRevealed==0 && board_[x][y].hasMine==1)
    {
        if(isFirstMove()==1)
        {
            board_[x][y].hasMine=0;
            board_[rand() % width_][rand() % height_].hasMine = 1;
        }
        else
        {
            this->game_status=FINISHED_LOSS;
        }
    }
}
bool MinesweeperBoard::isRevealed(int x, int y) const
{
    if(board_[x][y].isRevealed==1)
    {
        return true;
    }
}
char MinesweeperBoard::getFieldInfo(int x, int y) const
{
    if(x>width_ || y>height_)
    {
        return '#';
    }
    else if(board_[x][y].isRevealed==0 && board_[x][y].hasFlag==1 )
    {
        return 'F';
    }
    else if(board_[x][y].isRevealed==0 && board_[x][y].hasFlag==0 )
    {
        return '_';
    }
   else if(board_[x][y].isRevealed==1 && board_[x][y].hasMine==1 )
    {
        return 'x';
    }
    else if(board_[x][y].isRevealed==1 && this->countMines(x,y)==0 )
    {
        return ' ';
    }
    else if(board_[x][y].isRevealed==1 && this->countMines(x,y)!=0 )
    {
        return this->countMines(x,y); //sprawdz co tu zwrócii
    }

}
bool MinesweeperBoard::isFirstMove()
{
    int temp_counter=0;
    for(int j=0; j<height_; j++) {
        for (int i = 0; i < width_; i++) {
            if(board_[i][j].isRevealed==0)
            {
                temp_counter++;
            }

        }

    }
    if(temp_counter==(width_*height_))
    {
        return true;
    }
    else
        return false;
}
GameState MinesweeperBoard::getGameState() const
{
    if(this->game_status==RUNNING)
        return RUNNING;
    else if (this->game_status==FINISHED_LOSS)
    {
        return FINISHED_LOSS;
    } else if(this->whenWin()==true)
    {
        return FINISHED_WIN;
    }

}
bool MinesweeperBoard::whenWin() const
{

    int temp_counter_flags=0;
    int temp_counter_revealed=0;
    for(int j=0; j<height_; j++) {
        for (int i = 0; i < width_; i++) {
            if(board_[i][j].hasMine==1 && board_[i][j].hasFlag==1)
            {
                temp_counter_flags++;
            }
            if(board_[i][j].hasMine==1 && board_[i][j].isRevealed==0)
            {
                temp_counter_revealed++;
            }

        }

    }
    if(temp_counter_flags==this->getMineCount() || temp_counter_revealed==this->getMineCount())
    {
        return true;
    }


}