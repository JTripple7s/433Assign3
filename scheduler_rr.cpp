/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Joel Burlingame
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"

SchedulerRR::SchedulerRR(int time_quantum){
    total_turnaround_time = 0;
    total_waiting_time = 0;
    this->time_quantum = time_quantum;
}

SchedulerRR::~SchedulerRR(){

}

void SchedulerRR::init(std::vector<PCB>& process_list) {
    process_copy = process_list;

    waiting_times.resize(process_copy.size(), 0);
    turnaround_times.resize(process_copy.size(), 0);

    //copy pcbs into ready_queue
    for (size_t i = 0; i < process_copy.size(); ++i) {
        ready_queue.push(process_copy[i]);
    }
}

void SchedulerRR::print_results(){
    //vars get avg of respective times
    double avg_waiting_time = static_cast<double>(total_waiting_time) / waiting_times.size();
    double avg_turnaround_time = static_cast<double>(total_turnaround_time) / turnaround_times.size();

    for(int i = 0; i < process_copy.size(); i++){
        std::cout << process_copy.at(i).name << " turn-around-time = " 
        << turnaround_times.at(i) << ", waiting time = " << waiting_times.at(i) << std::endl;
    }
    std::cout << "Average turn-around time = " << avg_turnaround_time << " , Average waiting time = " << avg_waiting_time << std::endl;
}

void SchedulerRR::simulate() {
    unsigned int current_time = 0;
    std::vector<unsigned int> remaining_burst(process_copy.size());

    // Initialize remaining burst times
    for (size_t i = 0; i < process_copy.size(); ++i) {
        remaining_burst[i] = process_copy[i].burst_time;
    }

    // Execute round robin scheduling
    while (!ready_queue.empty()) {
        PCB process = ready_queue.front();
        ready_queue.pop();

        // Get index of the current process
        size_t idx = std::distance(process_copy.begin(), 
            std::find_if(process_copy.begin(), process_copy.end(), 
            [&process](const PCB& p) { return p.id == process.id; }));

        if (idx >= process_copy.size()) {
            std::cerr << "Error: Process ID out of range!" << std::endl;
            return;  // Prevent out-of-bounds access
        }

        unsigned int exec_time = std::min(static_cast<unsigned int>(time_quantum), remaining_burst[idx]);

        std::cout << "Running Process " << process.name << " for " << exec_time << " time units" << std::endl;

        remaining_burst[idx] -= exec_time;
        current_time += exec_time;

        if (remaining_burst[idx] > 0) {
            // Add process back to queue if it needs more time
            ready_queue.push(process);
        } else {
            // Process finished
            turnaround_times[idx] = current_time;
            waiting_times[idx] = turnaround_times[idx] - process.burst_time;
        }
    }

    // Calculate total turnaround and waiting time
    total_turnaround_time = std::accumulate(turnaround_times.begin(), turnaround_times.end(), 0);
    total_waiting_time = std::accumulate(waiting_times.begin(), waiting_times.end(), 0);
}