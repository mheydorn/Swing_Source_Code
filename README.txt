README

Instructions:
	1. The send.ino and recieve.ino files should be written to the respective arduinos (send to the one that connects to the PC and recieve to the one on the camera rotator). Use the arduino programming tool for this. Note that this is not neccesary unless the arduinos have been reprogrammed. 

	2. Install qt creator
	
	3. Open MotorControl.pro with qt creator and press play


Special Notes:
	1. The speed on the motor control GUI is not a speed but a delay betweeen microsteps (in micro seconds). A value of 200 is about as fast as it can go without skipping. It gets linearly slower as you increase the speed setting (400 is twice as slow as 200).

	2. This has been tested to work in bittern running qt creator 3.01
