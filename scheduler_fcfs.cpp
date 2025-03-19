/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Joel Burlingame
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here

SchedulerFCFS::SchedulerFCFS(){
    total_turnaround_time = 0;
    total_waiting_time = 0;
}

SchedulerFCFS::~SchedulerFCFS(){
    std::cout << "\nRunning ./fcfs schedule.txt " << endl;

}

void SchedulerFCFS::init(std::vector<PCB>& process_list) {
    //copy pcbs into ready_queue
    for(auto& process : process_list){
        ready_queue.push(process);
    }
    process_copy = process_list;

    for(int i = 0; i < process_copy.size(); i++){
        std::cout << "Process " << i << ": " << process_copy.at(i).name + " has priotity " 
        << process_copy.at(i).priority << " and burst time " << process_copy.at(i).burst_time << endl;
    }
}

void SchedulerFCFS::print_results(){
    double avg_waiting_time = static_cast<double>(total_waiting_time) / waiting_times.size();
    double avg_turnaround_time = static_cast<double>(total_turnaround_time) / turnaround_times.size();

    for(int i = 0; i < process_copy.size(); i++){
        std::cout << process_copy.at(i).name << " turn-around-time = " 
        << turnaround_times.at(i) << ", waiting time = " << waiting_times.at(i) << endl;
    }
    std::cout << "Average turn-around time = " << avg_turnaround_time << " , Average waiting time = " << avg_waiting_time << endl;
}

void SchedulerFCFS::simulate(){
    //current_time var
    unsigned int current_time = 0;

    while(!ready_queue.empty()){
        //store pcb into process var and pop current pcb from ready_queue
        PCB process = ready_queue.front();
        ready_queue.pop();
        //reporting status
        std::cout << "Running Process " << process.name << " for " << process.burst_time << " time units" << endl;

        //get current waiting time from current time
        unsigned int waiting_time = current_time;
        waiting_times.push_back(waiting_time);

        //get current turnaround time from TT formula
        //TT = CT - AT or TT = WT + BT
        unsigned int turnaround_time = waiting_time + process.burst_time;
        turnaround_times.push_back(turnaround_time);

        //getting new burst time
        current_time += process.burst_time;
        //calculating new total wait time
        total_waiting_time += waiting_time;
        //calculating new total turnaround time
        total_turnaround_time += turnaround_time;

    }
}
