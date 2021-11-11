#ifndef _LOGGENERATOR_HPP
#define _LOGGENERATOR_HPP

#include <fstream>
#include <string>
#include <unistd.h>

#include "Processor.h"

class LogGenerator {
private:
    std::ofstream output_log;
    std::vector<Processor*> core_list;
    std::vector<Cache*> cache_list;
    std::string output_path = "logs/";
    int NUM_OF_CORES = 4;
public:
    void initialize(Processor* core0, Processor* core1, Processor* core2, Processor* core3, std::string input_info) {
        core_list.push_back(core0);
        core_list.push_back(core1);
        core_list.push_back(core2);
        core_list.push_back(core3);

        cache_list.push_back(core0->get_cache());
        cache_list.push_back(core1->get_cache());
        cache_list.push_back(core2->get_cache());
        cache_list.push_back(core3->get_cache());

        output_path = output_path + input_info;
        int file_index = 0;
        std::string index;
        
        do {
            file_index += 1;
            std::stringstream ss;
            ss << file_index;
            ss >> index;            
        } while (!access((output_path + "_" + index + ".log").c_str(), F_OK));

        output_path = output_path + "_" + index + ".log";
        output_log.open(output_path, std::ios::out);

        output_log << "Outputs with inputs: " << input_info << std::endl;
        output_log << "========================================" << std::endl;

    }

    void print_compute_cycles() {
        output_log << "------------------------------" << std::endl;
        output_log << "2. Number of compute cycles per core" << std::endl;
        for (int i = 0; i < NUM_OF_CORES; i++) {
            int curr_val = core_list[i]->get_compute_cycle();
            output_log << "Core " << i << ": " << curr_val << std::endl;
        }
    }

    void print_num_mem_instr() {
        output_log << "------------------------------" << std::endl;
        output_log << "3. Number of load/store instructions per core" << std::endl;
        for (int i = 0; i < NUM_OF_CORES; i++) {
            int curr_val = core_list[i]->get_num_mem_instr();
            output_log << "Core " << i << ": " << curr_val << std::endl;
        }
    }

    void print_summary() {


        print_compute_cycles();
        print_num_mem_instr();

        output_log << "============== END OF LOG ==============" << std::endl;
        output_log << "========================================" << std::endl;
        output_log.close();
    }


};



#endif