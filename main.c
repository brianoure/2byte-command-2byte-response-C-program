//Prferrable to use preamble
//uint8_t, uint16_t, uint32_t or chars can be used to replace the int types- but int is universal and type size is not an issue
//rs485 data when A and !A
//i2c data when clock high


int main(){//main

//Boolean
int HIGH   = 1;
int LOW    = 0;
int PAUSE  = 2;
//SYMBOLS
int PING      = 34;//command
int ACK       = 47;//response
int NACK      = 52;//response
int SON       = 140;//command
int UHF       = 24;//parameter
int ADCS      = 162;//parameter
int GPS       = 75;//parameter
int SOF       = 218;//command
int SM        = 107;//command
int GM        = 122;//command
int GSC       = 94;//command
int SSC       = 209;//command
int GFP       = 134;//command
int SFP       = 90;//command
int FON       = 55;//command
int TWELVEBUS = 100;//telemetry parameter
int FIVEBUS   = 150;//telemetry parameter
int THREEBUS  = 200;//parameter
int FOF       = 233;//command
int GOSTM     = 157;//command
int KEN       = 255;//command
int KDIS      = 227;//command
int GD        = 15;//command
int PD        = 245;//command
int RD        = 222;//command
int WD        = 133;//command
int INITIALIZE    = 60;//mode parameter
int DETUMBLE      = 71;//mode parameter
int NORMAL        = 82;//mode parameter
int COMMUNICATION = 93;//mode parameter
int PAYLOAD       = 104;//mode parameter
int IMAGE         = 115;//mode parameter
int EMERGENCY     = 126;//mode parameter
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
int SA1_I = 97;//pin
int SA2_I = 79;//pin
int SA3_I = 63;//pin
// other variables
int RESPONSE_WAIT=10000;
int CURRENTMODE       =0;
int CURRENTSYSTEMCLOCK=0;
int COMMAND_RESULT1=0;
int COMMAND_RESULT2=0;
int COMMANDARRAY [16];
int RESPONSEARRAY[16];
 

/***
PING	34
SON	140
SOF	218
SM	1O7
GM	122
GSC	94
SSC	209
GFP	134
SFP	90
FON	55
FOF	233
GOSTM	157
KEN	255
KDIS	227
GD	15
PD	245
RD	222
WD	133
UHF	24
ADCS	162
GPS	75
INITIALIZE	60
DETUMBLE	71
NORMAL	82
COMMUNICATION	93
PAYLOAD	104
IMAGE	115
EMERGENCY	126
CUSTOM  69
PL5V_EN	230
ADCS5V_EN	143
RS12V_EN	205
XB12V_EN	139
 CCU5V_EN	155
 RS3V3_EN	212
 PL_EN	172
ADCS_EN	250
UHF_EN	189
GPS_EN	57
ADCS12V_EN	199
ACK	47
NACK	52
TWELVEBUS	100
FIVEBUS	150
THREEBUS	200
**/
	
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
    for( int count=0;  count<=RESPONSE_WAIT ;count++; ){ }//do nothing
    //HAL delay could work too
return 0;
}//response_wait


//shift all to left, insert new bit at end
//command_leftShift_insertEnd
int command_leftShift_insertEnd(int insertionbit){
    for( int index=0;  index<=14; index++; ){  COMMANDARRAY[index] = COMMANDARRAY[index+1];   }//for
    COMMANDARRAY[15] = insertionbit;
return 0;  
}//command_leftShift_insertEnd


//read_input
int transmit_bit_response(int X){
    //PC10 PA15 Y(TX)
    //0    0    2(pause)
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


//two_byte_respond
int two_byte_respond(){
    for( int index=0;  index<=15; index++; ){  transmit_bit_response(  RESPONSEARRAY[index]  );  }//for
return 0;
}//two_byte_respond


//reset_command_array()
int reset_command_array(){
    for( int index=0; index<=15;  index++; ){  COMMANDARRAY[index] = 0;  }//for
return 0;
}//reset_command_array()

   
//reset_response_array
int reset_response_array(){
    for( int index=0;  index<=15; index++; ){  RESPONSEARRAY[index] = 0;  }//for
return 0;
}//reset_response_array


	
//ack_response1
int ack_response1(){
    for( int index=0;  index<=7; index++; ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( ACK>>(7-index) ) ) & 1 );   
    }//for
return 0;
}//ack_response1


	
//nack_response1
int nack_response1(){
    for( int index=0;  index<=7; index++; ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( NACK>>(7-index) ) ) & 1 );
    }//for
return 0;
}//nack_response1
   


//my_response2
int my_response2( int myvalue){
    for( int index=8;  index<=15; index++; ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( myvalue>>(15-index) ) ) & 1 );
    }//for
return 0;
}//my_response2
   
   
//capture_command    
int captured_command(){
    COMMAND_RESULT1 = 0;
    for( int index=0;  index<=7;index++; ){
    COMMAND_RESULT1 = COMMAND_RESULT1 + ( COMMANDARRAY[ index ] * ( (int)( 1<<(7-index) ) ) );
    }//for
    COMMAND_RESULT2 = 0;
    for( int index=8;  index<=15;index++; ){
    COMMAND_RESULT2 = COMMAND_RESULT2 + ( COMMANDARRAY[ index ] * ( (int)(1<<(15-index) ) ) );
    }//for
return 0;
}//captured_command


//my_full_response
int my_full_response( int firstbyte, int secondbyte){
    for( int index=0;  index<=7;index++; ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( firstbyte >>(7 -index) ) ) & 1 ); // & 1 eliminates all preceding bits  
    }//for
    for( int index=8;  index<=15;index++;){
    RESPONSEARRAY[index] = (int) ( ( (int) ( secondbyte>>(15-index) ) ) & 1 ); // & 1 eliminates all preceding bits 
    }//for
