#define RECORDING "cityhall"
#define RECORDING_TYPE 2 //1 for in vehicle and 2 for on foot.

#include <a_npc>
main(){}
public OnRecordingPlaybackEnd() StartRecordingPlayback(PLAYER_RECORDING_TYPE_ONFOOT, RECORDING);
public OnNPCEnterVehicle(vehicleid, seatid) StartRecordingPlayback(PLAYER_RECORDING_TYPE_ONFOOT, RECORDING);
public OnNPCExitVehicle() StopRecordingPlayback();





