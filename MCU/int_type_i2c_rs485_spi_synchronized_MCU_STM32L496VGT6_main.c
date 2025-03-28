//As it stands for a single while loop cycle, tx 1 bit spi1, re
//Prferrable to use preamble
//uint8_t, uint16_t, uint32_t or chars can be used to replace the int types- but int is universal and type size is not an issue
//rs485 data when A and !A
//i2c data when clock high
//Dude, be cautious with your variables - public or global... _I are functions that read from input pins, _EN are raw integers(commands targeting output pins)
//Whoa! the EPS microntroller is actually  sampling the inputs in every while loop instance, so we have to check for changes in input states to determine if we have a 1 or a 0 

int main(){//main
	

// add const def	
//############ DECLARATIONS ###########
	
//Boolean
int HIGH          = 1  ;  int TRUE = HIGH; int ONE  = HIGH;
int LOW           = 0  ;  int FALSE= LOW ; int ZERO = LOW ;
int PAUSE         = 2  ;
int END           = 3  ;
//TRANSMISSION AND RECEPTION (COMMUNICATION) SYMBOLS
int PING          = 34 ;   //command
int ACK           = 47 ;   int ACKNOWLEDGE                   = ACK ;//response
int NACK          = 52 ;   int NOT_ACKNOWLEDGE               = NACK;//response
int SON           = 140;   int SWITCH_ON                     = SON ;//command
int UHF           = 24 ;   //parameter
int ADCS          = 162;   //parameter
int GPS           = 75 ;   //parameter
int SOF           = 218;   int SWITCH_OFF                    = SOF  ;//command
int SM            = 107;   int SET_MODE                      = SM   ;//command
int GM            = 122;   int GET_MODE                      = GM   ;//command
int GSC           = 94 ;   int GET_SYSTEM_CLOCK              = GSC  ;//command
int SSC           = 209;   int SET_SYSTEM_CLOCK              = SSC  ;//command
int GFP           = 134;   //command
int SFP           = 90 ;   //command
int FON           = 55 ;   int FUNCTION_ON                   = FON  ;//command
int TWELVEBUS     = 100;   //telemetry parameter
int FIVEBUS       = 150;   //telemetry parameter
int THREEBUS      = 200;   //parameter
int FOF           = 233;   int FUNCTION_OFF                  = FOF  ;//command
int GOSTM         = 157;   int GET_ONLINE_SYSTEM_TELEMETRY   = GOSTM;//command
int KEN           = 255;   int KILL_ENABLE                   = KEN  ;//command
int KDIS          = 227;   int KILL_DISABLE                  = KDIS ;//command
int GD            = 15 ;   int GET_DATA                      = GD   ;//command
int PD            = 245;   int PUT_DATA                      = PD   ;//command
int RD            = 222;   int READ_DATA                     = RD   ;//command
int WD            = 133;   int WRITE_DATA                    = WD   ;//command
int INITIALIZE    = 60 ;   //mode parameter
int DETUMBLE      = 71 ;   //mode parameter
int NORMAL        = 82 ;   //mode parameter
int COMMUNICATION = 93 ;   //mode parameter
int PAYLOAD       = 104;   //mode parameter
int IMAGE         = 115;   //mode parameter
int EMERGENCY     = 126;   //mode parameter
int CUSTOM        = 69 ;   //mode parameter
int PL5V_EN       = 230;   int PAYLOAD_5V_ENABLE              = PL5V_EN   ;//pin
int ADCS5V_EN     = 143;   int ADCS_5V_ENABLE                 = ADCS5V_EN ;//pin
int RS12V_EN      = 205;   int RESERVED_12V_EN                = RS12V_EN  ;//pin
int XB12V_EN      = 139;   int XBAND_12V_ENABLE               = XB12V_EN  ;//pin
int CCU5V_EN      = 155;   int CENTRAL_COMMAND_UNIT_5V_ENABLE = CCU5V_EN  ;//pin
int RS3V3_EN      = 212;   int RESERVED_3V_ENABLE             = RS3V3_EN  ;//pin
int PL_EN         = 172;   int PAYLOAD_ENABLE                 = PL_EN     ;//pin
int ADCS_EN       = 144;   int ADCS_ENABLE                    = ADCS_EN   ;//pin
int UHF_EN        = 189;   int UHF_ENABLE                     = UHF_EN    ;//pin
int GPS_EN        = 57 ;   int GPS_ENABLE                     = GPS_EN    ;//pin
int ADCS12V_EN    = 199;   int ADCS_12V_ENABLE                = ADCS12V_EN;//pin
int EPS_EN        = 97 ;   int EPS_ENABLE                     = EPS_EN    ;//funny

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
int RESPONSE_WAIT           = 10000;//response_wait()
int CURRENTMODE             = 0;
int CURRENTSYSTEMCLOCK      = 0;
int COMMAND_PARAMETER_RS485 = 0;

//####################################

//response_wait
int response_wait(){
    for( int count=0;  count<=RESPONSE_WAIT ;count++ ){ }//do nothing
    //HAL delay could work too
return 0;
}//response_wait
	
//################# RS485 METHODS ###################
	
int receive_rs485(){
int result;
RS4851_DE(0);
RS4852_DE(0);
if( RS4851_RX(1) & RS4852_RX(0)  ){result=1;}//1
if( RS4851_RX(0) & RS4852_RX(1)  ){result=0;}//0
if( RS4851_RX(0) & RS4852_RX(0)  ){result=2;}//end
if( RS4851_RX(1) & RS4852_RX(1)  ){result=3;}//pause
return result;
}//

//####################################
	
//get_command_parameter_after_leftShift_insertEnd_rs485
int get_command_parameter_after_leftShift_insertEnd_rs485(int insertionbit){
    COMMAND_PARAMETER_RS485 = (COMMAND_PARAMETER_RS485<<1) & (65534|insertionbit);
    return COMMAND_PARAMETER_RS485;
}//get_command_parameter_after_leftShift_insertEnd_rs485

//###################################
	
//TRUTH TABLE
//RS4851_TX RS4852_TX   Y
//0         0           3(end)
//0         1           0
//1         0           1
//1         1           2(pause)
//write_response_rs485
int write_response_rs485( int firstbyte, int secondbyte){
    void send_bit_rs485  (int bit){
         if(bit){ RS4851_TX(1); RS4852_TX(0); } else { RS4851_TX(0); RS4852_TX(1); }
         RS4851_DE(1); RS4852_DE(1);
         for(int i=0;i<1000;i++){}//for
	 RS4851_TX(1); RS4852_TX(1);
         RS4851_DE(1); RS4852_DE(1);
         for(int i=0;i<1000;i++){}//for
    return 0;
    }//send_bit_rs485
    int RESPONSEARRAY_RS485[16];
    for( int index=0; index<=7 ; index++ ){ RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( firstbyte >>(7 -index) ) ) & 1 ); }//for
    for( int index=8; index<=15; index++ ){ RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( secondbyte>>(15-index) ) ) & 1 ); }//for
    for( int index=0; index<=15; index++ ){ send_bit_rs485(  RESPONSEARRAY_RS485[index]  );                                  }//for
