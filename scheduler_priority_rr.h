/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.h
 * @author Joel Burlingame
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#ifndef ASSIGN3_SCHEDULER_PRIORITY_RR_H
#define ASSIGN3_SCHEDULER_PRIORITY_RR_H

#include "scheduler.h"
#include <queue>
#include <algorithm>
#include <numeric>
#include <map>
#include <unordered_map>
#include <iterator>
#include <functional>

class SchedulerPriorityRR : public Scheduler {
private:
    std::vector<PCB> process_copy;
    std::vector<unsigned int> turnaround_times;
    std::vector<unsigned int> waiting_times;
    unsigned int total_turnaround_time;
    unsigned int total_waiting_time;
    unsigned int time_quantum;

public:
    /**
     * @brief Construct a new SchedulerPriority object
     */
    SchedulerPriorityRR(int time_quantum = 10);

    /**
     * @brief Destroy the SchedulerPriority object
     */
    ~SchedulerPriorityRR() override;

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    void init(std::vector<PCB>& process_list) override;

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    void print_results() override;

    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    void simulate() override;

};


#endif //ASSIGN3_SCHEDULER_PRIORITY_RR_H
