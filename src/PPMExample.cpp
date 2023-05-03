#include <bits/stdc++.h>
#include "ppm.h"
#include "vec3.h"
#include "color.h"

const int IMAGE_WIDTH = 256;
const int IMAGE_HEIGHT = 256;
const int IMAGE_MAX_VALUE = 255;

int main(){

	PPM::initialize_ppm( "P3", IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_MAX_VALUE );

	for( int j = IMAGE_HEIGHT-1 ; j >= 0 ; j-- ) for( int i = 0 ; i < IMAGE_WIDTH ; i++ ) {
		
		double r = double( i ) / ( IMAGE_WIDTH-1 );
		double g = double( j ) / ( IMAGE_HEIGHT-1 );
		double b = 0.75;

		write_color( std::cout, color( r, g, b ) );
    
	}

}