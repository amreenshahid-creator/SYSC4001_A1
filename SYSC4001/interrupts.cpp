/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */

#include <interrupts.hpp>

int main(int argc, char** argv) {

    //vectors is a C++ std::vector of strings that contain the address of the ISR
    //delays  is a C++ std::vector of ints that contain the delays of each device
    //the index of these elemens is the device number, starting from 0
    auto [vectors, delays] = parse_args(argc, argv);
    std::ifstream input_file(argv[1]);

    std::string trace;      //!< string to store single line of trace file
    std::string execution;  //!< string to accumulate the execution output

    /******************ADD YOUR VARIABLES HERE*************************/
    int time = 0;
    int context_saved_time = 33;
    

    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);

        /******************ADD YOUR SIMULATION CODE HERE*************************/
        if (activity == "CPU") {
            execution += std:: to_string(time) + ", " + std::to_string(duration_intr) + ", CPU burst\n";
            time += duration_intr;
        }
        else if (activity == "SYSCALL") {
            auto [write, delayed_time] = intr_boilerplate(time, argc, context_saved_time, vectors);
            execution += write;
            time += delayed_time;
            execution += std:: to_string(time) + ", " + std::to_string(duration_intr) +  ", IRET\n";
            time += 1;
        }
        else if(activity == "END_IO") {
            execution += std:: to_string(time) + ", " + std::to_string(duration_intr) + ", Store information in memory.\n";
        }


        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}
