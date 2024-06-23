/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * This header contains the global/common variables of the project.
 * You don't really need to change anything.
 * TIP: After completing your project, you can make changes for aesthetics.
 * */


//---Title: PF-Project, Fall-2022 for BS(CS)---//
const char title[] = "PF-Project, Fall-2022";

//---Height and Width of the Actual Interactive Game---//
const int M = 20;   //Number of rows for a piece to cover on the screen (not the entire screen) = 20
const int N = 10;   //Number of columns for a piece to cover on the screen (not the entire screen) = 10

//---The Actual Interactive Game Grid - Built Over (MxN)---//
int gameGrid[M][N] = {0};

//---To Hold the Coordinates of the Piece---//
int point_1[4][2]={{0}}, point_2[4][2]={{0}};
int shadow_1[4][2]={{0}}, shadow_2[4][2]={{0}};
int bomb_1[4][2]={{0}}, bomb_2[4][2]={{0}};




//---Check Uncertain Conditions---//
bool anamoly(){
    for (int i=0;i<4;i++)
        if (point_1[i][0]<0 || point_1[i][0]>=N || point_1[i][1]>=M)
            return 0;
        else if (gameGrid[point_1[i][1]][point_1[i][0]])
            return 0;
    return 1;
}


//ANAMOLY FOR BLOCK STICK TO LEFT

bool rotate_anamoly_left(){
    for (int i=0;i<4;i++)
        if (point_1[i][0]<0)
            return 0;
        else if (gameGrid[point_1[i][1]][point_1[i][0]])
            return 0;
    return 1;
}


//ANAMOLY FOR BLOCK STICK TO RIGHT

bool rotate_anamoly_right(){
    for (int i=0;i<4;i++)
        if (point_1[i][0]>=N)
            return 0;
        else if (gameGrid[point_1[i][1]][point_1[i][0]])
            return 0;
            
    return 1;

}


//ANAMOLY FOR SHADOW

bool shadow_anamoly(){
    for (int i=0;i<4;i++)
        if (shadow_1[i][0]<0 || shadow_1[i][0]>=N || shadow_1[i][1]>=M-1)
            return 1;
        else if (gameGrid[shadow_1[i][1]+1][shadow_1[i][0]])
            return 1;
    return 0;
}


//ANAMOLY FOR BOMB

bool bomb_anamoly(bool& bomb1){
    for (int i=0;i<4;i++)
        if (bomb_1[i][0]<0 || bomb_1[i][0]>=N || bomb_1[i][1]>=M)
        {
            bomb1=0;
            return 0;
        }
        else if (gameGrid[bomb_1[i][1]][bomb_1[i][0]])
        {
            bomb1=0;
            return 0;
        }
        
    return 1;
}
