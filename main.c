//Prferrable to use preamble
//uint8_t, uint16_t, uint32_t or chars can be used to replace the int types- but int is universal and type size is not an issue
//rs485 data when A and !A
//i2c data when clock high
//Dude, be cautious with your variables - public or global... _I are functions that read from input pins, _EN are raw integers(commands targeting output pins)

int main(){//main

//Boolean
uint8_t HIGH   = 1;
uint8_t LOW    = 0;
uint8_t PAUSE  = 2;
//TRANSMISSION AND RECEPTION (COMMUNICATION) SYMBOLS
uint8_t PING      = 34;//command
uint8_t ACK       = 47;//response
uint8_t NACK      = 52;//response
uint8_t SON       = 140;//command
uint8_t UHF       = 24;//parameter
uint8_t ADCS      = 162;//parameter
uint8_t GPS       = 75;//parameter
uint8_t SOF       = 218;//command
uint8_t SM        = 107;//command
uint8_t GM        = 122;//command
uint8_t GSC       = 94;//command
uint8_t SSC       = 209;//command
uint8_t GFP       = 134;//command
uint8_t SFP       = 90;//command
uint8_t FON       = 55;//command
uint8_t TWELVEBUS = 100;//telemetry parameter
uint8_t FIVEBUS   = 150;//telemetry parameter
uint8_t THREEBUS  = 200;//parameter
uint8_t FOF       = 233;//command
uint8_t GOSTM     = 157;//command
uint8_t KEN       = 255;//command
uint8_t KDIS      = 227;//command
uint8_t GD        = 15;//command
uint8_t PD        = 245;//command
uint8_t RD        = 222;//command
uint8_t WD        = 133;//command
uint8_t INITIALIZE    = 60;//mode parameter
uint8_t DETUMBLE      = 71;//mode parameter
uint8_t NORMAL        = 82;//mode parameter
uint8_t COMMUNICATION = 93;//mode parameter
uint8_t PAYLOAD       = 104;//mode parameter
uint8_t IMAGE         = 115;//mode parameter
uint8_t EMERGENCY     = 126;//mode parameter
int CUSTOM        = 69;//mode parameter
int PL5V_EN   = 230;//pin
int ADCS5V_EN = 143;//pin
int RS12V_EN  = 205;//pin
int XB12V_EN  = 139;//pin
int CCU5V_EN  = 155;//pin
int RS3V3_EN  = 212;//pin
int PL_EN     = 172;//pin
int ADCS_EN   = 143;//pin
int UHF_EN    = 189;//pin
int GPS_EN    = 57;//pin
int ADCS12V_EN= 199;//pin
int EPS_EN =97;//funny
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
int RESPONSE_WAIT=10000;
int CURRENTMODE       =0;
int CURRENTSYSTEMCLOCK=0;
int COMMAND_RESULT1=0;
int COMMAND_RESULT2=0;
int COMMANDARRAY [16];
int RESPONSEARRAY[16];
int INVALIDCOMMAND=1008;

	
/***   
//Array Initialisation    
for( int index=0; index<=15; index++ ){
   int COMMANDARRAY [index]=0;
   int RESPONSEARRAY[index]=0;  
}//for
//Initialisation of variables
**/

/**   i2c pfft
//clock
int clock(){
    int result=0;
    //capture A1;
    //A1 = HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_9);
    for( int i=0 ; i<3;i++){}//pause
    //capture (A2) A again;
    //A2 = HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_9);
    for( int i=0; i<3; i++;){}//pause
    //capture (A3) A again;
    //A3 = HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_9);
    if(  (A1+A2+A3) >=2   ){result=1;}//if
return result;
}//clock
**/

//read_input
int read_input(){
    int result=0;
	   if( (!HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )) & (!HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )) ){result=2;}//pause00
	   if( (!HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )) &   HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )  ){result=2;}//pause01
	   if(   HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )  & (!HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )) ){result=0;}//zero10
	   if(   HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_15 )  &   HAL_GPIO_ReadPin( GPIOD, GPIO_PIN_10 )  ){result=1;}//one 11
return result;
}//read_input
   

//response_wait
int response_wait(){
    for( int count=0;  count<=RESPONSE_WAIT ;count++ ){ }//do nothing
    //HAL delay could work too
return 0;
}//response_wait


