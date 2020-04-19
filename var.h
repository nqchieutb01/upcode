#include <iostream>
#include "texture.h"
using namespace std ;
const int SCREEN_WIDTH  = 640 ;
const int SCREEN_HEIGHT   = 480;
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;
enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

SDL_Window* gWindow = NULL ;
SDL_Texture* gTexture = NULL;
SDL_Renderer* gRenderer = NULL ;
TTF_Font *gFont = NULL ;

class LTexture{
    public:
             LTexture() ;
             ~LTexture() ;
             bool LoadFromFile(std::string path) ;
             void free() ;
             void render(int x,int y,SDL_Rect *clip = NULL,double angle=0.0 , SDL_Point* center = NULL , SDL_RendererFlip flip = SDL_FLIP_NONE) ;
             int getWidth() ;
             int getHeight() ;
             void setColor(Uint8 r,Uint8 g,Uint8 b) ;
             void SetBlendMode(SDL_BlendMode blending) ;
             void SetAlpha(Uint8 alpha){
                 SDL_SetTextureAlphaMod(mTexture,alpha) ;
             }
             bool LoadFromRenderedText(std::string TextureText,SDL_Color textColor );
    private:
        SDL_Texture* mTexture ;
        int mWidth , mHeight ;

};
LTexture::LTexture(){
      mTexture = NULL ;
      mWidth = 0 ;
      mHeight = 0;
}
LTexture::~LTexture(){
    free() ;
}
int LTexture::getHeight(){
return mHeight ;
}
int  LTexture::getWidth(){
return mWidth ;
}
void LTexture::SetBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture , blending) ;
}

void LTexture::setColor(Uint8 r,Uint8 g,Uint8 b)
{
    SDL_SetTextureColorMod(mTexture,r,g,b) ;
}
bool LTexture::LoadFromFile( std::string path )
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    SDL_FreeSurface( loadedSurface );


	mTexture = newTexture;
	return mTexture != NULL;
}
void LTexture::free()
{
    SDL_DestroyTexture(mTexture) ;
    mTexture= NULL ;
    mWidth = 0 ; mHeight = 0 ;
}
void LTexture::render(int x,int y,SDL_Rect *clip , double angle , SDL_Point* center , SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x,y,mWidth,mHeight} ;
   // renderQuad.h = clip->h ;
  //  renderQuad.w = clip->w ;
    SDL_RenderCopyEx(gRenderer , mTexture , clip, &renderQuad , angle,center,flip) ;
}
bool LTexture::LoadFromRenderedText(string TextureText ,SDL_Color textColor)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont , TextureText.c_str() , textColor) ;
    mTexture = SDL_CreateTextureFromSurface(gRenderer,textSurface) ;
    mWidth  = textSurface ->w ;
    mHeight = textSurface ->h ;
    SDL_FreeSurface(textSurface) ;
    return true ;
}


class LButton{

   public :
       LButton() ;
       void setPosition(int x,int y) ;
       void handleEvent(SDL_Event* e) ;
       void render() ;
   private :
    SDL_Point mPosition ;
    LButtonSprite mCurrentSprite ;

};
LButton::LButton()
{
    mPosition.x = 0 ;
    mPosition.y = 0 ;
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT ;
}
void LButton::setPosition(int x, int y)
{
    mPosition.x = x ;
    mPosition.y = y ;
}
void LButton::handleEvent(SDL_Event* e)
{
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type ==SDL_MOUSEBUTTONUP)
    {
        int x,y ;
        SDL_GetMouseState(&x , &y) ;

        bool inside = true ;
        if(x< mPosition.x) inside = false ;
        else if( x> mPosition.x + BUTTON_WIDTH ) inside = false ;
        else if( y< mPosition.y) inside = false ;
        else if( y > mPosition.y + BUTTON_HEIGHT) inside = false ;

        if(!inside) mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT ;
        else
        {
            switch (e->type)
            {
                case SDL_MOUSEMOTION :
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION ;
                    break ;
                case SDL_MOUSEBUTTONDOWN :
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN ;
                    break ;
                case SDL_MOUSEBUTTONUP :
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_UP ;
                    break ;
            }
        }
    }
}
LTexture  gTextureText,gButtonSpriteSheetTexture ;
LButton gButtons[4] ;
SDL_Rect gSpriteClips[4] ;
void LButton::render()
{
    gButtonSpriteSheetTexture.render(mPosition.x , mPosition.y , &gSpriteClips[mCurrentSprite]) ;
}


