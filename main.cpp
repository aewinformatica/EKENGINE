#include <allegro.h>
#include <alpng.h> 
#include "sistema.h" 

int main(int argc, char *argv[])
{
    Sistema Jogo;
    
    BITMAP *Buffer = NULL;
            Buffer = create_bitmap(640,480);
    
    BITMAP *Logo = NULL;
            Logo = load_bitmap("fire.png",NULL);
            
    BITMAP *Logo2 = NULL;
            Logo2 = load_bitmap("logo.png",NULL);
             
    SAMPLE *Som = NULL;
            Som = load_sample("presents.wav");




Jogo.Abertura(Logo,Logo2,Som);




	// Fica em loop até pressionar a tecla ESC
	while(!Jogo.Fim()){
                       
  if(key[KEY_ENTER])
          {
             if (key_shifts & KB_ALT_FLAG) 

                          Jogo.Mudar_Tela();
          }
                          
		  if(key[KEY_ESC]||key[KEY_F4])
		  {
                         Jogo.Sair();
          }
     

blit(Buffer,screen,0,0,0,0,640,480);
	}

	// Sai do programa
	allegro_exit();
	return 0;     
}
// Esta macro converte o main para WinMain()
END_OF_MAIN();
