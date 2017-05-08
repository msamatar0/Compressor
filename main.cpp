#include "header.h"

string getUniqueChars(string str);
vector<int> frequencies(string str, string chars);
void codes(chNode *n, string s, map<char, int> &code);
string huffman(string str);

int main(){
	cout << "Compressed String: " << huffman(gettysburg) << endl;
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

void codes(chNode *n, string s, map<char, int> &code){
	int codeVal = 0;
	stringstream ss;
	if(n == nullptr)
		return;
	if(n->letter != '\0'){
		ss << s;
		ss >> codeVal;
		ss.clear();
		code.insert(pair<char, int>(n->letter, codeVal));
		cout << n->letter << ": " << s << endl;
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
	map<char, int> codeMap;
	codes(root, "", codeMap);
	cout << endl;
	
	for(int i = 0; i < str.length(); ++i)
		ss << codeMap[str[i]];
	ss >> bin;
	ss.clear();
	return bin;
}
