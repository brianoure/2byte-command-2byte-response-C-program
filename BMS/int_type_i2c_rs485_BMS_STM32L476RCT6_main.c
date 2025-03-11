//Prferrable to use preamble
//uint8_t, uint16_t, uint32_t or chars can be used to replace the int types- but int is universal and type size is not an issue
//rs485 data when A and !A
//i2c data when clock high
//Dude, be cautious with your variables - public or global... _I are functions that read from input pins, _EN are raw integers(commands targeting output pins)
//Whoa! the EPS microntroller is actually  sampling the inputs in every while loop instance, so we have to check for changes in input states to determine if we have a 1 or a 0 

int main(){//main
	

	
//############ DECLARATIONS ###########
	
//Boolean
int HIGH          = 1  ;  int TRUE = HIGH; int ONE  = HIGH;
int LOW           = 0  ;  int FALSE= LOW ; int ZERO = LOW ;
int PAUSE         = 2  ;
int END           = 3  ;
//TRANSMISSION AND RECEPTION (COMMUNICATION) SYMBOLS
int PING          = 34 ;   //command
int ACK           = 47 ;   int ACKNOWLEDGE                   = ACK ;//response
int NACK          = 52 ;   int NOT_ACKNOWLEDGE               = NACK;//response
int SON           = 140;   int SWITCH_ON                     = SON ;//command
int UHF           = 24 ;   //parameter
int ADCS          = 162;   //parameter
int GPS           = 75 ;   //parameter
int SOF           = 218;   int SWITCH_OFF                    = SOF  ;//command
int SM            = 107;   int SET_MODE                      = SM   ;//command
int GM            = 122;   int GET_MODE                      = GM   ;//command
int GSC           = 94 ;   int GET_SYSTEM_CLOCK              = GSC  ;//command
int SSC           = 209;   int SET_SYSTEM_CLOCK              = SSC  ;//command
int GFP           = 134;   //command
int SFP           = 90 ;   //command
int FON           = 55 ;   int FUNCTION_ON                   = FON  ;//command
int TWELVEBUS     = 100;   //telemetry parameter
int FIVEBUS       = 150;   //telemetry parameter
int THREEBUS      = 200;   //parameter
int FOF           = 233;   int FUNCTION_OFF                  = FOF  ;//command
int GOSTM         = 157;   int GET_ONLINE_SYSTEM_TELEMETRY   = GOSTM;//command
int KEN           = 255;   int KILL_ENABLE                   = KEN  ;//command
int KDIS          = 227;   int KILL_DISABLE                  = KDIS ;//command
int GD            = 15 ;   int GET_DATA                      = GD   ;//command
int PD            = 245;   int PUT_DATA                      = PD   ;//command
int RD            = 222;   int READ_DATA                     = RD   ;//command
int WD            = 133;   int WRITE_DATA                    = WD   ;//command
int INITIALIZE    = 60 ;   //mode parameter
int DETUMBLE      = 71 ;   //mode parameter
int NORMAL        = 82 ;   //mode parameter
int COMMUNICATION = 93 ;   //mode parameter
int PAYLOAD       = 104;   //mode parameter
int IMAGE         = 115;   //mode parameter
int EMERGENCY     = 126;   //mode parameter
int CUSTOM        = 69 ;   //mode parameter
int PL5V_EN       = 230;   int PAYLOAD_5V_ENABLE              = PL5V_EN   ;//pin
int ADCS5V_EN     = 143;   int ADCS_5V_ENABLE                 = ADCS5V_EN ;//pin
int RS12V_EN      = 205;   int RESERVED_12V_EN                = RS12V_EN  ;//pin
int XB12V_EN      = 139;   int XBAND_12V_ENABLE               = XB12V_EN  ;//pin
int CCU5V_EN      = 155;   int CENTRAL_COMMAND_UNIT_5V_ENABLE = CCU5V_EN  ;//pin
int RS3V3_EN      = 212;   int RESERVED_3V_ENABLE             = RS3V3_EN  ;//pin
int PL_EN         = 172;   int PAYLOAD_ENABLE                 = PL_EN     ;//pin
int ADCS_EN       = 144;   int ADCS_ENABLE                    = ADCS_EN   ;//pin
int UHF_EN        = 189;   int UHF_ENABLE                     = UHF_EN    ;//pin
int GPS_EN        = 57 ;   int GPS_ENABLE                     = GPS_EN    ;//pin
int ADCS12V_EN    = 199;   int ADCS_12V_ENABLE                = ADCS12V_EN;//pin
int EPS_EN        = 97 ;   int EPS_ENABLE                     = EPS_EN    ;//funny
//BOOT0
int HEATER1    () {return 0;}//op
int HEATER2    () {return 0;}//op
int ALERT2     () {return 0;}//ip
int BOOT       () {return 0;}//op
int BOOT2      () {return 0;}//op
int I2C1_SCL   () {return 0;} //out to balancing1
int I2C1_SDA   () {return 0;} //in from balancing1
int I2C2_SCL   () {return 0;} //out to balancing2
int I2C2_SDA   () {return 0;} //in from balancing2
int I2C3_SCL   () {return 0;} //clock in from EPS/MCU
int I2C3_SDA   () {return 0;} //out to EPS/MCU
int RS4852_RX  () {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}//in from MCU/EPS
int RS4852_DE  () {return 0;} //in from EPS/MCU
int RS4852_TX  () {/*HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);*/return 0;}//out to EPS/MCU
// other variables
int RESPONSE_WAIT          = 10000;//response_wait()
int CURRENTMODE            = 0;
int CURRENTSYSTEMCLOCK     = 0;
int COMMAND_RESULT1_I2C1   = 0;
int COMMAND_RESULT2_I2C1   = 0;
int COMMANDARRAY_I2C1     [16];
int RESPONSEARRAY_I2C1    [16];
int COMMAND_RESULT1_I2C2   = 0;
int COMMAND_RESULT2_I2C2   = 0;
int COMMANDARRAY_I2C2     [16];
int RESPONSEARRAY_I2C2    [16];
int COMMAND_RESULT1_I2C3   = 0;
int COMMAND_RESULT2_I2C3   = 0;
int COMMANDARRAY_I2C3     [16];
int RESPONSEARRAY_I2C3    [16];
int COMMAND_RESULT1_RS4852 = 0;
int COMMAND_RESULT2_RS4852 = 0;
int COMMANDARRAY_RS4852   [16];
int RESPONSEARRAY_RS4852  [16];
//####################################
	
//read_input
int read_binary_input_i2c1(){//BAL 1
//send clk1
//read data1
return 0;//return data1
}//read_input

//####################################

//read_input
int read_binary_input_i2c2(){//BAL 2
//send clk2
//read data2
return 0;//return data2
}//read_input

//####################################

//read_input
int read_binary_input_i2c3(){//temp sensors
//send clk3
//read data3
return 0;//return data3
}//read_input
	
//###################################
//read_input
int read_binary_input_rs4852(){//from EPS main controller (MCU)
    //TRUTH TABLE RS485
    //PC10 PA15 Y(TX) ...................CAUTION
    //0    0    3(end)
    //0    1    2(pause)
    //1    0    0
    //1    1    1
    int result=0;
     /*framework customizable
	   //rs485 in......input binary value is when  two lines are exctly opposite/complementing each other...you just have to agree which set represents the ONE and which set represents the ZERO
	   if( (!HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )) & (!HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )) ){result=3;}//end00
	   if( (!HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )) &   HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )  ){result=1;}//one01
	   if(   HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )  & (!HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )) ){result=0;}//zero10
	   if(   HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )  &   HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )  ){result=2;}//pause11
	   //rs485 in
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
//command_leftShift_insertEnd_i2c
int command_leftShift_insertEnd_i2c(int insertionbit){
    for( int index=0;  index<=14; index++ ){  COMMANDARRAY_I2C[index] = COMMANDARRAY_I2C[index+1];   }//for
    COMMANDARRAY_I2C[15] = insertionbit;
return 0;  
}//command_leftShift_insertEnd_i2c

//####################################

//shift all to left, insert new bit at end
//command_leftShift_insertEnd_rs485
int command_leftShift_insertEnd_rs485(int insertionbit){
    for( int index=0;  index<=14; index++ ){  COMMANDARRAY_RS485[index] = COMMANDARRAY_RS485[index+1];   }//for
    COMMANDARRAY_RS485[15] = insertionbit;
return 0;  
}//command_leftShift_insertEnd_rs485

//###################################

//transmit_bit_response_i2c
int transmit_bit_response_i2c(int X){
    //TRUTH TABLE
    //PC10 PA15 Y(TX) ...................CAUTION
    //0    0    3(end)
    //0    1    2(pause)
    //1    0    0
    //1    1    1
    //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);//0
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET  );//1
    //response_wait();//keep pins in pause state
    //if(X==1){
            /*transmit ONE*/
            //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);//1
            //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);//1
    //}//if
    //if(X==0){
            /*transmit ZERO*/
            //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET  );//1
            //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);//0
    //}//if
    //response_wait();//keep pins in X state
    //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);//0
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET  );//1
    //response_wait();//keep pins in pause state

return 0;
}//transmit_bit_response_i2c

