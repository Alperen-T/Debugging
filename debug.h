#include <vector>
#include <string>
#include <bitset>
#include <array>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

template<typename T>
vector<string> debug_print(T x);

vector<string> debug_print(bool flag);

vector<string> debug_print(char c);

vector<string> debug_print(string str);

template<typename T, typename T2>
vector<string> debug_print(pair<T, T2> p);

template<size_t SIZE>
vector<string> debug_print(bitset<SIZE> bitst);

template<typename T>
vector<string> debug_print(vector<T> vec, bool align = false);

template<typename T>
vector<string> debug_print(vector<vector<T>> vec, bool align = true);

template<typename T, size_t SIZE>
vector<string> debug_print(array<T, SIZE> arr, bool align = false);

template<typename T, size_t SIZE, size_t SIZE2>
vector<string> debug_print(array<array<T, SIZE2>, SIZE> arr, bool align = true);

template<typename T>
vector<string> debug_print(stack<T> stk);

template<typename T>
vector<string> debug_print(queue<T> que);

template<typename T>
vector<string> debug_print(deque<T> dque);

template<typename T>
vector<string> debug_print(priority_queue<T> pq);

template<typename T>
vector<string> debug_print(set<T> st);

template<typename T>
vector<string> debug_print(multiset<T> st);

template<typename T>
vector<string> debug_print(unordered_set<T> st);

template<typename T, typename T2>
vector<string> debug_print(map<T, T2> mp);

template<typename T, typename T2>
vector<string> debug_print(unordered_map<T, T2> mp);

// ANY VARIABLE

template<typename T>
vector<string> debug_print(T x){
    return {to_string(x)};
}

// BOOLEAN

vector<string> debug_print(bool flag){
    return {flag ? "true" : "false"};
}

// CHAR

vector<string> debug_print(char c){
    return {string("'") + c + "'"};
}


// STRING

vector<string> debug_print(string str){
    return {"\"" + str + "\""};
}

vector<string> debug_print(const char* str){
    return {string{"\""} + str + "\""};
}

// BITSET

template<size_t SIZE>
vector<string> debug_print(bitset<SIZE> bitst){
    return {"0b" + bitst.to_string()};
}

// PAIR 

template<typename T, typename T2>
vector<string> debug_print(pair<T, T2> p){
    return {"(" + debug_print(p.first)[0] + ", " + debug_print(p.second)[0] + ")"};
}

// VECTOR

template<typename T>
vector<string> debug_print(vector<T> vec, bool align){
    string output;

    output += "[";

    if(align) output += " ";
    
    for(int i = 0; i < vec.size(); i++){
        output += debug_print(vec[i])[0];

        if(i != (int)vec.size() - 1) output += ", "; 
    }

    output += "]";

    return {output};
}

template<typename T>
vector<string> debug_print(vector<vector<T>> vec, bool align){
    vector<string> outputs;

    outputs.push_back("[");

    for(int i = 0; i < vec.size(); i++){
        vector<string> outputs2 = debug_print(vec[i], align);

        for(auto output : outputs2){
            if(outputs.front().size() == 1) outputs[0] += output + "#";
            else outputs.push_back("#" + output + "#");
        }
    }

    if(outputs.back().back() == '#') outputs.back().pop_back();
    outputs.back() += ']';

    return outputs;
}

// ARRAY

template<typename T, size_t SIZE>
vector<string> debug_print(array<T, SIZE> arr, bool align){
    string output;

    output += "[";

    if(align) output += " ";
    
    for(int i = 0; i < arr.size(); i++){
        output += debug_print(arr[i])[0];

        if(i != (int)arr.size() - 1) output += ", "; 
    }

    output += "]";

    return {output};
}

template<typename T, size_t SIZE, size_t SIZE2>
vector<string> debug_print(array<array<T, SIZE2>, SIZE> arr, bool align){
    vector<string> outputs;

    outputs.push_back("[");

    for(int i = 0; i < arr.size(); i++){
        vector<string> outputs2 = debug_print(arr[i], align);

        for(auto output : outputs2){
            if(outputs.front().size() == 1) outputs[0] += output + "#";
            else outputs.push_back("#" + output + "#");
        }
    }

    if(outputs.back().back() == '#') outputs.back().pop_back();
    outputs.back() += ']';

    return outputs;
}

// STACK

