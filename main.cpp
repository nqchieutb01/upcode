#include <SDL.h>
#include<SDL_image.h>
#include<stdio.h>
#include<bits/stdc++.h>
#include<SDL_ttf.h>
#include "var.h"
using namespace std;
LTexture* currentTexture = NULL;
LTexture gPressTexture;
LTexture gUpTexture;
LTexture gDownTexture;
LTexture gLeftTexture;
LTexture gRightTexture;
//---------------------------------------------------------------------------------------//
void init()
{
    gWindow = SDL_CreateWindow("MyGame",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) ;
    gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gRenderer,0, 0xFF, 0xFF, 0xFF) ;
    //TTF_Init() ;
    IMG_Init(IMG_INIT_PNG) ;
}
bool loadMedia()
{

    gUpTexture.LoadFromFile("img/up.bmp")  ;
    gDownTexture.LoadFromFile("img/down.bmp")  ;
    gLeftTexture.LoadFromFile("img/left.bmp")  ;
    gRightTexture.LoadFromFile("img/right.bmp")  ;
    gPressTexture.LoadFromFile("img/press.bmp") ;
  //  ..SDL_Color  textColor = {0,0,0} ;
   // gTextureText.LoadFromRenderedText("xin chao ae ae co khoe ko" , textColor) ;
   		for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
		{
			gSpriteClips[ i ].x = 0;
			gSpriteClips[ i ].y = i * 200;
			gSpriteClips[ i ].w = BUTTON_WIDTH;
			gSpriteClips[ i ].h = BUTTON_HEIGHT;
		}

		//Set buttons in corners
		gButtons[ 0 ].setPosition( 0, 0 );
		gButtons[ 1 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, 0 );
		gButtons[ 2 ].setPosition( 0, SCREEN_HEIGHT - BUTTON_HEIGHT );
		gButtons[ 3 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT );
    return true ;
}
void close(){
    gButtonSpriteSheetTexture.free() ;
    TTF_CloseFont( gFont );
    gFont = NULL;

    SDL_DestroyTexture( gTexture );
    gTexture = NULL ;
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;

    SDL_Quit();
    IMG_Quit() ;
}

int main( int argc, char* args[] )
{
        init() ;
        bool quit = false;
        SDL_Event e ;
        Uint8 r=255,g=255,b=255 ;
        Uint8 a = 255 ;
        double degrees = 0 ;

        loadMedia() ;

        while(!quit)
        {
            while(SDL_PollEvent(&e) !=0){
                if(e.type==SDL_QUIT){
                    quit = true ;
                }
            }
                const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
                if( currentKeyStates[ SDL_SCANCODE_UP ] )
                {
                    currentTexture = &gUpTexture;
                }
                else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
                {
                    currentTexture = &gDownTexture;
                }
                else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
                {
                    currentTexture = &gLeftTexture;
                }
                else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
                {
                    currentTexture = &gRightTexture;
                }
                else
                {
                    currentTexture = &gPressTexture;
                }
            SDL_SetRenderDrawColor(gRenderer,255,255,255,255) ;
            SDL_RenderClear(gRenderer) ;

            currentTexture->render(0,0) ;

            SDL_RenderPresent(gRenderer) ;
        }

        close();
       return 0;
}
