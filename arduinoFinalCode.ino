/////////////////////////////////////////////////////////////////////////////////////////////
// This program allows the user to pick a plant from a list of 7 flower. The program then
// gathers data from 4 sensors and returns to the user an evaluation of how appropriate the
// place is for the chosen flower. The data shown to the user are temperature (temp),
// humidity (hum), soil moisture (SoilMoist), and luminosity (lux).
//
/////////////////SETUP OF THE SENSORS, LCD, BUTTONS, AND POTENTIOMETER///////////////////////
///////////////////////////TO THE ARDUINO/BREAD BOARDS///////////////////////////////////////

// Temperature and humidity sensor:
// Connect SIG pin to the digital pin 7 on the arduino board with a 10k resistor to 3.3V.
// Connect GND pin to GND on the bread board
// Connect VCC pin to either 5V or 3.3V on the bread board.

// Soil moisture sensor:
// Connect SIG pin to the analog pin A0 on the arduino board.
// Connect GND pin to the ground on the bread board
// Connect VCC pin to 5V and we suggest using a 10k Ohm resistor

// Luminosity sensor:
// Connect SDA pin to A4 on the arduino board.
// Connect SCL pin to A5 on the arduino board.
// Connect GND pin to the ground on the bread board.
// Connect VCC pin has to be connected to the 3.3V NOT 5V.

// Potentiometer:
// Side with two pins, connect one of them to GND and the other to 5V
// side with one pin, connect it to the LCD pin V0

// Control Buttons:
// one side to 5V
// other side has a 10k resistor and connects to digital pin 9 & 10
// on the arduino board

// LCD:
// Connect K to GND, RW, and VSS to GND
// Connect A to 5V with a 220 Ohm resistor
// Connect D4 - D7 to arudiono board digital pins D2 - D5
// D0 - D3 is not used
// Connect V0 to the potentionmete (previously done)
// Connect E to arudiono board digital pins D11
// Connect RS to arudiono board digital pins D12
// Connect VDD to 5V

/////////////////////////////////////////////////////////////////////////////////////////////

/*------------------------------------------Libraries---------------------------------------------------*/

#include "DHT.h"                    // library for temp/humid sensor
#define DHTPIN            7         // digital pin number for the  humidity/temperatur
#define DHTTYPE DHT22               // type of temperature/humidity sensor
#include <LiquidCrystal.h>          // library for LCD
#include <SparkFunTSL2561.h>        // library for luminosity
#include <Wire.h>                   // library required for luminosity

/*-----------------------------Prints intro in the LCD screen -------------------------------------------*/
void showIntro();
/*-----------------------Chooses plan with input from function getButtonPush ----------------------------*/
void choosePlant(int &flag, int flowerChoice);
/*-----------------------Gets button pushes on high/low (inputs 9 & 10)----------------------------------*/
void getButtonPush(int &flag, int &switch1State, int &switch2State, int &flowerChoice, int &maxChoiceNum);

LiquidCrystal lcd(12,11,5,4,3,2);             // LCD on

DHT dht(DHTPIN, DHTTYPE);                     // temperature/humidity sensor

SFE_TSL2561 light;                            // luminosity Sensor

boolean gain;                                 // related to luminosity sensor
unsigned int ms;                              // luminosity sensor

class Plant
{
public:
    /*-----------------------Initizalizes structure for chosen plant-------------------------------------*/
    void savePlantVariables(int flowerChoice);
    /*-----------------------Chooses sensor to gather data from-------------------------------------*/
    void chooseSensor(int &flag, int sensor);
private:
    /*-----------------------Soil Moisture sensor-------------------------------------*/
    void soilMoisture();
    /*-----------------------Luminosity sensor reading-------------------------------------*/
    void luminosity();
    /*-----------------------temperature sensor reading-------------------------------------*/
    void temperature();//code adapted from Adafruit example
    /*-----------------------Air humidity sensor-------------------------------------*/
    void airHumidity();//code adapted from Adafruit example
    
    //variables for selected flower
    int soilMoistMin, soilMoistMax;               // soil moisture sensor
    double luxMin, luxMax;                        // luminosity sensor
    int airHumidMin, airHumidMax;                 // humidity sensor
    int tempMin, tempMax;                         // temperature sensor
};

