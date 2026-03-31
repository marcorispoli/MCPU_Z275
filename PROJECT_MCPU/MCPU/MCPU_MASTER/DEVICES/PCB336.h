#pragma once
#include "CanDeviceProtocol.h"

/// <summary>
/// \defgroup PCB304_Module PCB304 Module: Grid device module controller
/// \ingroup CanDevice_Module  
/// 
/// \todo Magnifier device: implementare il protocollo di gestione dell'ingranditore
/// 
/// \todo Implementare la nuova gestione della luce della biopsia
/// 
/// </summary>
ref class PCB336 : public CanDeviceProtocol
{
public:
	/// <summary>
	/// This class implement the protocol data structure as described in the protocol specification.
	/// </summary>
	ref class ProtocolStructure {
	public:

		ref class StatusRegister {
		public:

			enum class register_index {
				STATUS_REGISTER = 0,	//!> This is the Status register with the Grid internal status				
				NUM_REGISTER
			};

			static bool decodeStatusRegister(Register^ sys) {
				if (sys == nullptr) return false;
				
				//inField =				sys->d0 & 0x1;				
				return true;
			}

			Register^ encodeStatusRegister(void) {

				// Creates a register with all bytes set to 0
				Register^ out = gcnew Register;

				//if (inField) out->d0 |= 0x1;
				return out;
			}

			// Declare the status variables here
			//static bool inField = false; 
		};


		ref class DataRegister {
		public:

			enum class register_index {
				DATA_REGISTER = 0,	//!> This is the Display Data register index				
				NUM_REGISTER
			};

			Register^ encodeDataRegister(void) {

				// Creates a register with all bytes set to 0
				Register^ out = gcnew Register;

				//if (display_on) out->d0 |= 0x1;
			
				return out;
			}

			static bool decodeDataRegister(Register^ sys) {
				if (sys == nullptr) return false;

				// D0
				//display_on = sys->d0 & 0x1;
				return true;
			}

			// Declare the data variables here
			//static bool display_on = false;
			

		};

		ref class ParameterRegister {
		public:
			enum class register_index {
				PARAM_REGISTER = 0,		
				NUM_REGISTER
			};
			
		};

		ref class Commands {
		public:
			enum class command_index {
				ABORT_COMMAND = 0, //!< Abort Command (mandatory as for device protocol)
					
			};

			// Encodes the commands here
			/*
			CanDeviceCommand^ encodeSetInOutCommand(bool InField) {
				if(InField)	return gcnew CanDeviceCommand((unsigned char)command_index::SET_INOUT, 1, 0, 0, 0);
				else	return gcnew CanDeviceCommand((unsigned char)command_index::SET_INOUT, 2, 0, 0, 0);
			}
			*/

		};

		static StatusRegister status_register;
		static DataRegister data_register;
		static ParameterRegister parameter_register;
		static Commands command;
	};

	PCB336() : CanDeviceProtocol(0x14, L"Filament")
	{
		// Data initializtion
		
	}
	static PCB336^ device = gcnew PCB336();

	literal int max_num_error_resets = 5; //!< Maximum number of attempts to reset a pending error condition

protected: 
	void runningLoop(void) override;
	

private:
	static ProtocolStructure protocol; // This is the structure with the Status register info
	static int  error_count = 0;

	enum class command_request_index {
		NO_COMMAND = 0,
	};

	static command_request_index command_request = command_request_index::NO_COMMAND;
	static bool command_busy = false;
};

