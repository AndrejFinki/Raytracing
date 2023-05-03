#ifndef PPM_H
#define PPM_H

#include "color.h"

class PPM { public:

	static void initialize_ppm( const std::string &ppm_type, const int &image_width, const int &image_height, const int &image_max_color ){
		std::cout << ppm_type << "\n" << image_width << " " << image_height << "\n" << image_max_color << "\n";
		set_max_color( image_max_color );
	}

};

#endif