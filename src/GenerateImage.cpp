#include <bits/stdc++.h>
#include "ppm.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"

const double ASPECT_RATIO = 16.0/9.0;
const int IMAGE_WIDTH = 256;
const int IMAGE_HEIGHT = int( IMAGE_WIDTH / ASPECT_RATIO );
const int IMAGE_MAX_VALUE = 255;

color ray_color( const ray & );

int main(){

	PPM::initialize_ppm( "P3", IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_MAX_VALUE );

	double viewport_height = 2;
	double viewport_width = viewport_height * ASPECT_RATIO;
	double focal_length = 1;

	point3 origin = point3( 0, 0, 0 );
	vec3 horizontal = vec3( viewport_width, 0, 0 );
	vec3 vertical = vec3( 0, viewport_height, 0 );
	vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3( 0, 0, focal_length );

	for( int j = IMAGE_HEIGHT-1 ; j >= 0 ; j-- ) for( int i = 0 ; i < IMAGE_WIDTH ; i++ ){

		double u = double(i) / ( IMAGE_WIDTH-1 );
		double v = double(j) / ( IMAGE_HEIGHT-1 );

		ray r( origin, lower_left_corner + u*horizontal + v*vertical - origin );

		color pixel_color = ray_color(r);

		write_color( std::cout, pixel_color );

	} 

}

color ray_color( const ray &r ){

	vec3 unit_direction = unit_vector( r.direction() );
	double t = 0.5 * ( unit_direction.y() + 1 );
	return ( 1 - t )*color( 1, 1, 1 ) + t*color( 0.3, 0.5, 1 );

}