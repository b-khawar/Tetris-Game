/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <sstream>
#include <fstream>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
//bool shapes[100]={0};
int main(){
	
	Font font;
  	font.loadFromFile("img/TIMESR.ttf");   //load font
	
	Music music;
    music.openFromFile("img/music.flac");   //load music
   	music.play();
    
	int score_arr[100]={0};   //array that stores high scores
	bool exit=0;
    srand(time(0));
    
    Texture MBG;
    MBG.loadFromFile("img/menu.jpg");
    Sprite menu_background(MBG);
    RenderWindow menu(VideoMode(320, 480), title);   //window for menu
    
    while (menu.isOpen())
    {
    	if (Keyboard::isKeyPressed(Keyboard::Enter))   //play game
    		menu.close();
    	else if (Keyboard::isKeyPressed(Keyboard::H))   //open help
    	{
    		menu.close();
    		Texture HBG;
    		HBG.loadFromFile("img/help.jpg");
    		Sprite help_background(HBG);
    		RenderWindow help(VideoMode(320, 480), title);   //window for help
    		
    		while (help.isOpen())
    		{
    			if (Keyboard::isKeyPressed(Keyboard::P))   //play game
    			{
    				help.close();
    			}
    			help.clear(Color::Black);
    			help.draw(help_background);
    			help.display();
    		}
    	}
    	else if (Keyboard::isKeyPressed(Keyboard::S))   // S is pressed to see high scores
    	{
    		menu.close();
    		int x=0;
    		string xyz=" ";
    		
    		ifstream file("highscore.txt");
    		while (getline(file,xyz))
    		{
    			score_arr[x] = stoi(xyz);
    			x += 1;
    		}
    		file.close();
    		sort(score_arr, 100);
    		
    		Texture HSBG;
   			HSBG.loadFromFile("img/score.jpg");
    		Sprite score_background(HSBG);
    		RenderWindow score_window(VideoMode(320, 480), title);   //window for highscore
    		
    		while (score_window.isOpen())
    		{
				score_window.clear(Color::Black);
				score_window.draw(score_background);
				
				Text score_1(std::string("Score: " + std::to_string(score_arr[0])), font, 30);
				score_1.setFillColor(sf::Color::White);
				score_1.setPosition(100.f,65.f);
				score_1.move(5.f,65.f);
				score_window.draw(score_1);
					
				Text score_2(std::string("Score: " + std::to_string(score_arr[1])), font, 30);
				score_2.setFillColor(sf::Color::White);
				score_2.setPosition(100.f,65.f);
				score_2.move(5.f,115.f);
				score_window.draw(score_2);
				
				Text score_3(std::string("Score: " + std::to_string(score_arr[2])), font, 30);
				score_3.setFillColor(sf::Color::White);
				score_3.setPosition(100.f,65.f);
				score_3.move(5.f,165.f);
				score_window.draw(score_3);
				
				if (Keyboard::isKeyPressed(Keyboard::P))   //play game
    			{
    				score_window.close();
    			}
    			
    			score_window.display();
    			
    		}
    	}
  		else if (Keyboard::isKeyPressed(Keyboard::E))   //exit game
  		{
  			menu.close();
  			exit=1;
  		}
    	menu.clear(Color::Black);
    	menu.draw(menu_background);
    	menu.display();
    }
    	
    RenderWindow window(VideoMode(320, 480), title);   //window for game
    Texture obj1, obj2, obj3, obj4, obj5;
    
    
	
//    Load "frames.png","tiles.png" and "background.png" for Texture objects
    
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/shadow.png");
    obj5.loadFromFile("img/tiles.png");
   
    
    Sprite sprite(obj1), background(obj2), frame(obj3), shadow(obj4), bomb(obj5);
    
    
    int delta_x=0;
    int colorNum=1, score=0;
    float timer=0, delay=0.1;
    bool rotate=0, space=0;
    bool bomb1=0, bomb_done=0;

    Clock clock;
    Rand_bomb();   //so that bomb falls from random position
    
    
    while (window.isOpen()){
    	
    	if (exit)   //exit game
    		window.close();
    	    	
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;


        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                       //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))        //Just another way to detect key presses without event listener
        	delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
		if (Keyboard::isKeyPressed(Keyboard::Space))       //If SPACE Key is pressed
			space = 1;
		if (Keyboard::isKeyPressed(Keyboard::B))           //If B Key is pressed
			if (bomb_done == 0)
				bomb1 = 1;
	
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        
        
                                                           //Example: fallingPiece() function is called here
        
        if (bomb1)
        {
        	falling_bomb(timer, delay, bomb1, bomb_done, colorNum);   //falling of bomb
        	make_shadow(bomb_1);                                      //shadow of bomb
        	drop_bomb(space);                                         //drop bomb
        }
        else
        {
        	Move_Horizontal(delta_x);                                 //horizontal movement of piece
        	fallingPiece(timer, delay, colorNum);                     //falling of the block
        	make_shadow(point_1);                                     //shadow of piece
        	drop_peice(space);                                        //drop piece
        }
        Row_Check(score);                                             //To check if a row is completed? if yes, the row will be finished
        Rotate(rotate);                                               //rotation of piece
        if (game_over(score))                                         //game over
        {
        	window.close();
    		Texture GOBG;
    		GOBG.loadFromFile("img/gameover.jpg");
    		Sprite gameover_background(GOBG);
    		RenderWindow GameOver(VideoMode(320, 480), title);   //window for game over
    		while (GameOver.isOpen())
    		{
    			if (Keyboard::isKeyPressed(Keyboard::E))           //If E Key is pressed to exit
					GameOver.close();
				
				GameOver.clear(Color::Black);
				GameOver.draw(gameover_background);
				GameOver.display();
    		}
        }
        
        
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////


        window.clear(Color::Black);
        window.draw(background);
        
        
		
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
        
        //DRAW SHADOW
        for (int i=0; i<4; i++){
            shadow.setTextureRect(IntRect(colorNum*18,0,18,18));
            shadow.setPosition(shadow_1[i][0]*18,shadow_1[i][1]*18);
            shadow.move(28,31);
            window.draw(shadow);
          }
          
        //DRAW BOMB
        if (bomb1)
        {
			for (int i=0; i<4; i++){
				bomb.setTextureRect(IntRect(colorNum*18,0,18,18));
				bomb.setPosition(bomb_1[i][0]*18,bomb_1[i][1]*18);
				bomb.move(28,31);
				window.draw(bomb);
			  }
        }
        
        
        delay = 0.3;   //---Delay is reset to its intitial value so that block falls faster only when DOWN KEY is pressed
        
        //---The Final on Which Everything is Drawn Over is Loaded---//
        
        window.draw(frame);
        
		
  		//DISPLAY SCORE
		Text score_text(std::string("Score: " + std::to_string(score)), font, 20);
		score_text.setFillColor(sf::Color::White);
		score_text.setPosition(138.f,65.f);
		score_text.move(85.f,65.f);
		window.draw(score_text);
		
		
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
       
    return 0;
}
