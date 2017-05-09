/*
 * Mohamed Samatar - 101848
 * Assignment 14 - Huffman Coding
 * Uses a Huffman Tree to compress a string
 */
#include "header.h"

string getUniqueChars(string str);
vector<int> frequencies(string str, string chars);
void codes(chNode *n, string s, map<char, string> &code);
string huffman(string str);

int main(){
	cout << "/*\n * Mohamed Samatar - 101848\n * Assignment 14 - Huffman Coding\n"
		<< " * Uses a Huffman Tree to compress a string\n */\n\n";
	huffman(gettysburg);
}

//Returns string containing all unique characters in given string
string getUniqueChars(string str){
	stringstream ss;
	set<char> sset;
	for(int i = 0; i < str.length(); ++i)
		sset.insert(str[i]);
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

//Traverses through rooted tree to get codes for each char
void codes(chNode *n, string s, map<char, string> &code){
	stringstream ss;
	if(n == nullptr)
		return;
	if(n->letter != '\0'){
		ss << s;
		code.insert(pair<char, string>(n->letter, ss.str()));
		ss.clear();
		if(n->letter == '\n')
			cout << "\\n";
		else
			cout << n->letter;
		cout << ": " << s << endl;
	}
	codes(n->left, s + '0', code);
	codes(n->right, s + '1', code);
}

//Huffman compression algorithm
string huffman(string str){
	stringstream ss;
	chNode *left, *right,
		*root = nullptr;

	string bin, uniques = getUniqueChars(str);
	vector<int> freqs = frequencies(str, uniques);

	auto greater = [](chNode *a, chNode *b){ return a->freq > b->freq; };
	priority_queue<chNode *, vector<chNode *>, decltype(greater)> heap(greater);

	for(int i = 0; i < freqs.size(); ++i)
		heap.push(new chNode(uniques[i], freqs[i]));

	//Builds a Huffman tree from the priority queue
	while(heap.size() > 1){
		left = heap.top();
		heap.pop();
		right = heap.top();
		heap.pop();
		//'\0' is used to indicate that the node is internal
		root = new chNode('\0', left->freq + right->freq);
		root->left = left;
		root->right = right;
		heap.push(root);
	}

	map<char, string> codeMap;
	codes(root, "", codeMap);
	cout << endl;

	for(int i = 0; i < str.length(); ++i)
		ss << codeMap[str[i]];
	ss >> bin;
	ss.clear();
	ss.str("");

	cout << "Compression Ratio = " <<
		(double)(str.length() * sizeof(char) * 8) / (double)bin.length() <<
		"\nCompressed String: " << bin << endl;

	//Make a "reverse map" for more efficient searching of table by code
	map<char, string>::const_iterator it;
	map<string, char> charMap;
	for(it = codeMap.begin(); it != codeMap.end(); ++it)
		charMap.insert(pair<string, char>(it->second, it->first));

	map<string, char>::iterator charIt;
	stringstream decode;
	for(int i = 0; i < bin.length(); ++i){
		ss << bin[i];
		charIt = charMap.find(ss.str());
		if(charIt != charMap.end()){
			decode << charIt->second;
			ss.clear();
			ss.str("");
		}
	}
	cout << "Decompressed string: " << decode.str() << endl;
	decode.clear();
	decode.str("");
	ss.clear();
	ss.str("");

	return bin;
}