template<typename T>
vector<string> debug_print(stack<T> stk){
    string output;

    output += ">";

    vector<string> outputs; 

    while(!stk.empty()){
        outputs.push_back(debug_print(stk.top())[0]);

        stk.pop();
    }

    reverse(outputs.begin(), outputs.end());

    for(int i = 0; i < outputs.size(); i++){
        output += outputs[i];

        if(i != (int)outputs.size() - 1) output += ", ";
    }

    output += ">";

    return {output};
}

// QUEUE

template<typename T>
vector<string> debug_print(queue<T> que){
    string output;

    output += "<";

    while(!que.empty()){
        output += debug_print(que.front())[0];

        que.pop();

        if(!que.empty()) output += ", ";
    }

    output += "<";

    return {output};
}

// DEQUE

template<typename T>
vector<string> debug_print(deque<T> dque){
    string output;

    output += "<";

    while(!dque.empty()){
        output += debug_print(dque.front())[0];

        dque.pop_front();

        if(!dque.empty()) output += ", ";
    }

    output += ">";

    return {output};
}

// PRIORITY_QUEUE

template<typename T>
vector<string> debug_print(priority_queue<T> pq){
    string output;

    output += "{";

    while(!pq.empty()){
        output += debug_print(pq.top())[0];

        pq.pop();

        if(!pq.empty()) output += ", ";
    }

    output += "}";

    return {output};
}

// SET

template<typename T>
vector<string> debug_print(set<T> st){
    string output = "{";

    for(auto it = st.begin(); it != st.end(); it++){
        output += debug_print(*it)[0];

        if(next(it) != st.end()) output += ", ";
    }

    output += "}";

    return {output};
}

// SET

template<typename T>
vector<string> debug_print(multiset<T> st){
    string output = "{";

    for(auto it = st.begin(); it != st.end(); it++){
        output += debug_print(*it)[0];

        if(next(it) != st.end()) output += ", ";
    }

    output += "}";

    return {output};
}

// UNORDERED_SET

template<typename T>
vector<string> debug_print(unordered_set<T> st){
    string output = "{";

    for(auto it = st.begin(); it != st.end(); it++){
        output += debug_print(*it)[0];

        if(next(it) != st.end()) output += ", ";
    }

    output.pop_back();
    output.pop_back();

    output += "}";

    return {output};
}

// MAP

template<typename T, typename T2>
vector<string> debug_print(map<T, T2> mp){
    vector<string> outputs;

    outputs.push_back("{");

    for(auto p : mp){
        string output = "( " + debug_print(p.first)[0] + ", " + debug_print(p.second)[0] + ")"; 

        if(outputs.front().size() == 1) outputs[0] += output + "#";
        else outputs.push_back("#" + output + "#");
    }

    if(outputs.back().back() == '#') outputs.back().pop_back();
    outputs.back() += '}';

    return outputs;
}

// UNORDERED_MAP

template<typename T, typename T2>
vector<string> debug_print(unordered_map<T, T2> mp){
    vector<string> outputs;

    outputs.push_back("{");

    for(auto p : mp){
        string output = "( " + debug_print(p.first)[0] + ", " + debug_print(p.second)[0] + ")"; 

        if(outputs.front().size() == 1) outputs[0] += output + "#";
        else outputs.push_back("#" + output + "#");
    }

    if(outputs.back().back() == '#') outputs.back().pop_back();
    outputs.back() += '}';

    return outputs;
}

// DEBUG