return 0;
}//write_response_rs485

//#################################

//execute
int execute_rs485( int cp ){
    int command  = (cp>>8) & 255;
    int parameter=  cp & 255;
    if(  command==PING ){ write_response_rs485(ACK,0); }//ACK...........Fault reporting mechanisms?
    if ( command==SON ){
                        int else_check=1;
                        if(parameter==PL5V_EN        ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);PL5V_EN   (1); }//ACK.... do action
                        if(parameter==ADCS5V_EN      ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);ADCS5V_EN (1); }//ACK.... do action
                        if(parameter==RS12V_EN       ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);RS12V_EN  (1); }//ACK.... do action
                        if(parameter==XB12V_EN       ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);XB12V_EN  (1); }//ACK.... do action
                        if(parameter==RS3V3_EN       ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);RS3V3_EN  (1); }//ACK.... do action
                        if(parameter==PL_EN          ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);PL_EN     (1); }//ACK.... do action
                        if(parameter==ADCS_EN        ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);ADCS_EN   (1); }//ACK.... do action
                        if(parameter==UHF_EN         ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);UHF_EN    (1); }//ACK.... do action
                        if(parameter==GPS_EN         ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);GPS_EN    (1); }//ACK.... do action
                        if(parameter==ADCS12V_EN     ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);ADCS12V_EN(1); }//ACK.... do action
                        if(else_check==1             ){                                write_response_rs485(NACK,0);               }//NACK
    }//SON
    if ( command==SOF ){
                        int else_check=1;
                        if(parameter==PL5V_EN        ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);PL5V_EN   (0); }//ACK.... do action
                        if(parameter==ADCS5V_EN      ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);ADCS5V_EN (0); }//ACK.... do action
                        if(parameter==RS12V_EN       ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);RS12V_EN  (0); }//ACK.... do action
                        if(parameter==XB12V_EN       ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);XB12V_EN  (0); }//ACK.... do action
                        if(parameter==RS3V3_EN       ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);RS3V3_EN  (0); }//ACK.... do action
                        if(parameter==PL_EN          ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);PL_EN     (0); }//ACK.... do action
                        if(parameter==ADCS_EN        ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);ADCS_EN   (0); }//ACK.... do action
                        if(parameter==UHF_EN         ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);UHF_EN    (0); }//ACK.... do action
                        if(parameter==GPS_EN         ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);GPS_EN    (0); }//ACK.... do action
                        if(parameter==ADCS12V_EN     ){else_check=0;CURRENTMODE=CUSTOM;write_response_rs485(ACK ,0);ADCS12V_EN(0); }//ACK.... do action
                        if(else_check==1             ){                                write_response_rs485(NACK,0);               }//NACK
    }//SOF
    if (  command==SM  ){
                         int else_check=1;
                         if(parameter==INITIALIZE    ){else_check=0;CURRENTMODE=INITIALIZE   ;write_response_rs485(ACK ,0);     }//ACK.... do action
                         if(parameter==DETUMBLE      ){else_check=0;CURRENTMODE=DETUMBLE     ;write_response_rs485(ACK ,0);     }//ACK.... do action
                         if(parameter==NORMAL        ){else_check=0;CURRENTMODE=NORMAL       ;write_response_rs485(ACK ,0);     }//ACK.... do action
                         if(parameter==COMMUNICATION ){else_check=0;CURRENTMODE=COMMUNICATION;write_response_rs485(ACK ,0);     }//ACK.... do action
                         if(parameter==PAYLOAD       ){else_check=0;CURRENTMODE=PAYLOAD      ;write_response_rs485(ACK ,0);     }//ACK.... do action
                         if(parameter==IMAGE         ){else_check=0;CURRENTMODE=IMAGE        ;write_response_rs485(ACK ,0);     }//ACK.... do action
                         if(parameter==EMERGENCY     ){else_check=0;CURRENTMODE=EMERGENCY    ;write_response_rs485(ACK ,0);     }//ACK.... do action
                         if(else_check==1            ){                                       write_response_rs485(NACK,0);     }//NACK
    }//SM
    if (  command==GM    ){ write_response_rs485(ACK,CURRENTMODE       ); }//ACK //GM
    if (  command==GSC   ){ write_response_rs485(ACK,CURRENTSYSTEMCLOCK); }//ACK.........MIGHT have to do away with 2 byte response limitation OR i can just specify what each count(1) represents as a time period for a 1 byte maximum
    if (  command==SSC   ){ write_response_rs485(ACK, 0  );CURRENTSYSTEMCLOCK=parameter; }//ACK
    if (  command==GOSTM ){
                             int a = (int) (XB12V_I  ()<<7);  int b = (int) (ADCS12V_I()<<6); int c = (int) (RS5V_I   ()<<5);  int d = (int) (RS3V3_I  ()<<4);
                             int e = (int) (SA1_I    ()<<3);  int f = (int) (SA2_I    ()<<2); int g = (int) (SA3_I    ()<<1);
                             write_response_rs485(  ACK, (int) (a | b | c | d | e | f | g |  1)    );
    }//ACK //GOSTM
    if ( command==KEN   ){ write_response_rs485(ACK,KEN ); }//ACK ...........shutting down all activity received from GCS or OBC //KEN
    if ( command==KDIS  ){ write_response_rs485(ACK,KDIS); }//ACK //KDIS
    //YOU CAN ALSO ADD LOGIC
