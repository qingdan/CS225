/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
	vector< string > vectorWords;
	ifstream words(filename);
	string word;
	if(words.is_open()) 
	{
    /* Reads a line from words into word until the file ends. */
   		while(getline(words, word)) 
        	vectorWords.push_back(word);
	}
	for(auto & vectorIt : vectorWords)
	{
		auto lookup = dict.find(vectorIt);
		if(lookup == dict.end())
		{
			std::vector <char> vectorChar;
			for (size_t i=0; i<vectorIt.length(); ++i)
    			vectorChar.push_back(vectorIt.at(i));
			std::sort(vectorChar.begin(),vectorChar.end());
			dict.insert(std::pair<string, std::vector< char >>(vectorIt, vectorChar));
		}	
	}
}

/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
    /* Your code goes here! */
	for(auto & vectorIt : words)
	{
		auto lookup = dict.find(vectorIt);
		if(lookup == dict.end())
		{
			std::vector <char> vectorChar;
			for (size_t i=0; i<vectorIt.length(); ++i)
    			vectorChar.push_back(vectorIt.at(i));
			std::sort(vectorChar.begin(),vectorChar.end());
			dict.insert(std::pair<string, std::vector< char >>(vectorIt, vectorChar));
		}	
	}
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
	vector< string > out;
	out = helper_get_anagrams(word);
	if(out.size() > 1)
    	return out;
	else
		return vector< string >();
}       

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
	vector< vector < string > > allVector;
	for(auto& dictIt : dict)
	{
		string tempWord = dictIt.first;
		vector< string > smallVector = helper_get_anagrams(tempWord);
		if(smallVector.size() > 1)
			allVector.push_back(smallVector);
	}
    return allVector;
}

//helper function
vector< string > AnagramDict::helper_get_anagrams(const string& word) const
{
    /* Your code goes here! */
	vector< string > out;
	auto lookup = dict.find(word);
	if(lookup != dict.end())
	{
		vector< char > vectorChar = lookup->second;
		for(auto & dictIt : dict)
		{
			if(dictIt.second == vectorChar)
				out.push_back(dictIt.first);
		}
	}
    return out;
}  
