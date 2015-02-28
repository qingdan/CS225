/**
 * @file animation.h
 *
 * Defintion for a class that encapsulates creating animated images from a
 * set of PNG object frames.
 *
 * @author Jack Toole
 * @date Fall 2011
 */
#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include "png.h"

using namespace std;

/**
 * Animation class---used to create animated images from a sequence of PNG
 * objects as frames of the animation.
 *
 * @author Jack Toole
 * @date Fall 2011
 */
class animation {
	public:
		/**
		 * Adds a frame to the animation.
		 *
		 * @param img The image to be added.
		 */
		void addFrame(const PNG & img);

		/**
		 * Writes the animation to the file name specified.
		 *
		 * @param filename The name of the file to be written to.
		 */
		void write(const std::string & filename);

	private:
		std::vector<PNG> frames;

		template <typename T>
		string to_string(const T & value);
		string getString(int i, int padToSameLengthAs);
		bool exists(const string & path);
};

#endif
