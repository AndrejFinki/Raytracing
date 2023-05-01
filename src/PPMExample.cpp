#include <bits/stdc++.h>
#include "Image.cpp"

int main(){

	Image::initialize_ppm( "P3", 256, 256, 255 );
	Image::print_ppm();

	for( int j = Image::image_height-1 ; j >= 0 ; j-- ) for( int i = 0 ; i < Image::image_width ; i++ ) {
		
		double r = double( i ) / ( Image::image_width-1 );
		double g = double( j ) / ( Image::image_height-1 );
		double b = 0.5;

		Image::draw_next_pixel_d( r, g, b );
    
	}

}