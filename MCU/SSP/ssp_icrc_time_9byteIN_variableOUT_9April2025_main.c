//simple serial protocol, 9byte command in, variable response out 
//As it stands for a single while loop cycle, tx 1 bit spi1, re
//Prferrable to use preamble
//uint8_t, uint16_t, uint32_t or chars can be used to replace the int types- but int is universal and type size is not an issue
//rs485 data when A and !A
//i2c data when clock high
//Dude, be cautious with your variables - public or global... _I are functions that read from input pins, _EN are raw integers(commands targeting output pins)
//Whoa! the EPS microntroller is actually  sampling the inputs in every while loop instance, so we have to check for changes in input states to determine if we have a 1 or a 0 

//SSP input bit frame :   1    ,   1               , 8  , 8     ,  1
//                      start  ,  address=number2 , cmd , param ,  end
                        flag, dest, src, cmd/resp , len, data, crc0, crc1, flag

//SSP output bit frame :   1    ,   1          , 8        , 8*16     ,  1
//                      start  ,  address=dest , ack/nack ,          ,  end

//SSP output bit frame :   1    ,   1          , 8  , 8     ,  1
//                      start  ,  address=dest , cmd , param ,  end




int main(){//main
struct ninebyte   { int byte1; int byte2; int byte3; int byte4; int byte5; int byte6; int byte7; int byte8; int byte9; };
struct fourbyte   { int byte1; int byte2; int byte3; int byte4; };
struct twobyte    { int byte1; int byte2; };
// add const def	
//############ DECLARATIONS ###########
const int EPS_MCU_ADDRESS=2;
//Boolean
const int HIGH    = 1   ;  
const int TRUE    = HIGH;
const int ONE     = HIGH;
const int LOW     = 0   ;  
const int FALSE   = LOW ;
const int ZERO    = LOW ;
const int PAUSE   = 2   ;
const int END     = 3   ;
//TRANSMISSION AND RECEPTION (COMMUNICATION) SYMBOLS
const int EMPTY           = 0   ;
const int ACK             = 47  ;   
const int PING            = 34  ; //command
const int ACKNOWLEDGE     = ACK ;
const int NACK            = 52  ;
const int NOT_ACKNOWLEDGE = NACK;
const int SON             = 140 ;
const int SWITCH_ON       = SON ;
const int UHF             = 24  ; //parameter
const int ADCS            = 162 ; //parameter
const int GPS             = 75  ; //parameter
const int SOF             = 218 ;
const int SWITCH_OFF      = SOF ; //command
const int SM              = 107 ;
const int SET_MODE        = SM  ; //command
const int GM              = 122 ;
const int GET_MODE        = GM  ; //command
const int GSC             = 94  ;
const int GET_SYSTEM_CLOCK= GSC ; //command
const int SSC             = 209 ; 
const int SET_SYSTEM_CLOCK= SSC ; //command
const int GFP             = 134 ; //command
const int SFP             = 90  ; //command
const int FON             = 55  ; 
const int FUNCTION_ON     = FON ; //command
const int TWELVEBUS       = 100 ; //telemetry parameter
const int FIVEBUS         = 150 ; //telemetry parameter
const int THREEBUS        = 200 ; //parameter
const int FOF             = 233 ; 
const int FUNCTION_OFF    = FOF ; //command
const int GOSTM           = 157 ;
const int GET_ONLINE_SYSTEM_TELEMETRY = GOSTM; //command
const int KEN             = 255 ;
const int KILL_ENABLE     = KEN ; //command
const int KDIS            = 227 ;
const int KILL_DISABLE    = KDIS; //command
const int GD              = 15  ;
const int GET_DATA        = GD  ; //command
const int PD              = 245 ;
const int PUT_DATA        = PD  ; //command
const int RD              = 222 ; 
const int READ_DATA       = RD  ; //command
const int WD              = 133 ; 
const int WRITE_DATA      = WD  ; //command
const int INITIALIZE      = 60  ; //mode parameter
const int DETUMBLE        = 71  ; //mode parameter
const int NORMAL          = 82  ; //mode parameter
const int COMMUNICATION   = 93  ; //mode parameter
const int PAYLOAD         = 104 ; //mode parameter
const int IMAGE           = 115 ; //mode parameter
const int EMERGENCY       = 126 ; //mode parameter
const int CUSTOM          = 69  ; //mode parameter
const int PL5V_EN         = 230 ; 
const int PAYLOAD_5V_ENABLE = PL5V_EN  ; //pin
const int ADCS5V_EN         = 143      ;
const int ADCS_5V_ENABLE    = ADCS5V_EN; //pin
const int RS12V_EN          = 205      ;
const int RESERVED_12V_EN   = RS12V_EN ; //pin
const int XB12V_EN          = 139      ;
const int XBAND_12V_ENABLE  = XB12V_EN ; //pin
const int CCU5V_EN          = 155      ; 
const int CENTRAL_COMMAND_UNIT_5V_ENABLE = CCU5V_EN; //pin
const int RS3V3_EN          = 212      ;
const int RESERVED_3V_ENABLE= RS3V3_EN ; //pin
const int PL_EN             = 172      ;
const int PAYLOAD_ENABLE    = PL_EN    ; //pin
const int ADCS_EN           = 144      ;
const int ADCS_ENABLE       = ADCS_EN  ; //pin
const int UHF_EN            = 189      ;
const int UHF_ENABLE        = UHF_EN   ; //pin
const int GPS_EN            = 57       ;
const int GPS_ENABLE        = GPS_EN   ; //pin
const int ADCS12V_EN        = 199      ; 
const int ADCS_12V_ENABLE   = ADCS12V_EN; //pin
const int EPS_EN            = 97        ; 
const int EPS_ENABLE        = EPS_EN    ;//funny

//############## PINS ##################

int  SA1_I      ()          {return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_0         );} //current reading from SA1  .............................................. PA0
int  SA2_I      ()          {return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_1         );} //current reading from SA2  .............................................. PA1
int  SA3_I      ()          {return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_2         );} //current reading from SA3  .............................................. PA2
int  RS4851_RX  ()          {return HAL_GPIO_ReadPin ( GPIOD, GPIO_PIN_6         );} //                          .............................................. PD6              //receiving (convolution amigo)
void RS4851_DE  (int value) {       HAL_GPIO_WritePin( GPIOD, GPIO_PIN_4 , value );} //                          .............................................. PD4              //sending if high, receiving if low
void RS4851_TX  (int value) {       HAL_GPIO_WritePin( GPIOD, GPIO_PIN_5 , value );} //                          .............................................. PD5              //sending
int  RS4852_RX  ()          {return HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_11        );} //                          .............................................. PB11             //receiving (convolution amigo)
void RS4852_DE  (int value) {       HAL_GPIO_WritePin( GPIOD, GPIO_PIN_12, value );} //                          .............................................. PD12             //sending if high, receiving if low
void RS4852_TX  (int value) {       HAL_GPIO_WritePin( GPIOB, GPIO_PIN_10, value );} //                          .............................................. PB10             //sending 
int  SPI1_SS    ()          {return HAL_GPIO_ReadPin ( GPIOE, GPIO_PIN_12        );} //                          .............................................. PE12
int  SPI1_SCK   ()          {return HAL_GPIO_ReadPin ( GPIOE, GPIO_PIN_13        );} //                          .............................................. PE13
void SPI1_MISO  (int value) {       HAL_GPIO_WritePin( GPIOE, GPIO_PIN_14, value );} //                          .............................................. PE14
int  SPI1_MOSI  ()          {return HAL_GPIO_ReadPin ( GPIOE, GPIO_PIN_15        );} //                          .............................................. PE15
int  SPI3_SS    ()          {return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_15        );} //                          .............................................. PA15
void SPI3_SCK   ()          {return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_10        );} //                          .............................................. PC10
void SPI3_MISO  (int value) {       HAL_GPIO_WritePin( GPIOC, GPIO_PIN_11, value );} //                          .............................................. PC11
int  SPI3_MOSI  ()          {return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_12        );} //                          .............................................. PC12
int  I2C2_SCL   ()          {                                             return 0;} // ccu/obc master, unidirectional  ....................................... PB13
int  I2C2_SDA   ()          {                                             return 0;} // ccu/obc master, unidirectional  ....................................... PB14
int  SYNC_PULSE ()          {return HAL_GPIO_ReadPin ( GPIOD, GPIO_PIN_12        );} // clock drain                     ....................................... PD1
int  OBC_FAULT  ()          {return HAL_GPIO_ReadPin ( GPIOD, GPIO_PIN_2         );} //if read LOW then fault, else no fault    ............................... PD2
int  CCU_FAULT  ()          {return HAL_GPIO_ReadPin ( GPIOD, GPIO_PIN_9         );} //if read LOW then fault, else no fault    ............................... PD9
int  OBC_I      ()          {return HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_1         );} //     ....................................................................PB1
int  CCU_I      ()          {return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_5         );} //     ....................................................................PA5
int  ADCS_I     ()          {return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_7         );} //     ....................................................................PA7
int  ADCS_FAULT ()          {return HAL_GPIO_ReadPin ( GPIOD, GPIO_PIN_0         );} //if read LOW then fault, else no fault                ....................PD0
void ADCS_EN    (int value) {       HAL_GPIO_WritePin( GPIOA, GPIO_PIN_12, value );} //if write HIGH then enable, if write LOW then disable ....................PA12
int  UHF_I      ()          {return HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_0         );} //                                               ..........................PB0
int  UHF_FLT    ()          {return HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_4         );} //if read LOW then fault, else no fault              ......................PB4
void UHF_EN     (int value) {       HAL_GPIO_WritePin( GPIOD, GPIO_PIN_7 , value );} //        .................................................................PD7
int  PL_I       ()          {return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_4         );} //        .................................................................PC4
int  PL_FLT     ()          {return HAL_GPIO_ReadPin ( GPIOD, GPIO_PIN_14        );} //if read LOW then fault, else no fault  ..................................PD14
void PL_EN      (int value) {       HAL_GPIO_WritePin( GPIOD, GPIO_PIN_13, value );} //                                       ..................................PD13
int  RS3V3_I    ()          {return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_6         );} //                                       ..................................PA6
int  RS3V3_FLT  ()          {return HAL_GPIO_ReadPin ( GPIOD, GPIO_PIN_8         );} //if read LOW then fault, else no fault  ..................................PD8
void RS3V3_EN   (int value) {       HAL_GPIO_WritePin( GPIOB, GPIO_PIN_15        );} //if write HIGH then enable, if write LOW then disable     ................PB15
int  GPS_I      ()          {return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_3         );} //                                                 ........................PC3
int  GPS_FLT    ()          {return HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_5         );} //if read LOW then fault, else no fault                       .............PB5
void GPS_EN     (int value) {       HAL_GPIO_WritePin( GPIOB, GPIO_PIN_6,  value );} //if write HIGH then enable, if write LOW then disable        .............PB6
int  ADCS5V_I   ()          {return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_2         );} //                                                        .................PC2
int  ADCS5V_FLT ()          {return HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_9         );} //if read LOW then fault, else no fault                     ...............PB9
void ADCS5V_EN  (int value) {       HAL_GPIO_WritePin( GPIOE, GPIO_PIN_4,  value );} //if write HIGH then enable, if write LOW then disable      ...............PE4
int  PL5V_I     ()          {return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_1         );} //                                                     ....................PC1
int  PL5V_FLT   ()          {return HAL_GPIO_ReadPin ( GPIOE, GPIO_PIN_0         );} //if read LOW then fault, else no fault                       .............PE0
void PL5V_EN    (int value) {       HAL_GPIO_WritePin( GPIOE, GPIO_PIN_3,  value );} //if write HIGH then enable, if write LOW then disable        .............PE3
int  CCU5V_I    ()          {return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_4         );} //                                                   ......................PA4
int  CCU5V_FLT  ()          {return HAL_GPIO_ReadPin ( GPIOE, GPIO_PIN_11        );} //if read LOW then fault, else no fault         ...........................PE11
void CCU5V_EN   (int value) {       HAL_GPIO_WritePin( GPIOE, GPIO_PIN_10, value );} //if write HIGH then enable, if write LOW then disable                 ....PE10
int  XB12V_I    ()          {return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_3         );} //                                      ...................................PA3
int  XB12V_FLT  ()          {return HAL_GPIO_ReadPin ( GPIOE, GPIO_PIN_9         );} //if read LOW then fault, else no fault               .....................PE9
void XB12V_EN   (int value) {       HAL_GPIO_WritePin( GPIOE, GPIO_PIN_8,  value );} //if write HIGH then enable, if write LOW then disable          ...........PE8
int  ADCS12V_FLT()          {return HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_7         );} //if read LOW then fault, else no fault                      ..............PB7
int  ADCS12V_I  ()          {return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_5         );} //                                                  .......................PC5
void ADCS12V_EN (int value) {       HAL_GPIO_WritePin( GPIOB, GPIO_PIN_8,  value );} //if write HIGH then enable, if write LOW then disable           ..........PB8
int  RS12V_FLT  ()          {return HAL_GPIO_ReadPin ( GPIOE, GPIO_PIN_7         );} //if read LOW then fault, else no fault                    ................PE7
void RS12V_EN   (int value) {       HAL_GPIO_WritePin( GPIOB, GPIO_PIN_2,  value );} //if write HIGH then enable, if write LOW then disable          ...........PB2
int  RS5V_FLT   ()          {return HAL_GPIO_ReadPin ( GPIOE, GPIO_PIN_1         );} //if read LOW then fault, else no fault               .....................PE1
int  RS5V_I     ()          {return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_0         );} //                                           ..............................PC0
void RS5V_EN    (int value) {       HAL_GPIO_WritePin( GPIOE, GPIO_PIN_2 , value );} //if write HIGH then enable, if write LOW then disable       ..............PE2
// other variables
int RESPONSE_WAIT            = 10000;//response_wait()
int CURRENTMODE              = 0;
int CURRENTSYSTEMCLOCK       = 0;
int FF                       = 255;
int OBC_ADDRESS              = 1  ;
int CCU_ADDRESS              = 3  ;
int EPS_ADDRESS              = 2  ;

	
//#######################

