#define RECORDING "train_by_vizor" //Имя вашего файла записи без расширения
 #define RECORDING_TYPE 1 //1 если путь записан в машине и 2 если путь записан пешком
 #include <a_npc>

 main(){}

 public OnRecordingPlaybackEnd() StartRecordingPlayback(RECORDING_TYPE, RECORDING);
 #if RECORDING_TYPE == 1
 public OnNPCEnterVehicle(vehicleid, seatid) StartRecordingPlayback(RECORDING_TYPE, RECORDING);
 public OnNPCExitVehicle() StopRecordingPlayback();
 #else
 public OnNPCSpawn() StartRecordingPlayback(RECORDING_TYPE, RECORDING); .
 #endif
