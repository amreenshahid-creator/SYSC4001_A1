/**

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

    //int kernel_switch_time = 1;
    int save_restore_context_time = 10;
    //int ISR_start_address_time = 1;
    //int get_address_time= 1;
    //int execute_ISRbody_time = 40;
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
            // Summary of what this command will do
            // 1. Switch modes 
            // 2. Update time using kernel_switch_time and save_restore_context_time
            // 3. From the device number, calculate where in memory the address is in
            // 4. Update time using ISR_start_address_time
            // 5. Get ISR address from vector table
            // 6. Update time using get_address_time

            // *helper function intr_boilerplate already does the steps above*

            // 7. Execute the ISR body
            // 8. Update time using delays
            // 9. Execute IRET
            // 10. Update time using execute_IRET_time
            
            auto[execute, time] = intr_boilerplate(current_time, duration_intr - 1, save_restore_context_time, vectors);
            execution += execute; 
            current_time = time;
            

            // 7. Execute the ISR body
            execution += std::to_string(current_time) + ", " + std:: to_string(delays[duration_intr - 1]) + ", SYSCALL: run the ISR (device driver)\n";

            // 8. Update time using delays 
            current_time += delays[duration_intr - 1]; //get delay (ms) from the device_table

            // 9. Execute IRET
            execution += std:: to_string(current_time) + ", " + std:: to_string(execute_IRET_time) + ", SYSCALL: Return from ISR\n"; //this doesnt have a event type in example exec.file but made one any way

            // 10. Update time using execute_IRET_time
            current_time += execute_IRET_time; 

        } 

        else if(activity == "END_IO") {
            //Same logic as System calls

            auto[execute, time] = intr_boilerplate(current_time, duration_intr - 1, save_restore_context_time, vectors);
            execution += execute; 
            current_time = time;
            
            execution += std::to_string(current_time) + ", " + std:: to_string(delays[duration_intr - 1]) + ", END_IO: run the ISR (device driver)\n";

            current_time += delays[duration_intr - 1];

            execution += std:: to_string(current_time) + ", " + std:: to_string(execute_IRET_time) + ", END_IO: Return from ISR\n"; 

            current_time += execute_IRET_time; 
        }

        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}
