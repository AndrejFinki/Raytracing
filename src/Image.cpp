#ifndef IMAGE_CPP
#define IMAGE_CPP

#include <bits/stdc++.h>
#include "color.cpp"

class Image { public:

	static std::string ppm_type;
	static int image_width;
	static int image_height;
	static int image_max_color;

	static void initialize_ppm( const std::string &ppm_type, const int &image_width, const int &image_height, const int &image_max_color ){
		Image::ppm_type = ppm_type;
		Image::image_height = image_height;
		Image::image_width = image_width;
		Image::image_max_color = image_max_color;
	}

	static void print_ppm(){
		std::cout << ppm_type << "\n" << image_width << " " << image_height << "\n" << image_max_color << "\n";
	}

	static void draw_next_pixel( color pixel_color ){
		Image::draw_next_pixel_d( pixel_color.x(), pixel_color.y(), pixel_color.z() );
	}

	static void draw_next_pixel_d( double r, double g, double b ){
		Image::draw_next_pixel_i( color_d_to_i(r,image_max_color), color_d_to_i(g,image_max_color), color_d_to_i(b,image_max_color) );
	}

	static void draw_next_pixel_i( int r, int g, int b ){
		std::cout << r << " " << g << " " << b << "\n";
	}

};

std::string Image::ppm_type = "";
int Image::image_height = 0;
int Image::image_width = 0;
int Image::image_max_color = 0;

#endif