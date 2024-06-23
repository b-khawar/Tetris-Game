#include<iostream>
using namespace std;
/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float& timer, float& delay, int& colorNum)
{

    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
        if (!anamoly()){
            
            for(int i = 0; i < 4; ++i)
            {
                gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
            }
               
            colorNum = 1 + (rand()%7);
            int n=rand()%7;
            //--- Un-Comment this Part When You Make BLOCKS array---//
            
                for (int i=0;i<4;i++){
                    point_1[i][0] = BLOCKS[n][i] % 2;
                    point_1[i][1] = BLOCKS[n][i] / 2;
                }
            
        }
        timer=0;
    }
}


/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///



//------------------------------------------------------------
//FUNCTION TO MOVE THE PIECE LEFT/RIGHT

void Move_Horizontal(int& delta_x)
{
	for (int i=0;i<4;i++)
	{
		point_2[i][0]=point_1[i][0];
        point_2[i][1]=point_1[i][1];
		point_1[i][0] += delta_x;    //Move left/right
	}
	
	if (!anamoly())
	{
		for (int i=0; i<4; ++i)
		{
			point_1[i][0]=point_2[i][0];
			point_1[i][1]=point_2[i][1];
		}
	}
	delta_x=0;
}


//------------------------------------------------------------
//FUNCTION TO ROTATE THE PIECE

void Rotate(bool& rotate)
{
	if (rotate)
	{
		//implementing the general formula of rotation
		for (int i=0; i<4; ++i)
		{
		int a = point_1[i][1]-point_1[1][1];
		int b = point_1[i][0]-point_1[1][0];
		point_1[i][0] = point_1[1][0]-a;
		point_1[i][1] = point_1[1][1]+b;
		}
	
		if (!anamoly())
		{
			if (!rotate_anamoly_left())   //sticks to left wall
				for (int i=0; i<4; ++i)
				{
					point_1[i][0]+=1;
				}
			
			if (!rotate_anamoly_right())   //sticks to right wall
				for (int i=0; i<4; ++i)
				{
					point_1[i][0]-=1;
				}
		}
	}
	rotate=0;
}


//------------------------------------------------------------
//FUNCTION TO CHECK IF A ROW IS COMPLETE

void Row_Check(int& score)
{
	int x=M-1;   //count value
	int rows_destroyed=0;
	
	for (int i = M - 1; i > 0; --i)
	{
		int blocks=0;
		for (int j = 0; j < N; ++j)
		{
	     	if (gameGrid[i][j])
	     		blocks += 1;
	     	gameGrid[x][j] = gameGrid[i][j];
		}
		if (blocks < N)
			x -= 1;
		else
			rows_destroyed += 1;
	}
	
	if (rows_destroyed == 1)
		score += 10;
	else if (rows_destroyed == 2)
		score += 30;
	else if (rows_destroyed == 3)
		score += 60;
	else if (rows_destroyed == 4)
		score += 100;
}


//------------------------------------------------------------
//FUNCTION TO MAKE A SHADOW(BOMB AND PIECE)

void make_shadow(int p[][2])
{
	for (int y=0; y<4; ++y)
	{
		shadow_1[y][0] = p[y][0];
		shadow_1[y][1] = p[y][1];
	}
	while (!shadow_anamoly())
		for (int i=0; i<4; ++i)
			shadow_1[i][1] += 1;
}


//------------------------------------------------------------
//FUNCTION TO DROP THE PIECE USING SPACE BAR

void drop_peice(bool& space)
{	
	if (space)
		for (int i=0; i<4; ++i)
		{
			point_1[i][1]=shadow_1[i][1];
			point_2[i][1]=shadow_2[i][1];
		}
	space=0;
}


//------------------------------------------------------------
//FUNCTION TO RANDOMIZE THE RELEASE POINT OF BOMB

void Rand_bomb()
{
	bomb_1[0][0]=rand()%10;
	for(int i=1;i<4;++i)
	{
		bomb_1[i][0]=bomb_1[0][0];
	}
}


//------------------------------------------------------------
//FUNCTION FOR EFFECT OF BOMB(GRID CLEAR, BLOCK CLEAR, OR NOTHING)

