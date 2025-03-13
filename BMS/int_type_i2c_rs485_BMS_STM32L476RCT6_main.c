//Preamble?
//uint8_t, uint16_t, uint32_t or chars can be used to replace the int types- but int is universal and type size is not an issue
//rs4852 data when A and !A
//i2c data when clock high
//Dude, be cautious with your variables - public or global... _I are functions that read from input pins, _EN are raw integers(commands targeting output pins)
//Whoa! the EPS microntroller is actually  sampling the inputs in every while loop instance, so we have to check for changes in input states to determine if we have a 1 or a 0 

int main(){//main
	
//############ DECLARATIONS ###########
struct channel_input  {int input1 ;int input2 ;};
struct channel_output {int output1;int output2;};
//Boolean
int HIGH   = 1  ;  int TRUE = HIGH; int ONE  = HIGH;
int LOW    = 0  ;  int FALSE= LOW ; int ZERO = LOW ;
int PAUSE  = 2  ;
int END    = 3  ;
//Commands
int PING           = 34 ;
int SWITCH_ON      = 223;
int HEATER1        = 235;
int HEATER2        = 218;
int SWITCH_OFF     = 147;
int HEATER1        = 194;
int HEATER2        = 103;
int GET            = 178;
int RESET          = 255;
int CELL_VOLTAGE1  = 131;
int CELL_VOLTAGE2  = 132;
int CELL_VOLTAGE3  = 133;
int CELL_VOLTAGE4  = 134;
int CELL_VOLTAGE5  = 135;
int CELL_VOLTAGE6  = 136;
int CELL_VOLTAGE7  = 137;
int CELL_VOLTAGE8  = 138;
int CELL_VOLTAGE9  = 139;
int CELL_VOLTAGE10 = 140;
int TEMPERATURE_BALANCING1 = 161;
int TEMPERATURE_BALANCING2 = 162;
//Responses
int ACKNOWLEDGE        = 47;//response
int NOT_ACKNOWLEDGE    = 52;//response
//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET)
//HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )
int write_HEATER1   (int x) {return 0;}//op
int write_HEATER2   (int x) {return 0;}//op
int read_ALERT2     (     ) {return 0;}//ip
int write_BOOT      (int x) {return 0;}//op
int write_BOOT2     (int x) {return 0;}//op
int write_I2C1_SCL  (int x) {return 0;} //out to balancing1
int read_I2C1_SDA   (     ) {return 0;} //in from balancing1 (IS THIS I2C REALLY HALF DUPLEX????!!!!)
int write_I2C2_SCL  (int x) {return 0;} //out to balancing2
int read_I2C2_SDA   (     ) {return 0;} //in from balancing2
int write_I2C3_SCL  (int x) {return 0;} //clock in from EPS/MCU
int read_I2C3_SDA   (     ) {return 0;} //out to EPS/MCU
int read_RS4852_RX  (     ) {return 0;}//in from MCU/EPS
int write_RS4852_DE (     ) {return 0;} //out to EPS/MCU since rs485 needs a pair to transmit
int write_RS4852_TX (int x) {return 0;}//out to EPS/MCU ............?????????????????!!!!!!!
// other variables
int RESPONSE_WAIT = 10000;//response_wait()
struct channel_output RESPONSE_RS485;
	
//###################################

int get_balancing1_telemetry_leftShift_insertEnd_i2c1(){
    return 0;
}//balancing1_telemetry_leftShift_insertEnd_i2c1

//####################################
	
int get_balancing2_telemetry_leftShift_insertEnd_i2c2(){
    return 0;
}//balancing2_telemetry_leftShift_insertEnd_i2c2

//###################################

int get_temperature_sensor_leftShift_insertEnd_i2c3(){//Temp cct
    //get the temperature from specific sensor
    return 0;
}//temperature_sensor_leftShift_insertEnd_i2c3
	
//###################################
	
//read_input
int read_binary_input_rs4852(){//from EPS main controller (MCU)
    //TRUTH TABLE RS4852
    //PC10 PA15 Y(TX) ...................CAUTION
    //0    0    3(end)
    //0    1    2(pause)
    //1    0    0
    //1    1    1
    int result=0;
     /*framework customizable
	   //rs4852 in......input binary value is when  two lines are exctly opposite/complementing each other...you just have to agree which set represents the ONE and which set represents the ZERO
	   if( (!HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )) & (!HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )) ){result=3;}//end00
	   if( (!HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )) &   HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )  ){result=1;}//one01
	   if(   HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )  & (!HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )) ){result=0;}//zero10
	   if(   HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )  &   HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )  ){result=2;}//pause11
	   //rs4852 in
    framework customizable */
return result;
}//read_input
	
//####################################  

//response_wait
int response_wait(){
    for( int count=0;  count<=RESPONSE_WAIT ;count++ ){ }//do nothing
    //HAL delay could work too
return 0;
}//response_wait

//####################################

//shift all to left, insert new bit at end
//command_leftShift_insertEnd_rs4852
int get_command_and_parameter_after_leftShift_insertEnd_rs4852(int insertionbit){
    COMMAND_PARAM_RS4852 = COMMAND_PARAM_RS4852 << 1;
    COMMAND_PARAM_RS4852 = COMMAND_PARAM_RS4852 & ( 65534 | insertionbit );
return COMMAND_PARAM_RS4852;  
}//command_leftShift_insertEnd_rs4852

//###################################

//write_response_rs4852
int write_response_rs4852( int firstbyte, int secondbyte){
    int RESPONSEARRAY_RS4852[16];
    int transmit_bit_response_rs4852(int X){
        //HOW TO SEND RS4852 BIT
        return 0;
    }//transmit_bit_response_rs4852
    //
    for( int index=0;  index<=7 ;index++ ){
        RESPONSEARRAY_RS4852[index] = (int) ( ( (int) ( firstbyte >>(7 -index) ) ) & 1 ); // & 1 eliminates all preceding bits  
    }//for
    //
    for( int index=8;  index<=15;index++ ){
        RESPONSEARRAY_RS4852[index] = (int) ( ( (int) ( secondbyte>>(15-index) ) ) & 1 ); // & 1 eliminates all preceding bits 
    }//for
    //
    for( int index=0;  index<=15; index++ ){  
	transmit_bit_response_rs4852(  RESPONSEARRAY_RS4852[index]  );  
    }//for
//return to IDLE HAL blaah blaah blaah
return 0;
}//write_response_rs4852

//#################################

//execute
int execute_rs4852( int command_parameter){
    int command  = ((int)(  command_parameter>>8       ));
    int parameter= ((int)(  command_parameter&255      ));
    if ( command==PING       ) {                              write_response_rs4852(ACKNOWLEDGE,0);     }//ACK...........Fault reporting mechanisms?
    if ( command==SWITCH_ON  ) {
                         int else_check=1;
                         if(parameter==HEATER1 ){else_check=0;write_response_rs4852(ACKNOWLEDGE,0);     }//ACK.... do action
                         if(parameter==HEATER2 ){else_check=0;write_response_rs4852(ACKNOWLEDGE,0);     }//ACK.... do action
                         if(else_check==1      ){             write_response_rs4852(NOT_ACKNOWLEDGE,0); }//NACK
    }//
    if ( command==SWITCH_OFF )  {
                         int else_check=1;
                         if(parameter==HEATER1 ){else_check=0;write_response_rs4852(ACKNOWLEDGE,0    );   }//ACK.... do action
                         if(parameter==HEATER2 ){else_check=0;write_response_rs4852(ACKNOWLEDGE,0    );   }//ACK.... do action
                         if(else_check==1      ){             write_response_rs4852(NOT_ACKNOWLEDGE,0);   }//NACK
    if ( command==GET    )  {
                         int else_check=1;
                         if(parameter==CELL_VOLTAGE1 ){else_check=0;write_response_rs4852(ACKNOWLEDGE,0    );   }//ACK.... do action
                         if(parameter==CELL_VOLTAGE2 ){else_check=0;write_response_rs4852(ACKNOWLEDGE,0    );   }//ACK.... do action
	                 if(parameter==CELL_VOLTAGE3 ){else_check=0;write_response_rs4852(ACKNOWLEDGE,0    );   }//ACK.... do action
	                 if(parameter==CELL_VOLTAGE4 ){else_check=0;write_response_rs4852(ACKNOWLEDGE,0    );   }//ACK.... do action
	                 if(parameter==CELL_VOLTAGE5 ){else_check=0;write_response_rs4852(ACKNOWLEDGE,0    );   }//ACK.... do action
	                 if(parameter==CELL_VOLTAGE6 ){else_check=0;write_response_rs4852(ACKNOWLEDGE,0    );   }//ACK.... do action
	                 if(parameter==CELL_VOLTAGE7 ){else_check=0;write_response_rs4852(ACKNOWLEDGE,0    );   }//ACK.... do action
	                 if(parameter==CELL_VOLTAGE8 ){else_check=0;write_response_rs4852(ACKNOWLEDGE,0    );   }//ACK.... do action
	                 if(parameter==CELL_VOLTAGE9 ){else_check=0;write_response_rs4852(ACKNOWLEDGE,0    );   }//ACK.... do action
	                 if(parameter==CELL_VOLTAGE10){else_check=0;write_response_rs4852(ACKNOWLEDGE,0    );   }//ACK.... do action
                         if(else_check==1      ){                   write_response_rs4852(NOT_ACKNOWLEDGE,0);   }//NACK
    }//
return 0;
}//execute

//################################################################## END OF DECLARATIONS ###############################################

//########################   MAIN EVENT  ###########################################
int raw_input_rs4852;
int previous_rs4852;
int flip_21_detected_rs4852=0;//change from 2(PAUSE) to 1(HIGH)
int flip_12_detected_rs4852=0;//change from 1(HIGH) to 2(PAUSE)
int flip_20_detected_rs4852=0;//change from 2(PAUSE) to 1(HIGH)
int flip_02_detected_rs4852=0;//change from 0(LOW) to 2(PAUSE)
//##
//MAIN LOOP
while(1){//while
	//######## RS4852 ############
	raw_input_rs4852 = read_binary_input_rs4852();
	if ( (previous_rs4852==2) & (raw_input_rs4852==1) ){  flip_21_detected_rs4852=1;  }
        if ( (previous_rs4852==1) & (raw_input_rs4852==2) ){  flip_12_detected_rs4852=1;  }
        if ( (previous_rs4852==2) & (raw_input_rs4852==0) ){  flip_20_detected_rs4852=1;  }
        if ( (previous_rs4852==0) & (raw_input_rs4852==2) ){  flip_02_detected_rs4852=1;  }
        if ( flip_21_detected_rs4852 & flip_12_detected_rs4852 ){ 
	   flip_21_detected_rs4852=0; flip_12_detected_rs4852=0;flip_20_detected_rs4852=0;flip_02_detected_rs4852=0;
	   execute_rs4852( get_command_and_parameter_after_leftShift_insertEnd_rs4852(1) );
	}//if
        if ( flip_20_detected_rs4852 & flip_02_detected_rs4852 ){
           flip_21_detected_rs4852=0;flip_12_detected_rs4852=0;flip_20_detected_rs4852=0;flip_02_detected_rs4852=0;
	   execute_rs4852( get_command_and_parameter_after_leftShift_insertEnd_rs4852(0) );
	}//if
        previous_rs4852= raw_input_rs4852;
	//######## END RS4852 ##########
}//while  
//MAIN LOOP
//#########################    END MAIN EVENT   #################################

return 0;
}//main

//#######################################################################################################################################
















/* GARBAGE DISPOSAL
1...............

	//######## I2C1 ##########
	raw_input_i2c1 = read_binary_input_i2c1();
	if ( (previous_i2c1==2) & (raw_input_i2c1==1) ){  flip_21_detected_i2c1=1;  }
        if ( (previous_i2c1==1) & (raw_input_i2c1==2) ){  flip_12_detected_i2c1=1;  }
        if ( (previous_i2c1==2) & (raw_input_i2c1==0) ){  flip_20_detected_i2c1=1;  }
        if ( (previous_i2c1==0) & (raw_input_i2c1==2) ){  flip_02_detected_i2c1=1;  }
        if ( flip_21_detected_i2c1 & flip_12_detected_i2c1 ){ 
	   flip_21_detected_i2c1=0;flip_12_detected_i2c1=0;flip_20_detected_i2c1=0;flip_02_detected_i2c1=0;
	   balancing1_telemetry_leftShift_insertEnd_i2c1(1);
	}//if
        if ( flip_20_detected_i2c1 & flip_02_detected_i2c1 ){
           flip_21_detected_i2c1=0;flip_12_detected_i2c1=0;flip_20_detected_i2c1=0;flip_02_detected_i2c1=0;
	   balancing1_telemetry_leftShift_insertEnd_i2c1(0);
	}//if
        previous_i2c1 = raw_input_i2c1;
	//######## END I2C1 ########
	//######## I2C2 ############
	raw_input_i2c2 = read_binary_input_i2c2();
	if ( (previous_i2c2==2) & (raw_input_i2c2==1) ){  flip_21_detected_i2c2=1;  }
        if ( (previous_i2c2==1) & (raw_input_i2c2==2) ){  flip_12_detected_i2c2=1;  }
        if ( (previous_i2c2==2) & (raw_input_i2c2==0) ){  flip_20_detected_i2c2=1;  }
        if ( (previous_i2c2==0) & (raw_input_i2c2==2) ){  flip_02_detected_i2c2=1;  }
        if ( flip_21_detected_i2c2 & flip_12_detected_i2c2 ){ 
	   flip_21_detected_i2c2=0;flip_12_detected_i2c2=0;flip_20_detected_i2c2=0;flip_02_detected_i2c2=0;
	   balancing2_telemetry_leftShift_insertEnd_i2c2(1);
	}//if
        if ( flip_20_detected_i2c2 & flip_02_detected_i2c2 ){
           flip_21_detected_i2c2=0;flip_12_detected_i2c2=0;flip_20_detected_i2c2=0;flip_02_detected_i2c2=0;
	   balancing2_telemetry_leftShift_insertEnd_i2c2(0);
	}//if
        previous_i2c2 = raw_input_i2c2;
	//######## END I2C2 ########
	//######## I2C3 ############
	raw_input_i2c3 = read_binary_input_i2c3();
	if ( (previous_i2c3==2) & (raw_input_i2c3==1) ){  flip_21_detected_i2c3=1;  }
        if ( (previous_i2c3==1) & (raw_input_i2c3==2) ){  flip_12_detected_i2c3=1;  }
        if ( (previous_i2c3==2) & (raw_input_i2c3==0) ){  flip_20_detected_i2c3=1;  }
        if ( (previous_i2c3==0) & (raw_input_i2c3==2) ){  flip_02_detected_i2c3=1;  }
        if ( flip_21_detected_i2c3 & flip_12_detected_i2c3 ){ 
	   flip_21_detected_i2c3=0;flip_12_detected_i2c3=0;flip_20_detected_i2c3=0;flip_02_detected_i2c3=0;
	   temperature_sensor_leftShift_insertEnd_i2c3(1);
	}//if
        if ( flip_20_detected_i2c3 & flip_02_detected_i2c3 ){
           flip_21_detected_i2c3=0;flip_12_detected_i2c3=0;flip_20_detected_i2c3=0;flip_02_detected_i2c3=0;
	   temperature_sensor_leftShift_insertEnd_i2c3(0);
	}//if
        previous_i2c3 = raw_input_i2c3;
	//######## END I2C3 #########

 2.....................................
int raw_input_i2c1;
int previous_i2c1;
int flip_21_detected_i2c1=0;//change from 2(PAUSE) to 1(HIGH)
int flip_12_detected_i2c1=0;//change from 1(HIGH) to 2(PAUSE)
int flip_20_detected_i2c1=0;//change from 2(PAUSE) to 1(HIGH)
int flip_02_detected_i2c1=0;//change from 0(LOW) to 2(PAUSE)
//##
int raw_input_i2c2;
int previous_i2c2;
int flip_21_detected_i2c2=0;//change from 2(PAUSE) to 1(HIGH)
int flip_12_detected_i2c2=0;//change from 1(HIGH) to 2(PAUSE)
int flip_20_detected_i2c2=0;//change from 2(PAUSE) to 1(HIGH)
int flip_02_detected_i2c2=0;//change from 0(LOW) to 2(PAUSE)
//##
int raw_input_i2c3;
int previous_i2c3;
int flip_21_detected_i2c3=0;//change from 2(PAUSE) to 1(HIGH)
int flip_12_detected_i2c3=0;//change from 1(HIGH) to 2(PAUSE)
int flip_20_detected_i2c3=0;//change from 2(PAUSE) to 1(HIGH)
int flip_02_detected_i2c3=0;//change from 0(LOW) to 2(PAUSE)
//##



3................................
	
int read_binary_input_i2c1(){return 0;}

//###################################

int read_binary_input_i2c2(){return 0;}

//###################################

int read_binary_input_i2c3(){return 0;}

//##################################

*/
