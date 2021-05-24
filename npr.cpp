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
using namespace std;

char ch[100]; //input
char numsym[100]; // anti-dutch

int prio(char ch){
	int ans;
	switch(ch){
	case'(':ans=0;break;
	case'+':
	case'-':ans=1;break;
	case'*':
	case'/':ans=2;break;
	case')':ans=3;break;
	default:ans=-1;break;
	}
	return ans;
}

void convert(){
	scanf("%s",ch);
	stack<char> symbol;
	int i = 0; // counter for numsym[]
	int n = 0; // counter for ch[]
	while(ch[n]!='\0'){
		if(ch[n]<='9' && ch[n]>='0'){
			numsym[i++]=ch[n];
		}
		else if(ch[n]=='('){
			symbol.push(ch[n]);
		}
		else if(ch[n]==')'){
			while(symbol.top()!='('){
				numsym[i++]=symbol.top();
				symbol.pop();
			}
			symbol.pop();
		}
		else if(symbol.empty()||prio(*ch)>prio(symbol.top())){ //empty check should be ahead, or top() dead end
			symbol.push(ch[n]);
		}
		else{
			while(prio(ch[n])<prio(symbol.top())){
				numsym[i++]=symbol.top();
				symbol.pop();
				if(symbol.empty()){
					break;
				}
			}
			symbol.push(ch[n]);
		}
		n++;
	}
	while(!symbol.empty()){
		numsym[i++]=symbol.top();
		symbol.pop();
	}
}



void calc(){
	stack<float> numbers;
	int k=0; // counter for numsym[]
	float num; // temporary holder
	while(numsym[k]!='\0'){
		if(numsym[k]<='9' && numsym[k]>='0'){
			numbers.push((float)numsym[k]-48);
		}
		else if(numsym[k]=='+'
				|| numsym[k]=='-'
						|| numsym[k]=='*'
								|| numsym[k]=='/'){
			float a = numbers.top();
			numbers.pop();
			float b = numbers.top();
			numbers.pop();
			switch(numsym[k]){
			case'+':
				num = (a+b);
				numbers.push(num);
				break;

			case'-':
				num =(b-a);
				numbers.push(num);
				break;
			case'*':
				num = a*b;
				numbers.push(num);
				break;
			case'/':
				if(a==(0)){
					cout<<"denominator cannot be 0"<<endl;
					break;
				}
				num = b/a;
				numbers.push(num);
				break;
			}
		}
		k++;
	}
	float result = numbers.top();
	cout<<result<<endl;

}




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