//shift all to left, insert new bit at end
//command_leftShift_insertEnd
int command_leftShift_insertEnd(int insertionbit){
    for( int index=0;  index<=14; index++ ){  COMMANDARRAY[index] = COMMANDARRAY[index+1];   }//for
    COMMANDARRAY[15] = insertionbit;
return 0;  
}//command_leftShift_insertEnd


//read_input
int transmit_bit_response(int X){
    //PC10 PA15 Y(TX)
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
}//read_input


//send_response
int send_response(){
    for( int index=0;  index<=15; index++ ){  transmit_bit_response(  RESPONSEARRAY[index]  );  }//for
return 0;
}//send_response


//reset_command_array()
int reset_command_array(){
    for( int index=0; index<=15;  index++ ){  COMMANDARRAY[index] = 0;  }//for
return 0;
}//reset_command_array()

   
//reset_response_array
//Equivalent to 
//int reset_response_array(){
//RESPONSEARRAY[0] = 0;  RESPONSEARRAY[1] = 0;  RESPONSEARRAY[2] = 0;  RESPONSEARRAY[3] = 0;  RESPONSEARRAY[4] = 0;  RESPONSEARRAY[5] = 0;  RESPONSEARRAY[6] = 0;  RESPONSEARRAY[7] = 0;
//return 0;	
//}
int reset_response_array(){
    for( int index=0;  index<=15; index++ ){  RESPONSEARRAY[index] = 0;  }//for
return 0;
}//reset_response_array


	
//ack_response1
//Equivalent to 
//int ack_response1(){
//RESPONSEARRAY[0] = (int) (ACK&128);  RESPONSEARRAY[1] = (int) (ACK&64);  RESPONSEARRAY[2] = (int) (ACK&32);  RESPONSEARRAY[3] = (int) (ACK&16);  RESPONSEARRAY[4] = (int) (ACK&8);  RESPONSEARRAY[5] = (int) (ACK&4);  RESPONSEARRAY[6] = (int) (ACK&2);  RESPONSEARRAY[7] = (int) (ACK&1);
//return 0;
//}
int ack_response1(){
    for( int index=0;  index<=7; index++ ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( ACK>>(7-index) ) ) & 1 );   
    }//for
return 0;
}//ack_response1


//nack_response1
//Equivalent to 
//int nack_response1(){
//RESPONSEARRAY[0] = (int) (NACK&128);  RESPONSEARRAY[1] = (int) (NACK&64);  RESPONSEARRAY[2] = (int) (NACK&32);  RESPONSEARRAY[3] = (int) (NACK&16);  RESPONSEARRAY[4] = (int) (NACK&8);  RESPONSEARRAY[5] = (int) (NACK&4);  RESPONSEARRAY[6] = (int) (NACK&2);  RESPONSEARRAY[7] = (int) (NACK&1);
//return 0;
//}
//nack_response1
int nack_response1(){
    for( int index=0;  index<=7; index++ ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( NACK>>(7-index) ) ) & 1 );
    }//for
return 0;
}//nack_response1
   

//my_response2
//Equivalent to 
//int my_response2(int myvalue){
//RESPONSEARRAY[8] = (int) (myvalue&128);  RESPONSEARRAY[9] = (int) (myvalue&64);  RESPONSEARRAY[10] = (int) (myvalue&32);  RESPONSEARRAY[11] = (int) (myvalue&16);  RESPONSEARRAY[12] = (int) (myvalue&8);  RESPONSEARRAY[13] = (int) (myvalue&4);  RESPONSEARRAY[14] = (int) (myvalue&2);  RESPONSEARRAY[15] = (int) (myvalue&1);
//return 0;
//}
//my_response2
int my_response2( int myvalue){
    for( int index=8;  index<=15; index++ ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( myvalue>>(15-index) ) ) & 1 );
    }//for
return 0;
}//my_response2
   