//response_wait
int response_wait(){
    for( int count=0;  count<=RESPONSE_WAIT ;count++ ){ }//do nothing
    //HAL delay could work too
return 0;
}//response_wait

//########################

struct twobyte crc16_generator_for_3byte(int a, int b, int c){
       struct twobyte {int byte1; int byte2;} rslt;
       int bits[40];
       for(int i=0 ; i<=7  ;  i++){bits[i]=((a>>(7 -i))&1);}
       for(int i=8 ; i<=15 ;  i++){bits[i]=((b>>(15-i))&1);}
       for(int i=16; i<=23 ;  i++){bits[i]=((c>>(23-i))&1);}//24 original
       for(int i=24; i<=39 ;  i++){bits[i]=          0    ;}//16 padding
       int poly[17]={1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1};//msb(left) to lsb(right)
       //for(int b=0;b<=16;b++){bits[b  ]=(bits[b+0]^poly[b  ]);}
       //for(int b=1;b<=17;b++){bits[b+1]=(bits[b+1]^poly[b-1]);}.........
       for(int b=0;b<=23;b++){
	  int one_is_present=0; int n=0;
	  while( (n<=23)&(one_is_present==0) ){ if( bits[n]==1 ){one_is_present=1;} n=n+1; }
	  if (one_is_present){    for(int x=b;x<=(b+16);x++){bits[x+b]=(bits[x+b]^poly[x-b]);}    }
       }//for
       rslt.byte1 = (bits[24]*128)+(bits[25]*64)+(bits[26]*32)+(bits[27]*16)+(bits[28]*8)+(bits[29]*4)+(bits[30]*2)+(bits[31] );
       rslt.byte2 = (bits[32]*128)+(bits[33]*64)+(bits[34]*32)+(bits[35]*16)+(bits[36]*8)+(bits[37]*4)+(bits[38]*2)+(bits[39] );
return rslt;
}//crc_generator_for_3byte

