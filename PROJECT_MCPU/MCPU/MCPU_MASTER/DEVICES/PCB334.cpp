
#include "PCB334.h"
#include "Notify.h"
#include <thread>
#include "gantry_global_status.h"

void PCB334::runningLoop(void) {
    static bool commerr = false;


    // Test the communication status
    if (commerr != isCommunicationError()) {
        commerr = isCommunicationError();
        if (isCommunicationError()) {
            Notify::activate(Notify::messages::ERROR_PCB334_COMMUNICATION_ERROR);
        }
        else {
            Notify::deactivate(Notify::messages::ERROR_PCB334_COMMUNICATION_ERROR);
        }
        error_count = 0;
    }

    // In Demo mode Only the Display works
    if (Gantry::isOperatingDemo()) {
        return;
    }

    // Always reads the grid Status register
    protocol.status_register.decodeStatusRegister(readStatusRegister((unsigned char)ProtocolStructure::StatusRegister::register_index::STATUS_REGISTER));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

        
    writeDataRegister((unsigned char)ProtocolStructure::DataRegister::register_index::DATA_REGISTER, protocol.data_register.encodeDataRegister());
    std::this_thread::sleep_for(std::chrono::milliseconds(10));


    // Command execution request here: the commands can be executed only if the Auto In/Out is disabled
    // The test commands are executed with the with delayed protocol command. So if a command complete is detected 
    // the previous in/out status shall be restored
    if (!device->isCommandCompleted()) return;
    command_busy = false;

    switch (command_request) {
    case command_request_index::NO_COMMAND:
        break;

    default:
        command_request = command_request_index::NO_COMMAND;
        command_busy = false;
        break;

    }


    return;
}

