class FeFET {
    
private:
    // Transistor Characteristics
    double Me;          // Mobility of Electron
    double Cox;         // Gate Oxide Capacitance per unit area
    double W_gate;      // Gate Junction Width
    double L_gate;      // Gate Junction Length
    double Vgs;         // Gate Source Voltage
    double Vth;         // Threshold Voltage
    double Vds;         // Drain Source Saturation Voltage

    // Ferroelectric Layer Characteristics
    double Q_fe;        // Charge stored in the ferroelectric layer
    double A_fe;        // Area of the ferroelectric layer
    double perm_fe;     // Permittivity of ferroelectric material
    double d_fe;        // Thickness of the ferroelectric layer

    // General Characteristics needed to represent the Ferroelectric Field Effect Transistor (FeFET)
    double Id;          // Drain Current
    double P_fe;        // Polarization of the Ferroelectric Layer
    double C_fe;        // Capacitance of the Ferroelectric Layer
    double V_fe;        // Voltage across the Ferroelectric Layer

public:
    FeFET(double Me, double Cox, double W_gate, double L_gate, double Vgs, double Vth, double Vds,
          double Q_fe, double A_fe, double perm_fe, double d_fe)

        : Me(Me), Cox(Cox), W_gate(W_gate), L_gate(L_gate), Vgs(Vgs), Vth(Vth), Vds(Vds),
          Q_fe(Q_fe), A_fe(A_fe), perm_fe(perm_fe), d_fe(d_fe) {}

    void setDrainVoltage(double voltage) {
        Vds = voltage;
    }

    void setGateSourceVoltage(double voltage) {
        Vgs = voltage;
    }

    double getDrainCurrent() {
        Id = Me * Cox * (W_gate / L_gate) * ((Vgs - Vth) * Vds - 0.5 * Vds * Vds);
        return Id;
    }

    double getFerroelectricPolarization() {
        P_fe = Q_fe / A_fe;
        return P_fe;
    }

    double getFerroelectricCapacitance() {
        C_fe = perm_fe * A_fe / d_fe;
        return C_fe;
    }

    double getFerroelectricVoltage() {
        V_fe = Q_fe / C_fe;
        return V_fe;
    }
};