return 0;
}//execute
	
//################# END RS485 METHODS ###################

//################# SPI1 METHODS ########################

int COMMAND_PARAMETER_SPI1=0;
int TWO_BYTE_RESPONSE_SPI1=0;
int receive_spi1(){ //external master clock
    int rx = 0;
    int   ss_3samples  =  SPI1_SS () +  SPI1_SS () +  SPI1_SS (); int   ss= 0; if(  ss_3samples>=2 ){  ss=1;}
    int  sck_3samples  =  SPI1_SCK() +  SPI1_SCK() +  SPI1_SCK(); int  sck= 0; if( sck_3samples>=2 ){ sck=1;}
    int mosi_3samples  = MOSI1_SCK() + MOSI1_SCK() + MOSI1_SCK(); int mosi= 0; if( sck_3samples>=2 ){mosi=1;}
    //miso guarantee
    if ( ss ){
	 if( ( sck) & ( mosi) ){rx=1;}//1
	 if( ( sck) & (!mosi) ){rx=0;}//0
	 if( (!sck) & ( mosi) ){rx=2;}//pause
	 if( (!sck) & (!mosi) ){rx=3;}//end
    }//if
return rx;
}//

//####################################

int write_response_spi1(int first, int second){ //external master clock
    void send_bit_spi1 (int bit){
	 int   ss_3samples  =  SPI1_SS () +  SPI1_SS () +  SPI1_SS (); int   ss= 0; if(  ss_3samples>=2 ){  ss=1;}
         int  sck_3samples  =  SPI1_SCK() +  SPI1_SCK() +  SPI1_SCK(); int  sck= 0; if( sck_3samples>=2 ){ sck=1;}
	 //miso guarantee
         if(   sck  &   bit ){ SPI1_MISO(1);}
	 if(   sck  & (!bit)){ SPI1_MISO(0);}
         if( (!sck) &   bit ){ SPI1_MISO(1);}
	 if( (!sck) & (!bit)){ SPI1_MISO(0);}
    }//send_bit
    int RESPONSEARRAY_RS485[16];
    for( int index=0; index<=7 ; index++ ){ RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( firstbyte >>(7 -index) ) ) & 1 ); }//for
    for( int index=8; index<=15; index++ ){ RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( secondbyte>>(15-index) ) ) & 1 ); }//for
    for( int index=0; index<=15; index++ ){ send_bit_rs485(  RESPONSEARRAY_RS485[index]  );                                  }//for
