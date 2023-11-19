

class Character
{
    public:
	    int HP;
		int posx;
        bool left;
        bool right;
   	    bool walking;
   	    int mPosX, mPosY;
   	    
   	    int frame;
		//The dimensions of the dot
		static const int Character_WIDTH = 20;
		static const int Character_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int Character_VEL = 6;

		//Initializes the variables
		Character();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e ,SDL_Rect& wall);

		//Moves the dot and checks collision
		void move( SDL_Rect& wall );

		//Shows the dot on the screen
		void render();
		void loadCharacter();
		bool defensepic;

        friend class Enemy;
		//friend void Enemy::moveEnemy(const Character&);
		void operator !(){
		//	cout << "John HP = " << this->HP << endl; 
		}
		void operator -(){cout << "John frame = " << this->frame << endl; }
		void operator +(){cout << "John walking = " << this->walking << endl; }
    private:
		int mVelX, mVelY;
		int mG;
		int aY;
		//Dot's collision box
		SDL_Rect mCollider;
		LTexture CharTexture;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		int mWidth;
        int mHeight;
        SDL_Rect gSpriteClips[5];
        SDL_Rect* currentClip;

        enum Weapons{
        	Weapon1, Wepaon2, Weapon3
        };
};
 
Character::Character()
{
	walking=0;
	left=0;
	right=0;
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;
	//Set collision box dimension
	mCollider.w = Character_WIDTH;
	mCollider.h = Character_HEIGHT;
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
	
    mG=1;
    aY=0;
    HP=100;
    defensepic = 0;
    frame = 0;
}

void Character::handleEvent( SDL_Event& e,SDL_Rect& wall)
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w:{
            	if(!defensepic){	       			
					if((wall.y-mPosY)<=200){
						mVelY -= 50;
					}					
				}
				break;
			}
            
            case SDLK_a: {
            	if(!defensepic){
            		mVelX -= Character_VEL;					
					if(mPosX>10&&scrollingOffset<=-10){						
						left=1;
					}
					walking = 1;
					flip = SDL_FLIP_HORIZONTAL;
				}
				break;
			}

            case SDLK_d:{
            	if(!defensepic){
					mVelX += Character_VEL;					
					right=1;
					walking = 1;
					flip = SDL_FLIP_NONE;
				}
				break;
			}
			case SDLK_s:{
				this->defensepic=1;
				break;
			}
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w:{
				break;
			}
            case SDLK_a:{
            	if(!defensepic){
	          	    mVelX += Character_VEL;
	          	    walking =0;
	          	    left=0;
	          	}
				break;
			}
            case SDLK_d:{
            	if(!defensepic){
	            	mVelX -= Character_VEL;
	            	walking =0;
	            	right=0;
	            }
				break;
			}
            case SDLK_s:{
				this->defensepic=0;
				break;
			}
        }
    }
}

void Character::move( SDL_Rect& wall )
{
    //Move the Character left or right
	mPosX += mVelX;
	mCollider.x = mPosX;
	posx = mPosX;
    //If the Character collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + Character_WIDTH +600> SCREEN_WIDTH ) || checkCollision( mCollider, wall ) )
    {
        //Move back
        mPosX -= mVelX;
		mCollider.x = mPosX;
    }

    //Move the Character up or down
	mVelY+=aY;
	mPosY += mVelY;
	mCollider.y = mPosY;

    //If the Character collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + Character_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mCollider, wall ) )
    {
        //Move back
        if(checkCollision( mCollider, wall )){
            mPosY -= mVelY;
            mCollider.y = mPosY;
        }
        else{
            //mVelY=-mVelY;
            mVelY=0;
            mPosY+=10;
        }
    }
    else{
  		  mVelY+=mG;
	}
}

void Character::render()
{
    currentClip = &gSpriteClips[ frame / 4 ];
	CharTexture.render( mPosX, mPosY, currentClip, NULL , NULL, flip);
}

void Character::loadCharacter()
{
    CharTexture.loadFromFile( "./img/John.png");

    gSpriteClips[ 0 ].x =   0;
    gSpriteClips[ 0 ].y =   0;
    gSpriteClips[ 0 ].w =  138;
    gSpriteClips[ 0 ].h = 192;

    gSpriteClips[ 1 ].x =  138;
    gSpriteClips[ 1 ].y =   0;
    gSpriteClips[ 1 ].w =  130;
    gSpriteClips[ 1 ].h = 192;

    gSpriteClips[ 2 ].x = 268;
    gSpriteClips[ 2 ].y =   0;
    gSpriteClips[ 2 ].w =  140;
    gSpriteClips[ 2 ].h = 192;

    gSpriteClips[ 3 ].x =   408;
    gSpriteClips[ 3 ].y =   0;
    gSpriteClips[ 3 ].w =   140;
    gSpriteClips[ 3 ].h = 192;

    gSpriteClips[ 4 ].x = 548;
    gSpriteClips[ 4 ].y =   0;
    gSpriteClips[ 4 ].w =   142;
    gSpriteClips[ 4 ].h = 192;
}
