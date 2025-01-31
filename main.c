
int main(){//main

//Boolean
int HIGH      =1;
int LOW       =0;
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
int TWELVEBUS = 0;//telemetry parameter
int FIVEBUS   = 0;//telemetry parameter
int THREEBUS  = 0;//parameter
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

   
//Array Initialisation    
for(int index=0;index++;index<=15){
   int COMMANDARRAY [index]=0;
   int RESPONSEARRAY[index]=0;  
}//for
//Initialisation of variables


   
//clock
int clock(){
    int result=0;
    //capture A1;
    //A1 = HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_9);
    for(int i=0;i++;i<3){}//just want to make sure we have the right reading...so let's do an average
    //capture (A2) A again;
    //A2 = HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_9);
    for(int i=0;i++;i<3){}//just want to make sure we have the right reading...so let's do an average
    //capture (A3) A again;
    //A3 = HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_9);
    if(  (A1+A2+A3) >=2   ){result=1;}//if
return 0;
}//clock


//read_input
int read_input(){
    int result=0;
    //capture A1;
    for(int i=0;i++;i<3){}//just want to make sure we have the right reading...so let's do an average
    //capture (A2) A again;
    for(int i=0;i++;i<3){}//just want to make sure we have the right reading...so let's do an average
    //capture (A3) A again;
    if(  (A1+A2+A3) >=2   ){result=1;}//if
return result;
}//read_input
   

//response_wait
int response_wait(){
    for(int count=0;count++;count<=RESPONSE_WAIT){ }//do nothing
return 0;
}//response_wait


//shift all to left, insert new bit at end
//command_leftShift_insertEnd
int command_leftShift_insertEnd(){
    for( int index=0; index++; index<=14 ){  COMMANDARRAY[index] = COMMANDARRAY[index+1];   }//for
    COMMANDARRAY[15] = read_input();
return 0;  
}//command_leftShift_insertEnd


//read_input
int transmit_bit_response(int X){
    if(X==1){/*transmit ONE*/
            //HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);
            //HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);
    }//if
    if(X==0){/*transmit ZERO*/
            //HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);
            //HAL_GPIO_WritePin( LEDgn_GPIO_Port, LEDgn_Pin, GPIO_PIN_SET);
    }//if
    response_wait();
return 0;
}//read_input


//two_byte_respond
int two_byte_respond(){
    for( int index=0; index++; index<=15 ){  transmit_bit_response(  RESPONSEARRAY[index]  );  }//for
return 0;
}//two_byte_respond

       
//ack_response1
int ack_response1(){
    for( int index=0; index++; index<=7 ){
    RESPONSEARRAY[index] = (int) ( ( (int) ( ACK>>(7-index) ) ) & 1 );   
    }//for
return 0;
}//ack_response1


//nack_response1
int nack_response1(){
    for(int index=0;index++;index<=7){
    RESPONSEARRAY[index] = (int) ( ( (int) ( NACK>>(7-index) ) ) & 1 );
    }//for
return 0;
}//nack_response1
   


//my_response2
int my_response2( int myvalue){
    for(int index=8;index++;index<=15){
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
    RESPONSEARRAY[index] = (int) ( ( (int) ( firstbyte >>(7 -index) ) ) & 1 );   
    }//for
    for(int index=8;index++;index<=15){
    RESPONSEARRAY[index] = (int) ( ( (int) ( secondbyte>>(15-index) ) ) & 1 );
    }//for
return 0;
}//my_full_response

   
//execute
int execute(){
    //PING
    if( COMMAND_RESULT1==PING ){ack_response1();}//ACK...........Fault reporrting mechanisms?
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
    }//SM
    //GM
    if (COMMAND_RESULT1==GM   ){ my_full_response(ACK,CURRENTMODE       );                     }//ACK
    //GM
    //GSC
    if (COMMAND_RESULT1==GSC  ){ my_full_response(ACK,CURRENTSYSTEMCLOCK);                     }//ACK.........MIGHT have to do away with 2 byte response limitation OR i can just specify what each count(1) represents as a time period for a 1 byte maximum
    //SSC
    if (COMMAND_RESULT1==SSC  ){ my_full_response(ACK, 0  );CURRENTSYSTEMCLOCK=COMMAND_RESULT2;}//ACK
    //GSC
    //GOSTM
    if (COMMAND_RESULT1==GOSTM){ my_full_response(ACK,   (int) ( ((int) (XB12V_I<<7)) | ((int) (ADCS12V_I<<6)) | ((int) (RS5V_I<<5)) | ((int) (RS3V3_I<<4)) | ((int) (SA1_I<<3)) | ((int) (SA2_I<<2)) | ((int) (SA3_I<<1)) |  1)    );     }//ACK
    //GOSTM
    //KEN
    if (COMMAND_RESULT1==KEN  ){ my_full_response(ACK,KEN );                                   }//ACK ...........shutting down all activity received from GCS or OBC
    //KEN
    //KDIS
    if (COMMAND_RESULT1==KDIS ){ my_full_response(ACK,KDIS);                                   }//ACK
    //KDIS
return 0;
}//execute

   
//MAIN LOOP
while(1){//while
        int SKIP = 0;
        //HIGH
        if ( clock() == HIGH ) {//shift all to left, insert new bit at end
                               command_leftShift_insertEnd();
                               captured_command();//int
                               //execute();//int
                               //two_byte_respond();
                               while(clock()==HIGH){}
                               SKIP=1;
        }//if
        //HIGH
        //LOW
        if( (SKIP==0) & (clock()==LOW) ){
                                        execute();//int
                                        two_byte_respond();
                                        while(clock()==LOW){}
        }//if
        //LOW
}//while  
//MAIN LOOP
   
return 0;
}//main
