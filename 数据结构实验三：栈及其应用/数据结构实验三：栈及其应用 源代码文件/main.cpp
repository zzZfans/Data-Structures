#include "ArrayStack.h"

int main() {

    string str = "abcdefghijklmnopqrstuvwxyz0123456789";

    ArrayStack<char> textReverseString;

    cout << "ÄæÐòÇ°£º" << str << endl;
    cout << "ÄæÐòºó£º" << textReverseString.ReverseString(str) << endl;

    string str2 = "[()] {} {[()()]()}";
    cout << str2;

    ArrayStack<char> textCheckBracketMatching;

    if (textCheckBracketMatching.CheckBracketMatching(str2))
        cout << "  À¨ºÅÆ¥Åä£¡" << endl;
    else
        cout << "  À¨ºÅ²»Æ¥Åä£¡" << endl;

    str2 = "[()] {} {[()()]()";
    cout << str2;
    textCheckBracketMatching.toEmpty();
    if (textCheckBracketMatching.CheckBracketMatching(str2))
        cout << "  À¨ºÅÆ¥Åä£¡" << endl;
    else
        cout << "  À¨ºÅ²»Æ¥Åä£¡" << endl;

    str2 = "[()] {} {[()()]()}}";
    cout << str2;
    textCheckBracketMatching.toEmpty();
    if (textCheckBracketMatching.CheckBracketMatching(str2))
        cout << "  À¨ºÅÆ¥Åä£¡" << endl;
    else
        cout << "  À¨ºÅ²»Æ¥Åä£¡" << endl;

    ArrayStack<char> textArithmeticExpressionEvaluation;
    string str3 = "((1.2*3.4+5^6-7)/8)";
    cout << "ËãÊõ±í´ïÊ½£º" << str3 << endl;
    cout << "×ª»»Îªºó×º±í´ïÊ½£º";
    vector<string> postfix = textArithmeticExpressionEvaluation.ArithmeticToPostfix(str3);
    for (auto str:postfix)
        cout << str;
    cout << endl << "ÇóµÃÖµÎª£º";
    cout << textArithmeticExpressionEvaluation.ArithmeticExpressionEvaluation(str3);

    return 0;
}