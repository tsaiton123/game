#ifndef LENEMY
#define LENEMY

class largeEnemy : public Enemy
{
public:
    largeEnemy();
    ~largeEnemy();

    largeEnemy* nextEnemy;
};

largeEnemy::largeEnemy() : Enemy()
{
    VelX = 10;
    VelY = 10;
    HP = 150;
    EnemyTexture = LTexture();
    EnemyTexture.loadFromFile( "./img/Lenemy.png");
    EnemyTexture.setHeight(200);
    EnemyTexture.setWidth(300);
    nextEnemy = NULL;
}

largeEnemy::~largeEnemy()
{
    nextEnemy = NULL;
    EnemyTexture.free();
}


#endif // LENEMY
