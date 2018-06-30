/*
 * Example program to show how to use EBox to determine when two bitmaps collide.
 * Jon Rafkind
 *
 * This code is freely distributable and can be changed or used any way you want.
 * There is no guarantee this code will work properly. Use at your own risk.
 */


#include "ebox.h"
#include "allegro.h"
#include <alpng.h>
#include <stdlib.h>
#include <time.h>

volatile int speed_counter = 0;

void inc_speed_counter(){
	speed_counter++;
}
END_OF_FUNCTION( inc_speed_counter );

//some online guide said this is the best way to get a random number using the rand()
//function. i dont know why, i just use it.
int rnd( int q ){
	return (int)( q * ( (double)rand() / ( (double)RAND_MAX + 1.0 ) ) );
}

int k = 0;
void animar();

void init(){
	allegro_init();
	alpng_init();
	srand( time( NULL ) );
	install_timer();
	install_keyboard();
	set_color_depth( 32 );
	set_alpha_blender();
	set_gfx_mode( GFX_AUTODETECT, 640, 480, 0, 0 );
	
	LOCK_VARIABLE( speed_counter );
	LOCK_FUNCTION( inc_speed_counter );
	install_int_ex( inc_speed_counter, MSEC_TO_TIMER( 40 ) );
		install_int_ex( animar, MSEC_TO_TIMER( 60 ) );
	


}

struct object{
	int x, y; //position of object
	BITMAP * bmp[10]; //bitmap of object
	ECollide * col; //collide object
	bool collided; //remember if we collided with something

	int dx, dy; //direction object is moving in
};


int main(){
	init();

	//initialize objects
	object olist[2];
	for ( int q = 0; q < 2; q++ ){
		olist[q].x = rnd( 640 );
		olist[q].y = rnd( 480 );
		olist[q].bmp[0] = load_bitmap("kyo/stand (0).PNG",NULL);
        olist[q].bmp[1] = load_bitmap("kyo/stand (1).PNG",NULL);
        olist[q].bmp[2] = load_bitmap("kyo/stand (2).PNG",NULL);
        olist[q].bmp[3] = load_bitmap("kyo/stand (3).PNG",NULL);
        olist[q].bmp[4] = load_bitmap("kyo/stand (4).PNG",NULL);
        olist[q].bmp[5] = load_bitmap("kyo/stand (5).PNG",NULL);
        olist[q].bmp[6] = load_bitmap("kyo/stand (6).PNG",NULL);
        olist[q].bmp[7] = load_bitmap("kyo/stand (7).PNG",NULL);
        olist[q].bmp[8] = load_bitmap("kyo/stand (8).PNG",NULL);
        
		//ear_to_color( olist[q].bmp[0], makecol(0,0,0) );
		olist[q].collided = false;
		olist[q].dx = rnd(2) * 2 - 1;
		olist[q].dy = rnd(2) * 2 - 1;
		//place random circles on the bitmap
		for ( int z = 0; z < 5; z++ )
			//circlefill( olist[q].bmp[0], rnd(90), rnd(90), rnd(20)+10, makecol(rnd(128)+50,20,rnd(255) ) );
              rectfill( olist[q].bmp[k],10,0,0,0,makecol(0,0,0));
		// change any of these variables to see what happens with the collide object
		int size = 2; //randge 1-infinity
		double percent = 88; //range 1-100

		olist[q].col = new ECollide( olist[q].bmp[k], size, makecol(0,0,0), percent );
	}
   
	BITMAP * work = create_bitmap( 640, 480 );
	clear( work );

	bool draw_boxes = true;
	bool hold = false;
	while ( !key[KEY_ESC] ){

		if ( key[KEY_H] && !hold ){
			draw_boxes = !draw_boxes;
			hold = true;
		}
		if ( !key[KEY_H] ) hold = false;

		while ( speed_counter > 0 ){

			for ( int q = 0; q < 2; q++ )olist[q].collided = false;

			
            if(key[KEY_LEFT])
            {
               olist[0].x -= olist[0].dx*2;               
            }
            if(key[KEY_RIGHT])
            {
               olist[0].x += olist[0].dx*2;               
            }
            if(key[KEY_DOWN])
            {
               olist[0].y -= olist[0].dy*2;               
            }
                        if(key[KEY_UP])
            {
               olist[0].y += olist[0].dy*2;               
            }
            
             if(key[KEY_A])
            {
               olist[1].x += olist[1].dx*2;               
            }
            if(key[KEY_D])
            {
               olist[1].x -= olist[1].dx*2;               
            }
            if(key[KEY_S])
            {
               olist[1].y += olist[1].dy*2;               
            }
                        if(key[KEY_W])
            {
               olist[1].y -= olist[1].dy*2;               
            }
            
            
            for ( int q = 0; q < 2; q++ ){

				//
				//olist[q].y += olist[q].dy*2;
			//	if( olist[q].x < 0 || olist[q].x > 640 ) olist[q].dx = -olist[q].dx;
				//if( olist[q].y < 0 || olist[q].y > 480 ) olist[q].dy = -olist[q].dy;

				//test to see if the current object collided with any other object
				for ( int m = 0; m < 2; m++ )
					if ( m != q )
						if ( olist[q].col->Collision(olist[m].col,olist[q].x,
							olist[q].y, olist[m].x, olist[m].y ) ){
							olist[q].collided = true;
							olist[m].collided = true;
						}
				
			}
			
			speed_counter--;
		}

		for ( int q = 0; q < 2; q++  ){
			int x = olist[q].x - olist[q].bmp[k]->w/2;
			int y = olist[q].y - olist[q].bmp[k]->h/2;
			//draw_trans_sprite( work, olist[0].bmp[k], x, y );
			//draw_trans_sprite();
			//draw_sprite_h_flip( work, olist[1].bmp[k], x, y );
            if ( draw_boxes )
			olist[q].col->display( work, olist[q].x, olist[q].y );
			textprintf_ex( work, font, olist[q].x, olist[q].y, makecol(255,255,255),-1, "Box:%d", q );
			if ( olist[q].collided ) 
				textprintf_ex(work,font,1,q*10,makecol(255,255,255),-1,"caixa %d colidiu com algo!", q );
			else	textprintf_ex(work,font,1,q*10,makecol(255,255,255),-1,"caixa %d nao colidiram");
		}
		textprintf_ex(work,font,1,470,makecol(255,255,255),-1,"Pressione H para alternar desenho de caixas de colisao");
	
        blit( work, screen, 0, 0, 0, 0, 640, 480 );
		clear( work );
		
	}
	destroy_bitmap( work );
	for ( int q = 0; q < 2; q++ ){
		destroy_bitmap( olist[q].bmp[k] );
		delete olist[q].col;
	}

}
END_OF_MAIN();
void animar()
{
     k++;
     if(k>8)
     k = 0;
 }

