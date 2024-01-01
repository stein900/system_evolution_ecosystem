#pragma once
class Settings {
public:
	//behavior
	int TIME_TO_LIVE = 12; //20
	int TIME_TO_LIVE_FOR_A = 25; //20
	int TIME_TO_LIVE_FOR_B = 12; //20
	int TIME_TO_LIVE_FOR_C = 6; //20
	int TIME_TO_LIVE_FOR_D = 12; //20
	float vision_Angle = 45.0f; //45
	float vision_Range = 100.0f; //100
	float speed_Multiplication = 3.0f; //3
	int PAUSE_DURATION_AFTER_CREATION = 20; //20

	//simulation settings
	int number_Of_Shape_Per_Type = 8; //20
	float frame_Rate_Number = 60; //60
	int MAX_OBJECTS_PER_TYPE_VAR = 60; //300
	int NUMBER_OF_ITERATIONS_BEFORE_DISPLAYING_STATISTICS = 60; //60
	
	//objects
	static constexpr float TYPE_A_OBJECT_RADIUS = 5; //5
	static constexpr float TYPE_B_OBJECT_RADIUS = 7; //7
	static constexpr float TYPE_C_OBJECT_RADIUS = 6; //6
	static constexpr float TYPE_D_OBJECT_RADIUS = 9; //9
	bool APPEND_OBJECTS_TYPE_A = true; //true
	bool APPEND_OBJECTS_TYPE_B = true; //true
	bool APPEND_OBJECTS_TYPE_C = true; //true
	bool APPEND_OBJECTS_TYPE_D = true; //true
	
	//survivale mode
	bool SMART_SURVIVAL_INSTINCT_MODE = true; //true
	const float HUNT_SPEED_VALUE = 3.0f; //3.0f
	const float ESCAPE_SPEED_VALUE = 3.0f; //3.0f
	bool IS_BIND_MODE = true; //true

};