return rx;
}//

//NNNNNNNNNNNNNNNN
int write_response_rs485( int firstbyte, int secondbyte){
    void send_bit_rs485  (int bit){
         if(bit){ RS4851_TX(1); RS4852_TX(0); } else { RS4851_TX(0); RS4852_TX(1); }
         RS4851_DE(1); RS4852_DE(1);
         for(int i=0;i<1000;i++){}//for
	 RS4851_TX(1); RS4852_TX(1);
         RS4851_DE(1); RS4852_DE(1);
         for(int i=0;i<1000;i++){}//for
    }//send_bit_rs485
    int RESPONSEARRAY_RS485[16];
    for( int index=0; index<=7 ; index++ ){ RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( firstbyte >>(7 -index) ) ) & 1 ); }//for
    for( int index=8; index<=15; index++ ){ RESPONSEARRAY_RS485[index] = (int) ( ( (int) ( secondbyte>>(15-index) ) ) & 1 ); }//for
    for( int index=0; index<=15; index++ ){ send_bit_rs485(  RESPONSEARRAY_RS485[index]  );                                  }//for
return 0;
}//write_response_rs485
//NNNNNNNNNNNNNNNNN

//###################################

//get_command_parameter_after_leftShift_insertEnd_spi1
int get_command_parameter_after_leftShift_insertEnd_spi1(int insertionbit){
    COMMAND_PARAMETER_SPI1 = COMMAND_PARAMETER_SPI1<<1 ;
    COMMAND_PARAMETER_SPI1 = COMMAND_PARAMETER_SPI1 & ( 65534|insertionbit );
    return COMMAND_PARAMETER_SPI1;
}//get_command_parameter_after_leftShift_insertEnd_spi1

//###################################
	
