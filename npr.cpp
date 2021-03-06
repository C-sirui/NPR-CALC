//============================================================================
// Name        : npr.cpp
// Author      : ME
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>
#include <stdio.h>
#include <cstring>
#include <sstream>
#include <vector>



using namespace std;

string ch; //input
string numsym[100]; // anti-dutch


// set up priority
int prio(string ch){
	int ans;
	//	const char* ch = ck.c_str();
	//	switch(hash_str_to_uint32(ch)){
	//	case hash_str_to_uint32("("):ans=0;break;
	//	case hash_str_to_uint32("+"):
	//	case hash_str_to_uint32("-"):ans=1;break;
	//	case hash_str_to_uint32("*"):
	//	case hash_str_to_uint32("/"):ans=2;break;
	//	case hash_str_to_uint32(")"):ans=3;break;
	//	default:ans=-1;break;
	//	}

	if(ch=="("){
		ans=0;
	}
	else if(ch=="+" || ch=="-"){
		ans=1;
	}
	else if(ch=="*" || ch=="/"){
		ans=2;
	}
	else if(ch==")"){
		ans=3;
	}
	else{
		ans=-1;
	}
	return ans;
}

// check if char a is +-*/1
int isCharSymbol(char a){

	if(a=='+' || a=='-'
			|| a=='*'
					|| a=='/'
							|| a=='('
									|| a==')'){
		return 1;
	}
	else{
		return 0;
	}

}

// check if string b is +-*/
int isStringSymbol(string b){

	if(b=="+" || b=="-"
			|| b=="*"
					|| b=="/"
							|| b=="("
									|| b==")"){
		return 1;
	}
	else{
		return 0;
	}
}

// cin get input and convert it to 后缀表达式 of string array
void convert(){

	cin>>ch;
	stack<string> symbol;
	//-----------seperated with space
	for(long long unsigned int i=0; i<ch.length(); i++){
		if(isCharSymbol(ch[i])==1){
			int j = i-2;
			int k = i-1;
			if(k!=-1 && isCharSymbol(ch[j])==0){ // not pre-space for first char && no pre-space for two consecutive char
				ch.insert(i," ");
				i++;
			}
			ch.insert(++i," ");
	}
		cout<<ch<<"end"<<endl;
	}
	//to string array with delimitor ' '
	vector<string> cin;
	stringstream ss(ch);
	string tmp;
	while(std::getline(ss, tmp, ' '))
	{
		cin.push_back(tmp);
	}


	//to 后缀
	int i = 0; // counter for numsym;
	for (string n : cin){
		if(isStringSymbol(n)==0){
			numsym[i++]=n;
		}
		else if(n=="("){
			symbol.push(n);
		}
		else if(n==")"){
			while(symbol.top()!="("){
				numsym[i++]=symbol.top();
				symbol.pop();
			}
			symbol.pop();
		}
		else if(symbol.empty()||prio(n)>prio(symbol.top())){ //empty check should be ahead, or top() dead end
			symbol.push(n);
		}
		else{
			while(prio(n)<=prio(symbol.top())){
				numsym[i++]=symbol.top();
				symbol.pop();
				if(symbol.empty()){
					break;
				}
			}
			symbol.push(n);
		}
	}

	// remaining symbols exit stack
	while(!symbol.empty()){
		numsym[i++]=symbol.top();
		symbol.pop();
	}

//		// print 後綴
//
			for(string k : numsym){
				cout<<k<<",";
			}
			printf("\n");
}

// convert string to float
float stringToNum(string str){
	istringstream iss(str);
	float num;
	iss >> num;
	return num;
}

// calculation with float
void calc(){
	stack<float> numbers;
	float num; // temporary holder
	int i = 0; // counter for numsym
	while(numsym[i]!="\0"){
		if(isStringSymbol(numsym[i])==0){
			numbers.push(stringToNum(numsym[i]));
		}
		else if(isStringSymbol(numsym[i])==1){
			// operand
			float a = numbers.top();
			numbers.pop();
			float b = numbers.top();
			numbers.pop();
			// symbol
			if(numsym[i]=="+"){
				num = (a+b);
				numbers.push(num);
//				printf("+\n");
//				cout<<num<<endl;
			}
			else if(numsym[i]=="-"){
				num =(b-a);
				numbers.push(num);
//				cout<<num<<endl;
//				printf("-\n");

			}
			else if(numsym[i]=="*"){
				num = a*b;
				numbers.push(num);
//				cout<<num<<endl;
//				printf("*\n");
			}
			else if(numsym[i]=="/"){
				if(a==(0)){
					cout<<"denominator cannot be 0"<<endl;
					break;
				}
				num = b/a;
				cout<<num<<endl;
//				numbers.push(num);
//				printf("/\n");
			}
		}
		i++;
	}
	float result = numbers.top();
	cout<<result<<endl;
}

// main
int main() {
	int i = 1;
	while(i==1){
		printf("Single Digit Calculator:\n");
		fflush(stdout);
		convert();
		calc();
		memset(numsym,'\0',sizeof(numsym)); // clear numsym for next round
		printf("Put 1 to continue\n");
		fflush(stdout);
		scanf("%d",&i);
	}
}


