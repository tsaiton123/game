int Mixer(){
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
	        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
	        return 3;
	}
	
	int mflags = MIX_INIT_MP3;
	if( (Mix_Init(mflags) & mflags) != mflags ) {
	    cout << "Mix_Init: Failed to init required ogg and mod support!\n";
	    cout << "Mix_Init: %s\n" << Mix_GetError() << endl;
	    return 3;
	}
	
	
	if(Mix_OpenAudio(128000, MIX_DEFAULT_FORMAT, 2, 2048)==-1) {
	    cout << "Mix_OpenAudio: %s\n" << Mix_GetError() << endl;
	    return 3;
	}
	 
	Mix_Music *bgm;
	bgm = Mix_LoadMUS("SFX/Blinding Lights.mp3"); 
	
	if(!bgm) {
	    cout << "Mix_LoadMUS(\"song1.mp3\"): %s\n" << Mix_GetError();
	    return 3;
	}
	Mix_VolumeMusic( 40);
	Mix_PlayMusic(  bgm, -1 );
	
	return 0;
	
}


