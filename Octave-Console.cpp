#include <iostream>
#include <string>
#include<sstream>
#include <stdlib.h>
#include <ctype.h>
#include <cctype>
#include <algorithm>
#define MAX 50

using namespace std;

bool isNumber(string);
inline std::string trim(const std::string &s);

class Data{
	public:
		string name;
		float matrix[10][10];
		int allocated,rows,columns;
	
	public:
		Data();
		void set(string name, string value);
		void display();
};

Data::Data(){
	allocated=0;
}

void Data::set(string var, string value){
	string str;
	int success=1;
	int i,j;
	int row1=0;
	int r=0; //row index
	int c=0;  //column index 
	for(i=0;i<value.length();i++){
		if(value[i] == ';'){
			if(r!=0 && c!=row1){
				success=0;
				break;
			}
			r++;
		    c=0;
		}
		else if(value[i]==' ' || value[i]==','){
			continue;
		}
		else{
			str="";
			while(value[i] != ';' && value[i] != ' ' && value[i] != ',' ){
				if(i==value.length()-1){
					str = str + value[i];
					i++;
					break;
				}else{
					str = str + value[i];
					i++;
				}
				
			}
			if(isNumber(str)){
				stringstream val(str);
				val >> matrix[r][c];
				c++;
				if(r==0){
					row1++;
				}
			}
			else{
				success=0;
			}
			i--;
		}
	}
	if(success==0 || c!=row1){
		cout<<"error: invalid dimensions/values"<<endl;
	}
	else{
		name=var;
		allocated=1;
		rows=r+1;
		columns=c;
		display();
	}
}

void Data::display(){
	cout<<name<<" =\n";
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			cout<<matrix[i][j]<<"\t";
		}
		cout<<endl;
	}
}

bool isNumber(string s) { 
    for (int i = 0; i < s.length(); i++) 
        if (isdigit(s[i]) == false && s[i]!='.') 
            return false; 
  
    return true; 
} 

inline std::string trim(std::string& str){
    str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
    str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
    return str;
}

Data allocations[MAX];

