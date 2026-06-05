#include <bits/stdc++.h>
using namespace std;
struct TrieNode {
	int next[26];
	bool end = 0;
	TrieNode() {
		fill(next, next + 26, -1);
	}
};

vector<TrieNode> trie {TrieNode()};

void insert(vector<TrieNode>& trie, const string& s) {
	int v = 0;
	for(char c : s) {
		if(trie[v].next[c-'a'] == -1) {
			trie[v].next[c-'a'] = trie.size();
			trie.push_back(TrieNode());
		}
		v = trie[v].next[c-'a'];
	}
	trie[v].end = 1;
}

int go(vector<TrieNode>& trie, const string& s) {
	int v = 0;
	for(char c : s) {
		if(trie[v].next[c-'a'] == -1) {
			return -1;
		}
		v = trie[v].next[c-'a'];
	}
	return v;
}