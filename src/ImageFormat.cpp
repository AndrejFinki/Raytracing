#include <bits/stdc++.h>

struct ImageFormat {

	static std::string ppm_type;
	static int image_width;
	static int image_height;
	static int image_max_color;

	static void initialize_ppm( const std::string &ppm_type, const int &image_width, const int &image_height, const int &image_max_color ){
		ImageFormat::ppm_type = ppm_type;
		ImageFormat::image_height = image_height;
		ImageFormat::image_width = image_width;
		ImageFormat::image_max_color = image_max_color;
	}

	static void print_ppm(){
		std::cout << ppm_type << "\n" << image_width << " " << image_height << "\n" << image_max_color << "\n";
	}

};

std::string ImageFormat::ppm_type = "";
int ImageFormat::image_height = 0;
int ImageFormat::image_width = 0;
int ImageFormat::image_max_color = 0;