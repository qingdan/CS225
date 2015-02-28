/**
 * @file animation.cpp
 *
 * Implementation of the animation class.
 * @author Jack Toole
 * @date Fall 2011
 */

#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <string>
#include "animation.h"

using namespace std;

template <typename T>
inline string animation::to_string(const T & value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}

string animation::getString(int i, int padToSameLengthAs) {
	string istr = to_string(i);
	string padstr = to_string(padToSameLengthAs);
	return string(padstr.length() - istr.length(), '0') + istr;
}

bool animation::exists(const string & path)
{
	// Try stat-ing it
	struct stat st;
	if (stat(path.c_str(), &st) != 0) return false;
	// Check for read permission
	if ((st.st_mode & S_IRUSR) == 0) return false;

	// Check for correct file/directory nature
	if (path[path.length()-1] != '/') return S_ISREG(st.st_mode);

	// Otherwise we want a directory
	if ((st.st_mode & S_IXUSR) == 0) return false;
	return S_ISDIR(st.st_mode);
}


void animation::addFrame(PNG const & img) {
	frames.push_back(img);
}

void animation::write(const std::string & filename) {
	if(frames.empty())
	{
		cout << "Animation Warning: No frames added!" << endl;
		return;
	}
	size_t filestart = filename.find_last_of("/");
	filestart = (filestart == string::npos) ? 0 : filestart+1;
	size_t extstart  = filename.find_last_of(".");
	string name = filename.substr(filestart, extstart - filestart);

	// Create the frames/ directory if it does not exist
	if (!exists("frames/"))
		mkdir("frames",0700);

	// Remove all previous frames from this image
	system(("ls frames | grep '^" + name + ".*\\.png$' | xargs -I% rm -f frames/%").c_str());

	// Generate Frames
	for (size_t i = 0; i < frames.size(); i++)
		frames[i].writeToFile(("frames/" + name + getString(i, frames.size()) + ".png").c_str());

	// Combine frames
	system(("convert frames/" + name + "*.png " + filename).c_str());
}