//#################################

//transmit_bit_response_rs485
int transmit_bit_response_rs485(int X){
    //TRUTH TABLE
    //PC10 PA15 Y(TX).....................CAUTION
    //0    0    3(end)
    //0    1    1
    //1    0    0
    //1    1    2(pause)
    //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);//0
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET  );//1
    //response_wait();//keep pins in pause state
    //if(X==1){/*transmit ONE*/
    //        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);//1
    //         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);//1
    //}//if
    //if(X==0){/*transmit ZERO*/
    //         HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET  );//1
    //        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);//0
    //}//if
    //response_wait();//keep pins in X state
    //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);//0
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET  );//1
    //response_wait();//keep pins in pause state
return 0;
}//transmit_bit_response_rs485

//#################################

//send_response_i2c
int send_response_i2c(){
    for( int index=0;  index<=15; index++ ){  transmit_bit_response_i2c(  RESPONSEARRAY_I2C[index]  );  }//for
return 0;
}//send_response_i2c

//##################################

//send_response_rs485
int send_response_rs485(){
    for( int index=0;  index<=15; index++ ){  transmit_bit_response_rs485(  RESPONSEARRAY_RS485[index]  );  }//for
return 0;
}//send_response_rs485

//################################
	
//reset_command_array_i2c
int reset_command_array_i2c(){
    for( int index=0; index<=15;  index++ ){  COMMANDARRAY_I2C[index] = 0;  }//for
return 0;
}//reset_command_array_i2c