//########################

struct twobyte crc16_generator(int a, int b, int c, int d, int e){
       struct twobyte {int byte1; int byte2;} rslt;
       int bits[56];
       for(int i=0 ; i<=7  ;  i++){bits[i]=((a>>(7 -i))&1);}
       for(int i=8 ; i<=15 ;  i++){bits[i]=((b>>(15-i))&1);}
       for(int i=16; i<=23 ;  i++){bits[i]=((c>>(23-i))&1);}
       for(int i=24; i<=31 ;  i++){bits[i]=((d>>(31-i))&1);}
       for(int i=32; i<=39 ;  i++){bits[i]=((e>>(39-i))&1);}//24 original
       for(int i=40; i<=55 ;  i++){bits[i]=          0    ;}//16 padding
       int poly[17]={1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1};//msb(left) to lsb(right)
       for(int b=0;b<=39;b++){
	  int one_is_present=0; int n=0;
	  while( (n<=39)&(one_is_present==0) ){ if( bits[n]==1 ){one_is_present=1;} n=n+1; }
	  if (one_is_present){    for(int x=b;x<=(b+16);x++){bits[x+b]=(bits[x+b]^poly[x-b]);}    }
       }//for
       rslt.byte1 = (crc[0]*128)+(crc[1]*64)+(crc[2 ]*32)+(crc[3 ]*16)+(crc[4 ]*8)+(crc[5 ]*4)+(crc[6 ]*2)+(crc[7 ] );
       rslt.byte2 = (crc[8]*128)+(crc[9]*64)+(crc[10]*32)+(crc[11]*16)+(crc[12]*8)+(crc[13]*4)+(crc[14]*2)+(crc[15] );
return rslt;
}//crc_generator_for_5byte
	
//################# RS485 METHODS/DECLARATIONS ###################

struct eleven COMMAND_PARAMETER_RS485  = {0,0,0,0,0,0,0,0,0};// a fusion of 4851 and 4852 because we can't identify pauses
  
int receive_rs485 (){
int result=0; int r4851=0; int r4852=0;
RS4851_DE(0); RS4852_DE(0);
if((RS4851_RX()+RS4851_RX()+RS4851_RX())>=2 ){r4851=1;}
if((RS4852_RX()+RS4852_RX()+RS4852_RX())>=2 ){r4852=1;}
if ( !r4851 & !r4852 ){result=0;}//0
if ( !r4851 &  r4852 ){result=2;}//2
if (  r4851 & !r4852 ){result=3;}//3
if (  r4851 &  r4852 ){result=1;}//1
return result;
}//

//####################################
	
//get_command_parameter_after_leftShift_insertEnd_rs485
struct ninebyte get_command_parameter_after_leftShift_insertEnd_rs485(int insertionbit){ //flag, dest, src, cmd/response , len, data, crc0, crc1, flag
       COMMAND_PARAMETER_RS485.byte1 = ( (COMMAND_PARAMETER_RS485.byte1<<1) | (COMMAND_PARAMETER_RS485.byte2>>7) ) & 255;//flag
       COMMAND_PARAMETER_RS485.byte2 = ( (COMMAND_PARAMETER_RS485.byte2<<1) | (COMMAND_PARAMETER_RS485.byte3>>7) ) & 255;//dest
       COMMAND_PARAMETER_RS485.byte3 = ( (COMMAND_PARAMETER_RS485.byte3<<1) | (COMMAND_PARAMETER_RS485.byte4>>7) ) & 255;//src
       COMMAND_PARAMETER_RS485.byte4 = ( (COMMAND_PARAMETER_RS485.byte4<<1) | (COMMAND_PARAMETER_RS485.byte5>>7) ) & 255;//cmd/response
       COMMAND_PARAMETER_RS485.byte5 = ( (COMMAND_PARAMETER_RS485.byte5<<1) | (COMMAND_PARAMETER_RS485.byte6>>7) ) & 255;//len
       COMMAND_PARAMETER_RS485.byte6 = ( (COMMAND_PARAMETER_RS485.byte6<<1) | (COMMAND_PARAMETER_RS485.byte7>>7) ) & 255;//data
       COMMAND_PARAMETER_RS485.byte7 = ( (COMMAND_PARAMETER_RS485.byte7<<1) | (COMMAND_PARAMETER_RS485.byte8>>7) ) & 255;//crc1
       COMMAND_PARAMETER_RS485.byte8 = ( (COMMAND_PARAMETER_RS485.byte8<<1) | (COMMAND_PARAMETER_RS485.byte9>>7) ) & 255;//crc0
       COMMAND_PARAMETER_RS485.byte9 = ( (COMMAND_PARAMETER_RS485.byte9<<1) | insertionbit                       ) & 255;//flag
return COMMAND_PARAMETER_RS485;
}//get_command_parameter_after_leftShift_insertEnd_rs485

