#ifndef COLOR_H
#define COLOR_H

#include <bits/stdc++.h>
#include "vec3.cpp"

const double ERR = 1e-5;

int color_d_to_i( double color_channel, const int image_max_color ){
	return static_cast<int>( color_channel * ( image_max_color+1 ) - ERR );
}

void write_color( std::ostream &out, color pixel_color, const int image_max_color ) {
    out << color_d_to_i( pixel_color.x(), image_max_color ) << ' ' << color_d_to_i( pixel_color.y(), image_max_color ) << ' ' << color_d_to_i( pixel_color.z(), image_max_color ) << '\n';
}

#endif