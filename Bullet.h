#ifndef B
#define B


#include <cmath>
#include <iostream>

using namespace std;

class Bullet{
    public:
		//The dimensions of the dot
		int b_WIDTH = 10;
		int b_HEIGHT = 10;
		
		
		Bullet( int);
		~Bullet();
		void loadBullet();
		void fire(double , double , int);
		void enemyFire( int, int, Character&);
		void flyBullet();
		void renderBullet(); 
		
		friend bool checkHitJohn( Bullet*, Character& );
		template <typename T>
	    friend void deleteEnemy(T*bulletOne);
		
		const double get_bPosX(){return bPosX;}
		const double get_bPosY(){return bPosY;}		
		void set_bPosX(double x){bPosX = x;}
		void set_bPosY(double y){bPosY = y;}
		
		LTexture BulletTexture;
		
		Bullet* nextBullet;
	
	    Bullet operator%(int);
	    void operator>(int);
		
		int bulletColor;	//black = 1	//red = 2
	private:
		double bPosX , bPosY;
		double bVelX, bVelY;
};

Bullet Bullet::operator%(int c)
{
	Bullet *b = new Bullet(1); 
	b->bPosX = -1000;
	b->bPosY = -1000;
	return *b;
}

void Bullet::operator>(int c)
{
	this->bPosX += this->bVelX;
	this->bPosY += this->bVelY;

	//If the dot went too far to the left or right
    if( ( this->bPosX < 0 ) || ( this->bPosX + this->b_WIDTH > SCREEN_WIDTH ) ){
    	*this%1;
    	return;
	}
    //If the dot went too far up or down
    if( ( this->bPosY < 0 ) || ( this->bPosY + this->b_HEIGHT > SCREEN_HEIGHT ) ){
    	*this%1;
		return;
	}
	
	return;
}

Bullet::Bullet(int color = 1)
{
    //Initialize the velocity
    bPosX = -100;
	bPosY = -100;
    bVelX = 0;
    bVelY = 0;
    nextBullet = NULL;
    BulletTexture = LTexture();
    bulletColor = color;
}

Bullet::~Bullet(){
	BulletTexture.free();
}

void Bullet::loadBullet()
{
	if( bulletColor == 1 ){
		BulletTexture.loadFromFile( "img/dot.png");	
	}
	if( bulletColor == 2 ){
		BulletTexture.loadFromFile( "img/dot_r.png");		
	}
	BulletTexture.setHeight(10);
    BulletTexture.setWidth(18);
}


void Bullet::fire( double startX = 10, double startY = 10, int bullet_speed = 10)
{
	//function that set variables before flying and rendering
	//set initial position
	bPosX = startX;
	bPosY = startY;
	//getting mouse pos
	int x, y;
    SDL_GetMouseState( &x, &y );
    //determine theta about Xaxis for flying
    double dx = x-bPosX-10;
    double dy = y-bPosY-10;
    double theta = atan(dx/dy);
	//determine flying speed in X and Y
    bVelX = bullet_speed *sin(theta);
    bVelY = bullet_speed *cos(theta);
	//adjusting the vector of velocity
    if( (dy ) < 0 ){
        if( (dx ) > 0 ){
            bVelY *= -1;
            bVelX *= -1;
        }
        if( (dx ) < 0 ){
            bVelX *= -1;
            bVelY *= -1;
        }
    }
}

void Bullet::enemyFire( int startX, int startY, Character &Char)
{
	//firing bullets from enemy
	bPosX =(double) startX;
	bPosY =(double) startY;

	int x = 100;
	int y = 100;
	
    double dx = Char.mPosX -bPosX-10;
    double dy = Char.mPosY -bPosY-10  +100;
    double theta = atan(dx/dy);

    bVelX = 10 *sin(theta);
    bVelY = 10 *cos(theta);

    if( (dy ) < 0 ){
        if( (dx ) > 0 ){
            bVelY *= -1;
            bVelX *= -1;
        }
    }
    if( (dy ) < 0 ){
        if( (dx ) < 0 ){
            bVelX *= -1;
            bVelY *= -1;
        }
    }
}

void Bullet::flyBullet()
{
	bPosX += bVelX;
	bPosY += bVelY;

	//If the dot went too far to the left or right
    if( ( bPosX < 0 ) || ( bPosX + b_WIDTH > SCREEN_WIDTH ) ){
    	return;
	}
    //If the dot went too far up or down
    if( ( bPosY < 0 ) || ( bPosY + b_HEIGHT > SCREEN_HEIGHT ) ){
		return;
	}
	
	return;
}

void Bullet::renderBullet()
{
	BulletTexture.render( bPosX, bPosY );	
}

template <typename T>
void deleteBullet(T* bulletOne)
{
    if(bulletOne == NULL) return;
    else{
        T* currentBullet = bulletOne;
        T* previousBullet = currentBullet;
        while(currentBullet != NULL ){
            previousBullet = currentBullet;
            currentBullet = currentBullet->nextBullet;
        }
        if(currentBullet == bulletOne){
            bulletOne = bulletOne->nextBullet;
            currentBullet->~T();
            return;
        }
        else{
            previousBullet->nextBullet = currentBullet->nextBullet;
            currentBullet->~T();
            return;
        }
    }
}

#endif // ENEMY
