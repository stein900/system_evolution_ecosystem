#pragma once
class Settings {
public:
	int time_To_Live = 12; //20
	int number_Of_Shape_Per_Type = 8; //20
	float vision_Angle = 45.0f; //45
	float vision_Range = 20.0f; //100
	float speed_Multiplication = 35.0f; //3
	float frame_Rate_Number = 60; //60
	int MAX_OBJECTS_PER_TYPE_VAR = 300; //300
	int PAUSE_DURATION_AFTER_CREATION = 20; //20
	int NUMBER_OF_ITERATIONS_BEFORE_DISPLAYING_STATISTICS = 60; //60
	static constexpr float TYPE_A_OBJECT_RADIUS = 5; //5
	static constexpr float TYPE_B_OBJECT_RADIUS = 7; //7
	static constexpr float TYPE_C_OBJECT_RADIUS = 6; //6
	static constexpr float TYPE_D_OBJECT_RADIUS = 9; //9
	bool APPEND_OBJECTS_TYPE_A = true;
	bool APPEND_OBJECTS_TYPE_B = true;
	bool APPEND_OBJECTS_TYPE_C = true;
	bool APPEND_OBJECTS_TYPE_D = true;
};