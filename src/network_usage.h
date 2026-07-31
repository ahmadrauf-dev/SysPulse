#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>


using namespace std;
void sum_network_usage();
void sum_network_usage()
{
    cout<<"\n==================================================\n";
    cout<<"                  NETWORK USAGE";
    cout<<"\n==================================================\n"; 
    string network_data1;
    string network_data2;
    string wlan_interface;
    const int time_interval = 1000;
    fstream network_file1("/proc/net/dev",ios::in);
    this_thread::sleep_for(chrono::milliseconds(time_interval));
    fstream network_file2("/proc/net/dev",ios::in);
    // ignoring the first two lines as i wont be needing them atleasst for now
    getline(network_file1,network_data1);getline(network_file2,network_data2);
    getline(network_file1,network_data1);getline(network_file2,network_data2);
    while(getline(network_file1,network_data1)&& getline(network_file2,network_data2))
    {


        // First instant
        unsigned long long prev_rxBytes;
        unsigned long long prev_txBytes;
        // so first found the colon position and what was before that was interface name
        size_t colon_position1 = network_data1.find(":");
        if (colon_position1 == string::npos) continue;

        // subtracted to find out the name
        string connection_interface = network_data1.substr(0,colon_position1);
        // the read the data which was infront of the colon,only the first too ignored the rest;
        string interface_data1 = network_data1.substr(colon_position1+1);
        stringstream stream_data1(interface_data1);

        stream_data1>>prev_rxBytes;
        // there are 7 more receive field before the transfer bytes so skipping them with loop
        string temp;
        for(int i = 0;i<7;i++)
        {
            stream_data1>>temp;
        }
        stream_data1>>prev_txBytes;
        
        // Second instant
        unsigned long long curr_rxbytes;
        unsigned long long curr_txBytes;

        size_t colon_position2 = network_data2.find(":");
        string interface_data2 = network_data2.substr(colon_position2+1);
        stringstream stream_data2(interface_data2);
        stream_data2>>curr_rxbytes;
        string temp2;
        for(int i =0;i<7;i++)
        {
            stream_data2>>temp2;       
        }
        stream_data2>>curr_txBytes;

        unsigned long long total_rxBytes = curr_rxbytes - prev_rxBytes;
        unsigned long long total_txBytes = curr_txBytes - prev_txBytes;

        double interval_sec = time_interval / 1000.0;
        double rx_kb = (total_rxBytes / interval_sec) / 1024.0;
        double tx_kb = (total_txBytes / interval_sec) / 1024.0;

        cout<<"Interface Type   : "<<connection_interface<<'\n'
            <<"Receive          : "<<rx_kb<<"kb/s"<<'\n'
            <<"Transfer         : "<<tx_kb<<"kb/s"<<endl;







        
        


        
    }
    network_file1.close();
    network_file2.close();
}