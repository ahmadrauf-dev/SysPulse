#include <iostream>
#include "cpu_usage.h"
#include "ram_usage.h"
#include "disk_usage.h"
#include "system_info.h"
#include "gpu_usage.h"

using namespace std;


int main()
{
    cout<<"\n==================================================\n";
    cout<<"            SYSTEM USAGE MONITOR";
    sum_cpu_usage(); 
    sum_ram_usage();
    sum_disk_usage();
    sum_system_info();
    sum_gpu_usage();
}
