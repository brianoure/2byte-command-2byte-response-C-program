
int main(){//main


int HIGH      =1;
int LOW       =0;
int CLOCKREAD =0;
int CLOCKPAUSE=0;

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
int TWELVEBUS = 0;//parameter
int FIVEBUS   = 0;//parameter
int THREEBUS  = 0;//parameter
int FOF       = 0;//command
int GOSTM     = 0;//command
int KEN       = 0;//command
int KDIS      = 0;//command
int GD        = 0;//command
int PD        = 0;//command
int RD        = 0;//command
int WD        = 0;//command
int INITIALIZE    = 0;//parameter
int DETUMBLE      = 0;//parameter
int NORMAL        = 0;//parameter
int COMMUNICATION = 0;//parameter
int PAYLOAD       = 0;//parameter
int IMAGE         = 0;//parameter
int EMERGENCY = 0;//pin
int PL5V_EN   = 0;//pin
int ADCS5V_EN = 0;//pin
int RS12V_EN  = 0;//pin
int XB12V_EN  = 0;//pin
int CCU5V_EN  = 0;//pin
int CCU5V_EN  = 0;//pin
int RS3V3_EN  = 0;//pin
int PL_EN     = 0;//pin
int ADCS_EN   = 0;//pin
int UHF_EN    = 0;//pin
int GPS_EN    = 0;//pin
int ADCS12V_EN= 0;//pin


int CURRENTMODE       =0;
int CURRENTSYSTEMCLOCK=0;


int COMMAND_RESULT1=0;
int COMMAND_RESULT2=0;

int COMMAND_ARRAY_INDEX_COUNTER=0;

int RESPONSE_WAIT=10000;

int COMMANDARRAY [16];
int RESPONSEARRAY[16];

//Initialisation of variables    
for(int index=0;index++;index<=15){
   int COMMANDARRAY [index]=0;
   int RESPONSEARRAY[index]=0;  
}//for
//Initialisation of variables

//response_wait
int response_wait(){
for(int count=0;count++;count<=RESPONSE_WAIT){}
return 0;
}//response_wait


//shift all to left, insert new bit at end
//command_leftShift_insertEnd
int command_leftShift_insertEnd(){
    for(int index=0;index++;index<=14){
    COMMANDARRAY[index] = COMMANDARRAY[index+1];
    }//for
    COMMANDARRAY[15]=read_input();
return 0;  
}//command_leftShift_insertEnd

   
//clock
int clock(){
return 0;
}//clock


//read_input
int read_input(){
return 0;
}//read_input


//read_input
int transmit_bit_response(int X){
    if(X==1){/*transmit ONE*/}//if
    if(X==0){/*transmit ZERO*/}//if
    response_wait();
return 0;
}//read_input


//two_byte_respond
int two_byte_respond(){
    for(int index=0;index++;index<=15){
    transmit_bit_response(  RESPONSEARRAY[index]  );
    //response_wait();
    }//for
return 0;
}//two_byte_respond

       
//ack_response
int ack_response(){
    for(int index=0;index++;index<=7){
    RESPONSEARRAY[index] = (int) (  ((int)(ACK>>(7-index))) & 1    );
    }//for
return 0;
}//ack_response


//nack_response
int nack_response(){
    for(int index=0;index++;index<=7){
    RESPONSEARRAY[index] = (int) (  ((int)(NACK>>(7-index))) & 1    );
    }//for
return 0;
}//nack_response
   


//my_response
int my_response( int myvalue){
    for(int index=0;index++;index<=7){
    RESPONSEARRAY[index] = (int) (  ((int)(myvalue>>(7-index))) & 1    );
    }//for
return 0;
}//my_response
   
   
//capture_command    
int captured_command(){
    for(int i=0;i++;i<=7){
    COMMAND_RESULT1 = COMMAND_RESULT1 + ( COMMANDARRAY[ i ] * ((int)(1<<(7-i))) );
    }//for
    for(int i=8;i++;i<=15){
    COMMAND_RESULT2 = COMMAND_RESULT2 + ( COMMANDARRAY[ i ] * ((int)(1<<(15-i))) );
    }//for
return 0;
}//captured_command

  
//execute
int execute(){
    //PING
    if( (COMMAND_RESULT1==PING) & (COMMAND_RESULT1==PING)  ){response(ACK,0);}
    //SON
    if (COMMAND_RESULT1==SON){
                             int else_check=1;
                             if(COMMAND_RESULT2==PL5V_EN    ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==ADCS5V_EN  ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==RS12V_EN   ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==XB12V_EN   ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==RS3V3_EN   ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==PL_EN      ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==ADCS_EN    ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==UHF_EN     ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==GPS_EN     ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==ADCS12V_EN ){else_check=0;ack_response();/*action*/}//ACK
                             if(else_check==1               ){nack_response();}//NACK
    }//SON
    //SOF  
    if (COMMAND_RESULT1==SOF){
                             int else_check=1;
                             if(COMMAND_RESULT2==PL5V_EN    ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==ADCS5V_EN  ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==RS12V_EN   ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==XB12V_EN   ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==RS3V3_EN   ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==PL_EN      ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==ADCS_EN    ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==UHF_EN     ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==GPS_EN     ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==ADCS12V_EN ){else_check=0;ack_response();/*action*/}//ACK
                             if(else_check==1               ){nack_response();}//NACK
    }//SOF
    //SM
    if (COMMAND_RESULT1==SOF){
                             int else_check=1;
                             if(COMMAND_RESULT2==INITIALIZE    ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==DETUMBLE      ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==NORMAL        ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==COMMUNICATION ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==PAYLOAD       ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==IMAGE         ){else_check=0;ack_response();/*action*/}//ACK
                             if(COMMAND_RESULT2==EMERGENCY     ){else_check=0;ack_response();/*action*/}//ACK
                             if(else_check==1                  ){nack_response();}//NACK
    }//SM
    //GM
    if (COMMAND_RESULT1==GM  ){ack_response();  my_response(CURRENTMODE       );/*action*/}//ACK
    //GM
    //GSC
    if (COMMAND_RESULT1==GSC ){ack_response();  my_response(CURRENTSYSTEMCLOCK);/*action*/}//ACK
    //GSC
    if (COMMAND_RESULT1==SSC ){ack_response();  /*my_response(0)*/              /*action*/}//ACK
    //GSC
    //GOSTM
    if(COMMAND_RESULT1==GOSTM){ack_response();  int resp = (int)();my_response(   resp    );      /*action*/}//ACK
    //GOSTM
    //KEN
    if(COMMAND_RESULT1==KEN  ){ack_response();  /*my_response(0)*/             /*action*/}//ACK
    //KEN
    //KDIS
    if(COMMAND_RESULT1==KDIS ){ack_response();  /*my_response(0)*/             /*action*/}//ACK
    //KDIS
return 0;
}//execute

//MAIN LOOP
while(1){//while
        int SKIP = 0;
        //HIGH
        if (clock() == HIGH) {
                             //shift all to left, insert new bit at end
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
                                        two_byte_respond(,);
                                        while(clock()==LOW){}
        }//if
        //LOW
}//while  
//MAIN LOOP
   
return 0;
}//main
