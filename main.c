int main(){//main

int CLOCKPAUSE=0;
int CLOCKREAD =0;

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

int read_command_input(){
//if clock high, wait till clock off
return 0;
}//read_command_input

int response(int VALUE1, int VALUE2){
//if clock off, wait till clock off
return 0;
}//response















while(1){//while
int current_command = read_command_input();
  
if(current_command==PING  ){response(ACK,0);}

//if(current_command==GD  ){response(ACK,0);}

//if(current_command==PD  ){response(ACK,0);}

//if(current_command==RD  ){response(ACK,0);}

//if(current_command==WD  ){response(ACK,0);}
  
//SON
if(current_command==SON_PL5V_EN    ){response(ACK ,0);}
if(current_command==SON_ADCS5V_EN  ){response(ACK ,0);}
if(current_command==SON_RS12V_EN   ){response(ACK ,0);}
if(current_command==SON_XB12V_EN   ){response(ACK ,0);}
if(current_command==SON_CCU5V_EN   ){response(ACK ,0);}
if(current_command==SON_RS3V3_EN   ){response(ACK ,0);}
if(current_command==SON_PL_EN      ){response(ACK ,0);}
if(current_command==SON_ADCS_EN    ){response(ACK ,0);}
if(current_command==SON_UHF_EN     ){response(ACK ,0);}
if(current_command==SON_GPS_EN     ){response(ACK ,0);}
if(current_command==SON_ADCS12V_EN ){response(ACK ,0);}
if(current_command==SON_else       ){response(NACK,0);}
//SON

//SOF  
if(current_command==SOF_PL5V_EN    ){response(ACK ,0);}
if(current_command==SOF_ADCS5V_EN  ){response(ACK ,0);}
if(current_command==SOF_RS12V_EN   ){response(ACK ,0);}
if(current_command==SOF_XB12V_EN   ){response(ACK ,0);}
if(current_command==SOF_CCU5V_EN   ){response(ACK ,0);}
if(current_command==SOF_RS3V3_EN   ){response(ACK ,0);}
if(current_command==SOF_PL_EN      ){response(ACK ,0);}
if(current_command==SOF_ADCS_EN    ){response(ACK ,0);}
if(current_command==SOF_UHF_EN     ){response(ACK ,0);}
if(current_command==SOF_GPS_EN     ){response(ACK ,0);}
if(current_command==SOF_ADCS12V_EN ){response(ACK ,0);}
if(current_command==SOF_else       ){response(NACK,0);}
//SOF

//SM
if(current_command==SM_INITIALIZE     ){response(ACK,0);}
if(current_command==SM_DETUMBLE       ){response(ACK,0);}
if(current_command==SM_NORMAL         ){response(ACK,0);}
if(current_command==SM_COMMUNICATION  ){response(ACK,0);}
if(current_command==SM_PAYLOAD        ){response(ACK,0);}
if(current_command==SM_IMAGE          ){response(ACK,0);}
if(current_command==SM_EMERGENCY      ){response(ACK,0);}
//SM


if(current_command==GM   ){response(ACK,CURRENTMODE       );}
if(current_command==GSC  ){response(ACK,CURRENTSYSTEMCLOCK);}
if(current_command==SSC_  ){response(ACK,0);}


//if(current_command==GFP  ){response(ACK,0);}

  
//if(current_command==SFP  ){response(ACK,0);}

  
//if(current_command==FON  ){response(ACK,0);}

  
//if(current_command==FOF  ){response(ACK,0);}


if(current_command==GOSTM){response(ACK,0);}
if(current_command==KEN  ){response(ACK,0);}
if(current_command==KDIS ){response(ACK,0);}

}//while

  
return 0;
}//main