//#################################

//reset_command_array_rs485
int reset_command_array_rs485(){
    for( int index=0; index<=15;  index++ ){  COMMANDARRAY_RS485[index] = 0;  }//for
return 0;
}//reset_command_array_rs485

//#################################

//reset_response_array_i2c
int reset_response_array_i2c(){
    for( int index=0;  index<=15; index++ ){  RESPONSEARRAY_I2C[index] = 0;  }//for
return 0;
}//reset_response_array_i2c
	
//#################################

//reset_response_array_rs485
int reset_response_array_rs485(){
    for( int index=0;  index<=15; index++ ){  RESPONSEARRAY_RS485[index] = 0;  }//for
return 0;
}//reset_response_array_rs485

//#################################

//capture_command_i2c    
int captured_command_i2c(){
    COMMAND_RESULT1_I2C = 0;
    for( int index=0; index<=7; index++ ){
       COMMAND_RESULT1_I2C = COMMAND_RESULT1_I2C + ( COMMANDARRAY_I2C[ index ] * ( (int)( 1<<( 7-index) ) ) ); 
    }//for
    COMMAND_RESULT2_I2C = 0;
    for( int index=8; index<=15; index++){
       COMMAND_RESULT2_I2C = COMMAND_RESULT2_I2C + ( COMMANDARRAY_I2C[ index ] * ( (int)( 1<<(15-index) ) ) );
    }//for
return 0;
}//captured_command_i2c 

//################################

//capture_command_rs485    
int captured_command_rs485(){
    COMMAND_RESULT1_RS485 = 0;
    for( int index=0;  index<=7;index++ ){
       COMMAND_RESULT1_RS485 = COMMAND_RESULT1_RS485 + ( COMMANDARRAY_RS485[ index ] * ( (int)( 1<<(7-index) ) ) ); 
    }//for
    COMMAND_RESULT2_RS485 = 0;
    for( int index=8;  index<=15;index++){
       COMMAND_RESULT2_RS485 = COMMAND_RESULT2_RS485 + ( COMMANDARRAY_RS485[ index ] * ( (int)(1<<(15-index) ) ) ); 
    }//for
return 0;
}//captured_command_rs485


