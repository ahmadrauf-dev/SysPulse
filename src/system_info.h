#include <iostream>
#include <iomanip>
#include <fstream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <sys/utsname.h>

using namespace std;

void sum_system_info();

void sum_system_info()
{
    // this gets the pc name
    char hostname[256];
    gethostname(hostname,sizeof(hostname));

    // kernal version

    struct utsname info;
    uname(&info);

    // uptime 
    int hours,minutes,seconds;
    fstream uptime_file("/proc/uptime",ios::in);
    if(!uptime_file)
    {
       cout<<"Uptime           :  Error opening file"; 
    }
    double system_uptime;
    uptime_file>>system_uptime;
    uptime_file.close();
    hours = system_uptime/3600.0;

    int remaining = (int)system_uptime%3600;
    minutes = remaining/60;
    seconds = remaining%60;

    // Finding os version
    string temp_os_line;
    string os_version;
    fstream os_file("/etc/os-release",ios::in);
    while(getline(os_file,temp_os_line))
    {
        if(temp_os_line.find("PRETTY_NAME=")==0)
        {
            string temp_os_version = temp_os_line.substr(12);
            temp_os_version = temp_os_version.substr(1,temp_os_version.size()-2);
            os_version = temp_os_version;
        }
        break;
    }


    cout<<"\n==================================================\n";
    cout<<"                  SYSTEM INFO";
    cout<<"\n==================================================\n";
    cout<<"PC NAME          : "<<hostname<<'\n'
        <<"OS Version       : "<<os_version<<'\n'
        <<"Kernel           : "<<info.release<<'\n'
        <<"Uptime           : "<<hours<<"h"<<minutes<<"m"<<seconds<<"s"<<'\n'
        <<"CPU Cores        : "<<thread::hardware_concurrency()<<'\n'
        <<"Architecture     : "<<info.machine<<'\n';

}