#include<vector>
#include<string>
using namespace std;

string mergeAlternately(string word1, string word2) {
	vector<char> final;

	int k=0;
	while(k < word1.size() && k < word2.size()) {
		final.push_back(word1[k]);
		final.push_back(word2[k]);
		k++;
	}

	int i = k;
	while(i < word1.size()) {
		final.push_back(word1[i]);
		i++;
	}

	int j = k;
	while(j < word2.size()) {
		final.push_back(word2[j]);
		j++;
	}

	string result(final.begin(), final.end());
	return result;
}


