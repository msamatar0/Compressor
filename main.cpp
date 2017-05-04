#include "header.h"

string getUniqueChars(string str);
vector<int> frequencies(string str, string chars);
string huffman(string str);

int main(){
	cout << testStr << "Compresses to " << huffman(testStr);
}

//Returns string containing all unique characters in given string
string getUniqueChars(string str){
	stringstream ss;
	set<char> sset;
	for(int i = 0; i < str.length(); ++i)
		sset.insert(tolower(str[i]));
	for(char c : sset)
		ss << c;
	return ss.str();
}

//Returns # of times a # of chars appear in a given string for each char
//Resulting vector is parallel to set of chars
vector<int> frequencies(string str, string chars){
	vector<int> freqs(chars.length());
	for(int i = 0; i < chars.length(); ++i)
		for(char c : str)
			if(chars[i] == c)
				freqs[i]++;
	return freqs;
}

//Huffman compression algorithm
string huffman(string str){
	string bin, chars = getUniqueChars(str);
	vector<int> freqs = frequencies(str, chars);
	return bin;
}