//###################################

//execute
int execute_rs485(struct ninebyte input ){ //flag, dest, src, cmd/response , len, data, crc0, crc1, flag
    int source      =input.byte3;
    int destination =input.byte2;
    int from_obc_or_from_ccu_to_eps = (int)(  ((source==OBC_ADDRESS)|(source==CCU_ADDRESS)) & (destination==EPS_ADDRESS)  );
    int proper_ssp_frame  = 1;//set to 1 is easier
    int proceed_execution = 0; if( from_obc_or_from_ccu_to_eps & proper_ssp_frame ){proceed_execution=1;}//who can talk to the EPS MCU
    if(proceed_execution){
                         int command  = input.byte4; int parameter= input.byte6;
                         int crc_validator_rs485 (){return 0;}
                         void pause_rs485(int x){}//mada mada
                         void send_bit_rs485  (int bit){
                              if(bit){ RS4851_TX(1); RS4852_TX(1); } else { RS4851_TX(0); RS4852_TX(0); }
                              RS4851_DE(1);RS4852_DE(1);
                              pause_rs485(1000);
                              RS4851_TX(0);RS4852_TX(1);
                              pause_rs485(1000);
	                      RS4851_DE(0);RS4852_DE(0);
                         }//send_bit_rs485
                         void send_byte_rs485( int out ){
                              for( int index= 0; index<= 7; index++ ){  send_bit_rs485( (int) ( ( (int) ( out >>(7 -index) ) ) & 1 ) ); }//for
                         }//send_byte_rs485
                         int  write_ssp_response_rs485( int dest, int src, int resp, int len, int d1, int d2, int d3, int d4, int d5, int d6, int d7, int d8, int d9, int d10, int d11, int d12, int d13, int d14, int d15, int d16, int d17){ //flag, dest, src, cmd/response , len, data, crc0, crc1, flag
			      struct twobyte crc16 = crc16_generator(dest,src,resp,len,data);
	                      if(len==0 ){send_byte_rs485( FF );send_byte_rs485( dest );send_byte_rs485( src );send_byte_rs485( resp );send_byte_rs485( len );                                                                                   send_byte_rs485( FF  );}//len 0
	                      if(len==1 ){send_byte_rs485( FF );send_byte_rs485( dest );send_byte_rs485( src );send_byte_rs485( resp );send_byte_rs485( len );send_byte_rs485( d1  );send_byte_rs485( crc16.byte1);send_byte_rs485( crc16.byte2);send_byte_rs485( FF  );}//len 1
	                      if(len==17){send_byte_rs485( FF );send_byte_rs485( dest );send_byte_rs485( src );send_byte_rs485( resp );send_byte_rs485( len ); 
		                          send_byte_rs485( d1 );send_byte_rs485( d2   );send_byte_rs485( d3  );send_byte_rs485( d4   );send_byte_rs485( d5  );send_byte_rs485( d6  );send_byte_rs485( d7  );send_byte_rs485( d8  );
		                          send_byte_rs485( d9 );send_byte_rs485( d10  );send_byte_rs485( d11 );send_byte_rs485( d12  );send_byte_rs485( d13 );send_byte_rs485( d14 );send_byte_rs485( d15 );send_byte_rs485( d16 );
		                          send_byte_rs485( d17);send_byte_rs485( crc16.byte1);send_byte_rs485( crc16.byte2);send_byte_rs485( FF  ); }//len 1        
                              return 0;
                         }//write_ssp_response_rs485
                         int check_command   (int cmd  ){  if ( command  ==cmd   ){ return 1; }else{ return 0;}  }//check_command
	                 int check_parameter (int param){  if ( parameter==param ){ return 1; }else{ return 0;}  }//check_input
                         if (check_command(PING) ){ write_ssp_response_rs485( OBC,EPS,ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0); }//ACK...........Fault reporting mechanisms? flag, dest, src, cmd/resp , len, data, crc0, crc1, flag
                         if (check_command(SON ) ){ int else_check=1;
                                                    if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);PL5V_EN   (1); }//ACK.... do action
                                                    if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);ADCS5V_EN (1); }//ACK.... do action
                                                    if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);RS12V_EN  (1); }//ACK.... do action
                                                    if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);XB12V_EN  (1); }//ACK.... do action
                                                    if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);RS3V3_EN  (1); }//ACK.... do action
                                                    if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);PL_EN     (1); }//ACK.... do action
                                                    if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);ADCS_EN   (1); }//ACK.... do action
                                                    if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);UHF_EN    (1); }//ACK.... do action
                                                    if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);GPS_EN    (1); }//ACK.... do action
                                                    if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);ADCS12V_EN(1); }//ACK.... do action
                                                    if(else_check==1                ){                                write_ssp_response_rs485( OBC,EPS,NACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);               }//NACK
                         }//SON
                         if ( check_command(SOF) ){ int else_check=1;
                                                    if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);PL5V_EN   (0); }//ACK.... do action
                                                    if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);ADCS5V_EN (0); }//ACK.... do action
                                                    if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);RS12V_EN  (0); }//ACK.... do action
                                                    if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);XB12V_EN  (0); }//ACK.... do action
                                                    if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);RS3V3_EN  (0); }//ACK.... do action
                                                    if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);PL_EN     (0); }//ACK.... do action
                                                    if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);ADCS_EN   (0); }//ACK.... do action
                                                    if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);UHF_EN    (0); }//ACK.... do action
                                                    if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);GPS_EN    (0); }//ACK.... do action
                                                    if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);ADCS12V_EN(0); }//ACK.... do action
                                                    if(else_check==1                ){                                write_ssp_response_rs485( OBC,EPS,NACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);               }//NACK
                        }//SOF
                        if ( check_command(SM )  ){ int else_check=1;
                                                    if(check_parameter( INITIALIZE    ) ){else_check=0;CURRENTMODE=INITIALIZE   ;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(check_parameter( DETUMBLE      ) ){else_check=0;CURRENTMODE=DETUMBLE     ;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(check_parameter( NORMAL        ) ){else_check=0;CURRENTMODE=NORMAL       ;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(check_parameter( COMMUNICATION ) ){else_check=0;CURRENTMODE=COMMUNICATION;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(check_parameter( PAYLOAD       ) ){else_check=0;CURRENTMODE=PAYLOAD      ;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(check_parameter( IMAGE         ) ){else_check=0;CURRENTMODE=IMAGE        ;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(check_parameter( EMERGENCY     ) ){else_check=0;CURRENTMODE=EMERGENCY    ;write_ssp_response_rs485( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(else_check==1                    ){                                       write_ssp_response_rs485( OBC,EPS,NACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//NACK
                        }//SM
                        if ( check_command(GM   ) ){  write_ssp_response_rs485( OBC,EPS, ACK,1,CURRENTMODE       ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);   }//ACK........ dest, src, cmd/response , len, data,
                        if ( check_command(GSC  ) ){  write_ssp_response_rs485( OBC,EPS, ACK,1,CURRENTSYSTEMCLOCK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);   }//ACK........ dest, src, cmd/response , len, data,
                        if ( check_command(SSC  ) ){  write_ssp_response_rs485( OBC,EPS, ACK,0,                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0); CURRENTSYSTEMCLOCK=input.byte6; }//ACK
                        if ( check_command(GOSTM) ){  SA2_I      (); 
                                                      SA3_I      (); 
	   		                              OBC_I      ();
			                              CCU_I      ();   
			                              ADCS_I     (); 
	                     			      UHF_I      ();  
			     			      PL_I       ();  
			    			      RS3V3_I    ();        
			   			      GPS_I      ();    
			   		              ADCS5V_I   ();  
						      PL5V_I     ();  
			  			      CCU5V_I    ();  
						      XB12V_I    ();   
						      ADCS12V_I  ();  
						      RS5V_I     ();
	                                              OBC_FAULT  (); CCU_FAULT  (); RS12V_FLT  ();  RS5V_FLT   ();  ADCS_FAULT ();  UHF_FLT    ();  PL_FLT     ();   RS3V3_FLT  ();
	                                              GPS_FLT    ();    ADCS5V_FLT ();   PL5V_FLT   (); CCU5V_FLT  ();    XB12V_FLT  ();   ADCS12V_FLT();  
                                                      write_ssp_response_rs485( OBC,EPS, ACK,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
                        }//ACK //GOSTM
                        if ( check_command(KEN ) ){ write_ssp_response_rs485( OBC,EPS, ACK,1,KEN ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0); }//ACK ...........shutting down all activity received from GCS or OBC //KEN
                        if ( check_command(KDIS) ){ write_ssp_response_rs485( OBC,EPS, ACK,1,KDIS,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0); }//ACK //KDIS
                        //YOU CAN ALSO ADD LOGIC
}//if proceed
return 0;
}//execute
	
//################# END RS485 METHODS ###################

//################# SPI1 METHODS ########################

struct fourbyte COMMAND_PARAMETER_SPI1  = {0,0,0,0};
  
int receive_spi1 (){
int result=0; int spi1_mosi=0; int spi1_sck=0; int spi1_ss=0;
if ((SPI1_MOSI() + SPI1_MOSI() + SPI1_MOSI())>=2){spi1_mosi = 1;}
if ((SPI1_SS  () + SPI1_SS  () + SPI1_SS  ())>=2){spi1_ss   = 1;}
if ((SPI1_SCK () + SPI1_SCK () + SPI1_SCK ())>=2){spi1_sck  = 1;}
if ( spi1_ss ){
	       if ( !spi1_ss & !spi1_sck ){result=3;}//3
               if ( !spi1_ss &  spi1_sck ){result=0;}//0
               if (  spi1_ss & !spi1_sck ){result=2;}//2
               if (  spi1_ss &  spi1_sck ){result=1;}//1
}
return result;
}//

//####################################
	
//get_command_parameter_after_leftShift_insertEnd_spi1
struct fourbyte get_command_parameter_after_leftShift_insertEnd_spi1(int insertionbit){ 
       COMMAND_PARAMETER_SPI1.byte1 = ( (COMMAND_PARAMETER_SPI1.byte1<<1) | (COMMAND_PARAMETER_SPI1.byte2>>7) ) & 255;
       COMMAND_PARAMETER_SPI1.byte2 = ( (COMMAND_PARAMETER_SPI1.byte2<<1) | (COMMAND_PARAMETER_SPI1.byte3>>7) ) & 255;
       COMMAND_PARAMETER_SPI1.byte3 = ( (COMMAND_PARAMETER_SPI1.byte3<<1) | (COMMAND_PARAMETER_SPI1.byte4>>7) ) & 255;
       COMMAND_PARAMETER_SPI1.byte4 = ( (COMMAND_PARAMETER_SPI1.byte4<<1) | insertionbit                      ) & 255;
return COMMAND_PARAMETER_SPI1;
}//get_command_parameter_after_leftShift_insertEnd_spi1	

//###################################

//execute
int execute_spi1( struct ninebyte input){
    int source      =input.byte3;
    int destination =input.byte2;
    int from_obc_or_from_ccu_to_eps = (int)(  ((source==OBC_ADDRESS)|(source==CCU_ADDRESS)) & (destination==EPS_ADDRESS)  );
    int proper_ssp_frame  = 1;//set to 1 is easier
    int proceed_execution = 0; if( from_obc_or_from_ccu_to_eps & proper_ssp_frame ){proceed_execution=1;}//who can talk to the EPS MCU
    if(proceed_execution){
	                 int command  = input.byte4; int parameter= input.byte6;
                         void pause_spi1( ){}//mada mada
                         void send_bit_spi1  (int bit){
			      if(bit){ SPI1_MISO(1); SPI3_MISO(1); pause_spi1(); SPI1_MISO(0); SPI3_MISO(1); pause_spi1(); }
	                      else   { SPI1_MISO(1); SPI3_MISO(0); pause_spi1(); SPI1_MISO(0); SPI3_MISO(1); pause_spi1(); }
                         }//send_bit_spi1
                         void send_byte_spi1( int out ){
                              for( int index= 0; index<= 7; index++ ){  send_bit_spi1( (int) ( ( (int) ( out >>(7 -index) ) ) & 1 ) ); }//for
                         }//send_byte_spi1
                         int  write_ssp_response_spi1( int dest, int src, int resp, int len, int d1, int d2, int d3, int d4, int d5, int d6, int d7, int d8, int d9, int d10, int d11, int d12, int d13, int d14, int d15, int d16, int d17){ //flag, dest, src, cmd/response , len, data, crc0, crc1, flag
			      struct twobyte crc16 = crc16_generator(dest,src,resp,len,data);//oops!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	                      if(len==0 ){send_byte_spi1( FF );send_byte_spi1( dest );send_byte_spi1( src );send_byte_spi1( resp );send_byte_spi1( len );                                                                                send_byte_spi1( FF  );}//len 0
	                      if(len==1 ){send_byte_spi1( FF );send_byte_spi1( dest );send_byte_spi1( src );send_byte_spi1( resp );send_byte_spi1( len );send_byte_spi1( d1  );send_byte_spi1( crc16.byte1);send_byte_spi1( crc16.byte2);send_byte_spi1( FF  );}//len 1
	                      if(len==17){send_byte_spi1( FF );send_byte_spi1( dest );send_byte_spi1( src );send_byte_spi1( resp );send_byte_spi1( len ); 
		                          send_byte_spi1( d1 );send_byte_spi1( d2   );send_byte_spi1( d3  );send_byte_spi1( d4   );send_byte_spi1( d5  );send_byte_spi1( d6  );send_byte_spi1( d7  );send_byte_spi1( d8  );
		                          send_byte_spi1( d9 );send_byte_spi1( d10  );send_byte_spi1( d11 );send_byte_spi1( d12  );send_byte_spi1( d13 );send_byte_spi1( d14 );send_byte_spi1( d15 );send_byte_spi1( d16 );
		                          send_byte_spi1( d17);send_byte_spi1( crc16.byte1);send_byte_spi1( crc16.byte2);send_byte_spi1( FF  ); }//len 1        
                              return 0;
                         }//write_ssp_response_spi1
	                 int check_command   (int cmd  ){  if ( command  ==cmd   ){ return 1; }else{ return 0;}  }//check_command
	                 int check_parameter (int param){  if ( parameter==param ){ return 1; }else{ return 0;}  }//check_input
                         if (check_command(PING) ){ write_ssp_response_spi1( OBC,EPS,ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0); }//ACK...........Fault reporting mechanisms? flag, dest, src, cmd/resp , len, data, crc0, crc1, flag
                         if (check_command(SON ) ){ int else_check=1;
                                                    if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);PL5V_EN   (1); }//ACK.... do action
                                                    if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);ADCS5V_EN (1); }//ACK.... do action
                                                    if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);RS12V_EN  (1); }//ACK.... do action
                                                    if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);XB12V_EN  (1); }//ACK.... do action
                                                    if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);RS3V3_EN  (1); }//ACK.... do action
                                                    if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);PL_EN     (1); }//ACK.... do action
                                                    if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);ADCS_EN   (1); }//ACK.... do action
                                                    if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);UHF_EN    (1); }//ACK.... do action
                                                    if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);GPS_EN    (1); }//ACK.... do action
                                                    if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);ADCS12V_EN(1); }//ACK.... do action
                                                    if(else_check==1                ){                                write_ssp_response_spi1( OBC,EPS,NACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);               }//NACK
                         }//SON
                         if ( check_command(SOF) ){ int else_check=1;
                                                    if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);PL5V_EN   (0); }//ACK.... do action
                                                    if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);ADCS5V_EN (0); }//ACK.... do action
                                                    if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);RS12V_EN  (0); }//ACK.... do action
                                                    if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);XB12V_EN  (0); }//ACK.... do action
                                                    if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);RS3V3_EN  (0); }//ACK.... do action
                                                    if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);PL_EN     (0); }//ACK.... do action
                                                    if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);ADCS_EN   (0); }//ACK.... do action
                                                    if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);UHF_EN    (0); }//ACK.... do action
                                                    if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);GPS_EN    (0); }//ACK.... do action
                                                    if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);ADCS12V_EN(0); }//ACK.... do action
                                                    if(else_check==1                ){                                write_ssp_response_spi1( OBC,EPS,NACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);               }//NACK
                        }//SOF
                        if ( check_command(SM )  ){ int else_check=1;
                                                    if(check_parameter( INITIALIZE    ) ){else_check=0;CURRENTMODE=INITIALIZE   ;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(check_parameter( DETUMBLE      ) ){else_check=0;CURRENTMODE=DETUMBLE     ;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(check_parameter( NORMAL        ) ){else_check=0;CURRENTMODE=NORMAL       ;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(check_parameter( COMMUNICATION ) ){else_check=0;CURRENTMODE=COMMUNICATION;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(check_parameter( PAYLOAD       ) ){else_check=0;CURRENTMODE=PAYLOAD      ;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(check_parameter( IMAGE         ) ){else_check=0;CURRENTMODE=IMAGE        ;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(check_parameter( EMERGENCY     ) ){else_check=0;CURRENTMODE=EMERGENCY    ;write_ssp_response_spi1( OBC,EPS, ACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//ACK.... do action
                                                    if(else_check==1                    ){                                       write_ssp_response_spi1( OBC,EPS,NACK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);     }//NACK
                        }//SM
                        if ( check_command(GM   ) ){  write_ssp_response_spi1( OBC,EPS, ACK,1,CURRENTMODE       ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);   }//ACK........ dest, src, cmd/response , len, data,
                        if ( check_command(GSC  ) ){  write_ssp_response_spi1( OBC,EPS, ACK,1,CURRENTSYSTEMCLOCK,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);   }//ACK........ dest, src, cmd/response , len, data,
                        if ( check_command(SSC  ) ){  write_ssp_response_spi1( OBC,EPS, ACK,0,                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0); CURRENTSYSTEMCLOCK=input.byte6; }//ACK
                        if ( check_command(GOSTM) ){  SA2_I      (); 
                                                      SA3_I      (); 
	   		                              OBC_I      ();
			                              CCU_I      ();   
			                              ADCS_I     (); 
	                     			      UHF_I      ();  
			     			      PL_I       ();  
			    			      RS3V3_I    ();        
			   			      GPS_I      ();    
			   		              ADCS5V_I   ();  
						      PL5V_I     ();  
			  			      CCU5V_I    ();  
						      XB12V_I    ();   
						      ADCS12V_I  ();  
						      RS5V_I     ();
	                                              OBC_FAULT  (); CCU_FAULT  (); RS12V_FLT  ();  RS5V_FLT   ();  ADCS_FAULT ();  UHF_FLT    ();  PL_FLT     ();   RS3V3_FLT  ();
	                                              GPS_FLT    ();    ADCS5V_FLT ();   PL5V_FLT   (); CCU5V_FLT  ();    XB12V_FLT  ();   ADCS12V_FLT();  
                                                      write_ssp_response_spi1( OBC,EPS, ACK,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
                        }//ACK //GOSTM
                        if ( check_command(KEN ) ){ write_ssp_response_spi1( OBC,EPS, ACK,1,KEN ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0); }//ACK ...........shutting down all activity received from GCS or OBC //KEN
                        if ( check_command(KDIS) ){ write_ssp_response_spi1( OBC,EPS, ACK,1,KDIS,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0); }//ACK //KDIS
                        //YOU CAN ALSO ADD LOGIC
    }//proceed execution    
    //YOU CAN ALSO ADD LOGIC
return 0;
}//execute	
//################# END SPI1 METHODS ###################
	
//################# SPI3 METHODS ########################

struct fourbyte COMMAND_PARAMETER_SPI3  = {0,0,0,0};
  
int receive_spi3 (){
int result=0; int spi3_mosi=0; int spi3_sck=0; int spi3_ss=0;
if ((SPI3_MOSI() + SPI3_MOSI() + SPI3_MOSI())>=2){spi3_mosi = 1;}
if ((SPI3_SS  () + SPI3_SS  () + SPI3_SS  ())>=2){spi3_ss   = 1;}
if ((SPI3_SCK () + SPI3_SCK () + SPI3_SCK ())>=2){spi3_sck  = 1;}
if ( spi3_ss ){
	       if ( !spi3_ss & !spi3_sck ){result=3;}//3
               if ( !spi3_ss &  spi3_sck ){result=0;}//0
               if (  spi3_ss & !spi3_sck ){result=2;}//2
               if (  spi3_ss &  spi3_sck ){result=1;}//1
}
return result;
}//

//####################################
	
//get_command_parameter_after_leftShift_insertEnd_spi3
struct fourbyte get_command_parameter_after_leftShift_insertEnd_spi3(int insertionbit){ 
       COMMAND_PARAMETER_SPI3.byte1 = ( (COMMAND_PARAMETER_SPI3.byte1<<1) | (COMMAND_PARAMETER_SPI3.byte2>>7) ) & 255;
       COMMAND_PARAMETER_SPI3.byte2 = ( (COMMAND_PARAMETER_SPI3.byte2<<1) | (COMMAND_PARAMETER_SPI3.byte3>>7) ) & 255;
       COMMAND_PARAMETER_SPI3.byte3 = ( (COMMAND_PARAMETER_SPI3.byte3<<1) | (COMMAND_PARAMETER_SPI3.byte4>>7) ) & 255;
       COMMAND_PARAMETER_SPI3.byte4 = ( (COMMAND_PARAMETER_SPI3.byte4<<1) | insertionbit                      ) & 255;
return COMMAND_PARAMETER_SPI3;
}//get_command_parameter_after_leftShift_insertEnd_spi3	

//###################################

//execute
int execute_spi3( struct fourbyte command_parameter){
    int write_response_spi1and3( struct twobyte ab, struct twobyte cd ){
        void send_bit_spi1and3  (int bit){
        if(bit){ SPI3_MISO(1); SPI3_MISO(1); for(int i=0;i<1000;i++){} SPI3_MISO(0); SPI3_MISO(1); for(int i=0;i<1000;i++){} }
	else   { SPI3_MISO(1); SPI3_MISO(0); for(int i=0;i<1000;i++){} SPI3_MISO(0); SPI3_MISO(1); for(int i=0;i<1000;i++){} }
        }//
        int RESPONSEARRAY_SPI3[32];
        for( int index= 0; index<= 7; index++ ){ RESPONSEARRAY_SPI3[index] = (int) ( ( (int) ( ab.byte1 >>(7 -index) ) ) & 1 ); }//for
        for( int index= 8; index<=15; index++ ){ RESPONSEARRAY_SPI3[index] = (int) ( ( (int) ( ab.byte2 >>(15-index) ) ) & 1 ); }//for
        for( int index=16; index<=23; index++ ){ RESPONSEARRAY_SPI3[index] = (int) ( ( (int) ( cd.byte1 >>(23-index) ) ) & 1 ); }//for
        for( int index=24; index<=31; index++ ){ RESPONSEARRAY_SPI3[index] = (int) ( ( (int) ( cd.byte2 >>(31-index) ) ) & 1 ); }//for
        for( int index= 0; index<=31; index++ ){ send_bit_spi1and3(  RESPONSEARRAY_SPI3[index]  );                                  }//for
    return 0;
    }//write_response_spi3
    int check_command  (struct twobyte x){ if ((command_parameter.byte1==x.byte1)&(command_parameter.byte2==x.byte2)){ return 1; }else{ return 0; } }
    int check_parameter(struct twobyte x){ if ((command_parameter.byte3==x.byte3)&(command_parameter.byte4==x.byte4)){ return 1; }else{ return 0; } }
    if ( check_command(PING)  ){ write_response_spi1and3(ACK,EMPTY); }//ACK...........Fault reporting mechanisms?
    if ( check_command(SON )  ){
                        int else_check=1;
                        if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);PL5V_EN   (1); }//ACK.... do action
                        if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);ADCS5V_EN (1); }//ACK.... do action
                        if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);RS12V_EN  (1); }//ACK.... do action
                        if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);XB12V_EN  (1); }//ACK.... do action
                        if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);RS3V3_EN  (1); }//ACK.... do action
                        if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);PL_EN     (1); }//ACK.... do action
                        if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);ADCS_EN   (1); }//ACK.... do action
                        if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);UHF_EN    (1); }//ACK.... do action
                        if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);GPS_EN    (1); }//ACK.... do action
                        if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);ADCS12V_EN(1); }//ACK.... do action
                        if(else_check==1                ){                                write_response_spi1and3(NACK,EMPTY);               }//NACK
    }//SON
    if ( check_command(SOF)  ){
                        int else_check=1;
                        if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);PL5V_EN   (0); }//ACK.... do action
                        if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);ADCS5V_EN (0); }//ACK.... do action
                        if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);RS12V_EN  (0); }//ACK.... do action
                        if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);XB12V_EN  (0); }//ACK.... do action
                        if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);RS3V3_EN  (0); }//ACK.... do action
                        if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);PL_EN     (0); }//ACK.... do action
                        if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);ADCS_EN   (0); }//ACK.... do action
                        if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);UHF_EN    (0); }//ACK.... do action
                        if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);GPS_EN    (0); }//ACK.... do action
                        if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_response_spi1and3(ACK ,EMPTY);ADCS12V_EN(0); }//ACK.... do action
                        if(else_check==1                ){                                write_response_spi1and3(NACK,EMPTY);               }//NACK
    }//SOF
    if ( check_command(SM )  ){
                         int else_check=1;
                         if(check_parameter( INITIALIZE    ) ){else_check=0;CURRENTMODE=INITIALIZE   ;write_response_spi1and3(ACK ,EMPTY);     }//ACK.... do action
                         if(check_parameter( DETUMBLE      ) ){else_check=0;CURRENTMODE=DETUMBLE     ;write_response_spi1and3(ACK ,EMPTY);     }//ACK.... do action
                         if(check_parameter( NORMAL        ) ){else_check=0;CURRENTMODE=NORMAL       ;write_response_spi1and3(ACK ,EMPTY);     }//ACK.... do action
                         if(check_parameter( COMMUNICATION ) ){else_check=0;CURRENTMODE=COMMUNICATION;write_response_spi1and3(ACK ,EMPTY);     }//ACK.... do action
                         if(check_parameter( PAYLOAD       ) ){else_check=0;CURRENTMODE=PAYLOAD      ;write_response_spi1and3(ACK ,EMPTY);     }//ACK.... do action
                         if(check_parameter( IMAGE         ) ){else_check=0;CURRENTMODE=IMAGE        ;write_response_spi1and3(ACK ,EMPTY);     }//ACK.... do action
                         if(check_parameter( EMERGENCY     ) ){else_check=0;CURRENTMODE=EMERGENCY    ;write_response_spi1and3(ACK ,EMPTY);     }//ACK.... do action
                         if(else_check==1                    ){                                       write_response_spi1and3(NACK,EMPTY);     }//NACK
    }//SM
    if ( check_command(GM   ) ){ write_response_spi1and3(ACK,CURRENTMODE       ); }//ACK //GM
    if ( check_command(GSC  ) ){ write_response_spi1and3(ACK,CURRENTSYSTEMCLOCK); }//ACK.........MIGHT have to do away with 2 byte response limitation OR i can just specify what each count(1) represents as a time period for a 1 byte maximum
    if ( check_command(SSC  ) ){ write_response_spi1and3(ACK, EMPTY );CURRENTSYSTEMCLOCK=parameter; }//ACK
    if ( check_command(GOSTM) ){
                               int a = (int) (XB12V_I  ()<<7);  int b = (int) (ADCS12V_I()<<6); int c = (int) (RS5V_I   ()<<5);  int d = (int) (RS3V3_I  ()<<4);
                               int e = (int) (SA1_I    ()<<3);  int f = (int) (SA2_I    ()<<2); int g = (int) (SA3_I    ()<<1);
                               write_response_spi1and3(  ACK, (int) (a | b | c | d | e | f | g |  1)    );
    }//ACK //GOSTM
    if ( check_command(KEN ) ){ write_response_spi1and3(ACK,KEN ); }//ACK ...........shutting down all activity received from GCS or OBC //KEN
    if ( check_command(KDIS) ){ write_response_spi1and3(ACK,KDIS); }//ACK //KDIS
    //YOU CAN ALSO ADD LOGIC
