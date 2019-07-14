// ***************************************************
// ***      OVERHEAD PANEL BOEING 737NG PMDG       ***
// ***  BACHELOR THESIS IN AEROSPACE ENGINEERING   ***
// ***       TECHNICAL UNIVERSITY OF MADRID        ***
// ***   CREATED BY SANTIAGO GIL LÓPEZ DE PABLO    ***
// ***                                             ***
// ***               VERSION v1.6                  ***
// ***************************************************


// --- LIBRARIES SECTION --- //

  #include <Servo.h>



// --- CLASSES SECTION --- //

  // *UPDATE SERVO POSITION CLASS*
  
  class SERVO {
    
    Servo servo; // the servo
    int updatePos; // desired new position
    int updateInterval; // Interval between updates
    int servo_pin; // Pin the servo must be attached to
    unsigned long lastUpdateServo = millis(); // Last update of position
  
    public:
      SERVO(int pin){
        servo_pin = pin; 
      }
      
      void Attach(){
        servo.attach(servo_pin);
      }
      
      void Detach(){
          servo.detach();
      }
  
      void Update(int interval, int pos){
        updateInterval = interval;
        updatePos = pos;
        if( (millis() - lastUpdateServo) > updateInterval ){  //time to update
          servo.write(updatePos);
          lastUpdateServo = millis();
        } 
      }
  };



// --- VARIABLES SECTION --- //


  // *PANEL C1-1 VARIABLES*
    
    // **LEDS**

      int valueBU='0', valueBV='0', valueBW='0', valueBX='1', valueBY='1', valueBZ='0'; //Control LED state
      int valueCA='0', valueCB='0', valueCC='0', valueCE='1'; //Control LED state

    // **SWITCHES**
    
      int PRE_SWITCH_YAW_DAMPER = 0, PRE_SWITCH_SPOILER_A = 1, PRE_SWITCH_SPOILER_B = 1, PRE_SWITCH_ALTERNATE_FLAPS = 0;
      int PRE_SWITCH_STBY_RUD_A = 2, PRE_SWITCH_STBY_RUD_B = 2, PRE_SWITCH_FLAPS_POS = 1; 
      
      int SWITCH_YAW_DAMPER, SWITCH_SPOILER_A, SWITCH_SPOILER_B, SWITCH_ALTERNATE_FLAPS;
      int SWITCH_STBY_RUD_A1, SWITCH_STBY_RUD_A2, SWITCH_STBY_RUD_B1, SWITCH_STBY_RUD_B2, SWITCH_FLAPS_POS_1, SWITCH_FLAPS_POS_2;
    
    // **SHIFT REGISTERS (OUT)**

      int dataPin_OUT_1 = 22; //Pin connected to DS of SR_OUT_1
      int latchPin_OUT_1 = 23; //Pin connected to ST_CP of SR_OUT_1
      int clockPin_OUT_1 = 24; //Pin connected to SH_CP of SR_OUT_1
    
      byte SR_OUT_1; //Control LED state
      byte SR_OUT_2; //Control LED state
      byte SR_OUT_3; //Control LED state
        
    // **SHIFT REGISTERS (IN)**

      int ploadPin_IN_1 = 25;  // Pin connected to PL of SR_IN_7
      int clockEnablePin_IN_1 = 26;  // Pin connected to CE of SR_IN_7
      int dataPin_IN_1 = 27; // Pin connected to Q7 of SR_IN_7
      int clockPin_IN_1 = 28; // Pin connected to CP of SR_IN_7
    
      #define NUMBER_OF_SHIFT_CHIPS_1   7 // How many shift register chips are daisy-chained.
      #define DATA_WIDTH_1   NUMBER_OF_SHIFT_CHIPS_1 * 8 // Width of data (how many ext lines).
      #define PULSE_WIDTH_USEC   0.001 // Width of pulse to trigger the shift register to read and latch.
      #define SR_IN_1_T unsigned long
      
      SR_IN_1_T SR_IN_1; //Control SWITCH state
      SR_IN_1_T OLD_SR_IN_1; //Control previous SWITCH state
      SR_IN_1_T SR_IN_5; //Control SWITCH state
      SR_IN_1_T OLD_SR_IN_5; //Control previous SWITCH state


  // *PANEL C1-2 VARIABLES*
      
    // **SWITCHES**
      
      int PRE_SWITCH_VHF_NAVIGATION = 1, PRE_SWITCH_IRS_SELECTOR = 1, PRE_SWITCH_FMC = 1, PRE_SELECTOR_DISPLAY_SOURCE = 1, PRE_SWITCH_CONTROL_PANEL = 1;

      int SWITCH_VHF_NAVIGATION_1, SWITCH_VHF_NAVIGATION_2, SWITCH_IRS_SELECTOR_1, SWITCH_IRS_SELECTOR_2, SWITCH_FMC_1, SWITCH_FMC_2;
      int SELECTOR_DISPLAY_SOURCE_1, SELECTOR_DISPLAY_SOURCE_2, SWITCH_CONTROL_PANEL_1, SWITCH_CONTROL_PANEL_2;

        
  // *PANEL C1-3 VARIABLES*
    
    // **LEDS**

        int valueCF='1', valueCG='1', valueCH='1', valueCI='1', valueCJ='0', valueCK='0'; //Control LED state
        int valueCL='0', valueCM='0', valueCN='0', valueCO='1', valueCP='1', valueCQ='1', valueCR='1'; //Control LED state

    // **SWITCHES**
    
        int PRE_SWITCH_CROSS_FEED = 0, PRE_SWITCH_FUEL_PUMPS_A = 0, PRE_SWITCH_FUEL_PUMPS_B = 0, PRE_SWITCH_AFT_FUEL_PUMP_1 = 0;
        int PRE_SWITCH_AFT_FUEL_PUMP_2 = 0, PRE_SWITCH_FWD_FUEL_PUMP_1 = 0, PRE_SWITCH_FWD_FUEL_PUMP_2 = 0;
        
        int SWITCH_CROSS_FEED, SWITCH_FUEL_PUMPS_A, SWITCH_FUEL_PUMPS_B, SWITCH_AFT_FUEL_PUMP_1, SWITCH_AFT_FUEL_PUMP_2;
        int SWITCH_FWD_FUEL_PUMP_1, SWITCH_FWD_FUEL_PUMP_2;

    // **SERVOS**

      SERVO SERVO_FUEL_TEMP(2); // Attached to pin D2
      int pos_servo_fuel_temp = 120; // Servo initial position after cold and dark
      String valueDOLLARB; // Entrance to servo position
      int valueDOLLARBi = 56; // valueDOLLARC string converted to integer (initial after cold and dark)
      int servo_activated_1 = 0; // Initially disconnected


  // *PANEL C1-4 VARIABLES*
    
    // **SWITCHES**
    
      int PRE_SWITCH_RETRACTABLE_LDG_LIGHTS_L = 0, PRE_SWITCH_RETRACTABLE_LDG_LIGHTS_R = 0, PRE_SWITCH_FIXED_LDG_LIGHTS_L = 0, PRE_SWITCH_FIXED_LDG_LIGHTS_R = 0;
      int PRE_SWITCH_RWY_LIGHT_L = 0, PRE_SWITCH_RWY_LIGHT_R = 0, PRE_SWITCH_TAXI_LIGHT = 0;
      int PRE_SWITCH_APU = 0;
      int PRE_SELECTOR_ENGINE_STATOR_L = 1, PRE_SELECTOR_ENGINE_STATOR_R = 1, PRE_SWITCH_IGNITION = 0;
      int PRE_SWITCH_LOGO_LIGHT = 0, PRE_SWITCH_STROBE_LIGHT = 1, PRE_SWITCH_ANTI_COLLITION_LIGHT = 0, PRE_SWITCH_WING_LIGHT = 0, PRE_SWITCH_WHEEL_WELL_LIGHT = 0;
      
      int SWITCH_RETRACTABLE_LDG_LIGHTS_L, SWITCH_RETRACTABLE_LDG_LIGHTS_R;
      int SWITCH_FIXED_LDG_LIGHTS_L, SWITCH_FIXED_LDG_LIGHTS_R, SWITCH_RWY_LIGHT_L, SWITCH_RWY_LIGHT_R, SWITCH_TAXI_LIGHT;
      int SWITCH_APU_1, SWITCH_APU_2;
      int SELECTOR_ENGINE_STATOR_L_1, SELECTOR_ENGINE_STATOR_L_2, SELECTOR_ENGINE_STATOR_L_3, SELECTOR_ENGINE_STATOR_L_4;
      int SELECTOR_ENGINE_STATOR_R_1, SELECTOR_ENGINE_STATOR_R_2, SELECTOR_ENGINE_STATOR_R_3, SELECTOR_ENGINE_STATOR_R_4;
      int SWITCH_IGNITION_1, SWITCH_IGNITION_2, SWITCH_LOGO_LIGHT, SWITCH_STROBE_LIGHT_1, SWITCH_STROBE_LIGHT_2, SWITCH_ANTI_COLLITION_LIGHT, SWITCH_WING_LIGHT, SWITCH_WHEEL_WELL_LIGHT;      

    // **SERVOS**
      
      SERVO SERVO_SELECTOR_ENGINE_STARTOR(3); // Attached to pin D3
      int pos_servo_selector_engine_startor = 105; // Servo initial position after cold and dark

  // *PANEL C2-1 VARIABLES*

    // **LEDS**

      int valueCY = '0', valueCZ = '0', valueDA = '0'; //Control LED state
      String valueCS, valueCU, valueCV, valueCW, valueCX; //Control LED numbers on the display, string value 
      int valueCSi = 0, valueCUi = 0, valueCVi = 0, valueCWi = 0, valueCXi = 0; //Control LED numbers on the display, integer value

      long display_num_1, display_num_2, display_num_3, display_num_4, display_num_5; //number shown in each digit
      int display_pos; //shifted position value
      int shift_number_1 [3]={}, shift_number_2 [3]={}, shift_number_3 [2]={}, shift_number_4 [3]={}, shift_number_5 [3]={}; //number shifted in an array
      int neg_num_1=0, neg_num_4=0;
      int last_empty_digit_1 = 0, last_empty_digit_4 = 0;
    
    // **SWITCHES**

      int PRE_BUTTON_MAINT = 0;
      int PRE_SELECTOR_DC_SOURCE = 2, PRE_SELECTOR_AC_SOURCE = 3; 
      int PRE_SWITCH_MAIN_BATTERY = 0, PRE_SWITCH_CAB_UTIL = 1, PRE_SWITCH_IFE_PASS_SEAT = 1;

      int BUTTON_MAINT;
      int SELECTOR_DC_SOURCE_0, SELECTOR_DC_SOURCE_1, SELECTOR_DC_SOURCE_2, SELECTOR_DC_SOURCE_3, SELECTOR_DC_SOURCE_4, SELECTOR_DC_SOURCE_5, SELECTOR_DC_SOURCE_6, SELECTOR_DC_SOURCE_7;
      int SELECTOR_AC_SOURCE_0, SELECTOR_AC_SOURCE_1, SELECTOR_AC_SOURCE_2, SELECTOR_AC_SOURCE_3, SELECTOR_AC_SOURCE_4, SELECTOR_AC_SOURCE_5, SELECTOR_AC_SOURCE_6;
      int SWITCH_MAIN_BATTERY;
      int SWITCH_CAB_UTIL, SWITCH_IFE_PASS_SEAT;
      
    // **SHIFT REGISTERS (OUT)**

      int dataPin_OUT_4 = 29; //Pin connected to DS of SR_OUT_4
      int latchPin_OUT_4 = 30; //Pin connected to ST_CP of SR_OUT_4
      int clockPin_OUT_4 = 31; //Pin connected to SH_CP of SR_OUT_4
    
      byte SR_OUT_4; //Control LED state
      byte SR_OUT_5; //Control LED state
      byte SR_OUT_6; //Control LED state
      byte SR_OUT_7; //Control LED state
      byte SR_OUT_8; //Control LED state
      byte SR_OUT_9; //Control LED state
      byte SR_OUT_10; //Control LED state
      byte SR_OUT_11; //Control LED state
      byte SR_OUT_12; //Control LED state
        
    // **SHIFT REGISTERS (IN)**

      int ploadPin_IN_8 = 32;  // Pin connected to PL of SR_IN_14
      int clockEnablePin_IN_8 = 33;  // Pin connected to CE of SR_IN_14
      int dataPin_IN_8 = 34; // Pin connected to Q7 of SR_IN_14
      int clockPin_IN_8 = 35; // Pin connected to CP of SR_IN_14
    
      #define NUMBER_OF_SHIFT_CHIPS_8   7 // How many shift register chips are daisy-chained.
      #define DATA_WIDTH_8   NUMBER_OF_SHIFT_CHIPS_8 * 8 // Width of data (how many ext lines).
      #define SR_IN_8_T unsigned long
      
      SR_IN_8_T SR_IN_8; //Control SWITCH state
      SR_IN_8_T OLD_SR_IN_8; //Control previous SWITCH state
      SR_IN_8_T SR_IN_12; //Control SWITCH state
      SR_IN_8_T OLD_SR_IN_12; //Control previous SWITCH state
  
  // *PANEL C2-2 VARIABLES*

    // **LEDS**
    
      int valueDB = '0', valueDC = '1', valueDD = '1'; //Control LED state

    // **SWITCHES**      

      int PRE_SWITCH_STANDBY_POWER = 2, PRE_SWITCH_DRIVE_1= 0, PRE_SWITCH_DRIVE_2= 0;

      int SWITCH_STANDBY_POWER_1, SWITCH_STANDBY_POWER_2, SWITCH_DRIVE_1, SWITCH_DRIVE_2;
      
  // *PANEL C2-3 VARIABLES*

    // **LEDS**
    
      int valueDE='0', valueDF='1', valueDG='1', valueDH='1', valueDI='1', valueDJ='1', valueDK='1', valueDL='0'; //Control LED state

    // **SWITCHES**
    
      int PRE_SWITCH_GROUND_POWER = 1, PRE_SWITCH_BUS_TRANSFER = 1;
      int PRE_SWITCH_MAIN_GEN_1 = 1, PRE_SWITCH_MAIN_GEN_2 = 1, PRE_SWITCH_APU_GEN_1 = 1, PRE_SWITCH_APU_GEN_2 = 1;

      int SWITCH_GROUND_POWER_ON, SWITCH_GROUND_POWER_OFF;
      int SWITCH_BUS_TRANSFER, SWITCH_MAIN_GEN_1_ON, SWITCH_MAIN_GEN_1_OFF, SWITCH_MAIN_GEN_2_ON, SWITCH_MAIN_GEN_2_OFF;
      int SWITCH_APU_GEN_1_ON, SWITCH_APU_GEN_1_OFF, SWITCH_APU_GEN_2_ON, SWITCH_APU_GEN_2_OFF;

  // *PANEL C2-4 VARIABLES*

    // **LEDS**

      int valueDM='0', valueDN='0', valueDO='0', valueDP='0';

    // **SWITCHES**

      int PRE_SELECTOR_WIPER_L = 0;
      
      int SELECTOR_WIPER_L_0, SELECTOR_WIPER_L_1, SELECTOR_WIPER_L_2, SELECTOR_WIPER_L_3;

    // **SERVOS**
      
      SERVO SERVO_EGT_APU(4); // Attached to pin D4
      int pos_servo_egt_apu = 10; // Posición del servo
      String valueDOLLARC; // Entrada de posición del servo
      int valueDOLLARCi = 0; // valueDOLLARC string convertido a integer

      int servo_activated_2 = 0;

  // *PANEL C3-1 VARIABLES*

    // **POTENCIOMETERS**

      const int POT_CIRCUIT_BREAKER = A0, POT_PANEL = A1;  // Analog input pin that the potentiometer is attached to
      const int LED_BACKLIGHT = 12; // Analog output pin that the LED is attached to

      int pot_circuit_breaker_value = 0, pot_panel_value = 0; // value read from the pot
      int led_backlight_value = 0; // value output to the PWM (analog out)

 // *PANEL C3-2 VARIABLES*

    // **LEDS**

      int valueDR= '0', valueDS = '0', valueDT = '1', valueDU = '0';
      
    // **SWITCHES**

      int PRE_SWITCH_EQUIP_SUPPLY = 0, PRE_SWITCH_EQUIP_EXHAUST = 0, PRE_SWITCH_EMER_EXIT_LIGHT = 0;
      int PRE_SWITCH_CHIME = 0, PRE_SWITCH_FASTEN_BELTS = 0;
      int PRE_BUTTON_ATTEND = 0, PRE_BUTTON_GRD_CALL = 0;
      int PRE_SELECTOR_WIPER_R = 0;

      int SWITCH_EQUIP_SUPPLY, SWITCH_EQUIP_EXHAUST; 
      int SWITCH_EMER_EXIT_LIGHT_1, SWITCH_EMER_EXIT_LIGHT_2;
      int SWITCH_CHIME, SWITCH_FASTEN_BELTS_1, SWITCH_FASTEN_BELTS_2;
      int BUTTON_ATTEND, BUTTON_GRD_CALL;
      int SELECTOR_WIPER_R_0, SELECTOR_WIPER_R_1, SELECTOR_WIPER_R_2, SELECTOR_WIPER_R_3;

 // *PANEL C4-1 VARIABLES*

    // **LEDS**

      int valueDW = '0', valueDX = '0', valueDY = '0', valueDZ = '0', valueEA = '0', valueEB = '0', valueEC = '0', valueED = '0';
      int valueEE = '1', valueEF = '1', valueEG = '1', valueEH = '1', valueEI = '1', valueEJ = '1', valueEK = '1', valueEL = '1';
      
    // **SWITCHES**

      int PRE_SWITCH_WH_SIDE_1 = 0, PRE_SWITCH_WH_SIDE_2 = 0, PRE_SWITCH_WH_FWD_1 = 0, PRE_SWITCH_WH_FWD_2 = 0;
      int PRE_SWITCH_PROBE_HEAT_A = 0, PRE_SWITCH_PROBE_HEAT_B = 0, PRE_SWITCH_OVERHEAT = 1, PRE_BUTTON_TAT_TEST = 0;

      int SWITCH_WH_SIDE_1, SWITCH_WH_SIDE_2, SWITCH_WH_FWD_1, SWITCH_WH_FWD_2;
      int SWITCH_PROBE_HEAT_A, SWITCH_PROBE_HEAT_B, SWITCH_OVERHEAT_1, SWITCH_OVERHEAT_2, BUTTON_TAT_TEST;

    // **SHIFT REGISTERS (OUT)**

      int dataPin_OUT_13 = 36; //Pin connected to DS of SR_OUT_13
      int latchPin_OUT_13 = 37; //Pin connected to ST_CP of SR_OUT_13
      int clockPin_OUT_13 = 38; //Pin connected to SH_CP of SR_OUT_13
    
      byte SR_OUT_13; //Control LED state
      byte SR_OUT_14; //Control LED state
      byte SR_OUT_15; //Control LED state
      byte SR_OUT_16; //Control LED state
      byte SR_OUT_17; //Control LED state
      byte SR_OUT_18; //Control LED state

    // **SHIFT REGISTERS (IN)**
    
      int ploadPin_IN_15 = 39;  // Pin connected to PL of SR_IN_19
      int clockEnablePin_IN_15 = 40;  // Pin connected to CE of SR_IN_19
      int dataPin_IN_15 = 41; // Pin connected to Q7 of SR_IN_19
      int clockPin_IN_15 = 42; // Pin connected to CP of SR_IN_19
    
      #define NUMBER_OF_SHIFT_CHIPS_15   5 // How many shift register chips are daisy-chained.
      #define DATA_WIDTH_15   NUMBER_OF_SHIFT_CHIPS_15 * 8 // Width of data (how many ext lines).
      #define SR_IN_15_T unsigned long
      
      SR_IN_15_T SR_IN_15; //Control SWITCH state
      SR_IN_15_T OLD_SR_IN_15; //Control previous SWITCH state
      SR_IN_15_T SR_IN_19; //Control SWITCH state
      SR_IN_15_T OLD_SR_IN_19; //Control previous SWITCH state

 // *PANEL C4-2 VARIABLES*

    // **LEDS**

      int valueEM = '0', valueEN = '0', valueEO = '0', valueEP = '0', valueEQ = '0', valueER = '0';
      
    // **SWITCHES**

      int PRE_SWITCH_WING_ANTI_ICE = 0, PRE_SWITCH_ENGINE_ANTI_ICE_1 = 0, PRE_SWITCH_ENGINE_ANTI_ICE_2 = 0;

      int SWITCH_WING_ANTI_ICE, SWITCH_ENGINE_ANTI_ICE_1, SWITCH_ENGINE_ANTI_ICE_2;

 // *PANEL C4-3 VARIABLES*

    // **LEDS**

      int valueES = '0', valueET = '0', valueEU = '1', valueEV = '1', valueEW = '1', valueEX = '1';
      
    // **SWITCHES**

      int PRE_SWITCH_ENGINE_HYD_1 = 1, PRE_SWITCH_ENGINE_HYD_2 = 1, PRE_SWITCH_ELECTRIC_HYD_1 = 0, PRE_SWITCH_ELECTRIC_HYD_2 = 0;

      int SWITCH_ENGINE_HYD_1, SWITCH_ENGINE_HYD_2, SWITCH_ELECTRIC_HYD_1, SWITCH_ELECTRIC_HYD_2;

 // *PANEL C4-4 VARIABLES*

    // **LEDS**

      int valueEY = '1', valueEZ = '0', valueFB = '0', valueFC = '0', valueFD = '0', valueFE = '0';
      int valueFF = '0', valueFG = '0', valueFH = '0', valueFI = '0', valueFJ = '0';           
      
 // *PANEL C4-5 VARIABLES*

    // **LEDS**
      
      int valueZZ = '0';
      
    // **SWITCHES**

      int PRE_BUTTON_COCKPIT_VOICE_TEST = 0, PRE_BUTTON_COCKPIT_VOICE_ERASE = 0;
      
      int BUTTON_COCKPIT_VOICE_TEST, BUTTON_COCKPIT_VOICE_ERASE;

 // *PANEL C4-6 VARIABLES*  

    // **SWITCHES**

      int PRE_BUTTON_ALT_HORN_CUTOUT = 0;
      
      int BUTTON_ALT_HORN_CUTOUT;

    // **SERVOS**

      SERVO SERVO_CABIN_ALT_EXT(5); // Attached to pin D5
      int pos_servo_cabin_alt_ext = 20; // Posición del servo
      String valueDOLLARH; // Entrada de posición del servo
      int valueDOLLARHi = 0; // valueDOLLARH string convertido a integer

      SERVO SERVO_CABIN_ALT_INT(6); // Attached to pin D6
      int pos_servo_cabin_alt_int = 15; // Posición del servo
      String valueDOLLARG; // Entrada de posición del servo
      int valueDOLLARGi = 0; // valueDOLLARG string convertido a integer

      SERVO SERVO_CABIN_CLIMB(7); // Attached to pin D7
      int pos_servo_cabin_climb = 91; // Posición del servo
      String valueDOLLARI; // Entrada de posición del servo
      int valueDOLLARIi = 800; // valueDOLLARI string convertido a integer

 // *PANEL C5-1 VARIABLES*  

    // **SWITCHES**

      int PRE_SWITCH_VOICE_RECORDER = 0;
      
      int SWITCH_VOICE_RECORDER;


 // *PANEL C5-2 VARIABLES*

    // **LEDS**
      
      int valueFO = '0', valueFP = '0', valueFQ = '0';
      
    // **SWITCHES**

      int PRE_SELECTOR_AIR_TEMP = 0, PRE_SWITCH_TRIM_AIR = 1;
      
      int SELECTOR_AIR_TEMP_0, SELECTOR_AIR_TEMP_1, SELECTOR_AIR_TEMP_2, SELECTOR_AIR_TEMP_3, SELECTOR_AIR_TEMP_4, SELECTOR_AIR_TEMP_5, SELECTOR_AIR_TEMP_6;
      int SWITCH_TRIM_AIR;

    // **POTENCIOMETERS**
      
      const int POT_CONT_CAB = A2, POT_FWD_CAB = A3, POT_AFT_CAB = A4;  // Analog input pin that the potentiometer is attached to
      int pot_cont_cab_Aread, pot_fwd_cab_Aread, pot_aft_cab_Aread; // Actual value read from the pot
      int pot_cont_cab_Lastread, pot_fwd_cab_Lastread, pot_aft_cab_Lastread; // Last value read from the pot
      int pot_cont_cab_Avalue, pot_fwd_cab_Avalue, pot_aft_cab_Avalue; //Actual mapped value
      int pot_cont_cab_Lastvalue, pot_fwd_cab_Lastvalue, pot_aft_cab_Lastvalue; //Last mapped value

    // **SERVOS**

      SERVO SERVO_CAB_TEMP(8); // Attached to pin D8
      int pos_servo_cab_temp = 7; // Posición del servo
      String valueDOLLARD; // Entrada de posición del servo
      int valueDOLLARDi = 0; // valueDOLLARD string convertido a integer      

 // *PANEL C5-3 VARIABLES*

    // **LEDS**

      int valueFR = '0', valueFS = '1', valueFT = '1', valueFU = '0', valueFV = '0';
      int valueFW = '0', valueFX = '0', valueFY = '0', valueFZ = '0', valueGC = '1', valueGD = '0', valueGE = '0', valueGF = '0';

    // **SWITCHES**

      int PRE_SWITCH_RECIRC_FAN_L = 0, PRE_SWITCH_RECIRC_FAN_R = 0, PRE_BUTTON_OVHT_TEST = 0, PRE_SWITCH_ISOLATION_VALVE = 1, PRE_BUTTON_TRIP_RESET = 0;
      int PRE_SWITCH_PACK_L = 1, PRE_SWITCH_PACK_R = 1, PRE_SWITCH_BLEED_AIR_1 = 0, PRE_SWITCH_BLEED_AIR_2 = 0, PRE_SWITCH_APU_BLEED_AIR = 0;

      int SWITCH_RECIRC_FAN_L, SWITCH_RECIRC_FAN_R, BUTTON_OVHT_TEST, SWITCH_ISOLATION_VALVE_1, SWITCH_ISOLATION_VALVE_2, BUTTON_TRIP_RESET;
      int SWITCH_PACK_L_1, SWITCH_PACK_L_2, SWITCH_PACK_R_1, SWITCH_PACK_R_2, SWITCH_BLEED_AIR_1, SWITCH_BLEED_AIR_2, SWITCH_APU_BLEED_AIR;

    // **SHIFT REGISTERS (OUT)**

      int dataPin_OUT_19 = 43; //Pin connected to DS of SR_OUT_19
      int latchPin_OUT_19 = 44; //Pin connected to ST_CP of SR_OUT_19
      int clockPin_OUT_19 = 45; //Pin connected to SH_CP of SR_OUT_19
    
      byte SR_OUT_19; //Control LED state
      byte SR_OUT_20; //Control LED state
      byte SR_OUT_21; //Control LED state
      byte SR_OUT_22; //Control LED state

    // **SERVOS**

      SERVO SERVO_DUCT_PRESS_L(9); // Attached to pin D9
      int pos_servo_duct_press_l = 12; // Posición del servo
      String valueDOLLARE; // Entrada de posición del servo
      int valueDOLLAREi = 0; // valueDOLLARE string convertido a integer
      
      SERVO SERVO_DUCT_PRESS_R(10); // Attached to pin D9
      int pos_servo_duct_press_r = 12; // Posición del servo
      String valueDOLLARF; // Entrada de posición del servo
      int valueDOLLARFi = 0; // valueDOLLARF string convertido a integer 

 // *PANEL C5-4 VARIABLES*

    // **LEDS**

      String valueGG, valueGH; //Control LED numbers on the display, string value 
      long valueGGi = 10000, valueGHi = 50; //Control LED numbers on the display, integer value

      long display_num_6, display_num_7; //number shown in each digit
      int shift_number_6 [5]={}, shift_number_7 [5]={}; //number shifted in an array
      int neg_num_6=0, neg_num_7=0;
      int last_empty_digit_6 = 0, last_empty_digit_7 = 0;

    // **SWITCHES**

      int PRE_SELECTOR_PRESSURIZATION = 0, PRE_SWITCH_VALVE = 1;

      int SELECTOR_PRESSURIZATION_1, SELECTOR_PRESSURIZATION_2, SWITCH_VALVE_1, SWITCH_VALVE_2;

      const int ROTARY_FLT_ALT_A=48, ROTARY_FLT_ALT_B=49; 
      const int ROTARY_LAND_ALT_A=50, ROTARY_LAND_ALT_B=51; 
      
      int rotary_flt_alt_State, rotary_flt_alt_LastState;
      int rotary_land_alt_State, rotary_land_alt_LastState;  

    // **SERVOS**

      SERVO SERVO_MANUAL_VALVE(11); // Attached to pin D11
      int pos_servo_manual_valve = 165; // Posición del servo
      String pre_valueDOLLARJ;
      String valueDOLLARJ; // Entrada de posición del servo
      int valueDOLLARJi = 0; // valueDOLLARJ string convertido a integer      

  // *GENERIC VARIABLES*
    
    int LED_TEST = 0; // Light test Overhead Panel
    
    int ground_power = 0;
    int apu_power = 0;
    int eng_power = 0;
    int aircraft_energy = 0;
    
    int valueZb = '1', valueZc = '1';
    int prevalueZb = '1', prevalueZc = '1';
    
    int CodeIn; //Store read code

    unsigned long lastUpdateLED; // last update of LEDs state
    unsigned long lastUpdateSwitch; //last update of switches state
    unsigned long lastUpdateServo; //last update of switches state

    int flag_1 = 1;
    int flag_2 = 1;
    int flag_3 = 0;
    int flag_4 = 0;
    int flag_5 = 1;
    int flag_6 = 0;

    char incomingChar;
    int display_received = 1;
    
// END VARIABLES SECTION



// --- SETUP SECTION --- //

