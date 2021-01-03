#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "algorithm.h"


using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions
 * 1. ~ 4. are listed in next block)
 *
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 *
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/

int findbest(Board board,Player now,Player next,int depth,int r,int c,int * record,char mecolor,char youcolor);
int countmax(Board board,char mecolor,char youcolor);
bool checkcorner(Board board,Player player,int corner[]);
bool goodchoice(Board board,Player player,int r,int c);
bool activatecorner(Board board,Player player,int cc[]);
bool checknear(Board board,Player player,int r,int c);
void algorithm_A(Board board, Player player, int index[])
{
//create a temp Board
//new funtcion
    char enemycolor=(player.get_color()=='r')?'b':'r';
    Player enemy(enemycolor);
    int store=0;
    int large=-200;
    int t;
    if(activatecorner(board,player,index)==true)
    {
        //cout<<"suck";
        return;
    }
    else if(checkcorner(board,player,index)==true)
    {
        //cout<<"shit";
        return;
    }
    else
    {
        //cout<<"fuck";
        //int corner[4][2]= {{0,0},{0,5},{4,0},{4,5}};
        for(int i=0; i<ROW; i++)
        {
            for(int j=0; j<COL; j++)
            {
                if(i==0 && j==0 || i==0 && j==5 || i==4 && j==0 || i==4 && j==5)
                    continue;

                if(board.get_cell_color(i,j)!=enemy.get_color() )
                {
                    t=findbest(board,player,enemy,1,i,j,&store,player.get_color(),enemycolor);
                    if(t>large)
                    {
                        large=t;
                        index[0]=i;
                        index[1]=j;
                    }
                }
            }
        }
        return;
    }
}
bool checkcorner(Board board,Player player,int cc[])
{
    int corner[4][2]= {{0,0},{0,5},{4,0},{4,5}};
    int near[8][2]= {{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};
    bool can=true;
    for(int i=0; i<4; i++)
    {
        if( board.get_cell_color(corner[i][0],corner[i][1])=='w'  )
        {

            for(int j=0; j<8; j++)
            {
                if(corner[i][0]+near[j][0]>=0 && corner[i][0]+near[j][0]<ROW && corner[i][1]+near[j][1]>=0 && corner[i][1]+near[j][1]<COL)
                {
                    //int r=corner[i][1]+near[j][0]; int c=corner[i][1]+near[j][0]
                    //cout<<board.get_capacity(corner[i][0]+near[j][0],corner[i][1]+near[j][1])<<endl;
                    //cout<<corner[i][0]+near[j][0]<<" "<<corner[i][1]+near[j][1]<<endl;

                    if(board.get_cell_color(corner[i][0]+near[j][0],corner[i][1]+near[j][1])!=player.get_color() && (board.get_capacity(corner[i][0]+near[j][0],corner[i][1]+near[j][1])-board.get_orbs_num(corner[i][0]+near[j][0],corner[i][1]+near[j][1])<board.get_capacity(corner[i][0],corner[i][1])))
                    {
                        //cout<<"eric";
                        can=false;
                        break;
                    }

                }
            }
            if(can)
            {
                cc[0]=corner[i][0];
                cc[1]=corner[i][1];
                return true;
            }
        }
    }
    for(int i=0; i<4; i++)
    {
        if(board.get_cell_color(corner[i][0],corner[i][1])==player.get_color() && board.get_orbs_num(corner[i][0],corner[i][1])==1)
        {
            cc[0]=corner[i][0];
            cc[1]=corner[i][1];
            return true;
        }
    }
    return false;
}
bool activatecorner(Board board,Player player,int cc[])
{
    int corner[4][2]= {{0,0},{0,5},{4,0},{4,5}};
    for(int i=0; i<4; i++)
    {
        if(board.get_cell_color(corner[i][0],corner[i][1])==player.get_color() && board.get_orbs_num(corner[i][0],corner[i][1])==2 && checknear(board,player,corner[i][0],corner[i][1]) )
        {
            cc[0]=corner[i][0];
            cc[1]=corner[i][1];
            return true;
        }
    }
}
bool checknear(Board board,Player player,int r,int c)
{
    int near[8][2]= {{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};
    for(int i=0; i<8; i++)
    {
        if(r+near[i][0]>=0 && r+near[i][0]<ROW && c+near[i][1]>=0 && c+near[i][1]<COL)
        {
            if(board.get_cell_color(r+near[i][0],c+near[i][1])!='w' && (board.get_cell_color(r+near[i][0],c+near[i][1])!=player.get_color() && (board.get_capacity(r+near[i][0],c+near[i][1])-board.get_orbs_num(r+near[i][0],c+near[i][1])<2)))
                return true;
        }
    }
    return false;
}
bool goodchoice(Board board,Player player,int r,int c)
{
    int near[8][2]= {{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};
    for(int i=0; i<8; i++)
    {
        if(r+near[i][0]>=0 && r+near[i][0]<ROW && c+near[i][1]>=0 && c+near[i][1]<COL)
        {
            if(!(board.get_cell_color(r+near[i][0],c+near[i][1])!='w' && board.get_cell_color(r+near[i][0],c+near[i][1])!=player.get_color() && (board.get_capacity(r+near[i][0],c+near[i][1])-board.get_orbs_num(r+near[i][0],c+near[i][1])>2)))
                return false;
        }
    }
    return true;

}
int findbest(Board board,Player now,Player next,int depth,int r,int c,int * record,char mecolor,char youcolor)
{
    if( depth==4)
    {
     int t=countmax(board,mecolor,youcolor);
        return t;
    }
        int state=0;
//place the orb
    board.place_orb(r,c,&now);
    if(now.get_color()==mecolor)
    {
        //find max
       int m=-1000;
        for(int i=0; i<ROW; i++)
        {
            for(int j=0; j<COL; j++)
            {
                if(board.get_cell_color(i,j)!=now.get_color()){
                     state=findbest(board,next,now,depth+1,i,j,record,mecolor,youcolor);
                     if(state>m){
                        m=state;
                     }
                }
            }
        }
return m;
    }
    else if(now.get_color()!=mecolor){
        //find min
      int m=1000;
        for(int i=0; i<ROW; i++)
        {
            for(int j=0; j<COL; j++)
            {
                if(board.get_cell_color(i,j)!=now.get_color()){
                     state=findbest(board,next,now,depth+1,i,j,record,mecolor,youcolor);
                     if(state<m){
                        m=state;
                     }
                }
            }
        }
       return m;
    }
}
int countmax(Board board,char mecolor,char youcolor)
{
    int countt=0;
    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            if(board.get_cell_color(i,j)==mecolor)
            {
                countt++;
            }
            else if(board.get_cell_color(i,j)==youcolor)
            {
                countt--;
            }
        }
    }
    return countt;
}
