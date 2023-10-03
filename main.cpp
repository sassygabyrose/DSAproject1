#include <iostream>
#include "AVL.h"
#include <sstream>
using namespace std;

void parse(string number);
bool verifyname(string fullname);
bool verifynumber(string fullnum);



int main() {

    string num;
    AVLTree t;
    getline(cin, num);
    bool is_number = false;
    for(char c : num){
        if(isdigit(c)){
            //cout << "it is a digit" << endl;
            is_number = true;
        }
    }
    if(is_number){

        int number = stoi(num);

        for(int i = 0; i < number; i++){
            string line = "";
            getline(cin, line);
            string command;
            int sub_start = 0;
            string after_command = "";
            for(auto x : line){
                sub_start += 1;
                if(x == ' '){
                    //cout << command << endl;
                    after_command = line.substr(sub_start);
                    break;
                    //line
                }
                else{
                    command += x;
                }
            }
            //now after we made the command, we check if it matches out functions
            if(command == "insert"){
                //this means we are going to call insert.
                //first we try to find where the quotations are
                int first_qu = after_command.find('"');
                //have to find second set of parenthesis
                string after_command_less = after_command.substr(1);
                int second_qu = after_command_less.find('"');
                //then we'll make the string name out of this
                string insert_name = after_command.substr(first_qu + 1, second_qu);
                bool is_name = verifyname(insert_name);
                string insert_num = after_command.substr(second_qu +3);
                bool is_num = verifynumber(insert_num);
                if(is_name && is_num){
                    t.Insert(t, insert_name, insert_num);
                    cout << "successful" << endl;
                }
                else{
                    cout << "unsuccessful" << endl;
                }

            }
            else if(command == "remove"){
                string remove_num = after_command.substr(0);
                //cout << after_command << endl;
                bool is_num = verifynumber(remove_num);
                if(is_num){
                    t.remove(remove_num, t);
                }
                else{
                    cout << "unsuccessful" << endl;
                }

                //now we call remove
            }
            else if(command == "search"){
                //now we call search and will check which search it could be
                if(after_command[0] == '"'){
                    //that means it is a name
                    int first_qu = after_command.find('"');
                    //have to find second set of parenthesis
                    string after_command_less = after_command.substr(1);
                    int second_qu = after_command_less.find('"');
                    //then we'll make the string name out of this
                    string insert_name = after_command.substr(first_qu + 1, second_qu);
                    bool is_name = verifyname(insert_name);
                    if(is_name){
                        string answer = t.searchName(insert_name, t);
                        cout << answer << endl;
                    }
                    else{
                        cout << "unsuccessful" << endl;
                    }

                }
                else{
                    bool is_num = verifynumber(after_command);
                    if(is_num){
                        t.searchID(after_command, t);
                    }
                    else{
                        cout << "unsuccessful" << endl;
                    }
                }

            }
            else if(command == "printInorder"){
                //we will call the print inorder function
                string answer = t.inorder(t);
                cout << answer << endl;
            }
            else if(command == "printPreorder"){
                //we will call the print Preorder function
                t.preorder(t);
            }
            else if(command == "printPostorder"){
                //we will call the print PostOrder function
                t.postorder(t);
            }
            else if(command == "printLevelCount"){
                //we will call the print Level count function
                t.printLevelCount(t);
            }
            else if(command == "removeInorder"){
                //now we call the remove in order function

                int count = 0;
                for(auto x : after_command){
                    if(isdigit(x)){
                        count += 1;
                    }
                }
                if(count == after_command.length()){
                    int number = stoi(after_command);
                    t.removeInorder(number, t);
                }
                else{
                    cout << "unsuccessful" << endl;
                }

            }
            else{
                //if it is none of those, it is unsuccessful
                cout << "unsuccessful" << endl;
            }


        }
    }
    else{
        cout << "unsuccessful" << endl;
    }
    return 0;
}

