#include <iomanip>
#include <iostream>
#include <fstream>

#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

template <typename Out>
void split(const string &s, char delim, Out result){
	istringstream iss(s);
	string item;
	while (getline(iss, item, delim)){
		*result++ = item;
	}
}

vector<string> split(const string &s, char delim){
	vector<string> elems;
	split(s, delim, back_inserter(elems));
	return elems;
}

int main(int argc, char** argv){
	string searchKey, line;
	vector<string> v(argv + 1, argv + argc);
	fstream file;

	if(v.size() == 0){
		cout << "Syntax: -k || --key <key> -c || --csv <file.csv>\n";
		return 0;
	}

	for(auto i = v.begin(); i != v.end(); ++i){
		if(*i == "-h" || *i == "--help"){
			cout << "Syntax: -k || --key <key> -c || --csv <file.csv>\n";
			return 0;
		}
		else if(*i == "-k" || *i == "--key"){
			searchKey = *++i;
		}
		else if(*i == "-c" || *i == "--csv"){
			string wrkspcFName = *++i;
			file.open(wrkspcFName);
			if(file.fail()){
				cout << "File: " << wrkspcFName << " has set failbit andor badbit flags\n";
				return 1;
			} 
		}
	}

	while(getline(file, line)){
		v = split(line, ',');
		if(v[0] == searchKey) cout << v[1] << "\n";
	}
}