return 0;
}//my_full_response

   
//execute
int execute(){
    //PING
    if( COMMAND_RESULT1==PING ){ack_response1();two_byte_respond();reset_response_array();}//ACK...........Fault reporrting mechanisms?
    //SON
    if (COMMAND_RESULT1==SON){
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
                             two_byte_respond();
                             reset_response_array();
    }//SON
    //SOF  
    if (COMMAND_RESULT1==SOF){
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
                             two_byte_respond();
                             reset_response_array();
    }//SOF
    //SM
    if (COMMAND_RESULT1==SM ){
                             int else_check=1;
                             if(COMMAND_RESULT2==INITIALIZE    ){else_check=0;CURRENTMODE=INITIALIZE   ;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==DETUMBLE      ){else_check=0;CURRENTMODE=DETUMBLE     ;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==NORMAL        ){else_check=0;CURRENTMODE=NORMAL       ;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==COMMUNICATION ){else_check=0;CURRENTMODE=COMMUNICATION;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==PAYLOAD       ){else_check=0;CURRENTMODE=PAYLOAD      ;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==IMAGE         ){else_check=0;CURRENTMODE=IMAGE        ;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(COMMAND_RESULT2==EMERGENCY     ){else_check=0;CURRENTMODE=EMERGENCY    ;ack_response1();/*HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);*/}//ACK
                             if(else_check==1                  ){nack_response1();}//NACK
                             two_byte_respond();
                             reset_response_array();
    }//SM
    //GM
    if (COMMAND_RESULT1==GM   ){ my_full_response(ACK,CURRENTMODE       );two_byte_respond();reset_response_array(); }//ACK
    //GM
    //GSC
    if (COMMAND_RESULT1==GSC  ){ my_full_response(ACK,CURRENTSYSTEMCLOCK);two_byte_respond();reset_response_array(); }//ACK.........MIGHT have to do away with 2 byte response limitation OR i can just specify what each count(1) represents as a time period for a 1 byte maximum
    //SSC
    if (COMMAND_RESULT1==SSC  ){ my_full_response(ACK, 0  );CURRENTSYSTEMCLOCK=COMMAND_RESULT2;two_byte_respond();reset_response_array(); }//ACK
    //GSC
    //GOSTM
    if (COMMAND_RESULT1==GOSTM){
        ////my_full_response(ACK,   (int) ( ((int) (XB12V_I<<7)) | ((int) (ADCS12V_I<<6)) | ((int) (RS5V_I<<5)) | ((int) (RS3V3_I<<4)) | ((int) (SA1_I<<3)) | ((int) (SA2_I<<2)) | ((int) (SA3_I<<1)) |  1 )    );
        int a = (int) (XB12V_I  <<7); 
        int b = (int) (ADCS12V_I<<6);
        int c = (int) (RS5V_I   <<5);
        int d = (int) (RS3V3_I  <<4);
        int e = (int) (SA1_I    <<3);
        int f = (int) (SA2_I    <<2);
        int g = (int) (SA3_I    <<1);
        my_full_response(  ACK, (int) (a | b | c | d | e | f | g |  1)    );
        //two_byte_respond();
        //reset_response_array();
    }//ACK
    //GOSTM
    //KEN
    if (COMMAND_RESULT1==KEN  ){ my_full_response(ACK,KEN ); two_byte_respond();reset_response_array(); }//ACK ...........shutting down all activity received from GCS or OBC
    //KEN
    //KDIS
    if (COMMAND_RESULT1==KDIS ){ my_full_response(ACK,KDIS); two_byte_respond();reset_response_array(); }//ACK
    //KDIS
return 0;
}//execute /*8801001003133498*/


int reset_and_assign_command_result_integers(){
    COMMAND_RESULT1 = 0;//refresh
    COMMAND_RESULT2 = 0;//refresh
    captured_command();//extract command(command_result1) and the parameter(command_result2)
return 0;
}

	
//MAIN LOOP
while(1){//while
        int SKIP = 0;
        //HIGH
        if ( read_input() == HIGH ) {
                                    command_leftShift_insertEnd(1);//shift all command array items to left(MSB), lose the first MSB bit, insert new (LSB) bit at end
		                    //execute();
                                    //COMMAND_RESULT1=0;//refresh
                                    //COMMAND_RESULT2=0;//refresh
                                    //captured_command();//extract command(command_result1) and the parameter(command_result2)
                		    reset_and_assign_command_result_integers();                    
				    while(read_input()==HIGH){}//wait out the HIGH cycle
                                    SKIP = 1;//start loop afresh
        }//if
        //HIGH
        //LOW
        if( (SKIP==0) & (read_input()==LOW ) ){
                                              command_leftShift_insertEnd(0);//shift all command array items to left(MSB), lose the first MSB bit, insert new (LSB) bit at end
					      //execute();
                                              //COMMAND_RESULT1=0;//refresh
                                    	      //COMMAND_RESULT2=0;//refresh
                                    	      //captured_command();//extract command(command_result1) and the parameter(command_result2)
                		    	      reset_and_assign_command_result_integers();
                                              while(read_input()==LOW){}//wait out the HIGH cycle
                                              SKIP = 1;//start loop afresh
        }//if
        //LOW
        if( (SKIP==0) & (read_input()==PAUSE) ){
                                               execute();//are there any valid commands captured...if so set up the response
                                               while(read_input()==PAUSE){}//wait out the LOW cycle
        }//if
}//while  
//MAIN LOOP
   
return 0;
}//main
