//As it stands for a single while loop cycle, tx 1 bit spi1, re
//Prferrable to use preamble
//uint8_t, uint16_t, uint32_t or chars can be used to replace the int types- but int is universal and type size is not an issue
//rs485 data when A and !A
//i2c data when clock high
//Dude, be cautious with your variables - public or global... _I are functions that read from input pins, _EN are raw integers(commands targeting output pins)
//Whoa! the EPS microntroller is actually  sampling the inputs in every while loop instance, so we have to check for changes in input states to determine if we have a 1 or a 0 

//SSP input bit frame :   1    ,   1               , 8  , 8     ,  1
//                      start  ,  address=number2 , cmd , param ,  end

//SSP output bit frame :   1    ,   1          , 8        , 8*16     ,  1
//                      start  ,  address=dest , ack/nack ,          ,  end

//SSP output bit frame :   1    ,   1          , 8  , 8     ,  1
//                      start  ,  address=dest , cmd , param ,  end


int main(){//main
struct
struct twobyte  { int byte1; int byte2; };
struct fourbyte { int byte1; int byte2; int byte3; int byte4; };
// add const def	
//############ DECLARATIONS ###########
	
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
const struct twobyte EMPTY           = {0  , 0 };
const struct twobyte PING            = {34 ,34 }; //command
const struct twobyte ACK             = {47 ,47 };   
const struct twobyte ACKNOWLEDGE     = ACK      ;
const struct twobyte NACK            = {52 ,52 };
const struct twobyte NOT_ACKNOWLEDGE = NACK     ;
const struct twobyte SON             = {140,140};
const struct twobyte SWITCH_ON       = SON      ;
const struct twobyte UHF             = {24 ,24 }; //parameter
const struct twobyte ADCS            = {162,162}; //parameter
const struct twobyte GPS             = {75 ,75 }; //parameter
const struct twobyte SOF             = {218,218};
const struct twobyte SWITCH_OFF      = SOF      ; //command
const struct twobyte SM              = {107,107};
const struct twobyte SET_MODE        = SM       ; //command
const struct twobyte GM              = {122,122};
const struct twobyte GET_MODE        = GM       ; //command
const struct twobyte GSC             = {94 ,94 };
const struct twobyte GET_SYSTEM_CLOCK= GSC      ; //command
const struct twobyte SSC             = {209,209}; 
const struct twobyte SET_SYSTEM_CLOCK= SSC      ; //command
const struct twobyte GFP             = {134,134}; //command
const struct twobyte SFP             = {90 ,90 }; //command
const struct twobyte FON             = {55 ,55 }; 
const struct twobyte FUNCTION_ON     = FON      ; //command
const struct twobyte TWELVEBUS       = {100,100}; //telemetry parameter
const struct twobyte FIVEBUS         = {150,150}; //telemetry parameter
const struct twobyte THREEBUS        = {200,200}; //parameter
const struct twobyte FOF             = {233,233}; 
const struct twobyte FUNCTION_OFF    = FOF      ; //command
const struct twobyte GOSTM           = {157,157};
const struct twobyte GET_ONLINE_SYSTEM_TELEMETRY = GOSTM; //command
const struct twobyte KEN             = {255,255};
const struct twobyte KILL_ENABLE     = KEN      ; //command
const struct twobyte KDIS            = {227,227};
const struct twobyte KILL_DISABLE    = KDIS     ; //command
const struct twobyte GD              = {15 ,15 };
const struct twobyte GET_DATA        = GD       ; //command
const struct twobyte PD              = {245,245};
const struct twobyte PUT_DATA        = PD       ; //command
const struct twobyte RD              = {222,222}; 
const struct twobyte READ_DATA       = RD       ; //command
const struct twobyte WD              = {133,133}; 
const struct twobyte WRITE_DATA      = WD       ; //command
const struct twobyte INITIALIZE      = {60 ,60 }; //mode parameter
const struct twobyte DETUMBLE        = {71 ,71 }; //mode parameter
const struct twobyte NORMAL          = {82 ,82 }; //mode parameter
const struct twobyte COMMUNICATION   = {93 ,93 }; //mode parameter
const struct twobyte PAYLOAD         = {104,104}; //mode parameter
const struct twobyte IMAGE           = {115,115}; //mode parameter
const struct twobyte EMERGENCY       = {126,126}; //mode parameter
const struct twobyte CUSTOM          = {69 ,69 }; //mode parameter
const struct twobyte PL5V_EN         = {230,230}; 
const struct twobyte PAYLOAD_5V_ENABLE = PL5V_EN  ; //pin
const struct twobyte ADCS5V_EN         = {143,143};
const struct twobyte ADCS_5V_ENABLE    = ADCS5V_EN; //pin
const struct twobyte RS12V_EN          = {205,205};
const struct twobyte RESERVED_12V_EN   = RS12V_EN ; //pin
const struct twobyte XB12V_EN          = {139,139};
const struct twobyte XBAND_12V_ENABLE= XB12V_EN ; //pin
const struct twobyte CCU5V_EN          = {155,155}; 
const struct twobyte CENTRAL_COMMAND_UNIT_5V_ENABLE = CCU5V_EN; //pin
const struct twobyte RS3V3_EN          = {212,212};
const struct twobyte RESERVED_3V_ENABLE= RS3V3_EN ; //pin
const struct twobyte PL_EN             = {172,172};
const struct twobyte PAYLOAD_ENABLE    = PL_EN    ; //pin
const struct twobyte ADCS_EN           = {144,144};
const struct twobyte ADCS_ENABLE       = ADCS_EN  ; //pin
const struct twobyte UHF_EN            = {189,189};
const struct twobyte UHF_ENABLE        = UHF_EN   ; //pin
const struct twobyte GPS_EN            = {57 ,57 };
const struct twobyte GPS_ENABLE        = GPS_EN   ; //pin
const struct twobyte ADCS12V_EN        = {199,199} ; 
const struct twobyte ADCS_12V_ENABLE   = ADCS12V_EN; //pin
const struct twobyte EPS_EN            = {97 ,97 } ; 
const struct twobyte EPS_ENABLE        = EPS_EN    ;//funny


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


//#######################

//response_wait
int response_wait(){
    for( int count=0;  count<=RESPONSE_WAIT ;count++ ){ }//do nothing
    //HAL delay could work too
return 0;
}//response_wait
	
//################# RS485 METHODS/DECLARATIONS ###################

struct fourbyte COMMAND_PARAMETER_RS485  = {0,0,0,0};// a fusion of 4851 and 4852 because we can't identify pauses
  
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
struct fourbyte get_command_parameter_after_leftShift_insertEnd_rs485(int insertionbit){ 
       COMMAND_PARAMETER_RS485.byte1 = ( (COMMAND_PARAMETER_RS485.byte1<<1) | (COMMAND_PARAMETER_RS485.byte2>>7) ) & 255;
       COMMAND_PARAMETER_RS485.byte2 = ( (COMMAND_PARAMETER_RS485.byte2<<1) | (COMMAND_PARAMETER_RS485.byte3>>7) ) & 255;
       COMMAND_PARAMETER_RS485.byte3 = ( (COMMAND_PARAMETER_RS485.byte3<<1) | (COMMAND_PARAMETER_RS485.byte4>>7) ) & 255;
       COMMAND_PARAMETER_RS485.byte4 = ( (COMMAND_PARAMETER_RS485.byte4<<1) | insertionbit                       ) & 255;
return COMMAND_PARAMETER_RS485;
}//get_command_parameter_after_leftShift_insertEnd_rs485

//###################################

//execute
int execute_rs485(struct fourbyte command_parameter){
    int write_response_rs485( struct twobyte ab, struct twobyte cd ){
        void send_bit_rs485  (int bit){
        if(bit){ RS4851_TX(1); RS4852_TX(1); } else { RS4851_TX(0); RS4852_TX(0); }
        RS4851_DE(1);RS4852_DE(1);
        for(int i=0;i<1000;i++){}//for
	      RS4851_TX(0);RS4852_TX(1);
        for(int i=0;i<1000;i++){}//for
	      RS4851_DE(0);RS4852_DE(0);
        }//send_bit_rs485
        int RESPONSEARRAY_RS485[32];
        for( int index= 0; index<= 7; index++ ){ RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( ab.byte1 >>(7 -index) ) ) & 1 ); }//for
        for( int index= 8; index<=15; index++ ){ RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( ab.byte2 >>(15-index) ) ) & 1 ); }//for
        for( int index=16; index<=23; index++ ){ RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( cd.byte1 >>(23-index) ) ) & 1 ); }//for
        for( int index=24; index<=31; index++ ){ RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( cd.byte2 >>(31-index) ) ) & 1 ); }//for
        for( int index= 0; index<=31; index++ ){ send_bit_rs485(  RESPONSEARRAY_RS485[index]  );                                  }//for
    return 0;
    }//write_response_rs485
    int check_command  (struct twobyte x){ if ((  command_parameter.byte1==x.byte1)&(  command_parameter.byte2==x.byte2)){ return 1; }else{ return 0; } }
    int check_parameter(struct twobyte x){ if ((  command_parameter.byte3==x.byte3)&(  command_parameter.byte4==x.byte4)){ return 1; }else{ return 0; } }
    if ( check_command(PING)  ){ write_response_rs485(ACK,EMPTY); }//ACK...........Fault reporting mechanisms?
    if ( check_command(SON )  ){
                        int else_check=1;
                        if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);PL5V_EN   (1); }//ACK.... do action
                        if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);ADCS5V_EN (1); }//ACK.... do action
                        if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);RS12V_EN  (1); }//ACK.... do action
                        if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);XB12V_EN  (1); }//ACK.... do action
                        if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);RS3V3_EN  (1); }//ACK.... do action
                        if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);PL_EN     (1); }//ACK.... do action
                        if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);ADCS_EN   (1); }//ACK.... do action
                        if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);UHF_EN    (1); }//ACK.... do action
                        if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);GPS_EN    (1); }//ACK.... do action
                        if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);ADCS12V_EN(1); }//ACK.... do action
                        if(else_check==1                ){                                write_response_rs485(NACK,EMPTY);               }//NACK
    }//SON
    if ( check_command(SOF)  ){
                        int else_check=1;
                        if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);PL5V_EN   (0); }//ACK.... do action
                        if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);ADCS5V_EN (0); }//ACK.... do action
                        if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);RS12V_EN  (0); }//ACK.... do action
                        if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);XB12V_EN  (0); }//ACK.... do action
                        if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);RS3V3_EN  (0); }//ACK.... do action
                        if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);PL_EN     (0); }//ACK.... do action
                        if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);ADCS_EN   (0); }//ACK.... do action
                        if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);UHF_EN    (0); }//ACK.... do action
                        if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);GPS_EN    (0); }//ACK.... do action
                        if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,EMPTY);ADCS12V_EN(0); }//ACK.... do action
                        if(else_check==1                ){                                write_response_rs485(NACK,EMPTY);               }//NACK
    }//SOF
    if ( check_command(SM )  ){
                         int else_check=1;
                         if(check_parameter( INITIALIZE    ) ){else_check=0;CURRENTMODE=INITIALIZE   ;write_response_rs485(ACK ,EMPTY);     }//ACK.... do action
                         if(check_parameter( DETUMBLE      ) ){else_check=0;CURRENTMODE=DETUMBLE     ;write_response_rs485(ACK ,EMPTY);     }//ACK.... do action
                         if(check_parameter( NORMAL        ) ){else_check=0;CURRENTMODE=NORMAL       ;write_response_rs485(ACK ,EMPTY);     }//ACK.... do action
                         if(check_parameter( COMMUNICATION ) ){else_check=0;CURRENTMODE=COMMUNICATION;write_response_rs485(ACK ,EMPTY);     }//ACK.... do action
                         if(check_parameter( PAYLOAD       ) ){else_check=0;CURRENTMODE=PAYLOAD      ;write_response_rs485(ACK ,EMPTY);     }//ACK.... do action
                         if(check_parameter( IMAGE         ) ){else_check=0;CURRENTMODE=IMAGE        ;write_response_rs485(ACK ,EMPTY);     }//ACK.... do action
                         if(check_parameter( EMERGENCY     ) ){else_check=0;CURRENTMODE=EMERGENCY    ;write_response_rs485(ACK ,EMPTY);     }//ACK.... do action
                         if(else_check==1                    ){                                       write_response_rs485(NACK,EMPTY);     }//NACK
    }//SM
    if ( check_command(GM   ) ){ write_response_rs485(ACK,CURRENTMODE       ); }//ACK //GM
    if ( check_command(GSC  ) ){ write_response_rs485(ACK,CURRENTSYSTEMCLOCK); }//ACK.........MIGHT have to do away with 2 byte response limitation OR i can just specify what each count(1) represents as a time period for a 1 byte maximum
    if ( check_command(SSC  ) ){ write_response_rs485(ACK, EMPTY  );CURRENTSYSTEMCLOCK=parameter; }//ACK
    if ( check_command(GOSTM) ){
                               int a = (int) (XB12V_I  ()<<7);  int b = (int) (ADCS12V_I()<<6); int c = (int) (RS5V_I   ()<<5);  int d = (int) (RS3V3_I  ()<<4);
                               int e = (int) (SA1_I    ()<<3);  int f = (int) (SA2_I    ()<<2); int g = (int) (SA3_I    ()<<1);
                               write_response_rs485(  ACK, (int) (a | b | c | d | e | f | g |  1)    );
    }//ACK //GOSTM
    if ( check_command(KEN ) ){ write_response_rs485(ACK,KEN ); }//ACK ...........shutting down all activity received from GCS or OBC //KEN
    if ( check_command(KDIS) ){ write_response_rs485(ACK,KDIS); }//ACK //KDIS
    //YOU CAN ALSO ADD LOGIC
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
int execute_spi1( struct fourbyte command_parameter){
    int write_response_spi1and3( struct twobyte ab, struct twobyte cd ){
        void send_bit_spi1and3  (int bit){
        if(bit){ SPI1_MISO(1); SPI3_MISO(1); for(int i=0;i<1000;i++){} SPI1_MISO(0); SPI3_MISO(1); for(int i=0;i<1000;i++){} }
	else   { SPI1_MISO(1); SPI3_MISO(0); for(int i=0;i<1000;i++){} SPI1_MISO(0); SPI3_MISO(1); for(int i=0;i<1000;i++){} }
        }//
        int RESPONSEARRAY_SPI1[32];
        for( int index= 0; index<= 7; index++ ){ RESPONSEARRAY_SPI1[index] = (int) ( ( (int) ( ab.byte1 >>(7 -index) ) ) & 1 ); }//for
        for( int index= 8; index<=15; index++ ){ RESPONSEARRAY_SPI1[index] = (int) ( ( (int) ( ab.byte2 >>(15-index) ) ) & 1 ); }//for
        for( int index=16; index<=23; index++ ){ RESPONSEARRAY_SPI1[index] = (int) ( ( (int) ( cd.byte1 >>(23-index) ) ) & 1 ); }//for
        for( int index=24; index<=31; index++ ){ RESPONSEARRAY_SPI1[index] = (int) ( ( (int) ( cd.byte2 >>(31-index) ) ) & 1 ); }//for
        for( int index= 0; index<=31; index++ ){ send_bit_spi1and3(  RESPONSEARRAY_SPI1[index]  );                                  }//for
    return 0;
    }//write_response_spi1
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
    if ( check_command(SSC  ) ){ write_response_spi1and3(ACK, EMPTY  );CURRENTSYSTEMCLOCK=parameter; }//ACK
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