void setup() {

  // *SERIAL CONNECTION*
  
    Serial.begin(115200);


  // *PINS*

    // **PANEL C1-1, C1-2, C1-3, C1-4 PINS**
    
      pinMode(dataPin_OUT_1, OUTPUT);
      pinMode(latchPin_OUT_1, OUTPUT);
      pinMode(clockPin_OUT_1, OUTPUT);
    
      pinMode(ploadPin_IN_1, OUTPUT);
      pinMode(clockEnablePin_IN_1, OUTPUT);
      pinMode(clockPin_IN_1, OUTPUT);
      pinMode(dataPin_IN_1, INPUT);

    //  **PANEL C2-1, C2-2, C2-3, C2-4, C3-2 PINS**

      pinMode(dataPin_OUT_4, OUTPUT);
      pinMode(latchPin_OUT_4, OUTPUT);
      pinMode(clockPin_OUT_4, OUTPUT);
    
      pinMode(ploadPin_IN_8, OUTPUT);
      pinMode(clockEnablePin_IN_8, OUTPUT);
      pinMode(clockPin_IN_8, OUTPUT);
      pinMode(dataPin_IN_8, INPUT);

    //  **PANEL C4-1, C4-2, C4-3, C4-4, C4-5, C4-6, C5-1, C5-2, C5-3, C5-4 PINS**

      pinMode(dataPin_OUT_13, OUTPUT);
      pinMode(latchPin_OUT_13, OUTPUT);
      pinMode(clockPin_OUT_13, OUTPUT);
    
      pinMode(ploadPin_IN_15, OUTPUT);
      pinMode(clockEnablePin_IN_15, OUTPUT);
      pinMode(clockPin_IN_15, OUTPUT);
      pinMode(dataPin_IN_15, INPUT);

    //  **PANEL C5-3, C5-4 PINS**

      pinMode(dataPin_OUT_19, OUTPUT);
      pinMode(latchPin_OUT_19, OUTPUT);
      pinMode(clockPin_OUT_19, OUTPUT);             

      pinMode (ROTARY_FLT_ALT_A,INPUT); 
      pinMode (ROTARY_FLT_ALT_B,INPUT);
      pinMode (ROTARY_LAND_ALT_A,INPUT); 
      pinMode (ROTARY_LAND_ALT_B,INPUT);
  
    //  **GENERIC PINS**    


  // *COLD AND DARK SETUP*

    // **PANEL C1-1 COLD AND DARK**
      
      // ***SHIFT REGISTERS (OUT)***

        for (int i=0; i<8; i++){
          bitClear(SR_OUT_1,i);
          bitClear(SR_OUT_2,i);
          bitClear(SR_OUT_3,i);          
        }
      
        update_SR_OUT_1();
      
        digitalWrite(dataPin_OUT_1, LOW);
        digitalWrite(latchPin_OUT_1, LOW);
        digitalWrite(clockPin_OUT_1, LOW);

         
      // ***SHIFT REGISTERS (IN)***

        SR_IN_5 = update_SR_IN_5();  
        SR_IN_1 = update_SR_IN_1();  
        modify_switch_values_1();
        OLD_SR_IN_5 = SR_IN_5; 
        OLD_SR_IN_1 = SR_IN_1;

        digitalWrite(clockPin_IN_1, LOW);
        digitalWrite(ploadPin_IN_1, HIGH);

    // **PANEL C1-3 COLD AND DARK**

      // ***SERVOS***

        SERVO_FUEL_TEMP.Attach();
        SERVO_FUEL_TEMP.Update(0, 1);
        delay(500);
        SERVO_FUEL_TEMP.Detach();


    // **PANEL C1-4 COLD AND DARK**   

      // ***SERVOS***
        
        SERVO_SELECTOR_ENGINE_STARTOR.Attach();
        SERVO_SELECTOR_ENGINE_STARTOR.Update(0, 105);
        delay(500);
        SERVO_SELECTOR_ENGINE_STARTOR.Detach();

    
    // **PANEL C2-1 COLD AND DARK**              

      // ***SHIFT REGISTERS (OUT)***
      
        for (int i=0; i<8; i++){
          bitClear(SR_OUT_4,i);
          bitClear(SR_OUT_5,i);
          bitClear(SR_OUT_6,i);
          bitClear(SR_OUT_7,i);
          bitClear(SR_OUT_8,i);
          bitClear(SR_OUT_9,i);
          bitClear(SR_OUT_10,i);
          bitClear(SR_OUT_11,i);
          bitClear(SR_OUT_12,i);          
        }
      
        update_SR_OUT_4();
      
        digitalWrite(dataPin_OUT_4, LOW);
        digitalWrite(latchPin_OUT_4, LOW);
        digitalWrite(clockPin_OUT_4, LOW);

        updateDisplay_1();
        updateDisplay_2();
        updateDisplay_3();
        updateDisplay_4();
        updateDisplay_5();
         
      // ***SHIFT REGISTERS (IN)***

        SR_IN_12 = update_SR_IN_12();  
        SR_IN_8 = update_SR_IN_8();  
        modify_switch_values_8();
        OLD_SR_IN_12 = SR_IN_12; 
        OLD_SR_IN_8 = SR_IN_8;

        digitalWrite(clockPin_IN_8, LOW);
        digitalWrite(ploadPin_IN_8, HIGH);

    // **PANEL C2-4 COLD AND DARK** 
    
      // ***SERVOS***

        SERVO_EGT_APU.Attach();
        SERVO_EGT_APU.Update(0, 10);
        delay(500);
        SERVO_EGT_APU.Detach();

    // **PANEL C4-1 COLD AND DARK**                 

      // ***SHIFT REGISTERS (OUT)***
      
        for (int i=0; i<8; i++){
          bitClear(SR_OUT_13,i);
          bitClear(SR_OUT_14,i);
          bitClear(SR_OUT_15,i);
          bitClear(SR_OUT_16,i);
          bitClear(SR_OUT_17,i);
          bitClear(SR_OUT_18,i);          
        }
      
        update_SR_OUT_13();
      
        digitalWrite(dataPin_OUT_13, LOW);
        digitalWrite(latchPin_OUT_13, LOW);
        digitalWrite(clockPin_OUT_13, LOW);

         
      // ***SHIFT REGISTERS (IN)***

        SR_IN_19 = update_SR_IN_19();  
        SR_IN_15 = update_SR_IN_15();  
        modify_switch_values_15();
        OLD_SR_IN_19 = SR_IN_19; 
        OLD_SR_IN_15 = SR_IN_15;

        digitalWrite(clockPin_IN_15, LOW);
        digitalWrite(ploadPin_IN_15, HIGH);

    // **PANEL C4-6 COLD AND DARK**                 

      // ***SERVOS***

        SERVO_CABIN_ALT_EXT.Attach();
        SERVO_CABIN_ALT_EXT.Update(0, 20);
        delay(500);
        SERVO_CABIN_ALT_EXT.Detach();

        SERVO_CABIN_ALT_INT.Attach();
        SERVO_CABIN_ALT_INT.Update(0, 15);
        delay(500);
        SERVO_CABIN_ALT_INT.Detach();

        SERVO_CABIN_CLIMB.Attach();
        SERVO_CABIN_CLIMB.Update(0, 13);
        delay(500);
        SERVO_CABIN_CLIMB.Detach();              
        
    // **PANEL C5-2 COLD AND DARK**                 

      // ***POTENCIOMETERS***

        pot_cont_cab_Aread = analogRead(POT_CONT_CAB);
        pot_cont_cab_Lastread = pot_cont_cab_Aread;
        pot_cont_cab_Avalue = map(pot_cont_cab_Aread, 87, 1023, 0, 106); // map it to the range of the analog out
        pot_cont_cab_Lastvalue = pot_cont_cab_Avalue;

        pot_fwd_cab_Aread = analogRead(POT_FWD_CAB);
        pot_fwd_cab_Lastread = pot_fwd_cab_Aread;
        pot_fwd_cab_Avalue = map(pot_fwd_cab_Aread, 87, 1023, 0, 106); // map it to the range of the analog out
        pot_fwd_cab_Lastvalue = pot_fwd_cab_Avalue;
        
        pot_aft_cab_Aread = analogRead(POT_AFT_CAB);
        pot_aft_cab_Lastread = pot_aft_cab_Aread;
        pot_aft_cab_Avalue = map(pot_aft_cab_Aread, 87, 1023, 0, 106); // map it to the range of the analog out
        pot_aft_cab_Lastvalue = pot_aft_cab_Avalue;

      // ***SERVOS***

        SERVO_CAB_TEMP.Attach();
        SERVO_CAB_TEMP.Update(0, 7);
        delay(500);
        SERVO_CAB_TEMP.Detach();
        
    // **PANEL C5-3 COLD AND DARK**                 

      // ***SHIFT REGISTERS (OUT)***
      
        for (int i=0; i<8; i++){
          bitClear(SR_OUT_19,i);
          bitClear(SR_OUT_20,i);
          bitClear(SR_OUT_21,i);
          bitClear(SR_OUT_22,i);         
        }
      
        update_SR_OUT_19();
      
        digitalWrite(dataPin_OUT_19, LOW);
        digitalWrite(latchPin_OUT_19, LOW);
        digitalWrite(clockPin_OUT_19, LOW);

      // ***SERVOS***

        SERVO_DUCT_PRESS_L.Attach();
        SERVO_DUCT_PRESS_L.Update(0, 12);
        delay(500);
        SERVO_DUCT_PRESS_L.Detach();

        SERVO_DUCT_PRESS_R.Attach();
        SERVO_DUCT_PRESS_R.Update(0, 12);
        delay(500);
        SERVO_DUCT_PRESS_R.Detach();        

    // **PANEL C5-4 COLD AND DARK**

      // ***SHIFT REGISTERS (OUT)***

        updateDisplay_6();
        updateDisplay_7();

      // ***ROTARY ENCODER***     
      
        rotary_flt_alt_LastState = digitalRead(ROTARY_FLT_ALT_A); // Reads the initial state of the ROTARY_FLT_ALT_A
        rotary_land_alt_LastState = digitalRead(ROTARY_LAND_ALT_A); // Reads the initial state of the ROTARY_LAND_ALT_A

      // ***SERVOS***

        SERVO_MANUAL_VALVE.Attach();
        SERVO_MANUAL_VALVE.Update(0, 165);
        delay(500);
        SERVO_MANUAL_VALVE.Detach();                


} // END SETUP SECTION



// --- LOOP SECTION --- //

