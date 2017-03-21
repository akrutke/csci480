
/***********************************************
Andrew Krutke
CSCI480 Operating Systems
Due  March 2

Make a program to read in some information.
The create fork process and determine information
about the processes.
***********************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <sys/utsname.h>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

//function prototypes
string get_cpu_info(string);

//Main
int main(int argc, char** argv)
{

cout << unitbuf;   //flush cout


//variables
struct utsname sysinfo;
uname(&sysinfo);
char const * get_env_string = getenv("PATH");
string ge_string;
string main_os_type = "/proc/sys/kernel/ostype"; 
string main_host = "/proc/sys/kernel/hostname";
string main_release = "/proc/sys/kernel/osrelease";
string main_version = "/proc/sys/kernel/version";

//function calls
string a = get_cpu_info(main_os_type);
string b = get_cpu_info(main_host);
string c = get_cpu_info(main_release);
string d = get_cpu_info(main_version);


//printing block
cout << "Field" << setw(20) << "File Data" << setw(50) << "API data" <<endl;
cout << "ostype" << setw(18) << a << setw(50) << sysinfo.sysname << endl;
cout << "hostname" << setw(17) << b << setw(50) << sysinfo.nodename << endl;
cout << "osrealse" << setw(25) << c << setw(50) << sysinfo.release << endl;
cout << "version" << setw(55) << d << setw(50) << sysinfo.version << endl;
cout << "Machine" << setw(68) << sysinfo.machine <<endl;

//getenv() section
if (get_env_string == NULL)
{	
string ge_string = "";		//make it blank on error
}
else     //the magic happens here
{	
string ge_string(get_env_string);  //move the char array into a string
string sub_path;

cout << endl << "My path is " << ge_string << endl << endl;  //get our path

   vector<string> path_strings;
   size_t start = ge_string.find_first_not_of(':'); 		//look for colons
   size_t end = 0;
   int total = 0;

while((end = ge_string.find_first_of(':', start)) !=string::npos)  //find some  colons
    {
        path_strings.push_back(ge_string.substr(start, end - start));   //move those substrings into a vector
        start = ge_string.find_first_not_of(':', end);
    }

    if(start != string::npos)				//check if we done
        path_strings.push_back(ge_string.substr(start));
	
for (unsigned int i = 0; i < path_strings.size(); i++)   //print out this vector!!!!!!!!
	{

            cout << path_strings[i] << setw(40 - path_strings[i].size()) <<  std::right << path_strings[i].size() << endl;;
            total +=  path_strings[i].size();	
	}
	cout<< endl << "Total" << setw(35) << total  << " Entries " << path_strings.size() <<endl;
	cout <<endl;
}

//fork, wait, system Part c stuff
int fork_1_call = 0;		//call first fork and make 1st set of process
int fork_2_call = 0;		//call second fork and make second set of process
int parent_1_pid = 0;
int kid_1_pid = 0;
int kid_2_pid = 0;
int mid_pid = 0;
int pid = 0;
string process_id;
//build our string variables
ostringstream  pid_out, pid_out_2, pid_out_3, pid_out_4;	//easier than clearing 
stringstream found_pids;


fork_1_call = fork();		//create out forks
fork_2_call = fork();

	if(fork_1_call == -1)		//check for errors in fork call
		return 1;
	if (fork_2_call ==-1)
		return 1;


if(fork_1_call > 0 && fork_2_call > 0 )		//check if they are children
	{

	pid = getpid();				//find those ids
	parent_1_pid = getppid();
 	
	//print it
	pid_out << "Parent: My PID is " << pid << "." << endl << "My parent is " << parent_1_pid << "." <<  endl
	<< "My children are " << fork_1_call << " and " << fork_2_call << "." << endl << endl;

	
	cout << pid_out.str()<<endl;

	//string to pass pids to system call
	found_pids << pid << "," << parent_1_pid << "," << fork_1_call << "," <<fork_2_call;
 
	process_id = "/bin/ps -f --ppid " + found_pids.str();
	
	cout << "Parent: Issuing command " << process_id << endl << endl;	

	system(process_id.c_str());		//call to the system

	cout << endl;

	waitpid(fork_2_call, 0, 0);        //make our processes wait
	waitpid(fork_1_call, 0, 0);

	}

	if(fork_1_call ==  0 && fork_2_call > 0)
	{
	
	mid_pid = getpid();		//get new pid
	pid = getppid();		//and the parents

	pid_out_2 << "Middle: My PID is " << mid_pid << "." << endl << "My parent is " <<
	pid << endl << "My child is " << fork_2_call << "." << endl << endl;	//build it up
												
	cout << pid_out_2.str() << endl;			//break it down -torbjorn

	system("sleep 3");		//sleep for a second

	cout << "Middle: " << mid_pid << " is awake." << endl<< endl;

	}

	//make the child process
	if(fork_1_call > 0 && fork_2_call == 0)
	{
	kid_1_pid = getpid();		//get the pids
	pid = getppid();

	pid_out_3 << "Child: My pid is " << kid_1_pid << "." << endl 
	<< "My parent is " << pid <<"." << endl << endl;

	cout << pid_out_3.str() << endl;

	system("sleep 3");		//sleep and wake up

	cout << "Child: " << kid_1_pid << " is awake." << endl << endl;
	}

	//last child process call, processes same as above
	if(fork_1_call == 0 && fork_2_call == 0)
	{
	
	kid_2_pid = getpid();
	mid_pid = getppid();

	pid_out_4 << "Child: My pid is " << kid_2_pid << "." << endl 
	<< "My parent is " << mid_pid << "." << endl << endl;

	cout << pid_out_4.str() <<endl;

	system("sleep 3");
		
	cout << "Child: " << kid_2_pid << " is awake." << endl << endl;
	}

return 0;
}


/*******************************************
Get info based on the path sent to the 
function about the operating systems
Parms: string
********************************************/
string get_cpu_info(string a)
{
    ifstream inFile;
    string os_info;

        inFile.open(a);
                if(!inFile)                     // error testing
                {
                        cout << "Error: Cannot open file." << endl;
                        exit(1);
                }
                while(!inFile.eof())
                {
                        getline(inFile,os_info);         // type of operating system
                        return os_info;
                }
        inFile.close();

        return os_info;
}

