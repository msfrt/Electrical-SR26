/******************************************************************************
    
    This file was generated automatically from a DBC file by the dbctocpp 
    utility, which is part of the StateCAN library, 
    a component of SR-Libraries.

    https://github.com/msfrt/SR-Libraries
    
******************************************************************************/

#ifndef ELCON_HPP
#define ELCON_HPP

#include <FlexCAN_T4.h>
#include <StateCAN.h>

// Message: Status [0x18ff50e5]
StateSignal OutputVoltage(16, false, 10, 0.0, 0, 0, 0.0, -1, 419385573);
StateSignal OutputCurrent(16, false, 10, 0.0, 0, 0, 0.0, -1, 419385573);
StateSignal HWStatus(1, false, 1, 0.0, 0, 0, 0.0, -1, 419385573);
StateSignal Temperature(1, false, 1, 0.0, 0, 0, 0.0, -1, 419385573);
StateSignal InputVoltage(1, false, 1, 0.0, 0, 0, 0.0, -1, 419385573);
StateSignal State(1, false, 1, 0.0, 0, 0, 0.0, -1, 419385573);
StateSignal CommunicationState(1, false, 1, 0.0, 0, 0, 0.0, -1, 419385573);

// Message: ChargingLimits [0x1806e5f4]
StateSignal MaxVoltage(16, false, 10, 0.0, 0, 0, 0.0, -1, 403105268);
StateSignal MaxCurrent(16, false, 10, 0.0, 0, 0, 0.0, -1, 403105268);
StateSignal Control(8, false, 1, 0.0, 0, 0, 0.0, -1, 403105268);




/************************************************************************************
    
    Incoming CAN frame decoding functions

************************************************************************************/


/*
 * Decode a CAN frame for the message Status
 * \param imsg A reference to the incoming CAN message frame
 */
void read_Status(const CAN_message_t &imsg) {

	OutputVoltage.set_can_value((imsg.buf[1]) | (imsg.buf[0] << 8));
	OutputCurrent.set_can_value((imsg.buf[3]) | (imsg.buf[2] << 8));
	HWStatus.set_can_value(((imsg.buf[4] & 0b00000001)));
	Temperature.set_can_value((((imsg.buf[4] & 0b00000010)) >> 1));
	InputVoltage.set_can_value((((imsg.buf[4] & 0b00000100)) >> 2));
	State.set_can_value((((imsg.buf[4] & 0b00001000)) >> 3));
	CommunicationState.set_can_value((((imsg.buf[4] & 0b00010000)) >> 4));

}

/*
 * Decode a CAN frame for the message ChargingLimits
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ChargingLimits(const CAN_message_t &imsg) {

	MaxVoltage.set_can_value((imsg.buf[1]) | (imsg.buf[0] << 8));
	MaxCurrent.set_can_value((imsg.buf[3]) | (imsg.buf[2] << 8));
	Control.set_can_value((imsg.buf[4]));

}




/************************************************************************************

    Distribute incoming messages to the correct decoding functions

************************************************************************************/


/*
 * Decode a CAN message for the bus captured in elcon.dbc.
 * To more efficiently allocate microcontroller resources, simply comment
 * out unnecessary messages that do not need to be decoded.
 * \param imsg A reference to the incoming CAN frame
 */
void decode_elcon(const CAN_message_t &imsg) {

	switch (imsg.id) {

		case 419385573:
			read_Status(imsg);
			break;

		case 403105268:
			read_ChargingLimits(imsg);
			break;

	}
}


#endif
