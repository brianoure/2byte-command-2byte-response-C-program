//Prferrable to use preamble
//uint8_t, uint16_t, uint32_t or chars can be used to replace the int types- but int is universal and type size is not an issue
//rs485 data when A and !A
//i2c data when clock high
//Dude, be cautious with your variables - public or global... _I are functions that read from input pins, _EN are raw integers(commands targeting output pins)
//Whoa! the EPS microntroller is actually  sampling the inputs in every while loop instance, so we have to check for changes in input states to determine if we have a 1 or a 0 

int main(){//main
	
//############ DECLARATIONS ###########
	
//Boolean
uint8_t HIGH   = 1; uint8_t TRUE = 1;
uint8_t LOW    = 0; uint8_t FALSE= 1;
uint8_t PAUSE  = 2;
uint8_t END    = 3;
//TRANSMISSION AND RECEPTION (COMMUNICATION) SYMBOLS
uint8_t PING      = 34;    //command
uint8_t ACK       = 47;    uint8_t ACKNOWLEDGE    = ACK; //response
uint8_t NACK      = 52;    uint8_t NOT_ACKNOWLEDGE= NACK;//response
uint8_t SON       = 140;   uint8_t SWITCH_ON      = SON; //command
uint8_t UHF       = 24;    //parameter
uint8_t ADCS      = 162;   //parameter
uint8_t GPS       = 75;    //parameter
uint8_t SOF       = 218;   uint8_t SWITCH_OFF      = SOF;//command
uint8_t SM        = 107;   uint8_t SET_MODE        = SM ;//command
uint8_t GM        = 122;   uint8_t GET_MODE        = GM ;//command
uint8_t GSC       = 94;    uint8_t GET_SYSTEM_CLOCK= GSC;//command
uint8_t SSC       = 209;   uint8_t SET_SYSTEM_CLOCK= SSC;//command
uint8_t GFP       = 134;   //command
uint8_t SFP       = 90;    //command
uint8_t FON       = 55;    uint8_t FUNCTION_ON     = FON;//command
uint8_t TWELVEBUS = 100;   //telemetry parameter
uint8_t FIVEBUS   = 150;   //telemetry parameter
uint8_t THREEBUS  = 200;   //parameter
uint8_t FOF       = 233;   uint8_t FUNCTION_OFF                = FOF  ;//command
uint8_t GOSTM     = 157;   uint8_t GET_ONLINE_SYSTEM_TELEMETRY = GOSTM;//command
uint8_t KEN       = 255;   uint8_t KILL_ENABLE                 = KEN  ;//command
uint8_t KDIS      = 227;   uint8_t KILL_DISABLE                = KDIS ;//command
uint8_t GD        = 15;    uint8_t GET_DATA  = GD;//command
uint8_t PD        = 245;   uint8_t PUT_DATA  = PD;//command
uint8_t RD        = 222;   uint8_t READ_DATA = RD;//command
uint8_t WD        = 133;   uint8_t WRITE DATA= WD;//command
uint8_t INITIALIZE    = 60; //mode parameter
uint8_t DETUMBLE      = 71; //mode parameter
uint8_t NORMAL        = 82; //mode parameter
uint8_t COMMUNICATION = 93; //mode parameter
uint8_t PAYLOAD       = 104;//mode parameter
uint8_t IMAGE         = 115;//mode parameter
uint8_t EMERGENCY     = 126;//mode parameter
uint8_t CUSTOM        = 69 ;//mode parameter
uint8_t PL5V_EN   = 230; uint8_t PAYLOAD_5V_ENABLE = PL5V_EN  ;//pin
uint8_t ADCS5V_EN = 143; uint8_t ADCS_5V_ENABLE    = ADCS5V_EN;//pin
uint8_t RS12V_EN  = 205; uint8_t RESERVED_12V_EN   = RS12V_EN ;//pin
uint8_t XB12V_EN  = 139; uint8_t XBAND_12V_ENABLE  = XB12V_EN ;//pin
uint8_t CCU5V_EN  = 155; uint8_t CENTRAL_COMMAND_UNIT_5V_ENABLE = CCU5V_EN ;//pin
uint8_t RS3V3_EN  = 212; uint8_t RESERVED_3V_ENABLE             = RS3V3_EN ;//pin
uint8_t PL_EN     = 172; uint8_t PAYLOAD_ENABLE  = PL_EN     ;//pin
uint8_t ADCS_EN   = 143; uint8_t ADCS_ENABLE     = ADCS_EN   ;//pin
uint8_t UHF_EN    = 189; uint8_t UHF_ENABLE      = UHF_EN    ;//pin
uint8_t GPS_EN    = 57 ; uint8_t GPS_ENABLE      = GPS_EN    ;//pin
uint8_t ADCS12V_EN= 199; uint8_t ADCS_12V_ENABLE = ADCS12V_EN;//pin
uint8_t EPS_EN    = 97 ; uint8_t EPS_ENABLE      = EPS_EN    ;//funny
//BOOT0
int SA1_I()     {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int SA2_I()     {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int SA3_I()     {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int RS4851_RX() {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int RS4851_DE() {return 0;}
int RS4851_TX() {/*HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);*/return 0;}
int RS4852_RX() {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int RS4852_DE() {return 0;}
int RS4852_TX() {/*HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);*/return 0;}
int SPI1_SS()   {return 0;}
int SPI1_SCK()  {return 0;}
int SPI1_MISO() {return 0;}
int SPI1_MOSI() {return 0;}
int SPI3_SS()   {return 0;}
int SPI3_SCK()  {return 0;}
int SPI3_MISO() {return 0;}
int SPI3_MOSI() {return 0;}
int I2C2_SCL()  {return 0;}
int I2C2_SDA()  {return 0;}
int SYNC_PULSE(){return 0;}
int E_RST1()    {return 0;}
int E_RST0()    {return 0;}
int PWR_RST()   {return 0;}
int OBC_FAULT()  {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int CCU_FLT()    {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int OBC_I()      {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int CCU_I()      {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int ADCS_I()     {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int ADCS_FLT()   {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int UHF_I()      {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int UHF_FLT()    {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int PL_I()       {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int PL_FLT()     {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int RS_3V3_I()   {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int RS3V3_FLT()  {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int GPS_I()      {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int GPS_FLT()    {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int ADCS5V_I()   {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int ADCS5V_FLT() {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int PL5V_I()     {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int PL5V_FLT()   {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int CCU5V_I()    {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int CCU5V_FLT()  {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int XB12V_I()    {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int XB12V_FLT()  {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int ADCS12V_FLT(){/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int ADCS12V_I()  {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int RS12V_FLT()  {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int RS5V_FLT()   {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
int RS5V_I()     {/*HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 ))*/return 0;}
// other variables
int RESPONSE_WAIT         = 10000;
int CURRENTMODE           = 0;
int CURRENTSYSTEMCLOCK    = 0;
int COMMAND_RESULT1_I2C   = 0;
int COMMAND_RESULT2_I2C   = 0;
int COMMAND_RESULT1_RS485 = 0;
int COMMAND_RESULT2_RS485 = 0;
int COMMANDARRAY_I2C     [16];
int COMMANDARRAY_RS485   [16];
int RESPONSEARRAY_I2C    [16];
int RESPONSEARRAY_RS485  [16];
int INVALIDCOMMAND       = 1008;

//#####################################
	
//read_input
int read_binary_input_i2c(){
    //TRUTH TABLE
    //PC10 PA15 Y(TX) ...................CAUTION
    //0    0    3(end)
    //0    1    2(pause)
    //1    0    0
    //1    1    1
    int result=0;
	   //i2c in....input binary value is the pin value when the clock is high...int this case pin B15 is the clock and D10 is the signal
	   if( (!HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )) & (!HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )) ){result=3;}//end00
	   if( (!HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )) &   HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )  ){result=2;}//pause01
	   if(   HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )  & (!HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )) ){result=0;}//zero10
	   if(   HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )  &   HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )  ){result=1;}//one 11
	   //i2c in
return result;
}//read_input

//#######################################

//read_input
int read_binary_input_rs485(){
    //TRUTH TABLE
    //PC10 PA15 Y(TX) ...................CAUTION
    //0    0    3(end)
    //0    1    2(pause)
    //1    0    0
    //1    1    1
    int result=0;
	   //rs485 in......input binary value is when  two lines are exctly opposite/complementing each other...you just have to agree which set represents the ONE and which set represents the ZERO
	   if( (!HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )) & (!HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )) ){result=3;}//end00
	   if( (!HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )) &   HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )  ){result=1;}//one01
	   if(   HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )  & (!HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )) ){result=0;}//zero10
	   if(   HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )  &   HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )  ){result=2;}//pause11
	   //rs485 in
return result;
}//read_input
	
//######################################   

//response_wait
int response_wait(){
    for( int count=0;  count<=RESPONSE_WAIT ;count++ ){ }//do nothing
    //HAL delay could work too
return 0;
}//response_wait

//#####################################

//shift all to left, insert new bit at end
//command_leftShift_insertEnd_i2c
int command_leftShift_insertEnd_i2c(int insertionbit){
    for( int index=0;  index<=14; index++ ){  COMMANDARRAY_I2C[index] = COMMANDARRAY_I2C[index+1];   }//for
    COMMANDARRAY_I2C[15] = insertionbit;
return 0;  
}//command_leftShift_insertEnd_i2c

//#################################

//shift all to left, insert new bit at end
//command_leftShift_insertEnd_rs485
int command_leftShift_insertEnd_rs485(int insertionbit){
    for( int index=0;  index<=14; index++ ){  COMMANDARRAY_RS485[index] = COMMANDARRAY_RS485[index+1];   }//for
    COMMANDARRAY_RS485[15] = insertionbit;
return 0;  
}//command_leftShift_insertEnd_rs485

//#################################

//transmit_bit_response_i2c
int transmit_bit_response_i2c(int X){
    //TRUTH TABLE
    //PC10 PA15 Y(TX) ...................CAUTION
    //0    0    3(end)
    //0    1    2(pause)
    //1    0    0
    //1    1    1
    if(X==1){/*transmit ONE*/
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);//1
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);//1
    }//if
    if(X==0){/*transmit ZERO*/
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET  );//1
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);//0
    }//if
    response_wait();//keep pins in X state
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);//0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET  );//1
    response_wait();//keep pins in pause state
return 0;
}//transmit_bit_response_i2c

//######################################

//transmit_bit_response_rs485
int transmit_bit_response_rs485(int X){
    //TRUTH TABLE
    //PC10 PA15 Y(TX).....................CAUTION
    //0    0    3(end)
    //0    1    1
    //1    0    0
    //1    1    2(pause)
    if(X==1){/*transmit ONE*/
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);//1
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);//1
    }//if
    if(X==0){/*transmit ZERO*/
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET  );//1
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);//0
    }//if
    response_wait();//keep pins in X state
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);//0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET  );//1
    response_wait();//keep pins in pause state
return 0;
}//transmit_bit_response_rs485

//######################################

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

//##################################
	
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
int reset_response_array_rs485(){
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
	
//ack_response1_i2c
int ack_response1_i2c(){
    for( int index=0;  index<=7; index++ ){
    RESPONSEARRAY_I2C[index] = (int) ( ( (int) ( ACK>>(7-index) ) ) & 1 );   
    }//for
return 0;
}//ack_response1_i2c

//################################

//ack_response1_rs485
int ack_response1_rs485(){
    for( int index=0;  index<=7; index++ ){
    RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( ACK>>(7-index) ) ) & 1 );   
    }//for
return 0;
}//ack_response1_rs485
	
//################################
	
//nack_response1_i2c
int nack_response1_i2c(){
    for( int index=0;  index<=7; index++ ){
    RESPONSEARRAY_I2C[index] = (int) ( ( (int) ( NACK>>(7-index) ) ) & 1 );
    }//for
return 0;
}//nack_response1_i2c
   
//###################################

//nack_response1_rs485
int nack_response1_rs485(){
    for( int index=0;  index<=7; index++ ){
    RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( NACK>>(7-index) ) ) & 1 );
    }//for
return 0;
}//nack_response1_rs485
	
//###################################
	
//my_response2_i2c
int my_response2_i2c( int myvalue){
    for( int index=8;  index<=15; index++ ){
    RESPONSEARRAY_I2C[index] = (int) ( ( (int) ( myvalue>>(15-index) ) ) & 1 );
    }//for
return 0;
}//my_response2_i2c

//#################################

//my_response2_rs485
int my_response2_rs485( int myvalue){
    for( int index=8;  index<=15; index++ ){
    RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( myvalue>>(15-index) ) ) & 1 );
    }//for
return 0;
}//my_response2_rs485
	
//#################################

//capture_command_i2c    
int captured_command_i2c(){
    COMMAND_RESULT1_I2C = 0;
    for( int index=0;  index<=7;index++ ){
	    if(  (COMMANDARRAY_I2C[ index ]==0) | (COMMANDARRAY_I2C[ index ]==1)  ){  COMMAND_RESULT1_I2C = COMMAND_RESULT1_I2C + ( COMMANDARRAY_I2C[ index ] * ( (int)( 1<<(7-index) ) ) );  } else { COMMANDRESULT1_I2C==INVALIDCOMMAND;}
    }//for
    COMMAND_RESULT2_I2C = 0;
    for( int index=8;  index<=15;index++){
	    if(  (COMMANDARRAY_I2C[ index ]==0) | (COMMANDARRAY_I2C[ index ]==1)  ){  COMMAND_RESULT2_I2C = COMMAND_RESULT2_I2C + ( COMMANDARRAY_I2C[ index ] * ( (int)(1<<(15-index) ) ) );  } else { COMMANDRESULT2_I2C==INVALIDCOMMAND;}
    }//for
    }//for
return 0;
}//captured_command_i2c 