//execute
int execute_spi1( int cp ){
    int command  = (cp>>8) & 255;
    int parameter=  cp & 255;
    if(  command==PING ){ TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0); }//ACK...........Fault reporting mechanisms?
    if ( command==SON ){
                        int else_check=1;
                        if(parameter==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);PL5V_EN   (1);  }//ACK.... do action
                        if(parameter==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);ADCS5V_EN (1);  }//ACK.... do action
                        if(parameter==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);RS12V_EN  (1);  }//ACK.... do action
                        if(parameter==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);XB12V_EN  (1);  }//ACK.... do action
                        if(parameter==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);RS3V3_EN  (1);  }//ACK.... do action
                        if(parameter==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);PL_EN     (1);  }//ACK.... do action
                        if(parameter==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);ADCS_EN   (1);  }//ACK.... do action
                        if(parameter==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);UHF_EN    (1);  }//ACK.... do action
                        if(parameter==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);GPS_EN    (1);  }//ACK.... do action
                        if(parameter==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);ADCS12V_EN(1);  }//ACK.... do action
                        if(else_check==1         ){                                TWO_BYTE_RESPONSE_SPI1 = (NACK<<8)|(0);                }//NACK
    }//SON
    if ( command==SOF ){
                        int else_check=1;
                        if(parameter==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);PL5V_EN   (0); }//ACK.... do action
                        if(parameter==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);ADCS5V_EN (0); }//ACK.... do action
                        if(parameter==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);RS12V_EN  (0); }//ACK.... do action
                        if(parameter==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);XB12V_EN  (0); }//ACK.... do action
                        if(parameter==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);RS3V3_EN  (0); }//ACK.... do action
                        if(parameter==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);PL_EN     (0); }//ACK.... do action
                        if(parameter==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);ADCS_EN   (0); }//ACK.... do action
                        if(parameter==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);GPS_EN    (0); }//ACK.... do action
                        if(parameter==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);GPS_EN    (0); }//ACK.... do action
                        if(parameter==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);ADCS12V_EN(0); }//ACK.... do action
                        if(else_check==1         ){                                TWO_BYTE_RESPONSE_SPI1 = (NACK<<8)|(0);               }//NACK
    }//SOF
    if (  command==SM  ){
                         int else_check=1;
                         if(parameter==INITIALIZE    ){else_check=0;CURRENTMODE=INITIALIZE   ;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);    }//ACK.... do action
                         if(parameter==DETUMBLE      ){else_check=0;CURRENTMODE=DETUMBLE     ;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);    }//ACK.... do action
                         if(parameter==NORMAL        ){else_check=0;CURRENTMODE=NORMAL       ;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);    }//ACK.... do action
                         if(parameter==COMMUNICATION ){else_check=0;CURRENTMODE=COMMUNICATION;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);    }//ACK.... do action
                         if(parameter==PAYLOAD       ){else_check=0;CURRENTMODE=PAYLOAD      ;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);    }//ACK.... do action
                         if(parameter==IMAGE         ){else_check=0;CURRENTMODE=IMAGE        ;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);    }//ACK.... do action
                         if(parameter==EMERGENCY     ){else_check=0;CURRENTMODE=EMERGENCY    ;TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0);    }//ACK.... do action
                         if(else_check==1            ){                                       TWO_BYTE_RESPONSE_SPI1 = (NACK<<8)|(0);    }//NACK
    }//SM
    if (  command==GM    ){ TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(CURRENTMODE       );                              }//ACK //GM
    if (  command==GSC   ){ TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(CURRENTSYSTEMCLOCK);                              }//ACK.........MIGHT have to do away with 2 byte response limitation OR i can just specify what each count(1) represents as a time period for a 1 byte maximum
    if (  command==SSC   ){ TWO_BYTE_RESPONSE_SPI1 = (ACK <<8)|(0                 );CURRENTSYSTEMCLOCK=parameter; }//ACK
    if (  command==GOSTM ){
                            int a = (int) (XB12V_I  ()<<7);  int b = (int) (ADCS12V_I()<<6); int c = (int) (RS5V_I   ()<<5);  int d = (int) (RS3V3_I  ()<<4);
                            int e = (int) (SA1_I    ()<<3);  int f = (int) (SA2_I    ()<<2); int g = (int) (SA3_I    ()<<1);
                            TWO_BYTE_RESPONSE_SPI1 = (  (ACK<<8)   |   ((int) (a | b | c | d | e | f | g |  1))    );
    }//ACK //GOSTM
    if ( command==KEN   ){ TWO_BYTE_RESPONSE_SPI1 = ((ACK << 8 )|(KEN )); }//ACK ...........shutting down all activity received from GCS or OBC //KEN
    if ( command==KDIS  ){ TWO_BYTE_RESPONSE_SPI1 = ((ACK << 8 )|(KDIS)); }//ACK //KDIS
    //YOU CAN ALSO ADD LOGIC
