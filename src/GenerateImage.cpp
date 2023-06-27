#include <bits/stdc++.h>
#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"
#include "ppm.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "camera.h"
#include "material.h"

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
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
	
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

	hit_record rec;

	if( depth <= 0 ) return color( 0, 0, 0 );

	if( world.hit( r, 0.001, infinity, rec ) ){
		ray scattered;
		color attenuation;
		if( rec.mat_ptr->scatter( r, rec, attenuation, scattered ) ) return attenuation * ray_color( scattered, world, depth-1 );
		return color( 0, 0, 0 );
	}

	vec3 unit_direction = unit_vector( r.direction() );
	double t = 0.5 * ( unit_direction.y() + 1 );
	return ( 1 - t )*color( 1, 1, 1 ) + t*color( 0.3, 0.5, 1 );

}