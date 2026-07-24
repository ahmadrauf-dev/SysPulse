#include <iostream>
#include <iomanip>
#include <fstream>
#include <thread>
#include <chrono>
#include <sys/statvfs.h>

using namespace std;

void sum_disk_usage();
struct statvfs disk;
void sum_disk_usage()
{
    statvfs("/", &disk);

    // //total blocks
    // disk.f_blocks;
    // //free blocks
    // disk.f_bfree;
    // // available block
    // disk.f_bavail;
    // // block size in byte
    // disk.f_frsize;

    long long total_disk = disk.f_blocks * disk.f_frsize;
    long long free_disk = disk.f_bavail * disk.f_frsize;
    long long used_disk = total_disk - free_disk;
    // #TODO
    // disk usage is not showing value fix it
    double usage_disk = (double)used_disk/total_disk*100.0;

    total_disk = total_disk/1073741824.0;
    free_disk = free_disk/1073741824.0;
    used_disk = used_disk/1073741824.0;
    usage_disk = usage_disk/1073741824.0;

    cout<<"\n==================================================\n";
    cout<<"                  DISK USAGE";
    cout<<"\n==================================================\n";
    cout<<"Disk Total       : "<<total_disk<<" GB"<<'\n';
    cout<<"Disk Used        : "<<used_disk<<" GB"<<'\n';
    cout<<"Disk free        : "<<free_disk<<" GB"<<'\n';
    // cout<<"usage            : "<<usage_disk<<" GB"<<'\n';

}