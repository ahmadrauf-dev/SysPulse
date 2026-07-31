#include <iostream>
#include <iomanip>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdio>

using namespace std;

void sum_gpu_usage();
void amd_gpu_usage();
void intel_gpu_usage();
void nvidia_gpu_usage();

void sum_gpu_usage()
{
    // 0x10de -> Nvidia
    // 0x1002 -> AMD
    // 0x8086 -> intel


    int gpu_vendor = 0;
    string gpu_vendor_id;
    fstream gpu_detect_file("/sys/class/drm/card0/device/vendor",ios::in);
    gpu_detect_file>>gpu_vendor_id;gpu_detect_file.close();
    if(gpu_vendor_id=="0x10de")
    {
        gpu_vendor = 1;
    }else if(gpu_vendor_id=="0x1002")
    {
        gpu_vendor = 2;
    }else if(gpu_vendor_id=="0x8086")
    {
        gpu_vendor = 3;
    }

    switch(gpu_vendor)
    {
        case 1:nvidia_gpu_usage();break;
        case 2:amd_gpu_usage();break;
        case 3:intel_gpu_usage();break;
        default:cout<<"Error"<<endl;
    }



}

void amd_gpu_usage()
{
    double gpu_usage;
    double vram_usage;
    double vram_total;
    fstream amd_usage_file("/sys/class/drm/card0/device/gpu_busy_percent",ios::in);
    amd_usage_file>>gpu_usage;
    amd_usage_file.close();

    fstream amd_vram_usage_file("/sys/class/drm/card0/device/mem_info_vram_used",ios::in);
    amd_vram_usage_file>>vram_usage;
    amd_vram_usage_file.close();

    fstream amd_vram_total_file("/sys/class/drm/card0/device/mem_info_vram_total",ios::in);
    amd_vram_total_file>>vram_total;
    amd_vram_total_file.close();

    // converting to MB
    vram_usage = vram_usage/1048576.0;
    vram_total = vram_total/1048576.0;

    cout<<"\n==================================================\n";
    cout<<"                  GPU USAGE";
    cout<<"\n==================================================\n";
    cout<<"GPU Vendor       : AMD"<<'\n'
        <<"GPU Utilisation  : "<<gpu_usage<<"%"<<'\n'  
        <<"Vram Usage       : "<<vram_usage<<" MB"<<'\n'
        <<"Vram Total       : "<<vram_total<<" MB"<<endl;
}

void intel_gpu_usage()
{

    
}

void nvidia_gpu_usage()
{
    // FILE *pipe = popen("nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits","r");
    // if(pipe==nullptr)
    // return -1;
}
