/**
 * @file common_words.h
 * Header file of a class to find all the common words across multiple files
 *
 * @author Zach Widder
 * @date Fall 2014
 */


#ifndef COMMON_WORDS_H
#define COMMON_WORDS_H

#include <string>
#include <map>
#include <vector>

using std::map;
using std::vector;
using std::string;

/**
 * CommonWords class. Definition of a class to find all the common words across multiple files
 *
 * @author Zach Widder
 * @date October 2014
 */
class CommonWords
{
public:
    
    /**
     * Constructs a CommonWords object from a vector of filenames. 
     * file_word_maps is a vector of maps, where each element of the vector represents a different file,
     * and the map hashes a word in the file to the number of time that word has been seen.
     * common is a map of words in all files that hashes to how many files it appeared in.
     * @param filenames The vector of strings where the strings are the filenames to read in.
     */
    CommonWords(const std::vector< std::string >& filenames);
    
	/**
	 * @param n The number of times to word has to appear.
	 * @return A vector of strings. Vector contains all words that appear in all
	 * files >= n times. I.e. the word must appear in all files more than 
	 * n times.
	 */
    std::vector< std::string > get_common_words(unsigned int n) const;
    
private:
    /* map from a word to the number of documents that word appears in */
    std::map< std::string, unsigned int > common;
    /* file_word_maps has each index of the vector corresponds to a different file, and each of those files have a map
     * from the the word in that file to the number of times that it was seen in that file.
     */
    vector< map< string, unsigned int > > file_word_maps;

    /* helper functions */
    /**
     * Takes a filename and transforms it to a vector of all words in that file.
     * @param filename The name of the file that will fill the vector
     */
    vector< string > file_to_vector(const string& filename) const;

    /**
     * Initializes file_word_maps, having each index hold a map going from the word 
     * seen in that file to the number of times the word appears in that file.
     * @param filenames The vector of names of the files that will be used
     */
    void init_file_word_maps(const vector< string >& filenames);

    /**
     * Initializes common, mapping a word to the number of documents it shows up in.
     */
    void init_common();
};

#endif
