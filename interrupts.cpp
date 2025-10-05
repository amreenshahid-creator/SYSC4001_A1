/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */

#include "interrupts.hpp"

int main(int argc, char** argv) {

    //vectors is a C++ std::vector of strings that contain the address of the ISR
    //delays  is a C++ std::vector of ints that contain the delays of each device
    //the index of these elemens is the device number, starting from 0
    auto [vectors, delays] = parse_args(argc, argv);
    std::ifstream input_file(argv[1]);

    std::string trace;      //!< string to store single line of trace file
    std::string execution;  //!< string to accumulate the execution output

    /******************ADD YOUR VARIABLES HERE*************************/

    int kernel_switch_time = 1;
    int save_restore_context_time = 10;
    int ISR_start_address_time = 1;
    int get_address = 1;
    int execute_ISRbody_time = 40;
    int execute_IRET_time = 1;
    int current_time = 0;

    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);

        /******************ADD YOUR SIMULATION CODE HERE*************************/
        
        if(activity == "CPU") {             //handles the activity CPU burst and is responsible for the durations.

            execution += std:: to_string(current_time) + ", " + std:: to_string(duration_intr) + ", CPU Burst\n"; //Time of event, Duration of the event, Event type
            current_time += duration_intr;  // updates the current time
        }


        else if(activity == "SYSCALL") {
            
        } 



        else if(activity == "END_IO") {}


        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}
