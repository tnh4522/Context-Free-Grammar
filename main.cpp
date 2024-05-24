#include "3.Library/ContextFreeGrammar.h"

string getPredictData(int input){
    string output = "./2.Predictive_Parsing_Data/";
    switch (input)
    {
    case 1:
        //Số nguyên không âm
        output += "1.Non_Negative_Integer.csv";
        break;
    case 2:
        //Phép toán cơ bản: Cộng & Nhân & Đóng ngoặc id
        output += "2.Sum_Multi_Parentheses.csv";
        break;
    case 3:
        //Xâu từ ký tự a & 0
        output += "3.Spam_a_0.csv";
        break;
    case 4:
        //Một biến
        output += "4.Variable.csv";
        break;  
    default:
        output += "1.Non_Negative_Integer.csv";
        break;
    }
    return output;
}

string getPredict_X(int input){
    switch (input)
    {
    case 1:
        //Số nguyên không âm
        return "2024";
    case 2:
        //Phép toán cơ bản: Cộng & Nhân & Đóng ngoặc id
        return "id+(id*id)";
    case 3:
        //Xâu từ ký tự a & 0
        return "a0a";
    case 4:
        //Một biến ký tự lowwercase
        return "_variable";
    default:
        return "2024";
    }
}

int main(){
    CFG cfg(getPredictData(2));
    cfg.checkSyntaxUsePredict_View(getPredict_X(2));
    
    return 0;
}