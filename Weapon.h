
class Weapon
{
	public:
		Weapon(int );
		~Weapon();

		void shoot(Character&);
		Uint32 reload();	
		void buy();
		int get_bullet();
		int get_total();
		void handleEvent( SDL_Event& e, Character&);
		
		int operator()(){cout <<this->id << endl; return this->id;};
		
		static int Points;
		int damage;
		static bool reloading;
		static Uint32 rt;
		
	private:
		int id;
		int bullets;
		Uint32 reload_speed; //second per bullet
	
		const int max();
		int total = 0;
		int fly_speed;
		
		Mix_Chunk *shotFX = NULL;
		Mix_Chunk *reloadFX = NULL;
		Mix_Chunk *emptyFX = NULL;
		
		LTimer Btimer;
		Uint32 Last_Shot = 0;
		
		Uint32 now = 0;
		
		Uint32 buffer;
		
		const int pistol_max_bullets = 10;
		const int rifle_max_bullets = 30;
		const int sniper_max_bullets = 5;
};

int Weapon::Points = 50;
bool Weapon::reloading = false;
Uint32 Weapon::rt = 0; 
const int Weapon::max()
{
	if(id == 1){
		return pistol_max_bullets;
	}
	if(id == 2){
		return rifle_max_bullets;
	}
	if(id == 3){
		return sniper_max_bullets;
	}
	return 0;
}

Weapon::Weapon(int x)
{
	if(x == 1){
		id = 1;		
		bullets = max();
		reload_speed = 50;
		fly_speed = 15;
		damage = 20;
		buffer = 300;
		shotFX = Mix_LoadWAV("SFX/Pistol Shot.wav");
		reloadFX = Mix_LoadWAV("SFX/Pistol Reload.wav");
		cout << "Construct weapon : pistol" << endl;
		
	}else if(x == 2){
		id = 2;		
		bullets = 0;
		reload_speed = 15;
		fly_speed = 40;
		damage = 25;
		buffer = 100;
		shotFX = Mix_LoadWAV("SFX/Rifle Shot.wav");
		reloadFX = Mix_LoadWAV("SFX/Rifle Reload.wav");
		cout << "Construct weapon : rifle" << endl;	
		
	}else if(x == 3){
		id = 3;
		bullets = 0;
		reload_speed = 15;
		fly_speed = 50;
		damage = 50;
		buffer = 1000;
		shotFX = Mix_LoadWAV("SFX/Sniper Shot.wav");
		reloadFX = Mix_LoadWAV("SFX/Sniper Reload.wav");
		cout << "Construct weapon : sniper rifle" << endl;
			
	}else{
		cout << "Invalid input !!! \n \n" << endl;
		return;
	}
	
	emptyFX = Mix_LoadWAV("SFX/No Ammo.wav");
	cout << "ID : " << id << endl;	
	cout << "Bullets : " << bullets << endl;
	cout << "Reload speed : " << reload_speed << endl;
	cout << "Damage : " << damage << endl;
	
	Btimer.start();	
	cout << endl;	
}

int Weapon::get_bullet()
{
	return bullets;
}


int Weapon::get_total()
{
	return total;
}

void Weapon::shoot(Character &Char)
{ 
	 //checking if bullets are enough	
	if( get_bullet() <= 0){
	//	cout << "Out of bullets" << endl;
		Mix_PlayChannel( -1, emptyFX, 0 );	
		return;
	}
	//adjust variables
	
	mbulletOne->fire( Char.mPosX, Char.mPosY+100, fly_speed );
	mBulletEnd++;
	bullets--;
	Mix_PlayChannel( -1, shotFX, 0 );	
	//cout
	/*
	if(id == 1){
		cout << "Shot Pistol ! ";
	}
	if(id == 2){			
		cout << "Shot Rifle ! ";
	}
	if(id == 3){		
		cout << "Shot Sniper rifle ! ";		
	}
	*/
	//remaining
	//cout << "Remaining bullets :" << bullets;
	//cout << endl << endl;
}


Uint32 Weapon::reload()
{	
	Uint32 reload_time;
	now = Btimer.getTicks();
	if( total <= 0){
	//	cout << "Out of total bullets" << endl << endl;
		return 0;
	}
	
	if( bullets >= max() ){
	//	cout << "Already full" << endl << endl;
		return 0;
	}
	
	if( total < max() -bullets ){
		reload_time = ( total ) *reload_speed;
		bullets += total;
		total = 0;
		
	}else{
		reload_time = ( max() -bullets ) *reload_speed;
		total -= (max() -bullets );
		bullets = max();		
	}
	Mix_PlayChannel( 1, reloadFX, 0 );	
/*
	if(id == 1){		
		cout << "Reloaded Pistol ! ";					
	}
	if(id == 2){
		cout << "Reloaded Rifle ! ";		
	}
	if(id == 3){				
		cout << "Reloaded Sniper rifle ! ";		
	}
*/	
	rt = reload_time;
//	cout << rt << endl;
	return reload_time;
}

void Weapon::buy()
{
	

	if(id == 1){
		if(Points-10 < 0){
		//	cout << "Not Enough points" << endl;
			return;
		}
		Points -= 10;
	//	cout << "Total Pistol bullets : ";
	}
	if(id == 2){
		if(Points-30 < 0){
		//	cout << "Not Enough points" << endl;
			return;
		}
		Points -= 30;
	//	cout << "Total Rifle bullets : ";
	}
	if(id == 3){
		if(Points-50 < 0){
		//	cout << "Not Enough points" << endl;
			return;
		}
		Points -= 50;
	//	cout << "Total Sniper rifle bullets : ";
	}
	total += max();
//	cout << total << endl << endl;

}

Weapon::~Weapon(){

	if(id == 1){
		cout << "Destruct weapon : Pistol" << endl;
	}
	if(id == 2){
		cout << "Destruct weapon : rifle" << endl;
	}
	if(id == 3){
		cout << "Destruct weapon : sniper rifle" << endl;
	}
}


void Weapon::handleEvent( SDL_Event& e, Character& Char )
{
    //If mouse event happened
    now = Btimer.getTicks();
    
    
	if( e.type == SDL_MOUSEBUTTONDOWN  & e.button.button ==SDL_BUTTON_LEFT)
    {
		if( now < Last_Shot + buffer || Char.defensepic){
	    	
			return;
		}		
		if(rt != 0){
			if(  now < Last_Shot +2000+rt ){
			//	cout << "Reloading" << endl;
				reloading = true;
				return;
			}
			reloading = false;
    	}			
		
		
    	shoot(Char); 
    	Last_Shot = now;
    	rt = 0;
    }
	else if( e.type == SDL_MOUSEBUTTONDOWN  & e.button.button ==SDL_BUTTON_RIGHT)
    {    	
    	if( now < Last_Shot + reload() ){
    	//	cout << "Reloading" << endl;
    		reloading = true;
	    	return;
		}
		Last_Shot = now; 
		reloading = false;       
    }
    else if( e.type == SDL_KEYDOWN )
    {        
        switch( e.key.keysym.sym )
        {
            case SDLK_q:
            	buy();
            	break;
            
    	}
    }
    
}

int GunSwitch( SDL_Event &e )
{
	if(e.type == SDL_MOUSEWHEEL)
	{
		if(e.wheel.y > 0) // scroll up
        {
        	cout << "up"<< endl;
        	if(GunType == 3){
        		GunType = 1;
			}else GunType++;
        }
        else if(e.wheel.y < 0) // scroll down
        {
        	cout << "down"<< endl;
            if(GunType == 1){
        		GunType = 3;
			}else GunType--;
        }
	}
	return GunType;
}

