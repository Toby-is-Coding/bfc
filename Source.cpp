#include <iostream>
#include <fstream>
#include "Tur.h"

using namespace std;

int interpret(Tur* tur, ifstream* code, int from = 0, bool isLoop = false, bool isIf = false) {
    static int interpretsOpen = 0;
    interpretsOpen++;
    code->seekg(from); //start from 'from'th character
    char op;
    int it_char = from; //iterator for the current char we read
    if (code->is_open()) {
        while (code->get(op)) {
            //cout << *tur << ' ' << interpretsOpen << ", " << it_char << endl; //debugging
            it_char++;
            switch (op) {
            case '>': //go right
                tur->right();
                break;
            case '<': //go left
                tur->left();
                break;
            case '!': //print as int
                cout << tur->get();
                break;
            case '@': //print as char
                cout << (char)tur->get();
                break;
            case '.': //set as input
                int c;
                cin >> c;
                tur->put(c);
                break;
            case '+': //increment
                tur->add();
                break;
            case '-': //decrement
                tur->sub();
                break;
            case '~': //zeroify
                tur->zeroify();
                break;
            case '^': //upload to register
                tur->upload();
                break;
            case '%': //download data from register
                tur->download();
                break;
            case '[': //start if statement
                if (tur->get() != 0) {
                    int skipChars = it_char;
                    skipChars = interpret(tur, code, it_char, false, true);
                    code->seekg(skipChars);
                }
                break;
            case ']': //end if statement
                if (isIf) {
                    --interpretsOpen;
                    return it_char;
                }
                break;
            case '(': //start loop
                while (tur->get() != 0) {
                    int skipChars = it_char;
                    skipChars = interpret(tur, code, it_char, true);
                    code->seekg(skipChars);
                }
                break;
            case ')': //end loop
                if (isLoop) {
                    --interpretsOpen;
                    return it_char;
                }
                break;
            default:
                break;
            }
        }
    }
    return it_char;
}

int main() {
    Tur tur;
    ifstream* code = new ifstream("brain.txt");
    interpret(&tur, code);
    code->close();
    delete code;
}