return 0;
}//execute

	
//################# END SPI1 METHODS ###################
	
//################# SPI3 METHODS ########################

int COMMAND_PARAMETER_SPI3=0;
int TWO_BYTE_RESPONSE_SPI3=0;
int spi3_bit_index=0;
int receive_bit_transmit_bit_spi3(){
    int rx = 0;
    int ss0  = SPI3_SS (); int ss1  = SPI3_SS (); int ss2  = SPI3_SS (); int ss =0; if((ss0 +ss1 +ss2 )>=2){ss =1;}
    int sck0 = SPI3_SCK(); int sck1 = SPI3_SCK(); int sck2 = SPI3_SCK(); int sck=0; if((sck0+sck1+sck2)>=2){sck=1;} 
    if ( ss & sck ){
         rx = SPI3_MOSI();
	 if(spi3_bit_index==16){spi3_bit_index=0;}
	 int tx_bit = (int) ( ( TWO_BYTE_RESPONSE_SPI3 >> (15-spi3_bit_index) ) & 1 );
	 SPI3_MISO( tx_bit );
	 spi3_bit_index = spi3_bit_index + 1;
    }//if
return rx;
}//

//####################################
	
//get_command_parameter_after_leftShift_insertEnd_spi3
int get_command_parameter_after_leftShift_insertEnd_spi3(int insertionbit){
    COMMAND_PARAMETER_SPI3 = COMMAND_PARAMETER_SPI3<<1 ;
    COMMAND_PARAMETER_SPI3 = COMMAND_PARAMETER_SPI3 & ( 65534|insertionbit );
    return COMMAND_PARAMETER_SPI3;
}//get_command_parameter_after_leftShift_insertEnd_spi3

//###################################
	
