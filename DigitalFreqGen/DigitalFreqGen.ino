/**
* DIGITAL FUNCTION GENERATOR
* CODE FOR ARDUINO UNO R3 and MCP4822 DAC
*
* Allows for square, triangle, sine, and sawtooth waveforms
* 
* Triangle and sine waveforms are pre-computed
*/

#include <LiquidCrystal.h>
#include <SPI.h>

/////////////////////// DAC SETTINGS /////////////////////// 

const int cs = 13; // CHANGE IF CS PIN CHANGES

const uint8_t DAC_Settings = 0b0001; // Write to DAC_A, 2x gain

const int speed = 4; // How many values are "jumped" in the array

const int max_vals = 128; // Length of the arrays

// Pre-computed values for sine and triangle waves
uint16_t sine_vals[] = {2047, 2147, 2247, 2347, 2446, 2544, 2641, 2736, 2830, 2922, 3011, 3099, 3184, 3266, 3345, 3421, 3494, 33563, 3629, 3691, 3749, 3802, 3852, 3897, 3938, 3974, 4005, 4032, 4054, 4071, 4084, 4091, 4094, 4091, 4084, 4071, 4054, 4032, 4005, 3974, 3938, 3897, 3852, 3802, 3749, 3691, 3629, 3563, 3494, 3421, 3345, 3266, 3184, 3099, 3011, 2922, 2830, 2736, 2641, 2544, 2446, 2347, 2247, 2147, 2047, 1946, 1846, 1746, 1647, 1549, 1452, 1357, 1263, 1171, 1082, 994, 909, 827, 748, 672, 599, 530, 464, 402, 344, 291, 241, 196, 155, 119, 88, 61, 39, 22, 9, 2, 0, 2, 9, 22, 39, 61, 88, 119, 155, 196, 241, 291, 344, 402, 464, 530, 599, 672, 748, 827, 909, 994, 1082, 1171, 1263, 1357, 1452, 1549, 1647, 1746, 1846, 1946};
uint16_t triangle_vals[] = {63, 126, 189, 252, 315, 378, 441, 504, 567, 630, 693, 756, 819, 882, 945, 1008, 1071, 1134, 1197, 1260, 1323, 1386, 1449, 1512, 1575, 1638, 1701, 1764, 1827, 1890, 1953, 2016, 2079, 2142, 2205, 2268, 2331, 2394, 2457, 2520, 2583, 2646, 2709, 2772, 2835, 2898, 2961, 3024, 3087, 3150, 3213, 3276, 3339, 3402, 3465, 3528, 3591, 3654, 3717, 3780, 3843, 3906, 3969, 4032, 3969, 3906, 3843, 3780, 3717, 3654, 3591, 3528, 3465, 3402, 3339, 3276, 3213, 3150, 3087, 3024, 2961, 2898, 2835, 2772, 2709, 2646, 2583, 2520, 2457, 2394, 2331, 2268, 2205, 2142, 2079, 2016, 1953, 1890, 1827, 1764, 1701, 1638, 1575, 1512, 1449, 1386, 1323, 1260, 1197, 1134, 1071, 1008, 945, 882, 819, 756, 693, 630, 567, 504, 441, 378, 315, 252, 189, 126, 63, 0};

/////////////////////// LCD SETTINGS /////////////////////// 

// LCD Display Settings
const int rs = 10, en = 12, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int wave_setting;

const int wave_button = 11; // CHANGE IF WAVE BUTTON CHANGES (button to control wave setting)

/////////////////////// FUCNTIONS /////////////////////// 

int DAC_init() {
  pinMode(cs, OUTPUT);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE1);
}

int start_transmission() {
  digitalWrite(cs, LOW);
}

int end_transmission() {
  digitalWrite(cs, HIGH);
}

void write_to_DAC(uint16_t DAC_data) {
  
  uint16_t send_to_DAC = (DAC_Settings << 12) | (DAC_data & 0x0FFF); // Puts settings to first 4 bits, then data bits in the last 12 bits
  
  start_transmission();

  SPI.transfer(send_to_DAC >> 8);  // Send the high byte
  SPI.transfer(send_to_DAC & 0xFF); // Send the low byte

  end_transmission();
}

/////////////////////// Code /////////////////////// 

void setup() {
  lcd.begin(16,1);
  lcd.print("Welcome!");
  delay(2000);
  lcd.clear();
  lcd.print("Freq Generator");

  Serial.begin(9600);
  DAC_init();                     // Initializes SPI but does not start it
  wave_setting = 0;
  pinMode(wave_button, INPUT);
}

void loop() {
  if(digitalRead(wave_button) == HIGH) {
    delay(1000); // Debounce delay

    if(wave_setting == 0) {
      lcd.print("Wave: Square");

    } else if (wave_setting == 1) {
      lcd.print("Wave: Triangle");

    } else if (wave_setting == 2) {
      lcd.print("Wave: Sine");

    } else if (wave_setting == 3) {
      lcd.print("Wave: Sawtooth");
    }

    if(wave_setting < 3) {
      wave_setting++;
    } else {
      wave_setting = 0;
    }
  }

  for(uint8_t i = 0; max_vals - i > speed; i += speed) {
    if(wave_setting == 0) { // Square
      if(i < (0xff / 2)) {
        write_to_DAC(0x0);
      } else {
        write_to_DAC(0x0FFF);
      }

    } else if (wave_setting == 1) { // Triangle
      write_to_DAC(triangle_vals[i]);

    } else if (wave_setting == 2) { // Sine
      write_to_DAC(sine_vals[i]);

    } else if (wave_setting == 3) { // Sawtooth
      write_to_DAC(i);

    }
  }
}