void bomb_effect()
{
	if (gameGrid[bomb_2[3][1]][bomb_2[3][0]] != 0)
		if (gameGrid[bomb_2[3][1]][bomb_2[3][0]] == gameGrid[bomb_2[3][1]+1][bomb_2[3][0]])   //same color
			for (int i=0; i<M; ++i)
				for (int j=0; j<N; ++j)
					gameGrid[i][j] = 0;   //assigns 0 to whole grid
			
		else if ((gameGrid[bomb_2[3][1]][bomb_2[3][0]] != gameGrid[bomb_2[3][1]+2][bomb_2[3][0]])&&(bomb_2[3][1] < M-1))   //diferent color
		{	
			gameGrid[bomb_2[3][1]][bomb_2[3][0]] = 0;
			gameGrid[bomb_2[3][1]+1][bomb_2[3][0]] = 0;
			gameGrid[bomb_2[3][1]-1][bomb_2[3][0]] = 0;
			gameGrid[bomb_2[3][1]][bomb_2[3][0]-1] = 0;
			gameGrid[bomb_2[3][1]+1][bomb_2[3][0]-1] = 0;
			gameGrid[bomb_2[3][1]-1][bomb_2[3][0]-1] = 0;
			gameGrid[bomb_2[3][1]][bomb_2[3][0]+1] = 0;
			gameGrid[bomb_2[3][1]+1][bomb_2[3][0]+1] = 0;
			gameGrid[bomb_2[3][1]-1][bomb_2[3][0]+1] = 0;
			
			for (int i=bomb_2[3][1]+1; i>4; --i)
			{
				for (int j=bomb_2[3][0]-1; j<bomb_2[3][0]+1; ++j)
				{
					gameGrid[i][j] = gameGrid[i-4][j];
				}
			}
		}
			
		else if (bomb_2[3][1] >= M-1)   //falls on grid edge
			for (int i=0; i<4; ++i)
				gameGrid[bomb_2[i][1]][bomb_2[i][0]] = 0;	
}


//------------------------------------------------------------
//FUNCTION FOR THE BOMB TO FALL

void falling_bomb(float& timer, float& delay, bool& bomb1, bool& bomb_done, int& colorNum)
{
	if (bomb1)
	{
		if (timer>delay){			
		    for (int i=0;i<4;i++){
		        bomb_2[i][0]=bomb_1[i][0];
		        bomb_2[i][1]=bomb_1[i][1];
		        bomb_1[i][1]+=1;                   //How much units downward
		    }
		    
		    if (!bomb_anamoly(bomb1)){
		        
		        for(int i=0; i<4; ++i)
		            gameGrid[bomb_2[i][1]][bomb_2[i][0]] = colorNum;
		            
		        bomb_effect();   //calls for effects after placement of bomb
		        bomb1=0;   //bomb flag is 0
				bomb_done=1;   //now bomb never occurs again
				for (int i=0; i<4; ++i)
					for (int j=0; j<2; ++j)
					{
						bomb_1[i][j]=0;
						bomb_2[i][j]=0;
					}
		    }
		    timer=0;
		}
	}
}


//------------------------------------------------------------
//FUNCTION TO DROP THE BOMB USING SPACE BAR

void drop_bomb(bool& space)
{	
	if (space)
		for (int i=0; i<4; ++i)
		{
			bomb_1[i][1]=shadow_1[i][1];
			bomb_2[i][1]=shadow_2[i][1];
		}
	space=0;
}


//------------------------------------------------------------
//FUNCTION FOR GAME OVER AND STORE SCORE TO highscore.txt

bool game_over(int& score)
{
	if (gameGrid[point_1[3][1]][point_1[3][0]] != 0)
	{
		ofstream file("highscore.txt", ios::app);   //append file
		file<<to_string(score)<<endl;   //add score
		file.close();   //close file
		return 1;
	}
	
	return 0;
}


//------------------------------------------------------------
//FUNCTION FOR BUBBLE SORT IN DECENDING ORDER

void sort(int arr[], int size)
{
	int temp=0;
	for (int i=0; i<size-1; ++i)
		for (int j=0; j<size-i-1; ++j)
			if (arr[j]<arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
}

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
