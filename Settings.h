#pragma once
class Settings {
public:
	int time_To_Live = 7;
	int number_Of_Shape_Per_Type = 20;
	float vision_Angle = 45.0f;
	float vision_Range = 100.0f;
	float speed_Multiplication = 3.0f;
	float frame_Rate_Number = 60;
	int MAX_OBJECTS_PER_TYPE_VAR = 300;
	int PAUSE_DURATION_AFTER_CREATION = 20;
	int NUMBER_OF_ITERATIONS_BEFORE_DISPLAYING_STATISTICS = 60;
};