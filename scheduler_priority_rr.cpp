/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Joel Burlingame
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_priority_rr.h"

SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum){
    total_turnaround_time = 0;
    total_waiting_time = 0;
    this->time_quantum = time_quantum;
}

SchedulerPriorityRR::~SchedulerPriorityRR(){

}

void SchedulerPriorityRR::init(std::vector<PCB>& process_list) {
    process_copy = process_list;

    waiting_times.resize(process_copy.size(), 0);
    turnaround_times.resize(process_copy.size(), 0);

    //copy pcbs into ready_queue
    std::sort(process_copy.begin(), process_copy.end(), [](const PCB& a, const PCB& b) {
        return a.priority > b.priority;
    });
}

void SchedulerPriorityRR::print_results(){
    //vars get avg of respective times
    double avg_waiting_time = static_cast<double>(total_waiting_time) / waiting_times.size();
    double avg_turnaround_time = static_cast<double>(total_turnaround_time) / turnaround_times.size();

    for(int i = 0; i < process_copy.size(); i++){
        std::cout << process_copy.at(i).name << " turn-around-time = " 
        << turnaround_times.at(i) << ", waiting time = " << waiting_times.at(i) << std::endl;
    }
    std::cout << "Average turn-around time = " << avg_turnaround_time << " , Average waiting time = " << avg_waiting_time << std::endl;
}

void SchedulerPriorityRR::simulate() {
    unsigned int current_time = 0;

    // Map to track remaining burst time by process ID
    std::unordered_map<int, unsigned int> remaining_burst;
    for (const auto& process : process_copy) {
        remaining_burst[process.id] = process.burst_time;
    }

    // Use a multimap to maintain priority ordering
    std::multimap<int, PCB, std::greater<int>> priority_queue;  // Highest priority first

    // Populate the initial queue with the processes
    for (auto& process : process_copy) {
        priority_queue.insert({process.priority, process});
    }

    while (!priority_queue.empty()) {
        auto it = priority_queue.begin();
        PCB process = it->second;
        priority_queue.erase(it);  // Remove the current process from the map

        size_t idx = std::distance(process_copy.begin(),
                                   std::find_if(process_copy.begin(), process_copy.end(),
                                                [&process](const PCB& p) { return p.id == process.id; }));

        if (idx >= process_copy.size()) {
            std::cerr << "Error: Process ID out of range!" << std::endl;
            return;
        }

        unsigned int exec_time = std::min(time_quantum, remaining_burst[process.id]);

        std::cout << "Running Process " << process.name
                  << " for " << exec_time << " time units" << std::endl;

        remaining_burst[process.id] -= exec_time;
        current_time += exec_time;

        if (remaining_burst[process.id] > 0) {
            // If process needs more time, reinsert it with the same priority
            priority_queue.insert({process.priority, process});
        } else {
            // Calculate turnaround and waiting times for completed processes
            turnaround_times[idx] = current_time;
            waiting_times[idx] = turnaround_times[idx] - process.burst_time;
        }
    }

    // Calculate total turnaround and waiting times
    total_turnaround_time = std::accumulate(turnaround_times.begin(), turnaround_times.end(), 0);
    total_waiting_time = std::accumulate(waiting_times.begin(), waiting_times.end(), 0);
}

