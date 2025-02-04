//Prferrable to use preamble
//uint8_t, uint16_t, uint32_t or chars can be used to replace the int types- but int is universal and type size is not an issue
//rs485
//


int main(){//main

//Boolean
int HIGH   = 1;
int LOW    = 0;
int PAUSE  = 2;
//SYMBOLS
int PING      = 0;//command
int ACK       = 0;//response
int NACK      = 0;//response
int SON       = 0;//command
int PAYLOAD   = 0;//parameter
int UHF       = 0;//parameter
int ADCS      = 0;//parameter
int GPS       = 0;//parameter
int SOF       = 0;//command
int SM        = 0;//command
int GM        = 0;//command
int GSC       = 0;//command
int SSC       = 0;//command
int GFP       = 0;//command
int SFP       = 0;//command
int FON       = 0;//command
//int TWELVEBUS = 0;//telemetry parameter
//int FIVEBUS   = 0;//telemetry parameter
//int THREEBUS  = 0;//parameter
int FOF       = 0;//command
int GOSTM     = 0;//command
int KEN       = 0;//command
int KDIS      = 0;//command
int GD        = 0;//command
int PD        = 0;//command
int RD        = 0;//command
int WD        = 0;//command
int INITIALIZE    = 0;//mode parameter
int DETUMBLE      = 0;//mode parameter
int NORMAL        = 0;//mode parameter
int COMMUNICATION = 0;//mode parameter
int PAYLOAD       = 0;//mode parameter
int IMAGE         = 0;//mode parameter
int EMERGENCY     = 0;//mode parameter
int CUSTOM        = 0;//mode parameter
int PL5V_EN   = 0;//pin
int ADCS5V_EN = 0;//pin
int RS12V_EN  = 0;//pin
int XB12V_EN  = 0;//pin
int CCU5V_EN  = 0;//pin
int RS3V3_EN  = 0;//pin
int PL_EN     = 0;//pin
int ADCS_EN   = 0;//pin
int UHF_EN    = 0;//pin
int GPS_EN    = 0;//pin
int ADCS12V_EN= 0;//pin
int SA1_I = 0;//pin
int SA2_I = 0;//pin
int SA3_I = 0;//pin
// other variables
int RESPONSE_WAIT=10000;
int CURRENTMODE       =0;
int CURRENTSYSTEMCLOCK=0;
int COMMAND_RESULT1=0;
int COMMAND_RESULT2=0;
int COMMANDARRAY [16];
int RESPONSEARRAY[16];
 

/***   
//Array Initialisation    
for( int index=0; index++; index<=15 ){
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
    for( int i=0 ;i++; i<3){}//pause
    //capture (A2) A again;
    //A2 = HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_9);
    for( int i=0; i++; i<3){}//pause
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
    for( int count=0; count++; count<=RESPONSE_WAIT ){ }//do nothing
    //HAL delay could work too
return 0;
}//response_wait


//shift all to left, insert new bit at end
//command_leftShift_insertEnd
int command_leftShift_insertEnd(int insertionbit){
    for( int index=0; index++; index<=14 ){  COMMANDARRAY[index] = COMMANDARRAY[index+1];   }//for
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
    for( int index=0; index++; index<=15 ){  transmit_bit_response(  RESPONSEARRAY[index]  );  }//for
return 0;
}//two_byte_respond


//reset_command_array()
int reset_command_array(){
    for( int index=0; index++; index<=15 ){  COMMANDARRAY[index] = 0;  }//for
return 0;
}//reset_command_array()

   
//reset_response_array
int reset_response_array(){
    for( int index=0; index++; index<=15 ){  RESPONSEARRAY[index] = 0;  }//for
return 0;
}//reset_response_array


	
//ack_response1
int ack_response1(){
    for( int index=0; index++; index<=7 ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( ACK>>(7-index) ) ) & 1 );   
    }//for
return 0;
}//ack_response1


	
//nack_response1
int nack_response1(){
    for( int index=0; index++; index<=7 ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( NACK>>(7-index) ) ) & 1 );
    }//for
return 0;
}//nack_response1
   


//my_response2
int my_response2( int myvalue){
    for( int index=8; index++; index<=15 ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( myvalue>>(15-index) ) ) & 1 );
    }//for
return 0;
}//my_response2
   
   
//capture_command    
int captured_command(){
    COMMAND_RESULT1 = 0;
    for( int index=0; index++; index<=7 ){
    COMMAND_RESULT1 = COMMAND_RESULT1 + ( COMMANDARRAY[ index ] * ( (int)( 1<<(7-index) ) ) );
    }//for
    COMMAND_RESULT2 = 0;
    for( int index=8; index++; index<=15 ){
    COMMAND_RESULT2 = COMMAND_RESULT2 + ( COMMANDARRAY[ index ] * ( (int)(1<<(15-index) ) ) );
    }//for
return 0;
}//captured_command


//my_full_response
int my_full_response( int firstbyte, int secondbyte){
    for( int index=0; index++; index<=7 ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( firstbyte >>(7 -index) ) ) & 1 ); // & 1 eliminates all preceding bits  
    }//for
    for( int index=8; index++; index<=15){
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
