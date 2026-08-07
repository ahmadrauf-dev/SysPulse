#ifndef CPU_USAge_H
#define CPU_USAGE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <thread>
#include <chrono>


using namespace std;

void sum_cpu_usage();
double sum_cpu_temp();

void sum_cpu_usage()
{
        // getting cpu temp;
        double cpu_temp = sum_cpu_temp();
    // reads data from stat file
    const int time_interval = 1000; // it will be in milli seconds
    fstream cpu_file1("/proc/stat",ios::in);
    string cpu;
    long long user,nice,system,idle,iowait,irq,softirq,steal;
    cpu_file1>>cpu
            >>user
            >>nice
            >>system
            >>idle
            >>iowait
            >>irq
            >>softirq
            >>steal;

    cpu_file1.close();

            // just to test if it gives values
            // cout<<"cpu :"<<cpu<<'\n'
            //     <<"user: "<<user<<'\n'
            //     <<"nice: "<<nice<<'\n'
            //     <<"system: "<<system<<'\n'
            //     <<"idle: "<<idle<<'\n'
            //     <<"iowait: "<<iowait<<'\n'
            //     <<"irq: "<<irq<<'\n'
            //     <<"softira: "<<softira<<'\n'
            //     <<"steal: "<<steal<<'\n';

            // i am measuring this at one instant 
    long long prev_total_usage = user + nice + system + idle + iowait + irq + softirq + steal;
    long long prev_idle_usage = idle + iowait; 
    
    // now i will measure it at a interval of like 500ms

    this_thread::sleep_for(chrono::milliseconds(time_interval));

    fstream cpu_file2("/proc/stat",ios::in);

    cpu_file2>>cpu
             >>user
             >>nice
             >>system
             >>idle
             >>iowait
             >>irq
             >>softirq
             >>steal;
    cpu_file2.close();

    long long current_total_usage = user + nice + system + idle + iowait + irq + softirq + steal;
    long long current_idle_usage = idle + iowait;

    //calculating total difference so this will give the cpu usage at the preseny instance

    long long total_usage = current_total_usage - prev_total_usage;
    long long idle_usage = current_idle_usage - prev_idle_usage;

    double cpu_usage = (double)(total_usage - idle_usage)/total_usage * 100.0;

    cout<<fixed<<setprecision(2);
    cout<<"\n==================================================\n";
    cout<<"                  CPU USAGE";
    cout<<"\n==================================================\n";
    cout<<"Cpu Usage        : "<< cpu_usage<<"%"<<"\n";
        if(cpu_temp!=-1)
        {
                cout<<"CPU Temperature  : "<<cpu_temp<<"°C"<<endl;    
        }else{
                cout<<"CPU Temperature  : "<<" N/A "<<endl;
        }
        

//     while(getline(cpu))


}
 double sum_cpu_temp()
 {
        fstream cpu_temp_file("/sys/class/thermal/thermal_zone0/temp",ios::in);
        int cpu_temp;
        if(!cpu_temp_file)
        {
                return -1;
        }
        cpu_temp_file>>cpu_temp;
        return cpu_temp/1000.0;
 }

#endif