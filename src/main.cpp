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

	try {
		scene.DrawImageFrom(filename, samples_per_pixel);
	} catch (std::invalid_argument& e) {
		std::cout << "Invalid argument: " << e.what() << std::endl;
	} catch (nlohmann::detail::type_error e) {
		std::cout << "Error while parsing JSON: " << e.what() << std::endl;
	} catch (std::out_of_range& oor) {
		std::cout << "Given material index out of range: " << oor.what() << std::endl;
	}

    }
    
    return 0;
}