//execute
int execute_spi3( int cp ){
    int command  = (cp>>8) & 255;
    int parameter=  cp & 255;
    if(  command==PING ){ TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0); }//ACK...........Fault reporting mechanisms?
    if ( command==SON ){
                        int else_check=1;
                        if(parameter==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);PL5V_EN   (1);  }//ACK.... do action
                        if(parameter==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);ADCS5V_EN (1);  }//ACK.... do action
                        if(parameter==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);RS12V_EN  (1);  }//ACK.... do action
                        if(parameter==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);XB12V_EN  (1);  }//ACK.... do action
                        if(parameter==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);RS3V3_EN  (1);  }//ACK.... do action
                        if(parameter==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);PL_EN     (1);  }//ACK.... do action
                        if(parameter==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);ADCS_EN   (1);  }//ACK.... do action
                        if(parameter==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);UHF_EN    (1);  }//ACK.... do action
                        if(parameter==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);GPS_EN    (1);  }//ACK.... do action
                        if(parameter==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);ADCS12V_EN(1);  }//ACK.... do action
                        if(else_check==1         ){                                TWO_BYTE_RESPONSE_SPI3 = (NACK<<8)|(0);                }//NACK
    }//SON
    if ( command==SOF ){
                        int else_check=1;
                        if(parameter==PL5V_EN    ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);PL5V_EN   (0); }//ACK.... do action
                        if(parameter==ADCS5V_EN  ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);ADCS5V_EN (0); }//ACK.... do action
                        if(parameter==RS12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);RS12V_EN  (0); }//ACK.... do action
                        if(parameter==XB12V_EN   ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);XB12V_EN  (0); }//ACK.... do action
                        if(parameter==RS3V3_EN   ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);RS3V3_EN  (0); }//ACK.... do action
                        if(parameter==PL_EN      ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);PL_EN     (0); }//ACK.... do action
                        if(parameter==ADCS_EN    ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);ADCS_EN   (0); }//ACK.... do action
                        if(parameter==UHF_EN     ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);GPS_EN    (0); }//ACK.... do action
                        if(parameter==GPS_EN     ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);GPS_EN    (0); }//ACK.... do action
                        if(parameter==ADCS12V_EN ){else_check=0;CURRENTMODE=CUSTOM;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);ADCS12V_EN(0); }//ACK.... do action
                        if(else_check==1         ){                                TWO_BYTE_RESPONSE_SPI3 = (NACK<<8)|(0);               }//NACK
    }//SOF
    if (  command==SM  ){
                         int else_check=1;
                         if(parameter==INITIALIZE    ){else_check=0;CURRENTMODE=INITIALIZE   ;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);    }//ACK.... do action
                         if(parameter==DETUMBLE      ){else_check=0;CURRENTMODE=DETUMBLE     ;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);    }//ACK.... do action
                         if(parameter==NORMAL        ){else_check=0;CURRENTMODE=NORMAL       ;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);    }//ACK.... do action
                         if(parameter==COMMUNICATION ){else_check=0;CURRENTMODE=COMMUNICATION;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);    }//ACK.... do action
                         if(parameter==PAYLOAD       ){else_check=0;CURRENTMODE=PAYLOAD      ;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);    }//ACK.... do action
                         if(parameter==IMAGE         ){else_check=0;CURRENTMODE=IMAGE        ;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);    }//ACK.... do action
                         if(parameter==EMERGENCY     ){else_check=0;CURRENTMODE=EMERGENCY    ;TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0);    }//ACK.... do action
                         if(else_check==1            ){                                       TWO_BYTE_RESPONSE_SPI3 = (NACK<<8)|(0);    }//NACK
    }//SM
    if (  command==GM    ){ TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(CURRENTMODE       );                              }//ACK //GM
    if (  command==GSC   ){ TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(CURRENTSYSTEMCLOCK);                              }//ACK.........MIGHT have to do away with 2 byte response limitation OR i can just specify what each count(1) represents as a time period for a 1 byte maximum
    if (  command==SSC   ){ TWO_BYTE_RESPONSE_SPI3 = (ACK <<8)|(0                 );CURRENTSYSTEMCLOCK=parameter; }//ACK
    if (  command==GOSTM ){
                            int a = (int) (XB12V_I  ()<<7);  int b = (int) (ADCS12V_I()<<6); int c = (int) (RS5V_I   ()<<5);  int d = (int) (RS3V3_I  ()<<4);
                            int e = (int) (SA1_I    ()<<3);  int f = (int) (SA2_I    ()<<2); int g = (int) (SA3_I    ()<<1);
                            TWO_BYTE_RESPONSE_SPI3 = (  (ACK<<8)   |   ((int) (a | b | c | d | e | f | g |  1))    );
    }//ACK //GOSTM
    if ( command==KEN   ){ TWO_BYTE_RESPONSE_SPI3 = ((ACK << 8 )|(KEN )); }//ACK ...........shutting down all activity received from GCS or OBC //KEN
    if ( command==KDIS  ){ TWO_BYTE_RESPONSE_SPI3 = ((ACK << 8 )|(KDIS)); }//ACK //KDIS
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
int raw_input_i2c;
int previous_i2c;
int input_1_detected_i2c;
int input_0_detected_i2c;
//##
int raw_input_rs4851;
int previous_rs4851;
int input_1_detected_rs4851;
int input_0_detected_rs4851;
//##
int raw_input_rs4852;
int previous_rs4852;
int input_1_detected_rs4852;
int input_0_detected_rs4852;
//##
//MAIN LOOP
while(1){//while
	       //######## SPI1 ############
	       raw_input_spi1 = receive_bit_transmit_bit_spi1();
               if ( ((previous_spi1==1) & (raw_input_spi1==2)) |  ((previous_spi1==1) & (raw_input_spi1==3)) ){  input_1_detected_spi1=1;  }
	       if ( ((previous_spi1==0) & (raw_input_spi1==2)) |  ((previous_spi1==0) & (raw_input_spi1==3)) ){  input_0_detected_spi1=1;  }
               if ( input_1_detected_spi1 ){ input_1_detected_spi1=0; command_leftShift_insertEnd_spi1(1); execute_spi1( get_command_parameter_after_leftShift_insertEnd_spi1(1) ); }//if
               if ( input_0_detected_spi1 ){ input_0_detected_spi1=0; command_leftShift_insertEnd_spi1(0); execute_spi1( get_command_parameter_after_leftShift_insertEnd_spi1(0) ); }//if
               previous_spi1 = raw_input_spi1;
	       //######## END SPI1 ############
               //######## SPI3 ################
	       raw_input_spi3 = receive_bit_transmit_bit_spi1();
               if ( ((previous_spi3==1) & (raw_input_spi3==2)) |  ((previous_spi3==1) & (raw_input_spi3==3)) ){  input_1_detected_spi3=1;  }
	       if ( ((previous_spi3==0) & (raw_input_spi3==2)) |  ((previous_spi3==0) & (raw_input_spi3==3)) ){  input_0_detected_spi3=1;  }
               if ( input_1_detected_spi3 ){ input_1_detected_spi3=0; command_leftShift_insertEnd_spi3(1); execute_spi3( get_command_parameter_after_leftShift_insertEnd_spi3(1) ); }//if
               if ( input_0_detected_spi3 ){ input_0_detected_spi3=0; command_leftShift_insertEnd_spi3(0); execute_spi3( get_command_parameter_after_leftShift_insertEnd_spi3(0) ); }//if
               previous_spi3 = raw_input_spi3;
	       //######## END SPI3 ############
	       //######## I2C ############
	       raw_input_i2c = receive_bit_transmit_bit_i2c();
               if ( ((previous_i2c==1) & (raw_input_i2c==2)) |  ((previous_i2c==1) & (raw_input_i2c==3)) ){  input_1_detected_i2c=1;  }
	       if ( ((previous_i2c==0) & (raw_input_i2c==2)) |  ((previous_i2c==0) & (raw_input_i2c==3)) ){  input_0_detected_i2c=1;  }
               if ( input_1_detected_i2c ){ input_1_detected_i2c=0; command_leftShift_insertEnd_i2c(1); execute_i2c( get_command_parameter_after_leftShift_insertEnd_i2c(1) ); }//if
               if ( input_0_detected_i2c ){ input_0_detected_i2c=0; command_leftShift_insertEnd_i2c(0); execute_i2c( get_command_parameter_after_leftShift_insertEnd_i2c(0) ); }//if
               previous_i2c = raw_input_i2c;
	       //######## END I2C ############
	       //######## RS4851 ##############
	       raw_input_rs4851 = receive_bit_transmit_bit_rs4851();
               if ( ((previous_rs4851==1) & (raw_input_rs4851==2)) |  ((previous_rs4851==1) & (raw_input_rs4851==3)) ){  input_1_detected_rs4851=1;  }
	       if ( ((previous_rs4851==0) & (raw_input_rs4851==2)) |  ((previous_rs4851==0) & (raw_input_rs4851==3)) ){  input_0_detected_rs4851=1;  }
               if ( input_1_detected_rs4851 ){ input_1_detected_rs4851=0; command_leftShift_insertEnd_rs4851(1); execute_rs4851( get_command_parameter_after_leftShift_insertEnd_rs4851(1) ); }//if
               if ( input_0_detected_rs4851 ){ input_0_detected_rs4851=0; command_leftShift_insertEnd_rs4851(0); execute_rs4851( get_command_parameter_after_leftShift_insertEnd_rs4851(0) ); }//if
               previous_rs4851 = raw_input_rs4851;
	       //######## END RS4851 ############
	       //######## RS4852 ##############
	       raw_input_rs4852 = receive_bit_transmit_bit_rs4852();
               if ( ((previous_rs4852==1) & (raw_input_rs4852==2)) |  ((previous_rs4852==1) & (raw_input_rs4852==3)) ){  input_1_detected_rs4852=1;  }
	       if ( ((previous_rs4852==0) & (raw_input_rs4852==2)) |  ((previous_rs4852==0) & (raw_input_rs4852==3)) ){  input_0_detected_rs4852=1;  }
               if ( input_1_detected_rs4852 ){ input_1_detected_rs4852=0; command_leftShift_insertEnd_rs4852(1); execute_rs4852( get_command_parameter_after_leftShift_insertEnd_rs4851(1) ); }//if
               if ( input_0_detected_rs4852 ){ input_0_detected_rs4852=0; command_leftShift_insertEnd_rs4852(0); execute_rs4852( get_command_parameter_after_leftShift_insertEnd_rs4851(0) ); }//if
               previous_rs4852 = raw_input_rs4852;
	       //######## END RS4852 ############
}//while  
//MAIN LOOP
//#########################    END MAIN EVENT   #################################

return 0;
}//main