//#############################

//capture_command_rs485    
int captured_command_rs485(){
    COMMAND_RESULT1_RS485 = 0;
    for( int index=0;  index<=7;index++ ){
	    if(  (COMMANDARRAY_RS485[ index ]==0) | (COMMANDARRAY_RS485[ index ]==1)  ){  COMMAND_RESULT1_RS485 = COMMAND_RESULT1_RS485 + ( COMMANDARRAY_RS485[ index ] * ( (int)( 1<<(7-index) ) ) );  } else { COMMANDRESULT1_RS485==INVALIDCOMMAND;}
    }//for
    COMMAND_RESULT2_RS485 = 0;
    for( int index=8;  index<=15;index++){
	    if(  (COMMANDARRAY_RS485[ index ]==0) | (COMMANDARRAY_RS485[ index ]==1)  ){  COMMAND_RESULT2_RS485 = COMMAND_RESULT2_RS485 + ( COMMANDARRAY_RS485[ index ] * ( (int)(1<<(15-index) ) ) );  } else { COMMANDRESULT2_RS485==INVALIDCOMMAND;}
    }//for
    }//for
return 0;
}//captured_command_rs485


//##########################

//write_response_i2c
int write_response_i2c( int firstbyte, int secondbyte){
    for( int index=0;  index<=7;index++ ){
    RESPONSEARRAY_I2C[index] = (int) ( ( (int) ( firstbyte >>(7 -index) ) ) & 1 ); // & 1 eliminates all preceding bits  
    }//for
    for( int index=8;  index<=15;index++ ){
    RESPONSEARRAY_I2C[index] = (int) ( ( (int) ( secondbyte>>(15-index) ) ) & 1 ); // & 1 eliminates all preceding bits 
    }//for
return 0;
}//write_response_i2c


