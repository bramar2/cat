#include <bits/stdc++.h>
using namespace std;

// Doubly linked list
template <typename T = int>
struct DLL {
	struct Node {
		T val;
		Node* prev = nullptr;
		Node* next = nullptr;
		Node(const T& c_val) : val(c_val) {}
		Node(T&& c_val) : val(move(c_val)) {}
	};
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t sz = 0;

	template <typename Container>
	void build(const Container& arr) {
		clear();
		for(const T& val : arr) {
			push_back(val);
		}
	}

	void push_front(T val) {
		sz += 1;
		if(head == nullptr) {
			head = tail = new Node(val);
		}else {
			head->prev = new Node(val);
			head = head->prev;
		}
	}

	void push_back(T val) {
		sz += 1;
		if(head == nullptr) {
			head = tail = new Node(val);
		}else {
			tail->next = new Node(val);
			tail = tail->next;
		}
	}

	void pop_front() {
		erase(head);
	}

	void pop_back() {
		erase(tail);
	}
	void clear() {
		for(Node* node = head; node != nullptr;) {
			Node* nxt = node->next;
			delete node;
			node = nxt;
		}
		sz = 0;
		head = tail = nullptr;
	}

	size_t size() {
		return sz;
	}

	// inserts after node, returns that inserted node
	Node* insert(Node* node, T val) {
		assert(node != nullptr);
		sz += 1;
		Node* ret = new Node(val);

		Node* left = node;
		Node* right = node->next;


		left->next = ret;
		ret->prev = left;

		if(right != nullptr) {
			right->prev = ret;
			ret->next = right;
		}else {
			tail = ret;
		}
		return ret;
	}

	// returns the node after this node (if any otherwise nullptr)
	Node* erase(Node* node) {
		assert(node != nullptr);
		sz -= 1;
		Node* ret = node->next;

		if(node->prev != nullptr) {
			node->prev->next = ret;
		}else {
			head = ret;
		}

		if(ret != nullptr) {
			ret->prev = node->prev;
		}else {
			tail = node->prev;
		}
		delete node;
		return ret;
	}
};