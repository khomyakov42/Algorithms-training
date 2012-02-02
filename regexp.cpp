#include <list>
#include <queue>
#include <stack>
#include <stdarg.h>
#include <iostream>

using namespace std;

class RegExp {
private:
	class State {
	protected:
		friend class RegExp;
		State *next;
	public:
		State(State *n = nullptr) : next(n) { };
		virtual list<State*> step(const char&) { return list<State*>(); };
		virtual void set_next(State* &st) { this->next = st; };
		virtual bool reachable(State* &st) { return this == st; }
	};

	class Step : public State {
	private:
		char ch;
	public:
		Step(const char &_ch) : ch(_ch) { };
		virtual list<State*> step(const char&);
	};

	class Split : public State {
	private:
		State *path1, *path2, *out1, *out2;
	public:
		Split(State *p1, State *p2, State *o1, State *o2, State *n = nullptr) : path1(p1), path2(p2), out1(o1), out2(o2), State(n) { };
		virtual list<State*> step(const char&);
		virtual void set_next(State* &st);
		virtual bool reachable(State* &st);
	};

	class Dummy : public State {
	public:
		virtual list<State*> step(const char&);
	};

	class End : public State {	};

private:
	State *start, *end;

	string parse(const string&);
	State* compile(const string&);
public:
	RegExp(const string &);

	bool test(const string&);
};
/////////////////NODE////////////////////////////
list<RegExp::State*> RegExp::Step::step(const char &_ch) {
	list<State*> res;
	if (this->ch == _ch) {
		res.push_back(this->next);
	}
	return res;
}

list<RegExp::State*> RegExp::Split::step(const char &_ch) {
	list<State*> res;
	if (this->path2 == nullptr) {
		res.merge(this->next->step(_ch));
	} else {
		res.merge(this->path2->step(_ch));
	}

	res.merge(this->path1->step(_ch));
	return res;
}

bool RegExp::Split::reachable(State* &st) {
	return this->path1->reachable(st) || (this->path2 != nullptr && this->path2->reachable(st));
}

void RegExp::Split::set_next(State* &_nxt) {
	this->next = _nxt;

	if (this->out1 != nullptr && this->out1->next != this) {
		this->out1->set_next(_nxt);
	}

	if (this->path2 == nullptr) {
		this->path2 = _nxt;
//		this->out2 = _nxt;
	} else if (this->out2 != nullptr && this->out2->next != this){
		this->out2->set_next(_nxt);
	}
}

list<RegExp::State*> RegExp::Dummy::step(const char &_ch) {
	list<State*> res;
	res.push_back(this->next);
	return res;
}
///////////////ENDNODE//////////////////////////

string RegExp::parse(const string &s) {
	int n = 0, m = 0;
	string res;
	stack<pair<int, int>> S;

	for (int i = 0; i < s.length(); ++i){
		switch(s[i]){
		case '(':
			if(m > 1){ --m; res += '$'; }
			S.push(pair<int, int>(n, m));
			n = 0;
			m = 0;
			break;
		case '|':
			if(m == 0) { return ""; }
			while(--m > 0) { res += '$'; }	
			n++;
			break;
		case ')':
			if (S.empty() || m == 0) { return ""; }

			while(--m > 0) {	res += '$'; }
			for(; n > 0; n--) { res += '|'; }

			n = S.top().first;
			m = S.top().second;
			S.pop();
			m++;
			break;
		case '*':
		case '+':
		case '?':
			if(m == 0) { return ""; }
			res += s[i];
			break;
		default:
			if(m > 1){ --m; res += '$'; }
			res += s[i];
			m++;
			break;
		}
	}

	while(--m > 0) { res += '$'; }
	for(; n > 0; n--) { res += '|'; }

	return res;
}

RegExp::State* RegExp::compile(const string &postre) {
	typedef pair<State*, State*> Edge;
	stack<Edge> S;
	State *s;
	Edge e1, e2;

	for (int i = 0; i < postre.length(); ++i) {
		switch(postre[i]) {
		case '$':
			e2 = S.top(); S.pop();
			e1 = S.top(); S.pop();
			e1.second->set_next(e2.first);
			S.push(Edge(e1.first, e2.second));
			break;
		case '|':
			e2 = S.top(); S.pop();
			e1 = S.top(); S.pop();
			s = new Split(e1.first, e2.first, e1.second, e2.second);
			S.push(Edge(s, s));
			break;
		case '?':
			e1 = S.top(); S.pop();
			s = new Split(e1.first, nullptr, e1.second, nullptr);
			S.push(Edge(s, s));
			break;
		case '*':
			e1 = S.top(); S.pop();
			s = new Split(e1.first, nullptr, e1.second, nullptr);
			e1.second->set_next(s);
			S.push(Edge(s, s));
			break;
		case '+':
			e1 = S.top(); S.pop();
			s = new Split(e1.first, nullptr, e1.second, nullptr);
			e1.second->set_next(s);
			S.push(Edge(e1.first, s));
			break;
		case '.':
			s = new Dummy();
			S.push(Edge(s, s));
			break;
		default:
			s = new Step(postre[i]);
			S.push(Edge(s, s));
			break;
		}
	}

	S.top().second->set_next(this->end);

	return S.top().first;
}

