#include "Scene.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

    if (argc > 1) {
	std::string filename(argv[1]);
	Scene scene = Scene();
	int samples_per_pixel = 1;

	if (argc > 2) {
	    std::string s = std::string(argv[2]);
	    samples_per_pixel = std::stoi(s);
	}

	std::cout << "Rendering an image with " << samples_per_pixel
		  << " rays per pixel" << std::endl;
	
	scene.DrawImageFrom(filename, samples_per_pixel);
    }
    
    return 0;
}
