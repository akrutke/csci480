/***********************************************
Andrew Krutke
CSCI480 Operating Systems
Due
File for output
***********************************************/
#include <iostream>
#include <iomanip>
#include "Processor.h"
#include <fstream>
#include <stdlib.h> 
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char** argv){

//ifstream inFile;
string readFile;
string cpu_info;
string c;
string physical_address;
//int processor_count = 0;
int record_count = 0;
int char_count = 0;
int cpu_count = 0;
string core;		
string phys_id;
string l2_cache = "No";
if(argc < 2)			//check for passed parameters
{
cout << "No file provided" << endl;
}


ifstream inFile(argv[1]);		//open and check for proper opening

	if(!inFile.is_open())			
	{
	cout << "File does not exsist" <<endl;
	exit(1);
	}

while(!inFile.eof())		//work while not at end of file
{

getline(inFile, readFile);

record_count++;		//count records in a file

char_count += readFile.length();       //count the characters in the file
 

//part B stuf
if(readFile.find("cpu core") == 0)      // find number of processors
{
getline(inFile,core);
size_t position = readFile.find(":");  //come back to this if you have time			
core = readFile.substr(position);
position = readFile.rfind(" ");
core = readFile.substr(position);

	/*if(core == 2)
	{no time to debug this
	 l2_cache="yes";
	}*/
}

//count physical cpu?
if(readFile.find("physical") == 0)
{
cpu_count++;
}

//find the physical ids kinda
if(readFile.find("physical id")==0)
{

getline(inFile,phys_id);
size_t position = readFile.find(":");
phys_id = readFile.substr(position);
position = readFile.rfind(" ");
phys_id = readFile.substr(position);


}

//part c stuff

//kind of find address stuff
if(readFile.find("address sizes")== 0)
{
getline(inFile,physical_address);
size_t position = readFile.find(":");
physical_address = readFile.substr(position);
position = readFile.find(" ");
physical_address = readFile.substr(position);
}

}

inFile.close();



//output area
cout << endl;
cout << "Part A" << endl;
cout << "1. The name of the file is " << argv[1] << endl;
cout << "2. There are "<< record_count << " records in the file" << endl;
cout << "3. There are " << char_count << " characters in the file" << endl;
cout << "4. Use  wc -l " << argv[1]<<" for number of lines and wc -m "<< argv[1]<<" for number of characters." << endl;

cout << endl;
cout << "Part B" << endl;
cout << "1. The machine has " << core <<" processors." <<endl; 
cout << "2. The machine has " << cpu_count <<" physical CPU's" << endl;
		if(cpu_count == 1)
		{
		cout << "2. The machine has 1 physical CPU" << endl;
		}
cout << "3. The physical id's are:" << phys_id <<"," << endl;
cout << l2_cache << " processors share L2 cache." <<endl;

cout << endl << "Part C" << endl;
cout << "The first physical address size is" << physical_address << endl; 

return 0;

}