/*-----------------------Arduino standard setup function (main) -------------------------------------*/
//
//
//
//
//
void setup()                          // setup
{
    Serial.begin(9600);               // sets serial's clock
    showIntro();                      // shows project title
    
}//END of setup
//
//
//
//
//

/*-----------------------Prints intro in the LCD screen -------------------------------------*/
//
//
//
void showIntro()
{
    /*--------------------------------------------LCD SCREEN PRINTS---------------------------------------------------------*/
    lcd.begin(16,2);
    pinMode(6,INPUT);
    pinMode(10,INPUT);
    
    // Introduction of the project name on the LCD
    lcd.print("Plant Placement");
    lcd.setCursor(0,1);
    lcd.print("Analyzer");
    delay(4000);
    lcd.clear();
    
    // Telling the user to choose which plant they want information about on the LCD
    lcd.print("Choose your");
    lcd.setCursor(0,1);
    lcd.print("flower:");
    delay(3000);
    lcd.clear();
}

/*-----------------------Chooses plan with input from function getButtonPush -------------------------------------*/
// passes flag by reference, used for another loop
// passes flowerChoice by reference, used for another function


void choosePlant(int &flag, int flowerChoice)
{
    int switch1State(0), switch2State(0);
    
    while (flag == 0)                             // while loop for different plants
    {
        switch (flowerChoice)                     // switch case statement for different plant names
        {
            case 0:                               // Plant Dahlia case 0
                lcd.setCursor(0,0);
                lcd.print("1. Dahlia");
                lcd.setCursor(0,1);
                lcd.print("<  >  Enter");
                break;
            case 1:                               // Plant Pansy case 1
                lcd.setCursor(0,0);
                lcd.print("2. Pansy");
                lcd.setCursor(0,1);
                lcd.print("<  >  Enter");
                break;
            case 2:                               // Plant Petunia case 2
                lcd.setCursor(0,0);
                lcd.print("3. Petunia");
                lcd.setCursor(0,1);
                lcd.print("<  >  Enter");
                break;
            case 3:                               // Plant Orchid case 3
                lcd.setCursor(0,0);
                lcd.print("4. Orchid");
                lcd.setCursor(0,1);
                lcd.print("<  >  Enter");
                break;
            case 4:                               // Plant Sunflower case 4
                lcd.setCursor(0,0);
                lcd.print("5. Sunflower");
                lcd.setCursor(0,1);
                lcd.print("<  >  Enter");
                break;
            case 5:                               // Plant Torenia case 5
                lcd.setCursor(0,0);
                lcd.print("6. Torenia");
                lcd.setCursor(0,1);
                lcd.print("<  >  Enter");
                break;
            case 6:                               // Plant Gaillardia case 6
                lcd.setCursor(0,0);
                lcd.print("7. Gaillardia");
                lcd.setCursor(0,1);
                lcd.print("<  >  Enter");
                break;
        }                                          //end of switch with plants' names
        
        getButtonPush(flag, switch1State, switch2State, flowerChoice, 6);           //gets physical button push
        
    }                                              //end of while loop
}
/*-----------------------Gets button pushes on high/low (inputs 9 & 10)-------------------------------------*/
//
//
//
//
void getButtonPush(int &flag, int &switch1State, int &switch2State, int &flowerChoice, int maxChoiceNum)//maxChoiceNum starts at 0, not 1!!! - 5 for flowers, 3 for sensors (4 reads)
{
    switch1State = digitalRead(9);                                  //reading left(down)
    switch2State = digitalRead(10);                                 //reding right push-button (up)
    delay(165);             //to avoid changing values too quickly and to control better the change on variable showFlowerName
    
    if ( switch1State == HIGH && switch2State == LOW)               // for selecting down
    {
        flowerChoice = flowerChoice - 1;
        if ( flowerChoice < 0 )                    // makes sure it stays within the expected range
        {
            flowerChoice = maxChoiceNum;
        }
        lcd.clear();
    }                   //end selecting down
    else if ( switch2State == HIGH && switch1State == LOW )       // selects up the list of plants
    {
        flowerChoice = flowerChoice + 1;
        
        if ( flowerChoice > maxChoiceNum )        // makes sure it stays within the expected range
        {
            flowerChoice = 0;
        }
        lcd.clear();
    }                   // for selecting up
    else if (switch2State == HIGH && switch1State == HIGH)        //selects down the list of plants
    {
        flag = 1;
        //selects plant
        lcd.clear();
    }                   //for saving the plant option
}