RegExp::RegExp(const string &_s) {
	this->end = new End();
	this->start = this->compile(this->parse(_s));
}

bool RegExp::test(const string &s) {
	list<State*> states, next_states;
	int i = 0;
	states.push_back(this->start);
	for (; i < s.length() && states.size(); i++) {
		next_states.clear();
		for (list<State*>::iterator itr = states.begin(); itr != states.end(); ++itr) {
			next_states.merge((*itr)->step(s[i]));
		}

		states = next_states;
	}

	for (list<State*>::iterator itr = states.begin(); itr != states.end(); ++itr) {
		if ((*itr)->reachable(this->end)) {
			return true;
		}
	}

	return false;
}


#define st(re) { RegExp r(re);;
#define t(s, res) if (r.test(s) == res) cout << "ok" << endl; else cout << "fail in line: " << __LINE__ << endl;
#define et }

int test_regexp() {

	st("a?b")
		t("b", 1)
		t("a", 0)
		t("ab", 1)
	et

	st("ab?")
		t("a", 1)
		t("b", 0)
	et

	st("a.b")
		t("aab", 1)
		t("a", 0)
		t("ab", 0)
		t("abc", 0)
		t("abce", 0)
		t("abcdfsdfsdfssdfsdfs", 0)
	et

	st("..a")
		t("aaa", 1)
		t("a", 0)
		t("..a", 1)
		t("sadasd", 0)
	et

	st(".")
		t("a", 1)
		t("asd", 0);
		t("", 0);
	et

	st("a|b")
		t("a", 1)
		t("b", 1)
		t("ac", 0)
		t("c", 0)
	et

	st("ab|cd")
		t("ab", 1)
		t("cd", 1)
		t("abd", 0)
		t("acd", 0)
	et

	st("ab?")
		t("a", 1)
		t("ab", 1)
		t("ac", 0)
		t("cb", 0)
		t("b", 0)
		t("ba", 0)
	et

	st("a+")
		t("aaa", 1)
		t("ba", 0)
	et

	st("ba+")
		t("baa", 1)
		t("ba", 1)
		t("a", 0)
		t("aa", 0)
	et

	st("a*")
		t("a", 1)
		t("aaaaa", 1)
		t("", 1)
		t("ba", 0)
		t("aaaab", 0)
	et

	st(".*")
		t("a", 1)
		t("sadsadsaasd", 1)
		t("", 1)
	et

	st("a(b|c)d")
		t("abd", 1)
		t("acd", 1)
		t("aed", 0)
		t("ab", 0)
		t("cd", 0)
		t("bc", 0)
	et

	st("((ab)|(b+))c?d*")
		t("abcd", 1)
		t("abd", 1)
		t("abdddd", 1)
		t("ab", 1)

		t("bbcd", 1)
		t("bbbbd", 1)
		t("bbbbdddd", 1)
		t("b", 1)

		t("c", 0)
	et

	st("a?b?c?d?")
		t("a", 1)
		t("b", 1)
		t("c", 1)
		t("d", 1)
		t("ab", 1)
		t("ac", 1)
		t("ad", 1)
		t("bc", 1)
		t("bd", 1)
		t("cd", 1)

		t("da", 0)
		t("db", 0)
		t("dc", 0)
		t("ca", 0)
		t("cb", 0)
	et

	st(".a..b.")
		t("karabo", 1)
		t("kakabo", 1)

		t("karbo", 0)
		t("akkbo", 0)
	et

	st(".?a")
		t("ca", 1)
		t("a", 1)
		t("ac", 0)
	et

	st("a+b+c+")
		t("abc", 1)
		t("aabc", 1)
		t("abbbc", 1)
		t("abcc", 1)

		t("a+b+c", 0)
		t("abcabc", 0)
	et

	st("-?(0|1|2|3|4|5|6|7|8|9)+(,(0|1|2|3|4|5|6|7|8|9)+)?")
		t("1", 1)
		t("12", 1)
		t("-1", 1)
		t("-100", 1)
		t("1,2", 1)
		t("1,00002", 1)

		t(",", 0)
		t("", 0)
		t("0,", 0)
		t(",0", 0)
	et
	return 0;
}