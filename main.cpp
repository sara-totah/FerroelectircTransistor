#include <iostream>
#include <cmath>
//********************** NCFET Equations **********************//

class NCFET {
  private:
    double oxideCapacitance; // oxide capacitance per unit area
    double channelWidth; // width of the channel
    double channelLength; // length of the channel
    double thresholdVoltage; // threshold voltage

    const double ferroelectricAlpha = -1.8 * pow(10,11); //Alpha Cofficient of the ferroelectric cn/F
    const double ferroelectricBeta = 10 * pow(10,22); //Beta Cofficient of the ferroelectric cm^5/F/Coul^2
    const double ferroelectricGamma = 0; //Gamma Cofficicent of the ferroelectric cm^9/F/Coul^4
    const double ferroelectricRho = 9;  //Rho coefficient of the ferroelectric cm - s/F
    const double ferroelectricTfe = 10 * pow(10,-7); //Thickness of the ferroelectric dielectric


    //******************** Cell Nodes ********************//
    double gateVoltage; //input
    const double sourceVoltage = 1; //kept at constant value
    double drainVoltage; //output

    double ferroelectricVoltage;

    // Gate attributes
    double gateCharge;
    const double gateCapacitance = 0.3;
    
    //time step should be taken frm the HSPICE Model
    const int timeStep = 1;


    double oxideVoltage = 0; //equals Vox + Vmos (constants)


  public:
    // Constructor
    NCFET(double Voltage) {
      gateVoltage = Voltage;
      setGateCharge();
      FerroelectricVoltage();
      setThresholdVoltage();
      operation(gateVoltage);
    }


    // Set Threshold Voltage to a constant value
    void setThresholdVoltage() {
      thresholdVoltage = oxideVoltage + ferroelectricVoltage;
    }

    void setGateCharge(){
      gateCharge = gateCapacitance * gateVoltage;
    }

    double getOxideCapacitance() const {
      return oxideCapacitance;
    }

    double getWidth() const {
      return channelWidth;
    }

    double getLength() const {
      return channelLength;
    }

    double getThresholdVoltage() const {
      return thresholdVoltage;
    }


    double getGateVoltage() const {
      return gateVoltage;
    }

    double getChannelWidth() const {
      return channelWidth;
    }

    double getChannelLength() const {
      return channelLength;
    }

    double getDrainVoltage() {
        return drainVoltage;
    }



    void FerroelectricVoltage (){
      ferroelectricVoltage = (2* ferroelectricAlpha * ferroelectricTfe * gateCharge) + (4 * ferroelectricBeta * ferroelectricTfe * pow(gateCharge,3)) + (6 * ferroelectricGamma * ferroelectricTfe * pow(gateCharge,5)) + (ferroelectricRho * ferroelectricTfe * gateCharge /timeStep);
    }

    void operation (double GateVoltage){
      //cutoff Region
      if ((GateVoltage - sourceVoltage < thresholdVoltage)){
        drainVoltage = 0;
      }
      else if ((GateVoltage - sourceVoltage >= thresholdVoltage ) && (drainVoltage < (gateVoltage - thresholdVoltage))){
        drainVoltage = ((((gateVoltage - sourceVoltage) - ((drainVoltage - sourceVoltage)/2)) - thresholdVoltage) * (drainVoltage - sourceVoltage))/(gateVoltage - thresholdVoltage);
      }
      else if (drainVoltage >= (gateVoltage - thresholdVoltage)){
        drainVoltage = pow((gateVoltage - thresholdVoltage),2);
      }
    }
};

class NOT_Gate {
  private:
    NCFET transistor;

  public:
    NOT_Gate(double voltage): transistor(voltage) {}

    bool operation(bool input) {
        transistor.operation(input ? 5.0 : 0.0); // Assume 5V for HIGH, 0V for LOW
        return transistor.getDrainVoltage() < 2.5; // Assume threshold for logical HIGH is 2.5V
    }
};

class NAND_Gate {
  private:
    NCFET transistor1, transistor2;

  public:
    NAND_Gate(double voltage1, double voltage2): transistor1(voltage1), transistor2(voltage2) {}

    bool operation(bool input1, bool input2) {
        transistor1.operation(input1 ? 5.0 : 0.0); // Assume 5V for HIGH, 0V for LOW
        transistor2.operation(input2 ? 5.0 : 0.0); // Assume 5V for HIGH, 0V for LOW
        return !(transistor1.getDrainVoltage() < 2.5 && transistor2.getDrainVoltage() < 2.5); // Assume threshold for logical HIGH is 2.5V
    }
};



int main() {
    NOT_Gate notGate(5.0);
    NAND_Gate nandGate(5.0, 5.0);

    int notResult = notGate.operation(true);  // Expect 0
    int nandResult = nandGate.operation(true, true);  // Expect 0

    std::cout << "NOT gate result: " << notResult << std::endl;
    std::cout << "NAND gate result: " << nandResult << std::endl;

    return 0;
}


