#include <iostream>
#include <iomanip>
#include <fstream>


using namespace std;

void ums_cpu_usage();

void ums_cpu_usage()
{

    // reads data from stat file
    fstream cpu_file("/proc/stat",ios::in);
    string cpu;
    long long user,nice,system,idle,iowait,irq,softira,steal;
    cpu_file>>cpu
            >>user
            >>nice
            >>system
            >>idle
            >>iowait
            >>irq
            >>softira
            >>steal;

            // just to test if it gives values
            cout<<"cpu :"<<cpu<<'\n'
                <<"user: "<<user<<'\n'
                <<"nice: "<<nice<<'\n'
                <<"system: "<<system<<'\n'
                <<"idle: "<<idle<<'\n'
                <<"iowait: "<<iowait<<'\n'
                <<"irq: "<<irq<<'\n'
                <<"softira: "<<softira<<'\n'
                <<"steal: "<<steal<<'\n';

    long long int total_usage = user + nice + system + idle + iowait + irq + softira + steal;
    long long int idle_usage = idle + iowait; 
    double cpu_usage;
    cpu_usage = static_cast<double>
    (total_usage-idle_usage)/total_usage*100;
    cout<<cpu_usage;


}