//#######################

//write_response_rs485
int write_response_rs485( int firstbyte, int secondbyte){
    for( int index=0;  index<=7;index++ ){
    RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( firstbyte >>(7 -index) ) ) & 1 ); // & 1 eliminates all preceding bits  
    }//for
    for( int index=8;  index<=15;index++ ){
    RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( secondbyte>>(15-index) ) ) & 1 ); // & 1 eliminates all preceding bits 
    }//for
return 0;
}//write_response_rs485

//#######################

//execute
int execute_i2c(){
    //PING
    if( (COMMAND_RESULT1_I2C==PING) & (!(COMMAND_RESULT1_I2C==INVALIDCOMMAND)) ){
	                       ack_response1_i2c();
	                       send_response_i2c();
	                       reset_response_array_i2c();
    }//ACK...........Fault reporting mechanisms?
    //SON
    if ( (COMMAND_RESULT1_I2C==SON) & (!(COMMAND_RESULT1_I2C==INVALIDCOMMAND)) ){
                             int else_check=1;
                             if(COMMAND_RESULT2_I2C==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(else_check==1               ){nack_response1_i2c();}//NACK
                             send_response_i2c();
                             reset_response_array_i2c();
    }//SON
    //SOF  
    if ( (COMMAND_RESULT1_I2C==SOF)  & (!(COMMAND_RESULT1_I2C==INVALIDCOMMAND))  ){
                             int else_check=1;
                             if(COMMAND_RESULT2_I2C==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(else_check==1               ){nack_response1_i2c();}//NACK
                             send_response_i2c();
                             reset_response_array_i2c();
    }//SOF
    //SM
    if (  (COMMAND_RESULT1_I2C==SM)  & (!(COMMAND_RESULT1_I2C==INVALIDCOMMAND))  ){
                             int else_check=1;
                             if(COMMAND_RESULT2_I2C==INITIALIZE    ){else_check=0;CURRENTMODE=INITIALIZE   ;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==DETUMBLE      ){else_check=0;CURRENTMODE=DETUMBLE     ;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==NORMAL        ){else_check=0;CURRENTMODE=NORMAL       ;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==COMMUNICATION ){else_check=0;CURRENTMODE=COMMUNICATION;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==PAYLOAD       ){else_check=0;CURRENTMODE=PAYLOAD      ;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==IMAGE         ){else_check=0;CURRENTMODE=IMAGE        ;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_I2C==EMERGENCY     ){else_check=0;CURRENTMODE=EMERGENCY    ;ack_response1_i2c();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(else_check==1                  ){nack_response1_i2c();}//NACK
                             send_response_i2c();
                             reset_response_array_i2c();
    }//SM
    //GM
    if (  (COMMAND_RESULT1_I2C==GM )  & (!(COMMAND_RESULT1_I2C==INVALIDCOMMAND))  ){ write_response_i2c(ACK,CURRENTMODE       );send_response_i2c();reset_response_array_i2c(); }//ACK
    //GM
    //GSC
    if (  (COMMAND_RESULT1_I2C==GSC)  & (!(COMMAND_RESULT1_I2C==INVALIDCOMMAND))  ){ write_response_i2c(ACK,CURRENTSYSTEMCLOCK);send_response_i2c();reset_response_array_i2c(); }//ACK.........MIGHT have to do away with 2 byte response limitation OR i can just specify what each count(1) represents as a time period for a 1 byte maximum
    //SSC
    if (  (COMMAND_RESULT1_I2C==SSC)  & (!(COMMAND_RESULT1_I2C==INVALIDCOMMAND))  ){ write_response_i2c(ACK, 0  );CURRENTSYSTEMCLOCK=COMMAND_RESULT2;send_response_i2c();reset_response_array_i2c(); }//ACK
    //GSC
    //GOSTM
    if (  (COMMAND_RESULT1_I2C==GOSTM)  & (!(COMMAND_RESULT1_I2C==INVALIDCOMMAND)) ){
        int a = (int) (XB12V_I()  <<7); 
        int b = (int) (ADCS12V_I()<<6);
        int c = (int) (RS5V_I()   <<5);
        int d = (int) (RS3V3_I()  <<4);
        int e = (int) (SA1_I()    <<3);
        int f = (int) (SA2_I()    <<2);
        int g = (int) (SA3_I()    <<1);
        write_response_i2c(  ACK, (int) (a | b | c | d | e | f | g |  1)    );
        //send_response();
        //reset_response_array();
    }//ACK
    //GOSTM
    //KEN
    if ( (COMMAND_RESULT1_I2C==KEN )   & (!(COMMAND_RESULT1_I2C==INVALIDCOMMAND))  ){ write_response_i2c(ACK,KEN ); send_response_i2c();reset_response_array_i2c(); }//ACK ...........shutting down all activity received from GCS or OBC
    //KEN
    //KDIS
    if (  (COMMAND_RESULT1_I2C==KDIS)  & (!(COMMAND_RESULT1_I2C==INVALIDCOMMAND))  ){ write_response_i2c(ACK,KDIS); send_response_i2c();reset_response_array_i2c(); }//ACK
    //KDIS
    //YOU CAN ALSO ADD LOGIC
return 0;
}//execute

//##############


//execute
int execute_rs485(){
    //PING
    if( (COMMAND_RESULT1_RS485==PING) & (!(COMMAND_RESULT1_RS485==INVALIDCOMMAND)) ){
	                       ack_response1_rs485();
	                       send_response_rs485();
	                       reset_response_array_rs485();
    }//ACK...........Fault reporting mechanisms?
    //SON
    if ( (COMMAND_RESULT1_RS485==SON) & (!(COMMAND_RESULT1_RS485==INVALIDCOMMAND)) ){
                             int else_check=1;
                             if(COMMAND_RESULT2_RS485==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(else_check==1               ){nack_response1_rs485();}//NACK
                             send_response_rs485();
                             reset_response_array_rs485();
    }//SON
    //SOF  
    if ( (COMMAND_RESULT1_RS485==SOF)  & (!(COMMAND_RESULT1_RS485==INVALIDCOMMAND))  ){
                             int else_check=1;
                             if(COMMAND_RESULT2_RS485==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(else_check==1               ){nack_response1_rs485();}//NACK
                             send_response_rs485();
                             reset_response_array_rs485();
    }//SOF
    //SM
    if (  (COMMAND_RESULT1_RS485==SM)  & (!(COMMAND_RESULT1_RS485==INVALIDCOMMAND))  ){
                             int else_check=1;
                             if(COMMAND_RESULT2_RS485==INITIALIZE    ){else_check=0;CURRENTMODE=INITIALIZE   ;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==DETUMBLE      ){else_check=0;CURRENTMODE=DETUMBLE     ;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==NORMAL        ){else_check=0;CURRENTMODE=NORMAL       ;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==COMMUNICATION ){else_check=0;CURRENTMODE=COMMUNICATION;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==PAYLOAD       ){else_check=0;CURRENTMODE=PAYLOAD      ;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==IMAGE         ){else_check=0;CURRENTMODE=IMAGE        ;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2_RS485==EMERGENCY     ){else_check=0;CURRENTMODE=EMERGENCY    ;ack_response1_rs485();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(else_check==1                  ){nack_response1_rs485();}//NACK
                             send_response_rs485();
                             reset_response_array_rs485();
    }//SM
    //GM
    if (  (COMMAND_RESULT1_RS485==GM )  & (!(COMMAND_RESULT1_RS485==INVALIDCOMMAND))  ){ write_response_rs485(ACK,CURRENTMODE       );send_response_rs485();reset_response_array_rs485(); }//ACK
    //GM
    //GSC
    if (  (COMMAND_RESULT1_RS485==GSC)  & (!(COMMAND_RESULT1_RS485==INVALIDCOMMAND))  ){ write_response_rs485(ACK,CURRENTSYSTEMCLOCK);send_response_rs485();reset_response_array_rs485(); }//ACK.........MIGHT have to do away with 2 byte response limitation OR i can just specify what each count(1) represents as a time period for a 1 byte maximum
    //SSC
    if (  (COMMAND_RESULT1_RS485==SSC)  & (!(COMMAND_RESULT1_RS485==INVALIDCOMMAND))  ){ write_response_rs485(ACK, 0  );CURRENTSYSTEMCLOCK=COMMAND_RESULT2;send_response_rs485();reset_response_array_rs485(); }//ACK
    //GSC
    //GOSTM
    if (  (COMMAND_RESULT1_RS485==GOSTM)  & (!(COMMAND_RESULT1_RS485==INVALIDCOMMAND)) ){
        int a = (int) (XB12V_I()  <<7); 
        int b = (int) (ADCS12V_I()<<6);
        int c = (int) (RS5V_I()   <<5);
        int d = (int) (RS3V3_I()  <<4);
        int e = (int) (SA1_I()    <<3);
        int f = (int) (SA2_I()    <<2);
        int g = (int) (SA3_I()    <<1);
        write_response_rs485(  ACK, (int) (a | b | c | d | e | f | g |  1)    );
        //send_response();
        //reset_response_array();
    }//ACK
    //GOSTM
    //KEN
    if ( (COMMAND_RESULT1_RS485==KEN )   & (!(COMMAND_RESULT1_RS485==INVALIDCOMMAND))  ){ write_response_rs485(ACK,KEN ); send_response_rs485();reset_response_array_rs485(); }//ACK ...........shutting down all activity received from GCS or OBC
    //KEN
    //KDIS
    if (  (COMMAND_RESULT1_RS485==KDIS)  & (!(COMMAND_RESULT1_RS485==INVALIDCOMMAND))  ){ write_response_rs485(ACK,KDIS); send_response_rs485();reset_response_array_rs485(); }//ACK
    //KDIS
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
    captured_command__rs485();//extract command(command_result1) and the parameter(command_result2)
return 0;
}//reset_and_assign_command_result_integers

//################################################################### END OF DECLARATIONS ################################################





//########################   MAIN EVENT  ###########################################
int previous_i2c;
int flip_21_detected_i2c=0;//change from 2(PAUSE) to 1(HIGH)
int flip_12_detected_i2c=0;//change from 1(HIGH) to 2(PAUSE)
int flip_20_detected_i2c=0;//change from 2(PAUSE) to 1(HIGH)
int flip_02_detected_i2c=0;//change from 0(LOW) to 2(PAUSE)
//##
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
	   shiftleft_insertendbit_i2c(1);
	   flip_21_detected_i2c=0;
           flip_12_detected_i2c=0;
           flip_20_detected_i2c=0;
           flip_02_detected_i2c=0;
	   reset_and_assign_command_result_integers_i2c();
	   execute_i2c();
	}//if
        if ( flip_20_detected_i2c & flip_02_detected_i2c ){
           shiftleft_insertendbit_i2c(0);
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
	raw_input_i2c = read_binary_input_i2c();
	if ( (previous_rs485==2) & (raw_input_rs485==1) ){  flip_21_detected_rs485=1;  }
        if ( (previous_rs485==1) & (raw_input_rs485==2) ){  flip_12_detected_rs485=1;  }
        if ( (previous_rs485==2) & (raw_input_rs485==0) ){  flip_20_detected_rs485=1;  }
        if ( (previous_rs485==0) & (raw_input_rs485==2) ){  flip_02_detected_rs485=1;  }
        if ( flip_21_detected__rs485 & flip_12_detected_rs485 ){ 
	   shiftleft_insertendbit_rs485(1);
	   flip_21_detected_rs485=0;
           flip_12_detected_rs485=0;
           flip_20_detected_rs485=0;
           flip_02_detected_rs485=0;
	   reset_and_assign_command_result_integers_rs485();
	   execute_rs485();
	}//if
        if ( flip_20_detected_rs485 & flip_02_detected_rs485 ){
           shiftleft_insertendbit_rs485(0);
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