/*-----------------------Initizalizes structure for chosen plant-------------------------------------*/
// private member function of class Plan
//int soilMoistMin, soilMoistMax;
//int luxMin, luxMax;
//int airHumidMin, airHumidMax;
//int tempMin, tempMax;

void Plant::savePlantVariables(int flowerChoice)
{
    switch (flowerChoice)
    {
        case 0:                                     //Dahlia
            soilMoistMin = 200; soilMoistMax = 400;               //soil moisture
            luxMin = 40000; luxMax = 65000;                       //luminosity
            airHumidMin = 10; airHumidMax = 50;                   //air humidity
            tempMin = 67; tempMax = 72;                           //ideal temperature
            break;
        case 1:                                     //Pansy
            soilMoistMin = 200; soilMoistMax = 400;               //soil moisture
            luxMin = 40000; luxMax = 60000;                       //luminosity
            airHumidMin = 30; airHumidMax = 50;                   //air humidity
            tempMin = 64; tempMax = 67;                           //ideal temperature
            break;
        case 2:                                     //Petunia
            soilMoistMin = 100; soilMoistMax = 400;               //soil moisture
            luxMin = 3500; luxMax = 5000;                         //luminosity
            airHumidMin = 30; airHumidMax = 50;                   //air humidity
            tempMin = 55; tempMax = 75;                           //ideal temperature
            break;
        case 3:                                     //Orchid
            soilMoistMin = 200; soilMoistMax = 400;               //soil moisture
            luxMin = 10000; luxMax = 30000;                       //luminosity
            airHumidMin = 40; airHumidMax = 60;                   //air humidity
            tempMin = 66; tempMax = 84;                           //ideal temperature
            break;
        case 4:                                     //Sunflower
            soilMoistMin = 300; soilMoistMax = 400;               //soil moisture
            luxMin = 35000; luxMax = 45000;                       //luminosity
            airHumidMin = 30; airHumidMax = 50;                   //air humidity
            tempMin = 65; tempMax = 70;                           //ideal temperature
            break;
        case 5:                                     //Torenia
            soilMoistMin = 200; soilMoistMax = 400;               //soil moisture
            luxMin = 10000; luxMax = 30000;                       //luminosity
            airHumidMin = 30; airHumidMax = 70;                   //air humidity
            tempMin = 65; tempMax = 68;                           //ideal temperature
            break;
        case 6:                                     //Gaillardia
            soilMoistMin = 200; soilMoistMax = 400;               //soil moisture
            luxMin = 50000; luxMax = 75000;                       //luminosity
            airHumidMin = 30; airHumidMax = 50;                   //air humidity
            tempMin = 55; tempMax = 60;                           //ideal temperature
            break;
    }                   //end of switch
    
}         //end of Plant constructor

/*-----------------------Choose sensor-------------------------------------*/
// switch statement
// USES function getButtonPush for reading digital buttons being pressed
//
//
void Plant::chooseSensor(int &flag, int sensor)
{
    int switch1State(0), switch2State(0);
    
    while (flag == 0)
    {
        switch (sensor)                     // switch case for plant sensors choices
        {
            case 0:
                Plant::temperature();       // temperature case 0
                break;
            case 1:
                Plant::airHumidity();       //  humidity case 1
                break;
            case 2:
                Plant::soilMoisture();      // soil moisture case 2
                break;
            case 3:
                Plant::luminosity();        // luminosity case 3
        }                                                           //end of switch with plants' names
        
        getButtonPush(flag, switch1State, switch2State, sensor, 3);         //gets physical button push
        
    }                                                               //end of while loop
}


/*-----------------------temperature sensor reading-------------------------------------*/
// private member function of class Plan
// USES private member variables - tempMin, tempMax
//
//
void Plant::temperature()                         // temperature sensor test
{
    float temp = dht.readTemperature(true);       // Reads temperature as Fahrenheit (isFahrenheit = true)
    lcd.setCursor(0,0);
    lcd.print("temp ");
    lcd.setCursor(0,1);
    lcd.print(temp);
    lcd.setCursor(10,0);
    lcd.print("<> RET");
    
    if (isnan(temp))                              // Check if any reads failed and exit early (to try again)
    {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Failed reading - DHT sensor");
        delay(2000);
        return;
    }
    
    lcd.setCursor(4,1);
    // if else statement to evaluates temperatures measurements
    if ( temp < tempMin )
    {
        lcd.print(" F  too low ");
    }
    else if ( temp > tempMax )
    {
        lcd.print(" F  too high");
    }
    else if (( temp >= tempMin ) && ( temp <= tempMax ))
    {
        lcd.print(" F     good");
    }
}

