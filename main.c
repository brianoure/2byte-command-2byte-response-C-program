int main(){//main


//BOARD or SYSTEM transfer
int PING = 0; //command
int ACK = 0; 
int NACK= 0;
int SON= 0; //command
int P= 0;
int UH= 0;
int AD= 0;
int GP= 0;
int SOF= 0; //command
int SM= 0;//command
int GM= 0;//command
int GSC= 0;//command
int SSC= 0;//command
int GFP= 0;//command
int SFP= 0;//command
int FON= 0;//command
int TWELVEBUS= 0;
int FIVEBUS= 0;
int THREEBUS= 0;
int FOF= 0;//command
int GOSTM= 0;//command
int KEN= 0;//command
int KDIS= 0;//command
int GD= 0;//command
int PD= 0;//command
int RD= 0;//command
int WD= 0;//command
int INITMODE= 0;
int DETMODE= 0;
int NORMODE= 0;
int COMMODE= 0;
int PLDMODE= 0;
int IMGMODE= 0;
int EMMODE= 0;
int PL5V_EN= 0;
int ADCS5V_EN= 0;
int RS12V_EN= 0;
int XB12V_EN= 0;
int CCU5V_EN= 0;
int CCU5V_EN= 0;
int RS3V3_EN= 0;
int PL_EN= 0;
int ADCS_EN= 0;
int UHF_EN= 0;
int GPS_EN= 0;
int ADCS12V_EN= 0;

int read_command_input(){return 0;}

while(1){//while
int current_command = read_command_input();
if(current_command==PING){}
if(current_command==SON){}
if(current_command==SOF){}
if(current_command==SM){}
if(current_command==GM){}
if(current_command==GSC){}
if(current_command==SSC){}
if(current_command==GFP){}
if(current_command==SFP){}
if(current_command==FON){}
if(current_command==FOF){}
if(current_command==GOSTM){}
if(current_command==KEN){}
if(current_command==KDIS){}
if(current_command==GD){}
if(current_command==PD){}
if(current_command==RD){}
if(current_command==WD){} 
}//while

//BOARD or SYSTEM transfer

  
return 0;
}//main