void parse(string number){
    cin >> number;
    //cout << number << endl;
    bool is_number = false;
    for(char c : number){
        if(isdigit(c)){
            //cout << "it is a digit" << endl;
            is_number = true;
        }
    }

    if(is_number){
        int count = 0;
        int first_loop = 2;
        for(int i = 0; i < first_loop; i ++){
            count += 1;
            int nums = stoi(number);
            string line;

            getline(cin, line);
            //cout << line << endl;
            //this is just to get the command out
            string command;
            int sub_start = 0;
            string after_command = "";
            for(auto x : line){
                sub_start += 1;
                if(x == ' '){
                    //cout << command << endl;
                    after_command = line.substr(sub_start + 1);
                    break;
                    //line
                }
                else{
                    command += x;
                }
            }
            //checks if the command is insert
            if(command == "insert"){
                string name;
                int sub_start = 0;
                bool is_name = false;
                string after_name = "";
                for(auto x : after_command){
                    sub_start += 1;
                    //cout << sub_start << endl;
                    if(isalpha(x) or (x == ' ')){

                        //cout << x << endl;
                        name += x;
                        //cout << name << endl;
                    }
                    else{
                        if(x == '"'){
                            //cout << name << endl;
                            after_name = after_command.substr(sub_start + 1);
                            is_name = true;
                            break;
                        }
                        //cout << x << endl;
                        //cout << "unsuccsessful" << endl;
                        is_name = false;
                        break;
                    }
                }
                string final_name = name;
                if(is_name){
                    //cout << name << endl;
                    bool is_num = true;
                    string number = "";
                    int num_leng = 0;
                    for(auto x : after_name){
                        num_leng += 1;
                        if(isdigit(x)){

                            //cout << x << endl;
                            number += x;
                            //cout << number << endl;
                        }
                        else{

                            //cout << x << endl;
                            cout << "unsuccsessful" << endl;
                            is_num = false;
                            break;
                        }
                    }
                    if(is_num && num_leng == 8){
                        AVLTree t;
                        t.Insert(t,final_name, number);
                        cout << "successful" << endl;
                        //repeats for rest of the commands
                        int count = 0;
                        for(int i = 0; i < nums - 1; ++i){

                            string line;

                            getline(cin, line);
                            //cout << line << endl;
                            //this is just to get the command out
                            string command;
                            int sub_start = 0;
                            string after_command = "";
                            for(auto x : line){
                                sub_start += 1;
                                if(x == ' '){
                                    //cout << command << endl;
                                    after_command = line.substr(sub_start);
                                    break;
                                    //line
                                }
                                else{
                                    command += x;
                                }
                            }
                            //checks if the command is insert
                            if(command == "insert"){
                                after_command = after_command.substr(1);
                                string name;
                                int sub_start = 0;
                                bool is_name = false;
                                string after_name = "";
                                for(auto x : after_command){
                                    sub_start += 1;
                                    //cout << sub_start << endl;
                                    if(isalpha(x) or (x == ' ')){

                                        //cout << x << endl;
                                        name += x;
                                        //cout << name << endl;
                                    }
                                    else{
                                        if(x == '"'){
                                            //cout << name << endl;
                                            after_name = after_command.substr(sub_start + 1);
                                            is_name = true;
                                            break;
                                        }
                                        //cout << x << endl;
                                        cout << "unsuccsessful" << endl;
                                        is_name = false;
                                        break;
                                    }
                                }
                                string final_name = name;
                                if(is_name){
                                    //cout << name << endl;
                                    bool is_num = true;
                                    string number = "";
                                    int num_leng = 0;
                                    for(auto x : after_name){
                                        num_leng += 1;
                                        if(isdigit(x)){

                                            //cout << x << endl;
                                            number += x;
                                            //cout << number << endl;
                                        }
                                        else{

                                            //cout << x << endl;
                                            cout << "unsuccsessful" << endl;
                                            is_num = false;
                                            break;
                                        }
                                    }
                                    if(is_num && num_leng == 8){
                                        //cout << final_name << endl;
                                        //cout << number << endl;
                                        t.Insert(t,final_name, number);
                                        count += 1;
                                        cout << "successful" << endl;
                                    }
                                    else{
                                        cout << "unsuccessful " << endl;
                                    }

                                }
                            }
                            else if(command == "remove"){
                                bool is_num = true;
                                string number = "";
                                int num_leng = 0;
                                //cout << after_command << endl;
                                for(auto x : after_command){
                                    num_leng += 1;
                                    if(isdigit(x)){

                                        //cout << x << endl;
                                        number += x;
                                        //cout << number << endl;
                                    }
                                    else{

                                        //cout << x << endl;
                                        cout << "unsuccsessful" << endl;
                                        is_num = false;
                                        break;
                                    }
                                }
                                if(is_num && num_leng == 8){
                                    t.remove(number, t);
                                    //cout << "successful" << endl;
                                }
                                else{
                                    cout << "unsuccessful" << endl;
                                }
                            }
                            else if(command == "removeInorder"){
                                bool is_num = true;
                                string number = "";
                                //cout << after_command << endl;
                                for(auto x : after_command){
                                    if(isdigit(x)){

                                        //cout << x << endl;
                                        number += x;
                                        //cout << number << endl;
                                    }
                                    else{

                                        //cout << x << endl;
                                        cout << "unsuccsessful" << endl;
                                        is_num = false;
                                        break;
                                    }
                                }
                                if(is_num){
                                    int nth = stoi(number);
                                    t.removeInorder(nth, t);
                                    //cout << "successful" << endl;
                                }
                                else{
                                    cout << "unsuccessful" << endl;
                                }
                            }
                            else if(command == "search"){


                                if(isdigit(after_command[0])){
                                    bool is_num = true;
                                    string number = "";
                                    int num_leng = 0;
                                    //cout << "it's a number" << endl;
                                    for(auto x : after_command){
                                        num_leng += 1;
                                        if(isdigit(x)){

                                            //cout << x << endl;
                                            number += x;
                                            //cout << number << endl;
                                        }
                                        else{

                                            //cout << x << endl;
                                            cout << "unsuccsessful" << endl;
                                            is_num = false;
                                            break;
                                        }
                                    }
                                    if(is_num && num_leng == 8){
                                        t.searchID(number, t);
                                        //cout << "successful" << endl;
                                    }
                                    else{
                                        cout << "unsuccsessful" << endl;
                                    }
                                }
                                else if(isalpha(after_command[1])){
                                    bool is_name = false;
                                    string name = "";
                                    after_command = after_command.substr(1);
                                    for(auto x : after_command){
                                        sub_start += 1;
                                        //cout << sub_start << endl;
                                        if(isalpha(x) or (x == ' ')){

                                            //cout << x << endl;
                                            name += x;
                                            //cout << name << endl;
                                        }
                                        else{
                                            if(x == '"'){


                                                is_name = true;
                                                break;
                                            }
                                            //cout << x << endl;
                                            cout << "unsuccsessful" << endl;
                                            is_name = false;
                                            break;
                                        }
                                    }
                                    if(is_name){
                                        t.searchName(name, t);
                                        //cout << "will search by name" << endl;

                                    }
                                    else{
                                        cout << "unsuccessful" << endl;
                                    }

                                }
                                else{
                                    cout << "unsuccessful" << endl;
                                }
                            }
                            else if(command == "printInorder"){
                                if(line.length() > 12){
                                    cout << "unsuccessful" << endl;
                                }
                                else{
                                    t.inorder(t);
                                    //cout << "successful" << endl;
                                }
                            }
                            else if(command == "printPreorder"){
                                if(line.length() > 13){
                                    cout << "unsuccessful" << endl;
                                }
                                else{
                                    t.preorder(t);
                                    //cout << "successful" << endl;
                                }
                            }
                            else if(command == "printPostorder"){
                                if(line.length() > 14){
                                    t.postorder(t);
                                    //cout << "unsuccessful" << endl;
                                }
                                else{
                                    t.postorder(t);
                                    //cout << "successful" << endl;
                                }
                            }
                            else if(command == "printLevelCount"){
                                if(line.length() != 15){
                                    cout << "unsuccessful" << endl;
                                }
                                else{
                                    t.printLevelCount(t);
                                    //cout << "successful" << endl;
                                }


                            }
                        }

                    }
                    else{
                        cout << "unsuccessful" << endl;
                    }

                }
            }
            else{
                //this is if it is not insert
                if(count == 1){
                    count = 1;
                }
                else{
                    cout << "unsuccessful" << endl;
                    if(count >= 2){
                        first_loop += 1;
                    }
                }

            }


        }


    }
}


bool verifyname(string fullname){
    int count = 0;
    for(auto x : fullname){
        //cout << sub_start << endl;
        if(isalpha(x) or (x == ' ')){
            count += 1;
        }
        else{
            return false;
        }
    }
    if(count == fullname.length()){
        return true;
    }
}
bool verifynumber(string fullnum){
    int num_leng = 0;
    for(auto x : fullnum){
        num_leng += 1;
        if(isdigit(x)){
            num_leng += 0;

        }
        else{
            return false;
        }
    }
    if(num_leng == 8){
        return true;
    }
}


