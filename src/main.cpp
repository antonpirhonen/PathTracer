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
		try {
			samples_per_pixel = std::stoi(s);
		} catch (std::invalid_argument& e) {
			std::cout << "Given sample size not convertible to int. Using sample size of 1." << std::endl;
		}
	}

	if (samples_per_pixel < 1) {
		std::cout << "Sample size must be greater or equal to 1. Using sample size of 1." << std::endl;
		samples_per_pixel = 1;
	}

	std::cout << "Rendering an image with " << samples_per_pixel
		  << " rays per pixel" << std::endl;

	try {
		scene.DrawImageFrom(filename, samples_per_pixel);
	} catch (std::invalid_argument& e) {
		std::cout << "Invalid input: " << e.what() << std::endl;
	} catch (nlohmann::detail::type_error& e) {
		std::cout << "Error while parsing JSON: " << e.what() << std::endl;
	} catch (std::out_of_range& oor) {
		std::cout << "Index out of range: " << oor.what() << std::endl;
	}

    }
    
    return 0;
}
