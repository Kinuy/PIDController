#include "PIDController.h"

PIDController::PIDController(double pGain, double iGain, double dGain) : pGain(pGain), iGain(iGain),dGain(dGain),prevProportionalValue(0.0),integralValue(0.0)
{
	lastTime = std::chrono::steady_clock::now();
	startTime = std::chrono::steady_clock::now();
}

double PIDController::calculateCurrentSteeringValue(double targetValue, double measuredValue)
{
	this->targetValue = targetValue;
	this->measuredValue = measuredValue;
	proportionalValue = this->targetValue - this->measuredValue;

	currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsedTime = currentTime - lastTime;
	double deltaTime = elapsedTime.count();
	
	integralValue += proportionalValue * deltaTime;
	differentialValue = (proportionalValue - prevProportionalValue) / deltaTime;

	steeringValue = (pGain * proportionalValue) + (iGain * integralValue) + (dGain * differentialValue);

	prevProportionalValue = proportionalValue;
	lastTime = currentTime;

	vProportionalValues.push_back(proportionalValue);
	vIntegralValues.push_back(integralValue);
	vDifferentialValues.push_back(differentialValue);
	vMeasuredValues.push_back(measuredValue);
	vSteeringValues.push_back(steeringValue);

	return steeringValue;
}

void PIDController::logger()
{
	getAndSetTimeStamp();
	*loggerObj
		<< "UTC Time:" << lastTime.time_since_epoch().count()<<" , "
		<< "Target Value:" << targetValue << " , "
		<< "MeasuredValue Value:" << measuredValue << " , "
		<< "Steering Value:" << steeringValue << " , "
		<< "Proportional Value:" << steeringValue << " , "
		<< "Integral Value:" << steeringValue << " , "
		<< "Differential Value:" << steeringValue << endl;
}

void PIDController::initLogger()
{
	loggerObj = new ofstream("PIDDataLogger.txt");
	if (!loggerObj)
	{
		cout << "The log could not be opened\n";
	}
	else {
		cout << "The log has been initialized successfully\n";
	}
}

void PIDController::getAndSetTimeStamp()
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	this->timestamp - st.wSecond;
}