#include <bits/stdc++.h>
#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"
#include "ppm.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "camera.h"

const double ASPECT_RATIO = 16.0/9.0;
const int IMAGE_WIDTH = 800;
const int IMAGE_HEIGHT = int( IMAGE_WIDTH / ASPECT_RATIO );
const int IMAGE_MAX_VALUE = 255;
const int SAMPLES_PER_PIXEL = 20;
const int MAX_DEPTH = 20;

color ray_color( const ray &, const hittable &, int );
int main(){

	PPM::initialize_ppm( "P3", IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_MAX_VALUE );

	hittable_list world;
	world.add( make_shared<sphere>( point3( 0, 0, -1 ), 0.5 ) );
	world.add( make_shared<sphere>( point3( 0, -100.5, -1 ), 100 ) );

	camera cam;

	int last_scanline = IMAGE_HEIGHT-1;
	for( int j = IMAGE_HEIGHT-1 ; j >= 0 ; j-- ) for( int i = 0 ; i < IMAGE_WIDTH ; i++ ){

		if( j != last_scanline ){
			last_scanline = j;
			std::cerr << "Scanlines remaining: " << j << std::endl;
		}

		color pixel_color( 0, 0, 0 );
		for( int s = 0 ; s < SAMPLES_PER_PIXEL ; s++ ) {
			double u = ( i + random_double() ) / ( IMAGE_WIDTH-1 );
			double v = ( j + random_double() ) / ( IMAGE_HEIGHT-1 );
			ray r = cam.get_ray( u, v );
			pixel_color += ray_color( r, world, MAX_DEPTH );
		}
		
		write_color( std::cout, pixel_color, SAMPLES_PER_PIXEL );

	} 

}

color ray_color( const ray &r, const hittable &world, int depth ){

	hit_record record;

	if( depth <= 0 ) return color( 0, 0, 0 );

	if( world.hit( r, 0.001, infinity, record ) ){
		point3 target = record.p + record.normal + random_unit_vector();
		return 0.5 * ray_color( ray( record.p, target - record.p ), world, depth-1 );
	}

	vec3 unit_direction = unit_vector( r.direction() );
	double t = 0.5 * ( unit_direction.y() + 1 );
	return ( 1 - t )*color( 1, 1, 1 ) + t*color( 0.3, 0.5, 1 );

}