int main() {
	string input,token;
	int len,j,index1,index2;
	int error=0;
	int count=0;
	int updated = 0;
	size_t pos = 0;
	cout<<"Welcome to Universal Complex Scripting Calculator by UCSC, Sri Lanka. Version: 1.0 \n";
	while(input != "exit"){
		error=0;
		count=0;
		cout<<">>";
		getline(cin,input);
		len = input.length();
		for(int i=0;i<len;i++){
			if(error==0 && input[i] == '='){
				for(j=i+1;j<len;j++){
					if(input[j]=='=' || input[j] =='+' || input[j] =='*'){
						cout<<"error: use only one operation for statement\n";
						error=1;
						break;
					}
				}
				if(error==0){
					pos = input.find("=");
					token = input.substr(0, pos);
				    input.erase(0, pos+1);
					
					trim(token);
					trim(input);
					
					//check [ ]
					if((input[0] == '[' && input[input.length()-1] != ']') || (input[input.length()-1] == ']' && input[0] != '[')){
						cout<<"error: invalid parenthesis\n";
					}
					else if(input[0] == '[' && input[input.length()-1] == ']'){
						input.erase(0,1);
						input.erase(input.length()-1);
					}
				    if(input==""){
				    	cout<<"error: no value defined\n";
				    	break;
					}
					
				    //update if variable exists
				    for(int j=0;j<MAX;j++){
				    	if(allocations[j].name == token){
				    		allocations[j].set(token,input);
				    		updated = 1;
				    		break;
						}
					}
					
					//assign if variable does not exists
					if(updated==0){
						int j=0;
						while(j<MAX && allocations[j].allocated!=0){
							j++;
						}
						if(allocations[j].allocated==0){
							allocations[j].set(token,input);
						}
					}
			    
				}
				else{
					cout<<"error"<<endl;
				}
				break;
				
			}
			else if(error==0 && input[i] == '+'){
				for(j=i+1;j<len;j++){
					if(input[j]=='=' || input[j] =='+' || input[j] == '-' || input[j] =='*'){
						cout<<"error: use only one operation for statement\n";
						error=1;
						break;
					}
				}
				if(error==0){
					pos = input.find("+");
					string val1 = input.substr(0, pos);
				    input.erase(0, pos+1);
				    string val2 = input;
				    
				    trim(val1);
				    trim(val2);
				    
				    for(j=0;j<MAX;j++){
				    	if(allocations[j].allocated==1 && allocations[j].name==val1){
				    		index1=j;
				    		count++;
						}
						if(allocations[j].allocated==1 && allocations[j].name==val2){
				    		index2=j;
				    		count++;
						}
					}
					if(count!=2){
						cout<<"error: values not found\n";
						error=1;
						break;
					}
					else{
						if((allocations[index1].rows!=allocations[index2].rows) || (allocations[index1].columns != allocations[index2].columns)){
							cout<<"error: dimensions do not match\n";
							error=1;
						}
						else{
							cout<<val1<<"+"<<val2<<"=\n";
							for(int x=0;x<allocations[index1].rows;x++){
								for(int y=0;y<allocations[index1].columns;y++){
									cout<<allocations[index1].matrix[x][y]+allocations[index2].matrix[x][y]<<"\t";
								}
								cout<<endl;
							}
						}
					}
				}
				break;
			}
			
			else if(error==0 && input[i] == '-'){
				for(j=i+1;j<len;j++){
					if(input[j]=='=' || input[j] =='+' || input[j] == '-' || input[j] =='*'){
						cout<<"error: use only one operation for statement\n";
						error=1;
						break;
					}
				}
				if(error==0){
					pos = input.find("-");
					string val1 = input.substr(0, pos);
				    input.erase(0, pos+1);
				    string val2 = input;
				    
				    trim(val1);
				    trim(val2);
				    
				    for(j=0;j<MAX;j++){
				    	if(allocations[j].allocated==1 && allocations[j].name==val1){
				    		index1=j;
				    		count++;
						}
						if(allocations[j].allocated==1 && allocations[j].name==val2){
				    		index2=j;
				    		count++;
						}
					}
					if(count!=2){
						cout<<"error: values not found\n";
						error=1;
						break;
					}
					else{
						if((allocations[index1].rows!=allocations[index2].rows) || (allocations[index1].columns != allocations[index2].columns)){
							cout<<"error: dimensions do not match\n";
							error=1;
						}
						else{
							cout<<val1<<"-"<<val2<<"=\n";
							for(int x=0;x<allocations[index1].rows;x++){
								for(int y=0;y<allocations[index1].columns;y++){
									cout<<allocations[index1].matrix[x][y]-allocations[index2].matrix[x][y]<<"\t";
								}
								cout<<endl;
							}
						}
					}
				}
				break;
			}
			
			else if(error==0 && input[i] == '*'){
				for(j=i+1;j<len;j++){
					if(input[j]=='=' || input[j] =='+' || input[j] == '-' || input[j] =='*'){
						cout<<"error: use only one operation for statement\n";
						error=1;
						break;
					}
				}
				if(error==0){
					pos = input.find("*");
					string val1 = input.substr(0, pos);
				    input.erase(0, pos+1);
				    string val2 = input;
				    
				    trim(val1);
				    trim(val2);
				    
				    for(j=0;j<MAX;j++){
				    	if(allocations[j].allocated==1 && allocations[j].name==val1){
				    		index1=j;
				    		count++;
						}
						if(allocations[j].allocated==1 && allocations[j].name==val2){
				    		index2=j;
				    		count++;
						}
					}
					if(count!=2){
						cout<<"error: values not found\n";
						error=1;
						break;
					}
					else{
						if(allocations[index1].rows==1 && allocations[index1].columns==1){
							for(int x=0;x<allocations[index2].rows;x++){
								for(int y=0;y<allocations[index2].columns;y++){
									cout<<allocations[index1].matrix[0][0]*allocations[index2].matrix[x][y]<<"\t";
								}
								cout<<endl;
							}
						}
						else if(allocations[index2].rows==1 && allocations[index2].columns==1){
							for(int x=0;x<allocations[index1].rows;x++){
								for(int y=0;y<allocations[index1].columns;y++){
									cout<<allocations[index2].matrix[0][0]*allocations[index1].matrix[x][y]<<"\t";
								}
								cout<<endl;
							}
						}
						else if(allocations[index1].rows!=allocations[index2].columns){
							cout<<"error: dimensions do not match\n";
							error=1;
						}
						else{
							cout<<val1<<"*"<<val2<<"=\n";
							for(int x=0;x<allocations[index1].rows;x++){
								for(int y=0;y<allocations[index2].columns;y++){
									int val=0;
									for(int c=0;c<allocations[index1].columns;c++){
										val = val+ (allocations[index1].matrix[x][c] * allocations[index2].matrix[c][y]);
									}
									cout<<val<<"\t";
								}
								cout<<endl;
							}
						}
					}
				}
				break;
			}
			
			else if(error==0 && input[i] == '.'){
				if(input[i+1] != '*'){
					cout<<"error: invalid operator\n";
					error=1;
					break;
				}
				for(j=i+1;j<len;j++){
					if(input[j]=='=' || input[j] =='+' || input[j] == '-'){
						cout<<"error: use only one operation for statement\n";
						error=1;
						break;
					}
				}
				if(error==0){
					pos = input.find(".");
					string val1 = input.substr(0, pos);
				    input.erase(0, pos+1);
				    pos = input.find("*");
				    input.erase(0, pos+1);
				    string val2 = input;
				    
				    trim(val1);
				    trim(val2);
				    
				    for(j=0;j<MAX;j++){
				    	if(allocations[j].allocated==1 && allocations[j].name==val1){
				    		index1=j;
				    		count++;
						}
						if(allocations[j].allocated==1 && allocations[j].name==val2){
				    		index2=j;
				    		count++;
						}
					}
					if(count!=2){
						cout<<"error: values not found\n";
						error=1;
						break;
					}
					else{
						if(allocations[index1].rows==1 && allocations[index1].columns==1){
							for(int x=0;x<allocations[index2].rows;x++){
								for(int y=0;y<allocations[index2].columns;y++){
									cout<<allocations[index1].matrix[0][0]*allocations[index2].matrix[x][y]<<"\t";
								}
								cout<<endl;
							}
						}
						else if(allocations[index2].rows==1 && allocations[index2].columns==1){
							for(int x=0;x<allocations[index1].rows;x++){
								for(int y=0;y<allocations[index1].columns;y++){
									cout<<allocations[index2].matrix[0][0]*allocations[index1].matrix[x][y]<<"\t";
								}
								cout<<endl;
							}
						}
						else{
							if((allocations[index1].rows!=allocations[index2].rows) || (allocations[index1].columns != allocations[index2].columns)){
								cout<<"error: dimensions do not match\n";
								error=1;
							}
							else{
								cout<<val1<<".*"<<val2<<"=\n";
								for(int x=0;x<allocations[index1].rows;x++){
									for(int y=0;y<allocations[index1].columns;y++){
										cout<<allocations[index1].matrix[x][y]*allocations[index2].matrix[x][y]<<"\t";
									}
									cout<<endl;
								}
							}
						}		
					}
				}
				break;
			}
			else if(input!="exit" && i==len-1){
				trim(input);
				for(j=0;j<MAX;j++){
			    	if(allocations[j].allocated==1 && allocations[j].name==input){
			    		index1=j;
			    		count++;
			    		break;
					}
				}
				if(count==1){
					allocations[index1].display();
				}
				else{
					cout<<"error: value not found\n";
					error=1;
					break;
				}
			}
		}
	}
}
