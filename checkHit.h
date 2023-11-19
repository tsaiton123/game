
#include"enemy.h"


bool checkHitJohn( Bullet* , Character& );
bool checkHitEnemy( Bullet* ,Enemy* );

bool checkHitJohn( Bullet* bullet , Character &Char )
{
	//cout << Char.mPosX;
	bool hit = true;
    //acout << "check hit" << endl;
    if( bullet->bPosX < Char.mPosX){
    	hit = false;
	}
	if( bullet->bPosX > Char.mPosX + 32){
    	hit = false;
	}
	if( bullet->bPosY < Char.mPosY){
    	hit = false;
	}
	if( bullet->bPosY > Char.mPosY + 205){
    	hit = false;
	}
    
	if(hit){
		Char.HP -= 5;
		!Char;
	//	cout << "hit john" << endl;
		if( Char.defensepic == 1){
			Char.HP += 5;
		}
	}
    return hit;
}

bool checkHitEnemy( Bullet* bb , Enemy* current )
{   
	bool hit = true;	
    if( bb->get_bPosX() < current->PosX){
    	hit = false;
	}
	if( bb->get_bPosX() > current->PosX + 64){
    	hit = false;
	}
	if( bb->get_bPosY() < current->PosY){
    	hit = false;
	}
	if( bb->get_bPosY() > current->PosY + 120){
    	hit = false;
	}
    
	if(hit){			
	//	cout << "hit" << endl;
	}

    return hit;
}

