#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <string.h>

using namespace std;

vector<string> context;
char cmd[100];

class Singleton {
private:
	vector<string> value;
	static Singleton* s_instance;

	Singleton(vector<string> v = {}) {
		value = v;
	}
public:
	vector<string> get_value() {
		return value;
	}
	void set_value(vector<string> v) {
		value = v;
	}
	static Singleton* instance() {
		if (!s_instance) {
			s_instance = new Singleton();
		}
		return s_instance;
	}
};

Singleton* Singleton::s_instance = 0;

void printPage(vector<string>::iterator it) {
    vector<string>::iterator iter;
    string tmp_str = "";
    int tmp_size = 0;
    int line_number = 0;
    
    for (iter = it; iter != Singleton::instance()->get_value().end(); iter++) {
        if (line_number == 0) {
            cout << setw(2) << line_number + 1 << "| ";
            line_number++;
        }

        tmp_str = *iter;
        tmp_size += tmp_str.length() + 1;
        
        if (tmp_size > 76) {
            line_number++;
            if (line_number == 21) {
                break;
            }
            cout << endl << setw(2) << line_number << "| " + tmp_str + " ";
            if (tmp_str == Singleton::instance()->get_value().back()) break;
            tmp_size = tmp_str.length() + 1;
        }
        else {
            cout << tmp_str + " ";
            if (tmp_str == Singleton::instance()->get_value().back()) break;
        }
    }
    cout << endl;
}

void introCommand() {
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "(콘솔메시지)" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "입력: ";
    cin >> cmd;
    cout << "--------------------------------------------------------------------------------" << endl;
}

void inputCommand() {
    vector<string>::iterator it = Singleton::instance()->get_value().begin();

    while (1) {
        vector<string> v = Singleton::instance()->get_value();
        printPage(it);
        introCommand();

        if (cmd[0] == 'n') {
            vector<string>::iterator tmp_iterator;
            string tmp_str;
            int tmp_size = 0, line_number = 1;
            for (tmp_iterator = it; tmp_iterator != v.end(); tmp_iterator++) {
                tmp_str = *tmp_iterator;
                tmp_size += tmp_str.length() + 1;

                if (tmp_size > 76) {
                    line_number++;
                    if (line_number == 21) {
                        break;
                    }
                    tmp_size = tmp_str.length() + 1;
                }
            }
            it = tmp_iterator;
        }
        else if (cmd[0] == 'p') {
            vector<string>::iterator tmp_iterator;
            string tmp_str;
            int tmp_size = 0, line_number = 1;
            for (tmp_iterator = it-1; tmp_iterator != v.begin(); tmp_iterator--) {
                tmp_str = *tmp_iterator;
                tmp_size += tmp_str.length() + 1;

                if (tmp_size > 76) {
                    line_number++;
                    if (line_number == 21) {
                        break;
                    }
                    tmp_size = tmp_str.length() + 1;
                }
            }
            it = tmp_iterator;
        }
        else if (cmd[0] == 'i') {
            vector<string>::iterator tmp_iterator;
            string tmp_str, insert_word, target_line, target_order;
            int tmp_size = 0, chk = 0;

            for (int i = 2; i < strlen(cmd)-1; i++) {
                if (cmd[i] == ',') {
                    chk++;
                    continue;
                }

                if (chk == 0) {
                    target_line += cmd[i];
                }
                else if (chk == 1) {
                    target_order += cmd[i];
                }
                else {
                    insert_word += cmd[i];
                }
            }

            int word_number = 1, line_number = 1;
            for (tmp_iterator = it; tmp_iterator != v.end(); tmp_iterator++) {
                if (line_number == stoi(target_line) && word_number == stoi(target_order)) {
                    v.insert(tmp_iterator+1,insert_word);
                    break;
                }

                tmp_str = *tmp_iterator;
                tmp_size += tmp_str.length() + 1;

                if (tmp_size > 76) {
                    line_number++;
                    word_number = 1;
                    if (line_number == stoi(target_line) && word_number == stoi(target_order)) {
                        v.insert(tmp_iterator+1,insert_word);
                        break;
                    }
                    if (line_number == 21) {
                        break;
                    }
                    tmp_size = tmp_str.length() + 1;
                }
                word_number++;
            }
        }
        else if (cmd[0] == 'd') {
            vector<string>::iterator tmp_iterator;
            string tmp_str, target_line, target_order;
            int tmp_size = 0, chk = 0;

            for (int i = 2; i < strlen(cmd)-1; i++) {
                if (cmd[i] == ',') {
                    chk++;
                    continue;
                }

                if (chk == 0) {
                    target_line += cmd[i];
                }
                else {
                    target_order += cmd[i];
                }
            }

            int word_number = 1, line_number = 1;
            for (tmp_iterator = it; tmp_iterator != v.end(); tmp_iterator++) {
                if (line_number == stoi(target_line) && word_number == stoi(target_order)) {
                    v.erase(tmp_iterator);
                    break;
                }

                tmp_str = *tmp_iterator;
                tmp_size += tmp_str.length() + 1;
                if (tmp_size > 76) {
                    line_number++;
                    word_number = 1;
                    if (line_number == stoi(target_line) && word_number == stoi(target_order)) {
                        v.erase(tmp_iterator);
                        break;
                    }
                    if (line_number == 21) {
                        break;
                    }
                    tmp_size = tmp_str.length() + 1;
                }
                word_number++;
            }
        }
        else if (cmd[0] == 'c') {
            string source, destination;
            vector<string> tmp;
            vector<string>::iterator tmp_iterator;
            int chk = 0;

            for (int i = 2; i < strlen(cmd)-1; i++) {
                if (cmd[i] == ',') {
                    chk++;
                    continue;
                }
                
                if (chk == 0) {
                    source += cmd[i];
                }
                else {
                    destination += cmd[i];
                }
            }

            for (tmp_iterator = v.begin(); tmp_iterator != v.end(); tmp_iterator++) {
                if (*tmp_iterator == source) {
                    tmp.push_back(destination);
                }
                else {
                    tmp.push_back(*tmp_iterator);
                }
            }
            v = tmp;
        }
        else if (cmd[0] == 's') {
            string target;
            vector<string>::iterator tmp_iterator;
            for (int i = 2; i < strlen(cmd)-1; i++) {
                target += cmd[i]; 
            }
            for (tmp_iterator = v.begin(); tmp_iterator != v.end(); tmp_iterator++) {
                if (*tmp_iterator == target) {
                    break;
                }
            }
            it = tmp_iterator;
        }
        else if (cmd[0] == 't') {
            break;
        }
        else {
            continue;
        }
        Singleton::instance()->set_value(v);
    }
}

int main() {
    ifstream examFile("CNU_OOP_00/textEditor_TermProject/test.txt");
    if (examFile.is_open()) {
        string s;
        while (examFile >> s) {
            context.push_back(s);
        }
        examFile.close();
    }
    else {
        cout << "unable" << endl;
    }
    Singleton::instance()->set_value(context);

    inputCommand();
    
    ofstream writeFile("CNU_OOP_00/textEditor_TermProject/test.txt");
    if (writeFile.is_open()) {
        for (string s : Singleton::instance()->get_value()) {
            writeFile << s + " ";
        }
        writeFile.close();
    }
    return 0;
}