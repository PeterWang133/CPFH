/* C++ Homework Final Part 1
* H.Wang
* Development of the Algorithm
* Calculates the rate of change of the temperature based on given value
*/

#include <iostream>
# include <cmath>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

float RateofChange (float, float, float, float, float, float);

int main() {
    // Intro
    cout<<"This program calculates the rate of change of the temperature and time taken to reach the constant temperature state."<<endl;
    // Take as user inputs eventually
    float T0; // Initial temperature of the thermocouple
    float Tl; // Constant temperature of the liquid
    float h; // Heat Transfer coefficient
    float rho; // Sphere density
    float c; // Material specific heat
    float r; // Sphere Radius
    float dt; // Time step
    float m;
    ofstream results;

        //OPENS data file for writing in data
        results.open("CPFH1_HWang", ios::out);
        // ASKS user for initial temperature
        cout << "Enter Value of initial temperature" << endl;
        cin >> T0;
        // ASKS user for constant temperature (or liquid temperature)
        cout << "Enter Value of constant temperature" << endl;
        cin >> Tl;
        // ASKS user for heat transfer coefficient
        cout << "Enter Value of heat transfer coefficient" << endl;
        cin >> h;
        // ASKS user for sphere density
        cout << "Enter Value of sphere density" << endl;
        cin >> rho;
        // ASKS user for material specific heat
        cout << "Enter Value of material specific heat" << endl;
        cin >> c;
        // ASKS user for sphere radius
        cout << "Enter Value of sphere radius" << endl;
        cin >> r;
        // ASKS user for time interval
        cout << "Enter Value of time interval." << endl;
        cin >> dt;
        float Tc = T0; // Current Temperature (Will update each loop)
        float tc = 0; // Current time (Will update each loop)
        cout << "Time" << '\t' << "Temperature" << endl;
        // DO
        do {
            float k;
            // Calculates rate of change by using function RateofChange()
            k = RateofChange(r, rho, h, Tl, Tc, c);
            // Calculates the current temperature based on the value of rate of change
            Tc = Tc + k * dt;

            // Update the time
            tc = tc + dt;
            // PRINTS results
            cout << tc << '\t' << Tc << endl;
            // Writes the time and temperature to the data file
            results << tc << '\t' << Tc << endl;
        // WHILE current temperature is not within 0.1 degree of the constant temperature
        } while (Tc > Tl + 0.1);
        // CLOSE data file
        results.close();
        // PRINTS result
        cout << "Time to steady state temperature: " << tc<<endl;
// END of PROGRAM
}

// Determine the Rate of Change
// Assignment Requirement for this to become a function
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