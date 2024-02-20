/* C++ Homework Final Part 2
* H.Wang
* Test Cases
* Investigates the effect of the radius change to the system
*/

#include <iostream>
# include <cmath>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>
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
    float t;
    float lastTime = 0;
    float deltaT;
    ofstream results_radius; // Used for writing results of radius
    ofstream results_transient; // Used for writing results of transient curve
    ifstream infile; // Used for reading files
    ifstream infile2; // Used for reading and writing files into array
    int count = 0; // Used for counting the number of materials needed for computation
    // Lists of filename for storing data of radius for each material
    string filename_radius[] = {"changeofRadius", "changeofRadius2", "changeofRadius3", "changeofRadius4"};
    // Lists of filename for storing data of temperature change with min radius for each material
    string filename_transient_minRadius[] = {"transientResponse", "transientResponse2", "transientResponse3",
                                             "transientResponse4"};
    // Lists of filename for storing data of temperature change with mid radius for each material
    string filename_transient_midRadius[] = {"transientResponse5", "transientResponse6", "transientResponse7",
                                             "transientResponse8"};
    // Lists of filename for storing data of temperature change with max radius for each material
    string filename_transient_maxRadius[] = {"transientResponse9", "transientResponse10", "transientResponse11",
                                             "transientResponse12"};
    // OPENS file that contains information about the properties of the four materials
    infile.open("propertiesTable_HWang.txt", ios::in);
    infile2.open("propertiesTable_HWang.txt", ios::in);

    // CHECKS IF file exists
    // IF File does not exist
    if (!infile||!infile2) {
        // Prints information that notices the user
        // PRINTS File could not be found
        cout << "Unable to open sample.txt file" << endl;
        cout << "Program to force exit...\n";
        return (1);
    // ENDIF
    }

    // WHILE end of file is not reached
    while (!infile.eof()) {
        infile >> c;
        infile >> rho;
        // COUNTS the number of rows of the file
        count++;
    // ENDWHILE
    }

    // CREATES array with the size of the row of the file
    float RHO[count];
    float C[count];

    // FOR
    for (int i = 0; i < count; i++) {
        // READS the properties of the material into the array
        infile2 >> C[i];
        infile2 >> RHO[i];
    // ENDFOR
    }

    float Tc; // Current Temperature (Will update each loop)
    float tc; // Current time (Will update each loop)

    // FOR
    for (int i = 0; i < count; i++) {
        // OPEN a text file to write in the data
        results_radius.open(filename_radius[i].c_str(), ios::out);
        // SETS initial radius to 0.3 mm
        r = 0.3;
        // DO
        do {
            // SETS initial condition
            T0 = 120;
            h = 1200;
            dt = 0.01;
            Tc = T0; // Current Temperature (Will update each loop)
            tc = 0; // Current time (Will update each loop)
            Tl = 30;
            // DO
            do {
                // Starts Timing (program processing time)
                t = clock() / CLOCKS_PER_SEC;
                float k;
                // CALCULATES the rate of change by using the function RateofChange
                k = RateofChange(r, RHO[i], h, Tl, Tc, C[i]);
                // UPDATES the temperature reading
                Tc = Tc + k * dt;
                // Update the time
                tc = tc + dt;
                // Calculates the program processing time
                deltaT = t - lastTime;
            // WHILE current temperature is greater than 0.1 degrees of the liquid temperature
            // AND PROGRAM processing time is less than 5 seconds
            } while (Tc > Tl + 0.1 && deltaT < 5);
            // STORES the last second of processing time
            lastTime = t;
            cout<<"Radius: "<<r<<endl;
            cout<<"Time: "<<tc<<endl;
            // WRITES the radius and the time taken to reach liquid temperature state into the opened data file
            results_radius<<tc<<"\t"<<r<<endl;
            // Increases the radius value by 0.05
            r=r+0.05;
        // WHILE PROCESSING TIME is less than 5 seconds
        }while(deltaT<5);
        // Indicates the computation has ENDED by printing “end”
        cout<<"end"<<endl;
        // CLOSE data file
        results_radius.close();
    } // ENDFOR
    // CLOSES File
    infile.close();
    infile2.close();
    // Create an array of radius value
    // FOR
    for (int i = 0; i < count; i++) {
        // OPENS data file that recorded radius
        infile.open(filename_radius[i].c_str(),ios::in);
        infile2.open(filename_radius[i].c_str(),ios::in);
        int num = 0;
        float t;
        float radius;
        float min;
        float mid;
        float max;
        // FINDS how many rows are in the data file
        while(!infile.eof()){
            infile>>t;
            infile>>radius;
            num++;
        }
        num=num-2;
        infile.close();
        float T[num];
        float Radius[num];
        // Writes the radius value into the array (the last row of the data
        // file was omitted on purpose because the processing time for the
        // last row of tje data file was 5 seconds, which means the result is invalid)
        for(int i=0;i<num;i++){
            infile2>>T[i];
            infile2>>Radius[i];
        }
        infile2.close();

        // Find the minimum radius value
        min=Radius[0];
        // Find the maximum radius value
        max=Radius[num-1];
        // Determine if the number of row of the data file is even or odd
        int remain=num%2;
        // IF the row value is EVEN
        if(remain==0){
            // Take the average value of the two data that are in the middle of the row
            mid=(Radius[(num/2)-1]+Radius[num/2])/2;
        }
        // ELSE
        else{
            // Take the value that lies exactly at the middle of the row
            mid=Radius[(num+1)/2];
        // ENDIF
        }
        // Write data with minimum radius
        // SETS initial conditions
        T0 = 120;
        h = 1200;
        dt = 0.01;
        Tc = T0; // Current Temperature (Will update each loop)
        tc = 0; // Current time (Will update each loop)
        Tl = 30;
        r=min;

        // OPENS the data file for recording temperature change with min radius value
        results_transient.open(filename_transient_minRadius[i].c_str(),ios::out);

        // COMPUTES the temperature change with min radius value
        //DO
        do {
            float k;
            // Calculates rate of change by using function RateofChange()
            k = RateofChange(r, RHO[i], h, Tl, Tc, C[i]);
            // Calculates the current temperature based on the value of rate of change
            Tc = Tc + k * dt;
            // Update the time
            tc = tc + dt;
            // Writes the time and temperature to the data file
            results_transient<<tc<<'\t'<<Tc<<endl;
        // WHILE Current temperature is greater than 0.1 degrees of the Liquid Temperature
        } while (Tc > Tl + 0.1);
        // CLOSES data file for recording temperature change with min radius value
        results_transient.close();

        // Write data with middle value of radius
        // SETS initial conditions
        T0 = 120;
        h = 1200;
        dt = 0.01;
        Tc = T0; // Current Temperature (Will update each loop)
        tc = 0; // Current time (Will update each loop)
        Tl = 30;
        r=mid;
        // OPENS the data file for recording temperature change with mid radius value
        results_transient.open(filename_transient_midRadius[i].c_str(),ios::out);

        // COMPUTES the temperature change with mid radius value
        // DO
        do {
            float k;
            // Calculates rate of change by using function RateofChange()
            k = RateofChange(r, RHO[i], h, Tl, Tc, C[i]);
            // Calculates the current temperature based on the value of rate of change
            Tc = Tc + k * dt;
            // Update the time
            tc = tc + dt;
            // Writes the time and temperature to the data file
            results_transient<<tc<<'\t'<<Tc<<endl;
        // WHILE Current temperature is greater than 0.1 degrees of the Liquid Temperature
        } while (Tc > Tl + 0.1);
        // CLOSES data file for recording temperature change with mid radius value
        results_transient.close();

        // Write data with maximum value of radius
        // SETS initial condition
        T0 = 120;
        h = 1200;
        dt = 0.01;
        Tc = T0; // Current Temperature (Will update each loop)
        tc = 0; // Current time (Will update each loop)
        Tl = 30;
        r=max;
        // OPENS the data file for recording temperature change with max radius value
        results_transient.open(filename_transient_maxRadius[i].c_str(),ios::out);

        // COMPUTES the temperature change with max radius value
        // DO
        do {
            float k;
            // Calculates rate of change by using function RateofChange()
            k = RateofChange(r, RHO[i], h, Tl, Tc, C[i]);
            // Calculates the current temperature based on the value of rate of change
            Tc = Tc + k * dt;
            // Update the time
            tc = tc + dt;
            // Writes the time and temperature to the data file
            results_transient<<tc<<'\t'<<Tc<<endl;
        // WHILE Current temperature is greater than 0.1 degrees of the Liquid Temperature
        } while (Tc > Tl + 0.1);
        // CLOSES data file for recording temperature change with max radius value
        results_transient.close();
    // END FOR
    }
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