#pragma once

#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include "windows.h"

using namespace std;

class PIDController {
private:
	ofstream* loggerObj;
	long double timestamp;
	double pGain, iGain, dGain;
	double prevProportionalValue;
	double integralValue, proportionalValue, differentialValue;
	double targetValue, measuredValue, steeringValue;
	std::chrono::steady_clock::time_point lastTime, currentTime, startTime;
	vector<double> vIntegralValues, vProportionalValues, vDifferentialValues, vMeasuredValues, vSteeringValues;


public:

	PIDController(double pGain, double iGain, double dGain);

	double calculateCurrentSteeringValue(double targetValue, double measuredValue);
	void logger();
	void getAndSetTimeStamp();
	void initLogger();
	vector<double> getProportionalValues() { return vProportionalValues; }
	vector<double> getIntegralValues() { return vIntegralValues; }
	vector<double> getDifferentialValues() { return vDifferentialValues; }
	vector<double> getMeasuredValues() { return vMeasuredValues; }
	vector<double> getSteeringValues() { return vSteeringValues; }

};