//capture_command
//Equivalent to 
//int capture_command(){
//COMMAND_RESULT1 = COMMANDARRAY[0] + COMMANDARRAY[1] + COMMANDARRAY[2 ] + COMMANDARRAY[3 ] + COMMANDARRAY[4 ] + COMMANDARRAY[5 ] + COMMANDARRAY[6 ] + COMMANDARRAY[7 ] ;
//COMMAND_RESULT2 = COMMANDARRAY[8] + COMMANDARRAY[9] + COMMANDARRAY[10] + COMMANDARRAY[11] + COMMANDARRAY[12] + COMMANDARRAY[13] + COMMANDARRAY[14] + COMMANDARRAY[15] ;
//return 0;
//}   
//capture_command    
int captured_command(){
    COMMAND_RESULT1 = 0;
    for( int index=0;  index<=7;index++ ){
	    if(  (COMMANDARRAY[ index ]==0) | (COMMANDARRAY[ index ]==1)  ){  COMMAND_RESULT1 = COMMAND_RESULT1 + ( COMMANDARRAY[ index ] * ( (int)( 1<<(7-index) ) ) );  } else { COMMANDRESULT1==INVALIDCOMMAND;}
    }//for
    COMMAND_RESULT2 = 0;
    for( int index=8;  index<=15;index++){
	    if(  (COMMANDARRAY[ index ]==0) | (COMMANDARRAY[ index ]==1)  ){  COMMAND_RESULT2 = COMMAND_RESULT2 + ( COMMANDARRAY[ index ] * ( (int)(1<<(15-index) ) ) );  } else { COMMANDRESULT2==INVALIDCOMMAND;}
    }//for
    }//for
return 0;
}//captured_command

//write_response
//Equivalent to
//int write_response( int firstbyte, int secondbyte){
//RESPONSEARRAY[0] = (int) (firstbyte &128); RESPONSEARRAY[1] = (int) (firstbyte &64); RESPONSEARRAY[2 ] = (int) (firstbyte &32); RESPONSEARRAY[3 ] = (int) (firstbyte &16); RESPONSEARRAY[4 ] = (int) (firstbyte &8); RESPONSEARRAY[5 ] = (int) (firstbyte &4); RESPONSEARRAY[6 ] = (int) (firstbyte &2); RESPONSEARRAY[7 ] = (int) (firstbyte &1);    
//RESPONSEARRAY[8] = (int) (secondbyte&128); RESPONSEARRAY[9] = (int) (secondbyte&64); RESPONSEARRAY[10] = (int) (secondbyte&32); RESPONSEARRAY[11] = (int) (secondbyte&16); RESPONSEARRAY[12] = (int) (secondbyte&8); RESPONSEARRAY[13] = (int) (secondbyte&4); RESPONSEARRAY[14] = (int) (secondbyte&2); RESPONSEARRAY[15] = (int) (secondbyte&1);
//return 0;
//}
//write_response
int write_response( int firstbyte, int secondbyte){
    for( int index=0;  index<=7;index++ ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( firstbyte >>(7 -index) ) ) & 1 ); // & 1 eliminates all preceding bits  
    }//for
    for( int index=8;  index<=15;index++ ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( secondbyte>>(15-index) ) ) & 1 ); // & 1 eliminates all preceding bits 
    }//for
