#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <filesystem>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
void sum_pid_info();

// change this to change how many top processes to show
const int check_number_of_processes = 10;
struct Process
{
    int pid;
    string name;
    long total_time;
    long current_time;

};
void sum_pid_info()
{
    vector<Process> cpu_processes;

    // idk what i am doing but hope it works

    // -_-

    // saving the first snapshot
    for(auto file:filesystem::directory_iterator("/proc"))
    {
        string temp_name = file.path().filename();
        bool is_pid = true;
        for(char c : temp_name )
        {
            if(!isdigit(c))
            {
                is_pid = false;
                break;
            }
        }
        if(is_pid)
        {
            string path = "/proc/" + temp_name + "/stat";
            ifstream processFile(path);
            if(processFile.is_open())
            {
                Process p1;
                // cout<<"Opened"<<path<<endl;
                int cpu_pid;
                string process_name;
                char state;
                long utime,stime;
                string temp;
                processFile>>cpu_pid;
                processFile>>process_name;
                processFile>>state;

                // cout<<"PID: "<<cpu_pid<<endl;
                // cout<<"Name: "<<process_name<<endl;
                // cout<<"State: "<<state<<endl;

                for(int i =0;i<10;i++)
                {
                    processFile>>temp;
                }
                processFile>>utime;
                processFile>>stime;
                // cout<<process_name<<" "
                //     <<utime<<" "
                //     <<stime<<" "<<endl;

                p1.pid = cpu_pid;
                p1.name = process_name;
                // p1.utime = utime;
                // p1.stime = stime;
                p1.total_time = utime + stime;
                p1.current_time=p1.total_time;

                // cout<<p1.pid<<" "
                //     <<p1.name<<" "
                //     <<p1.utime<<" "
                //     <<p1.stime<<endl;

                cpu_processes.push_back(p1);
            }else{
                continue;
                cout<<"failed"<<endl;
            }
        }
        
    }
    // stopping for one second before reading again so i can get the instantaneous value
    sleep(1);
    for(auto file:filesystem::directory_iterator("/proc"))
    {
        string temp_name = file.path().filename();
        bool is_pid = true;
        for(char c : temp_name )
        {
            if(!isdigit(c))
            {
                is_pid = false;
                break;
            }
        }
        if(is_pid)
        {
            string path = "/proc/" + temp_name + "/stat";
            ifstream processFile(path);
            if(processFile.is_open())
            {
                // Process p1;
                // p1.current_time=0;
                // cout<<"Opened"<<path<<endl;
                int cpu_pid;
                string process_name;
                char state;
                long utime,stime;
                string temp;
                processFile>>cpu_pid;
                processFile>>process_name;
                processFile>>state;

                // cout<<"PID: "<<cpu_pid<<endl;
                // cout<<"Name: "<<process_name<<endl;
                // cout<<"State: "<<state<<endl;

                for(int i =0;i<10;i++)
                {
                    processFile>>temp;
                }
                processFile>>utime;
                processFile>>stime;

                long current_time = utime + stime;

                for(auto &p1:cpu_processes)
                {
                    if(p1.pid==cpu_pid)
                    {
                        p1.current_time = current_time;
                        break;
                    }
                }
                // cout<<process_name<<" "
                //     <<utime<<" "
                //     <<stime<<" "<<endl;

                // p1.pid = cpu_pid;
                // p1.name = process_name;
                // // p1.utime = utime;
                // // p1.stime = stime;
                // p1.total_time = utime + stime;

                // cout<<p1.pid<<" "
                //     <<p1.name<<" "
                //     <<p1.utime<<" "
                //     <<p1.stime<<endl;

                // cpu_processes.push_back(p1);
            }else{
                cout<<"failed"<<endl;
                continue;
            }
        }
        
    }
    sort(cpu_processes.begin(), cpu_processes.end(),
    [](const Process &a, const Process &b)
    {
        return (a.current_time - a.total_time) >
               (b.current_time - b.total_time);
    });
    for(int i = 0; i < check_number_of_processes && i < cpu_processes.size(); i++)
    {
        long delta = cpu_processes[i].current_time - cpu_processes[i].total_time;
        if(delta == 0)
        continue;
        cout << cpu_processes[i].pid << " "
             << cpu_processes[i].name << " "
             << delta << endl;
    }
    

    
}