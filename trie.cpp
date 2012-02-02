#include <cstdio>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class trie {
private:
	class node {
	private:
		friend class trie;
		node* parent;
		list<node*> children;
		int start, end;

		void check_index_contains(const int &index);
	public:
		static const int INF = -2;
		node* reference;
		node(node* _p = NULL, int _s = 0, int _e = 0, node* _r = NULL) 
			: start(_s), end(_e), parent(_p), reference(_r) {};

		node* gemmate(const int &index);
		node* add(const int &pos);
		bool contains(const int &index);
	};

public:
	class iterator {
	public:
		class OutOfRange {};
	private:
		friend class trie;
		friend class node;
		trie* parent;
		node* exp_itr;
		int imp_itr;

		iterator(trie* _p, node* _eit, int _iitm);
		iterator(trie* _p, node* _eit = NULL);

		bool is_implicit();
		bool is_explicit();
	public:
		iterator() : exp_itr(NULL) {};
		iterator& operator= (const iterator&);
		
		iterator& operator+= (const char&);
		iterator& operator+= (const string&);

		iterator& operator-= (const int&);

		const iterator operator+ (const char&) const;
		const iterator operator+ (const string&) const;
		
		const iterator operator- (const int&) const;
		
		bool operator== (const iterator&) const;
		bool operator!= (const iterator&) const;
	};

private:
	node* dummy;
	node* root;
	iterator start;
	string text;

	void push(char _ch);
	void delete_node(node*&);
public:
	trie(const string&);
	~trie();

	void add(const string&);
	void add(const char&);

	iterator begin();
	iterator end();
	iterator find();
	
};


//////////////////////NODE////////////////////////////

void trie::node::check_index_contains(const int &index) {
	if (!this->contains(index)) {
		throw "The index is not contained in the node.";
	}
}

bool trie::node::contains(const int &index) {
	return this->start <= index && (index <= this->end || this->end == node::INF);
}

trie::node* trie::node::gemmate(const int &index) {
	this->check_index_contains(index);
	node* mnode = new node(this->parent, this->start, index, this->reference);
	for (list<node*>::iterator ch = mnode->parent->children.begin(); ch != mnode->parent->children.end(); ++ch) {
		if (*ch == this) {
			*ch = mnode;
			break;
		}
	}
	mnode->children.push_back(this);

	this->parent = mnode;
	this->start = index + 1;
	return mnode;
}

trie::node* trie::node::add(const int &pos) {
	node* new_node = new node(this, pos, node::INF);
	this->children.push_back(new_node);
	return new_node;
}

//////////////////////ITERATOR////////////////////////
trie::iterator::iterator(trie* _p, node* _eit, int _iit) {
	this->parent = _p;
	this->exp_itr = _eit;
	this->imp_itr = _iit;
}

trie::iterator::iterator(trie* _p, node* _eit) {
	this->parent = _p;
	this->exp_itr = _eit;
	this->imp_itr = 0;
	if (this->exp_itr != NULL) {
		this->imp_itr = _eit->start;
	}
}

bool trie::iterator::is_explicit() {
	return this->exp_itr != NULL && this->imp_itr == this->exp_itr->end && (this->exp_itr == this->parent->root 
		|| this->exp_itr == this->parent->dummy || this->exp_itr->children.size() >= 2);
}

bool trie::iterator::is_implicit() {
	return this->exp_itr != NULL && !this->is_explicit();
}

trie::iterator& trie::iterator::operator= (const iterator &_itr) {
	if (this == &_itr){
		return *this;
	}

	this->parent = _itr.parent;
	this->exp_itr = _itr.exp_itr;
	this->imp_itr = _itr.imp_itr;
	return *this;
}

