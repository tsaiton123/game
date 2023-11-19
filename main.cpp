/*
How to Play

press mouse left button to shoot
press mouse Right button to reload

*/

//Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

//Bullet for the Main Character
//the start bullet of the main character every time the screen renders
int mBulletStart = 0;
//the end bullet of the main character every time the screen renders
int mBulletEnd = 0;
//the id of bullet for the main character when the screen is rendering
int mBulletId;

//Bullet for Enemies
//the start bullet of the Enemies every time the screen renders
int eBulletStart = 0;
//the end bullet of the Enemies every time the screen renders
int eBulletEnd = 0;
//the id of bullet for the Enemies when the screen is rendering
int eBulletId;


//1 pistol , 2 rifle , 3 sniper
//initial type pistol
int GunType = 1; 
int dead = 0;


int scrollingOffset = 0;
int scrollingOffset2 = 0;
const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//Do not change the sequence of included header files
#include "texture.h"
LTexture gBackgroundTexture;
LTexture gBGTexture;
LTexture endingCover;
LTexture bBulletTexture;
LTexture rBulletTexture;
LTexture LoadingTexture; 
LTexture gTextTexture; 


LTexture pistolTexture;
LTexture rifleTexture;
LTexture sniperTexture;
#include "SFX.h"
#include "Timer.h"
#include "init.h"
#include "character.h"

#include "text.h"
#include "Bullet.h"
Bullet* mbulletOne = new Bullet(1);
Bullet* ebulletOne = new Bullet(2);

#include "streamText.h"        
#include "Weapon.h"
#include "enemy.h"
#include "checkHit.h"
#include "time.h"
//Do not change the sequence of included header files

enum gameState{
    Menu,
    Playing,
    End
};

