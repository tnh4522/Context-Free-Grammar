#ifndef _FC_
#define _FC_

#include <string>
#include <iomanip>
#include <iostream>
#include "StackTemplate.h"
using namespace std;

bool endsWith(const string& a, const string& b) {
    //A = ...B ?
    if (a.length() < b.length()) {
        return false;
    }
    return a.compare(a.length() - b.length(), b.length(), b) == 0;
}
bool isNumber(string s){
    bool valid = true;
    for (int i = 0; i< s.length(); i++){
        if((s[i] >= '0')&&(s[i] <= '9')||(s[i] == '.')){
            continue;
        }
        else{
            valid = false;
            break;
        }
    }
    return valid;
}
bool hasSpace(string s){
    //check xâu có khoảng trắng k
    for (char c : s) {
        if (c == ' ') {
            return true;
            break;
        }
    }
    return false;
}
bool isKeyword(string s){
    string keyword[] = {"auto", "break", "case", "char", "const", "continue", "default",
                        "double","do", "else", "enum", "extern", "float", "for", "goto",
                        "if", "long", "register", "return", "short", "signed", "sizeof",
                        "static", "struct", "switch", "typedef", "union", "unsigned", "void",
                        "volatile", "while", "byte", "integer", "real", "begin", "end", "read",
                        "var", "write", "true", "false", "then", "int", "id"};
    for (int i = 0; i < (sizeof(keyword)/sizeof(string)); i++){
        if (s == keyword[i]) return true;
    }
    return false;
}
bool isOperator(char ch){
    string value = "+-*/<>!";
    for (int i = 0; i < value.length(); i++){
        if (ch == value[i]) return true;
    }
    return false;
}
bool isSubstring(const string& a, const string& b) {
    //A chứa B ?, có phân biệt B' với B
    bool found = false;
    string temp;
    for (int i = 0; i < a.length(); i++){
        temp = "";
        if (a[i] == b[0]){
            found = true;
            for (int j = 0; j <= b.length(); j++){
                if (j == b.length()){
                    if (a[j+i] == '\''){
                        found = false;
                    }
                }else{
                    temp += a[j+i];
                    if (temp == b && (a[j+i+1] != '\'')){
                        return true;
                    }
                    else{
                        if(b[j] != a[i+j]){
                            found = false;
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool isSeparator(char ch){
    string value = ",;(){}[]:=";
    for (int i = 0; i < value.length(); i++){
        if (ch == value[i]) return true;
    }
    return false;
}
bool isIdentifier(string s){
    bool valid = true;

    if(isKeyword(s)) valid = false;
    if (valid){
        if((s[0] >= '0') && (s[0] <= '9')) valid = false;
    }
    if (valid){
        for (int i = 0; i < s.length(); i++){
            if(((s[i]>='a')&&(s[i]<='z'))||((s[i]>='A')&&(s[i]<='Z'))||((s[i]>='0')&&(s[i]<='9'))||(s[i]=='_')){
                continue;
            }
            else{
                valid = false;
                break;
            }
        }
    }
    return valid;
}
bool containsKeyword(const std::string& x) {
    string keywords[] = {"auto", "break", "case", "char", "const", "continue", "default",
                        "double","do", "else", "enum", "extern", "float", "for", "goto",
                        "if", "long", "register", "return", "short", "signed", "sizeof",
                        "static", "struct", "switch", "typedef", "union", "unsigned", "void",
                        "volatile", "while", "byte", "integer", "real", "begin", "end", "read",
                        "var", "write", "true", "false", "then", "int", "id"};
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (size_t i = 0; i < x.size(); ++i) {
        for (int j = 0; j < numKeywords; ++j) {
            if (x.substr(i, keywords[j].size()) == keywords[j]) {
                if ((i == 0 || !isalpha(x[i - 1])) && (i + keywords[j].size() == x.size() || !isalpha(x[i + keywords[j].size()]))) {
                    return true;
                }
            }
        }
    }

    return false;
}

void printSpam(string x, int number){
    //spam ký tự x, số lần number
    for (int i = 0; i < number; i++){
        cout << x;
    }
}
void printSpecial(const string& symbol, const int& left = 4, const int& right = 4, const string& wall = "|"){
    int x = symbol.length();
    cout << symbol;
    if (symbol == "ε"){x--;}
    printSpam(" ", left - x);
    cout << wall;
    printSpam(" ", right);
}
void printHorizontalLine(int columnWidth, int columnCount, const string& symbol = "|", const string& symbol_r = "|", const string& sSpam = "-"){
    //in đường thẳng, kẻ theo bảng
    for (int i = 0; i < columnCount; i++){
        cout << symbol;
        printSpam(sSpam, columnWidth - 1);
        cout << symbol_r;
    }
    cout << endl;
}
void printCenteredString(const string& str, int width, const string& symbol) {
    //im một chuỗi ở giữa cân đối với 2 symbol
    int leftSpace = (width - str.length()) / 2;
    int rightSpace = width - leftSpace - str.length();
    std::cout << symbol << std::setw(leftSpace) << "" << str << std::setw(rightSpace) << symbol;
}
void removeSubstringFromEnd(string &a, const string &b) {
    // Kiểm tra xem chuỗi b có nằm ở cuối chuỗi a không
    if (a.length() >= b.length() && a.substr(a.length() - b.length()) == b) {
        // Nếu có, lsoại bỏ chuỗi b từ cuối chuỗi a
        a.erase(a.length() - b.length());
    }
}

string getUnique(string& input){
    //aaabsdd = absd
    string output ="";
     for (char c : input) {
        bool found = false;
        for (char uniqueChar : output) {
            if (c == uniqueChar) {
                found = true;
                break;
            }
        }
        if (!found) {
            output += c;
        }
    }
    return output;
};
string removeSpaces(string str) {
    //a b c = abc
    string output;
    int length = str.length();
    int countSpaces = 0;
    
    for (int i = 0; i < length; ++i) {
        if (str[i] == ' ') {
            for (int j = i; j < length - 1; ++j) {
                str[j] = str[j + 1];
            }
            length--;
            i--;
        }
    }
    // Cắt bớt phần dư sau khi xóa các khoảng trắng
    str.resize(length);
    output = str;
    return output;
}
string getErrEpsilon(){
    //trả về lỗi khi chuyển từ epsilon sang, thuận tiện cho việc so sánh ký tự đặc biệt 
    string x = "ε";
    return string(1, x[0]);
}
string processString(string s) {
    //giãn cách ký tự nếu chuỗi k có khoảng trắng
    bool hasSpaces = hasSpace(s);
    string result ="";
    if (hasSpaces) {
        return s;
    } else {
        for (int i = 0; i < s.length(); i++){
            if (s[i] == '\'') continue;
            else{
                if (s[i + 1] == '\''){
                    result += string(1, s[i]);
                    for(int j = i+1; j < s.length(); j++){
                        if (s[j] == '\''){
                            result+= string(1, s[j]);
                        }else break;
                    }
                    result += " ";
                }else{
                    result += string(1, s[i]);
                    result += " ";
                }
            }
        }
    }
    return result;
}
string getDiffString(const string &a,const string &b){
    //return B - A
    string output;
    for (char c : b) {
        bool found = false;
        for (char aChar : a) {
            if (c == aChar) {
                found = true;
                break;
            }
        }
        if (!found) {
            output.push_back(c);
        }
    }
    return output;
}
string reverseString(const string &input){
    //abc = cba
    string output;
    for (int i = input.length() - 1; i >= 0; --i) {
        output.push_back(input[i]);
    }
    return output;
}
string replaceSubstring(string a, string b, string replacementSymbol) {
    //A chứa B ? thay B trong A = string
    size_t pos = a.find(b);
    if (pos != string::npos){
        a.replace(pos, b.length(), replacementSymbol);
    }
    return a;
}

LinkedList<string> getToken_Lord(string s){
    //hàm có chức năng giống tách ký hiệu, na ná như bộ phân tích từ vựng nhưng hơi lỏ, không tách được số >= 10
    LinkedList<string> list;
    string temp = "";
    Stack<char> st;
    if (s.length() == 1){
        list.AddTail(s);
    }
    else if (s.length() == 2 && (string(1, s[0]) == getErrEpsilon())){
        list.AddTail(s);
    }
    else{
        if(!containsKeyword(s) && !hasSpace(s)){
            s = processString(s);
        }
        for (int i = 0; i < s.length(); i++){
            if (s[i] == ' '){
                continue;
            }else{
                st.Push(s[i]);
                if (s[i] == '.'){
                    if (!(s[i + 1] >= '0' && s[i + 1] <= '9')){
                        st.Pop();
                        list.AddTail(st.toString());
                        st.Destroy();
                        st.Push('.');
                    }
                }
                if (s[i] == '\''){
                    st.Pop();
                    continue;
                }
                else{
                    if (s[i + 1] == '\''){
                        for (int j = i+1; j < s.length(); j++){
                            if (s[j] == '\''){
                                st.Push('\'');
                            }else break;
                        }
                        list.AddTail(st.toString());
                        st.Destroy();
                        continue;
                    }
                }
                if (isSeparator(st.Top()) || isOperator(st.Top())){
                    list.AddTail(string(1, st.Top()));
                    st.Pop();
                }
                else{
                    temp = st.toString();
                    if (temp != ""){
                        if ((isKeyword(temp) || isNumber(temp)) && (s[i + 1] == ' ' || isSeparator(s[i + 1]) || isOperator(s[i + 1])) && s[i + 1] != '\0'){
                            list.AddTail(temp);
                            st.Destroy();
                        }
                        else{
                            if (s[i + 1] == ' ' || isSeparator(s[i + 1]) || isOperator(s[i + 1]) || s[i + 1] == '\0'){
                                list.AddTail(temp);
                                st.Destroy();
                            }
                            else{
                                continue;
                            }
                        }
                    }
                }
            }
        }
    }
    return list;
} 

#endif