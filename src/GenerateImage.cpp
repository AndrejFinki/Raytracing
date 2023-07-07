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
const int IMAGE_WIDTH = 1920;
const int IMAGE_HEIGHT = int( IMAGE_WIDTH / ASPECT_RATIO );
const int IMAGE_MAX_VALUE = 255;
const int SAMPLES_PER_PIXEL = 500;
const int MAX_DEPTH = 50;

hittable_list project_scene();
hittable_list random_scene();
color ray_color( const ray &, const hittable &, int );
int main(){

	PPM::initialize_ppm( "P3", IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_MAX_VALUE );

	hittable_list world = project_scene();

    point3 lookfrom(30,30,30);
    point3 lookat(0,sqrt(100),0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 30.0;
    auto aperture = 0;
    camera cam(lookfrom, lookat, vup, 25, ASPECT_RATIO, aperture, dist_to_focus);

	int last_scanline = IMAGE_HEIGHT-1;
	for( int j = IMAGE_HEIGHT-1 ; j >= 0 ; j-- ) for( int i = 0 ; i < IMAGE_WIDTH ; i++ ){

		if( j < last_scanline ){
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
	return ( 1 - t )*color( 1, 1, 1 ) + t*color( 0.8, 0.8, 0.8 );

}

hittable_list project_scene() {

    hittable_list world;

	auto ground_material = make_shared<metal>( color( 0.9, 0.9, 0.9 ), 0.0 );
    world.add( make_shared<sphere>( point3( 0, -1000, 0), 1000, ground_material ) );

	const double ANGLE_INC = 3 * M_PI;
	const double HALF_POINTS = 100;	
	const double CENTER_POINT_Y = 1.1 * sqrt( HALF_POINTS );

	double angle = 0;
	for( int i = 1 ; i < HALF_POINTS ; i++, angle += ANGLE_INC ){

		world.add( make_shared<sphere>( point3( sqrt(i) * cos( degrees_to_radians( angle ) ),
										1.3*sqrt(i),
										sqrt(i) * sin( degrees_to_radians( angle ) ) ),
										0.5,
										make_shared<lambertian>( color( 1, std::max( (double)0.0, cos( degrees_to_radians( angle ) ) ), std::max( (double)0.0, -sin( degrees_to_radians( angle ) ) ) ) )
		) );

	}
	for( int i = HALF_POINTS ; i < 2*HALF_POINTS ; i++, angle += ANGLE_INC ){

		world.add( make_shared<sphere>( point3( sqrt(201-i) * cos( degrees_to_radians( angle ) ),
										1.3*sqrt(i),
										sqrt(201-i) * sin( degrees_to_radians( angle ) ) ),
										0.5,
										make_shared<lambertian>( color( 1, std::max( (double)0.0, -cos( degrees_to_radians( angle ) ) ), std::max( (double)0.0, sin( degrees_to_radians( angle ) ) ) ) )
		) );

	}

    world.add( make_shared<sphere>( point3( 0, CENTER_POINT_Y, 0 ),
									CENTER_POINT_Y / 2,
									make_shared<metal>( color( 0.7, 0.6, 0.5 ), 0.0 )
	) );

    return world;

}


hittable_list random_scene() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}
