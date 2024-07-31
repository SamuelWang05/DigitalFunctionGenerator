#include <iostream>
#include <stdint.h>
#include <cmath>

using namespace std;

// Define constants
const int max_length = 128;         // Max length of the array containing values for DAC
const int max_val = 4095;                 // Steps that the DAC is capable of
const double pi = 3.1415926535;

int dacVal[max_length];             // Array to hold data bits sent to DAC

///////////////////////////// CALCULATING TRIANGLE ARRAY /////////////////////////////

void calcTriangle() {
    cout << "Triangle values: {";

        int currSum = 0;                            // Current sum of DAC values
        int step = max_val / (max_length / 2);      // "Height" of each step relative to max value

    for(int i = 0; i < max_length; i++) {

        if(i < (max_length / 2)) {
            currSum += step;
            dacVal[i] = currSum;
        } else {
            currSum -= step;
            dacVal[i] = currSum;
        }

        if(i < max_length - 1) {   
            cout << dacVal[i] << ", ";
        } else {
            cout << dacVal[i] << "}\n";    // Handles fencepost
        }
    } 
}

/////////////////////////////// CALCULATING SINE ARRAY ///////////////////////////////

void calcSine() {

    double step = (2 * pi) / max_length;

    cout << "Sine values: {";

    for(int i = 0; i < max_length; i++) {
        double rad = i * step;                      // Computes radian
        double amp_y = sin(rad);                    // Computes corresponding amplitude (y-value), gives value from -1 to 1
        amp_y += 1;                                 // Changes range of sine to be from 0 - 2, DAC cannot handle negative values

        double dac_amp = amp_y * (max_val / 2);     // Changes amplitude to match DAC

        int int_dac_amp = (int) dac_amp;
        dacVal[i] = int_dac_amp;

        if(i < max_length - 1) {
            cout << dacVal[i] << ", ";
        } else {
            cout << dacVal[i] << "}\n";
        }
        
    }
}

/////////////////////////////////  PRINT DAC VALUES  /////////////////////////////////

int main() {
    calcTriangle();
    cout << "\n";
    calcSine();

    return 0;
}