#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>
#include <SDL/SDL_ttf.h>
#define delta_t 10
#define width 640
#define fps 30
#define height 480
int tempsavant=0, tempsap = 0;
int frame=0;
    int continuer = 1;
    int mouvement_balle = 0;
	int up1=0,up2=0,down1=0,down2=0;
struct Joueur{
	
	int x;
	int y;
	
};
struct Balle{
	
	int x;
	int y;
	int accx;
	int accy;
	
};

typedef struct Joueur Joueur;
typedef struct Balle Balle;
SDL_Surface* joueur_1;
SDL_Surface* joueur_2;
SDL_Surface*  balle;
Balle balle_st;
Joueur joueur1;
Joueur joueur2;
void SDL_Balle() ;
void SDL_Joueur();
SDL_Rect position;
SDL_Event event;
SDL_Surface *score1;
SDL_Surface *score2;
SDL_Surface *frame_aff;
TTF_Font *police;

int score_1 = 0;
int score_2 = 0;
char buf[255];
SDL_Color blanc = {255,255,255};
int SDL_Jeu(SDL_Surface* ecran);
void pause(SDL_Surface* ecran);
void  gestion_clavier_appuie(SDL_Event *event);
void gestion_clavier_up(SDL_Event *event);
int main (int argc, char ** argv){
	
	
	//Initialisation de la SDL
	
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();		
	SDL_Surface* ecran = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
	if(ecran == NULL) { printf ("Erreur d'initialisation\n"); exit(-1);}
	SDL_WM_SetCaption("Pong ",NULL);
	
	police = TTF_OpenFont("earwigfa.ttf",35);
	if(police == NULL){ printf ("erreur police\n"); exit(-1);}
	joueur_1 = SDL_LoadBMP("barre.bmp");
	joueur_2 = SDL_LoadBMP("barre_b.bmp");
	balle = SDL_LoadBMP("balle.bmp");
	//Répétition des touches
	
	//SDL_EnableKeyRepeat(10, 10);

//On initialise les psition des joueurs et la balle
joueur1.x = 10;
joueur1.y = 200;
joueur2.x = 620;
joueur2.y = 200;

balle_st.x = 320;
balle_st.y = 240;
//on initialise l'accélération de la balle
balle_st.accx = 15;
balle_st.accy = -15;




	//boucle de jeu
	pause(ecran);

	SDL_FreeSurface(joueur_1);
	SDL_FreeSurface(joueur_2);
	SDL_FreeSurface(balle);
	
	

		SDL_FreeSurface(ecran);
		TTF_Quit();
	SDL_Quit();
	
}
void SDL_Joueur(){
	
	if(up1 & !down1 & joueur1.y >= 2) joueur1.y-=20;
	if(!up1 & down1 & joueur1.y <= 420) joueur1.y+=20;
	if(up2 & !down2  & joueur2.y >= 2) joueur2.y-=20;
	if(!up2 & down2 & joueur2.y <= 420) joueur2.y+=20;
}
void pause(SDL_Surface *ecran)
{


 
    while (continuer)
    
    {	
    	//gestion du temps
    	tempsap = SDL_GetTicks();
    	if(tempsap - tempsavant >fps){
    	frame = 1000/(tempsap -tempsavant);
    	SDL_Joueur();
    	SDL_Balle();    	
    	SDL_Jeu(ecran);    	
		tempsavant = tempsap;
	} else {
		
		SDL_Delay(fps - (tempsap - tempsavant));

	}
    	
        while(SDL_PollEvent(&event)){
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;break;
            case SDL_KEYDOWN: gestion_clavier_appuie(&event);break;
            case SDL_KEYUP: gestion_clavier_up(&event);break;
            default:break;  
        }
    }
}
}
int SDL_Jeu(SDL_Surface* ecran){
	
   	//on affichhe pas toutes les images
				
		
		//On remet à zéero le nombre de  fps
    	
	
	//on affiche les scores
	sprintf(buf,"%i",score_1);
	score1 = TTF_RenderText_Blended	(police,buf,blanc);
	sprintf(buf,"%i",score_2);
	score2 = TTF_RenderText_Blended	(police,buf,blanc);
	//on affiche le frame rate
	sprintf(buf,"FPS: %i",frame);
	frame_aff = TTF_RenderText_Blended(police,buf,blanc);
	//On efface l'écran
	SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
	
	
	//On positionne le fps
	position.x = 250;
	position.y = 20;
	SDL_BlitSurface(frame_aff,NULL,ecran,&position);
	//On positionne le joueur1 suivnat les coordonnées
	position.x = joueur1.x;
	position.y = joueur1.y;
	SDL_BlitSurface(joueur_1, NULL,ecran ,&position);
	
	
	//On ajoute le joueur2 suivnat les coordonnées
	position.x = joueur2.x;
	position.y = joueur2.y;
	SDL_BlitSurface(joueur_2, NULL,ecran ,&position);
	
	//on pose la ballle
	position.x = balle_st.x;
	position.y = balle_st.y;
	//printf("%i %i\n ",balle_st.x,balle_st.y);
	SDL_BlitSurface(balle, NULL,ecran ,&position);
	
	//On ajoute les scores
	position.x = 100;
	position.y = 20;
	SDL_BlitSurface(score1,NULL, ecran,&position);
	position.x =470;
	SDL_BlitSurface(score2,NULL, ecran,&position);
	//mise à jour de l'écran
	//on  met à jour la valeur dui nombre d'image par seconde
	
	
	
	SDL_Flip(ecran);
	
	return 0;
}
void gestion_clavier_up(SDL_Event *event){
	
	Uint8 * touches = SDL_GetKeyState(NULL);
	    if(!touches[SDLK_UP]) up2=0;
	    if(!touches[SDLK_DOWN]) down2=0;
	    if(!touches[SDLK_z]) up1=0;
	    if(!touches[SDLK_s]) down1=0;
	
}
void gestion_clavier_appuie(SDL_Event *event){
	/*switch(event->key.keysym.sym){
		
		default: break;
		
		case SDLK_UP : if(joueur2.y >= 2) joueur2.y-=5;break;
		case SDLK_DOWN : if(joueur2.y <= 420) joueur2.y+=5;break;
		case SDLK_z : if(joueur1.y >= 2) joueur1.y-=5;break;
		case SDLK_s : if(joueur1.y <= 420) joueur1.y+=5;break;
		*/
		
		Uint8 * touches = SDL_GetKeyState(NULL);
		if(touches[SDLK_q])
        continuer = 0;

    if(touches[SDLK_UP])
       up2=1;
       
        if(touches[SDLK_DOWN] )
		down2=1;
        
         if(touches[SDLK_z])
       up1=1;
        
         if(touches[SDLK_s])
        down1=1;
        
        if(touches[SDLK_SPACE])  mouvement_balle = 1; 	
        
        if(touches[SDLK_ESCAPE]) continuer = 0;
	}
	
	

