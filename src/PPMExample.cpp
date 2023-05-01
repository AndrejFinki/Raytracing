#include <bits/stdc++.h>
#include "ImageFormat.cpp"

const double ERR = 1e-5;

int main(){

	ImageFormat::initialize_ppm( "P3", 256, 256, 255 );
	ImageFormat::print_ppm();

	for( int j = ImageFormat::image_height-1 ; j >= 0 ; j-- ) for( int i = 0 ; i < ImageFormat::image_width ; i++ ) {
		
		double r = double( i ) / ( ImageFormat::image_width-1 );
		double g = double( j ) / ( ImageFormat::image_height-1 );
		double b = 0.5;

		int ir = static_cast<int>( r * 256 - ERR );
		int ig = static_cast<int>( g * 256 - ERR );
		int ib = static_cast<int>( b * 256 - ERR );

		std::cout << ir << ' ' << ig << ' ' << ib << "\n";
    
	}

}