#include <iostream>
#include "Ferroelectric_Transistor.cpp"

int main() {
    // Set up FeFET with initial parameters
    double Me = 0.1;
    double Cox = 1e-6;
    double W_gate = 1e-4;
    double L_gate = 1e-4;
    double Vth = 1.0;
    double Qfe = 1e-9;
    double A_fe = 1e-8;
    double prem_fe = 1e-8;
    double d_fe = 1e-7;
    FeFET myFeFET(Me, Cox, W_gate, L_gate, 0.0, Vth, 0.0, Qfe, A_fe, prem_fe, d_fe);

    // Set input voltages
    double Vgs = 1.5;
    double Vds = 1.0;
    myFeFET.setGateSourceVoltage(Vgs);
    myFeFET.setDrainVoltage(Vds);

    // Calculate and output results
    std::cout << "Input voltages: Vgs = " << Vgs << " V, Vds = " << Vds << " V\n";
    std::cout << "Drain current: " << myFeFET.getDrainCurrent() << " A\n";
    std::cout << "Ferroelectric polarization: " << myFeFET.getFerroelectricPolarization() << " C/m^2\n";
    std::cout << "Ferroelectric capacitance: " << myFeFET.getFerroelectricCapacitance() << " F\n";
    std::cout << "Ferroelectric voltage: " << myFeFET.getFerroelectricVoltage() << " V\n";

    return 0;
}
