#pragma once

#include <chrono>
#include <iostream>
#include <fstream>
#include "windows.h"

using namespace std;

class PIDController {
private:
	ofstream* loggerObj;
	long double timestamp;
	double pGain, iGain, dGain;
	double prevProportionalValue;
	double integralValue, proportionalValue, derivativeValue;
	double targetValue, measuredValue, steeringValue;
	std::chrono::steady_clock::time_point lastTime, currentTime, startTime;


public:

	PIDController(double pGain, double iGain, double dGain);

	double calculateCurrentSteeringValue(double targetValue, double measuredValue);
	void logger();
	void getAndSetTimeStamp();
	void initLogger();

};