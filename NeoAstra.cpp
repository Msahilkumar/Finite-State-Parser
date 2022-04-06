#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
#define all(v) (v).begin(),(v).end()
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

/* The State-Transition Diagram is drawn in the PDF file, attched with the code file.
Here is the brief description of relevant vocabulary used in this problem
States :-
0 --> The initial state
1 --> This is the state just after getting http:// or https://
2 --> This is the state just after getting a Capital letter character
3 --> This is the state just after getting a Small letter character
4 --> This is the state after getting ".com" or ".in" or ".org"
5 --> This is the state just after getting a white space
6 --> This is the state just after getting a dot
7 --> This is for exception handeling (Once we are in this state there is no way to come out)

Inputs :-
0 -->  Initially input is 0
1 -->  If http:// or https:// shows in the string
2 -->  If there is a Capital letter character in the string
3 -->  If a Small letter character shows
4 -->  If .com or .in or .org shows in the string
5 -->  If a white space is there
6 -->  If a '.' is there (there may be a dot in between the urls for ex. https://erp.iitkgp.ac.in)
7 -->  This is for exception handeling, if any other character shows Input is 7.
*/

// In this code the state-transition table is represented using a 2-D vector of size 8x8 
vector<vector<int>> state_transition_table = {
// 0  1  2  3  4  5  6  7
  {7, 1, 2, 7, 7, 7, 7, 7}, //0    
  {7, 7, 7, 3, 7, 7, 7, 7}, //1    
  {7, 7, 7, 3, 7, 7, 7, 7}, //2   
  {7, 7, 7, 3, 4, 5, 6, 7}, //3
  {7, 7, 7, 7, 7, 7, 7, 7}, //4
  {7, 7, 2, 7, 7, 7, 7, 7}, //5
  {7, 7, 7, 1, 7, 7, 7, 7}, //6
  {7, 7, 7, 7, 7, 7, 7, 7}, //7
};

signed main() {
IOS

cout<<"Enter the string : ";
string s;
getline(cin,s);
cout<<s<<endl;
int state=0;
int input =0;
int i=0;

int n=s.length();

int flag=0; /* when the string starts with "http://" or "https://" we set flag =1 (a web URL)
                when the string starts with a Capital letter character, we set flag == 2 (a Name )*/

while(i<n){
    /* This code block is to identify the http part*/
    if((i + 7 < n && "http://" == s.substr(i,7)) || (i + 8 < n && "https://" == s.substr(i,8))){
         if("http://" == s.substr(i,7)){
            if(i==0) flag = 1;  /* we set flag = 1 only if the string starts with http part */
            input = 1;
            i += 7;
            state = state_transition_table[state][input];
        }else if("https://" == s.substr(i,8)){
            if(i==0) flag = 1;
            input = 1;
            i += 8;
            state = state_transition_table[state][input];
        } 
    }
    /*This code block is to check the presence of .com | .org | .in at the end of string*/
    else if((".com" == s.substr(i,4)) || (".net" == s.substr(i,4)) || (".org" == s.substr(i,4)) || (".gov" == s.substr(i,4)) || (".in" == s.substr(i,3))){
        if((".com" == s.substr(i,4)) || (".org" == s.substr(i,4)) || (".net" == s.substr(i,4)) || (".gov" == s.substr(i,4))){
            i = i + 4;
            input = 4;
            state = state_transition_table[state][input];
        }else if(".in" == s.substr(i,3)){
            i += 3;
            input = 4;
            state = state_transition_table[state][input];
        }
    }
    /*This code block is to check Wheather the charcter is in between [A-Z]*/
    else if(s[i] >= 'A' && s[i] <= 'Z'){
        if(i==0) flag=2;
        input = 2;
        i++;
        state = state_transition_table[state][input];
    }
    /*This code block is to check Wheather the charcter is in between [a-z]*/
    else if(s[i] >= 'a' && s[i] <= 'z'){
        i++;
        input = 3;
        state = state_transition_table[state][input];
    }
    /*This code block is to check Wheather there is a white space*/
    else if(s[i] == ' '){
        i++;
        if(flag==2) input = 5; /*We only allow the input = 5 if and only if it's a Name (spaces are not allowed in the URLs) */
        else input =7;
        state = state_transition_table[state][input];
    }
    /*This code block is to check Wheather there is a dot*/
    else if(s[i] == '.'){
        i++;
        if(flag==1) input = 6; /*We only allow the input = 6 if and only if it's a URL (dots are not allowed in the Names) */
        else input = 7;
        state = state_transition_table[state][input];
    }
    /*This code block is for exception handeling if there is any other charcter shows*/
    else{
        i++;
        input = 7;
        state = state_transition_table[state][input];
    }
}

if(state==4 && flag==1) cout<<"it's a Web URL"<<endl; /*it's a web url if it ends at state 4 (.com/.in/.org) and flag==1(for URL)*/
else if(state==3 && flag==2) cout<<"it's a Name"<<endl; /*it's a Name if it ends at state 3 (.com/.in/.org) and flag==2(for names)*/
else cout<<"it's neither a Name nor a URL"<<endl; /*Otherwise it's state 7, which means neither name nor URL*/
}