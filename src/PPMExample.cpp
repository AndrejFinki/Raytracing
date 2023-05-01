#include "Image.cpp"

const double ERR = 1e-5;

int main(){

	Image::initialize_ppm( "P3", 256, 256, 255 );
	Image::print_ppm();

	for( int j = Image::image_height-1 ; j >= 0 ; j-- ) for( int i = 0 ; i < Image::image_width ; i++ ) {
		
		double r = double( i ) / ( Image::image_width-1 );
		double g = double( j ) / ( Image::image_height-1 );
		double b = 0.5;

		int ir = static_cast<int>( r * 256 - ERR );
		int ig = static_cast<int>( g * 256 - ERR );
		int ib = static_cast<int>( b * 256 - ERR );

		Image::draw_next_pixel( ir, ig, ib );
    
	}

}