return 0;
}//execute

	
//################# END SPI3 METHODS ###################


//################################################################ END OF DECLARATIONS ################################################

//########################   MAIN EVENT  ###########################################
int raw_input_spi1;
int previous_spi1;
int input_1_detected_spi1;
int input_0_detected_spi1;	
//##
int raw_input_spi3;
int previous_spi3;
int input_1_detected_spi3;
int input_0_detected_spi3;
//##
//int raw_input_i2c;
//int previous_i2c;
//int input_1_detected_i2c;
//int input_0_detected_i2c;
//##
int raw_input_rs485;
int previous_rs485;
int input_1_detected_rs485;
int input_0_detected_rs485;
//##
//MAIN LOOP
while(1){//while
	       //######## SPI1 #############
	       raw_input_spi1 = receive_spi1();
               if ( ((previous_spi1==1) & (raw_input_spi1==2)) |  ((previous_spi1==1) & (raw_input_spi1==3)) ){  input_1_detected_spi1=1;  }
	       if ( ((previous_spi1==0) & (raw_input_spi1==2)) |  ((previous_spi1==0) & (raw_input_spi1==3)) ){  input_0_detected_spi1=1;  }
               if ( input_1_detected_spi1 ){ input_1_detected_spi1=0; execute_spi1( get_command_parameter_after_leftShift_insertEnd_spi1(1) ); }//if
               if ( input_0_detected_spi1 ){ input_0_detected_spi1=0; execute_spi1( get_command_parameter_after_leftShift_insertEnd_spi1(0) ); }//if
               previous_spi1 = raw_input_spi1;
	       //######## END SPI1 ##########
               //######## SPI3 ##############
	       raw_input_spi3 = receive_spi3();
               if ( ((previous_spi3==1) & (raw_input_spi3==2)) |  ((previous_spi3==1) & (raw_input_spi3==3)) ){  input_1_detected_spi3=1;  }
	       if ( ((previous_spi3==0) & (raw_input_spi3==2)) |  ((previous_spi3==0) & (raw_input_spi3==3)) ){  input_0_detected_spi3=1;  }
               if ( input_1_detected_spi3 ){ input_1_detected_spi3=0;  execute_spi3( get_command_parameter_after_leftShift_insertEnd_spi3(1) ); }//if
               if ( input_0_detected_spi3 ){ input_0_detected_spi3=0;  execute_spi3( get_command_parameter_after_leftShift_insertEnd_spi3(0) ); }//if
               previous_spi3 = raw_input_spi3;
	       //######## END SPI3 ##########
	       //######## I2C ###############
	       //raw_input_i2c = receive_bit_transmit_bit_i2c();
               //if ( ((previous_i2c==1) & (raw_input_i2c==2)) |  ((previous_i2c==1) & (raw_input_i2c==3)) ){  input_1_detected_i2c=1;  }
	       //if ( ((previous_i2c==0) & (raw_input_i2c==2)) |  ((previous_i2c==0) & (raw_input_i2c==3)) ){  input_0_detected_i2c=1;  }
               //if ( input_1_detected_i2c ){ input_1_detected_i2c=0;  execute_i2c( get_command_parameter_after_leftShift_insertEnd_i2c(1) ); }//if
               //if ( input_0_detected_i2c ){ input_0_detected_i2c=0;  execute_i2c( get_command_parameter_after_leftShift_insertEnd_i2c(0) ); }//if
               //previous_i2c = raw_input_i2c;
	       //######## END I2C ############
	       //######## RS485 ##############
	       raw_input_rs485 = receive_rs485();
               if ( ((previous_rs485==1) & (raw_input_rs485==2)) |  ((previous_rs485==1) & (raw_input_rs485==3)) ){  input_1_detected_rs485=1;  }
	       if ( ((previous_rs485==0) & (raw_input_rs485==2)) |  ((previous_rs485==0) & (raw_input_rs485==3)) ){  input_0_detected_rs485=1;  }
               if ( input_1_detected_rs485 ){ input_1_detected_rs485=0; execute_rs485( get_command_parameter_after_leftShift_insertEnd_rs485(1) ); }//if
               if ( input_0_detected_rs485 ){ input_0_detected_rs485=0; execute_rs485( get_command_parameter_after_leftShift_insertEnd_rs485(0) ); }//if
	       previous_rs485 = raw_input_rs485;
	       //######## END RS485 ############
}//while  
//MAIN LOOP
//#########################    END MAIN EVENT   #################################

return 0;
}//main