int main( int argc, char* args[] )
{	
	
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
        //Main loop flag
        
	
	
	//Clear screen
	    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	    SDL_RenderClear( gRenderer );
	    if( !LoadingTexture.loadFromFile( "./img/Loading.png" ) )
		{
			printf( "Failed to initialize!\n" );
		} 		
		
		Start:
        bool quit = false;
        SDL_Event e;
        Mixer();
        srand(time(NULL));
        gameState gamingState = Menu;
        std::stringstream pointStream;
        std::stringstream walkingLength;
		walkingLength.str("");
        //Load background
        
        
        bBulletTexture.loadFromFile( "./img/bullet.png");
        bBulletTexture.setHeight(15);
        bBulletTexture.setWidth(15);
        endingCover.loadFromFile( "./img/endingCover.png");
        endingCover.setWidth(1200);
        endingCover.setAlpha(200);
        
        
        gBGTexture.loadFromFile( "./img/bgground.png" );
        gBackgroundTexture.loadFromFile( "./img/bgcloud.png" );
        pistolTexture.loadFromFile( "./img/pistol.png" );
		rifleTexture.loadFromFile( "./img/rifle.png" );
		sniperTexture.loadFromFile( "./img/sniper.png" );
        
		///Weapon should be created in main character at the end
        Weapon Pistol(1);
        Weapon Rifle(2);
        Weapon Sniper(3);
        
        
        Character John;
        John.loadCharacter();
        Character Mary = John;
        
        SDL_Rect wall = {0, 540, 1080, 40};

        Enemy* first = NULL;
        first = new Enemy;
        
        
        mbulletOne->loadBullet();
        ebulletOne->loadBullet();
        
        Enemy* firstEnemy = NULL;
        firstEnemy = new Enemy;
        //initializing streamtext
        streamText points("./fonts/Gobold Regular.otf","Points ", 25, {255, 255, 255});
        streamText pistol_bullet("./fonts/Gobold Regular.otf","Pistol Bullets ", 25, {255, 255, 255});
        streamText rifle_bullet("./fonts/Gobold Regular.otf", "Rifle  Bullets ", 25, {255, 255, 255});
        streamText sniper_bullet("./fonts/Gobold Regular.otf","Sniper Bullets ", 25, {255, 255, 255});
        streamText pistol_total("./fonts/Gobold Regular.otf"," / ", 25, {255, 255, 255});
        streamText rifle_total("./fonts/Gobold Regular.otf", " / ", 25, {255, 255, 255});
        streamText sniper_total("./fonts/Gobold Regular.otf"," / ", 25, {255, 255, 255});
        streamText HP("./fonts/Gobold Regular.otf"," HP ", 25, {255, 255, 255});
        Text reloading("./fonts/Gobold Regular.otf"," RELOADING ", 50, {255,0 , 0});
        

        //While application is running
        while( !quit )
        {	
        	///Menu Done
            if(gamingState == Menu){
                Text clickToStart("./fonts/CHICKEN Pie Height.ttf", "Click To Start", 35, {0, 0, 0});
                Text littleCS("./fonts/CHICKEN Pie Height.ttf", "Little  CS", 100, {51, 25, 0});
                Text littleCS2("./fonts/CHICKEN Pie Height.ttf", "Little  CS", 100, {97, 54, 12});
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_MOUSEBUTTONDOWN){
                        gamingState = Playing;
                    }
                }
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                gBGTexture.render(0, 0);
                littleCS.renderText(230, 180);
                littleCS2.renderText(235, 185);
                clickToStart.renderText(430, 350);
                SDL_RenderPresent( gRenderer );
				Weapon::Points = 50;
            }
        
        	if(John.HP <= 0){
        		gamingState = End;
        		Weapon::Points = 50;
			}
			///In the Game
			
			if(gamingState == Playing){
				
				
	            while( SDL_PollEvent( &e ) != 0 )
	            {
	                //User requests quit
	                if( e.type == SDL_QUIT )
	                {
	                    quit = true;
	                }
	                GunType = GunSwitch(e);
	                if( GunType == 1){
	                	Pistol.handleEvent(e, John);                	
					}else if( GunType == 2){
	                	Rifle.handleEvent(e, John);                	
					}else if( GunType == 3){
	                	Sniper.handleEvent(e, John);                	
					}
	                //Handle input for the shooting
	                John.handleEvent( e ,wall);                 
	            }
				
	            John.move( wall );
	            
	            attackEnemy(first, John);
                createEnemy(first);
                moveEnemy(first, John);
	
	            if(John.right == 1){
	                scrollingOffset -=John.Character_VEL;
	                John.walking = 1;
	            }
	            if(John.left==1&&scrollingOffset<=-10&&John.posx>10){
	                scrollingOffset +=John.Character_VEL;
	                John.walking = 1;
	            } 
	            if( scrollingOffset < -gBGTexture.getWidth() ){
	                scrollingOffset = 0;
	            }
	            --scrollingOffset2;
	            if( scrollingOffset2 < -gBackgroundTexture.getWidth() )
	            {
	                scrollingOffset2 = 0;
	            }
	            //input text
                points << Weapon::Points;
                
				if( GunType == 1){
	            	pistol_bullet << Pistol.get_bullet();
					pistol_total << Pistol.get_total();     	
				}else if( GunType == 2){
	                rifle_bullet << Rifle.get_bullet();
					rifle_total << Rifle.get_total();                 	
				}else if( GunType == 3){
	            	sniper_bullet << Sniper.get_bullet();
					sniper_total << Sniper.get_total();            	
				}
				HP << John.HP;       
                
	            //Clear screen
	            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	            SDL_RenderClear( gRenderer );	
				
	            gBGTexture.render( scrollingOffset, 0 );
	            gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );	
	            gBackgroundTexture.render( scrollingOffset2, 0 );
	            gBackgroundTexture.render( scrollingOffset2 + gBackgroundTexture.getWidth(), 0 );
		 	
		 		
				if( GunType == 1){
	            	pistolTexture.render( 0, 50 );             	
				}else if( GunType == 2){
	                rifleTexture.render( 0, 50 );                 	
				}else if( GunType == 3){
	            	sniperTexture.render( 0, 50 );                  	
				}
				int temp = 0;
		
				Enemy* current = first;
				Bullet* mcurrentBullet = mbulletOne;
			
	            for( mBulletId = mBulletStart; mBulletId < mBulletEnd; mBulletId++){
					while(current != NULL){
						if(checkHitEnemy( mbulletOne, current) ){
							int damage;
							if( GunType == 1){
				            	damage = Pistol.damage; 
								Pistol();              	
							}else if( GunType == 2){
				            	damage = Rifle.damage; 
								Rifle();              	
							}else if( GunType == 3){
				            	damage = Sniper.damage; 
								Sniper();              	
							}
							
							current->HP -= damage;
							temp++;	
							//bullet disappear operator							
							*mcurrentBullet%1;
						}
						current = current->nextEnemy;
						
					}	
					mcurrentBullet->renderBullet();
					//bullet of main character flying operator
					*mcurrentBullet>1;
					mBulletStart += temp;
	            }
	            /*	*/
	            temp = 0;
				current = first;
				while(current != NULL){				
					if(current->HP <= 0 ){
						temp++;				
						current->PosX = -1000;
						current->PosY = -1000;
						
					}					
					current = current->nextEnemy;
				}
				Weapon::Points += 50*(temp-dead);
				dead = temp;
				
				Bullet* ecurrentBullet = ebulletOne;
				temp = 0;
	            for( eBulletId = eBulletStart; eBulletId < eBulletEnd; eBulletId++){	
						ecurrentBullet->flyBullet();					
						if( checkHitJohn( ecurrentBullet, John) ){
							temp++;						
						}
						ecurrentBullet->renderBullet();
	            }
	            eBulletStart += temp;
	            SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
	            	
	            John.render();
	            
	            renderEnemy(first);
	            //text rendering
                points.renderText(200, 0);
                
                if( GunType == 1){
	            	pistol_bullet.renderText( 200, 50 );
					pistol_total.renderText( 420, 50 );               	
				}else if( GunType == 2){
	                rifle_bullet.renderText( 200, 50  ); 
					rifle_total.renderText( 420, 50  );                	
				}else if( GunType == 3){
	            	sniper_bullet.renderText( 200, 50  ); 
					sniper_total.renderText( 420, 50  );                  	
				}
				HP.renderText( 700, 0);
				
				if(Weapon::reloading){
					reloading.renderText(400, 200);
				}
	
	            SDL_RenderPresent( gRenderer );
	
	            //Go to next frame
	            if(John.defensepic==0){
	                if(John.walking==1){
	                    John.frame++;
	                }
	                if( John.frame / 4 >= 4 ){
	                    John.frame = 0;
	                }
	            }else{
	                John.frame=19;
	            }
	            
	            	while(mbulletOne->nextBullet != NULL){
						deleteBullet(mbulletOne);
					}
					while(ebulletOne->nextBullet != NULL){
						deleteBullet(ebulletOne);
					}
	            
	        }
	        if(gamingState == End){
	        	closeAllEnemy(first);
                endingCover.render(0, 0);
                Text Continue("./fonts/CHICKEN Pie Height.ttf", "Continue? Y/N", 80, {255, 255, 255, 0});
                Continue.renderText(450, 400);
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.key.keysym.sym ==  SDLK_y)
                    {
                        goto Start;
                    }
                    if( e.key.keysym.sym ==  SDLK_n)
                    {
                        quit = true;
                    }
                }
				Text grade("./fonts/CHICKEN Pie Height.ttf", checkGrade(Weapon::Points), 400, {255, 255, 255, 0});
				grade.renderText(110, 45);
				
                SDL_RenderPresent( gRenderer );
                
                GunType = 1;
                
                
			}//end of game end if
			
		}//end of while loop
		
	}
	
	//Free resources and close SDL
	close();
	

	
	return 0;
}
