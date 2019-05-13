#include "rooms.h"



/*
 * Room::get_name
 *
 * This function returns the name of the room.
 *
 * @Return: char* containing the room currently looking at.
 */
char* Room::get_name()
{
	return rname;
}

/*
 * Room::device_check
 *
 * This function checks to see if a device by the name provided already exists in the room
 *
 * @Param: name The name of the device trying to be added
 *
 * @Return: True if device is not in array, False if device is in array
 */
bool Room::device_check(char* name)
{
	for(int i = 0;i<num_devices;i++)
	{
		if(devices[i] == name)
			return false;
	}
	return true;
}


/*
 * Room::addDevicetoRoom
 *
 * This functions attempts to add the name of a device to a certain room.
 *
 * @Param: name the name of the device to be added to the room.
 *
 * @Return: True if device name was successfully added to the list, False if adding failed
 */
bool Room::addDevicetoRoom(char* name)
{
	if(!device_check(name))
	{
		return false; //device with that name already exists in room
	}
	if(num_devices == 100)
	{
		return false; // exceeded max number of devices in a room
	}

	devices[num_devices] = name;
	num_devices++;
}

