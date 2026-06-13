#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <iomanip>

using namespace std;


class DPDA{
    
    private:
        string state;
        stack<string> DPDAstack;
        string input;
        int pos;
        int stepNum;

    public:
        //constructor
        DPDA(string stringInput){
            input = stringInput;
            state = "p";
            pos = 0;
            stepNum = 0;
        }

        void printStep(string delta, string rule) {
            string top;
            if (DPDAstack.empty()){
                top = "e";
            }
            else{
                top = DPDAstack.top();
            }

            string unread;
            if (pos >= (int)input.size()){
                unread = "e";
            }
            else {
                unread = input.substr(pos);
            }
            //top row
            cout << left 
                << setw(8) << stepNum 
                 << setw(8) << state 
                 << setw(15) << unread 
                 << setw(15) << getStackContents() 
                 << setw(15) << delta
                 << setw(10) << rule << endl;
        }

        string getStackContents() {
            if (DPDAstack.empty()){
                return "e";
            }

            stack<string> temp = DPDAstack;  // copy the stack
            string result = "";
            
            while (!temp.empty()) {
                result += temp.top();        // add top to result
                temp.pop();                  // remove top
            }
            return result;
        }

        void run(){

            cout << left 
                << setw(8) << "Step" 
                 << setw(8) << "State"
                 << setw(15) << "Unread Input"
                 << setw(15) << "Stack" 
                 << setw(15) << "Delta Used"
                 << setw(10) << "Rule Used" << endl;

            printStep("", "");
            while (state != "q$") {
                
                string delta = " ";
                string rule = " ";

                char currentInput = input[pos];     //what is read
                string stackTop = " ";

                if (!DPDAstack.empty()) {
                    stackTop = DPDAstack.top();     //top of stack
                }

                //rule 1 (p, e, e) → (q, S)
                if (state == "p") {
                    delta = "1";
                    state = "q";
                    DPDAstack.push("S");
                }

                //rule 2 (q, a, e) → (qa, e)
                else if (state == "q" && currentInput == 'a') {
                    delta = "2";
                    state = "qa";
                    pos++;
                }

                //rule 3 (qa, e, a) → (q, e)
                else if (state == "qa" && stackTop == "a") {
                    delta = "3";
                    state = "q";
                    DPDAstack.pop();
                }

                //rule 4 (q, b, e) → (qb, e)
                else if (state == "q" && currentInput == 'b') {
                    delta = "4";
                    state = "qb";
                    pos++;

                }

                //rule 5 (qb, e, b) → (q, e)
                else if (state == "qb" && stackTop == "b") {
                    delta = "5";
                    state = "q";
                    DPDAstack.pop();

                }

                //rule 6 (q, $, e) → (q$, e)
                else if (state == "q" && currentInput == '$') {
                    delta = "6";
                    state = "q$";
                    pos++;
                }

                //rule 7 (qa, e, S) → (qa, aSb) 
                else if (state == "qa" && stackTop == "S") {
                    delta = "7";
                    rule = "S -> aSb";
                    DPDAstack.pop();
                    DPDAstack.push("b");
                    DPDAstack.push("S");
                    DPDAstack.push("a");
                }

                //rule 8 (qb, e, S) → (qb, e)
                else if (state == "qb" && stackTop == "S") {
                    rule = "S -> e";
                    delta = "8";
                    DPDAstack.pop();
                }
                
                stepNum++;
                printStep(delta, rule);
                
            }

            if (state == "q$") {
                cout << "ACCEPTED" << endl;
                cout << endl;
            }
            else {
                cout << "REJECTED" << endl;
            }
            
        }




};

int main()
{
    vector<string> inputs = {"ab$", "aabb$", "aaabbb$", "aaaabbbb$", "aaaaabbbbb$", "aaaaaabbbbbb$"};
    for (string input : inputs) {
        cout << "Input: " << input << endl;
        DPDA dpda(input);
        dpda.run();
    }

    return 0;





}