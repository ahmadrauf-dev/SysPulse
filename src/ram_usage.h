#include <iostream>
#include <iomanip>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

void sum_ram_usage();

void sum_ram_usage()
{

    string label,unit;
    double mem_value;
    double mem_total,mem_free,mem_available,mem_buffer,mem_cached;
    fstream ram_file1("/proc/meminfo",ios::in);

    // ram_file1>>label>>mem_total>>unit;
    // ram_file1>>label>>mem_free>>unit;
    // ram_file1>>label>>mem_available>>unit;
    // ram_file1>>label>>mem_buffer>>unit;
    // ram_file1>>label>>mem_cached>>unit;

    // i should apply a specific search
    while (ram_file1 >> label >> mem_value >> unit) {
        if (label == "MemTotal:")       mem_total = mem_value;
        else if (label == "MemFree:")   mem_free = mem_value;
        else if (label == "MemAvailable:") mem_available = mem_value;
        else if (label == "Buffers:")   mem_buffer = mem_value;
        else if (label == "Cached:")    mem_cached = mem_value;
    }

    // converting to GB
    mem_total = mem_total/1048576.0;
    mem_free = mem_free/1048576.0;
    mem_available = mem_available/1048576.0;
    mem_buffer = mem_buffer/1048576.0;
    mem_cached = mem_cached/1048576.0;



    cout<<"\n==================================================\n";
    cout<<"                  RAM USAGE";
    cout<<"\n==================================================\n";
    cout<<"Total Memory     : "<<mem_total<<" GB"<<'\n'
        <<"Available Memory : "<<mem_available<<" GB"<<'\n'
        <<"Free Memory      : "<<mem_free<<" GB"<<'\n'
        <<"Buffer Memory    : "<<mem_buffer<<" GB"<<'\n'
        <<"Cached Memory    : "<<mem_cached<<" GB"<<'\n';
}