return 0;
}//write_response

   
//execute
int execute(){
    //PING
    if( (COMMAND_RESULT1==PING) & (!(COMMAND_RESULT1==INVALIDCOMMAND)) ){
	                       ack_response1();
	                       send_response();
	                       reset_response_array();
    }//ACK...........Fault reporting mechanisms?
    //SON
    if ( (COMMAND_RESULT1==SON) & (!(COMMAND_RESULT1==INVALIDCOMMAND)) ){
                             int else_check=1;
                             if(COMMAND_RESULT2==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(else_check==1               ){nack_response1();}//NACK
                             send_response();
                             reset_response_array();
    }//SON
    //SOF  
    if ( (COMMAND_RESULT1==SOF)  & (!(COMMAND_RESULT1==INVALIDCOMMAND))  ){
                             int else_check=1;
                             if(COMMAND_RESULT2==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(else_check==1               ){nack_response1();}//NACK
                             send_response();
                             reset_response_array();
    }//SOF
    //SM
    if (  (COMMAND_RESULT1==SM)  & (!(COMMAND_RESULT1==INVALIDCOMMAND))  ){
                             int else_check=1;
                             if(COMMAND_RESULT2==INITIALIZE    ){else_check=0;CURRENTMODE=INITIALIZE   ;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==DETUMBLE      ){else_check=0;CURRENTMODE=DETUMBLE     ;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==NORMAL        ){else_check=0;CURRENTMODE=NORMAL       ;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==COMMUNICATION ){else_check=0;CURRENTMODE=COMMUNICATION;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==PAYLOAD       ){else_check=0;CURRENTMODE=PAYLOAD      ;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==IMAGE         ){else_check=0;CURRENTMODE=IMAGE        ;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==EMERGENCY     ){else_check=0;CURRENTMODE=EMERGENCY    ;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(else_check==1                  ){nack_response1();}//NACK
                             send_response();
                             reset_response_array();
    }//SM
    //GM
    if (  (COMMAND_RESULT1==GM )  & (!(COMMAND_RESULT1==INVALIDCOMMAND))  ){ write_response(ACK,CURRENTMODE       );send_response();reset_response_array(); }//ACK
    //GM
    //GSC
    if (  (COMMAND_RESULT1==GSC)  & (!(COMMAND_RESULT1==INVALIDCOMMAND))  ){ write_response(ACK,CURRENTSYSTEMCLOCK);send_response();reset_response_array(); }//ACK.........MIGHT have to do away with 2 byte response limitation OR i can just specify what each count(1) represents as a time period for a 1 byte maximum
    //SSC
    if (  (COMMAND_RESULT1==SSC)  & (!(COMMAND_RESULT1==INVALIDCOMMAND))  ){ write_response(ACK, 0  );CURRENTSYSTEMCLOCK=COMMAND_RESULT2;send_response();reset_response_array(); }//ACK
    //GSC
    //GOSTM
    if (  (COMMAND_RESULT1==GOSTM)  & (!(COMMAND_RESULT1==INVALIDCOMMAND)) ){
        int a = (int) (XB12V_I()  <<7); 
        int b = (int) (ADCS12V_I()<<6);
        int c = (int) (RS5V_I()   <<5);
        int d = (int) (RS3V3_I()  <<4);
        int e = (int) (SA1_I()    <<3);
        int f = (int) (SA2_I()    <<2);
        int g = (int) (SA3_I()    <<1);
        write_response(  ACK, (int) (a | b | c | d | e | f | g |  1)    );
        //send_response();
        //reset_response_array();
    }//ACK
    //GOSTM
    //KEN
    if ( (COMMAND_RESULT1==KEN )   & (!(COMMAND_RESULT1==INVALIDCOMMAND))  ){ write_response(ACK,KEN ); send_response();reset_response_array(); }//ACK ...........shutting down all activity received from GCS or OBC
    //KEN
    //KDIS
    if (  (COMMAND_RESULT1==KDIS)  & (!(COMMAND_RESULT1==INVALIDCOMMAND))  ){ write_response(ACK,KDIS); send_response();reset_response_array(); }//ACK
    //KDIS
    //YOU CAN ALSO ADD LOGIC
return 0;
}//execute /*8801001003133498*/


int reset_and_assign_command_result_integers(){
    COMMAND_RESULT1 = 0;//refresh
    COMMAND_RESULT2 = 0;//refresh
    captured_command();//extract command(command_result1) and the parameter(command_result2)
return 0;
}

int PREVIOUS=0;	
//MAIN LOOP
while(1){//while
        int SKIP = 0;
        //HIGH
        if ( (read_input() == HIGH) & (PREVIOUS==PAUSE) ) {
                                    command_leftShift_insertEnd(1);//shift all command array items to left(MSB), lose the first MSB bit, insert new (LSB) bit at end
		                    execute();
                                    //COMMAND_RESULT1=0;//refresh
                                    //COMMAND_RESULT2=0;//refresh
                                    //captured_command();//extract command(command_result1) and the parameter(command_result2)
                		    reset_and_assign_command_result_integers();                    
				    //while(read_input()==HIGH){}//wait out the HIGH cycle
				    PREVIOUS=1;
                                    SKIP = 1;//start loop afresh
        }//if
        //HIGH
        //LOW
        if( (SKIP==0) & (read_input()==LOW ) & (PREVIOUS==PAUSE) ){
                                              command_leftShift_insertEnd(0);//shift all command array items to left(MSB), lose the first MSB bit, insert new (LSB) bit at end
					      execute();
                                              //COMMAND_RESULT1=0;//refresh
                                    	      //COMMAND_RESULT2=0;//refresh
                                    	      //captured_command();//extract command(command_result1) and the parameter(command_result2)
                		    	      reset_and_assign_command_result_integers();
                                              //while(read_input()==LOW){}//wait out the HIGH cycle
					      PREVIOUS=0;
                                              SKIP = 1;//start loop afresh
        }//if
        //LOW
        if( (SKIP==0) & (read_input()==PAUSE) ){
                                               //execute();//are there any valid commands captured...if so set up the response
                                               //while(read_input()==PAUSE){}//wait out the LOW cycle
		                               PREVIOUS=PAUSE;
        }//if
}//while  
//MAIN LOOP
   
return 0;
}//main
