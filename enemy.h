
#ifndef ENEMY
#define ENEMY


class Enemy
{
	public:
	    Enemy();
	    ~Enemy();
	    Enemy(const Enemy&);
	    Enemy& operator=(const Enemy&);

	    void moveEnemy(const Character &Char);
	    void renderEnemy();
	    void enemyAttack(Character &Char);
	    void enemyAttacked();
	    void enemyDead();

	    template <typename T>
	    friend void createEnemy(T* first);
	    template <typename T>
	    friend void deleteEnemy(T*first);
	    template <typename T>
	    friend void moveEnemy(T* first, const Character& Char);
	    template <typename T>
	    friend void renderEnemy(T* first);
	    template <typename T>
	    friend void attackEnemy(T* first,Character &Char);
		
		LTexture EnemyTexture;
		Enemy* nextEnemy;
		int HP;
		static int enemyKilled;
        static int enemyNumber;

	    int PosX, PosY;
	protected:
		Mix_Chunk *FX;
		int VelX, VelY;
		
};

int Enemy::enemyKilled = 0;
int Enemy::enemyNumber = 0;


Enemy::Enemy()
{
    PosX = 1050;
    PosY = 100;
    VelX = 20;
    VelY = 20;
    HP = 100;
    EnemyTexture = LTexture();
    EnemyTexture.loadFromFile( "./img/enemy.png");
    EnemyTexture.setHeight(120);
    EnemyTexture.setWidth(180);
    enemyNumber += 1;
    nextEnemy = NULL;
    FX = Mix_LoadWAV("./SFX/eShot.wav");
}
Enemy::~Enemy()
{
	nextEnemy = NULL;
    EnemyTexture.free();
}

void Enemy::enemyAttack(Character &Char)
{
    if((rand() % 150 == 0) && (PosX > 50) && (PosY < 950)){
        ebulletOne->enemyFire(PosX, PosY, Char);
        eBulletEnd++;
        Mix_PlayChannel( 2, FX, 0 );
    }
}

void Enemy::renderEnemy()
{
    EnemyTexture.render(PosX, PosY);
}
///Enemy Move to Edit
void Enemy::moveEnemy(const Character &Char)
{
    int num = 50;
    if(PosX < 0){
		PosX += VelX;
	}
	if(PosX > SCREEN_WIDTH){
		PosX -= VelX;
	}
	if(PosY > Char.mPosY+150){
		PosY -= VelY;
	}
	if(PosY < 0){
		PosY += VelY;
	}
	
	switch(rand()%num){
        case 0 : PosX -= VelX; PosY += VelY; break;
        case 1 : PosX -= VelX; PosY -= VelY; break;
        case 2 : PosX -= VelX; break;
        case 3 : PosY += VelY; break;
        case 4 : PosY -= VelY; break;
	}
}

Enemy::Enemy(const Enemy& prev)
{
    this->nextEnemy = NULL;
}

Enemy& Enemy::operator=(const Enemy& prev)
{
    this->nextEnemy = NULL;
    return *this;
}

template <typename T>
void createEnemy(T* first)
{
    if(rand() % 250 == 0){
        if(first == NULL){
            first = new T;
        }
        else{
            T* current = first;
            while(current->nextEnemy != NULL){
                current = current->nextEnemy;
            }
            current->nextEnemy = new T;
        }
    }
}

template <typename T>
void deleteEnemy(T* first)
{
    if(first == NULL) return;
    else{
        T* current = first;
        T* previous = current;
        while(current != NULL && current->HP != 0){
            previous = current;
            current = current->nextEnemy;
        }
        if(current == first){
            first = first->nextEnemy;
            current->~T();
            return;
        }
        else{
            previous->nextEnemy = current->nextEnemy;
            current->~T();
            Enemy::enemyKilled += 1;
            Enemy::enemyNumber -= 1;
            
            return;
        }
    }
}
template <typename T>
void moveEnemy(T* first, const Character& Char)
{
    if(first == NULL) return;
    else{
        Enemy* current = first;
        while(current != NULL){        
            current->moveEnemy(Char);
            current = current->nextEnemy;
        }
    }
}
template <typename T>
void attackEnemy(T* first, Character &Char)
{
    if(first == NULL) return;
    else{
        T* current = first;        
        while(current != NULL){
		/*        	
        	if(Enemy::enemyKilled < mBulletStart){
        		current = current->nextEnemy;
        		continue;
			}
		*/
            current->enemyAttack(Char);
            current = current->nextEnemy;
        }
    }
}
template <typename T>
void renderEnemy(T* first)
{
    if(first == NULL) return;
    else{
        T* current = first;
        while(current != NULL){
            current->renderEnemy();
            current = current->nextEnemy;
        }
    }
}

template <typename T>
void closeAllEnemy(T* first)
{
    if(first == NULL){
        return;
    }
    else{
        T* current = first;
        while(current != NULL){
            first = first->nextEnemy;
            current->~T();
            current = first;
        }
    }
}

#endif // ENEMY
