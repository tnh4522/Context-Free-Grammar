#ifndef _CFG_
#define _CFG_

#include "Prod.h"
#include <fstream>
#include <sstream>
#include "StackTemplate.h"
#include "LinkedListTemplate.h"
#include "PredictiveParsingTable.h"
/*Văn phạm G(Σ, Δ, s, p):
    + Σ: Tập hữu hạn các ký hiệu kết thúc (chữ thường)
    + Δ: Tập hữu hạn các ký hiệu chưa kết thúc (chữ hoa)
    + s: Ký hiệu bắt đầu, s ∈ Δ (nằm bên trái của sản xuất)
    + p: tập các sản xuất có dạng A -> α/ẞ với A ∈ Δ và α/ẞ ∈ (Σ giao Δ)*
*/
class CFG
{
public:
    string s;
    LinkedList<Prod> p;
    LinkedList<string> sigma;
    LinkedList<string> delta;

    void checkSyntaxUsePredict_View(string);
    void deploy(Stack<string>&, const Prod&);
    void fixStack(Stack<string>&, const string&);
    void matching(Stack<string>&, LinkedList<string>&);

    bool belongToSigma(string) const;
    bool belongToDelta(string) const;
    bool checkSyntaxUsePredict(string);

    LinkedList<string> getToken(string) const;

    friend ostream &operator<<(ostream &, const CFG &);

    CFG(string);
    ~CFG();
};

void CFG::checkSyntaxUsePredict_View(string x){
    cout << *this << endl;
    cout << "Xau x: " << x << endl << endl;
    M m(this->p, this->delta, this->sigma);
    cout << "Bang tien doan M " << endl;
    m.PrintTable();
    cout << endl;
    cout << "Phan tich cu phap dung Bang Tien Doan" << endl;
    Stack<string> stack;
    stack.Push(this->s);                                            //Stack  = S$;
    LinkedList<string> buffer;                                  
    buffer = this->getToken(x);                                     //Buffer = x$;
    int i = 0, stt = 7, stac_k = 35, buffe_r = 35, hd = 25;
    printSpam("_", stt + stac_k + buffe_r + hd); cout << endl;
    cout << setw(stt) << left << "STT " << setw(stac_k) << right << "STACK" << setw(buffe_r) << right << "BUFFER" << setw(hd) << right << "Hanh Dong" << endl;
    printSpam("¯", stt + stac_k + buffe_r + hd); cout << endl;
    bool emptyBuffer = false;    
    while (true){                                                   //Lặp
        cout << setw(stt) << left << i;
        if (stack.isEmpty() && buffer.isEmpty()){                   //If (Stack là $) và (Buffer là $)
            cout << setw(stac_k) << right << stack.toStringTopDown() + "$";
            cout << setw(buffe_r) << right << buffer.toString() + "$";
            cout << setw(hd+3) << right << "Chap Nhan ! " << endl;
            return;                                                 //x đúng cú pháp, dừng vòng lặp
        }
        else if(this->belongToSigma(stack.Top()) && this->belongToSigma(buffer.getHead())){               //a ∈ Σ ở đỉnh stack và buffer
            cout << setw(stac_k) << right << stack.toStringTopDown() + "$";
            cout << setw(buffe_r) << right << buffer.toString() + "$";
            cout << setw(hd-1) << right << "Doi sanh" << endl;
            this->matching(stack, buffer);                    //xx
            emptyBuffer = buffer.isEmpty() ? true : false;
        }
        else if((this->belongToDelta(stack.Top()) && (this->belongToSigma(buffer.getHead()))) || emptyBuffer){              //a ∈ Σ ở đỉnh stack & a ∈ Δ ở đỉnh buffer
            Prod prod;
            if (emptyBuffer){
                prod = m(stack.Top(), "$");
            }else{
                prod = m(stack.Top(), buffer.getHead());
            }
            if (prod.alpha.isEmpty()){
                cout << setw(stac_k) << right << stack.toStringTopDown() + "$";
                cout << setw(buffe_r) << right << buffer.toString() + "$";
                cout << setw(hd+9) << right << "Khong chap nhan !" << endl;
                return;
            }else{
                cout << setw(stac_k) << right << stack.toStringTopDown() + "$";
                cout << setw(buffe_r) << right << buffer.toString() + "$";
                cout << setw(hd) << right << "Trien khai "<< prod.toString() << endl;
                this->deploy(stack, prod);                
            }
        }
        else{
            cout << setw(stac_k) << right << stack.toStringTopDown() + "$";
            cout << setw(buffe_r) << right << buffer.toString() + "$";
            cout << setw(hd+9) << right << "Khong chap nhan !" << endl;
            return;
        }
        if (i > 100){
            cout << "Chuong trinh loi ! " << endl; 
        }
        i++;    
    }
}