vector<string> fix_outputs(vector<string> outputs){
    int n = outputs.size();

    for(int i = 0; i < n; i++) reverse(outputs[i].begin(), outputs[i].end());

    vector<string> fixed_outputs(n, "");

    vector<int> pointers(n, 0);

    bool isunfinished = true;

    while(isunfinished){
        bool flag = true;

        for(int i = 0; i < n; i++){
            if(pointers[i] < outputs[i].size()){
                if(outputs[i][pointers[i]] != ' ') flag = false;
            }
        }

        if(flag){
            for(int i = 0; i < n; i++){
                if(pointers[i] < outputs[i].size()){
                    fixed_outputs[i] += outputs[i][pointers[i]++];
                }
            }
        }
        else{
            for(int i = 0; i < n; i++){
                if(pointers[i] < outputs[i].size()){
                    if(outputs[i][pointers[i]] == ' ') fixed_outputs[i] += ' ';
                    else fixed_outputs[i] += outputs[i][pointers[i]++];
                }
            }
        }

        isunfinished = false;

        for(int i = 0; i < n; i++){
            if(pointers[i] < outputs[i].size()) isunfinished = true;
        }
    }

    for(int i = 0; i < n; i++) reverse(fixed_outputs[i].begin(), fixed_outputs[i].end());

    for(int i = 0; i < n; i++){
        for(int j = 0; j < fixed_outputs[i].size(); j++){
            if(fixed_outputs[i][j] == ' '){
                fixed_outputs[i].erase(fixed_outputs[i].begin() + j);
                break;
            }
        }

        for(int j = 0; j < fixed_outputs[i].size(); j++){
            if(fixed_outputs[i][j] == '#') fixed_outputs[i][j] = ' ';
            else break;
        }

        for(int j = (int)fixed_outputs[i].size() - 1; j >= 0; j--){
            if(fixed_outputs[i][j] == '#') fixed_outputs[i][j] = ' ';
            else break;
        }
    }

    return fixed_outputs;
}

void debug_iterate(bool isline, istream_iterator<string> it){
    if(isline) cout << "}\n";
    else cout << "\n";
}

template<typename T, typename... Args>
void debug_iterate(bool isline, istream_iterator<string> it, T x, Args... args){
    if(isline) cout << "    ";
    cout << *it << " = ";
    
    vector<string> outputs = debug_print(x);

    if((outputs[0][0] == '[' && outputs[0][1] == '[') || (outputs[0][0] == '{' && outputs[0][1] == '(')) outputs = fix_outputs(outputs);

    for(int i = 0; i < outputs.size(); i++){
        if(i != 0) for(int j = 0; j < (isline ? 7 : 3) + (*it).size(); j++) cout << " ";

        cout << outputs[i] << "\n";
    }

    debug_iterate(isline, next(it), args...);
}

void cdebug_iterate(bool isline, istream_iterator<string> it){
    if(isline) cerr << "}\n";
    else cerr << "\n";
}

template<typename T, typename... Args>
void cdebug_iterate(bool isline, istream_iterator<string> it, T x, Args... args){
    if(isline) cerr << "    ";
    cerr << *it << " = ";
    
    vector<string> outputs = debug_print(x);

    if((outputs[0][0] == '[' && outputs[0][1] == '[') || (outputs[0][0] == '{' && outputs[0][1] == '(')) outputs = fix_outputs(outputs);

    for(int i = 0; i < outputs.size(); i++){
        if(i != 0) for(int j = 0; j < isline ? 7 : 3 + (*it).size(); j++) cerr << " ";

        cerr << outputs[i] << "\n";
    }

    cdebug_iterate(isline, next(it), args...);
}

string replace_commas(string str){
    string ans;

    for(int i = 0; i < str.size(); i++){
        if(i + 1 < str.size() && str[i] == ',' && str[i + 1] == ' ') continue;
        else ans += str[i];
    }

    return ans;
}

#define debug(args...){                                    \
    string _varnames = #args;                              \
    _varnames = replace_commas(_varnames);                 \
    stringstream _varstream(_varnames);                    \
    istream_iterator<string> _varit(_varstream);           \
    debug_iterate(false, _varit, args);                    \
}                                                          \

#define debugl(args...){                                   \
    string _varnames = #args;                              \
    _varnames = replace_commas(_varnames);                 \
    stringstream _varstream(_varnames);                    \
    istream_iterator<string> _varit(_varstream);           \
    cout << "Debug[" << __LINE__ << "]{\n";                \
    debug_iterate(true, _varit, args);                     \
}

#define cdebug(args...){                                   \
    string _varnames = #args;                              \
    _varnames = replace_commas(_varnames);                 \
    stringstream _varstream(_varnames);                    \
    istream_iterator<string> _varit(_varstream);           \
    cdebug_iterate(false, _varit, args);                   \
}                                                          \

#define cdebugl(args...){                                  \
    string _varnames = #args;                              \
    _varnames = replace_commas(_varnames);                 \
    stringstream _varstream(_varnames);                    \
    istream_iterator<string> _varit(_varstream);           \
    cout << "Debug[" << __LINE__ << "]{\n";                \
    cdebug_iterate(true, _varit, args);                    \
}