void SDL_Balle() {
	//on bouge les joueurs 
	
	if (mouvement_balle == 1) {
		
		//on rélise les teste sur la balle
		//en bas et en haut
		if(balle_st.y > (height - 10) | balle_st.y< 5){
			
			balle_st.accy = -balle_st.accy;
			
			
		} 
		 //on teste si près du joueur 1 
		 if ( abs(balle_st.y - joueur1.y) < 50 & balle_st.x < 20) {
		 	
		 		balle_st.accx = -balle_st.accx;
		}
		 if ( abs(balle_st.y - joueur2.y) < 50 & balle_st.x > (width-30)) {
		 	
		 		balle_st.accx = -balle_st.accx;
		}
		
		//On teste si le joueuer de gauche a perdu 
		if (balle_st.x < 0) {
			
			mouvement_balle = 0;
			score_2++;
			balle_st.x = 320;
			balle_st.y = 240;
		}
		
		if (balle_st.x > width) {
			
			mouvement_balle = 0;
			score_1++;
			balle_st.x = 320;
			balle_st.y = 240;
		}
		
		 //on bouge la balle
		 
		 balle_st.y+=balle_st.accy;
		 balle_st.x+=balle_st.accx;
		//SDL_Delay(1);
		
		
	}
	
	
	
	
	
	
}