void CFG::deploy(Stack<string>& stack, const Prod& prod){
    if (prod.alpha.getHead() == "ε"){
        stack.Pop();
    }else{
        stack.Pop();
        this->fixStack(stack, prod.alpha.getHead());
    }
}

void CFG::fixStack(Stack<string>& stack, const string& alpha){
    LinkedList<string> list_token = this->getToken(alpha);
    list_token.reverseList();
    for (Node<string>* p = list_token.head; p != NULL; p = p->next){
        stack.Push(p->data);
    }
}

void CFG::matching(Stack<string>& stack, LinkedList<string>& list){
    if (stack.Top() == list.getHead()){
        stack.Pop();
        list.DelHead();
    }
}

bool CFG::belongToSigma(string x) const{
    for (Node<string>* p = this->sigma.head; p != NULL; p = p->next){
        if (p->data == x) return true;
    }
    return false;
}

bool CFG::belongToDelta(string x) const{
    for (Node<string>* p = this->delta.head; p != NULL; p = p->next){
        if (p->data == x) return true;
    }
    return false;
}

bool CFG::checkSyntaxUsePredict(string x){
    M m(this->p, this->delta, this->sigma);
    Stack<string> stack;
    stack.Push(this->s);                                            //Stack  = S$;
    LinkedList<string> buffer;                                  
    buffer = this->getToken(x);                                     //Buffer = x$;
    int i = 0;
    bool emptyBuffer = false;    
    while (true){                                                   //Lặp
        if (stack.isEmpty() && buffer.isEmpty()){                   //If (Stack là $) và (Buffer là $)
            return true;                                                 //x đúng cú pháp, dừng vòng lặp
        }
        else if(this->belongToSigma(stack.Top()) && this->belongToSigma(buffer.getHead())){               //a ∈ Σ ở đỉnh stack và buffer
            this->matching(stack, buffer);                    //xx
            emptyBuffer = buffer.isEmpty() ? true : false;
        }
        else if((this->belongToDelta(stack.Top()) && (this->belongToSigma(buffer.getHead()))) || emptyBuffer){              //a ∈ Σ ở đỉnh stack & a ∈ Δ ở đỉnh buffer
            Prod prod;
            if (emptyBuffer){
                prod = m(stack.Top(), "$");
            }else{
                prod = m(stack.Top(), buffer.getHead());
            }
            if (prod.alpha.isEmpty()){
                return false;
            }else{
                this->deploy(stack, prod);                
            }
        }
        else{
            return false;
        }
        if (i > 100){ return false;}
        i++;    
    }
    return false;
}

LinkedList<string> CFG::getToken(string s) const{
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

ostream &operator << (ostream &out, const CFG &x){
    cout << "Van Pham G(Σ, Δ, s, p): " << endl;
    cout << "Σ: {" << x.sigma << "}" << endl;
    cout << "Δ: {" << x.delta << "}" << endl;
    cout << "s: " << x.s << endl;
    cout << "p: " << endl;
    for (Node<Prod>* p = x.p.head; p != NULL; p = p->next){
        cout << "  "<< setw(3) << left << p->data << endl;
    }
    return out;
}

CFG::CFG(string file_Name)
{
    ifstream file(file_Name);

    //Mở file, add các sản xuất
    if (file.is_open()){
        string line;
        Prod prod;
        while (getline(file, line))
        {
            stringstream ss(line);
            string cell;
            getline(ss, cell, ',');
            prod.A = cell;
            while (getline(ss, cell, ','))
            {
                prod.alpha.AddTail(cell);
            }
            this->p.AddTail(prod);
            prod.alpha.Destroy();
        }
        file.close();
    }else return;

    //Với A của sản xuất đầu tiên sẽ là ký hiệu bắt đầu
    this->s = this->p.head->data.A;

    //từ các sản xuất, lọc ký hiệu và thêm vào tập Σ và tập Δ
    for (Node<Prod>* p = this->p.head; p != NULL; p = p->next){
        this->delta.AddTail(p->data.A);
        for (Node<string>* k = p->data.alpha.head; k != NULL; k = k->next){
            if (k->data == "ε") continue;
            LinkedList<string> temp = this->getToken(k->data);
            for (Node<string>* t = temp.head; t != NULL; t = t->next){
                this->sigma.AddTail(t->data);
            }
        }
    }
    
    //loại bỏ các ký hiệu của tập Σ bị trùng với tập Δ
    Node<string>* current = this->sigma.head;
    while (current != NULL) {
        if (this->delta.isExist(current->data)) {
            this->sigma.DelData(current->data);
        }
        current = current->next;
    }
    
    //loại bỏ các ký hiệu lặp lại trong tập Σ
    this->sigma.beContainUniqueItem();
}

CFG::~CFG()
{
    this->p.Destroy();
    this->delta.Destroy();
    this->sigma.Destroy();
}

#endif