trie::iterator& trie::iterator::operator+= (const char &_ch) {
	if (this->exp_itr != NULL) {
		if (this->exp_itr == this->parent->dummy) {
			return *this = this->parent->begin();
		} else if (this->exp_itr->contains(this->imp_itr + 1) && this->imp_itr + 1 < this->parent->text.length()) {
			if (this->parent->text[this->imp_itr + 1] == _ch) {
				++this->imp_itr;
				return *this;
			}
		} else {
			for (list<node*>::iterator child = this->exp_itr->children.begin(); child != this->exp_itr->children.end(); ++child) {
				if (this->parent->text[(*child)->start] == _ch) {
					this->exp_itr = *child;
					this->imp_itr = (*child)->start;
					return *this;
				}
			}
		}
	}
	return *this = this->parent->end();
}

trie::iterator& trie::iterator::operator+= (const string &_s) {
	for (int i = 0; i < _s.length() && *this != this->parent->end(); ++i) {
		*this += _s[i];
	}
	return *this;
}

trie::iterator& trie::iterator::operator-= (const int &_i){
	if (this->exp_itr == NULL) {
		return *this = this->parent->end();
	}

	if (this->exp_itr->contains(this->imp_itr - 1)) {
		return *this = iterator(this->parent, this->exp_itr, this->imp_itr - 1);
	}
	
	return *this = iterator(this->parent, this->exp_itr->parent, this->exp_itr->parent->end);
}

const trie::iterator trie::iterator::operator+ (const char &_ch) const {
	return iterator(*this) += _ch;
}

const trie::iterator trie::iterator::operator+ (const string &_s) const {
	return iterator(*this) += _s;
}

bool trie::iterator::operator== (const iterator &_itr) const {
	return this->exp_itr == _itr.exp_itr && this->imp_itr == _itr.imp_itr && this->parent == _itr.parent;
}

bool trie::iterator::operator!= (const iterator &_itr) const {
	return !(*this == _itr);
}

////////////////TRIE//////////////////////////////
trie::trie(const string &_s) {
	this->dummy = new node(NULL);
	this->root = new node(NULL, -1, -1, this->dummy);
	this->start = this->begin();

	this->text.reserve(_s.length());

	for (int i = 0; i < _s.length(); ++i) {
		this->push(_s[i]);
	}
}

trie::~trie() {
	this->delete_node(this->root);
	this->delete_node(this->dummy);
}

void trie::delete_node(node* &_node) {
	if (_node != NULL) {
		for (list<node*>::iterator ch = _node->children.begin(); ch != _node->children.end(); ++ch) {
			this->delete_node(*ch);
		}
		delete _node;
	}
}

void trie::push(char _ch) {
	int pos = this->text.length();
	this->text += _ch;
	
	node *new_node = NULL, *prev_node = NULL;
	iterator next_itr;
	while ((this->start + this->text[pos]) == this->end()) {
		if (this->start.is_explicit()) {
			this->start.exp_itr->add(pos);
			if (prev_node != NULL) {
				prev_node->reference = this->start.exp_itr;
				prev_node = NULL;
			}
			this->start = iterator(this, this->start.exp_itr->reference);
		} else {
			new_node = this->start.exp_itr->gemmate(this->start.imp_itr);
			new_node->add(pos);
			this->start = iterator(this, new_node->parent->reference);
			for (int i = new_node->start; i <= new_node->end; ++i) {
				this->start += this->text[i];
			}
			if (this->start == this->end()) {
				throw "";
			}

			if (prev_node != NULL) {
				prev_node->reference = new_node;
			}
			prev_node = new_node;
		}
	}

	
	if (prev_node != NULL) {
		prev_node->reference = this->start.exp_itr;
	}
	this->start += _ch;
}

trie::iterator trie::begin() {
	return iterator(this, this->root, this->root->start);
}

trie::iterator trie::end() {
	return iterator(this, NULL);
}


int test_trie() {
	ifstream fi("input.txt");
	ofstream fo("output.txt");
	int n;
	string s;
	
	fi >> s >> n;
	trie bor(s);
	for (int i = 0; i < n; ++i) {
		string t;
		fi >> t;
		fo << (bor.begin() + t != bor.end()) << " ";
	}
	
	fi.close();
	fo.close();
	return 0;
}




