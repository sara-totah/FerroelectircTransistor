#include <iostream>

#include <cmath>
//********************** NCFET Equations **********************//

using namespace std;

class NCFET {

    const double ferroelectricAlpha = -1.8 * pow(10,11); //Alpha Cofficient of the ferroelectric cn/F
    const double ferroelectricBeta = 5.8 * pow(10,22); //Beta Cofficient of the ferroelectric cm^5/F/Coul^2
    const double ferroelectricGamma = 0; //Gamma Cofficicent of the ferroelectric cm^9/F/Coul^4
    const double ferroelectricRho = 9;  //Rho coefficient of the ferroelectric cm - s/F
    const double ferroelectricTfe = 10 * pow(10,-7); //Thickness of the ferroelectric dielectric

    double thresholdVoltage; // threshold voltage
    double ferroelectricVoltage;
    double oxideVoltage = 0; //equals Vox + Vmos (constants)

    double gateVoltage; //input
    const double sourceVoltage = 1; //kept at constant value
    double drainVoltage; //output

    // Gate attributes
    double gateCharge;
    const double gateCapacitance = 0.3;

    //time step should be taken frm the HSPICE Model
    const int timeStep = 1;

public:
    void make(double Voltage)
    {
        this->gateVoltage = Voltage;
        setGateCharge();
        FerroelectricVoltage();
        setThresholdVoltage();
        operation(gateVoltage);
    }

    // Set Threshold Voltage to a constant value
    void setThresholdVoltage() {
        //thresholdVoltage = oxideVoltage + ferroelectricVoltage;
        thresholdVoltage = 0.32; //technology node 45nm from citation number 10, NC model paper
    }

    void setGateCharge(){
        this->gateCharge = this->gateCapacitance * this->gateVoltage;
    }

    double getThresholdVoltage() const {
        return thresholdVoltage;
    }


    double getGateVoltage() const {
        return gateVoltage;
    }

    double getDrainVoltage() {
        return drainVoltage;
    }

    double getGateCharge(){
        return gateCharge;
    }

    void FerroelectricVoltage (){
        this->ferroelectricVoltage = (2* ferroelectricAlpha * ferroelectricTfe * gateCharge) + (4 * ferroelectricBeta * ferroelectricTfe * pow(gateCharge,3)) + (6 * ferroelectricGamma * ferroelectricTfe * pow(gateCharge,5)) + (ferroelectricRho * ferroelectricTfe * gateCharge /timeStep);
    }

    void operation (double GateVoltage){
        //cutoff Region
        if ((GateVoltage - sourceVoltage < thresholdVoltage)){
            this->drainVoltage = 0;
        }
        else if ((GateVoltage - sourceVoltage >= thresholdVoltage ) && (drainVoltage < (gateVoltage - thresholdVoltage))){
            this->drainVoltage = ((((gateVoltage - sourceVoltage) - ((drainVoltage - sourceVoltage)/2)) - thresholdVoltage) * (drainVoltage - sourceVoltage))/(gateVoltage - thresholdVoltage);
        }
        else if (drainVoltage >= (gateVoltage - thresholdVoltage)){
            this->drainVoltage = pow((gateVoltage - thresholdVoltage),2);
        }
    }
};

int NOT_Gate(NCFET transistor);
int main(){

    NCFET transistor1, transistor2;
    transistor1.make(100.0);
    transistor2.make(0.0);

    std::cout << "NOT gate result for input 5: " << NOT_Gate(transistor1) << std::endl;
    std::cout << "NOT gate result for input 0: " << NOT_Gate(transistor2) << std::endl;


}

int NOT_Gate(NCFET transistor){
    return transistor.getDrainVoltage() < 1;
}

