
int main(){//main

int CLOCKREAD=0;
int CLOCKPAUSE=0;
int clock(){}

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

int COMMANDARRAY[16];
int RESPONSEARRAY[16];

int command_result1=0;
int command_result2=0;


int COMMAND_ARRAY_INDEX_COUNTER=0;



int captured_command(){
    for(int i=0;i++;i<=7){
    command_result1 = command_result1 + ( COMMANDARRAY[ i ] * ((int)(1<<(7-i))) );
    }//for
    for(int i=8;i++;i<=15){
    command_result2 = command_result2 + ( COMMANDARRAY[ i ] * ((int)(1<<(15-i))) );
    }//for
return 0;
}//captured_command

  
//execute
int execute(){
    //PING
    if( (command_result1==PING) & (command_result1==PING)  ){response(ACK,0);}
    //SON
    if (command_result1==SON){
                             int else_check=1;
                             if(command_result2==PL5V_EN    ){else_check=0;}//ACK
                             if(command_result2==ADCS5V_EN  ){else_check=0;}//ACK
                             if(command_result2==RS12V_EN   ){else_check=0;}//ACK
                             if(command_result2==XB12V_EN   ){else_check=0;}//ACK
                             if(command_result2==RS3V3_EN   ){else_check=0;}//ACK
                             if(command_result2==PL_EN      ){else_check=0;}//ACK
                             if(command_result2==ADCS_EN    ){else_check=0;}//ACK
                             if(command_result2==UHF_EN     ){else_check=0;}//ACK
                             if(command_result2==GPS_EN     ){else_check=0;}//ACK
                             if(command_result2==ADCS12V_EN ){else_check=0;}//ACK
                             if(else_check==1               ){}//NACK
    }//son
    //SOF  
    if (command_result1==SOF){
                             int else_check=1;
                             if(command_result2==PL5V_EN    ){else_check=0;}//ACK
                             if(command_result2==ADCS5V_EN  ){else_check=0;}//ACK
                             if(command_result2==RS12V_EN   ){else_check=0;}//ACK
                             if(command_result2==XB12V_EN   ){else_check=0;}//ACK
                             if(command_result2==RS3V3_EN   ){else_check=0;}//ACK
                             if(command_result2==PL_EN      ){else_check=0;}//ACK
                             if(command_result2==ADCS_EN    ){else_check=0;}//ACK
                             if(command_result2==UHF_EN     ){else_check=0;}//ACK
                             if(command_result2==GPS_EN     ){else_check=0;}//ACK
                             if(command_result2==ADCS12V_EN ){else_check=0;}//ACK
                             if(else_check==1               ){}//NACK
    }//son
    //SOF
    //SM
    if (command_result1==SOF){
                             int else_check=1;
                             if(command_result2==INITIALIZE    ){else_check=0;}//ACK
                             if(command_result2==DETUMBLE      ){else_check=0;}//ACK
                             if(command_result2==NORMAL        ){else_check=0;}//ACK
                             if(command_result2==COMMUNICATION ){else_check=0;}//ACK
                             if(command_result2==PAYLOAD       ){else_check=0;}//ACK
                             if(command_result2==IMAGE         ){else_check=0;}//ACK
                             if(command_result2==EMERGENCY     ){else_check=0;}//ACK
                             if(else_check==1                  ){}//NACK
    }//SM
    //GM
    if (command_result1==GM ){response(ACK,CURRENTMODE       );}//ACK
    //GM
    //GSC
    if (command_result1==GSC){response(ACK,CURRENTSYSTEMCLOCK);}//ACK
    //GSC
    if (command_result1==SSC){response(ACK,0);}//ACK
    //GSC
    //GOSTM
    if(command_result1==GOSTM){response(ACK,0);}//ACK
    //GOSTM
    //KEN
    if(command_result1==KEN  ){response(ACK,0);}//ACK
    //KEN
    //KDIS
    if(command_result1==KDIS ){response(ACK,0);}//ACK
    //KDIS
return 0;
}//execute


while(1){//while
        SKIP = 1;
        if( CLOCK_COUNTER == 31 ){ CLOCK_COUNTER = 0; }
        if( COMMAND_ARRAY_INDEX_COUNTER == 15 ){ COMMAND_ARRAY_INDEX_COUNTER = 0; }
        //HIGH
        if( (OBC_CLOCK == HIGH) & (CLOCK_COUNTER >= 0) & (CLOCK_COUNTER <= 15) ){
                     COMMANDARRAY[ CLOCK_COUNTER ] = read_input();
                     captured_command();//void
                     execute();//int
        while(OBC_CLOCK==HIGH){}
        }
        //HIGH
        //LOW
        if( (SKIP!=1) & (OBC_CLOCK==LOW) & (CLOCK_COUNTER>=16) & (CLOCK_COUNTER<=31) ){
        while(OBC_CLOCK==LOW){}
        }
        //LOW
        CLOCK_COUNTER = CLOCK_COUNTER + 1;
        COMMAND_ARRAY_INDEX_COUNTER = COMMAND_ARRAY_INDEX_COUNTER + 1;

}//main while loop  

return 0;
}//main
