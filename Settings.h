#pragma once
class Settings {
public:
	//behavior
	int TIME_TO_LIVE = 7; //20
	bool INDIVIDUAL_LIFETIME = true; // IMPORTANT
	int TIME_TO_LIVE_FOR_A = 4; //20
	int TIME_TO_LIVE_FOR_B = 4; //20
	int TIME_TO_LIVE_FOR_C = 4; //20
	int TIME_TO_LIVE_FOR_D = 30; //20

	float SPEED_MULTIPLICATION = 3.0f; //3
	int PAUSE_DURATION_AFTER_CREATION = 20; //20

	float VISION_ANGLE = 30.0f; //45
	float VISION_RANGE = 32.0f; //100
	bool INDIVIDUAL_VISION_BEHAVIOR = false;
		float VISION_ANGLE_OF_A_ObJECT_TYPE = 312.0f; //45
		float VISION_RANGE_OF_A_ObJECT_TYPE = 240.0f; //100
			float VISION_ANGLE_OF_B_ObJECT_TYPE = 45.0f; //45
			float VISION_RANGE_OF_B_ObJECT_TYPE = 100.0f; //100
				float VISION_ANGLE_OF_C_ObJECT_TYPE = 20.0f; //45
				float VISION_RANGE_OF_C_ObJECT_TYPE = 60.0f; //100
					float VISION_ANGLE_OF_D_ObJECT_TYPE = 45.0f; //45
					float VISION_RANGE_OF_D_ObJECT_TYPE = 100.0f; //100

	//simulation settings
	int NUMBER_OF_SHAPE_PER_TYPE = 30; //20
	float NUMBER_OF_FRAME_RATE_PER_SECONDS = 60; //60
	int MAX_OBJECTS_PER_TYPE_VAR = 60; //300
	int NUMBER_OF_ITERATIONS_BEFORE_DISPLAYING_STATISTICS = 60; //60
	bool SAVE_DATE_AT_THE_END = true;
	
	//objects
	static constexpr float TYPE_A_OBJECT_RADIUS = 3; //5
	static constexpr float TYPE_B_OBJECT_RADIUS = 3; //7
	static constexpr float TYPE_C_OBJECT_RADIUS = 3; //6
	static constexpr float TYPE_D_OBJECT_RADIUS = 3; //9
	bool APPEND_OBJECTS_TYPE_A = true; //true
	bool APPEND_OBJECTS_TYPE_B = true; //true
	bool APPEND_OBJECTS_TYPE_C = true; //true
	bool APPEND_OBJECTS_TYPE_D = true; //true
	
	//survivale mode
	bool SMART_SURVIVAL_INSTINCT_MODE = true; //true
	const float HUNT_SPEED_VALUE = 5.0f; //3.0f
	const float ESCAPE_SPEED_VALUE = 3.0f; //3.0f
	bool IS_BIND_MODE = true; //true

};