/*-----------------------Air humidity sensor-------------------------------------*/
// private member function of class Plan
// USES private member variables - airHumidMin, airHumidMax;
//
//
void Plant::airHumidity()                       // humidity sensor test
{
    float humidity = dht.readHumidity();        // reads humidity by percentage
    lcd.setCursor(0,0);
    lcd.print("hum ");
    lcd.setCursor(0,1);
    lcd.print(humidity);
    lcd.setCursor(10,0);
    lcd.print("<> RET");
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity))
    {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Failed reading - DHT sensor");
        delay(2000);
        return;
    }
    
    lcd.setCursor(4,1);
    // if else statement to evaluates humidity measurements
    if ( humidity < airHumidMin )
    {
        lcd.print("%  too low ");
    }
    else if ( humidity > airHumidMax )
    {
        lcd.print("%  too high");
    }
    else if (( humidity >= airHumidMin ) && ( humidity <= airHumidMax ))
    {
        lcd.print("%      good");
    }
}

/*-----------------------Soil Moisture sensor-------------------------------------*/
// private member function of class Plan
// USES private member variables - soilMoistMin, soilMoistMax
//
//
void Plant::soilMoisture()                          // soil moisture sensor test
{
    int sensorPin = A0;
    int moisture = analogRead(sensorPin)*0.5;
    delay(200);                                     //avoid overloading sensor
    lcd.setCursor(0,0);
    lcd.print("SoilMoist");
    lcd.setCursor(0,1);
    lcd.print(moisture);
    lcd.setCursor(10,0);
    lcd.print("<> RET");
    
    lcd.setCursor(4,1);
    // if else statement to evaluates soil moisture measurements
    if ( moisture < soilMoistMin )
    {
        lcd.print("   too low ");
    }
    else if ( moisture > soilMoistMax )
    {
        lcd.print("   too high");
    }
    else if (( moisture >= soilMoistMin ) && ( moisture <= soilMoistMax ))
    {
        lcd.print("      good");
    }
    
}

/*-----------------------Luminosity-------------------------------------*/
// private member function of class Plan
// USES private member variables - luxMin, luxMax
//
//
void Plant::luminosity()//code adapted from Sparkfun example
{
    lcd.clear();
    unsigned int data0, data1;
    double lux;
    boolean good;
    
    light.begin();
    gain = 0;                               // Low Gain
    unsigned char time = 1;                 // Medium Integration Time
    
    // If gain = false (0), device is set to low gain (1X)
    // If gain = high (1), device is set to high gain (16X)
    // If time = 0, integration will be 13.7ms
    // If time = 1, integration will be 101ms
    // If time = 2, integration will be 402ms
    // If time = 3, use manual start / stop
    
    lcd.setCursor(0,0);
    lcd.print("lux");
    lcd.setCursor(0,1);
    lcd.print(lux);
    lcd.setCursor(10,0);
    lcd.print("<> RET");
    
    light.setTiming(gain,time,ms);                        // Outputs parameters to sensor
    light.setPowerUp();                                   // Powers up
    delay(ms);
    
    
    light.getData(data0,data1);                           // Retrieve Data
    good = light.getLux(gain,ms,data0,data1,lux);         // Performs lux calculation
    
    
    lcd.setCursor(8,1);
    
    if ( lux < luxMin && good == 1 )                      //evaluates temperatures
    {
        lcd.print(" too low");
    }
    else if ( lux > luxMax )
    {
        lcd.print("too high");
    }
    else if (( lux >= luxMin ) && ( lux <= luxMax ))
    {
        lcd.print("    good");
    }
    else if (good == 0)
        
        lcd.print("saturated");
}
/*-----------------------Arduino standard execution loop-------------------------------------*/
//
//
//
//
void loop()
{
    int flowerChoice(0), flag(0), sensor(0);
    choosePlant(flag,flowerChoice);
    Plant flower;
    flower.savePlantVariables(flowerChoice);
    dht.begin();//starts humidity sensor readings
    flag = 0;//for running the next for loop
    flower.chooseSensor(flag,sensor);
}
