#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

double MAX_COLOR = 256;
const double ERR = 1e-5;

void write_color(std::ostream &out, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>( MAX_COLOR * pixel_color.x() - ERR ) << ' '
        << static_cast<int>( MAX_COLOR * pixel_color.y() - ERR ) << ' '
        << static_cast<int>( MAX_COLOR * pixel_color.z() - ERR ) << '\n';
}

void set_max_color( double new_color ){
	MAX_COLOR = new_color;
}

#endif