//################################

//write_response_i2c
int write_response_i2c( int firstbyte, int secondbyte){
    for( int index=0;  index<=7;index++ ){
    RESPONSEARRAY_I2C[index] = (int) ( ( (int) ( firstbyte >>(7 -index) ) ) & 1 ); // & 1 eliminates all preceding bits  
    }//for
    for( int index=8;  index<=15;index++ ){
    RESPONSEARRAY_I2C[index] = (int) ( ( (int) ( secondbyte>>(15-index) ) ) & 1 ); // & 1 eliminates all preceding bits 
    }//for
    send_response_i2c();
    reset_response_array_i2c();
return 0;
}//write_response_i2c

//################################

//write_response_rs485
int write_response_rs485( int firstbyte, int secondbyte){
    for( int index=0;  index<=7;index++ ){
    RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( firstbyte >>(7 -index) ) ) & 1 ); // & 1 eliminates all preceding bits  
    }//for
    for( int index=8;  index<=15;index++ ){
    RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( secondbyte>>(15-index) ) ) & 1 ); // & 1 eliminates all preceding bits 
    }//for
    send_response_rs485();
    reset_response_array_rs485();
return 0;
}//write_response_rs485

//#################################

//execute
int execute_i2c(){
    if ( COMMAND_RESULT1_I2C==PING  ){  write_response_i2c(ACK,ZERO);  }//ACK...........Fault reporting mechanisms?
    if ( COMMAND_RESULT1_I2C==SON   ){
                             int else_check=1;
                             if(COMMAND_RESULT2_I2C==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(else_check==1                   ){write_response_i2c(NACK,0);}//NACK
    }//SON  
    if ( COMMAND_RESULT1_I2C==SOF  ){
                             int else_check=1;
                             if(COMMAND_RESULT2_I2C==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(else_check==1                   ){write_response_i2c(NACK,0);}//NACK
    }//SOF
    if ( COMMAND_RESULT1_I2C==SM  ){
                             int else_check=1;
                             if(COMMAND_RESULT2_I2C==INITIALIZE    ){else_check=0;CURRENTMODE=INITIALIZE   ;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==DETUMBLE      ){else_check=0;CURRENTMODE=DETUMBLE     ;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==NORMAL        ){else_check=0;CURRENTMODE=NORMAL       ;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==COMMUNICATION ){else_check=0;CURRENTMODE=COMMUNICATION;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==PAYLOAD       ){else_check=0;CURRENTMODE=PAYLOAD      ;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==IMAGE         ){else_check=0;CURRENTMODE=IMAGE        ;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_I2C==EMERGENCY     ){else_check=0;CURRENTMODE=EMERGENCY    ;write_response_i2c(ACK,0);     }//ACK.... do action
                             if(else_check==1                      ){write_response_i2c(NACK,0);}//NACK
    }//SM
    if (  COMMAND_RESULT1_I2C==GM    ){ write_response_i2c(ACK,CURRENTMODE       ); }//ACK
    if (  COMMAND_RESULT1_I2C==GSC   ){ write_response_i2c(ACK,CURRENTSYSTEMCLOCK); }//ACK.........MIGHT have to do away with 2 byte response limitation OR i can just specify what each count(1) represents as a time period for a 1 byte maximum
    if (  COMMAND_RESULT1_I2C==SSC   ){ write_response_i2c(ACK, 0  );CURRENTSYSTEMCLOCK=COMMAND_RESULT2_I2C; }//ACK
    if (  COMMAND_RESULT1_I2C==GOSTM ){
                             int a = ((int) (XB12V_I  ()<<7));  int b = ((int) (ADCS12V_I()<<6)); int c = ((int) (RS5V_I   ()<<5));  int d = ((int) (RS3V3_I  ()<<4));
                             int e = ((int) (SA1_I    ()<<3));  int f = ((int) (SA2_I    ()<<2)); int g = ((int) (SA3_I    ()<<1));
                             write_response_i2c(  ACK, ((int) (a | b | c | d | e | f | g |  1) )  );
    }//ACK GOSTM
    if ( COMMAND_RESULT1_I2C==KEN   ){ write_response_i2c(ACK,KEN );  }//ACK ...........shutting down all activity received from GCS or OBC//KEN
    if ( COMMAND_RESULT1_I2C==KDIS  ){ write_response_i2c(ACK,KDIS);  }//ACK //KDIS
    //YOU CAN ALSO ADD LOGIC
return 0;
}//execute

//#################################

//execute
int execute_rs485(){
    if(  COMMAND_RESULT1_RS485==PING ){ write_response_rs485(ACK,0); }//ACK...........Fault reporting mechanisms?
    if ( COMMAND_RESULT1_RS485==SON ){
                             int else_check=1;
                             if(COMMAND_RESULT2_RS485==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(else_check==1                     ){write_response_rs485(NACK,0);}//NACK
    }//SON
    if ( COMMAND_RESULT1_RS485==SOF ){
                             int else_check=1;
                             if(COMMAND_RESULT2_RS485==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(else_check==1                     ){write_response_rs485(NACK,0);}//NACK
    }//SOF
    if (  COMMAND_RESULT1_RS485==SM ){
                             int else_check=1;
                             if(COMMAND_RESULT2_RS485==INITIALIZE    ){else_check=0;CURRENTMODE=INITIALIZE   ;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==DETUMBLE      ){else_check=0;CURRENTMODE=DETUMBLE     ;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==NORMAL        ){else_check=0;CURRENTMODE=NORMAL       ;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==COMMUNICATION ){else_check=0;CURRENTMODE=COMMUNICATION;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==PAYLOAD       ){else_check=0;CURRENTMODE=PAYLOAD      ;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==IMAGE         ){else_check=0;CURRENTMODE=IMAGE        ;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(COMMAND_RESULT2_RS485==EMERGENCY     ){else_check=0;CURRENTMODE=EMERGENCY    ;write_response_rs485(ACK,0);     }//ACK.... do action
                             if(else_check==1                        ){write_response_rs485(NACK,0);}//NACK
    }//SM
    if (  COMMAND_RESULT1_RS485==GM    ){ write_response_rs485(ACK,CURRENTMODE       ); }//ACK //GM
    if (  COMMAND_RESULT1_RS485==GSC   ){ write_response_rs485(ACK,CURRENTSYSTEMCLOCK); }//ACK.........MIGHT have to do away with 2 byte response limitation OR i can just specify what each count(1) represents as a time period for a 1 byte maximum
    if (  COMMAND_RESULT1_RS485==SSC   ){ write_response_rs485(ACK, 0  );CURRENTSYSTEMCLOCK=COMMAND_RESULT2_RS485; }//ACK
    if (  COMMAND_RESULT1_RS485==GOSTM ){
                             int a = (int) (XB12V_I  ()<<7);  int b = (int) (ADCS12V_I()<<6); int c = (int) (RS5V_I   ()<<5);  int d = (int) (RS3V3_I  ()<<4);
                             int e = (int) (SA1_I    ()<<3);  int f = (int) (SA2_I    ()<<2); int g = (int) (SA3_I    ()<<1);
                             write_response_rs485(  ACK, (int) (a | b | c | d | e | f | g |  1)    );
    }//ACK //GOSTM
    if ( COMMAND_RESULT1_RS485==KEN   ){ write_response_rs485(ACK,KEN ); }//ACK ...........shutting down all activity received from GCS or OBC //KEN
    if ( COMMAND_RESULT1_RS485==KDIS  ){ write_response_rs485(ACK,KDIS); }//ACK //KDIS
    //YOU CAN ALSO ADD LOGIC
return 0;
}//execute

//#####################################

int reset_and_assign_command_result_integers_i2c(){
    COMMAND_RESULT1_I2C = 0;//refresh
    COMMAND_RESULT2_I2C = 0;//refresh
    captured_command_i2c();//extract command(command_result1) and the parameter(command_result2)
return 0;
}//reset_and_assign_command_result_integers

//####################################
int reset_and_assign_command_result_integers_rs485(){
    COMMAND_RESULT1_RS485 = 0;//refresh
    COMMAND_RESULT2_RS485 = 0;//refresh
    captured_command_rs485();//extract command(command_result1) and the parameter(command_result2)
return 0;
}//reset_and_assign_command_result_integers

//################################################################### END OF DECLARATIONS ################################################





//########################   MAIN EVENT  ###########################################
int raw_input_i2c;
int previous_i2c;
int flip_21_detected_i2c=0;//change from 2(PAUSE) to 1(HIGH)
int flip_12_detected_i2c=0;//change from 1(HIGH) to 2(PAUSE)
int flip_20_detected_i2c=0;//change from 2(PAUSE) to 1(HIGH)
int flip_02_detected_i2c=0;//change from 0(LOW) to 2(PAUSE)
//##
int raw_input_rs485;
int previous_rs485;
int flip_21_detected_rs485=0;//change from 2(PAUSE) to 1(HIGH)
int flip_12_detected_rs485=0;//change from 1(HIGH) to 2(PAUSE)
int flip_20_detected_rs485=0;//change from 2(PAUSE) to 1(HIGH)
int flip_02_detected_rs485=0;//change from 0(LOW) to 2(PAUSE)
//##
//MAIN LOOP
while(1){//while
	//######## I2C ############
	raw_input_i2c = read_binary_input_i2c();
	if ( (previous_i2c==2) & (raw_input_i2c==1) ){  flip_21_detected_i2c=1;  }
        if ( (previous_i2c==1) & (raw_input_i2c==2) ){  flip_12_detected_i2c=1;  }
        if ( (previous_i2c==2) & (raw_input_i2c==0) ){  flip_20_detected_i2c=1;  }
        if ( (previous_i2c==0) & (raw_input_i2c==2) ){  flip_02_detected_i2c=1;  }
        if ( flip_21_detected_i2c & flip_12_detected_i2c ){ 
	   command_leftShift_insertEnd_i2c(1);
	   flip_21_detected_i2c=0;
           flip_12_detected_i2c=0;
           flip_20_detected_i2c=0;
           flip_02_detected_i2c=0;
	   reset_and_assign_command_result_integers_i2c();
	   execute_i2c();
	}//if
        if ( flip_20_detected_i2c & flip_02_detected_i2c ){
           command_leftShift_insertEnd_i2c(0);
           flip_21_detected_i2c=0;
           flip_12_detected_i2c=0;
           flip_20_detected_i2c=0;
           flip_02_detected_i2c=0;
	   reset_and_assign_command_result_integers_i2c();
	   execute_i2c();
	}//if
        previous_i2c = raw_input_i2c;
	//######## END I2C ############
	//######## RS485 ##############
	raw_input_rs485 = read_binary_input_rs485();
	if ( (previous_rs485==2) & (raw_input_rs485==1) ){  flip_21_detected_rs485=1;  }
        if ( (previous_rs485==1) & (raw_input_rs485==2) ){  flip_12_detected_rs485=1;  }
        if ( (previous_rs485==2) & (raw_input_rs485==0) ){  flip_20_detected_rs485=1;  }
        if ( (previous_rs485==0) & (raw_input_rs485==2) ){  flip_02_detected_rs485=1;  }
        if ( flip_21_detected_rs485 & flip_12_detected_rs485 ){ 
	   command_leftShift_insertEnd_rs485(1);
	   flip_21_detected_rs485=0;
           flip_12_detected_rs485=0;
           flip_20_detected_rs485=0;
           flip_02_detected_rs485=0;
	   reset_and_assign_command_result_integers_rs485();
	   execute_rs485();
	}//if
        if ( flip_20_detected_rs485 & flip_02_detected_rs485 ){
           command_leftShift_insertEnd_rs485(0);
           flip_21_detected_rs485=0;
           flip_12_detected_rs485=0;
           flip_20_detected_rs485=0;
           flip_02_detected_rs485=0;
	   reset_and_assign_command_result_integers_rs485();
	   execute_rs485();
	}//if
        previous_rs485= raw_input_rs485;
	//######## END RS485 ############
}//while  
//MAIN LOOP
//#########################    END MAIN EVENT   #################################

return 0;
}//main