void loop() {

  // *LEDS*

    // **SERIAL DATA ACQUISITION**
    
      if (Serial.available()){
        
        CodeIn = getChar();

        if (CodeIn == 'B') {B();} //First identifier is B
        if (CodeIn == 'C') {C();} //First identifier is C        
        if (CodeIn == 'D') {D();} //First identifier is D
        if (CodeIn == 'E') {E();} //First identifier is E
        if (CodeIn == 'F') {EFE();} //First identifier is F
        if (CodeIn == 'G') {G();} //First identifier is G                
        if (CodeIn == 'Z') {Z();} //First identifier is Z
        if (CodeIn == '$') {DOLLAR();} //First identifier is $
        
      }
  
    // **LED TEST LOGIC**
    
      while( ((LED_TEST) == 1) && (aircraft_energy != 0) ){

        for (int i=0; i<8; i++){
          bitSet(SR_OUT_1,i);
          bitSet(SR_OUT_2,i);
          bitSet(SR_OUT_3,i);
          bitSet(SR_OUT_10,i);
          bitSet(SR_OUT_11,i);
          bitSet(SR_OUT_12,i);
          bitSet(SR_OUT_13,i);
          bitSet(SR_OUT_14,i);
          bitSet(SR_OUT_15,i);
          bitSet(SR_OUT_16,i);
          bitSet(SR_OUT_17,i);
          bitSet(SR_OUT_18,i);
          bitSet(SR_OUT_19,i);
          bitSet(SR_OUT_20,i);
          bitSet(SR_OUT_21,i);
          bitSet(SR_OUT_22,i);             
        }

        bitClear(SR_OUT_20,7); //Digit 1 FLT ALT
        bitClear(SR_OUT_21,0); //Digit 2 FLT ALT
        bitClear(SR_OUT_21,1); //Digit 3 FLT ALT
        bitClear(SR_OUT_21,2); //Digit 4 FLT ALT
        bitClear(SR_OUT_21,3); //Digit 5 FLT ALT
        bitClear(SR_OUT_22,3); //Digit 1 LAND ALT
        bitClear(SR_OUT_22,4); //Digit 2 LAND ALT
        bitClear(SR_OUT_22,5); //Digit 3 LAND ALT
        bitClear(SR_OUT_22,6); //Digit 4 LAND ALT
        bitClear(SR_OUT_22,7); //Digit 5 LAND ALT

        refreshDisplay_1();

        update_SR_OUT_1();
        update_SR_OUT_4();
        update_SR_OUT_13();
        update_SR_OUT_19();
        
        SR_IN_19 = update_SR_IN_19();  
        SR_IN_15 = update_SR_IN_15();      
      
        if( (SR_IN_15 != OLD_SR_IN_15) || (SR_IN_19 != OLD_SR_IN_19) ){
          
          modify_switch_values_15();
          OLD_SR_IN_19 = SR_IN_19;
          OLD_SR_IN_15 = SR_IN_15;    
          
        }        
        
      }
    
      if((LED_TEST) == 0){
         
        // ***PANEL C1-1***
        
          if(valueBU == '0') {bitClear(SR_OUT_1,0);}
          if(valueBV == '0') {bitClear(SR_OUT_1,1);}
          if(valueBW == '0') {bitClear(SR_OUT_1,2);}
          if(valueBX == '0') {bitClear(SR_OUT_1,3);}
          if(valueBY == '0') {bitClear(SR_OUT_1,4);}
          if(valueBZ == '0') {bitClear(SR_OUT_1,5);}
          if(valueCA == '0') {bitClear(SR_OUT_1,6);}
          if(valueCB == '0') {bitClear(SR_OUT_1,7);}
          if(valueCC == '0') {bitClear(SR_OUT_2,0);}
          if(valueCE == '0') {bitClear(SR_OUT_2,1);}

        // ***PANEL C1-3***
        
          if(valueCF == '0') {bitClear(SR_OUT_2,2);}
          if(valueCG == '0') {bitClear(SR_OUT_2,3);}
          if(valueCH == '0') {bitClear(SR_OUT_2,4);}
          if(valueCI == '0') {bitClear(SR_OUT_2,5);}
          if(valueCJ == '0') {bitClear(SR_OUT_2,6);}
          if(valueCK == '0') {bitClear(SR_OUT_2,7);}
          if(valueCL == '0') {bitClear(SR_OUT_3,0);}
          if(valueCM == '0') {bitClear(SR_OUT_3,1);}
          if(valueCN == '0') {bitClear(SR_OUT_3,2);}
          if(valueCO == '0') {bitClear(SR_OUT_3,3);}
          if(valueCP == '0') {bitClear(SR_OUT_3,4);}
          if(valueCQ == '0') {bitClear(SR_OUT_3,5);}
          if(valueCR == '0') {bitClear(SR_OUT_3,6);}
          
        // ***PANEL C2-1***

          if(valueCY == '0') {bitClear(SR_OUT_10,1);}
          if(valueCZ == '0') {bitClear(SR_OUT_10,2);}
          if(valueDA == '0') {bitClear(SR_OUT_10,3);}
        
        // ***PANEL C2-2***

          if(valueDB == '0') {bitClear(SR_OUT_10,4);}
          if(valueDC == '0') {bitClear(SR_OUT_10,5);}
          if(valueDD == '0') {bitClear(SR_OUT_10,6);}

        // ***PANEL C2-3***

          if(valueDE == '0') {bitClear(SR_OUT_10,7);}
          if(valueDF == '0') {bitClear(SR_OUT_11,0);}
          if(valueDG == '0') {bitClear(SR_OUT_11,1);}
          if(valueDH == '0') {bitClear(SR_OUT_11,2);}
          if(valueDI == '0') {bitClear(SR_OUT_11,3);}
          if(valueDJ == '0') {bitClear(SR_OUT_11,4);}
          if(valueDK == '0') {bitClear(SR_OUT_11,5);}
          if(valueDL == '0') {bitClear(SR_OUT_11,6);}  

        // ***PANEL C2-4***

          if(valueDM == '0') {bitClear(SR_OUT_11,7);}
          if(valueDN == '0') {bitClear(SR_OUT_12,0);}
          if(valueDO == '0') {bitClear(SR_OUT_12,1);}
          if(valueDP == '0') {bitClear(SR_OUT_12,2);}

        // ***PANEL C3-2***

          if(valueDR == '0') {bitClear(SR_OUT_12,3);}
          if(valueDS == '0') {bitClear(SR_OUT_12,4);}
          if(valueDT == '0') {bitClear(SR_OUT_12,5);}
          if(valueDU == '0') {bitClear(SR_OUT_12,6);}

        // ***PANEL C4-1***

          if(valueDW == '0') {bitClear(SR_OUT_13,0);}
          if(valueDX == '0') {bitClear(SR_OUT_13,1);}
          if(valueDY == '0') {bitClear(SR_OUT_13,2);}
          if(valueDZ == '0') {bitClear(SR_OUT_13,3);}
          if(valueEA == '0') {bitClear(SR_OUT_13,4);}
          if(valueEB == '0') {bitClear(SR_OUT_13,5);}
          if(valueEC == '0') {bitClear(SR_OUT_13,6);}
          if(valueED == '0') {bitClear(SR_OUT_13,7);}
          if(valueEE == '0') {bitClear(SR_OUT_14,0);}
          if(valueEF == '0') {bitClear(SR_OUT_14,1);}
          if(valueEG == '0') {bitClear(SR_OUT_14,2);}
          if(valueEH == '0') {bitClear(SR_OUT_14,3);}
          if(valueEI == '0') {bitClear(SR_OUT_14,4);}
          if(valueEJ == '0') {bitClear(SR_OUT_14,5);}
          if(valueEK == '0') {bitClear(SR_OUT_14,6);}
          if(valueEL == '0') {bitClear(SR_OUT_14,7);}

        // ***PANEL C4-2***

          if(valueEQ == '0') {bitClear(SR_OUT_15,0);}
          if(valueER == '0') {bitClear(SR_OUT_15,1);}
          if(valueEM == '0') {bitClear(SR_OUT_15,2);}
          if(valueEN == '0') {bitClear(SR_OUT_15,3);}
          if(valueEO == '0') {bitClear(SR_OUT_15,4);}
          if(valueEP == '0') {bitClear(SR_OUT_15,5);}

        // ***PANEL C4-3***

          if(valueES == '0') {bitClear(SR_OUT_15,6);}
          if(valueET == '0') {bitClear(SR_OUT_15,7);}
          if(valueEU == '0') {bitClear(SR_OUT_16,0);}
          if(valueEV == '0') {bitClear(SR_OUT_16,1);}
          if(valueEW == '0') {bitClear(SR_OUT_16,3);}
          if(valueEX == '0') {bitClear(SR_OUT_16,2);}


        // ***PANEL C4-4***

          if(valueEY == '0') {bitClear(SR_OUT_16,4);}
          if(valueEZ == '0') {bitClear(SR_OUT_16,5);}
          if(valueFB == '0') {bitClear(SR_OUT_16,6);}
          if(valueFC == '0') {bitClear(SR_OUT_16,7);}
          if(valueFD == '0') {bitClear(SR_OUT_17,0);}
          if(valueFE == '0') {bitClear(SR_OUT_17,1);}
          if(valueFF == '0') {bitClear(SR_OUT_17,2);}
          if(valueFG == '0') {bitClear(SR_OUT_17,3);}
          if(valueFH == '0') {bitClear(SR_OUT_17,4);}
          if(valueFI == '0') {bitClear(SR_OUT_17,5);}
          if(valueFJ == '0') {bitClear(SR_OUT_17,6);}

        // ***PANEL C4-5***

          if(valueZZ == '0') {bitClear(SR_OUT_17,7);}

        // ***PANEL C5-2***

          if(valueFO == '0') {bitClear(SR_OUT_18,0);}
          if(valueFP == '0') {bitClear(SR_OUT_18,1);}
          if(valueFQ == '0') {bitClear(SR_OUT_18,2);}

        // ***PANEL C5-3***

          if(valueFR == '0') {bitClear(SR_OUT_18,3);}
          if(valueFS == '0') {bitClear(SR_OUT_18,4);}
          if(valueFT == '0') {bitClear(SR_OUT_18,5);}
          if(valueFU == '0') {bitClear(SR_OUT_18,6);}
          if(valueFV == '0') {bitClear(SR_OUT_18,7);}
          if(valueFW == '0') {bitClear(SR_OUT_19,0);}
          if(valueFX == '0') {bitClear(SR_OUT_19,1);}
          if(valueFY == '0') {bitClear(SR_OUT_19,2);}
          if(valueFZ == '0') {bitClear(SR_OUT_19,3);}
          if(valueGC == '0') {bitClear(SR_OUT_19,4);}
          if(valueGD == '0') {bitClear(SR_OUT_19,5);}
          if(valueGE == '0') {bitClear(SR_OUT_19,6);}
          if(valueGF == '0') {bitClear(SR_OUT_19,7);}                                                                                
                   
        update_SR_OUT_1();
        update_SR_OUT_4();
        update_SR_OUT_13();
        update_SR_OUT_19();
      
      }

    // **LED ENERGY LOGIC**
      
      if(aircraft_energy == 0){

        // ***PANEL C1-1, C1-3***
    
          for (int i=0; i<8; i++){
            bitClear(SR_OUT_1,i);
            bitClear(SR_OUT_2,i);
            bitClear(SR_OUT_3,i);
          }
          
          update_SR_OUT_1();

          servo_activated_1 = 0;

          flag_1 = 1;
        
        // ***PANEL C2-1***

          for (int i=0; i<8; i++){
            bitClear(SR_OUT_10,i);
            bitClear(SR_OUT_11,i);
            bitClear(SR_OUT_12,i);
          }

          bitSet(SR_OUT_4,7); //Digit 1 DC AMPS
          bitSet(SR_OUT_5,0); //Digit 2 DC AMPS
          bitSet(SR_OUT_5,1); //Digit 3 DC AMPS
          bitSet(SR_OUT_6,1); //Digit 1 CPRS FREQ
          bitSet(SR_OUT_6,2); //Digit 2 CPRS FREQ
          bitSet(SR_OUT_6,3); //Digit 2 CPRS FREQ
          bitSet(SR_OUT_7,3); //Digit 1 DC VOLTS
          bitSet(SR_OUT_7,4); //Digit 2 DC VOLTS
          bitSet(SR_OUT_8,4); //Digit 1 AC AMPS
          bitSet(SR_OUT_8,5); //Digit 2 AC AMPS
          bitSet(SR_OUT_8,6); //Digit 3 AC AMPS
          bitSet(SR_OUT_9,6); //Digit 1 AC VOLTS
          bitSet(SR_OUT_9,7); //Digit 2 AC VOLTS
          bitSet(SR_OUT_10,0); //Digit 3 AC VOLTS
          
          update_SR_OUT_4();

        // ***PANEL C2-4***
        
          servo_activated_2 = 0;

        // ***PANEL C4-1***

          for (int i=0; i<8; i++){
            bitClear(SR_OUT_10,i);
            bitClear(SR_OUT_11,i);
            bitClear(SR_OUT_12,i);
            bitClear(SR_OUT_13,i);
            bitClear(SR_OUT_14,i);
            bitClear(SR_OUT_15,i);
            bitClear(SR_OUT_16,i);
            bitClear(SR_OUT_17,i);
            bitClear(SR_OUT_18,i);
          }
                            
          update_SR_OUT_13();

        // ***PANEL C4-6***

          flag_2 = 1;

          if(flag_4 == 1){
            flag_4 = 0;
            SERVO_CABIN_CLIMB.Attach();
            SERVO_CABIN_CLIMB.Update(0, 13);
            delay(500);
            SERVO_CABIN_CLIMB.Detach();        
          }

        // ***PANEL C5-2***

          flag_5 = 1;
        
        // ***PANEL C5-3***

          for (int i=0; i<8; i++){
            bitClear(SR_OUT_19,i);
          }

          bitSet(SR_OUT_20,7); //Digit 1 FLT ALT
          bitSet(SR_OUT_21,0); //Digit 2 FLT ALT
          bitSet(SR_OUT_21,1); //Digit 3 FLT ALT
          bitSet(SR_OUT_21,2); //Digit 4 FLT ALT
          bitSet(SR_OUT_21,3); //Digit 5 FLT ALT
          bitSet(SR_OUT_22,3); //Digit 1 LAND ALT 
          bitSet(SR_OUT_22,4); //Digit 2 LAND ALT
          bitSet(SR_OUT_22,5); //Digit 3 LAND ALT
          bitSet(SR_OUT_22,6); //Digit 4 LAND ALT
          bitSet(SR_OUT_22,7); //Digit 5 LAND ALT
          
          update_SR_OUT_19();
          
      }
    
      if(aircraft_energy == 1){

        // ***PANEL C1-1***
         
          for (int i=0; i<8; i++){
            bitClear(SR_OUT_1,i);
          }

          for (int i=0; i<2; i++){
            bitClear(SR_OUT_2,i);
          }
        
        // ***PANEL C1-3***

          bitSet(SR_OUT_2,2);
          bitSet(SR_OUT_2,3);
          bitSet(SR_OUT_2,4);
          bitSet(SR_OUT_2,5);
          bitSet(SR_OUT_3,3);
          bitSet(SR_OUT_3,4);
          bitSet(SR_OUT_3,5);
          bitSet(SR_OUT_3,6);       

          update_SR_OUT_1();

          servo_activated_1 = 0;

          flag_1 = 1;

          if(flag_3 == 1){
            flag_3 = 0;
            SERVO_FUEL_TEMP.Attach();
            SERVO_FUEL_TEMP.Update(0, 1);
            lastUpdateServo = millis();
          }
          
        // ***PANEL C2-2***

          bitClear(SR_OUT_10,4);
          
        // ***PANEL C2-3***
          
          bitSet(SR_OUT_11,0);
          bitSet(SR_OUT_11,1);
          bitSet(SR_OUT_11,2);
          bitSet(SR_OUT_11,3);
          bitSet(SR_OUT_11,4);
          bitSet(SR_OUT_11,5);
          
          update_SR_OUT_4();

        // ***PANEL C2-4***
        
          servo_activated_2 = 1;
        
        // ***PANEL C4-1***

          bitSet(SR_OUT_14,0);
          bitSet(SR_OUT_14,1);
          bitSet(SR_OUT_14,2);
          bitSet(SR_OUT_14,3);

        // ***PANEL C4-3***

          bitSet(SR_OUT_16,0);
          bitSet(SR_OUT_16,1);
          bitSet(SR_OUT_16,2);
          bitSet(SR_OUT_16,3);

        // ***PANEL C4-3***

          bitSet(SR_OUT_16,4);

        // ***PANEL C4-6***

          flag_2 = 1;

        // ***PANEL C5-2***
          
          flag_5 = 1;

          if(flag_6 == 1){
            flag_6 = 0;
            SERVO_CAB_TEMP.Attach();
            SERVO_CAB_TEMP.Update(0, 7);
            lastUpdateServo = millis();
          }

        // ***PANEL C5-3***

          bitSet(SR_OUT_19,4);

          update_SR_OUT_13();

        // ***PANEL C5-4***

          bitClear(SR_OUT_20,7); //Digit 1 FLT ALT
          bitClear(SR_OUT_21,0); //Digit 2 FLT ALT
          bitClear(SR_OUT_21,1); //Digit 3 FLT ALT
          bitClear(SR_OUT_21,2); //Digit 4 FLT ALT
          bitClear(SR_OUT_21,3); //Digit 5 FLT ALT
          bitClear(SR_OUT_22,3); //Digit 1 LAND ALT
          bitClear(SR_OUT_22,4); //Digit 2 LAND ALT
          bitClear(SR_OUT_22,5); //Digit 3 LAND ALT
          bitClear(SR_OUT_22,6); //Digit 4 LAND ALT
          bitClear(SR_OUT_22,7); //Digit 5 LAND ALT

          bitClear(SR_OUT_20,0); // A segment
          bitClear(SR_OUT_20,1); // B segment
          bitClear(SR_OUT_20,2); // C segment
          bitClear(SR_OUT_20,3); // D segment
          bitClear(SR_OUT_20,4); // E segment
          bitClear(SR_OUT_20,5); // F segment
          bitSet(SR_OUT_20,6); // G segment

          bitClear(SR_OUT_21,4); // A segment
          bitClear(SR_OUT_21,5); // B segment
          bitClear(SR_OUT_21,6); // C segment
          bitClear(SR_OUT_21,7); // D segment
          bitClear(SR_OUT_22,0); // E segment
          bitClear(SR_OUT_22,1); // F segment
          bitSet(SR_OUT_22,2); // G segment 

          update_SR_OUT_19(); 
             
      }   
    
      if(aircraft_energy == 2){

        // ***PANEL C1-1***
        
          if(valueBX == '1') {bitSet(SR_OUT_1,3);}
          if(valueBY == '1') {bitSet(SR_OUT_1,4);}
          if(valueCE == '1') {bitSet(SR_OUT_2,1);}
          bitClear(SR_OUT_1,6);
          bitClear(SR_OUT_1,7);
      
        // ***PANEL C1-3***

          if(valueCF == '1') {bitSet(SR_OUT_2,2);}
          if(valueCG == '1') {bitSet(SR_OUT_2,3);}
          if(valueCH == '1') {bitSet(SR_OUT_2,4);}
          if(valueCI == '1') {bitSet(SR_OUT_2,5);}
          if(valueCO == '1') {bitSet(SR_OUT_3,3);}
          if(valueCP == '1') {bitSet(SR_OUT_3,4);}
          if(valueCQ == '1') {bitSet(SR_OUT_3,5);}
          if(valueCR == '1') {bitSet(SR_OUT_3,6);}

          update_SR_OUT_1();

          servo_activated_1 = 1;

          if(flag_1 == 1){
            flag_1 = 0;
            flag_3 = 1;
            SERVO_FUEL_TEMP.Attach();
            SERVO_FUEL_TEMP.Update(0, 120);
            lastUpdateServo = millis();
          }

          
        // ***PANEL C2-1***

          bitClear(SR_OUT_10,1);

        // ***PANEL C2-2***
        
          bitClear(SR_OUT_10,4);

        // ***PANEL C2-3***
        
          bitClear(SR_OUT_11,0);
          bitClear(SR_OUT_11,1);
          bitClear(SR_OUT_11,2);
          bitClear(SR_OUT_11,3);  
          
          update_SR_OUT_4();

        // ***PANEL C4-1***

          if(SWITCH_PROBE_HEAT_A == 1){bitSet(SR_OUT_14,0);}
          if(SWITCH_PROBE_HEAT_A == 1){bitSet(SR_OUT_14,1);}
          if(SWITCH_PROBE_HEAT_A == 1){bitSet(SR_OUT_14,2);}
          if(SWITCH_PROBE_HEAT_A == 1){bitSet(SR_OUT_14,3);}
          if(SWITCH_PROBE_HEAT_B == 1){bitSet(SR_OUT_14,4);}
          if(SWITCH_PROBE_HEAT_B == 1){bitSet(SR_OUT_14,5);}
          if(SWITCH_PROBE_HEAT_B == 1){bitSet(SR_OUT_14,6);}
          if(SWITCH_PROBE_HEAT_B == 1){bitSet(SR_OUT_14,7);}
          
          if(SWITCH_PROBE_HEAT_A == 0){bitClear(SR_OUT_14,0);}
          if(SWITCH_PROBE_HEAT_A == 0){bitClear(SR_OUT_14,1);}
          if(SWITCH_PROBE_HEAT_A == 0){bitClear(SR_OUT_14,2);}
          if(SWITCH_PROBE_HEAT_A == 0){bitClear(SR_OUT_14,3);}
          if(SWITCH_PROBE_HEAT_B == 0){bitClear(SR_OUT_14,4);}
          if(SWITCH_PROBE_HEAT_B == 0){bitClear(SR_OUT_14,5);}
          if(SWITCH_PROBE_HEAT_B == 0){bitClear(SR_OUT_14,6);}
          if(SWITCH_PROBE_HEAT_B == 0){bitClear(SR_OUT_14,7);}

        // ***PANEL C4-6***
        
          if(flag_2 == 1){
            flag_2 = 0;
            flag_4 = 1;
            SERVO_CABIN_CLIMB.Attach();
            SERVO_CABIN_CLIMB.Update(0, 91);
            lastUpdateServo = millis();
          }

        // ***PANEL C5-2***
          
          if(flag_5 == 1){
            flag_5 = 0;
            flag_6 = 1;
            SERVO_CAB_TEMP.Attach();
            SERVO_CAB_TEMP.Update(0, 50);
            lastUpdateServo = millis();
          }

        // ***PANEL C5-3***
        
          if(valueFS == '1'){bitSet(SR_OUT_18,4);}
          if(valueFT == '1'){bitSet(SR_OUT_18,5);}     

          bitClear(SR_OUT_19,4);
          
          update_SR_OUT_13();
          update_SR_OUT_19();
           
      }  
    
      if(aircraft_energy == 3){
    
        // ***PANEL C1-1***
        
          if(valueBX == '1') {bitSet(SR_OUT_1,3);}
          if(valueBY == '1') {bitSet(SR_OUT_1,4);}
          if(valueCE == '1') {bitSet(SR_OUT_2,1);}

        // ***PANEL C1-3***

          bitClear(SR_OUT_2,2);
          bitClear(SR_OUT_2,3);
          bitClear(SR_OUT_2,4);
          bitClear(SR_OUT_2,5);
          
          update_SR_OUT_1();

        // ***PANEL C2-1***          

          bitSet(SR_OUT_4,7); //Digit 1 DC AMPS
          bitSet(SR_OUT_5,0); //Digit 2 DC AMPS
          bitSet(SR_OUT_5,1); //Digit 3 DC AMPS
          bitSet(SR_OUT_6,1); //Digit 1 CPRS FREQ
          bitSet(SR_OUT_6,2); //Digit 2 CPRS FREQ
          bitSet(SR_OUT_6,3); //Digit 2 CPRS FREQ
          bitSet(SR_OUT_7,3); //Digit 1 DC VOLTS
          bitSet(SR_OUT_7,4); //Digit 2 DC VOLTS
          bitSet(SR_OUT_8,4); //Digit 1 AC AMPS
          bitSet(SR_OUT_8,5); //Digit 2 AC AMPS
          bitSet(SR_OUT_8,6); //Digit 3 AC AMPS
          bitSet(SR_OUT_9,6); //Digit 1 AC VOLTS
          bitSet(SR_OUT_9,7); //Digit 2 AC VOLTS
          bitSet(SR_OUT_10,0); //Digit 3 AC VOLTS
        
        // ***PANEL C3-2***

          bitClear(SR_OUT_12,5);
          
          update_SR_OUT_4();

        // ***PANEL C5-4***            
          
          bitSet(SR_OUT_20,7); //Digit 1 FLT ALT
          bitSet(SR_OUT_21,0); //Digit 2 FLT ALT
          bitSet(SR_OUT_21,1); //Digit 3 FLT ALT
          bitSet(SR_OUT_21,2); //Digit 4 FLT ALT
          bitSet(SR_OUT_21,3); //Digit 5 FLT ALT
          bitSet(SR_OUT_22,3); //Digit 1 LAND ALT
          bitSet(SR_OUT_22,4); //Digit 2 LAND ALT
          bitSet(SR_OUT_22,5); //Digit 3 LAND ALT
          bitSet(SR_OUT_22,6); //Digit 4 LAND ALT
          bitSet(SR_OUT_22,7); //Digit 5 LAND ALT
      }

      if(aircraft_energy == 4 || aircraft_energy == 5 ){
        
        // ***PANEL C4-1***          
         
          if(SWITCH_PROBE_HEAT_A == 0){bitClear(SR_OUT_14,2);}
          
          update_SR_OUT_13();
      }

    // DISPLAY LEDS
 
      if(aircraft_energy != 0 && aircraft_energy != 3){  
        refreshDisplay_1();
      }
      if(aircraft_energy >= 2 && aircraft_energy != 3){  
        refreshDisplay_2();
      }  
      
    // **CIRCUIT BREAKER BACKLIT**

      pot_circuit_breaker_value = analogRead(POT_CIRCUIT_BREAKER); // read the analog in value
    
    // **PANEL BACKLIT**

      pot_panel_value = analogRead(POT_PANEL); // read the analog in value
      led_backlight_value = map(pot_panel_value, 0, 1023, 0, 255); // map it to the range of the analog out

      if(aircraft_energy >= 2){
        analogWrite(LED_BACKLIGHT, led_backlight_value); // change the analog out value
      }
      
      delay(2); // wait 2 milliseconds before the next loop for the analog-to-digital converter to settle after the last reading
    
  // *SWITCHES*

    // **PANEL C1-1 SWITCHES**
    
      // ***SHIFT REGISTERS (IN)***
      
        SR_IN_5 = update_SR_IN_5();  
        SR_IN_1 = update_SR_IN_1();      
      
        if( (SR_IN_1 != OLD_SR_IN_1) || (SR_IN_5 != OLD_SR_IN_5) ){
          
          modify_switch_values_1();
          OLD_SR_IN_5 = SR_IN_5;
          OLD_SR_IN_1 = SR_IN_1;    
          
        }

        SR_IN_12 = update_SR_IN_12();  
        SR_IN_8 = update_SR_IN_8();      
      
        if( (SR_IN_8 != OLD_SR_IN_8) || (SR_IN_12 != OLD_SR_IN_12) ){
          
          modify_switch_values_8();
          OLD_SR_IN_12 = SR_IN_12;
          OLD_SR_IN_8 = SR_IN_8;    
          
        }

        SR_IN_19 = update_SR_IN_19();  
        SR_IN_15 = update_SR_IN_15();      
      
        if( (SR_IN_15 != OLD_SR_IN_15) || (SR_IN_19 != OLD_SR_IN_19) ){
          
          modify_switch_values_15();
          OLD_SR_IN_19 = SR_IN_19;
          OLD_SR_IN_15 = SR_IN_15;    
          
        }        
        
      // ***SWITCHES LOGIC***
      
        if( ((SWITCH_YAW_DAMPER) == 1) && (PRE_SWITCH_YAW_DAMPER == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HY0"); PRE_SWITCH_YAW_DAMPER = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_YAW_DAMPER) == 0) && (PRE_SWITCH_YAW_DAMPER == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HY1"); PRE_SWITCH_YAW_DAMPER = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_SPOILER_A) == 1) && (PRE_SWITCH_SPOILER_A == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HW0"); PRE_SWITCH_SPOILER_A = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_SPOILER_A) == 0) && (PRE_SWITCH_SPOILER_A == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HW1"); PRE_SWITCH_SPOILER_A = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_SPOILER_B) == 1) && (PRE_SWITCH_SPOILER_B == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HX0"); PRE_SWITCH_SPOILER_B = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_SPOILER_B) == 0) && (PRE_SWITCH_SPOILER_B == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HX1"); PRE_SWITCH_SPOILER_B = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_ALTERNATE_FLAPS) == 1) && (PRE_SWITCH_ALTERNATE_FLAPS == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HU0"); PRE_SWITCH_ALTERNATE_FLAPS = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_ALTERNATE_FLAPS) == 0) && (PRE_SWITCH_ALTERNATE_FLAPS == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HU1"); PRE_SWITCH_ALTERNATE_FLAPS = 0; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_STBY_RUD_A1) == 0) && (SWITCH_STBY_RUD_A2) == 1 && (PRE_SWITCH_STBY_RUD_A == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HS0"); PRE_SWITCH_STBY_RUD_A = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_STBY_RUD_A1) == 0) && (SWITCH_STBY_RUD_A2) == 0 && ( (PRE_SWITCH_STBY_RUD_A == 0) || (PRE_SWITCH_STBY_RUD_A == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HS1"); PRE_SWITCH_STBY_RUD_A = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_STBY_RUD_A1) == 1) && (SWITCH_STBY_RUD_A2) == 0 && (PRE_SWITCH_STBY_RUD_A == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HS2"); PRE_SWITCH_STBY_RUD_A = 2; lastUpdateSwitch = millis();} }
        
        if( ((SWITCH_STBY_RUD_B1) == 0) && (SWITCH_STBY_RUD_B2) == 1 && (PRE_SWITCH_STBY_RUD_B == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HT0"); PRE_SWITCH_STBY_RUD_B = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_STBY_RUD_B1) == 0) && (SWITCH_STBY_RUD_B2) == 0 && ( (PRE_SWITCH_STBY_RUD_B == 0) || (PRE_SWITCH_STBY_RUD_B == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HT1"); PRE_SWITCH_STBY_RUD_B = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_STBY_RUD_B1) == 1) && (SWITCH_STBY_RUD_B2) == 0 && (PRE_SWITCH_STBY_RUD_B == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HT2"); PRE_SWITCH_STBY_RUD_B = 2; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_FLAPS_POS_1) == 0) && (SWITCH_FLAPS_POS_2) == 1 && (PRE_SWITCH_FLAPS_POS == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HV0"); PRE_SWITCH_FLAPS_POS = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_FLAPS_POS_1) == 0) && (SWITCH_FLAPS_POS_2) == 0 && ( (PRE_SWITCH_FLAPS_POS == 0) || (PRE_SWITCH_FLAPS_POS == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HV1"); PRE_SWITCH_FLAPS_POS = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_FLAPS_POS_1) == 1) && (SWITCH_FLAPS_POS_2) == 0 && (PRE_SWITCH_FLAPS_POS == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HV2"); PRE_SWITCH_FLAPS_POS = 2; lastUpdateSwitch = millis();} }


    // **PANEL C1-2 SWITCHES**
    
      // ***SWITCHES LOGIC***

        if( ((SWITCH_VHF_NAVIGATION_1) == 0) && (SWITCH_VHF_NAVIGATION_2) == 1 && (PRE_SWITCH_VHF_NAVIGATION == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HZ0"); PRE_SWITCH_VHF_NAVIGATION = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_VHF_NAVIGATION_1) == 0) && (SWITCH_VHF_NAVIGATION_2) == 0 && ( (PRE_SWITCH_VHF_NAVIGATION == 0) || (PRE_SWITCH_VHF_NAVIGATION == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HZ1"); PRE_SWITCH_VHF_NAVIGATION = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_VHF_NAVIGATION_1) == 1) && (SWITCH_VHF_NAVIGATION_2) == 0 && (PRE_SWITCH_VHF_NAVIGATION == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("HZ2"); PRE_SWITCH_VHF_NAVIGATION = 2; lastUpdateSwitch = millis();} }
        
        if( ((SWITCH_IRS_SELECTOR_1) == 0) && (SWITCH_IRS_SELECTOR_2) == 1 && (PRE_SWITCH_IRS_SELECTOR == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IA0"); PRE_SWITCH_IRS_SELECTOR = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_IRS_SELECTOR_1) == 0) && (SWITCH_IRS_SELECTOR_2) == 0 && ( (PRE_SWITCH_IRS_SELECTOR == 0) || (PRE_SWITCH_IRS_SELECTOR == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IA1"); PRE_SWITCH_IRS_SELECTOR = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_IRS_SELECTOR_1) == 1) && (SWITCH_IRS_SELECTOR_2) == 0 && (PRE_SWITCH_IRS_SELECTOR == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IA2"); PRE_SWITCH_IRS_SELECTOR = 2; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_FMC_1) == 0) && (SWITCH_FMC_2) == 1 && (PRE_SWITCH_FMC == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IB0"); PRE_SWITCH_FMC = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_FMC_1) == 0) && (SWITCH_FMC_2) == 0 && ( (PRE_SWITCH_FMC == 0) || (PRE_SWITCH_FMC == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IB1"); PRE_SWITCH_FMC = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_FMC_1) == 1) && (SWITCH_FMC_2) == 0 && (PRE_SWITCH_FMC == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IB2"); PRE_SWITCH_FMC = 2; lastUpdateSwitch = millis();} }
      
        if( ((SELECTOR_DISPLAY_SOURCE_1) == 1) && (SELECTOR_DISPLAY_SOURCE_2) == 0 && (PRE_SELECTOR_DISPLAY_SOURCE == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IC0"); PRE_SELECTOR_DISPLAY_SOURCE = 2; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_DISPLAY_SOURCE_1) == 0) && (SELECTOR_DISPLAY_SOURCE_2) == 0 && ( (PRE_SELECTOR_DISPLAY_SOURCE == 0) || (PRE_SELECTOR_DISPLAY_SOURCE == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IC1"); PRE_SELECTOR_DISPLAY_SOURCE = 1; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_DISPLAY_SOURCE_1) == 0) && (SELECTOR_DISPLAY_SOURCE_2) == 1 && (PRE_SELECTOR_DISPLAY_SOURCE == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IC2"); PRE_SELECTOR_DISPLAY_SOURCE = 0; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_CONTROL_PANEL_1) == 0) && (SWITCH_CONTROL_PANEL_2) == 1 && (PRE_SWITCH_CONTROL_PANEL == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("ID0"); PRE_SWITCH_CONTROL_PANEL = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_CONTROL_PANEL_1) == 0) && (SWITCH_CONTROL_PANEL_2) == 0 && ( (PRE_SWITCH_CONTROL_PANEL == 0) || (PRE_SWITCH_CONTROL_PANEL == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("ID1"); PRE_SWITCH_CONTROL_PANEL = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_CONTROL_PANEL_1) == 1) && (SWITCH_CONTROL_PANEL_2) == 0 && (PRE_SWITCH_CONTROL_PANEL == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("ID2"); PRE_SWITCH_CONTROL_PANEL = 2; lastUpdateSwitch = millis();} }


    // **PANEL C1-3 SWITCHES**

      // ***SWITCHES LOGIC***
      
        if( ((SWITCH_CROSS_FEED) == 1) && (PRE_SWITCH_CROSS_FEED == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IE0"); PRE_SWITCH_CROSS_FEED = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_CROSS_FEED) == 0) && (PRE_SWITCH_CROSS_FEED == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IE1"); PRE_SWITCH_CROSS_FEED = 0; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_FUEL_PUMPS_A) == 1) && (PRE_SWITCH_FUEL_PUMPS_A == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IF0"); PRE_SWITCH_FUEL_PUMPS_A = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_FUEL_PUMPS_A) == 0) && (PRE_SWITCH_FUEL_PUMPS_A == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IF1"); PRE_SWITCH_FUEL_PUMPS_A = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_FUEL_PUMPS_B) == 1) && (PRE_SWITCH_FUEL_PUMPS_B == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IG0"); PRE_SWITCH_FUEL_PUMPS_B = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_FUEL_PUMPS_B) == 0) && (PRE_SWITCH_FUEL_PUMPS_B == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IG1"); PRE_SWITCH_FUEL_PUMPS_B = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_AFT_FUEL_PUMP_1) == 1) && (PRE_SWITCH_AFT_FUEL_PUMP_1 == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IH0"); PRE_SWITCH_AFT_FUEL_PUMP_1 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_AFT_FUEL_PUMP_1) == 0) && (PRE_SWITCH_AFT_FUEL_PUMP_1 == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IH1"); PRE_SWITCH_AFT_FUEL_PUMP_1 = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_AFT_FUEL_PUMP_2) == 1) && (PRE_SWITCH_AFT_FUEL_PUMP_2 == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("II0"); PRE_SWITCH_AFT_FUEL_PUMP_2 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_AFT_FUEL_PUMP_2) == 0) && (PRE_SWITCH_AFT_FUEL_PUMP_2 == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("II1"); PRE_SWITCH_AFT_FUEL_PUMP_2 = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_FWD_FUEL_PUMP_1) == 1) && (PRE_SWITCH_FWD_FUEL_PUMP_1 == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IJ0"); PRE_SWITCH_FWD_FUEL_PUMP_1 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_FWD_FUEL_PUMP_1) == 0) && (PRE_SWITCH_FWD_FUEL_PUMP_1 == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IJ1"); PRE_SWITCH_FWD_FUEL_PUMP_1 = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_FWD_FUEL_PUMP_2) == 1) && (PRE_SWITCH_FWD_FUEL_PUMP_2 == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IK0"); PRE_SWITCH_FWD_FUEL_PUMP_2 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_FWD_FUEL_PUMP_2) == 0) && (PRE_SWITCH_FWD_FUEL_PUMP_2 == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IK1"); PRE_SWITCH_FWD_FUEL_PUMP_2 = 1; lastUpdateSwitch = millis();} }


    // **PANEL C1-4 SWITCHES**
     
      // ***SWITCHES LOGIC***
      
        if( ((SWITCH_RETRACTABLE_LDG_LIGHTS_L) == 1) && (PRE_SWITCH_RETRACTABLE_LDG_LIGHTS_L == 2) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ab0"); PRE_SWITCH_RETRACTABLE_LDG_LIGHTS_L = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_RETRACTABLE_LDG_LIGHTS_L) == 0) && (PRE_SWITCH_RETRACTABLE_LDG_LIGHTS_L == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ab2"); PRE_SWITCH_RETRACTABLE_LDG_LIGHTS_L = 2; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_RETRACTABLE_LDG_LIGHTS_R) == 1) && (PRE_SWITCH_RETRACTABLE_LDG_LIGHTS_R == 2) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ac0"); PRE_SWITCH_RETRACTABLE_LDG_LIGHTS_R = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_RETRACTABLE_LDG_LIGHTS_R) == 0) && (PRE_SWITCH_RETRACTABLE_LDG_LIGHTS_R == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ac2"); PRE_SWITCH_RETRACTABLE_LDG_LIGHTS_R = 2; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_FIXED_LDG_LIGHTS_L) == 1) && (PRE_SWITCH_FIXED_LDG_LIGHTS_L == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ad0"); PRE_SWITCH_FIXED_LDG_LIGHTS_L = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_FIXED_LDG_LIGHTS_L) == 0) && (PRE_SWITCH_FIXED_LDG_LIGHTS_L == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ad1"); PRE_SWITCH_FIXED_LDG_LIGHTS_L = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_FIXED_LDG_LIGHTS_R) == 1) && (PRE_SWITCH_FIXED_LDG_LIGHTS_R == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ae0"); PRE_SWITCH_FIXED_LDG_LIGHTS_R = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_FIXED_LDG_LIGHTS_R) == 0) && (PRE_SWITCH_FIXED_LDG_LIGHTS_R == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ae1"); PRE_SWITCH_FIXED_LDG_LIGHTS_R = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_RWY_LIGHT_L) == 1) && (PRE_SWITCH_RWY_LIGHT_L == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Af0"); PRE_SWITCH_RWY_LIGHT_L = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_RWY_LIGHT_L) == 0) && (PRE_SWITCH_RWY_LIGHT_L == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Af1"); PRE_SWITCH_RWY_LIGHT_L = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_RWY_LIGHT_R) == 1) && (PRE_SWITCH_RWY_LIGHT_R == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ag0"); PRE_SWITCH_RWY_LIGHT_R = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_RWY_LIGHT_R) == 0) && (PRE_SWITCH_RWY_LIGHT_R == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ag1"); PRE_SWITCH_RWY_LIGHT_R = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_TAXI_LIGHT) == 1) && (PRE_SWITCH_TAXI_LIGHT == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ah0"); PRE_SWITCH_TAXI_LIGHT = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_TAXI_LIGHT) == 0) && (PRE_SWITCH_TAXI_LIGHT == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ah1"); PRE_SWITCH_TAXI_LIGHT = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_APU_1) == 0) && ((SWITCH_APU_2) == 1) && (PRE_SWITCH_APU == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ai0"); PRE_SWITCH_APU = 0; lastUpdateSwitch = millis(); apu_power = 0;} }
        if( ((SWITCH_APU_1) == 0) && ((SWITCH_APU_2) == 0) && ( (PRE_SWITCH_APU == 0) || (PRE_SWITCH_APU == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ai1"); PRE_SWITCH_APU = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_APU_1) == 1) && ((SWITCH_APU_2) == 0) && (PRE_SWITCH_APU == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ai2"); PRE_SWITCH_APU = 2; lastUpdateSwitch = millis();} }
      
        if( ((SELECTOR_ENGINE_STATOR_L_1) == 1) && ((SELECTOR_ENGINE_STATOR_L_2) == 0) && ((SELECTOR_ENGINE_STATOR_L_3) == 0) && ((SELECTOR_ENGINE_STATOR_L_4) == 0) && (PRE_SELECTOR_ENGINE_STATOR_L == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Aj0"); PRE_SELECTOR_ENGINE_STATOR_L = 0; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_ENGINE_STATOR_L_1) == 0) && ((SELECTOR_ENGINE_STATOR_L_2) == 1) && ((SELECTOR_ENGINE_STATOR_L_3) == 0) && ((SELECTOR_ENGINE_STATOR_L_4) == 0) && ( (PRE_SELECTOR_ENGINE_STATOR_L == 0) || (PRE_SELECTOR_ENGINE_STATOR_L == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Aj1"); PRE_SELECTOR_ENGINE_STATOR_L = 1; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_ENGINE_STATOR_L_1) == 0) && ((SELECTOR_ENGINE_STATOR_L_2) == 0) && ((SELECTOR_ENGINE_STATOR_L_3) == 1) && ((SELECTOR_ENGINE_STATOR_L_4) == 0) && ( (PRE_SELECTOR_ENGINE_STATOR_L == 1) || (PRE_SELECTOR_ENGINE_STATOR_L == 3) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Aj2"); PRE_SELECTOR_ENGINE_STATOR_L = 2; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_ENGINE_STATOR_L_1) == 0) && ((SELECTOR_ENGINE_STATOR_L_2) == 0) && ((SELECTOR_ENGINE_STATOR_L_3) == 0) && ((SELECTOR_ENGINE_STATOR_L_4) == 1) && (PRE_SELECTOR_ENGINE_STATOR_L == 2) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Aj3"); PRE_SELECTOR_ENGINE_STATOR_L = 3; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_IGNITION_1) == 0) && ((SWITCH_IGNITION_2) == 1) && (PRE_SWITCH_IGNITION == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Al0"); PRE_SWITCH_IGNITION = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_IGNITION_1) == 0) && ((SWITCH_IGNITION_2) == 0) && ( (PRE_SWITCH_IGNITION == 0) || (PRE_SWITCH_IGNITION == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Al1"); PRE_SWITCH_IGNITION = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_IGNITION_1) == 1) && ((SWITCH_IGNITION_2) == 0) && (PRE_SWITCH_IGNITION == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Al2"); PRE_SWITCH_IGNITION = 2; lastUpdateSwitch = millis();} }
      
        if( ((SELECTOR_ENGINE_STATOR_R_1) == 1) && ((SELECTOR_ENGINE_STATOR_R_2) == 0) && ((SELECTOR_ENGINE_STATOR_R_3) == 0) && ((SELECTOR_ENGINE_STATOR_R_4) == 0) && (PRE_SELECTOR_ENGINE_STATOR_R == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ak0"); PRE_SELECTOR_ENGINE_STATOR_R = 0; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_ENGINE_STATOR_R_1) == 0) && ((SELECTOR_ENGINE_STATOR_R_2) == 1) && ((SELECTOR_ENGINE_STATOR_R_3) == 0) && ((SELECTOR_ENGINE_STATOR_R_4) == 0) && ( (PRE_SELECTOR_ENGINE_STATOR_R == 0) || (PRE_SELECTOR_ENGINE_STATOR_R == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ak1"); PRE_SELECTOR_ENGINE_STATOR_R = 1; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_ENGINE_STATOR_R_1) == 0) && ((SELECTOR_ENGINE_STATOR_R_2) == 0) && ((SELECTOR_ENGINE_STATOR_R_3) == 1) && ((SELECTOR_ENGINE_STATOR_R_4) == 0) && ( (PRE_SELECTOR_ENGINE_STATOR_R == 1) || (PRE_SELECTOR_ENGINE_STATOR_R == 3) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ak2"); PRE_SELECTOR_ENGINE_STATOR_R = 2; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_ENGINE_STATOR_R_1) == 0) && ((SELECTOR_ENGINE_STATOR_R_2) == 0) && ((SELECTOR_ENGINE_STATOR_R_3) == 0) && ((SELECTOR_ENGINE_STATOR_R_4) == 1) && (PRE_SELECTOR_ENGINE_STATOR_R == 2) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ak3"); PRE_SELECTOR_ENGINE_STATOR_R = 3; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_LOGO_LIGHT) == 1) && (PRE_SWITCH_LOGO_LIGHT == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Am0"); PRE_SWITCH_LOGO_LIGHT = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_LOGO_LIGHT) == 0) && (PRE_SWITCH_LOGO_LIGHT == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Am1"); PRE_SWITCH_LOGO_LIGHT = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_STROBE_LIGHT_1) == 0) && ((SWITCH_STROBE_LIGHT_2) == 1) && (PRE_SWITCH_STROBE_LIGHT == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("An0"); PRE_SWITCH_STROBE_LIGHT = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_STROBE_LIGHT_1) == 0) && ((SWITCH_STROBE_LIGHT_2) == 0) && ( (PRE_SWITCH_STROBE_LIGHT == 0) || (PRE_SWITCH_STROBE_LIGHT == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("An1"); PRE_SWITCH_STROBE_LIGHT = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_STROBE_LIGHT_1) == 1) && ((SWITCH_STROBE_LIGHT_2) == 0) && (PRE_SWITCH_STROBE_LIGHT == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("An2"); PRE_SWITCH_STROBE_LIGHT = 2; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_ANTI_COLLITION_LIGHT) == 1) && (PRE_SWITCH_ANTI_COLLITION_LIGHT == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ao0"); PRE_SWITCH_ANTI_COLLITION_LIGHT = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_ANTI_COLLITION_LIGHT) == 0) && (PRE_SWITCH_ANTI_COLLITION_LIGHT == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ao1"); PRE_SWITCH_ANTI_COLLITION_LIGHT = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_WING_LIGHT) == 1) && (PRE_SWITCH_WING_LIGHT == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ap0"); PRE_SWITCH_WING_LIGHT = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_WING_LIGHT) == 0) && (PRE_SWITCH_WING_LIGHT == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Ap1"); PRE_SWITCH_WING_LIGHT = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_WHEEL_WELL_LIGHT) == 1) && (PRE_SWITCH_WHEEL_WELL_LIGHT == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Aq0"); PRE_SWITCH_WHEEL_WELL_LIGHT = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_WHEEL_WELL_LIGHT) == 0) && (PRE_SWITCH_WHEEL_WELL_LIGHT == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("Aq1"); PRE_SWITCH_WHEEL_WELL_LIGHT = 1; lastUpdateSwitch = millis();} } 

     
    // **PANEL C2-1 SWITCHES**

      // ***SWITCHES LOGIC***
      
        if( ((BUTTON_MAINT) == 0) && (PRE_BUTTON_MAINT == 1)) { if( (millis()-lastUpdateSwitch) > 10){Serial.println("IM0"); PRE_BUTTON_MAINT = 0; lastUpdateSwitch = millis();} }
        if( ((BUTTON_MAINT) == 1) && (PRE_BUTTON_MAINT == 0)) { if( (millis()-lastUpdateSwitch) > 10){Serial.println("IM1"); PRE_BUTTON_MAINT = 1; lastUpdateSwitch = millis();} }            
      
        if( ((SELECTOR_DC_SOURCE_0) == 1) && (PRE_SELECTOR_DC_SOURCE == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IN7"); PRE_SELECTOR_DC_SOURCE = 0; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_DC_SOURCE_1) == 1) && ((PRE_SELECTOR_DC_SOURCE == 2) || (PRE_SELECTOR_DC_SOURCE == 0)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IN0"); PRE_SELECTOR_DC_SOURCE = 1; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_DC_SOURCE_2) == 1) && ((PRE_SELECTOR_DC_SOURCE == 3) || (PRE_SELECTOR_DC_SOURCE == 1)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IN1"); PRE_SELECTOR_DC_SOURCE = 2; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_DC_SOURCE_3) == 1) && ((PRE_SELECTOR_DC_SOURCE == 4) || (PRE_SELECTOR_DC_SOURCE == 2)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IN2"); PRE_SELECTOR_DC_SOURCE = 3; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_DC_SOURCE_4) == 1) && ((PRE_SELECTOR_DC_SOURCE == 5) || (PRE_SELECTOR_DC_SOURCE == 3)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IN3"); PRE_SELECTOR_DC_SOURCE = 4; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_DC_SOURCE_5) == 1) && ((PRE_SELECTOR_DC_SOURCE == 6) || (PRE_SELECTOR_DC_SOURCE == 4)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IN4"); PRE_SELECTOR_DC_SOURCE = 5; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_DC_SOURCE_6) == 1) && ((PRE_SELECTOR_DC_SOURCE == 7) || (PRE_SELECTOR_DC_SOURCE == 5)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IN5"); PRE_SELECTOR_DC_SOURCE = 6; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_DC_SOURCE_7) == 1) && ((PRE_SELECTOR_DC_SOURCE == 0) || (PRE_SELECTOR_DC_SOURCE == 6)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IN6"); PRE_SELECTOR_DC_SOURCE = 7; lastUpdateSwitch = millis();} }
        
        if( ((SELECTOR_AC_SOURCE_0) == 1) && (PRE_SELECTOR_AC_SOURCE == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IO0"); PRE_SELECTOR_AC_SOURCE = 0; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_AC_SOURCE_1) == 1) && ((PRE_SELECTOR_AC_SOURCE == 2) || (PRE_SELECTOR_AC_SOURCE == 0)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IO1"); PRE_SELECTOR_AC_SOURCE = 1; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_AC_SOURCE_2) == 1) && ((PRE_SELECTOR_AC_SOURCE == 3) || (PRE_SELECTOR_AC_SOURCE == 1)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IO2"); PRE_SELECTOR_AC_SOURCE = 2; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_AC_SOURCE_3) == 1) && ((PRE_SELECTOR_AC_SOURCE == 4) || (PRE_SELECTOR_AC_SOURCE == 2)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IO3"); PRE_SELECTOR_AC_SOURCE = 3; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_AC_SOURCE_4) == 1) && ((PRE_SELECTOR_AC_SOURCE == 5) || (PRE_SELECTOR_AC_SOURCE == 3)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IO4"); PRE_SELECTOR_AC_SOURCE = 4; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_AC_SOURCE_5) == 1) && ((PRE_SELECTOR_AC_SOURCE == 6) || (PRE_SELECTOR_AC_SOURCE == 4)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IO5"); PRE_SELECTOR_AC_SOURCE = 5; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_AC_SOURCE_6) == 1) && (PRE_SELECTOR_AC_SOURCE == 5) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IO6"); PRE_SELECTOR_AC_SOURCE = 6; lastUpdateSwitch = millis();} }

        if( ((SWITCH_MAIN_BATTERY) == 1) && (PRE_SWITCH_MAIN_BATTERY == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IP0"); PRE_SWITCH_MAIN_BATTERY = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_MAIN_BATTERY) == 0) && (PRE_SWITCH_MAIN_BATTERY == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IP1"); PRE_SWITCH_MAIN_BATTERY = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_CAB_UTIL) == 1) && (PRE_SWITCH_CAB_UTIL == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IQ0"); PRE_SWITCH_CAB_UTIL = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_CAB_UTIL) == 0) && (PRE_SWITCH_CAB_UTIL == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IQ1"); PRE_SWITCH_CAB_UTIL = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_IFE_PASS_SEAT) == 1) && (PRE_SWITCH_IFE_PASS_SEAT == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IR0"); PRE_SWITCH_IFE_PASS_SEAT = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_IFE_PASS_SEAT) == 0) && (PRE_SWITCH_IFE_PASS_SEAT == 0) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("IR1"); PRE_SWITCH_IFE_PASS_SEAT = 1; lastUpdateSwitch = millis();} }

    // **PANEL C2-2 SWITCHES**

      // ***SWITCHES LOGIC***

        if( ((SWITCH_DRIVE_1) == 1) && (PRE_SWITCH_DRIVE_1 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IT0"); PRE_SWITCH_DRIVE_1 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_DRIVE_1) == 0) && (PRE_SWITCH_DRIVE_1 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IT1"); PRE_SWITCH_DRIVE_1 = 1; lastUpdateSwitch = millis();} }
        
        if( ((SWITCH_DRIVE_2) == 1) && (PRE_SWITCH_DRIVE_2 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IU0"); PRE_SWITCH_DRIVE_2 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_DRIVE_2) == 0) && (PRE_SWITCH_DRIVE_2 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IU1"); PRE_SWITCH_DRIVE_2 = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_STANDBY_POWER_1) == 0) && (SWITCH_STANDBY_POWER_2) == 1 && (PRE_SWITCH_STANDBY_POWER == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IS0"); PRE_SWITCH_STANDBY_POWER = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_STANDBY_POWER_1) == 0) && (SWITCH_STANDBY_POWER_2) == 0 && ( (PRE_SWITCH_STANDBY_POWER == 0) || (PRE_SWITCH_STANDBY_POWER == 2) )){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IS1"); PRE_SWITCH_STANDBY_POWER = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_STANDBY_POWER_1) == 1) && (SWITCH_STANDBY_POWER_2) == 0 && (PRE_SWITCH_STANDBY_POWER == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IS2"); PRE_SWITCH_STANDBY_POWER = 2; lastUpdateSwitch = millis();} }
      
              
    // **PANEL C2-3 SWITCHES**

      // ***SWITCHES LOGIC***
      
        if( ((SWITCH_GROUND_POWER_ON) == 0) && (SWITCH_GROUND_POWER_OFF) == 1 && (PRE_SWITCH_GROUND_POWER == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IV0"); PRE_SWITCH_GROUND_POWER = 2; ground_power = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_GROUND_POWER_ON) == 0) && (SWITCH_GROUND_POWER_OFF) == 0 && ( (PRE_SWITCH_GROUND_POWER == 0) || (PRE_SWITCH_GROUND_POWER == 2) )){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IV1"); PRE_SWITCH_GROUND_POWER = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_GROUND_POWER_ON) == 1) && (SWITCH_GROUND_POWER_OFF) == 0 && (PRE_SWITCH_GROUND_POWER == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IV2"); PRE_SWITCH_GROUND_POWER = 0; ground_power = 1; lastUpdateSwitch = millis();} }
        
        if( ((SWITCH_BUS_TRANSFER) == 1) && (PRE_SWITCH_BUS_TRANSFER == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IW0"); PRE_SWITCH_BUS_TRANSFER = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_BUS_TRANSFER) == 0) && (PRE_SWITCH_BUS_TRANSFER == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IW1"); PRE_SWITCH_BUS_TRANSFER = 1; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_MAIN_GEN_1_ON) == 0) && (SWITCH_MAIN_GEN_1_OFF) == 1 && (PRE_SWITCH_MAIN_GEN_1 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IX0"); PRE_SWITCH_MAIN_GEN_1 = 2; lastUpdateSwitch = millis();} }
        if( ((SWITCH_MAIN_GEN_1_ON) == 0) && (SWITCH_MAIN_GEN_1_OFF) == 0 && ( (PRE_SWITCH_MAIN_GEN_1 == 0) || (PRE_SWITCH_MAIN_GEN_1 == 2) )){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IX1"); PRE_SWITCH_MAIN_GEN_1 = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_MAIN_GEN_1_ON) == 1) && (SWITCH_MAIN_GEN_1_OFF) == 0 && (PRE_SWITCH_MAIN_GEN_1 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IX2"); PRE_SWITCH_MAIN_GEN_1 = 0; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_MAIN_GEN_2_ON) == 0) && (SWITCH_MAIN_GEN_2_OFF) == 1 && (PRE_SWITCH_MAIN_GEN_2 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IY0"); PRE_SWITCH_MAIN_GEN_2 = 2; lastUpdateSwitch = millis();} }
        if( ((SWITCH_MAIN_GEN_2_ON) == 0) && (SWITCH_MAIN_GEN_2_OFF) == 0 && ( (PRE_SWITCH_MAIN_GEN_2 == 0) || (PRE_SWITCH_MAIN_GEN_2 == 2) )){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IY1"); PRE_SWITCH_MAIN_GEN_2 = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_MAIN_GEN_2_ON) == 1) && (SWITCH_MAIN_GEN_2_OFF) == 0 && (PRE_SWITCH_MAIN_GEN_2 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IY2"); PRE_SWITCH_MAIN_GEN_2 = 0; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_APU_GEN_1_ON) == 0) && (SWITCH_APU_GEN_1_OFF) == 1 && (PRE_SWITCH_APU_GEN_1 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IZ0"); PRE_SWITCH_APU_GEN_1 = 2; lastUpdateSwitch = millis();} }
        if( ((SWITCH_APU_GEN_1_ON) == 0) && (SWITCH_APU_GEN_1_OFF) == 0 && ( (PRE_SWITCH_APU_GEN_1 == 0) || (PRE_SWITCH_APU_GEN_1 == 2) )){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IZ1"); PRE_SWITCH_APU_GEN_1 = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_APU_GEN_1_ON) == 1) && (SWITCH_APU_GEN_1_OFF) == 0 && (PRE_SWITCH_APU_GEN_1 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IZ2"); PRE_SWITCH_APU_GEN_1 = 0; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_APU_GEN_2_ON) == 0) && (SWITCH_APU_GEN_2_OFF) == 1 && (PRE_SWITCH_APU_GEN_2 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JA0"); PRE_SWITCH_APU_GEN_2 = 2; lastUpdateSwitch = millis();} }
        if( ((SWITCH_APU_GEN_2_ON) == 0) && (SWITCH_APU_GEN_2_OFF) == 0 && ( (PRE_SWITCH_APU_GEN_2 == 0) || (PRE_SWITCH_APU_GEN_2 == 2) )){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JA1"); PRE_SWITCH_APU_GEN_2 = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_APU_GEN_2_ON) == 1) && (SWITCH_APU_GEN_2_OFF) == 0 && (PRE_SWITCH_APU_GEN_2 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JA2"); PRE_SWITCH_APU_GEN_2 = 0; lastUpdateSwitch = millis();} }
      
    // **PANEL C2-4 SWITCHES**

      // ***SWITCHES LOGIC***

        if( ((SELECTOR_WIPER_L_0) == 1) && (PRE_SELECTOR_WIPER_L == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JB0"); PRE_SELECTOR_WIPER_L = 0; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_WIPER_L_1) == 1) && ((PRE_SELECTOR_WIPER_L == 2) || (PRE_SELECTOR_WIPER_L == 0)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JB1"); PRE_SELECTOR_WIPER_L = 1; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_WIPER_L_2) == 1) && ((PRE_SELECTOR_WIPER_L == 3) || (PRE_SELECTOR_WIPER_L == 1)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JB2"); PRE_SELECTOR_WIPER_L = 2; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_WIPER_L_3) == 1) && (PRE_SELECTOR_WIPER_L == 2) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JB3"); PRE_SELECTOR_WIPER_L = 3; lastUpdateSwitch = millis();} }
  
    // **PANEL C3-2 SWITCHES**

      // ***SWITCHES LOGIC***

        if( ((SWITCH_EQUIP_SUPPLY) == 1) && (PRE_SWITCH_EQUIP_SUPPLY == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JD0"); PRE_SWITCH_EQUIP_SUPPLY = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_EQUIP_SUPPLY) == 0) && (PRE_SWITCH_EQUIP_SUPPLY == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JD1"); PRE_SWITCH_EQUIP_SUPPLY = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_EQUIP_EXHAUST) == 1) && (PRE_SWITCH_EQUIP_EXHAUST == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JE0"); PRE_SWITCH_EQUIP_EXHAUST = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_EQUIP_EXHAUST) == 0) && (PRE_SWITCH_EQUIP_EXHAUST == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JE1"); PRE_SWITCH_EQUIP_EXHAUST = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_EMER_EXIT_LIGHT_1) == 0) && (SWITCH_EMER_EXIT_LIGHT_2) == 1 && (PRE_SWITCH_EMER_EXIT_LIGHT == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JF0"); PRE_SWITCH_EMER_EXIT_LIGHT = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_EMER_EXIT_LIGHT_1) == 0) && (SWITCH_EMER_EXIT_LIGHT_2) == 0 && ( (PRE_SWITCH_EMER_EXIT_LIGHT == 0) || (PRE_SWITCH_EMER_EXIT_LIGHT == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JF1"); PRE_SWITCH_EMER_EXIT_LIGHT = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_EMER_EXIT_LIGHT_1) == 1) && (SWITCH_EMER_EXIT_LIGHT_2) == 0 && (PRE_SWITCH_EMER_EXIT_LIGHT == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JF2"); PRE_SWITCH_EMER_EXIT_LIGHT = 2; lastUpdateSwitch = millis();} }

        if( ((SWITCH_CHIME) == 1) && (PRE_SWITCH_CHIME == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JG0"); PRE_SWITCH_CHIME = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_CHIME) == 0) && (PRE_SWITCH_CHIME == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JG1"); PRE_SWITCH_CHIME = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_FASTEN_BELTS_1) == 0) && (SWITCH_FASTEN_BELTS_2) == 1 && (PRE_SWITCH_FASTEN_BELTS == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JH0"); PRE_SWITCH_FASTEN_BELTS = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_FASTEN_BELTS_1) == 0) && (SWITCH_FASTEN_BELTS_2) == 0 && ( (PRE_SWITCH_FASTEN_BELTS == 0) || (PRE_SWITCH_FASTEN_BELTS == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JH1"); PRE_SWITCH_FASTEN_BELTS = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_FASTEN_BELTS_1) == 1) && (SWITCH_FASTEN_BELTS_2) == 0 && (PRE_SWITCH_FASTEN_BELTS == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JH2"); PRE_SWITCH_FASTEN_BELTS = 2; lastUpdateSwitch = millis();} }

        if( ((BUTTON_ATTEND) == 0) && (PRE_BUTTON_ATTEND == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JI0"); PRE_BUTTON_ATTEND = 0; lastUpdateSwitch = millis();} }
        if( ((BUTTON_ATTEND) == 1) && (PRE_BUTTON_ATTEND == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JI1"); PRE_BUTTON_ATTEND = 1; lastUpdateSwitch = millis();} }

        if( ((BUTTON_GRD_CALL) == 0) && (PRE_BUTTON_GRD_CALL == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JJ0"); PRE_BUTTON_GRD_CALL = 0; lastUpdateSwitch = millis();} }
        if( ((BUTTON_GRD_CALL) == 1) && (PRE_BUTTON_GRD_CALL == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JJ1"); PRE_BUTTON_GRD_CALL = 1; lastUpdateSwitch = millis();} }

        if( ((SELECTOR_WIPER_R_0) == 1) && (PRE_SELECTOR_WIPER_R == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JC0"); PRE_SELECTOR_WIPER_R = 0; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_WIPER_R_1) == 1) && ((PRE_SELECTOR_WIPER_R == 2) || (PRE_SELECTOR_WIPER_R == 0)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JC1"); PRE_SELECTOR_WIPER_R = 1; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_WIPER_R_2) == 1) && ((PRE_SELECTOR_WIPER_R == 3) || (PRE_SELECTOR_WIPER_R == 1)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JC2"); PRE_SELECTOR_WIPER_R = 2; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_WIPER_R_3) == 1) && (PRE_SELECTOR_WIPER_R == 2) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JC3"); PRE_SELECTOR_WIPER_R = 3; lastUpdateSwitch = millis();} }

    // **PANEL C4-1 SWITCHES**

      // ***SWITCHES LOGIC***

        if( ((SWITCH_WH_SIDE_1) == 1) && (PRE_SWITCH_WH_SIDE_1 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JK0"); PRE_SWITCH_WH_SIDE_1 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_WH_SIDE_1) == 0) && (PRE_SWITCH_WH_SIDE_1 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JK1"); PRE_SWITCH_WH_SIDE_1 = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_WH_SIDE_2) == 1) && (PRE_SWITCH_WH_SIDE_2 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JL0"); PRE_SWITCH_WH_SIDE_2 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_WH_SIDE_2) == 0) && (PRE_SWITCH_WH_SIDE_2 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JL1"); PRE_SWITCH_WH_SIDE_2 = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_WH_FWD_1) == 1) && (PRE_SWITCH_WH_FWD_1 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JM0"); PRE_SWITCH_WH_FWD_1 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_WH_FWD_1) == 0) && (PRE_SWITCH_WH_FWD_1 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JM1"); PRE_SWITCH_WH_FWD_1 = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_WH_FWD_2) == 1) && (PRE_SWITCH_WH_FWD_2 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JN0"); PRE_SWITCH_WH_FWD_2 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_WH_FWD_2) == 0) && (PRE_SWITCH_WH_FWD_2 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JN1"); PRE_SWITCH_WH_FWD_2 = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_PROBE_HEAT_A) == 1) && (PRE_SWITCH_PROBE_HEAT_A == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JO0"); PRE_SWITCH_PROBE_HEAT_A = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_PROBE_HEAT_A) == 0) && (PRE_SWITCH_PROBE_HEAT_A == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JO1"); PRE_SWITCH_PROBE_HEAT_A = 1; lastUpdateSwitch = millis();} }      

        if( ((SWITCH_PROBE_HEAT_B) == 1) && (PRE_SWITCH_PROBE_HEAT_B == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JP0"); PRE_SWITCH_PROBE_HEAT_B = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_PROBE_HEAT_B) == 0) && (PRE_SWITCH_PROBE_HEAT_B == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JP1"); PRE_SWITCH_PROBE_HEAT_B = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_OVERHEAT_1) == 0) && (SWITCH_OVERHEAT_2) == 1 && (PRE_SWITCH_OVERHEAT == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JQ0"); PRE_SWITCH_OVERHEAT = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_OVERHEAT_1) == 0) && (SWITCH_OVERHEAT_2) == 0 && ( (PRE_SWITCH_OVERHEAT == 0) || (PRE_SWITCH_OVERHEAT == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JQ1"); PRE_SWITCH_OVERHEAT = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_OVERHEAT_1) == 1) && (SWITCH_OVERHEAT_2) == 0 && (PRE_SWITCH_OVERHEAT == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("JQ2"); PRE_SWITCH_OVERHEAT = 2; lastUpdateSwitch = millis();} }

        if( ((BUTTON_TAT_TEST) == 0) && (PRE_BUTTON_TAT_TEST == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("--0"); PRE_BUTTON_TAT_TEST = 0; lastUpdateSwitch = millis();} }
        if( ((BUTTON_TAT_TEST) == 1) && (PRE_BUTTON_TAT_TEST == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("--1"); PRE_BUTTON_TAT_TEST = 1; lastUpdateSwitch = millis();} }

    // **PANEL C4-2 SWITCHES**

      // ***SWITCHES LOGIC***

        if( ((SWITCH_WING_ANTI_ICE) == 1) && (PRE_SWITCH_WING_ANTI_ICE == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JR0"); PRE_SWITCH_WING_ANTI_ICE = 0; lastUpdateSwitch = millis(); } }
        if( ((SWITCH_WING_ANTI_ICE) == 0) && (PRE_SWITCH_WING_ANTI_ICE == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JR1"); PRE_SWITCH_WING_ANTI_ICE = 1; lastUpdateSwitch = millis(); } }

        if( ((SWITCH_ENGINE_ANTI_ICE_1) == 1) && (PRE_SWITCH_ENGINE_ANTI_ICE_1 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JS0"); PRE_SWITCH_ENGINE_ANTI_ICE_1 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_ENGINE_ANTI_ICE_1) == 0) && (PRE_SWITCH_ENGINE_ANTI_ICE_1 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JS1"); PRE_SWITCH_ENGINE_ANTI_ICE_1 = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_ENGINE_ANTI_ICE_2) == 1) && (PRE_SWITCH_ENGINE_ANTI_ICE_2 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JT0"); PRE_SWITCH_ENGINE_ANTI_ICE_2 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_ENGINE_ANTI_ICE_2) == 0) && (PRE_SWITCH_ENGINE_ANTI_ICE_2 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JT1"); PRE_SWITCH_ENGINE_ANTI_ICE_2 = 1; lastUpdateSwitch = millis();} }

    // **PANEL C4-3 SWITCHES**

      // ***SWITCHES LOGIC***

        if( ((SWITCH_ENGINE_HYD_1) == 1) && (PRE_SWITCH_ENGINE_HYD_1 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JU0"); PRE_SWITCH_ENGINE_HYD_1 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_ENGINE_HYD_1) == 0) && (PRE_SWITCH_ENGINE_HYD_1 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JU1"); PRE_SWITCH_ENGINE_HYD_1 = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_ENGINE_HYD_2) == 1) && (PRE_SWITCH_ENGINE_HYD_2 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JV0"); PRE_SWITCH_ENGINE_HYD_2 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_ENGINE_HYD_2) == 0) && (PRE_SWITCH_ENGINE_HYD_2 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JV1"); PRE_SWITCH_ENGINE_HYD_2 = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_ELECTRIC_HYD_1) == 1) && (PRE_SWITCH_ELECTRIC_HYD_1 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JW0"); PRE_SWITCH_ELECTRIC_HYD_1 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_ELECTRIC_HYD_1) == 0) && (PRE_SWITCH_ELECTRIC_HYD_1 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JW1"); PRE_SWITCH_ELECTRIC_HYD_1 = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_ELECTRIC_HYD_2) == 1) && (PRE_SWITCH_ELECTRIC_HYD_2 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JX0"); PRE_SWITCH_ELECTRIC_HYD_2 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_ELECTRIC_HYD_2) == 0) && (PRE_SWITCH_ELECTRIC_HYD_2 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("JX1"); PRE_SWITCH_ELECTRIC_HYD_2 = 1; lastUpdateSwitch = millis();} }

    // **PANEL C4-5 SWITCHES**

      // ***SWITCHES LOGIC***

        if( ((BUTTON_COCKPIT_VOICE_TEST) == 0) && (PRE_BUTTON_COCKPIT_VOICE_TEST == 1) ){if( (millis()-lastUpdateSwitch) > 50){Serial.println("JY0"); PRE_BUTTON_COCKPIT_VOICE_TEST = 0; lastUpdateSwitch = millis(); valueZZ = '0'; bitClear(SR_OUT_17,7); update_SR_OUT_13();} }
        if( ((BUTTON_COCKPIT_VOICE_TEST) == 1) && (PRE_BUTTON_COCKPIT_VOICE_TEST == 0) ){if( (millis()-lastUpdateSwitch) > 50){Serial.println("JY1"); PRE_BUTTON_COCKPIT_VOICE_TEST = 1; lastUpdateSwitch = millis(); valueZZ = '1'; bitSet(SR_OUT_17,7); update_SR_OUT_13();} }

        if( ((BUTTON_COCKPIT_VOICE_ERASE) == 0) && (PRE_BUTTON_COCKPIT_VOICE_ERASE == 1) ){if( (millis()-lastUpdateSwitch) > 50){Serial.println("JZ0"); PRE_BUTTON_COCKPIT_VOICE_ERASE = 0; lastUpdateSwitch = millis();} }
        if( ((BUTTON_COCKPIT_VOICE_ERASE) == 1) && (PRE_BUTTON_COCKPIT_VOICE_ERASE == 0) ){if( (millis()-lastUpdateSwitch) > 50){Serial.println("JZ1"); PRE_BUTTON_COCKPIT_VOICE_ERASE = 1; lastUpdateSwitch = millis();} }

    // **PANEL C4-6 SWITCHES**

      // ***SWITCHES LOGIC***

        if( ((BUTTON_ALT_HORN_CUTOUT) == 0) && (PRE_BUTTON_ALT_HORN_CUTOUT == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("As0"); PRE_BUTTON_ALT_HORN_CUTOUT = 0; lastUpdateSwitch = millis();} }
        if( ((BUTTON_ALT_HORN_CUTOUT) == 1) && (PRE_BUTTON_ALT_HORN_CUTOUT == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("As1"); PRE_BUTTON_ALT_HORN_CUTOUT = 1; lastUpdateSwitch = millis();} }

    // **PANEL C5-1 SWITCHES**

      // ***SWITCHES LOGIC***

        if( ((SWITCH_VOICE_RECORDER) == 1) && (PRE_SWITCH_VOICE_RECORDER == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IL0"); PRE_SWITCH_VOICE_RECORDER = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_VOICE_RECORDER) == 0) && (PRE_SWITCH_VOICE_RECORDER == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("IL1"); PRE_SWITCH_VOICE_RECORDER = 1; lastUpdateSwitch = millis();} }
      
    // **PANEL C5-2 SWITCHES**

      // ***SWITCHES LOGIC***
      
        if( ((SELECTOR_AIR_TEMP_0) == 1) && (PRE_SELECTOR_AIR_TEMP == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KA0"); PRE_SELECTOR_AIR_TEMP = 0; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_AIR_TEMP_1) == 1) && ((PRE_SELECTOR_AIR_TEMP == 2) || (PRE_SELECTOR_AIR_TEMP == 0)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KA1"); PRE_SELECTOR_AIR_TEMP = 1; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_AIR_TEMP_2) == 1) && ((PRE_SELECTOR_AIR_TEMP == 3) || (PRE_SELECTOR_AIR_TEMP == 1)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KA2"); PRE_SELECTOR_AIR_TEMP = 2; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_AIR_TEMP_3) == 1) && ((PRE_SELECTOR_AIR_TEMP == 4) || (PRE_SELECTOR_AIR_TEMP == 2)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KA3"); PRE_SELECTOR_AIR_TEMP = 3; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_AIR_TEMP_4) == 1) && ((PRE_SELECTOR_AIR_TEMP == 5) || (PRE_SELECTOR_AIR_TEMP == 3)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KA4"); PRE_SELECTOR_AIR_TEMP = 4; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_AIR_TEMP_5) == 1) && ((PRE_SELECTOR_AIR_TEMP == 6) || (PRE_SELECTOR_AIR_TEMP == 4)) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KA5"); PRE_SELECTOR_AIR_TEMP = 5; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_AIR_TEMP_6) == 1) && (PRE_SELECTOR_AIR_TEMP == 5) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KA6"); PRE_SELECTOR_AIR_TEMP = 6; lastUpdateSwitch = millis();} }
        
        if( ((SWITCH_TRIM_AIR) == 1) && (PRE_SWITCH_TRIM_AIR == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("At0"); PRE_SWITCH_TRIM_AIR = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_TRIM_AIR) == 0) && (PRE_SWITCH_TRIM_AIR == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("At1"); PRE_SWITCH_TRIM_AIR = 1; lastUpdateSwitch = millis();} }

      // ***POTENCIOMETERS LOGIC***

        pot_cont_cab_Aread = analogRead(POT_CONT_CAB); // read the analog in value
        if ( abs(pot_cont_cab_Aread - pot_cont_cab_Lastread) >= 2){ // Eliminates oscilation of the analog read value
          pot_cont_cab_Avalue = map(pot_cont_cab_Aread, 87, 1023, 0, 106); // map it to the range of the analog out
          if (pot_cont_cab_Avalue > pot_cont_cab_Lastvalue){
            int dif = (pot_cont_cab_Avalue - pot_cont_cab_Lastvalue);
            for (int i=0; i<dif; i++){
              Serial.println("KB1");
            }
          }
          else if (pot_cont_cab_Avalue < pot_cont_cab_Lastvalue){
            int dif = (pot_cont_cab_Lastvalue - pot_cont_cab_Avalue);
            for (int i=0; i<dif; i++){
              Serial.println("KB0");
            }
          }
          pot_cont_cab_Lastread = pot_cont_cab_Aread;
        }
        pot_cont_cab_Lastvalue = pot_cont_cab_Avalue;

        pot_fwd_cab_Aread = analogRead(POT_FWD_CAB); // read the analog in value
        if ( abs(pot_fwd_cab_Aread - pot_fwd_cab_Lastread) >= 2){ // Eliminates oscilation of the analog read value
          pot_fwd_cab_Avalue = map(pot_fwd_cab_Aread, 87, 1023, 0, 106); // map it to the range of the analog out
          if (pot_fwd_cab_Avalue > pot_fwd_cab_Lastvalue){
            int dif = (pot_fwd_cab_Avalue - pot_fwd_cab_Lastvalue);
            for (int i=0; i<dif; i++){
              Serial.println("KC1");
            }
          }
          else if (pot_fwd_cab_Avalue < pot_fwd_cab_Lastvalue){
            int dif = (pot_fwd_cab_Lastvalue - pot_fwd_cab_Avalue);
            for (int i=0; i<dif; i++){
              Serial.println("KC0");
            }
          }
          pot_fwd_cab_Lastread = pot_fwd_cab_Aread;
        }
        pot_fwd_cab_Lastvalue = pot_fwd_cab_Avalue;

        pot_aft_cab_Aread = analogRead(POT_AFT_CAB); // read the analog in value
        if ( abs(pot_aft_cab_Aread - pot_aft_cab_Lastread) >= 2){  
          pot_aft_cab_Avalue = map(pot_aft_cab_Aread, 87, 1023, 0, 106); // map it to the range of the analog out
          if (pot_aft_cab_Avalue > pot_aft_cab_Lastvalue){
            int dif = (pot_aft_cab_Avalue - pot_aft_cab_Lastvalue);
            for (int i=0; i<dif; i++){
              Serial.println("KD1");
            }
          }
          else if (pot_aft_cab_Avalue < pot_aft_cab_Lastvalue){
            int dif = (pot_aft_cab_Lastvalue - pot_aft_cab_Avalue);
            for (int i=0; i<dif; i++){
              Serial.println("KD0");
            }
          }
          pot_aft_cab_Lastread = pot_aft_cab_Aread;  
        }  
        pot_aft_cab_Lastvalue = pot_aft_cab_Avalue;

    // **PANEL C5-3 SWITCHES**

      // ***SWITCHES LOGIC***
        
        if( ((SWITCH_RECIRC_FAN_L) == 1) && (PRE_SWITCH_RECIRC_FAN_L == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("KE0"); PRE_SWITCH_RECIRC_FAN_L = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_RECIRC_FAN_L) == 0) && (PRE_SWITCH_RECIRC_FAN_L == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("KE1"); PRE_SWITCH_RECIRC_FAN_L = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_RECIRC_FAN_R) == 1) && (PRE_SWITCH_RECIRC_FAN_R == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("KF0"); PRE_SWITCH_RECIRC_FAN_R = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_RECIRC_FAN_R) == 0) && (PRE_SWITCH_RECIRC_FAN_R == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("KF1"); PRE_SWITCH_RECIRC_FAN_R = 1; lastUpdateSwitch = millis();} }
      
        if( ((BUTTON_OVHT_TEST) == 0) && (PRE_BUTTON_OVHT_TEST == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("Au0"); PRE_BUTTON_OVHT_TEST = 0; lastUpdateSwitch = millis();} }
        if( ((BUTTON_OVHT_TEST) == 1) && (PRE_BUTTON_OVHT_TEST == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("Au1"); PRE_BUTTON_OVHT_TEST = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_ISOLATION_VALVE_1) == 0) && (SWITCH_ISOLATION_VALVE_2) == 1 && (PRE_SWITCH_ISOLATION_VALVE == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KG0"); PRE_SWITCH_ISOLATION_VALVE = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_ISOLATION_VALVE_1) == 0) && (SWITCH_ISOLATION_VALVE_2) == 0 && ( (PRE_SWITCH_ISOLATION_VALVE == 0) || (PRE_SWITCH_ISOLATION_VALVE == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KG1"); PRE_SWITCH_ISOLATION_VALVE = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_ISOLATION_VALVE_1) == 1) && (SWITCH_ISOLATION_VALVE_2) == 0 && (PRE_SWITCH_ISOLATION_VALVE == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KG2"); PRE_SWITCH_ISOLATION_VALVE = 2; lastUpdateSwitch = millis();} }

        if( ((BUTTON_TRIP_RESET) == 0) && (PRE_BUTTON_TRIP_RESET == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("KH0"); PRE_BUTTON_TRIP_RESET = 0; lastUpdateSwitch = millis();} }
        if( ((BUTTON_TRIP_RESET) == 1) && (PRE_BUTTON_TRIP_RESET == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("KH1"); PRE_BUTTON_TRIP_RESET = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_PACK_L_1) == 0) && (SWITCH_PACK_L_2) == 1 && (PRE_SWITCH_PACK_L == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KI0"); PRE_SWITCH_PACK_L = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_PACK_L_1) == 0) && (SWITCH_PACK_L_2) == 0 && ( (PRE_SWITCH_PACK_L == 0) || (PRE_SWITCH_PACK_L == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KI1"); PRE_SWITCH_PACK_L = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_PACK_L_1) == 1) && (SWITCH_PACK_L_2) == 0 && (PRE_SWITCH_PACK_L == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KI2"); PRE_SWITCH_PACK_L = 2; lastUpdateSwitch = millis();} }

        if( ((SWITCH_PACK_R_1) == 0) && (SWITCH_PACK_R_2) == 1 && (PRE_SWITCH_PACK_R == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KJ0"); PRE_SWITCH_PACK_R = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_PACK_R_1) == 0) && (SWITCH_PACK_R_2) == 0 && ( (PRE_SWITCH_PACK_R == 0) || (PRE_SWITCH_PACK_R == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KJ1"); PRE_SWITCH_PACK_R = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_PACK_R_1) == 1) && (SWITCH_PACK_R_2) == 0 && (PRE_SWITCH_PACK_R == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KJ2"); PRE_SWITCH_PACK_R = 2; lastUpdateSwitch = millis();} }

        if( ((SWITCH_BLEED_AIR_1) == 1) && (PRE_SWITCH_BLEED_AIR_1 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("KK0"); PRE_SWITCH_BLEED_AIR_1 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_BLEED_AIR_1) == 0) && (PRE_SWITCH_BLEED_AIR_1 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("KK1"); PRE_SWITCH_BLEED_AIR_1 = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_BLEED_AIR_2) == 1) && (PRE_SWITCH_BLEED_AIR_2 == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("KL0"); PRE_SWITCH_BLEED_AIR_2 = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_BLEED_AIR_2) == 0) && (PRE_SWITCH_BLEED_AIR_2 == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("KL1"); PRE_SWITCH_BLEED_AIR_2 = 1; lastUpdateSwitch = millis();} }

        if( ((SWITCH_APU_BLEED_AIR) == 1) && (PRE_SWITCH_APU_BLEED_AIR == 1) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("KM0"); PRE_SWITCH_APU_BLEED_AIR = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_APU_BLEED_AIR) == 0) && (PRE_SWITCH_APU_BLEED_AIR == 0) ){if( (millis()-lastUpdateSwitch) > 10){Serial.println("KM1"); PRE_SWITCH_APU_BLEED_AIR = 1; lastUpdateSwitch = millis();} }

    // **PANEL C5-4 SWITCHES**

      // ***SWITCHES LOGIC***

        if( ((SELECTOR_PRESSURIZATION_1) == 1) && (SELECTOR_PRESSURIZATION_2) == 0 && (PRE_SELECTOR_PRESSURIZATION == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KP0"); PRE_SELECTOR_PRESSURIZATION = 2; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_PRESSURIZATION_1) == 0) && (SELECTOR_PRESSURIZATION_2) == 0 && ( (PRE_SELECTOR_PRESSURIZATION == 0) || (PRE_SELECTOR_PRESSURIZATION == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KP1"); PRE_SELECTOR_PRESSURIZATION = 1; lastUpdateSwitch = millis();} }
        if( ((SELECTOR_PRESSURIZATION_1) == 0) && (SELECTOR_PRESSURIZATION_2) == 1 && (PRE_SELECTOR_PRESSURIZATION == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KP2"); PRE_SELECTOR_PRESSURIZATION = 0; lastUpdateSwitch = millis();} }
      
        if( ((SWITCH_VALVE_1) == 0) && (SWITCH_VALVE_2) == 1 && (PRE_SWITCH_VALVE == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KQ0"); PRE_SWITCH_VALVE = 0; lastUpdateSwitch = millis();} }
        if( ((SWITCH_VALVE_1) == 0) && (SWITCH_VALVE_2) == 0 && ( (PRE_SWITCH_VALVE == 0) || (PRE_SWITCH_VALVE == 2) )){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KQ1"); PRE_SWITCH_VALVE = 1; lastUpdateSwitch = millis();} }
        if( ((SWITCH_VALVE_1) == 1) && (SWITCH_VALVE_2) == 0 && (PRE_SWITCH_VALVE == 1) ){ if( (millis()-lastUpdateSwitch) > 10){Serial.println("KQ2"); PRE_SWITCH_VALVE = 2; lastUpdateSwitch = millis();} }

      // ***ROTARY ENCODER LOGIC***
        
        rotary_flt_alt_State = digitalRead(ROTARY_FLT_ALT_A); // Reads the "current" state of the ROTARY_FLT_ALT_A
        if (rotary_flt_alt_State != rotary_flt_alt_LastState){     
          if (digitalRead(ROTARY_FLT_ALT_B) != rotary_flt_alt_State) { //Rotating clockwise
            Serial.println("KN1");
          } 
          else { //Rotating antti-clockwise
            Serial.println("KN0");
          }
        } 
        rotary_flt_alt_LastState = rotary_flt_alt_State;

        rotary_land_alt_State = digitalRead(ROTARY_LAND_ALT_A); // Reads the "current" state of the ROTARY_LAND_ALT_A
        if (rotary_land_alt_State != rotary_land_alt_LastState){     
          if (digitalRead(ROTARY_LAND_ALT_B) != rotary_land_alt_State) { //Rotating clockwise
            Serial.println("KO1");
          } 
          else { //Rotating antti-clockwise
            Serial.println("KO0");
          }
        } 
        rotary_land_alt_LastState = rotary_land_alt_State;
        
  // *ALL SERVO DETACH*
    
    if( (millis() - lastUpdateServo) >= 500 ){  //time to update
          
          SERVO_FUEL_TEMP.Detach();
          SERVO_SELECTOR_ENGINE_STARTOR.Detach();
          SERVO_EGT_APU.Detach();
          SERVO_CABIN_ALT_EXT.Detach();
          SERVO_CABIN_ALT_INT.Detach();
          SERVO_CABIN_CLIMB.Detach();
          SERVO_CAB_TEMP.Detach();
          SERVO_DUCT_PRESS_L.Detach();
          SERVO_DUCT_PRESS_R.Detach();
          SERVO_MANUAL_VALVE.Detach();
          
          lastUpdateServo = millis();
    }
    
  // *AIRCRAFT ENERGY STATES*
  
    if( valueDE == '0'){ground_power=0;}

    if(valueDJ == '0' || valueDK== '0'){eng_power = 1;}
    if(valueDJ == '1' && valueDK== '1'){eng_power = 0;}
    
    if( PRE_SWITCH_MAIN_BATTERY == 0 && ground_power == 0 ){aircraft_energy=0;}
    else if( PRE_SWITCH_MAIN_BATTERY == 1 && ground_power == 0 && (aircraft_energy == 0 || aircraft_energy == 2)){aircraft_energy=1;}
    else if( PRE_SWITCH_MAIN_BATTERY == 1 && ground_power == 1 && apu_power == 0 && eng_power == 0){aircraft_energy=2;}
    else if( aircraft_energy == 2 && PRE_SWITCH_MAIN_BATTERY == 0 && ground_power == 1 ){aircraft_energy=3;}
    else if( aircraft_energy == 0 && PRE_SWITCH_MAIN_BATTERY == 0 && ground_power == 1 ){aircraft_energy=0;}
    else if( PRE_SWITCH_MAIN_BATTERY == 1 && apu_power == 1 && eng_power == 0 && (aircraft_energy == 2 || aircraft_energy == 5)){aircraft_energy=4;}
    else if( PRE_SWITCH_MAIN_BATTERY == 1 && eng_power == 1 && aircraft_energy == 4){aircraft_energy=5;}
     
} // END LOOP SECTION



// --- FUNCTION SECTION --- //

  // *GETCHAR FUNCTION*

    char getChar() { // Get one character from serial buffer
      if (Serial.available() > 0){
        char incomingByte = Serial.read();
        return(incomingByte);
      }
    }


  // *CHARACTER B FUNCTION*

    void B() { // First identifier has been B
    
      CodeIn = getChar(); // Get the second identifier
    
      switch(CodeIn) {
    
        case 'U': // CODE BU; LED STANDBY_HYD_LOW_QUANTITY
          valueBU = getChar();
          if (valueBU == '1'){ bitSet(SR_OUT_1,0); }
          else{ bitClear(SR_OUT_1,0); }
          update_SR_OUT_1();  
        break;
    
        case 'V': // CODE BV; LED STANDBY_HYD_LOW_PRESSURE
          valueBV = getChar();
          if (valueBV == '1'){ bitSet(SR_OUT_1,1); }
          else{ bitClear(SR_OUT_1,1); }
          update_SR_OUT_1(); 
        break;
    
        case 'W': // CODE BW; LED STANDBY_HYD_STBY_RUD_ON
          valueBW = getChar();
          if (valueBW == '1'){ bitSet(SR_OUT_1,2); }
          else{ bitClear(SR_OUT_1,2); }
          update_SR_OUT_1(); 
        break;
    
        case 'X': // CODE BX; LED FLT_CONTROL_A_LOW_PRESSURE
          valueBX = getChar();
          if (valueBX == '1' && (aircraft_energy == 2 || aircraft_energy ==3)){ bitSet(SR_OUT_1,3); }
          else{ bitClear(SR_OUT_1,3); }
          update_SR_OUT_1(); 
        break;
    
        case 'Y': // CODE BY; LED FLT_CONTROL_B_LOW_PRESSURE
          valueBY = getChar();
          if (valueBY == '1' && (aircraft_energy == 2 || aircraft_energy ==3)){ bitSet(SR_OUT_1,4); }
          else{ bitClear(SR_OUT_1,4); }
          update_SR_OUT_1(); 
        break;
    
        case 'Z': // CODE BZ; LED FEEL_DIFF_PRESS
          valueBZ = getChar();
          if (valueBZ == '1' && (aircraft_energy == 2 || aircraft_energy ==3)){ bitSet(SR_OUT_1,5); }
          else{ bitClear(SR_OUT_1,5); }
          update_SR_OUT_1(); 
        break;
    
      } // End switch
    } //End B()



  // *CHARACTER C FUNCTION*

    void C() { // First identifier has been C
    
      CodeIn = getChar(); // Get the second identifier
    
      switch(CodeIn) {
    
        case 'A': // CODE CA; LED SPEED_TRIM_FAIL
          valueCA = getChar();
          if (valueCA == '1'){ bitSet(SR_OUT_1,6); }
          else{ bitClear(SR_OUT_1,6); }
          update_SR_OUT_1(); 
        break;
    
        case 'B': // CODE CB; LED MACH_TRIM_FAIL
          valueCB = getChar();
          if (valueCB == '1'){ bitSet(SR_OUT_1,7); }
          else{ bitClear(SR_OUT_1,7); }
          update_SR_OUT_1(); 
        break;
    
        case 'C': // CODE CC; LED AUTO_SLAT_FAIL
          valueCC = getChar();
          if (valueCC == '1'){ bitSet(SR_OUT_2,0); }
          else{ bitClear(SR_OUT_2,0); }
          update_SR_OUT_1(); 
        break;
    
        case 'E': // CODE CE; LED YAW_DAMPER
          valueCE = getChar();
          if (valueCE == '1' && (aircraft_energy == 2 || aircraft_energy == 3)){ bitSet(SR_OUT_2,1); }
          else{ bitClear(SR_OUT_2,1); }
          update_SR_OUT_1();
        break;

        case 'F': // CODE CF; LED ENGINE_VALVE_CLOSED_1
          valueCF = getChar();
          if (valueCF == '1'){ bitSet(SR_OUT_2,2); }
          else{ bitClear(SR_OUT_2,2); }
          update_SR_OUT_1(); 
        break;
    
        case 'G': // CODE CG; LED ENGINE_VALVE_CLOSED_2
          valueCG = getChar();
          if (valueCG == '1'){ bitSet(SR_OUT_2,3); }
          else{ bitClear(SR_OUT_2,3); }
          update_SR_OUT_1(); 
        break;
    
        case 'H': // CODE CH; LED SPAR_VALVE_CLOSED_1
          valueCH = getChar();
          if (valueCH == '1'){ bitSet(SR_OUT_2,4); }
          else{ bitClear(SR_OUT_2,4); }
          update_SR_OUT_1(); 
        break;
    
        case 'I': // CODE CI; LED SPAR_VALVE_CLOSED_2
          valueCI = getChar();
          if (valueCI == '1'){ bitSet(SR_OUT_2,5); }
          else{ bitClear(SR_OUT_2,5); }
          update_SR_OUT_1();
        break;
    
        case 'J': // CODE CJ; LED FILTER_BYPASS_1
          valueCJ = getChar();
          if (valueCJ == '1'){ bitSet(SR_OUT_2,6); }
          else{ bitClear(SR_OUT_2,6); }
          update_SR_OUT_1();
        break;
    
        case 'K': // CODE CK; LED FILTER_BYPASS_2
          valueCK = getChar();
          if (valueCK == '1'){ bitSet(SR_OUT_2,7); }
          else{ bitClear(SR_OUT_2,7); }
          update_SR_OUT_1();
        break;
    
        case 'L': // CODE CL; LED VALVE_OPEN
          valueCL = getChar();
          if (valueCL == '1'){ bitSet(SR_OUT_3,0); }
          else{ bitClear(SR_OUT_3,0); }
          update_SR_OUT_1();
        break;
    
        case 'M': // CODE CM; LED FUEL_PUMP_LOW_PRESSURE_1
          valueCM = getChar();
          if (valueCM == '1'){ bitSet(SR_OUT_3,1); }
          else{ bitClear(SR_OUT_3,1); }
          update_SR_OUT_1();
        break;
    
        case 'N': // CODE CN; LED FUEL_PUMP_LOW_PRESSURE_2
          valueCN = getChar();
          if (valueCN == '1'){ bitSet(SR_OUT_3,2); }
          else{ bitClear(SR_OUT_3,2); }
          update_SR_OUT_1();
        break;
        
        case 'O': // CODE CO; LED AFT_LOW_PRESSURE_1
          valueCO = getChar();
          if (valueCO == '1'){ bitSet(SR_OUT_3,3); }
          else{ bitClear(SR_OUT_3,3); }
          update_SR_OUT_1();
        break;
    
        case 'P': // CODE CP; LED AFT_LOW_PRESSURE_2
          valueCP = getChar();
          if (valueCP == '1'){ bitSet(SR_OUT_3,4); }
          else{ bitClear(SR_OUT_3,4); }
          update_SR_OUT_1();
        break;
    
        case 'Q': // CODE CQ; LED FWD_LOW_PRESSURE_1
          valueCQ = getChar();
          if (valueCQ == '1'){ bitSet(SR_OUT_3,5); }
          else{ bitClear(SR_OUT_3,5); }
          update_SR_OUT_1();
        break;
    
        case 'R': // CODE CR; LED FWD_LOW_PRESSURE_2
          valueCR = getChar();
          if (valueCR == '1'){ bitSet(SR_OUT_3,6); }
          else{ bitClear(SR_OUT_3,6); }
          update_SR_OUT_1();
        break;

        case 'S': // CODE CS; DISPLAY DC_AMPS
          valueCS = "";
          while(Serial.available() > 0){
              valueCS += getChar(); //Get values from display's number
          }
          valueCSi = valueCS.toInt();
          updateDisplay_1();          
        break;

        case 'U': // CODE CU; DISPLAY CPS_FREQ
          valueCU = "";
          while(Serial.available() > 0){
              valueCU += getChar(); //Get values from display's number
          }
          valueCUi = valueCU.toInt();
          updateDisplay_2();                    
        break;

        case 'V': // CODE CV; DISPLAY DC VOLTS
          valueCV = "";
          while(Serial.available() > 0){
              valueCV += getChar(); //Get values from display's number
          }
          valueCVi = valueCV.toInt();
          updateDisplay_3();       
        break;

        case 'W': // CODE CW; DISPLAY AC AMPS
          valueCW = "";
          while(Serial.available() > 0){
              valueCW += getChar(); //Get values from display's number
          }
          valueCWi = valueCW.toInt();
          updateDisplay_4();                    
        break;

        case 'X': // CODE CX; DISPLAY AC VOLTS
          valueCX = "";
          while(Serial.available() > 0){
              valueCX += getChar(); //Get values from display's number
          }
          valueCXi = valueCX.toInt();
          updateDisplay_5();                    
        break;                                           

        case 'Y': // CODE CY; LED BAT_DISCHARGE
          valueCY = getChar();
          if (valueCY == '1'){ bitSet(SR_OUT_10,1); }
          else{ bitClear(SR_OUT_10,1); }
          update_SR_OUT_4(); 
        break;
    
        case 'Z': // CODE CZ; LED TR_UNIT
          valueCZ = getChar();
          if (valueCZ == '1'){ bitSet(SR_OUT_10,2); }
          else{ bitClear(SR_OUT_10,2); }
          update_SR_OUT_4();  
        break;        
    
     } // End switch
    } //End c()



  // *CHARACTER D FUNCTION*

    void D(){ // First identifier has been D 
    
      CodeIn = getChar(); // Get the second identifier
    
      switch(CodeIn) {
    
        case 'A': // CODE DA; LED ELEC
          valueDA = getChar();
          if (valueDA == '1'){ bitSet(SR_OUT_10,3); }
          else{ bitClear(SR_OUT_10,3); }
          update_SR_OUT_4(); 
        break;        

        case 'B': // CODE DB; LED STANDBY_POWER_OFF
          valueDB = getChar();
          if (valueDB == '1'){ bitSet(SR_OUT_10,4); }
          else{ bitClear(SR_OUT_10,4); }
          update_SR_OUT_4(); 
        break;
    
        case 'C': // CODE DC; LED DRIVE_1
          valueDC = getChar();
          if (valueDC == '1'){ bitSet(SR_OUT_10,5); }
          else{ bitClear(SR_OUT_10,5); }
          update_SR_OUT_4(); 
        break;
        
        case 'D': // CODE DD; LED DRIVE_2
          valueDD = getChar();
          if (valueDD == '1'){ bitSet(SR_OUT_10,6); }
          else{ bitClear(SR_OUT_10,6); }
          update_SR_OUT_4(); 
        break;
        
        case 'E': // CODE DE; LED GROUND_POWER_AVAILABLE
          valueDE = getChar();
          if (valueDE == '1'){ bitSet(SR_OUT_10,7); }
          else{ bitClear(SR_OUT_10,7); ground_power = 0;}
          update_SR_OUT_4(); 
        break;        
    
        case 'F': // CODE DF; LED TRANSFER_BUS_OFF_1
          valueDF = getChar();
          if (valueDF == '1'){ bitSet(SR_OUT_11,0); }
          else{ bitClear(SR_OUT_11,0); }
          update_SR_OUT_4(); 
        break;    
    
        case 'G': // CODE DG; LED TRANSFER_BUS_OFF_2
          valueDG = getChar();
          if (valueDG == '1'){ bitSet(SR_OUT_11,1); }
          else{ bitClear(SR_OUT_11,1); }
          update_SR_OUT_4(); 
        break;
    
        case 'H': // CODE DH; LED SOURCE_OFF_1
          valueDH = getChar();
          if (valueDH == '1'){ bitSet(SR_OUT_11,2); }
          else{ bitClear(SR_OUT_11,2); }
          update_SR_OUT_4(); 
        break;
    
        case 'I': // CODE DI; LED SOURCE_OFF_2
          valueDI = getChar();
          if (valueDI == '1'){ bitSet(SR_OUT_11,3); }
          else{ bitClear(SR_OUT_11,3); }
          update_SR_OUT_4(); 
        break;
    
        case 'J': // CODE DJ; LED GEN_OFF_BUS_1
          valueDJ = getChar();
          if (valueDJ == '1'){ bitSet(SR_OUT_11,4); }
          else{ bitClear(SR_OUT_11,4); }
          update_SR_OUT_4(); 
        break;
    
        case 'K': // CODE DK; LED GEN_OFF_BUS_2
          valueDK = getChar();
          if (valueDK == '1'){ bitSet(SR_OUT_11,5); }
          else{ bitClear(SR_OUT_11,5); }
          update_SR_OUT_4(); 
        break;
    
        case 'L': // CODE DL; LED APU_GEN_OFF_BUS
          valueDL = getChar();
          if (valueDL == '1'){ 
            bitSet(SR_OUT_11,6); 
            if(PRE_SWITCH_APU == 1){
              apu_power = 1;
            }
          }
          else{ bitClear(SR_OUT_11,6); }
          update_SR_OUT_4(); 
        break;

        case 'M': // CODE DM; LED APU_MAINT
          valueDM = getChar();
          if (valueDM == '1'){ bitSet(SR_OUT_11,7); }
          else{ bitClear(SR_OUT_11,7); }
          update_SR_OUT_4(); 
        break;

        case 'N': // CODE DN; LED LOW_OIL_PRESSURE
          valueDN = getChar();
          if (valueDN == '1'){ bitSet(SR_OUT_12,0); }
          else{ bitClear(SR_OUT_12,0); }
          update_SR_OUT_4(); 
        break;

        case 'O': // CODE DO; LED FAULT
          valueDO = getChar();
          if (valueDO == '1'){ bitSet(SR_OUT_12,1); }
          else{ bitClear(SR_OUT_12,1); }
          update_SR_OUT_4(); 
        break;

        case 'P': // CODE DP; LED OVER_SPEED
          valueDP = getChar();
          if (valueDP == '1'){ bitSet(SR_OUT_12,2); }
          else{ bitClear(SR_OUT_12,2); }
          update_SR_OUT_4(); 
        break;

        case 'R': // CODE DR; LED EQP_COOLING_SUPPLY
          valueDR = getChar();
          if (valueDR == '1'){ bitSet(SR_OUT_12,3); }
          else{ bitClear(SR_OUT_12,3); }
          update_SR_OUT_4(); 
        break;

        case 'S': // CODE DS; LED COOLING_EXHAUST
          valueDS = getChar();
          if (valueDS == '1'){ bitSet(SR_OUT_12,4); }
          else{ bitClear(SR_OUT_12,4); }
          update_SR_OUT_4(); 
        break;

        case 'T': // CODE DT; LED EMERGENCY_EXIT_NOT_ARMED
          valueDT = getChar();
          if (valueDT == '1'){ bitSet(SR_OUT_12,5); }
          else{ bitClear(SR_OUT_12,5); }
          update_SR_OUT_4(); 
        break;

        case 'U': // CODE DU; LED CALL
          valueDU = getChar();
          if (valueDU == '1'){ bitSet(SR_OUT_12,6); }
          else{ bitClear(SR_OUT_12,6); }
          update_SR_OUT_4(); 
        break;

        case 'W': // CODE DW; LED OVER_HEAT_1
          valueDW = getChar();
          if (valueDW == '1'){ bitSet(SR_OUT_13,0); }
          else{ bitClear(SR_OUT_13,0); }
          update_SR_OUT_13(); 
        break;

        case 'X': // CODE DX; LED LED_OVER_HEAT_2
          valueDX = getChar();
          if (valueDX == '1'){ bitSet(SR_OUT_13,1); }
          else{ bitClear(SR_OUT_13,1); }
          update_SR_OUT_13(); 
        break;

        case 'Y': // CODE DY; LED LED_OVER_HEAT_3
          valueDY = getChar();
          if (valueDY == '1'){ bitSet(SR_OUT_13,2); }
          else{ bitClear(SR_OUT_13,2); }
          update_SR_OUT_13(); 
        break;

        case 'Z': // CODE DZ; LED LED_OVER_HEAT_4
          valueDZ = getChar();
          if (valueDZ == '1'){ bitSet(SR_OUT_13,3); }
          else{ bitClear(SR_OUT_13,3); }
          update_SR_OUT_13(); 
        break;
        
     } // End switch
    } //End D()



  // *CHARACTER E FUNCTION*

    void E(){ // First identifier has been E 
    
      CodeIn = getChar(); // Get the second identifier
    
      switch(CodeIn) {
    
        case 'A': // CODE EA; LED WH_ON_1
          valueEA = getChar();
          if (valueEA == '1'){ bitSet(SR_OUT_13,4); }
          else{ bitClear(SR_OUT_13,4); }
          update_SR_OUT_13(); 
        break;        

        case 'B': // CODE EB; LED WH_ON_2
          valueEB = getChar();
          if (valueEB == '1'){ bitSet(SR_OUT_13,5); }
          else{ bitClear(SR_OUT_13,5); }
          update_SR_OUT_13(); 
        break;
    
        case 'C': // CODE EC; LED WH_ON_3
          valueEC = getChar();
          if (valueEC == '1'){ bitSet(SR_OUT_13,6); }
          else{ bitClear(SR_OUT_13,6); }
          update_SR_OUT_13(); 
        break;

        case 'D': // CODE ED; LED WH_ON_4
          valueED = getChar();
          if (valueED == '1'){ bitSet(SR_OUT_13,7); }
          else{ bitClear(SR_OUT_13,7); }
          update_SR_OUT_13(); 
        break;        
        
        case 'E': // CODE EE; LED CAPT_PITOT
          valueEE = getChar();
          if (valueEE == '1'){ bitSet(SR_OUT_14,0); }
          else{ bitClear(SR_OUT_14,0);}
          update_SR_OUT_13(); 
        break;        
    
        case 'F': // CODE EF; LED L_ELEV_PITOT
          valueEF = getChar();
          if (valueEF == '1'){ bitSet(SR_OUT_14,1); }
          else{ bitClear(SR_OUT_14,1); }
          update_SR_OUT_13(); 
        break;    
    
        case 'G': // CODE EG; LED L_ALPHA_VANE
          valueEG = getChar();
          if (valueEG == '1'){ bitSet(SR_OUT_14,2); }
          else{ bitClear(SR_OUT_14,2); }
          update_SR_OUT_13(); 
        break;
    
        case 'H': // CODE EH; LED TEMP_PROBE
          valueEH = getChar();
          if (valueEH == '1'){ bitSet(SR_OUT_14,3); }
          else{ bitClear(SR_OUT_14,3); }
          update_SR_OUT_13(); 
        break;
    
        case 'I': // CODE EI; LED FO_PITOT
          valueEI = getChar();
          if (valueEI == '1'){ bitSet(SR_OUT_14,4); }
          else{ bitClear(SR_OUT_14,4); }
          update_SR_OUT_13(); 
        break;
    
        case 'J': // CODE EJ; LED R_ELEV_PITOT
          valueEJ = getChar();
          if (valueEJ == '1'){ bitSet(SR_OUT_14,5); }
          else{ bitClear(SR_OUT_14,5); }
          update_SR_OUT_13(); 
        break;
    
        case 'K': // CODE EK; LED R_ALPHA_VANE
          valueEK = getChar();
          if (valueEK == '1'){ bitSet(SR_OUT_14,6); }
          else{ bitClear(SR_OUT_14,6); }
          update_SR_OUT_13(); 
        break;
    
        case 'L': // CODE EL; LED AUX_PITOT
          valueEL = getChar();
          if (valueEL == '1'){ bitSet(SR_OUT_14,7); }
          else{ bitClear(SR_OUT_14,7); }
          update_SR_OUT_13(); 
        break;

        case 'Q': // CODE EQ; LED COWL_ANIT_ICE_1
          valueEQ = getChar();
          if (valueEQ == '1'){ bitSet(SR_OUT_15,0); }
          else{ bitClear(SR_OUT_15,0); }
          update_SR_OUT_13(); 
        break;

        case 'R': // CODE ER; LED COWL_ANIT_ICE_2
          valueER = getChar();
          if (valueER == '1'){ bitSet(SR_OUT_15,1); }
          else{ bitClear(SR_OUT_15,1); }
          update_SR_OUT_13(); 
        break;

        case 'M': // CODE EM; LED L_VALVE_OPEN
          valueEM = getChar();
          if (valueEM == '1'){ bitSet(SR_OUT_15,2); }
          else{ bitClear(SR_OUT_15,2); }
          update_SR_OUT_13(); 
        break;

        case 'N': // CODE EN; LED R_VALVE_OPEN
          valueEN = getChar();
          if (valueEN == '1'){ bitSet(SR_OUT_15,3); }
          else{ bitClear(SR_OUT_15,3); }
          update_SR_OUT_13(); 
        break;

        case 'O': // CODE EO; LED COWL_VALVE_OPEN_1
          valueEO = getChar();
          if (valueEO == '1'){ bitSet(SR_OUT_15,4); }
          else{ bitClear(SR_OUT_15,4); }
          update_SR_OUT_13(); 
        break;

        case 'P': // CODE EP; LED COWL_VALVE_OPEN_2
          valueEP = getChar();
          if (valueEP == '1'){ bitSet(SR_OUT_15,5); }
          else{ bitClear(SR_OUT_15,5); }
          update_SR_OUT_13(); 
        break;

        case 'S': // CODE ES; LED HYD_OVER_HEAT_1
          valueES = getChar();
          if (valueES == '1'){ bitSet(SR_OUT_15,6); }
          else{ bitClear(SR_OUT_15,6); }
          update_SR_OUT_13(); 
        break;

        case 'T': // CODE ET; LED HYD_OVER_HEAT_2
          valueET = getChar();
          if (valueET == '1'){ bitSet(SR_OUT_15,7); }
          else{ bitClear(SR_OUT_15,7); }
          update_SR_OUT_13(); 
        break;

        case 'U': // CODE EU; LED LOW_PRESSURE_ENG_1
          valueEU = getChar();
          if (valueEU == '1'){ bitSet(SR_OUT_16,0); }
          else{ bitClear(SR_OUT_16,0); }
          update_SR_OUT_13(); 
        break;

        case 'V': // CODE EV; LED LOW_PRESSURE_ENG_2
          valueEV = getChar();
          if (valueEV == '1'){ bitSet(SR_OUT_16,1); }
          else{ bitClear(SR_OUT_16,1); }
          update_SR_OUT_13(); 
        break;

        case 'W': // CODE EW; LED LOW_PRESSURE_ELEC_1
          valueEW = getChar();
          if (valueEW == '1'){ bitSet(SR_OUT_16,3); }
          else{ bitClear(SR_OUT_16,3); }
          update_SR_OUT_13(); 
        break;

        case 'X': // CODE EX; LED LOW_PRESSURE_ELEC_2
          valueEX = getChar();
          if (valueEX == '1'){ bitSet(SR_OUT_16,2); }
          else{ bitClear(SR_OUT_16,2); }
          update_SR_OUT_13(); 
        break;

        case 'Y': // CODE EY; LED FWD_ENTRY
          valueEY = getChar();
          if (valueEY == '1'){ bitSet(SR_OUT_16,4); }
          else{ bitClear(SR_OUT_16,4); }
          update_SR_OUT_13(); 
        break;

        case 'Z': // CODE EZ; LED FWD_SERVICE
          valueEZ = getChar();
          if (valueEZ == '1'){ bitSet(SR_OUT_16,5); }
          else{ bitClear(SR_OUT_16,5); }
          update_SR_OUT_13(); 
        break;
        
     } // End switch
    } //End E()



  // *CHARACTER F FUNCTION*

    void EFE(){ // First identifier has been F 
    
      CodeIn = getChar(); // Get the second identifier
    
      switch(CodeIn) {       

        case 'B': // CODE FB; LED LEFT_FWD_OVERWING
          valueFB = getChar();
          if (valueFB == '1'){ bitSet(SR_OUT_16,6); }
          else{ bitClear(SR_OUT_16,6); }
          update_SR_OUT_13(); 
        break;
    
        case 'C': // CODE FC; LED RIGHT_FWD_OVERWING
          valueFC = getChar();
          if (valueFC == '1'){ bitSet(SR_OUT_16,7); }
          else{ bitClear(SR_OUT_16,7); }
          update_SR_OUT_13(); 
        break;

        case 'D': // CODE FD; LED FWD_CARGO
          valueFD = getChar();
          if (valueFD == '1'){ bitSet(SR_OUT_17,0); }
          else{ bitClear(SR_OUT_17,0); }
          update_SR_OUT_13(); 
        break;        
        
        case 'E': // CODE FE; LED EQUIP
          valueFE = getChar();
          if (valueFE == '1'){ bitSet(SR_OUT_17,1); }
          else{ bitClear(SR_OUT_17,1);}
          update_SR_OUT_13(); 
        break;        
    
        case 'F': // CODE FF; LED LEFT_AFT_OVERWING
          valueFF = getChar();
          if (valueFF == '1'){ bitSet(SR_OUT_17,2); }
          else{ bitClear(SR_OUT_17,2); }
          update_SR_OUT_13(); 
        break;    
    
        case 'G': // CODE FG; LED RIGHT_AFT_OVERWING
          valueFG = getChar();
          if (valueFG == '1'){ bitSet(SR_OUT_17,3); }
          else{ bitClear(SR_OUT_17,3); }
          update_SR_OUT_13(); 
        break;
    
        case 'H': // CODE FH; LED AFT_CARGO
          valueFH = getChar();
          if (valueFH == '1'){ bitSet(SR_OUT_17,4); }
          else{ bitClear(SR_OUT_17,4); }
          update_SR_OUT_13(); 
        break;
    
        case 'I': // CODE FI; LED AFT_ENTRY
          valueFI = getChar();
          if (valueFI == '1'){ bitSet(SR_OUT_17,5); }
          else{ bitClear(SR_OUT_17,5); }
          update_SR_OUT_13(); 
        break;
    
        case 'J': // CODE FJ; LED AFT_SERVICE
          valueFJ = getChar();
          if (valueFJ == '1'){ bitSet(SR_OUT_17,6); }
          else{ bitClear(SR_OUT_17,6); }
          update_SR_OUT_13(); 
        break;

        case 'O': // CODE FO; LED ZONE_TEMP_1
          valueFO = getChar();
          if (valueFO == '1'){ bitSet(SR_OUT_18,0); }
          else{ bitClear(SR_OUT_18,0); }
          update_SR_OUT_13(); 
        break;

        case 'P': // CODE FP; LED ZONE_TEMP_2
          valueFP = getChar();
          if (valueFP == '1'){ bitSet(SR_OUT_18,1); }
          else{ bitClear(SR_OUT_18,1); }
          update_SR_OUT_13(); 
        break;

        case 'Q': // CODE FQ; LED ZONE_TEMP_3
          valueFQ = getChar();
          if (valueFQ == '1'){ bitSet(SR_OUT_18,2); }
          else{ bitClear(SR_OUT_18,2); }
          update_SR_OUT_13(); 
        break;

        case 'R': // CODE FR; LED DUAL_BLEED
          valueFR = getChar();
          if (valueFR == '1'){ bitSet(SR_OUT_18,3); }
          else{ bitClear(SR_OUT_18,3); }
          update_SR_OUT_13(); 
        break;

        case 'S': // CODE FS; LED RAM_DOOR_FULL_OPEN_1
          valueFS = getChar();
          if (valueFS == '1'){ bitSet(SR_OUT_18,4); }
          else{ bitClear(SR_OUT_18,4); }
          update_SR_OUT_13(); 
        break;

        case 'T': // CODE FT; LED RAM_DOOR_FULL_OPEN_2
          valueFT = getChar();
          if (valueFT == '1'){ bitSet(SR_OUT_18,5); }
          else{ bitClear(SR_OUT_18,5); }
          update_SR_OUT_13(); 
        break;

        case 'U': // CODE FU; LED PACK_TRIP_OFF_1
          valueFU = getChar();
          if (valueFU == '1'){ bitSet(SR_OUT_18,6); }
          else{ bitClear(SR_OUT_18,6); }
          update_SR_OUT_13(); 
        break;

        case 'V': // CODE FU; LED PACK_TRIP_OFF_2
          valueFU = getChar();
          if (valueFU == '1'){ bitSet(SR_OUT_18,7); }
          else{ bitClear(SR_OUT_18,7); }
          update_SR_OUT_13(); 
        break;

        case 'W': // CODE FW; LED WING_BODY_OVER_HEAT_1
          valueFW = getChar();
          if (valueFW == '1'){ bitSet(SR_OUT_19,0); }
          else{ bitClear(SR_OUT_19,0); }
          update_SR_OUT_19(); 
        break;

        case 'X': // CODE FX; LED WING_BODY_OVER_HEAT_2
          valueFX = getChar();
          if (valueFX == '1'){ bitSet(SR_OUT_19,1); }
          else{ bitClear(SR_OUT_19,1); }
          update_SR_OUT_19(); 
        break;

        case 'Y': // CODE FY; LED BLEED_TRIP_OFF_1
          valueFY = getChar();
          if (valueFY == '1'){ bitSet(SR_OUT_19,2); }
          else{ bitClear(SR_OUT_19,2); }
          update_SR_OUT_19(); 
        break;

        case 'Z': // CODE FZ; LED BLEED_TRIP_OFF_2
          valueFZ = getChar();
          if (valueFZ == '1'){ bitSet(SR_OUT_19,3); }
          else{ bitClear(SR_OUT_19,3); }
          update_SR_OUT_19(); 
        break;
        
     } // End switch
    } //End F()    



  // *CHARACTER G FUNCTION*

    void G(){ // First identifier has been G 
    
      CodeIn = getChar(); // Get the second identifier
    
      switch(CodeIn) {       

        case 'C': // CODE GC; LED AUTO_FAIL
          valueGC = getChar();
          if (valueGC == '1'){ bitSet(SR_OUT_19,4); }
          else{ bitClear(SR_OUT_19,4); }
          update_SR_OUT_19(); 
        break;
    
        case 'D': // CODE GD; LED OFF_SCHED_DESCENT
          valueGD = getChar();
          if (valueGD == '1'){ bitSet(SR_OUT_19,5); }
          else{ bitClear(SR_OUT_19,5); }
          update_SR_OUT_19(); 
        break;

        case 'E': // CODE GE; LED ALTN
          valueGE = getChar();
          if (valueGE == '1'){ bitSet(SR_OUT_19,6); }
          else{ bitClear(SR_OUT_19,6); }
          update_SR_OUT_19(); 
        break;        
        
        case 'F': // CODE GF; LED MANUAL
          valueGF = getChar();
          if (valueGF == '1'){ bitSet(SR_OUT_19,7); }
          else{ bitClear(SR_OUT_19,7);}
          update_SR_OUT_19(); 
        break;

        case 'G': // CODE GG; DISPLAY FLT_ALT
          valueGG = "";
          while(Serial.available() > 0){
              valueGG += getChar(); //Get values from display's number
          }
          valueGGi = valueGG.toInt();
          updateDisplay_6();          
        break;                

        case 'H': // CODE GH; DISPLAY LAND_ALT
          valueGH = "";
          while(Serial.available() > 0){
              valueGH += getChar(); //Get values from display's number
          }
          valueGHi = valueGH.toInt();
          updateDisplay_7();          
        break;
        
     } // End switch
    } //End G()    



  // *CHARACTER Z FUNCTION*

    void Z(){ // First identifier has been Z 
    
      CodeIn = getChar(); // Get the second identifier
    
      switch(CodeIn) {
    
        case 'b': // CODE Zb; SERVO SELECTOR_ENGINE_STATOR
          prevalueZb = valueZb;
          valueZb = getChar();
          if ( (valueZb == '1') && (prevalueZb == '0') ){

            SERVO_SELECTOR_ENGINE_STARTOR.Attach();  
            SERVO_SELECTOR_ENGINE_STARTOR.Update(0, 70);
            delay(300);
            SERVO_SELECTOR_ENGINE_STARTOR.Update(0, 105);
            lastUpdateServo = millis();
            
          }
        break;
    
        case 'c': // CODE Zc; SERVO SELECTOR_ENGINE_STATOR
          prevalueZc = valueZc;
          valueZc = getChar();
          if ( (valueZc == '1') && (prevalueZc == '0') ){
   
            SERVO_SELECTOR_ENGINE_STARTOR.Attach();  
            SERVO_SELECTOR_ENGINE_STARTOR.Update(0, 70);
            delay(300);
            SERVO_SELECTOR_ENGINE_STARTOR.Update(0, 105);
            lastUpdateServo = millis();
            
          }
        break;

        case 'L': // CODE ZL; ELECTRICAL METERING PANEL
          valueCS = "";
          valueCU = "";
          valueCV = "";
          valueCW = "";
          valueCX = "";
          display_received = 1;
          while(Serial.available() > 0){
            incomingChar = Serial.read(); //Get values from display's number
            if(incomingChar != 'F' && incomingChar != '&' && incomingChar != '$' && display_received == 1){
              valueCS += incomingChar; //Get values from display's number
            }
            if(incomingChar == '&' && display_received == 1){
              display_received = 2;
              incomingChar = ' ';
            }
            if(incomingChar == '&' && display_received == 2){
              display_received = 3;
              incomingChar = ' ';
            }
            if(incomingChar != 'F' && incomingChar != '&' && incomingChar != '$' && display_received == 3){
              valueCU += incomingChar; //Get values from display's number
            }
            if(incomingChar == '$' && display_received == 3){
              display_received = 4;
              incomingChar = ' ';
            }
            if(incomingChar != 'F' && incomingChar != '&' && incomingChar != '$' && display_received == 4){
              valueCV += incomingChar; //Get values from display's number
            }
            if(incomingChar == '&' && display_received == 4){
              display_received = 5;
              incomingChar = ' ';
            }
            if(incomingChar != 'F' && incomingChar != '&' && incomingChar != '$' && display_received == 5){
              valueCW += incomingChar; //Get values from display's number
            }
            if(incomingChar == '&' && display_received == 5){
              display_received = 6;
              incomingChar = ' ';
            }
            if(incomingChar != 'F' && incomingChar != '&' && incomingChar != '$' && display_received == 6){
              valueCX += incomingChar; //Get values from display's number
            }
          }
          valueCSi = valueCS.toInt();
          valueCUi = valueCU.toInt();
          valueCVi = valueCV.toInt();
          valueCWi = valueCW.toInt();
          valueCXi = valueCX.toInt();
          updateDisplay_1();
          updateDisplay_2(); 
          updateDisplay_3(); 
          updateDisplay_4(); 
          updateDisplay_5();           
        break;
        
     } // End switch
    } //End Z()



  // *CHARACTER $ FUNCTION*

    void DOLLAR(){ // First identifier has been $
    
      CodeIn = getChar(); //Get the second identifier
    
      switch(CodeIn) {
    
        case 'B': // CODE $B; SERVO_FUEL_TEMP

            valueDOLLARB = "";
            while(Serial.available() > 0){
              valueDOLLARB += getChar(); //Get values from servo position
            }
            valueDOLLARBi = valueDOLLARB.toInt();
            pos_servo_fuel_temp = map(valueDOLLARBi, 30, 68, 112, 130);
          
          if (servo_activated_1 == 1 && valueDOLLARBi != 0){                
            SERVO_FUEL_TEMP.Attach();
            SERVO_FUEL_TEMP.Update(0, pos_servo_fuel_temp);
            lastUpdateServo = millis();
          }
          
        break;

        case 'C': // CODE $C; SERVO_EGT_APU

            valueDOLLARC = "";
            while(Serial.available() > 0){
              valueDOLLARC += getChar(); //Get values from servo position
            }
            valueDOLLARCi = valueDOLLARC.toInt();
            pos_servo_egt_apu = map(valueDOLLARCi, 0, 1000, 10, 162);
            
            if (servo_activated_2 == 1 && valueDOLLARCi != 0){
              SERVO_EGT_APU.Attach();
              SERVO_EGT_APU.Update(0, pos_servo_egt_apu);
              lastUpdateServo = millis();
            }
            
        break;

        case 'D': // CODE $D; SERVO_CAB_TEMP

            valueDOLLARD = "";
            while(Serial.available() > 0){
              valueDOLLARD += getChar(); //Get values from servo position
            }
            valueDOLLARDi = valueDOLLARD.toInt();
            pos_servo_cab_temp = map(valueDOLLARDi, 20, 40, 36, 70);

            if (servo_activated_1 == 1 && valueDOLLARDi != 0){                
              SERVO_CAB_TEMP.Attach();
              SERVO_CAB_TEMP.Update(0, pos_servo_cab_temp);
              lastUpdateServo = millis();
            }
          
        break;

        case 'E': // CODE $E; SERVO_DUCT_PRESS_L

            valueDOLLARE = "";
            while(Serial.available() > 0){
              valueDOLLARE += getChar(); //Get values from servo position
            }
            valueDOLLAREi = valueDOLLARE.toInt();
            pos_servo_duct_press_l = map(valueDOLLAREi, 0, 80, 12, 153);

            if (servo_activated_1 == 1 && valueDOLLAREi != 0){                
              SERVO_DUCT_PRESS_L.Attach();
              SERVO_DUCT_PRESS_L.Update(0, pos_servo_duct_press_l);
              lastUpdateServo = millis();
            }
          
        break;

        case 'F': // CODE $F; SERVO_DUCT_PRESS_R

            valueDOLLARF = "";
            while(Serial.available() > 0){
              valueDOLLARF += getChar(); //Get values from servo position
            }
            valueDOLLARFi = valueDOLLARF.toInt();
            pos_servo_duct_press_r = map(valueDOLLARFi, 413, 445, 28, 82);
            if(valueDOLLARFi < 400 && valueDOLLARFi != 0){
              pos_servo_duct_press_r = 12;
            }
            if (servo_activated_1 == 1 && valueDOLLARFi != 0){                
              SERVO_DUCT_PRESS_R.Attach();
              SERVO_DUCT_PRESS_R.Update(0, pos_servo_duct_press_r);
              lastUpdateServo = millis();
            }

        break;                

        case 'G': // CODE $G; SERVO_CABIN_ALT_INT

            valueDOLLARG = "";
            while(Serial.available() > 0){
              valueDOLLARG += getChar(); //Get values from servo position
            }
            valueDOLLARGi = valueDOLLARG.toInt();
            pos_servo_cabin_alt_int = map(valueDOLLARGi, 0, 5, 15, 48);

            if (servo_activated_1 == 1 && valueDOLLARGi != 0){                
              SERVO_CABIN_ALT_INT.Attach();
              SERVO_CABIN_ALT_INT.Update(0, pos_servo_cabin_alt_int);
              lastUpdateServo = millis();
            }
          
        break;

        case 'H': // CODE $H; SERVO_CABIN_ALT_EXT

            valueDOLLARH = "";
            while(Serial.available() > 0){
              valueDOLLARH += getChar(); //Get values from servo position
            }
            valueDOLLARHi = valueDOLLARH.toInt();
            pos_servo_cabin_alt_ext = map(valueDOLLARHi, 0, 100, 20, 163);

            if (servo_activated_1 == 1 && valueDOLLARHi != 0){                
              SERVO_CABIN_ALT_EXT.Attach();
              SERVO_CABIN_ALT_EXT.Update(0, pos_servo_cabin_alt_ext);
              lastUpdateServo = millis();
            }
          
        break;                

        case 'I': // CODE $I; SERVO_CABIN_CLIMB

            valueDOLLARI = "";
            while(Serial.available() > 0){
              valueDOLLARI += getChar(); //Get values from servo position
            }
            valueDOLLARIi = valueDOLLARI.toInt();

            pos_servo_cabin_climb = map(valueDOLLARIi, 800, 1300, 91, 114);

            if (servo_activated_2 == 1 && valueDOLLARIi > 0 && valueDOLLARIi <= 1600){                
              SERVO_CABIN_CLIMB.Attach();
              SERVO_CABIN_CLIMB.Update(0, pos_servo_cabin_climb);
              lastUpdateServo = millis();
            }
          
        break;
        
        case 'J': // CODE $J; SERVO_MANUAL_VALVE

            valueDOLLARJ = "";
            while(Serial.available() > 0){
              valueDOLLARJ += getChar(); //Get values from servo position
            }
            valueDOLLARJi = valueDOLLARJ.toInt();
            pos_servo_manual_valve = map(valueDOLLARJi, 0, 100, 165, 36);

            if (servo_activated_1 == 1 && valueDOLLARJi != 0){                
              SERVO_MANUAL_VALVE.Attach();
              SERVO_MANUAL_VALVE.Update(0, pos_servo_manual_valve);
              lastUpdateServo = millis();
            }
          
        break;  
    
     } // End switch
    } //End $()



  // *UPDATE SR_OUT_1 FUNCTION*

    void update_SR_OUT_1() { // Sends the data to SR_OUT_1
      
      if ((millis() - lastUpdateLED) > 0.01){
        
        digitalWrite(latchPin_OUT_1,LOW);
        shiftOut(dataPin_OUT_1, clockPin_OUT_1, MSBFIRST, SR_OUT_3);
        shiftOut(dataPin_OUT_1, clockPin_OUT_1, MSBFIRST, SR_OUT_2);
        shiftOut(dataPin_OUT_1, clockPin_OUT_1, MSBFIRST, SR_OUT_1);
        digitalWrite(latchPin_OUT_1, HIGH);
        lastUpdateLED = millis();  
        
      }

      
    } //End update_SR_OUT_1()



  // *UPDATE SR_OUT_4 FUNCTION*

    void update_SR_OUT_4() { // Sends the data to SR_OUT_4
      
      if ((millis() - lastUpdateLED) > 0.01){
        
        digitalWrite(latchPin_OUT_4,LOW);
        shiftOut(dataPin_OUT_4, clockPin_OUT_4, MSBFIRST, SR_OUT_12);
        shiftOut(dataPin_OUT_4, clockPin_OUT_4, MSBFIRST, SR_OUT_11);
        shiftOut(dataPin_OUT_4, clockPin_OUT_4, MSBFIRST, SR_OUT_10);
        shiftOut(dataPin_OUT_4, clockPin_OUT_4, MSBFIRST, SR_OUT_9);
        shiftOut(dataPin_OUT_4, clockPin_OUT_4, MSBFIRST, SR_OUT_8);
        shiftOut(dataPin_OUT_4, clockPin_OUT_4, MSBFIRST, SR_OUT_7);
        shiftOut(dataPin_OUT_4, clockPin_OUT_4, MSBFIRST, SR_OUT_6);
        shiftOut(dataPin_OUT_4, clockPin_OUT_4, MSBFIRST, SR_OUT_5);
        shiftOut(dataPin_OUT_4, clockPin_OUT_4, MSBFIRST, SR_OUT_4);
        digitalWrite(latchPin_OUT_4, HIGH);
        lastUpdateLED = millis();  
        
      }

      
    } //End update_SR_OUT_4()    



  // *UPDATE SR_OUT_13 FUNCTION*

    void update_SR_OUT_13() { // Sends the data to SR_OUT_13
      
      if ((millis() - lastUpdateLED) > 0.01){
        
        digitalWrite(latchPin_OUT_13,LOW);
        shiftOut(dataPin_OUT_13, clockPin_OUT_13, MSBFIRST, SR_OUT_18);
        shiftOut(dataPin_OUT_13, clockPin_OUT_13, MSBFIRST, SR_OUT_17);
        shiftOut(dataPin_OUT_13, clockPin_OUT_13, MSBFIRST, SR_OUT_16);
        shiftOut(dataPin_OUT_13, clockPin_OUT_13, MSBFIRST, SR_OUT_15);
        shiftOut(dataPin_OUT_13, clockPin_OUT_13, MSBFIRST, SR_OUT_14);
        shiftOut(dataPin_OUT_13, clockPin_OUT_13, MSBFIRST, SR_OUT_13);
        digitalWrite(latchPin_OUT_13, HIGH);
        lastUpdateLED = millis();  
        
      }

      
    } //End update_SR_OUT_13()



  // *UPDATE SR_OUT_19 FUNCTION*

    void update_SR_OUT_19() { // Sends the data to SR_OUT_19
      
      if ((millis() - lastUpdateLED) > 0.01){
        
        digitalWrite(latchPin_OUT_19,LOW);
        shiftOut(dataPin_OUT_19, clockPin_OUT_19, MSBFIRST, SR_OUT_22);
        shiftOut(dataPin_OUT_19, clockPin_OUT_19, MSBFIRST, SR_OUT_21);
        shiftOut(dataPin_OUT_19, clockPin_OUT_19, MSBFIRST, SR_OUT_20);
        shiftOut(dataPin_OUT_19, clockPin_OUT_19, MSBFIRST, SR_OUT_19);
        digitalWrite(latchPin_OUT_19, HIGH);
        lastUpdateLED = millis();  
        
      }

      
    } //End update_SR_OUT_19()



  // *UPDATE SR_IN_5 FUNCTION*

    SR_IN_1_T update_SR_IN_5() { // Receive the data from SR_IN_5 to SR_IN_7
        
        long bitVal;
        SR_IN_1_T bytesVal= 0;
        
    
        /* Trigger a parallel Load to latch the state of the data lines,
        */
        digitalWrite(clockEnablePin_IN_1, HIGH);
        digitalWrite(ploadPin_IN_1, LOW);
        delayMicroseconds(PULSE_WIDTH_USEC);
        digitalWrite(ploadPin_IN_1, HIGH);
        digitalWrite(clockEnablePin_IN_1, LOW);
    
        /* Loop to read each bit value from the serial out line
         * of the SN74HC165N.
        */
        for(int i = 0; i < (DATA_WIDTH_1-32); i++)
        {
            bitVal = digitalRead(dataPin_IN_1);
    
            /* Set the corresponding bit in bytesVal.
            */
            bytesVal |= (bitVal << ((DATA_WIDTH_1-33) - i));
    
            /* Pulse the Clock (rising edge shifts the next bit).
            */
            digitalWrite(clockPin_IN_1, HIGH);
            delayMicroseconds(PULSE_WIDTH_USEC);
            digitalWrite(clockPin_IN_1, LOW);
        }

        return(bytesVal);
        
    }//End update_SR_IN_5() 



  // *UPDATE SR_IN_1 FUNCTION*

    SR_IN_1_T update_SR_IN_1() { // Receive the data from SR_IN_1 to SR_IN_4
        
        long bitVal;
        SR_IN_1_T bytesVal= 0;

    
        /* Loop to read each bit value from the serial out line
         * of the SN74HC165N.
        */
        for(int i = 24; i < DATA_WIDTH_1; i++)
        {
            bitVal = digitalRead(dataPin_IN_1);
    
            /* Set the corresponding bit in bytesVal.
            */
            bytesVal |= (bitVal << ((DATA_WIDTH_1-1) - i));
    
            /* Pulse the Clock (rising edge shifts the next bit).
            */
            digitalWrite(clockPin_IN_1, HIGH);
            delayMicroseconds(PULSE_WIDTH_USEC);
            digitalWrite(clockPin_IN_1, LOW);
        }
    
        return(bytesVal);
        
    }//End update_SR_IN_1()
                


  // *UPDATE SR_IN_12 FUNCTION*

    SR_IN_8_T update_SR_IN_12() { // Receive the data from SR_IN_12 to SR_IN_14
        
        long bitVal;
        SR_IN_8_T bytesVal= 0;
        
    
        /* Trigger a parallel Load to latch the state of the data lines,
        */
        digitalWrite(clockEnablePin_IN_8, HIGH);
        digitalWrite(ploadPin_IN_8, LOW);
        delayMicroseconds(PULSE_WIDTH_USEC);
        digitalWrite(ploadPin_IN_8, HIGH);
        digitalWrite(clockEnablePin_IN_8, LOW);
    
        /* Loop to read each bit value from the serial out line
         * of the SN74HC165N.
        */
        for(int i = 0; i < (DATA_WIDTH_8-32); i++)
        {
            bitVal = digitalRead(dataPin_IN_8);
    
            /* Set the corresponding bit in bytesVal.
            */
            bytesVal |= (bitVal << ((DATA_WIDTH_8-33) - i));
    
            /* Pulse the Clock (rising edge shifts the next bit).
            */
            digitalWrite(clockPin_IN_8, HIGH);
            delayMicroseconds(PULSE_WIDTH_USEC);
            digitalWrite(clockPin_IN_8, LOW);
        }

        return(bytesVal);
        
    }//End update_SR_IN_12()



  // *UPDATE SR_IN_8 FUNCTION*

    SR_IN_8_T update_SR_IN_8() { // Receive the data from SR_IN_8 to SR_IN_11
        
        long bitVal;
        SR_IN_8_T bytesVal= 0;

    
        /* Loop to read each bit value from the serial out line
         * of the SN74HC165N.
        */
        for(int i = 24; i < DATA_WIDTH_8; i++)
        {
            bitVal = digitalRead(dataPin_IN_8);
    
            /* Set the corresponding bit in bytesVal.
            */
            bytesVal |= (bitVal << ((DATA_WIDTH_8-1) - i));
    
            /* Pulse the Clock (rising edge shifts the next bit).
            */
            digitalWrite(clockPin_IN_8, HIGH);
            delayMicroseconds(PULSE_WIDTH_USEC);
            digitalWrite(clockPin_IN_8, LOW);
        }
    
        return(bytesVal);
        
    }//End update_SR_IN_8()



  // *UPDATE SR_IN_15 FUNCTION*

    SR_IN_15_T update_SR_IN_15() { // Receive the data from SR_IN_15 to SR_IN_18
        
        long bitVal;
        SR_IN_15_T bytesVal= 0;

    
        /* Loop to read each bit value from the serial out line
         * of the SN74HC165N.
        */
        for(int i = 8; i < DATA_WIDTH_15; i++)
        {
            bitVal = digitalRead(dataPin_IN_15);
    
            /* Set the corresponding bit in bytesVal.
            */
            bytesVal |= (bitVal << ((DATA_WIDTH_15-1) - i));
    
            /* Pulse the Clock (rising edge shifts the next bit).
            */
            digitalWrite(clockPin_IN_15, HIGH);
            delayMicroseconds(PULSE_WIDTH_USEC);
            digitalWrite(clockPin_IN_15, LOW);
        }
    
        return(bytesVal);
        
    }//End update_SR_IN_15()    
    

  // *UPDATE SR_IN_19 FUNCTION*

    SR_IN_15_T update_SR_IN_19() { // Receive the data from SR_IN_19
        
        long bitVal;
        SR_IN_15_T bytesVal= 0;
        
    
        /* Trigger a parallel Load to latch the state of the data lines,
        */
        digitalWrite(clockEnablePin_IN_15, HIGH);
        digitalWrite(ploadPin_IN_15, LOW);
        delayMicroseconds(PULSE_WIDTH_USEC);
        digitalWrite(ploadPin_IN_15, HIGH);
        digitalWrite(clockEnablePin_IN_15, LOW);
    
        /* Loop to read each bit value from the serial out line
         * of the SN74HC165N.
        */
        for(int i = 0; i < (DATA_WIDTH_15-32); i++)
        {
            bitVal = digitalRead(dataPin_IN_15);
    
            /* Set the corresponding bit in bytesVal.
            */
            bytesVal |= (bitVal << ((DATA_WIDTH_15-33) - i));
    
            /* Pulse the Clock (rising edge shifts the next bit).
            */
            digitalWrite(clockPin_IN_15, HIGH);
            delayMicroseconds(PULSE_WIDTH_USEC);
            digitalWrite(clockPin_IN_15, LOW);
        }

        return(bytesVal);
        
    }//End update_SR_IN_19()


    
  // *MODIFY SWITCH VALUES 1 FUNCTION*

    void modify_switch_values_1(){ //Modifies the SWITCH values asociated with SR_IN_1 to SR_IN_7
       
        for(int i = 0; i < DATA_WIDTH_1; i++){
          
           switch(i){
            
              case 0: // PIN D0_1; SWITCH_STBY_RUD_A1; CODE HS
                   if((SR_IN_1 >> i) & 1){SWITCH_STBY_RUD_A1 = 1;}
                   else{SWITCH_STBY_RUD_A1 = 0;}
              break;
    
              case 1: // PIN D1_1; SWITCH_STBY_RUD_A2; CODE HS
                   if((SR_IN_1 >> i) & 1){SWITCH_STBY_RUD_A2 = 1;}
                   else{SWITCH_STBY_RUD_A2 = 0;}
              break;
    
              case 2: // PIN D2_1; SWITCH_STBY_RUD_B1; CODE HT
                   if((SR_IN_1 >> i) & 1){SWITCH_STBY_RUD_B1 = 1;}
                   else{SWITCH_STBY_RUD_B1 = 0;}
              break;
    
              case 3: // PIN D3_1; SWITCH_STBY_RUD_B2; CODE HT
                   if((SR_IN_1 >> i) & 1){SWITCH_STBY_RUD_B2 = 1;}
                   else{SWITCH_STBY_RUD_B2 = 0;}
              break;
    
              case 4: // PIN D4_1; SWITCH_ALTERNATE_FLAPS; CODE HU
                   if((SR_IN_1 >> i) & 1){SWITCH_ALTERNATE_FLAPS = 1;}
                   else{SWITCH_ALTERNATE_FLAPS = 0;}
              break;
    
              case 5: // PIN D5_1; SWITCH_FLAPS_POS_1; CODE HV
                   if((SR_IN_1 >> i) & 1){SWITCH_FLAPS_POS_1 = 1;}
                   else{SWITCH_FLAPS_POS_1 = 0;}
              break;
    
              case 6: // PIN D6_1; SWITCH_FLAPS_POS_2; CODE HV
                   if((SR_IN_1 >> i) & 1){SWITCH_FLAPS_POS_2 = 1;}
                   else{SWITCH_FLAPS_POS_2 = 0;}
              break;
    
              case 7: // PIN D7_1; SWITCH_SPOILER_A; CODE HW
                   if((SR_IN_1 >> i) & 1){SWITCH_SPOILER_A = 1;}
                   else{SWITCH_SPOILER_A = 0;}
              break;
    
              case 8: // PIN D0_2; SWITCH_SPOILER_B; CODE HX
                   if((SR_IN_1 >> i) & 1){SWITCH_SPOILER_B = 1;}
                   else{SWITCH_SPOILER_B = 0;}
              break;
    
              case 9: // PIN D1_2; SWITCH_YAW_DAMPER; CODE HY
                   if((SR_IN_1 >> i) & 1){SWITCH_YAW_DAMPER = 1;}
                   else{SWITCH_YAW_DAMPER = 0;}
              break;

              case 10: // PIN D2_2; SWITCH_VHF_NAVIGATION_1; CODE HZ
                   if((SR_IN_1 >> i) & 1){SWITCH_VHF_NAVIGATION_1 = 1;}
                   else{SWITCH_VHF_NAVIGATION_1 = 0;}
              break;
    
              case 11: // PIN D3_2; SWITCH_VHF_NAVIGATION_2; CODE HZ
                   if((SR_IN_1 >> i) & 1){SWITCH_VHF_NAVIGATION_2 = 1;}
                   else{SWITCH_VHF_NAVIGATION_2 = 0;}
              break;
    
              case 12: // PIN D4_2; SWITCH_IRS_SELECTOR_1; CODE IA
                   if((SR_IN_1 >> i) & 1){SWITCH_IRS_SELECTOR_1 = 1;}
                   else{SWITCH_IRS_SELECTOR_1 = 0;}
              break;
    
              case 13: // PIN D5_2; SWITCH_IRS_SELECTOR_2; CODE IA
                   if((SR_IN_1 >> i) & 1){SWITCH_IRS_SELECTOR_2 = 1;}
                   else{SWITCH_IRS_SELECTOR_2 = 0;}
              break;
    
              case 14: // PIN D6_2; SWITCH_FMC_1; CODE IB
                   if((SR_IN_1 >> i) & 1){SWITCH_FMC_1 = 1;}
                   else{SWITCH_FMC_1 = 0;}
              break;
    
              case 15: // PIN D7_2; SWITCH_FMC_2; CODE IB
                   if((SR_IN_1 >> i) & 1){SWITCH_FMC_2 = 1;}
                   else{SWITCH_FMC_2 = 0;}
              break;
    
              case 16: // PIN D0_3; SELECTOR_DISPLAY_SOURCE_1; CODE IC
                   if((SR_IN_1 >> i) & 1){SELECTOR_DISPLAY_SOURCE_1 = 1;}
                   else{SELECTOR_DISPLAY_SOURCE_1 = 0;}
              break;
    
              case 17: // PIN D1_3; SELECTOR_DISPLAY_SOURCE_2; CODE IC
                   if((SR_IN_1 >> i) & 1){SELECTOR_DISPLAY_SOURCE_2 = 1;}
                   else{SELECTOR_DISPLAY_SOURCE_2 = 0;}
              break;
    
              case 18: // PIN D2_3; SWITCH_CONTROL_PANEL_1; CODE ID
                   if((SR_IN_1 >> i) & 1){SWITCH_CONTROL_PANEL_1 = 1;}
                   else{SWITCH_CONTROL_PANEL_1 = 0;}
              break;
    
              case 19: // PIN D3_3; SWITCH_CONTROL_PANEL_2; CODE ID
                   if((SR_IN_1 >> i) & 1){SWITCH_CONTROL_PANEL_2 = 1;}
                   else{SWITCH_CONTROL_PANEL_2 = 0;}
              break;
              
              case 20: // PIN D4_3; SWITCH_CROSS_FEED; CODE IE
                   if((SR_IN_1 >> i) & 1){SWITCH_CROSS_FEED = 1;}
                   else{SWITCH_CROSS_FEED = 0;}
              break;
    
              case 21: // PIN D5_3; SWITCH_FUEL_PUMPS_A; CODE IF
                   if((SR_IN_1 >> i) & 1){SWITCH_FUEL_PUMPS_A = 1;}
                   else{SWITCH_FUEL_PUMPS_A = 0;}
              break;
    
              case 22: // PIN D6_3; SWITCH_FUEL_PUMPS_B; CODE IG
                   if((SR_IN_1 >> i) & 1){SWITCH_FUEL_PUMPS_B = 1;}
                   else{SWITCH_FUEL_PUMPS_B = 0;}
              break;
    
              case 23: // PIN D7_3; SWITCH_AFT_FUEL_PUMP_1; CODE IH
                   if((SR_IN_1 >> i) & 1){SWITCH_AFT_FUEL_PUMP_1 = 1;}
                   else{SWITCH_AFT_FUEL_PUMP_1 = 0;}
              break;
    
              case 24: // PIN D0_4; SWITCH_AFT_FUEL_PUMP_2; CODE II
                   if((SR_IN_1 >> i) & 1){SWITCH_AFT_FUEL_PUMP_2 = 1;}
                   else{SWITCH_AFT_FUEL_PUMP_2 = 0;}
              break;
    
              case 25: // PIN D1_4; SWITCH_FWD_FUEL_PUMP_1; CODE IJ
                   if((SR_IN_1 >> i) & 1){SWITCH_FWD_FUEL_PUMP_1 = 1;}
                   else{SWITCH_FWD_FUEL_PUMP_1 = 0;}
              break;
    
              case 26: // PIN D2_4; SWITCH_FWD_FUEL_PUMP_2; CODE IK
                   if((SR_IN_1 >> i) & 1){SWITCH_FWD_FUEL_PUMP_2 = 1;}
                   else{SWITCH_FWD_FUEL_PUMP_2 = 0;}
              break;              

              case 27: // PIN D3_4; SWITCH_RETRACTABLE_LDG_LIGHTS_L; CODE Ab
                   if((SR_IN_1 >> i) & 1){SWITCH_RETRACTABLE_LDG_LIGHTS_L = 1;}
                   else{SWITCH_RETRACTABLE_LDG_LIGHTS_L = 0;}
              break;
    
              case 29: // PIN D5_4; SWITCH_RETRACTABLE_LDG_LIGHTS_R; CODE Ac
                   if((SR_IN_1 >> i) & 1){SWITCH_RETRACTABLE_LDG_LIGHTS_R = 1;}
                   else{SWITCH_RETRACTABLE_LDG_LIGHTS_R = 0;}
              break;
    
              case 31: // PIN D7_4; SWITCH_FIXED_LDG_LIGHTS_L; CODE Ad
                   if((SR_IN_1 >> i) & 1){SWITCH_FIXED_LDG_LIGHTS_L = 1;}
                   else{SWITCH_FIXED_LDG_LIGHTS_L = 0;}
              break;
    
              case 32: // PIN D0_5; SWITCH_FIXED_LDG_LIGHTS_R; CODE Ae
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_FIXED_LDG_LIGHTS_R = 1;}
                   else{SWITCH_FIXED_LDG_LIGHTS_R = 0;}
              break;
    
              case 33: // PIN D1_5; SWITCH_RWY_LIGHT_L; CODE Af
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_RWY_LIGHT_L = 1;}
                   else{SWITCH_RWY_LIGHT_L = 0;}
              break;

              case 34: // PIN D2_5; SWITCH_RWY_LIGHT_R; CODE Ag
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_RWY_LIGHT_R = 1;}
                   else{SWITCH_RWY_LIGHT_R = 0;}
              break;

              case 35: // PIN D3_5; SWITCH_TAXI_LIGHT; CODE Ah
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_TAXI_LIGHT = 1;}
                   else{SWITCH_TAXI_LIGHT = 0;}
              break;              

              case 36: // PIN D4_5; SWITCH_APU_1; CODE Ai
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_APU_1 = 1;}
                   else{SWITCH_APU_1 = 0;}
              break;

              case 37: // PIN D5_5; SWITCH_APU_2; CODE Ai
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_APU_2 = 1;}
                   else{SWITCH_APU_2 = 0;}
              break;

              case 38: // PIN D6_5; SELECTOR_ENGINE_STATOR_L_1; CODE Aj
                   if((SR_IN_5 >> (i-32)) & 1){SELECTOR_ENGINE_STATOR_L_1 = 1;}
                   else{SELECTOR_ENGINE_STATOR_L_1 = 0;}
              break;

              case 39: // PIN D7_5; SELECTOR_ENGINE_STATOR_L_2; CODE Aj
                   if((SR_IN_5 >> (i-32)) & 1){SELECTOR_ENGINE_STATOR_L_2 = 1;}
                   else{SELECTOR_ENGINE_STATOR_L_2 = 0;}
              break;

              case 40: // PIN D0_6; SELECTOR_ENGINE_STATOR_L_3; CODE Aj
                   if((SR_IN_5 >> (i-32)) & 1){SELECTOR_ENGINE_STATOR_L_3 = 1;}
                   else{SELECTOR_ENGINE_STATOR_L_3 = 0;}
              break;

              case 41: // PIN D1_6; SELECTOR_ENGINE_STATOR_L_4; CODE Aj
                   if((SR_IN_5 >> (i-32)) & 1){SELECTOR_ENGINE_STATOR_L_4 = 1;}
                   else{SELECTOR_ENGINE_STATOR_L_4 = 0;}
              break;

              case 42: // PIN D2_6; SELECTOR_ENGINE_STATOR_R_1; CODE Ak
                   if((SR_IN_5 >> (i-32)) & 1){SELECTOR_ENGINE_STATOR_R_1 = 1;}
                   else{SELECTOR_ENGINE_STATOR_R_1 = 0;}
              break;

              case 43: // PIN D3_6; SELECTOR_ENGINE_STATOR_R_2; CODE Ak
                   if((SR_IN_5 >> (i-32)) & 1){SELECTOR_ENGINE_STATOR_R_2 = 1;}
                   else{SELECTOR_ENGINE_STATOR_R_2 = 0;}
              break;

              case 44: // PIN D4_6; SELECTOR_ENGINE_STATOR_R_3; CODE Ak
                   if((SR_IN_5 >> (i-32)) & 1){SELECTOR_ENGINE_STATOR_R_3 = 1;}
                   else{SELECTOR_ENGINE_STATOR_R_3 = 0;}
              break;

              case 45: // PIN D5_6; SELECTOR_ENGINE_STATOR_R_4; CODE Ak
                   if((SR_IN_5 >> (i-32)) & 1){SELECTOR_ENGINE_STATOR_R_4 = 1;}
                   else{SELECTOR_ENGINE_STATOR_R_4 = 0;}
              break;

              case 46: // PIN D6_6; SWITCH_IGNITION_1; CODE Al
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_IGNITION_1 = 1;}
                   else{SWITCH_IGNITION_1 = 0;}
              break;

              case 47: // PIN D7_6; SWITCH_IGNITION_2; CODE Al
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_IGNITION_2 = 1;}
                   else{SWITCH_IGNITION_2 = 0;}
              break;

              case 48: // PIN D0_7; SWITCH_LOGO_LIGHT; CODE Am
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_LOGO_LIGHT = 1;}
                   else{SWITCH_LOGO_LIGHT = 0;}
              break;

              case 49: // PIN D1_7; SWITCH_STROBE_LIGHT_1; CODE An
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_STROBE_LIGHT_1 = 1;}
                   else{SWITCH_STROBE_LIGHT_1 = 0;}
              break;

              case 50: // PIN D2_7; SWITCH_STROBE_LIGHT_2; CODE An
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_STROBE_LIGHT_2 = 1;}
                   else{SWITCH_STROBE_LIGHT_2 = 0;}
              break;

              case 51: // PIN D3_7; SWITCH_ANTI_COLLITION_LIGHT; CODE Ao
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_ANTI_COLLITION_LIGHT = 1;}
                   else{SWITCH_ANTI_COLLITION_LIGHT = 0;}
              break;

              case 52: // PIN D4_7; SWITCH_WING_LIGHT; CODE Ap
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_WING_LIGHT = 1;}
                   else{SWITCH_WING_LIGHT = 0;}
              break;

              case 53: // PIN D5_7; SWITCH_WHEEL_WELL_LIGHT; CODE Aq
                   if((SR_IN_5 >> (i-32)) & 1){SWITCH_WHEEL_WELL_LIGHT = 1;}
                   else{SWITCH_WHEEL_WELL_LIGHT = 0;}
              break;

           }
        }
        
    }//End modify_switch_values_1()


  // *MODIFY SWITCH VALUES 8 FUNCTION*

    void modify_switch_values_8(){ //Modifies the SWITCH values asociated with SR_IN_8 to SR_IN_14
       
        for(int i = 0; i < DATA_WIDTH_8; i++){
          
          switch(i){
              
              case 0: // PIN D0_8; BUTTON_MAINT; CODE IM
                   if((SR_IN_8 >> i) & 1){BUTTON_MAINT = 1;}
                   else{BUTTON_MAINT = 0;}
              break;

              case 1: // PIN D1_8; SELECTOR_DC_SOURCE_0; CODE IN
                   if((SR_IN_8 >> i) & 1){SELECTOR_DC_SOURCE_0 = 1;}
                   else{SELECTOR_DC_SOURCE_0 = 0;}
              break;

              case 2: // PIN D2_8; SELECTOR_DC_SOURCE_1; CODE IN
                   if((SR_IN_8 >> i) & 1){SELECTOR_DC_SOURCE_1 = 1;}
                   else{SELECTOR_DC_SOURCE_1 = 0;}
              break;

              case 3: // PIN D3_8; SELECTOR_DC_SOURCE_2; CODE IN
                   if((SR_IN_8 >> i) & 1){SELECTOR_DC_SOURCE_2 = 1;}
                   else{SELECTOR_DC_SOURCE_2 = 0;}
              break;

              case 4: // PIN D4_8; SELECTOR_DC_SOURCE_3; CODE IN
                   if((SR_IN_8 >> i) & 1){SELECTOR_DC_SOURCE_3 = 1;}
                   else{SELECTOR_DC_SOURCE_3 = 0;}
              break;
              
              case 5: // PIN D5_8; SELECTOR_DC_SOURCE_4; CODE IN
                   if((SR_IN_8 >> i) & 1){SELECTOR_DC_SOURCE_4 = 1;}
                   else{SELECTOR_DC_SOURCE_4 = 0;}
              break;
              
              case 6: // PIN D6_8; SELECTOR_DC_SOURCE_5; CODE IN
                   if((SR_IN_8 >> i) & 1){SELECTOR_DC_SOURCE_5 = 1;}
                   else{SELECTOR_DC_SOURCE_5 = 0;}
              break;
              
              case 7: // PIN D7_8; SELECTOR_DC_SOURCE_6; CODE IN
                   if((SR_IN_8 >> i) & 1){SELECTOR_DC_SOURCE_6 = 1;}
                   else{SELECTOR_DC_SOURCE_6 = 0;}
              break;
              
              case 8: // PIN D0_9; SELECTOR_DC_SOURCE_7; CODE IN
                   if((SR_IN_8 >> i) & 1){SELECTOR_DC_SOURCE_7 = 1;}
                   else{SELECTOR_DC_SOURCE_7 = 0;}
              break;
              
              case 9: // PIN D1_9; SELECTOR_AC_SOURCE_0; CODE IO
                   if((SR_IN_8 >> i) & 1){SELECTOR_AC_SOURCE_0 = 1;}
                   else{SELECTOR_AC_SOURCE_0 = 0;}
              break;
              
              case 10: // PIN D2_9; SELECTOR_AC_SOURCE_1; CODE IO
                   if((SR_IN_8 >> i) & 1){SELECTOR_AC_SOURCE_1 = 1;}
                   else{SELECTOR_AC_SOURCE_1 = 0;}
              break;
              
              case 11: // PIN D3_9; SELECTOR_AC_SOURCE_2; CODE IO
                   if((SR_IN_8 >> i) & 1){SELECTOR_AC_SOURCE_2 = 1;}
                   else{SELECTOR_AC_SOURCE_2 = 0;}
              break;
              
              case 12: // PIN D4_9; SELECTOR_AC_SOURCE_3; CODE IO
                   if((SR_IN_8 >> i) & 1){SELECTOR_AC_SOURCE_3 = 1;}
                   else{SELECTOR_AC_SOURCE_3 = 0;}
              break;
              
              case 13: // PIN D5_9; SELECTOR_AC_SOURCE_4; CODE IO
                   if((SR_IN_8 >> i) & 1){SELECTOR_AC_SOURCE_4 = 1;}
                   else{SELECTOR_AC_SOURCE_4 = 0;}
              break;
              
              case 14: // PIN D6_9; SELECTOR_AC_SOURCE_5; CODE IO
                   if((SR_IN_8 >> i) & 1){SELECTOR_AC_SOURCE_5 = 1;}
                   else{SELECTOR_AC_SOURCE_5 = 0;}
              break;
              
              case 15: // PIN D7_9; SELECTOR_AC_SOURCE_6; CODE IO
                   if((SR_IN_8 >> i) & 1){SELECTOR_AC_SOURCE_6 = 1;}
                   else{SELECTOR_AC_SOURCE_6 = 0;}
              break;
              
              case 16: // PIN D0_10; SWITCH_MAIN_BATTERY; CODE IP
                   if((SR_IN_8 >> i) & 1){SWITCH_MAIN_BATTERY = 1;}
                   else{SWITCH_MAIN_BATTERY = 0;}
              break;
              
              case 17: // PIN D1_10; SWITCH_CAB_UTIL; CODE IQ
                   if((SR_IN_8 >> i) & 1){SWITCH_CAB_UTIL = 1;}
                   else{SWITCH_CAB_UTIL = 0;}
              break;
              
              case 18: // PIN D2_10; SWITCH_IFE_PASS_SEAT; CODE IR
                   if((SR_IN_8 >> i) & 1){SWITCH_IFE_PASS_SEAT = 1;}
                   else{SWITCH_IFE_PASS_SEAT = 0;}
              break;
              
              case 19: // PIN D3_10; SWITCH_STANDBY_POWER_1; CODE IS
                   if((SR_IN_8 >> i) & 1){SWITCH_STANDBY_POWER_1 = 1;}
                   else{SWITCH_STANDBY_POWER_1 = 0;}
              break;
              
              case 20: // PIN D4_10; SWITCH_STANDBY_POWER_2; CODE IS
                   if((SR_IN_8 >> i) & 1){SWITCH_STANDBY_POWER_2 = 1;}
                   else{SWITCH_STANDBY_POWER_2 = 0;}
              break;
              
              case 21: // PIN D5_10; SWITCH_DRIVE_1; CODE IT
                   if((SR_IN_8 >> i) & 1){SWITCH_DRIVE_1 = 1;}
                   else{SWITCH_DRIVE_1 = 0;}
              break;
              
              case 22: // PIN D6_10; SWITCH_DRIVE_2; CODE IU
                   if((SR_IN_8 >> i) & 1){SWITCH_DRIVE_2 = 1;}
                   else{SWITCH_DRIVE_2 = 0;}
              break;
              
              case 23: // PIN D7_10; SWITCH_GROUND_POWER_ON; CODE IV
                   if((SR_IN_8 >> i) & 1){SWITCH_GROUND_POWER_ON = 1;}
                   else{SWITCH_GROUND_POWER_ON = 0;}
              break;
              
              case 24: // PIN D0_11; SWITCH_GROUND_POWER_OFF; CODE IV
                   if((SR_IN_8 >> i) & 1){SWITCH_GROUND_POWER_OFF = 1;}
                   else{SWITCH_GROUND_POWER_OFF = 0;}
              break;
              
              case 25: // PIN D1_11; SWITCH_BUS_TRANSFER; CODE IW
                   if((SR_IN_8 >> i) & 1){SWITCH_BUS_TRANSFER = 1;}
                   else{SWITCH_BUS_TRANSFER = 0;}
              break;
              
              case 26: // PIN D2_11; SWITCH_MAIN_GEN_1_ON; CODE IX
                   if((SR_IN_8 >> i) & 1){SWITCH_MAIN_GEN_1_ON = 1;}
                   else{SWITCH_MAIN_GEN_1_ON = 0;}
              break;
              
              case 27: // PIN D3_11; SWITCH_MAIN_GEN_1_OFF; CODE IX
                   if((SR_IN_8 >> i) & 1){SWITCH_MAIN_GEN_1_OFF = 1;}
                   else{SWITCH_MAIN_GEN_1_OFF = 0;}
              break;
              
              case 28: // PIN D4_11; SWITCH_MAIN_GEN_2_ON; CODE IY
                   if((SR_IN_8 >> i) & 1){SWITCH_MAIN_GEN_2_ON = 1;}
                   else{SWITCH_MAIN_GEN_2_ON = 0;}
              break;

              case 29: // PIN D5_11; SWITCH_MAIN_GEN_2_OFF; CODE IY
                   if((SR_IN_8 >> i) & 1){SWITCH_MAIN_GEN_2_OFF = 1;}
                   else{SWITCH_MAIN_GEN_2_OFF = 0;}
              break;

              case 30: // PIN D6_11; SWITCH_APU_GEN_1_ON; CODE IZ
                   if((SR_IN_8 >> i) & 1){SWITCH_APU_GEN_1_ON = 1;}
                   else{SWITCH_APU_GEN_1_ON = 0;}
              break;

              case 31: // PIN D7_11; SWITCH_APU_GEN_1_OFF; CODE IZ
                   if((SR_IN_8 >> i) & 1){SWITCH_APU_GEN_1_OFF = 1;}
                   else{SWITCH_APU_GEN_1_OFF = 0;}
              break;

              case 32: // PIN D0_12; SWITCH_APU_GEN_2_ON; CODE JA
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_APU_GEN_2_ON = 1;}
                   else{SWITCH_APU_GEN_2_ON = 0;}
              break;

              case 33: // PIN D1_12; SWITCH_APU_GEN_2_OFF; CODE JA
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_APU_GEN_2_OFF = 1;}
                   else{SWITCH_APU_GEN_2_OFF = 0;}
              break;

              case 34: // PIN D2_12; SELECTOR_WIPER_L_0; CODE JB
                   if((SR_IN_12 >> (i-32)) & 1){SELECTOR_WIPER_L_0 = 1;}
                   else{SELECTOR_WIPER_L_0 = 0;}
              break;

              case 35: // PIN D3_12; SELECTOR_WIPER_L_1; CODE JB
                   if((SR_IN_12 >> (i-32)) & 1){SELECTOR_WIPER_L_1 = 1;}
                   else{SELECTOR_WIPER_L_1 = 0;}
              break;

              case 36: // PIN D4_12; SELECTOR_WIPER_L_2; CODE JB
                   if((SR_IN_12 >> (i-32)) & 1){SELECTOR_WIPER_L_2 = 1;}
                   else{SELECTOR_WIPER_L_2 = 0;}
              break;

              case 37: // PIN D5_12; SELECTOR_WIPER_L_3; CODE JB
                   if((SR_IN_12 >> (i-32)) & 1){SELECTOR_WIPER_L_3 = 1;}
                   else{SELECTOR_WIPER_L_3 = 0;}
              break;

              case 38: // PIN D6_12; SWITCH_EQUIP_SUPPLY; CODE JD
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_EQUIP_SUPPLY = 1;}
                   else{SWITCH_EQUIP_SUPPLY = 0;}
              break;

              case 39: // PIN D7_12; SWITCH_EQUIP_EXHAUST; CODE JE
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_EQUIP_EXHAUST = 1;}
                   else{SWITCH_EQUIP_EXHAUST = 0;}
              break;

              case 40: // PIN D0_13; SWITCH_EMER_EXIT_LIGHT_1; CODE JF
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_EMER_EXIT_LIGHT_1 = 1;}
                   else{SWITCH_EMER_EXIT_LIGHT_1 = 0;}
              break;

              case 41: // PIN D1_13; SWITCH_EMER_EXIT_LIGHT_2; CODE JF
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_EMER_EXIT_LIGHT_2 = 1;}
                   else{SWITCH_EMER_EXIT_LIGHT_2 = 0;}
              break;

              case 42: // PIN D2_13; SWITCH_CHIME; CODE JG
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_CHIME = 1;}
                   else{SWITCH_CHIME = 0;}
              break;

              case 43: // PIN D3_13; SWITCH_FASTEN_BELTS_1; CODE JH
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_FASTEN_BELTS_1 = 1;}
                   else{SWITCH_FASTEN_BELTS_1 = 0;}
              break;

              case 44: // PIN D4_13; SWITCH_FASTEN_BELTS_2; CODE JH
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_FASTEN_BELTS_2 = 1;}
                   else{SWITCH_FASTEN_BELTS_2 = 0;}
              break;

              case 45: // PIN D5_13; BUTTON_ATTEND; CODE JI
                   if((SR_IN_12 >> (i-32)) & 1){BUTTON_ATTEND = 1;}
                   else{BUTTON_ATTEND = 0;}
              break;

              case 46: // PIN D6_13; BUTTON_GRD_CALL; CODE JJ
                   if((SR_IN_12 >> (i-32)) & 1){BUTTON_GRD_CALL = 1;}
                   else{BUTTON_GRD_CALL = 0;}
              break;

              case 47: // PIN D7_13; SELECTOR_WIPER_R_0; CODE JC
                   if((SR_IN_12 >> (i-32)) & 1){SELECTOR_WIPER_R_0 = 1;}
                   else{SELECTOR_WIPER_R_0 = 0;}
              break;

              case 48: // PIN D0_14; SELECTOR_WIPER_R_1; CODE JC
                   if((SR_IN_12 >> (i-32)) & 1){SELECTOR_WIPER_R_1 = 1;}
                   else{SELECTOR_WIPER_R_1 = 0;}
              break;

              case 49: // PIN D1_14; SELECTOR_WIPER_R_2; CODE JC
                   if((SR_IN_12 >> (i-32)) & 1){SELECTOR_WIPER_R_2 = 1;}
                   else{SELECTOR_WIPER_R_2 = 0;}
              break;

              case 50: // PIN D2_14; SELECTOR_WIPER_R_3; CODE JC
                   if((SR_IN_12 >> (i-32)) & 1){SELECTOR_WIPER_R_3 = 1;}
                   else{SELECTOR_WIPER_R_3 = 0;}
              break;

              case 51: // PIN D3_14; SWITCH_WH_SIDE_1; CODE JK
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_WH_SIDE_1 = 1;}
                   else{SWITCH_WH_SIDE_1 = 0;}
              break;

              case 52: // PIN D4_14; SWITCH_WH_SIDE_2; CODE JL
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_WH_SIDE_2 = 1;}
                   else{SWITCH_WH_SIDE_2 = 0;}
              break;

              case 53: // PIN D5_14; SWITCH_WH_FWD_1; CODE JM
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_WH_FWD_1 = 1;}
                   else{SWITCH_WH_FWD_1 = 0;}
              break;

              case 54: // PIN D6_14; SWITCH_WH_FWD_2; CODE JN
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_WH_FWD_2 = 1;}
                   else{SWITCH_WH_FWD_2 = 0;}
              break;

              case 55: // PIN D7_14; SWITCH_PROBE_HEAT_A; CODE JO
                   if((SR_IN_12 >> (i-32)) & 1){SWITCH_PROBE_HEAT_A = 1;}
                   else{SWITCH_PROBE_HEAT_A = 0;}
              break;
            
          }

        }
        
    }//End modify_switch_values_8()


  // *MODIFY SWITCH VALUES 15 FUNCTION*

    void modify_switch_values_15(){ //Modifies the SWITCH values asociated with SR_IN_15 to SR_IN_19
       
        for(int i = 0; i < DATA_WIDTH_15; i++){
          
          switch(i){

              case 0: // PIN D0_15; SWITCH_PROBE_HEAT_B; CODE JP
                   if((SR_IN_15 >> i) & 1){SWITCH_PROBE_HEAT_B = 1;}
                   else{SWITCH_PROBE_HEAT_B = 0;}
              break;

              case 1: // PIN D1_15; SWITCH_OVERHEAT_1; CODE JQ
                   if((SR_IN_15 >> i) & 1){SWITCH_OVERHEAT_1 = 1;}
                   else{SWITCH_OVERHEAT_1 = 0;}
              break;

              case 2: // PIN D2_15; SWITCH_OVERHEAT_2; CODE JQ
                   if((SR_IN_15 >> i) & 1){SWITCH_OVERHEAT_2 = 1;}
                   else{SWITCH_OVERHEAT_2 = 0;}
              break;

              case 3: // PIN D3_15; BUTTON_TAT_TEST; NO CODE
                   if((SR_IN_15 >> i) & 1){BUTTON_TAT_TEST = 1;}
                   else{BUTTON_TAT_TEST = 0;}
              break;

              case 4: // PIN D4_15; SWITCH_WING_ANTI_ICE; CODE JR
                   if((SR_IN_15 >> i) & 1){SWITCH_WING_ANTI_ICE = 1;}
                   else{SWITCH_WING_ANTI_ICE = 0;}
              break;

              case 5: // PIN D5_15; SWITCH_ENGINE_ANTI_ICE_1; CODE JS
                   if((SR_IN_15 >> i) & 1){SWITCH_ENGINE_ANTI_ICE_1 = 1;}
                   else{SWITCH_ENGINE_ANTI_ICE_1 = 0;}
              break;

              case 6: // PIN D6_15; SWITCH_ENGINE_ANTI_ICE_2; CODE JT
                   if((SR_IN_15 >> i) & 1){SWITCH_ENGINE_ANTI_ICE_2 = 1;}
                   else{SWITCH_ENGINE_ANTI_ICE_2 = 0;}
              break;

              case 7: // PIN D7_15; SWITCH_ENGINE_HYD_1; CODE JU
                   if((SR_IN_15 >> i) & 1){SWITCH_ENGINE_HYD_1 = 1;}
                   else{SWITCH_ENGINE_HYD_1 = 0;}
              break;

              case 8: // PIN D0_16; SWITCH_ENGINE_HYD_2; CODE JV
                   if((SR_IN_15 >> i) & 1){SWITCH_ENGINE_HYD_2 = 1;}
                   else{SWITCH_ENGINE_HYD_2 = 0;}
              break;

              case 9: // PIN D1_16; SWITCH_ELECTRIC_HYD_1; CODE JW
                   if((SR_IN_15 >> i) & 1){SWITCH_ELECTRIC_HYD_1 = 1;}
                   else{SWITCH_ELECTRIC_HYD_1 = 0;}
              break;

              case 10: // PIN D2_16; SWITCH_ELECTRIC_HYD_2; CODE JX
                   if((SR_IN_15 >> i) & 1){SWITCH_ELECTRIC_HYD_2 = 1;}
                   else{SWITCH_ELECTRIC_HYD_2 = 0;}
              break;
              
              case 11: // PIN D3_16; BUTTON_COCKPIT_VOICE_TEST; CODE JY
                   if((SR_IN_15 >> i) & 1){BUTTON_COCKPIT_VOICE_TEST = 1;}
                   else{BUTTON_COCKPIT_VOICE_TEST = 0;}
              break;
              
              case 12: // PIN D4_16; BUTTON_COCKPIT_VOICE_ERASE; CODE JZ
                   if((SR_IN_15 >> i) & 1){BUTTON_COCKPIT_VOICE_ERASE = 1; LED_TEST = 1;}
                   else{BUTTON_COCKPIT_VOICE_ERASE = 0; LED_TEST = 0;}
              break;

              case 13: // PIN D5_16; BUTTON_ALT_HORN_CUTOUT; CODE ??
                   if((SR_IN_15 >> i) & 1){BUTTON_ALT_HORN_CUTOUT = 1;}
                   else{BUTTON_ALT_HORN_CUTOUT = 0;}
              break;

              case 14: // PIN D6_16; SWITCH_VOICE_RECORDER; NO CODE
                   if((SR_IN_15 >> i) & 1){SWITCH_VOICE_RECORDER = 1;}
                   else{SWITCH_VOICE_RECORDER = 0;}
              break;

              case 15: // PIN D7_16; SELECTOR_AIR_TEMP_0; CODE KA
                   if((SR_IN_15 >> i) & 1){SELECTOR_AIR_TEMP_0 = 1;}
                   else{SELECTOR_AIR_TEMP_0 = 0;}
              break;

              case 16: // PIN D0_17; SELECTOR_AIR_TEMP_1; CODE KA
                   if((SR_IN_15 >> i) & 1){SELECTOR_AIR_TEMP_1 = 1;}
                   else{SELECTOR_AIR_TEMP_1 = 0;}
              break;

              case 17: // PIN D1_17; SELECTOR_AIR_TEMP_2; CODE KA
                   if((SR_IN_15 >> i) & 1){SELECTOR_AIR_TEMP_2 = 1;}
                   else{SELECTOR_AIR_TEMP_2 = 0;}
              break;

              case 18: // PIN D2_17; SELECTOR_AIR_TEMP_3; CODE KA
                   if((SR_IN_15 >> i) & 1){SELECTOR_AIR_TEMP_3 = 1;}
                   else{SELECTOR_AIR_TEMP_3 = 0;}
              break;

              case 19: // PIN D3_17; SELECTOR_AIR_TEMP_4; CODE KA
                   if((SR_IN_15 >> i) & 1){SELECTOR_AIR_TEMP_4 = 1;}
                   else{SELECTOR_AIR_TEMP_4 = 0;}
              break;

              case 20: // PIN D4_17; SELECTOR_AIR_TEMP_5; CODE KA
                   if((SR_IN_15 >> i) & 1){SELECTOR_AIR_TEMP_5 = 1;}
                   else{SELECTOR_AIR_TEMP_5 = 0;}
              break;

              case 21: // PIN D5_17; SELECTOR_AIR_TEMP_6; CODE KA
                   if((SR_IN_15 >> i) & 1){SELECTOR_AIR_TEMP_6 = 1;}
                   else{SELECTOR_AIR_TEMP_6 = 0;}
              break;

              case 22: // PIN D6_17; SWITCH_TRIM_AIR; CODE ??
                   if((SR_IN_15 >> i) & 1){SWITCH_TRIM_AIR = 1;}
                   else{SWITCH_TRIM_AIR = 0;}
              break;

              case 23: // PIN D7_17; SWITCH_RECIRC_FAN_L; CODE KE
                   if((SR_IN_15 >> i) & 1){SWITCH_RECIRC_FAN_L = 1;}
                   else{SWITCH_RECIRC_FAN_L = 0;}
              break;

              case 24: // PIN D0_18; SWITCH_RECIRC_FAN_R; CODE KG
                   if((SR_IN_15 >> i) & 1){SWITCH_RECIRC_FAN_R = 1;}
                   else{SWITCH_RECIRC_FAN_R = 0;}
              break;

              case 25: // PIN D1_18; BUTTON_OVHT_TEST; CODE ??
                   if((SR_IN_15 >> i) & 1){BUTTON_OVHT_TEST = 1;}
                   else{BUTTON_OVHT_TEST = 0;}
              break;

              case 26: // PIN D2_18; SWITCH_ISOLATION_VALVE_1; CODE KG
                   if((SR_IN_15 >> i) & 1){SWITCH_ISOLATION_VALVE_1 = 1;}
                   else{SWITCH_ISOLATION_VALVE_1 = 0;}
              break;

              case 27: // PIN D3_18; SWITCH_ISOLATION_VALVE_2; CODE KG
                   if((SR_IN_15 >> i) & 1){SWITCH_ISOLATION_VALVE_2 = 1;}
                   else{SWITCH_ISOLATION_VALVE_2 = 0;}
              break;

              case 28: // PIN D4_18; BUTTON_TRIP_RESET; CODE KH
                   if((SR_IN_15 >> i) & 1){BUTTON_TRIP_RESET = 1;}
                   else{BUTTON_TRIP_RESET = 0;}
              break;

              case 29: // PIN D5_18; SWITCH_PACK_L_1; CODE KI
                   if((SR_IN_15 >> i) & 1){SWITCH_PACK_L_1 = 1;}
                   else{SWITCH_PACK_L_1 = 0;}
              break;

              case 30: // PIN D6_18; SWITCH_PACK_L_2; CODE KI
                   if((SR_IN_15 >> i) & 1){SWITCH_PACK_L_2 = 1;}
                   else{SWITCH_PACK_L_2 = 0;}
              break;

              case 31: // PIN D7_18; SWITCH_PACK_R_1; CODE KJ
                   if((SR_IN_15 >> i) & 1){SWITCH_PACK_R_1 = 1;}
                   else{SWITCH_PACK_R_1 = 0;}
              break;

              case 32: // PIN D0_19; SWITCH_PACK_R_2; CODE KJ
                   if((SR_IN_19 >> (i-32)) & 1){SWITCH_PACK_R_2 = 1;}
                   else{SWITCH_PACK_R_2 = 0;}
              break;

              case 33: // PIN D1_19; SWITCH_BLEED_AIR_1; CODE KK
                   if((SR_IN_19 >> (i-32)) & 1){SWITCH_BLEED_AIR_1 = 1;}
                   else{SWITCH_BLEED_AIR_1 = 0;}
              break;

              case 34: // PIN D2_19; SWITCH_BLEED_AIR_2; CODE KL
                   if((SR_IN_19 >> (i-32)) & 1){SWITCH_BLEED_AIR_2 = 1;}
                   else{SWITCH_BLEED_AIR_2 = 0;}
              break;

              case 35: // PIN D3_19; SWITCH_APU_BLEED_AIR; CODE KM
                   if((SR_IN_19 >> (i-32)) & 1){SWITCH_APU_BLEED_AIR = 1;}
                   else{SWITCH_APU_BLEED_AIR = 0;}
              break;

              case 36: // PIN D4_19; SELECTOR_PRESSURIZATION_1; CODE KP
                   if((SR_IN_19 >> (i-32)) & 1){SELECTOR_PRESSURIZATION_1 = 1;}
                   else{SELECTOR_PRESSURIZATION_1 = 0;}
              break;

              case 37: // PIN D5_19; SELECTOR_PRESSURIZATION_2; CODE KP
                   if((SR_IN_19 >> (i-32)) & 1){SELECTOR_PRESSURIZATION_2 = 1;}
                   else{SELECTOR_PRESSURIZATION_2 = 0;}
              break;

              case 38: // PIN D6_19; SWITCH_VALVE_1; CODE KQ
                   if((SR_IN_19 >> (i-32)) & 1){SWITCH_VALVE_1 = 1;}
                   else{SWITCH_VALVE_1 = 0;}
              break;

              case 39: // PIN D7_19; SWITCH_VALVE_2; CODE KQ
                   if((SR_IN_19 >> (i-32)) & 1){SWITCH_VALVE_2 = 1;}
                   else{SWITCH_VALVE_2 = 0;}
              break;
            
          }

        }
        
    }//End modify_switch_values_15()



  // *UPDATE DISPLAY 1 FUNCTION*

    void updateDisplay_1(){
      display_num_1 = valueCSi;
      if(display_num_1 < 0){
        display_num_1 = abs(display_num_1);
        neg_num_1 = 1;
      }
      else{
        neg_num_1 = 0;
      }          
      for (display_pos=0; display_pos<3; display_pos++){
        shift_number_1[2-display_pos]= display_num_1%10;     
        display_num_1 = display_num_1/10;
      }
      last_empty_digit_1 = 0;
      if (shift_number_1[0] == 0 || shift_number_1[0] == 10){ //Eliminate 0 at the left
        shift_number_1[0]=10;
        last_empty_digit_1 = 1;
        if(shift_number_1[1] == 0 || shift_number_1[1] == 10){
          shift_number_1[1]=10;
          last_empty_digit_1 = 2;
        }
      }      
    }//End updateDisplay_1()



  // *UPDATE DISPLAY 2 FUNCTION*

    void updateDisplay_2(){
      display_num_2 = valueCUi;
      for (display_pos=0; display_pos<3; display_pos++){
        shift_number_2[2-display_pos]= display_num_2%10;
        display_num_2 = display_num_2/10;
      }
      if (shift_number_2[0] == 0 || shift_number_2[0] == 10){ //Eliminate 0 at the left
       shift_number_2[0]=10;
        if(shift_number_2[1] == 0 || shift_number_2[1] == 10){
          shift_number_2[1]=10;
        }
      }      
    }//End updateDisplay_2()



  // *UPDATE DISPLAY 3 FUNCTION*

    void updateDisplay_3(){
      display_num_3 = valueCVi;
      for (display_pos=0; display_pos<2; display_pos++){
        shift_number_3[1-display_pos]= display_num_3%10;
        display_num_3 = display_num_3/10;
      }
      if (shift_number_3[0] == 0 || shift_number_3[0] == 10){ //Eliminate 0 at the left
        shift_number_3[0]=10;
      }      
    }//End updateDisplay_3()



  // *UPDATE DISPLAY 4 FUNCTION*

    void updateDisplay_4(){
      display_num_4 = valueCWi;
      if(display_num_4 < 0){
        display_num_4 = abs(display_num_4);
        neg_num_4 = 1;
      }
      else{
        neg_num_4 = 0;
      }
      for (display_pos=0; display_pos<3; display_pos++){
        shift_number_4[2-display_pos]= display_num_4%10;
        display_num_4 = display_num_4/10; 
      }
      last_empty_digit_4 = 0;
      if (shift_number_4[0] == 0 || shift_number_4[0] == 10){ //Eliminate 0 at the left
        shift_number_4[0]=10;
        last_empty_digit_4 = 1;
        if(shift_number_4[1] == 0 || shift_number_4[1] == 10){
          shift_number_4[1]=10;
          last_empty_digit_4 = 2;
        }
      }      
    }//End updateDisplay_4()



  // *UPDATE DISPLAY 5 FUNCTION*

    void updateDisplay_5(){
      display_num_5 = valueCXi;
      for (display_pos=0; display_pos<3; display_pos++){
        shift_number_5[2-display_pos]= display_num_5%10;
        display_num_5 = display_num_5/10;
      }
      if (shift_number_5[0] == 0 || shift_number_5[0] == 10){ //Eliminate 0 at the left
        shift_number_5[0]=10;
        if(shift_number_5[1] == 0 || shift_number_5[1] == 10){
          shift_number_5[1]=10;
        }
      }      
    }//End updateDisplay_5()



  // *UPDATE DISPLAY 6 FUNCTION*

    void updateDisplay_6(){
      display_num_6 = valueGGi;
      if(display_num_6 < 0){
        display_num_6 = abs(display_num_6);
        neg_num_6 = 1;
      }
      else{
        neg_num_6 = 0;
      }               
      for (display_pos=0; display_pos<5; display_pos++){
        shift_number_6[4-display_pos]= display_num_6%10;     
        display_num_6 = display_num_6/10;
      }
      last_empty_digit_6 = 0;      
      if (shift_number_6[0] == 0 || shift_number_6[0] == 10){ //Eliminate 0 at the left
        shift_number_6[0]=10;
        last_empty_digit_6 = 1;
        if(shift_number_6[1] == 0 || shift_number_6[1] == 10){
          shift_number_6[1]=10;
          last_empty_digit_6 = 2;
          if(shift_number_6[2] == 0 || shift_number_6[2] == 10){
            shift_number_6[2]=10;
            last_empty_digit_6 = 3;
            if(shift_number_6[3] == 0 || shift_number_6[3] == 10){
              shift_number_6[3]=10;
              last_empty_digit_6 = 4;
            }
          }
        }
      }      
    }//End updateDisplay_6()



  // *UPDATE DISPLAY 7 FUNCTION*

    void updateDisplay_7(){
      display_num_7 = valueGHi;
      if(display_num_7 < 0){
        display_num_7 = abs(display_num_7);
        neg_num_7 = 1;
      }
      else{
        neg_num_7 = 0;
      }               
      for (display_pos=0; display_pos<5; display_pos++){
        shift_number_7[4-display_pos]= display_num_7%10;     
        display_num_7 = display_num_7/10;
      }
      last_empty_digit_7 = 0;      
      if (shift_number_7[0] == 0 || shift_number_7[0] == 10){ //Eliminate 0 at the left
        shift_number_7[0]=10;
        last_empty_digit_7 = 1;
        if(shift_number_7[1] == 0 || shift_number_7[1] == 10){
          shift_number_7[1]=10;
          last_empty_digit_7 = 2;
          if(shift_number_7[2] == 0 || shift_number_7[2] == 10){
            shift_number_7[2]=10;
            last_empty_digit_7 = 3;
            if(shift_number_7[3] == 0 || shift_number_7[3] == 10){
              shift_number_7[3]=10;
              last_empty_digit_7 = 4;
            }
          }
        }
      }     
    }//End updateDisplay_7()  


    
  // *REFRESH DISPLAY 1 FUNCTION*

    void refreshDisplay_1(){

      for (display_pos=0; display_pos<4; display_pos++){

        if (display_pos == 0){bitClear(SR_OUT_4,7), bitSet(SR_OUT_5,0), bitSet(SR_OUT_5,1);
                              bitClear(SR_OUT_6,1), bitSet(SR_OUT_6,2), bitSet(SR_OUT_6,3);
                              bitSet(SR_OUT_7,3), bitSet(SR_OUT_7,4);
                              bitClear(SR_OUT_8,4), bitSet(SR_OUT_8,5), bitSet(SR_OUT_8,6);
                              bitClear(SR_OUT_9,6), bitSet(SR_OUT_9,7), bitSet(SR_OUT_10,0);}
        if (display_pos == 1){bitSet(SR_OUT_4,7), bitClear(SR_OUT_5,0), bitSet(SR_OUT_5,1);
                              bitSet(SR_OUT_6,1), bitClear(SR_OUT_6,2), bitSet(SR_OUT_6,3);
                              bitClear(SR_OUT_7,3), bitSet(SR_OUT_7,4);
                              bitSet(SR_OUT_8,4), bitClear(SR_OUT_8,5), bitSet(SR_OUT_8,6);
                              bitSet(SR_OUT_9,6), bitClear(SR_OUT_9,7), bitSet(SR_OUT_10,0);}
        if (display_pos == 2){bitSet(SR_OUT_4,7), bitSet(SR_OUT_5,0), bitClear(SR_OUT_5,1);
                              bitSet(SR_OUT_6,1), bitSet(SR_OUT_6,2), bitClear(SR_OUT_6,3);
                              bitSet(SR_OUT_7,3), bitClear(SR_OUT_7,4);
                              bitSet(SR_OUT_8,4), bitSet(SR_OUT_8,5), bitClear(SR_OUT_8,6);
                              bitSet(SR_OUT_9,6), bitSet(SR_OUT_9,7), bitClear(SR_OUT_10,0);}
        if (display_pos == 3){bitSet(SR_OUT_4,7), bitSet(SR_OUT_5,0), bitSet(SR_OUT_5,1);
                              bitSet(SR_OUT_6,1), bitSet(SR_OUT_6,2), bitSet(SR_OUT_6,3);
                              bitSet(SR_OUT_7,3), bitSet(SR_OUT_7,4);
                              bitSet(SR_OUT_8,4), bitSet(SR_OUT_8,5), bitSet(SR_OUT_8,6);
                              bitSet(SR_OUT_9,6), bitSet(SR_OUT_9,7), bitSet(SR_OUT_10,0);}
        
        switch( shift_number_1[display_pos] ){ //DC AMPS DISPLAY

          case 0:
            bitSet(SR_OUT_4,0); // A segment
            bitSet(SR_OUT_4,1); // B segment
            bitSet(SR_OUT_4,2); // C segment
            bitSet(SR_OUT_4,3); // D segment
            bitSet(SR_OUT_4,4); // E segment
            bitSet(SR_OUT_4,5); // F segment
            bitClear(SR_OUT_4,6); // G segment
          break;

          case 1:
            bitClear(SR_OUT_4,0); // A segment
            bitSet(SR_OUT_4,1); // B segment
            bitSet(SR_OUT_4,2); // C segment
            bitClear(SR_OUT_4,3); // D segment
            bitClear(SR_OUT_4,4); // E segment
            bitClear(SR_OUT_4,5); // F segment
            bitClear(SR_OUT_4,6); // G segment
          break;                

          case 2:
            bitSet(SR_OUT_4,0); // A segment
            bitSet(SR_OUT_4,1); // B segment
            bitClear(SR_OUT_4,2); // C segment
            bitSet(SR_OUT_4,3); // D segment
            bitSet(SR_OUT_4,4); // E segment
            bitClear(SR_OUT_4,5); // F segment
            bitSet(SR_OUT_4,6); // G segment
          break; 

          case 3:
            bitSet(SR_OUT_4,0); // A segment
            bitSet(SR_OUT_4,1); // B segment
            bitSet(SR_OUT_4,2); // C segment
            bitSet(SR_OUT_4,3); // D segment
            bitClear(SR_OUT_4,4); // E segment
            bitClear(SR_OUT_4,5); // F segment
            bitSet(SR_OUT_4,6); // G segment
          break; 

          case 4:
            bitClear(SR_OUT_4,0); // A segment
            bitSet(SR_OUT_4,1); // B segment
            bitSet(SR_OUT_4,2); // C segment
            bitClear(SR_OUT_4,3); // D segment
            bitClear(SR_OUT_4,4); // E segment
            bitSet(SR_OUT_4,5); // F segment
            bitSet(SR_OUT_4,6); // G segment
          break; 

          case 5:
            bitSet(SR_OUT_4,0); // A segment
            bitClear(SR_OUT_4,1); // B segment
            bitSet(SR_OUT_4,2); // C segment
            bitSet(SR_OUT_4,3); // D segment
            bitClear(SR_OUT_4,4); // E segment
            bitSet(SR_OUT_4,5); // F segment
            bitSet(SR_OUT_4,6); // G segment
          break; 

          case 6:
            bitSet(SR_OUT_4,0); // A segment
            bitClear(SR_OUT_4,1); // B segment
            bitSet(SR_OUT_4,2); // C segment
            bitSet(SR_OUT_4,3); // D segment
            bitSet(SR_OUT_4,4); // E segment
            bitSet(SR_OUT_4,5); // F segment
            bitSet(SR_OUT_4,6); // G segment
          break;

          case 7:
            bitSet(SR_OUT_4,0); // A segment
            bitSet(SR_OUT_4,1); // B segment
            bitSet(SR_OUT_4,2); // C segment
            bitClear(SR_OUT_4,3); // D segment
            bitClear(SR_OUT_4,4); // E segment
            bitClear(SR_OUT_4,5); // F segment
            bitClear(SR_OUT_4,6); // G segment
          break; 

          case 8:
            bitSet(SR_OUT_4,0); // A segment
            bitSet(SR_OUT_4,1); // B segment
            bitSet(SR_OUT_4,2); // C segment
            bitSet(SR_OUT_4,3); // D segment
            bitSet(SR_OUT_4,4); // E segment
            bitSet(SR_OUT_4,5); // F segment
            bitSet(SR_OUT_4,6); // G segment
          break;

          case 9:
            bitSet(SR_OUT_4,0); // A segment
            bitSet(SR_OUT_4,1); // B segment
            bitSet(SR_OUT_4,2); // C segment
            bitSet(SR_OUT_4,3); // D segment
            bitClear(SR_OUT_4,4); // E segment
            bitSet(SR_OUT_4,5); // F segment
            bitSet(SR_OUT_4,6); // G segment
          break;

          case 10: //empty digit
            bitClear(SR_OUT_4,0); // A segment
            bitClear(SR_OUT_4,1); // B segment
            bitClear(SR_OUT_4,2); // C segment
            bitClear(SR_OUT_4,3); // D segment
            bitClear(SR_OUT_4,4); // E segment
            bitClear(SR_OUT_4,5); // F segment
            bitClear(SR_OUT_4,6); // G segment
          break;
          
        }

        switch( shift_number_2[display_pos] ){ //CPS FREQ DISPLAY

          case 0:
            bitSet(SR_OUT_5,2); // A segment
            bitSet(SR_OUT_5,3); // B segment
            bitSet(SR_OUT_5,4); // C segment
            bitSet(SR_OUT_5,5); // D segment
            bitSet(SR_OUT_5,6); // E segment
            bitSet(SR_OUT_5,7); // F segment
            bitClear(SR_OUT_6,0); // G segment
          break;

          case 1:
            bitClear(SR_OUT_5,2); // A segment
            bitSet(SR_OUT_5,3); // B segment
            bitSet(SR_OUT_5,4); // C segment
            bitClear(SR_OUT_5,5); // D segment
            bitClear(SR_OUT_5,6); // E segment
            bitClear(SR_OUT_5,7); // F segment
            bitClear(SR_OUT_6,0); // G segment
          break;                

          case 2:
            bitSet(SR_OUT_5,2); // A segment
            bitSet(SR_OUT_5,3); // B segment
            bitClear(SR_OUT_5,4); // C segment
            bitSet(SR_OUT_5,5); // D segment
            bitSet(SR_OUT_5,6); // E segment
            bitClear(SR_OUT_5,7); // F segment
            bitSet(SR_OUT_6,0); // G segment
          break; 

          case 3:
            bitSet(SR_OUT_5,2); // A segment
            bitSet(SR_OUT_5,3); // B segment
            bitSet(SR_OUT_5,4); // C segment
            bitSet(SR_OUT_5,5); // D segment
            bitClear(SR_OUT_5,6); // E segment
            bitClear(SR_OUT_5,7); // F segment
            bitSet(SR_OUT_6,0); // G segment
          break; 

          case 4:
            bitClear(SR_OUT_5,2); // A segment
            bitSet(SR_OUT_5,3); // B segment
            bitSet(SR_OUT_5,4); // C segment
            bitClear(SR_OUT_5,5); // D segment
            bitClear(SR_OUT_5,6); // E segment
            bitSet(SR_OUT_5,7); // F segment
            bitSet(SR_OUT_6,0); // G segment
          break; 

          case 5:
            bitSet(SR_OUT_5,2); // A segment
            bitClear(SR_OUT_5,3); // B segment
            bitSet(SR_OUT_5,4); // C segment
            bitSet(SR_OUT_5,5); // D segment
            bitClear(SR_OUT_5,6); // E segment
            bitSet(SR_OUT_5,7); // F segment
            bitSet(SR_OUT_6,0); // G segment
          break; 

          case 6:
            bitSet(SR_OUT_5,2); // A segment
            bitClear(SR_OUT_5,3); // B segment
            bitSet(SR_OUT_5,4); // C segment
            bitSet(SR_OUT_5,5); // D segment
            bitSet(SR_OUT_5,6); // E segment
            bitSet(SR_OUT_5,7); // F segment
            bitSet(SR_OUT_6,0); // G segment
          break;

          case 7:
            bitSet(SR_OUT_5,2); // A segment
            bitSet(SR_OUT_5,3); // B segment
            bitSet(SR_OUT_5,4); // C segment
            bitClear(SR_OUT_5,5); // D segment
            bitClear(SR_OUT_5,6); // E segment
            bitClear(SR_OUT_5,7); // F segment
            bitClear(SR_OUT_6,0); // G segment
          break; 

          case 8:
            bitSet(SR_OUT_5,2); // A segment
            bitSet(SR_OUT_5,3); // B segment
            bitSet(SR_OUT_5,4); // C segment
            bitSet(SR_OUT_5,5); // D segment
            bitSet(SR_OUT_5,6); // E segment
            bitSet(SR_OUT_5,7); // F segment
            bitSet(SR_OUT_6,0); // G segment
          break;

          case 9:
            bitSet(SR_OUT_5,2); // A segment
            bitSet(SR_OUT_5,3); // B segment
            bitSet(SR_OUT_5,4); // C segment
            bitSet(SR_OUT_5,5); // D segment
            bitClear(SR_OUT_5,6); // E segment
            bitSet(SR_OUT_5,7); // F segment
            bitSet(SR_OUT_6,0); // G segment
          break;

          case 10:
            bitClear(SR_OUT_5,2); // A segment
            bitClear(SR_OUT_5,3); // B segment
            bitClear(SR_OUT_5,4); // C segment
            bitClear(SR_OUT_5,5); // D segment
            bitClear(SR_OUT_5,6); // E segment
            bitClear(SR_OUT_5,7); // F segment
            bitClear(SR_OUT_6,0); // G segment
          break;                                                                                                                     
        }            

        switch( shift_number_3[display_pos-1] ){ //DC VOLTS DISPLAY

          case 0:
            bitSet(SR_OUT_6,4); // A segment
            bitSet(SR_OUT_6,5); // B segment
            bitSet(SR_OUT_6,6); // C segment
            bitSet(SR_OUT_6,7); // D segment
            bitSet(SR_OUT_7,0); // E segment
            bitSet(SR_OUT_7,1); // F segment
            bitClear(SR_OUT_7,2); // G segment
          break;

          case 1:
            bitClear(SR_OUT_6,4); // A segment
            bitSet(SR_OUT_6,5); // B segment
            bitSet(SR_OUT_6,6); // C segment
            bitClear(SR_OUT_6,7); // D segment
            bitClear(SR_OUT_7,0); // E segment
            bitClear(SR_OUT_7,1); // F segment
            bitClear(SR_OUT_7,2); // G segment
          break;                

          case 2:
            bitSet(SR_OUT_6,4); // A segment
            bitSet(SR_OUT_6,5); // B segment
            bitClear(SR_OUT_6,6); // C segment
            bitSet(SR_OUT_6,7); // D segment
            bitSet(SR_OUT_7,0); // E segment
            bitClear(SR_OUT_7,1); // F segment
            bitSet(SR_OUT_7,2); // G segment
          break; 

          case 3:
            bitSet(SR_OUT_6,4); // A segment
            bitSet(SR_OUT_6,5); // B segment
            bitSet(SR_OUT_6,6); // C segment
            bitSet(SR_OUT_6,7); // D segment
            bitClear(SR_OUT_7,0); // E segment
            bitClear(SR_OUT_7,1); // F segment
            bitSet(SR_OUT_7,2); // G segment
          break; 

          case 4:
            bitClear(SR_OUT_6,4); // A segment
            bitSet(SR_OUT_6,5); // B segment
            bitSet(SR_OUT_6,6); // C segment
            bitClear(SR_OUT_6,7); // D segment
            bitClear(SR_OUT_7,0); // E segment
            bitSet(SR_OUT_7,1); // F segment
            bitSet(SR_OUT_7,2); // G segment
          break; 

          case 5:
            bitSet(SR_OUT_6,4); // A segment
            bitClear(SR_OUT_6,5); // B segment
            bitSet(SR_OUT_6,6); // C segment
            bitSet(SR_OUT_6,7); // D segment
            bitClear(SR_OUT_7,0); // E segment
            bitSet(SR_OUT_7,1); // F segment
            bitSet(SR_OUT_7,2); // G segment
          break; 

          case 6:
            bitSet(SR_OUT_6,4); // A segment
            bitClear(SR_OUT_6,5); // B segment
            bitSet(SR_OUT_6,6); // C segment
            bitSet(SR_OUT_6,7); // D segment
            bitSet(SR_OUT_7,0); // E segment
            bitSet(SR_OUT_7,1); // F segment
            bitSet(SR_OUT_7,2); // G segment
          break;

          case 7:
            bitSet(SR_OUT_6,4); // A segment
            bitSet(SR_OUT_6,5); // B segment
            bitSet(SR_OUT_6,6); // C segment
            bitClear(SR_OUT_6,7); // D segment
            bitClear(SR_OUT_7,0); // E segment
            bitClear(SR_OUT_7,1); // F segment
            bitClear(SR_OUT_7,2); // G segment
          break; 

          case 8:
            bitSet(SR_OUT_6,4); // A segment
            bitSet(SR_OUT_6,5); // B segment
            bitSet(SR_OUT_6,6); // C segment
            bitSet(SR_OUT_6,7); // D segment
            bitSet(SR_OUT_7,0); // E segment
            bitSet(SR_OUT_7,1); // F segment
            bitSet(SR_OUT_7,2); // G segment
          break;

          case 9:
            bitSet(SR_OUT_6,4); // A segment
            bitSet(SR_OUT_6,5); // B segment
            bitSet(SR_OUT_6,6); // C segment
            bitSet(SR_OUT_6,7); // D segment
            bitClear(SR_OUT_7,0); // E segment
            bitSet(SR_OUT_7,1); // F segment
            bitSet(SR_OUT_7,2); // G segment
          break;
          
          case 10:
            bitClear(SR_OUT_6,4); // A segment
            bitClear(SR_OUT_6,5); // B segment
            bitClear(SR_OUT_6,6); // C segment
            bitClear(SR_OUT_6,7); // D segment
            bitClear(SR_OUT_7,0); // E segment
            bitClear(SR_OUT_7,1); // F segment
            bitClear(SR_OUT_7,2); // G segment
          break;                                                                                                                     
        }

        switch( shift_number_4[display_pos] ){ //AC AMPS DISPLAY

          case 0:
            bitSet(SR_OUT_7,5); // A segment
            bitSet(SR_OUT_7,6); // B segment
            bitSet(SR_OUT_7,7); // C segment
            bitSet(SR_OUT_8,0); // D segment
            bitSet(SR_OUT_8,1); // E segment
            bitSet(SR_OUT_8,2); // F segment
            bitClear(SR_OUT_8,3); // G segment
          break;

          case 1:
            bitClear(SR_OUT_7,5); // A segment
            bitSet(SR_OUT_7,6); // B segment
            bitSet(SR_OUT_7,7); // C segment
            bitClear(SR_OUT_8,0); // D segment
            bitClear(SR_OUT_8,1); // E segment
            bitClear(SR_OUT_8,2); // F segment
            bitClear(SR_OUT_8,3); // G segment
          break;                

          case 2:
            bitSet(SR_OUT_7,5); // A segment
            bitSet(SR_OUT_7,6); // B segment
            bitClear(SR_OUT_7,7); // C segment
            bitSet(SR_OUT_8,0); // D segment
            bitSet(SR_OUT_8,1); // E segment
            bitClear(SR_OUT_8,2); // F segment
            bitSet(SR_OUT_8,3); // G segment
          break; 

          case 3:
            bitSet(SR_OUT_7,5); // A segment
            bitSet(SR_OUT_7,6); // B segment
            bitSet(SR_OUT_7,7); // C segment
            bitSet(SR_OUT_8,0); // D segment
            bitClear(SR_OUT_8,1); // E segment
            bitClear(SR_OUT_8,2); // F segment
            bitSet(SR_OUT_8,3); // G segment
          break; 

          case 4:
            bitClear(SR_OUT_7,5); // A segment
            bitSet(SR_OUT_7,6); // B segment
            bitSet(SR_OUT_7,7); // C segment
            bitClear(SR_OUT_8,0); // D segment
            bitClear(SR_OUT_8,1); // E segment
            bitSet(SR_OUT_8,2); // F segment
            bitSet(SR_OUT_8,3); // G segment
          break; 

          case 5:
            bitSet(SR_OUT_7,5); // A segment
            bitClear(SR_OUT_7,6); // B segment
            bitSet(SR_OUT_7,7); // C segment
            bitSet(SR_OUT_8,0); // D segment
            bitClear(SR_OUT_8,1); // E segment
            bitSet(SR_OUT_8,2); // F segment
            bitSet(SR_OUT_8,3); // G segment
          break; 

          case 6:
            bitSet(SR_OUT_7,5); // A segment
            bitClear(SR_OUT_7,6); // B segment
            bitSet(SR_OUT_7,7); // C segment
            bitSet(SR_OUT_8,0); // D segment
            bitSet(SR_OUT_8,1); // E segment
            bitSet(SR_OUT_8,2); // F segment
            bitSet(SR_OUT_8,3); // G segment
          break;

          case 7:
            bitSet(SR_OUT_7,5); // A segment
            bitSet(SR_OUT_7,6); // B segment
            bitSet(SR_OUT_7,7); // C segment
            bitClear(SR_OUT_8,0); // D segment
            bitClear(SR_OUT_8,1); // E segment
            bitClear(SR_OUT_8,2); // F segment
            bitClear(SR_OUT_8,3); // G segment
          break; 

          case 8:
            bitSet(SR_OUT_7,5); // A segment
            bitSet(SR_OUT_7,6); // B segment
            bitSet(SR_OUT_7,7); // C segment
            bitSet(SR_OUT_8,0); // D segment
            bitSet(SR_OUT_8,1); // E segment
            bitSet(SR_OUT_8,2); // F segment
            bitSet(SR_OUT_8,3); // G segment
          break;

          case 9:
            bitSet(SR_OUT_7,5); // A segment
            bitSet(SR_OUT_7,6); // B segment
            bitSet(SR_OUT_7,7); // C segment
            bitSet(SR_OUT_8,0); // D segment
            bitClear(SR_OUT_8,1); // E segment
            bitSet(SR_OUT_8,2); // F segment
            bitSet(SR_OUT_8,3); // G segment
          break;
          
          case 10:
            bitClear(SR_OUT_7,5); // A segment
            bitClear(SR_OUT_7,6); // B segment
            bitClear(SR_OUT_7,7); // C segment
            bitClear(SR_OUT_8,0); // D segment
            bitClear(SR_OUT_8,1); // E segment
            bitClear(SR_OUT_8,2); // F segment
            bitClear(SR_OUT_8,3); // G segment
          break;                                                                                                                     
        }

        switch( shift_number_5[display_pos] ){ //AC VOLTS DISPLAY

          case 0:
            bitSet(SR_OUT_8,7); // A segment
            bitSet(SR_OUT_9,0); // B segment
            bitSet(SR_OUT_9,1); // C segment
            bitSet(SR_OUT_9,2); // D segment
            bitSet(SR_OUT_9,3); // E segment
            bitSet(SR_OUT_9,4); // F segment
            bitClear(SR_OUT_9,5); // G segment
          break;

          case 1:
            bitClear(SR_OUT_8,7); // A segment
            bitSet(SR_OUT_9,0); // B segment
            bitSet(SR_OUT_9,1); // C segment
            bitClear(SR_OUT_9,2); // D segment
            bitClear(SR_OUT_9,3); // E segment
            bitClear(SR_OUT_9,4); // F segment
            bitClear(SR_OUT_9,5); // G segment
          break;                

          case 2:
            bitSet(SR_OUT_8,7); // A segment
            bitSet(SR_OUT_9,0); // B segment
            bitClear(SR_OUT_9,1); // C segment
            bitSet(SR_OUT_9,2); // D segment
            bitSet(SR_OUT_9,3); // E segment
            bitClear(SR_OUT_9,4); // F segment
            bitSet(SR_OUT_9,5); // G segment
          break; 

          case 3:
            bitSet(SR_OUT_8,7); // A segment
            bitSet(SR_OUT_9,0); // B segment
            bitSet(SR_OUT_9,1); // C segment
            bitSet(SR_OUT_9,2); // D segment
            bitClear(SR_OUT_9,3); // E segment
            bitClear(SR_OUT_9,4); // F segment
            bitSet(SR_OUT_9,5); // G segment
          break; 

          case 4:
            bitClear(SR_OUT_8,7); // A segment
            bitSet(SR_OUT_9,0); // B segment
            bitSet(SR_OUT_9,1); // C segment
            bitClear(SR_OUT_9,2); // D segment
            bitClear(SR_OUT_9,3); // E segment
            bitSet(SR_OUT_9,4); // F segment
            bitSet(SR_OUT_9,5); // G segment
          break; 

          case 5:
            bitSet(SR_OUT_8,7); // A segment
            bitClear(SR_OUT_9,0); // B segment
            bitSet(SR_OUT_9,1); // C segment
            bitSet(SR_OUT_9,2); // D segment
            bitClear(SR_OUT_9,3); // E segment
            bitSet(SR_OUT_9,4); // F segment
            bitSet(SR_OUT_9,5); // G segment
          break; 

          case 6:
            bitSet(SR_OUT_8,7); // A segment
            bitClear(SR_OUT_9,0); // B segment
            bitSet(SR_OUT_9,1); // C segment
            bitSet(SR_OUT_9,2); // D segment
            bitSet(SR_OUT_9,3); // E segment
            bitSet(SR_OUT_9,4); // F segment
            bitSet(SR_OUT_9,5); // G segment
          break;

          case 7:
            bitSet(SR_OUT_8,7); // A segment
            bitSet(SR_OUT_9,0); // B segment
            bitSet(SR_OUT_9,1); // C segment
            bitClear(SR_OUT_9,2); // D segment
            bitClear(SR_OUT_9,3); // E segment
            bitClear(SR_OUT_9,4); // F segment
            bitClear(SR_OUT_9,5); // G segment
          break; 

          case 8:
            bitSet(SR_OUT_8,7); // A segment
            bitSet(SR_OUT_9,0); // B segment
            bitSet(SR_OUT_9,1); // C segment
            bitSet(SR_OUT_9,2); // D segment
            bitSet(SR_OUT_9,3); // E segment
            bitSet(SR_OUT_9,4); // F segment
            bitSet(SR_OUT_9,5); // G segment
          break;

          case 9:
            bitSet(SR_OUT_8,7); // A segment
            bitSet(SR_OUT_9,0); // B segment
            bitSet(SR_OUT_9,1); // C segment
            bitSet(SR_OUT_9,2); // D segment
            bitClear(SR_OUT_9,3); // E segment
            bitSet(SR_OUT_9,4); // F segment
            bitSet(SR_OUT_9,5); // G segment
          break;

          case 10:
            bitClear(SR_OUT_8,7); // A segment
            bitClear(SR_OUT_9,0); // B segment
            bitClear(SR_OUT_9,1); // C segment
            bitClear(SR_OUT_9,2); // D segment
            bitClear(SR_OUT_9,3); // E segment
            bitClear(SR_OUT_9,4); // F segment
            bitClear(SR_OUT_9,5); // G segment
          break;                                                                                                                     
        }

        if ( (neg_num_1 == 1) && (display_pos == (last_empty_digit_1 - 1)) ){ //print a dash (-) on the first digit
          
          bitClear(SR_OUT_4,0); // A segment
          bitClear(SR_OUT_4,1); // B segment
          bitClear(SR_OUT_4,2); // C segment
          bitClear(SR_OUT_4,3); // D segment
          bitClear(SR_OUT_4,4); // E segment
          bitClear(SR_OUT_4,5); // F segment
          bitSet(SR_OUT_4,6); // G segment
           
        }

        if ( (neg_num_4 == 1) && (display_pos == (last_empty_digit_4 - 1)) ){ //print a dash (-) on the first digit
          
          bitClear(SR_OUT_7,5); // A segment
          bitClear(SR_OUT_7,6); // B segment
          bitClear(SR_OUT_7,7); // C segment
          bitClear(SR_OUT_8,0); // D segment
          bitClear(SR_OUT_8,1); // E segment
          bitClear(SR_OUT_8,2); // F segment
          bitSet(SR_OUT_8,3); // G segment
           
        }

        if (PRE_SELECTOR_DC_SOURCE ==0){bitSet(SR_OUT_4,7); bitSet(SR_OUT_5,0); bitSet(SR_OUT_5,1); bitSet(SR_OUT_7,3); bitSet(SR_OUT_7,4);}
        if (PRE_SELECTOR_DC_SOURCE ==1){bitSet(SR_OUT_4,7); bitSet(SR_OUT_5,0); bitSet(SR_OUT_5,1);}
        if (PRE_SELECTOR_DC_SOURCE ==2){bitSet(SR_OUT_4,7); bitSet(SR_OUT_5,0); bitSet(SR_OUT_5,1);}

        if (PRE_SELECTOR_AC_SOURCE ==0){bitSet(SR_OUT_8,4); bitSet(SR_OUT_8,5); bitSet(SR_OUT_8,6);}          
        if (PRE_SELECTOR_AC_SOURCE ==1 && valueDE == '0'){bitSet(SR_OUT_6,1); bitSet(SR_OUT_6,2); bitSet(SR_OUT_6,3); bitSet(SR_OUT_8,4); bitSet(SR_OUT_8,5); bitSet(SR_OUT_8,6); bitSet(SR_OUT_9,6); bitSet(SR_OUT_9,7); bitSet(SR_OUT_10,0);}
        if (PRE_SELECTOR_AC_SOURCE ==2 && valueDC == '1'){bitSet(SR_OUT_6,1); bitSet(SR_OUT_6,2); bitSet(SR_OUT_6,3);}          
        if (PRE_SELECTOR_AC_SOURCE ==3 && apu_power == 0){bitSet(SR_OUT_6,1); bitSet(SR_OUT_6,2); bitSet(SR_OUT_6,3);}          
        if (PRE_SELECTOR_AC_SOURCE ==4 && valueDD == '1'){bitSet(SR_OUT_6,1); bitSet(SR_OUT_6,2); bitSet(SR_OUT_6,3);}          
        if (PRE_SELECTOR_AC_SOURCE ==5){bitSet(SR_OUT_8,4); bitSet(SR_OUT_8,5); bitSet(SR_OUT_8,6);}          
        if (PRE_SELECTOR_AC_SOURCE ==6){bitSet(SR_OUT_6,1); bitSet(SR_OUT_6,2); bitSet(SR_OUT_6,3); bitSet(SR_OUT_8,4); bitSet(SR_OUT_8,5); bitSet(SR_OUT_8,6); bitSet(SR_OUT_9,6); bitSet(SR_OUT_9,7); bitSet(SR_OUT_10,0);}          


        delay(1); //delay as long as necessary to get time to watch on display

        update_SR_OUT_4();
          
      }
              
    }//End refreshDisplay_1()



  // *REFRESH DISPLAY 2 FUNCTION*

    void refreshDisplay_2(){

      for (display_pos=0; display_pos<6; display_pos++){

        if (display_pos == 0){bitClear(SR_OUT_20,7), bitSet(SR_OUT_21,0), bitSet(SR_OUT_21,1), bitSet(SR_OUT_21,2), bitSet(SR_OUT_21,3);
                              bitClear(SR_OUT_22,3), bitSet(SR_OUT_22,4), bitSet(SR_OUT_22,5), bitSet(SR_OUT_22,6), bitSet(SR_OUT_22,7);}
        if (display_pos == 1){bitSet(SR_OUT_20,7), bitClear(SR_OUT_21,0), bitSet(SR_OUT_21,1), bitSet(SR_OUT_21,2), bitSet(SR_OUT_21,3);
                              bitSet(SR_OUT_22,3), bitClear(SR_OUT_22,4), bitSet(SR_OUT_22,5), bitSet(SR_OUT_22,6), bitSet(SR_OUT_22,7);}
        if (display_pos == 2){bitSet(SR_OUT_20,7), bitSet(SR_OUT_21,0), bitClear(SR_OUT_21,1), bitSet(SR_OUT_21,2), bitSet(SR_OUT_21,3);
                              bitSet(SR_OUT_22,3), bitSet(SR_OUT_22,4), bitClear(SR_OUT_22,5), bitSet(SR_OUT_22,6), bitSet(SR_OUT_22,7);}
        if (display_pos == 3){bitSet(SR_OUT_20,7), bitSet(SR_OUT_21,0), bitSet(SR_OUT_21,1), bitClear(SR_OUT_21,2), bitSet(SR_OUT_21,3);
                              bitSet(SR_OUT_22,3), bitSet(SR_OUT_22,4), bitSet(SR_OUT_22,5), bitClear(SR_OUT_22,6), bitSet(SR_OUT_22,7);}
        if (display_pos == 4){bitSet(SR_OUT_20,7), bitSet(SR_OUT_21,0), bitSet(SR_OUT_21,1), bitSet(SR_OUT_21,2), bitClear(SR_OUT_21,3);
                              bitSet(SR_OUT_22,3), bitSet(SR_OUT_22,4), bitSet(SR_OUT_22,5), bitSet(SR_OUT_22,6), bitClear(SR_OUT_22,7);}                                                                                          
        if (display_pos == 5){bitSet(SR_OUT_20,7), bitSet(SR_OUT_21,0), bitSet(SR_OUT_21,1), bitSet(SR_OUT_21,2), bitSet(SR_OUT_21,3);
                              bitSet(SR_OUT_22,3), bitSet(SR_OUT_22,4), bitSet(SR_OUT_22,5), bitSet(SR_OUT_22,6), bitSet(SR_OUT_22,7);}
        
        switch( shift_number_6[display_pos] ){ //FLT ALT DISPLAY

          case 0:
            bitSet(SR_OUT_20,0); // A segment
            bitSet(SR_OUT_20,1); // B segment
            bitSet(SR_OUT_20,2); // C segment
            bitSet(SR_OUT_20,3); // D segment
            bitSet(SR_OUT_20,4); // E segment
            bitSet(SR_OUT_20,5); // F segment
            bitClear(SR_OUT_20,6); // G segment
          break;

          case 1:
            bitClear(SR_OUT_20,0); // A segment
            bitSet(SR_OUT_20,1); // B segment
            bitSet(SR_OUT_20,2); // C segment
            bitClear(SR_OUT_20,3); // D segment
            bitClear(SR_OUT_20,4); // E segment
            bitClear(SR_OUT_20,5); // F segment
            bitClear(SR_OUT_20,6); // G segment
          break;                

          case 2:
            bitSet(SR_OUT_20,0); // A segment
            bitSet(SR_OUT_20,1); // B segment
            bitClear(SR_OUT_20,2); // C segment
            bitSet(SR_OUT_20,3); // D segment
            bitSet(SR_OUT_20,4); // E segment
            bitClear(SR_OUT_20,5); // F segment
            bitSet(SR_OUT_20,6); // G segment
          break; 

          case 3:
            bitSet(SR_OUT_20,0); // A segment
            bitSet(SR_OUT_20,1); // B segment
            bitSet(SR_OUT_20,2); // C segment
            bitSet(SR_OUT_20,3); // D segment
            bitClear(SR_OUT_20,4); // E segment
            bitClear(SR_OUT_20,5); // F segment
            bitSet(SR_OUT_20,6); // G segment
          break; 

          case 4:
            bitClear(SR_OUT_20,0); // A segment
            bitSet(SR_OUT_20,1); // B segment
            bitSet(SR_OUT_20,2); // C segment
            bitClear(SR_OUT_20,3); // D segment
            bitClear(SR_OUT_20,4); // E segment
            bitSet(SR_OUT_20,5); // F segment
            bitSet(SR_OUT_20,6); // G segment
          break; 

          case 5:
            bitSet(SR_OUT_20,0); // A segment
            bitClear(SR_OUT_20,1); // B segment
            bitSet(SR_OUT_20,2); // C segment
            bitSet(SR_OUT_20,3); // D segment
            bitClear(SR_OUT_20,4); // E segment
            bitSet(SR_OUT_20,5); // F segment
            bitSet(SR_OUT_20,6); // G segment
          break; 

          case 6:
            bitSet(SR_OUT_20,0); // A segment
            bitClear(SR_OUT_20,1); // B segment
            bitSet(SR_OUT_20,2); // C segment
            bitSet(SR_OUT_20,3); // D segment
            bitSet(SR_OUT_20,4); // E segment
            bitSet(SR_OUT_20,5); // F segment
            bitSet(SR_OUT_20,6); // G segment
          break;

          case 7:
            bitSet(SR_OUT_20,0); // A segment
            bitSet(SR_OUT_20,1); // B segment
            bitSet(SR_OUT_20,2); // C segment
            bitClear(SR_OUT_20,3); // D segment
            bitClear(SR_OUT_20,4); // E segment
            bitClear(SR_OUT_20,5); // F segment
            bitClear(SR_OUT_20,6); // G segment
          break; 

          case 8:
            bitSet(SR_OUT_20,0); // A segment
            bitSet(SR_OUT_20,1); // B segment
            bitSet(SR_OUT_20,2); // C segment
            bitSet(SR_OUT_20,3); // D segment
            bitSet(SR_OUT_20,4); // E segment
            bitSet(SR_OUT_20,5); // F segment
            bitSet(SR_OUT_20,6); // G segment
          break;

          case 9:
            bitSet(SR_OUT_20,0); // A segment
            bitSet(SR_OUT_20,1); // B segment
            bitSet(SR_OUT_20,2); // C segment
            bitSet(SR_OUT_20,3); // D segment
            bitClear(SR_OUT_20,4); // E segment
            bitSet(SR_OUT_20,5); // F segment
            bitSet(SR_OUT_20,6); // G segment
          break;

          case 10: //empty digit
            bitClear(SR_OUT_20,0); // A segment
            bitClear(SR_OUT_20,1); // B segment
            bitClear(SR_OUT_20,2); // C segment
            bitClear(SR_OUT_20,3); // D segment
            bitClear(SR_OUT_20,4); // E segment
            bitClear(SR_OUT_20,5); // F segment
            bitClear(SR_OUT_20,6); // G segment
          break;
          
        }

        switch( shift_number_7[display_pos] ){ //LAND ALT DISPLAY

          case 0:
            bitSet(SR_OUT_21,4); // A segment
            bitSet(SR_OUT_21,5); // B segment
            bitSet(SR_OUT_21,6); // C segment
            bitSet(SR_OUT_21,7); // D segment
            bitSet(SR_OUT_22,0); // E segment
            bitSet(SR_OUT_22,1); // F segment
            bitClear(SR_OUT_22,2); // G segment
          break;

          case 1:
            bitClear(SR_OUT_21,4); // A segment
            bitSet(SR_OUT_21,5); // B segment
            bitSet(SR_OUT_21,6); // C segment
            bitClear(SR_OUT_21,7); // D segment
            bitClear(SR_OUT_22,0); // E segment
            bitClear(SR_OUT_22,1); // F segment
            bitClear(SR_OUT_22,2); // G segment
          break;                

          case 2:
            bitSet(SR_OUT_21,4); // A segment
            bitSet(SR_OUT_21,5); // B segment
            bitClear(SR_OUT_21,6); // C segment
            bitSet(SR_OUT_21,7); // D segment
            bitSet(SR_OUT_22,0); // E segment
            bitClear(SR_OUT_22,1); // F segment
            bitSet(SR_OUT_22,2); // G segment
          break; 

          case 3:
            bitSet(SR_OUT_21,4); // A segment
            bitSet(SR_OUT_21,5); // B segment
            bitSet(SR_OUT_21,6); // C segment
            bitSet(SR_OUT_21,7); // D segment
            bitClear(SR_OUT_22,0); // E segment
            bitClear(SR_OUT_22,1); // F segment
            bitSet(SR_OUT_22,2); // G segment
          break; 

          case 4:
            bitClear(SR_OUT_21,4); // A segment
            bitSet(SR_OUT_21,5); // B segment
            bitSet(SR_OUT_21,6); // C segment
            bitClear(SR_OUT_21,7); // D segment
            bitClear(SR_OUT_22,0); // E segment
            bitSet(SR_OUT_22,1); // F segment
            bitSet(SR_OUT_22,2); // G segment
          break; 

          case 5:
            bitSet(SR_OUT_21,4); // A segment
            bitClear(SR_OUT_21,5); // B segment
            bitSet(SR_OUT_21,6); // C segment
            bitSet(SR_OUT_21,7); // D segment
            bitClear(SR_OUT_22,0); // E segment
            bitSet(SR_OUT_22,1); // F segment
            bitSet(SR_OUT_22,2); // G segment
          break; 

          case 6:
            bitSet(SR_OUT_21,4); // A segment
            bitClear(SR_OUT_21,5); // B segment
            bitSet(SR_OUT_21,6); // C segment
            bitSet(SR_OUT_21,7); // D segment
            bitSet(SR_OUT_22,0); // E segment
            bitSet(SR_OUT_22,1); // F segment
            bitSet(SR_OUT_22,2); // G segment
          break;

          case 7:
            bitSet(SR_OUT_21,4); // A segment
            bitSet(SR_OUT_21,5); // B segment
            bitSet(SR_OUT_21,6); // C segment
            bitClear(SR_OUT_21,7); // D segment
            bitClear(SR_OUT_22,0); // E segment
            bitClear(SR_OUT_22,1); // F segment
            bitClear(SR_OUT_22,2); // G segment
          break; 

          case 8:
            bitSet(SR_OUT_21,4); // A segment
            bitSet(SR_OUT_21,5); // B segment
            bitSet(SR_OUT_21,6); // C segment
            bitSet(SR_OUT_21,7); // D segment
            bitSet(SR_OUT_22,0); // E segment
            bitSet(SR_OUT_22,1); // F segment
            bitSet(SR_OUT_22,2); // G segment
          break;

          case 9:
            bitSet(SR_OUT_21,4); // A segment
            bitSet(SR_OUT_21,5); // B segment
            bitSet(SR_OUT_21,6); // C segment
            bitSet(SR_OUT_21,7); // D segment
            bitClear(SR_OUT_22,0); // E segment
            bitSet(SR_OUT_22,1); // F segment
            bitSet(SR_OUT_22,2); // G segment
          break;

          case 10:
            bitClear(SR_OUT_21,4); // A segment
            bitClear(SR_OUT_21,5); // B segment
            bitClear(SR_OUT_21,6); // C segment
            bitClear(SR_OUT_21,7); // D segment
            bitClear(SR_OUT_22,0); // E segment
            bitClear(SR_OUT_22,1); // F segment
            bitClear(SR_OUT_22,2); // G segment
          break;                                                                                                                     
        }            

        if ( (neg_num_6 == 1) && (display_pos == (last_empty_digit_6 - 1)) ){ //print a dash (-) on the first digit
          
          bitClear(SR_OUT_20,0); // A segment
          bitClear(SR_OUT_20,1); // B segment
          bitClear(SR_OUT_20,2); // C segment
          bitClear(SR_OUT_20,3); // D segment
          bitClear(SR_OUT_20,4); // E segment
          bitClear(SR_OUT_20,5); // F segment
          bitSet(SR_OUT_20,6); // G segment
           
        }

        if ( (neg_num_7 == 1) && (display_pos == (last_empty_digit_7 - 1)) ){ //print a dash (-) on the first digit
          
          bitClear(SR_OUT_21,4); // A segment
          bitClear(SR_OUT_21,5); // B segment
          bitClear(SR_OUT_21,6); // C segment
          bitClear(SR_OUT_21,7); // D segment
          bitClear(SR_OUT_22,0); // E segment
          bitClear(SR_OUT_22,1); // F segment
          bitSet(SR_OUT_22,2); // G segment
           
        }

        delay(1); //delay as long as necessary to get time to watch on display
       
        update_SR_OUT_19();
          
      }
              
    }//End refreshDisplay_2()

        
// END FUNCTION SECTION        
