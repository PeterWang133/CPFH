/* C++ Homework Final Part 3
* H.Wang
* Examine the Data Acquisition System
* Investigates the affect of heat transfer coefficient on the system
*/

#include <iostream>
# include <cmath>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

float RateofChange (float, float, float, float, float, float);

// MAIN PROGRAM
int main() {
    float T0; // Initial temperature of the thermocouple
    float Tl; // Constant temperature of the liquid
    float h; // Heat Transfer coefficient
    float rho; // Sphere density
    float c; // Material specific heat
    float r; // Sphere Radius
    float dt; // Time step
    ofstream results; // Used for writing data
    // SETS initial heat transfer coefficient to be 300
    h = 300;
    // OPENS data file for writing in data
    results.open("CPFH3_HWang.txt",ios::out);
    // DO
    do {
        // SETS all the initial condition to the same user input from Part 1
        T0 = 100;
        Tl = 25;
        rho = 8922;
        c = 287;
        r = 0.0005;
        dt = 0.001;
        float Tc = T0; // Current Temperature (Will update each loop)
        float tc = 0; // Current time (Will update each loop)
        // DO
        do {
            float k;
            // Calculates rate of change by using function RateofChange()
            k = RateofChange(r, rho, h, Tl, Tc, c);
            // Calculates the current temperature based on the value of rate of change
            Tc = Tc + k * dt;
            // Update the time
            tc = tc + dt;
        // WHILE current temperature is not within 0.1 degree of the constant temperature
        } while (Tc > Tl + 0.1);
        // WRITES the data into the data file – the time taken to reach liquid temperature
        // state and the related coefficient
        results<<tc<<"\t"<<h<<endl;
        // INCREASE the heat transfer coefficient by an increment of 25
        h = h + 25;
        cout << "Time to steady state temperature: " << tc << endl;
    // WHILE heat transfer coefficient is less than 1001
    } while (h < 1001);
    // CLOSE data file
    results.close();
// END of PROGRAM
}

// FUNCTION RateofChange
float RateofChange(float rad, float D, float htc, float T1, float T2, float sh)
{
    float Roc;
    float m, As;
    float pi = 3.1415926;
    // CALCULATES the area
    As = 4.0 * pi * pow(rad, 2);
    // CALCULATES the mass
    m = (4.0 / 3.0) * pi * D * pow(rad, 3);
    // CALCULATES the rate of change of temperature
    Roc = (htc * As * (T1 - T2)) / (m * sh); // Ti/ti
    // RETURN Rate of Change value
    return Roc;
// END FUNCTION
}