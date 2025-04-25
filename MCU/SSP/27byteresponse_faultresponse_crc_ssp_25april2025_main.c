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
//                       flag, dest, src, cmd/resp , len, data, crc0, crc1, flag

//SSP output bit frame :   1    ,   1          , 8        , 8*16     ,  1
//                      start  ,  address=dest , ack/nack ,          ,  end

//SSP output bit frame :   1    ,   1          , 8  , 8     ,  1
//                      start  ,  address=dest , cmd , param ,  end



//mode actions, analogue reads(*_i), pause timing, 8bit ints


int main(){//main

    int ADC_CHANNEL_COUNT = 16;
    uint32_t adcValues[ADC_CHANNEL_COUNT];
    static void MX_ADC1_Init(void){
                ADC_ChannelConfTypeDef sConfig = {0};
                hadc1.Instance = ADC1;
                hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
                hadc1.Init.Resolution = ADC_RESOLUTION_12B;
                hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
                hadc1.Init.ContinuousConvMode = ENABLE;        // Enable continuous for auto-restart
                hadc1.Init.DiscontinuousConvMode = DISABLE;
                hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
                hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
                hadc1.Init.NbrOfConversion = ADC_CHANNEL_COUNT;
                hadc1.Init.DMAContinuousRequests = ENABLE;
                HAL_ADC_Init(&hadc1);
                uint32_t channels[] = {
                         ADC_CHANNEL_0 , ADC_CHANNEL_1 , ADC_CHANNEL_2 , ADC_CHANNEL_3 ,
                         ADC_CHANNEL_4 , ADC_CHANNEL_5 , ADC_CHANNEL_6 , ADC_CHANNEL_7 ,
                         ADC_CHANNEL_8 , ADC_CHANNEL_9 , ADC_CHANNEL_10, ADC_CHANNEL_11,
                         ADC_CHANNEL_12, ADC_CHANNEL_13, ADC_CHANNEL_14, ADC_CHANNEL_15
                };
    for (int i = 0; i < ADC_CHANNEL_COUNT; i++) {
          sConfig.Channel = channels[i];
          sConfig.Rank = i + 1;
          sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
          HAL_ADC_ConfigChannel(&hadc1, &sConfig);
    }//for
    }//MX_ADC1_Init
    HAL_ADC_Start_DMA(&hadc1, adcValues, ADC_CHANNEL_COUNT);\
    //HAL_ADC_Stop_DMA(&hadc1);
    float voltages[ADC_CHANNEL_COUNT];
    for (int i = 0; i < ADC_CHANNEL_COUNT; i++) {
    voltages[i] = (adcValues[i] / 4095.0f) * 3.3f;
    }//for

    struct ninebyte   { int byte1; int byte2; int byte3; int byte4; int byte5; int byte6; int byte7; int byte8; int byte9; };
    struct fourbyte   { int byte1; int byte2; int byte3; int byte4; };
    struct twobyte    { int byte1; int byte2; };
    // add const def	
    //############ DECLARATIONS ###########
    const int EPS_MCU_ADDRESS=2;
    //Boolean
    const int HIGH    = 1 ;  
    const int TRUE    = 1 ;
    const int ONE     = 1 ;
    const int LOW     = 0 ;  
    const int FALSE   = 0 ;
    const int ZERO    = 0 ;
    const int PAUSE   = 2 ;
    const int END     = 3 ;
    //TRANSMISSION AND RECEPTION (COMMUNICATION) SYMBOLS
    const int EMPTY           = 0   ;
    const int PING            = 34  ; //command
    const int ACK             = 47  ;
    const int ACKNOWLEDGE     = 47  ;
    const int FLT             = 85  ;
    const int NACK            = 52  ;
    const int NOT_ACKNOWLEDGE = 52  ;
    const int SON             = 140 ;
    const int SWITCH_ON       = 140 ;
    const int UHF             = 24  ; //parameter
    const int ADCS            = 162 ; //parameter
    const int GPS             = 75  ; //parameter
    const int SOF             = 218 ;
    const int SWITCH_OFF      = 218 ; //command
    const int SM              = 107 ;
    const int SET_MODE        = 107 ; //command
    const int GM              = 122 ;
    const int GET_MODE        = 122 ; //command
    const int GSC             = 94  ;
    const int GET_SYSTEM_CLOCK= 94  ; //command
    const int SSC             = 209 ; 
    const int SET_SYSTEM_CLOCK= 209 ; //command
    const int GFP             = 134 ; //command
    const int SFP             = 90  ; //command
    const int FON             = 55  ; 
    const int FUNCTION_ON     = 55  ; //command
    const int TWELVEBUS       = 100 ; //telemetry parameter
    const int FIVEBUS         = 150 ; //telemetry parameter
    const int THREEBUS        = 200 ; //parameter
    const int FOF             = 233 ; 
    const int FUNCTION_OFF    = 233 ; //command
    const int GOSTM           = 157 ;
    const int GET_ONLINE_SYSTEM_TELEMETRY = 157; //command
    const int KEN             = 255 ;
    const int KILL_ENABLE     = 255 ; //command
    const int KDIS            = 227 ;
    const int KILL_DISABLE    = 227 ; //command
    const int GD              = 15  ;
    const int GET_DATA        = 15  ; //command
    const int PD              = 245 ;
    const int PUT_DATA        = 245 ; //command
    const int RD              = 222 ; 
    const int READ_DATA       = 222 ; //command
    const int WD              = 133 ; 
    const int WRITE_DATA      = 133 ; //command
    const int INITIALIZE      = 60  ; //mode parameter
    const int DETUMBLE        = 71  ; //mode parameter
    const int NORMAL          = 82  ; //mode parameter
    const int COMMUNICATION   = 93  ; //mode parameter
    const int PAYLOAD         = 104 ; //mode parameter
    const int IMAGE           = 115 ; //mode parameter
    const int EMERGENCY       = 126 ; //mode parameter
    const int CUSTOM          = 69  ; //mode parameter
    const int PL5V_EN           = 230      ; 
    const int PAYLOAD_5V_ENABLE = 230      ; //pin
    const int ADCS5V_EN         = 143      ;
    const int ADCS_5V_ENABLE    = 143      ; //pin
    const int RS12V_EN          = 205      ;
    const int RESERVED_12V_EN   = 205      ; //pin
    const int XB12V_EN          = 139      ;
    const int XBAND_12V_ENABLE  = 139      ; //pin
    const int CCU5V_EN          = 155      ; 
    const int CENTRAL_COMMAND_UNIT_5V_ENABLE = 155 ; //pin
    const int RS3V3_EN          = 212      ;
    const int RESERVED_3V_ENABLE= 212      ; //pin
    const int PL_EN             = 172      ;
    const int PAYLOAD_ENABLE    = 172      ; //pin
    const int ADCS_EN           = 144      ;
    const int ADCS_ENABLE       = 144      ; //pin
    const int UHF_EN            = 189      ;
    const int UHF_ENABLE        = 189      ; //pin
    const int GPS_EN            = 57       ;
    const int GPS_ENABLE        = 57       ; //pin
    const int ADCS12V_EN        = 199      ; 
    const int ADCS_12V_ENABLE   = 199      ; //pin
    const int EPS_EN            = 97       ; 
    const int EPS_ENABLE        = 97       ;//funny

//############## PINS ##################

int  SA1_I      ()          {    return  (int)((adcValues[0] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_0         );} //current reading from SA1  .............................................. PA0
int  SA2_I      ()          {    return  (int)((adcValues[1] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_1         );} //current reading from SA2  .............................................. PA1
int  SA3_I      ()          {    return  (int)((adcValues[2] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_2         );} //current reading from SA3  .............................................. PA2
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
int  OBC_I      ()          {    return  (int)((adcValues[9 ] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_1         );} //     ....................................................................PB1
int  CCU_I      ()          {    return  (int)((adcValues[5 ] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_5         );} //     ....................................................................PA5
int  ADCS_I     ()          {    return  (int)((adcValues[7 ] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_7         );} //     ....................................................................PA7
int  ADCS_FAULT ()          {return HAL_GPIO_ReadPin ( GPIOD, GPIO_PIN_0         );} //if read LOW then fault, else no fault                ....................PD0
void ADCS_EN    (int value) {       HAL_GPIO_WritePin( GPIOA, GPIO_PIN_12, value );} //if write HIGH then enable, if write LOW then disable ....................PA12
int  UHF_I      ()          {    return  (int)((adcValues[8 ] / 4095.0f) * 3.3f);   }//{    return  (int)((adcValues[0] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_0         );} //              ..........................PB0
int  UHF_FLT    ()          {return HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_4         );} //if read LOW then fault, else no fault              ......................PB4
void UHF_EN     (int value) {       HAL_GPIO_WritePin( GPIOD, GPIO_PIN_7 , value );} //        .................................................................PD7
int  PL_I       ()          {    return  (int)((adcValues[14] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_4         );} //        .................................................................PC4
int  PL_FLT     ()          {return HAL_GPIO_ReadPin ( GPIOD, GPIO_PIN_14        );} //if read LOW then fault, else no fault  ..................................PD14
void PL_EN      (int value) {       HAL_GPIO_WritePin( GPIOD, GPIO_PIN_13, value );} //                                       ..................................PD13
int  RS3V3_I    ()          {    return  (int)((adcValues[6 ] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_6         );} //                                       ..................................PA6
int  RS3V3_FLT  ()          {return HAL_GPIO_ReadPin ( GPIOD, GPIO_PIN_8         );} //if read LOW then fault, else no fault  ..................................PD8
void RS3V3_EN   (int value) {       HAL_GPIO_WritePin( GPIOB, GPIO_PIN_15        );} //if write HIGH then enable, if write LOW then disable     ................PB15
int  GPS_I      ()          {    return  (int)((adcValues[13] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_3         );} //                                                 ........................PC3
int  GPS_FLT    ()          {return HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_5         );} //if read LOW then fault, else no fault                       .............PB5
void GPS_EN     (int value) {       HAL_GPIO_WritePin( GPIOB, GPIO_PIN_6,  value );} //if write HIGH then enable, if write LOW then disable        .............PB6
int  ADCS5V_I   ()          {    return  (int)((adcValues[12] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_2         );} //                                                        .................PC2
int  ADCS5V_FLT ()          {return HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_9         );} //if read LOW then fault, else no fault                     ...............PB9
void ADCS5V_EN  (int value) {       HAL_GPIO_WritePin( GPIOE, GPIO_PIN_4,  value );} //if write HIGH then enable, if write LOW then disable      ...............PE4
int  PL5V_I     ()          {    return  (int)((adcValues[11] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_1         );} //                                                     ....................PC1
int  PL5V_FLT   ()          {return HAL_GPIO_ReadPin ( GPIOE, GPIO_PIN_0         );} //if read LOW then fault, else no fault                       .............PE0
void PL5V_EN    (int value) {       HAL_GPIO_WritePin( GPIOE, GPIO_PIN_3,  value );} //if write HIGH then enable, if write LOW then disable        .............PE3
int  CCU5V_I    ()          {    return  (int)((adcValues[4 ] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_4         );} //                                                   ......................PA4
int  CCU5V_FLT  ()          {return HAL_GPIO_ReadPin ( GPIOE, GPIO_PIN_11        );} //if read LOW then fault, else no fault         ...........................PE11
void CCU5V_EN   (int value) {       HAL_GPIO_WritePin( GPIOE, GPIO_PIN_10, value );} //if write HIGH then enable, if write LOW then disable                 ....PE10
int  XB12V_I    ()          {    return  (int)((adcValues[3 ] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOA, GPIO_PIN_3         );} //                                      ...................................PA3
int  XB12V_FLT  ()          {return HAL_GPIO_ReadPin ( GPIOE, GPIO_PIN_9         );} //if read LOW then fault, else no fault               .....................PE9
void XB12V_EN   (int value) {       HAL_GPIO_WritePin( GPIOE, GPIO_PIN_8,  value );} //if write HIGH then enable, if write LOW then disable          ...........PE8
int  ADCS12V_FLT()          {return HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_7         );} //if read LOW then fault, else no fault                      ..............PB7
int  ADCS12V_I  ()          {    return  (int)((adcValues[15] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_5         );} //                                                  .......................PC5
void ADCS12V_EN (int value) {       HAL_GPIO_WritePin( GPIOB, GPIO_PIN_8,  value );} //if write HIGH then enable, if write LOW then disable           ..........PB8
int  RS12V_FLT  ()          {return HAL_GPIO_ReadPin ( GPIOE, GPIO_PIN_7         );} //if read LOW then fault, else no fault                    ................PE7
void RS12V_EN   (int value) {       HAL_GPIO_WritePin( GPIOB, GPIO_PIN_2,  value );} //if write HIGH then enable, if write LOW then disable          ...........PB2
int  RS5V_FLT   ()          {return HAL_GPIO_ReadPin ( GPIOE, GPIO_PIN_1         );} //if read LOW then fault, else no fault               .....................PE1
int  RS5V_I     ()          {    return  (int)((adcValues[10] / 4095.0f) * 3.3f);   }//{return HAL_GPIO_ReadPin ( GPIOC, GPIO_PIN_0         );} //                                           ..............................PC0
void RS5V_EN    (int value) {       HAL_GPIO_WritePin( GPIOE, GPIO_PIN_2 , value );} //if write HIGH then enable, if write LOW then disable       ..............PE2
// other variables
const int RESPONSE_WAIT            = 10000;//response_wait()
const int CURRENTMODE              = 0;
const int CURRENTSYSTEMCLOCK       = 0;
const int FF                       = 255;
const int OBC_ADDRESS              = 1  ; const int OBC = 1;
const int CCU_ADDRESS              = 3  ; const int CCU = 3;
const int EPS_ADDRESS              = 2  ; const int EPS = 2;
const int ADCSFLT   =100;
const int UHFFLT    =101;
const int PLFLT     =102;
const int RS3V3FLT  =103;
const int GPSFLT    =104;
const int ADCS5VFLT =105;
const int PL5VFLT   =106;
const int CCU5VFLT  =107;
const int XB12VFLT  =108;
const int ADCS12VFLT=109;
const int RS12VFLT  =110;
const int RS5VFLT   =111;
//#######################

//response_wait
int response_wait(){
    for( int count=0;  count<=RESPONSE_WAIT ;count++ ){ }//do nothing
    //HAL delay could work too
return 0;
}//response_wait

//########################

struct twobyte crc16_generator(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, 
                               int k, int l, int m, int n, int o, int p, int q, int r, int s, int t,
                               int u, int v, int w, int x, int y, int z, int A, int B, int C, int D, 
                               int E)
                              { //dest, src, cmd/resp , len, data[27] excluding 2 flags and 2 crcs
                              struct twobyte rslt;
                              int number_of_bits = (4*8) + (d*8) + 16; // (first4*8) + (len*8) +padding16
                              int bits[ number_of_bits ];//total bits for 4 basic and [d] length data
                              for(int i=0 ; i<=7  ;  i++){bits[i]=((a>>(7 -i))&1);}
                              for(int i=8 ; i<=15 ;  i++){bits[i]=((b>>(15-i))&1);}
                              for(int i=16; i<=23 ;  i++){bits[i]=((c>>(23-i))&1);}
                              for(int i=24; i<=31 ;  i++){bits[i]=((d>>(31-i))&1);}
                              if ( (d>=1 ) ) { for(int i=24 ; i<=31 ;  i++){bits[i]=((e>>(31 -i))&1);} }
                              if ( (d>=2 ) ) { for(int i=32 ; i<=39 ;  i++){bits[i]=((f>>(39 -i))&1);} }
                              if ( (d>=3 ) ) { for(int i=40 ; i<=47 ;  i++){bits[i]=((g>>(47 -i))&1);} }
                              if ( (d>=4 ) ) { for(int i=48 ; i<=55 ;  i++){bits[i]=((h>>(55 -i))&1);} }
                              if ( (d>=5 ) ) { for(int i=56 ; i<=63 ;  i++){bits[i]=((i>>(63 -i))&1);} }
                              if ( (d>=6 ) ) { for(int i=64 ; i<=71 ;  i++){bits[i]=((j>>(71 -i))&1);} }
                              if ( (d>=7 ) ) { for(int i=72 ; i<=79 ;  i++){bits[i]=((k>>(79 -i))&1);} }
                              if ( (d>=8 ) ) { for(int i=80 ; i<=87 ;  i++){bits[i]=((l>>(87 -i))&1);} }
                              if ( (d>=9 ) ) { for(int i=88 ; i<=95 ;  i++){bits[i]=((m>>(95 -i))&1);} }
                              if ( (d>=10) ) { for(int i=96 ; i<=103;  i++){bits[i]=((n>>(103-i))&1);} }
                              if ( (d>=11) ) { for(int i=104; i<=111;  i++){bits[i]=((o>>(111-i))&1);} }
                              if ( (d>=12) ) { for(int i=112; i<=119;  i++){bits[i]=((p>>(119-i))&1);} }
                              if ( (d>=13) ) { for(int i=120; i<=127;  i++){bits[i]=((q>>(127-i))&1);} }
                              if ( (d>=14) ) { for(int i=128; i<=135;  i++){bits[i]=((r>>(135-i))&1);} }
                              if ( (d>=15) ) { for(int i=136; i<=143;  i++){bits[i]=((s>>(143-i))&1);} }
                              if ( (d>=16) ) { for(int i=144; i<=151;  i++){bits[i]=((t>>(151-i))&1);} }
                              if ( (d>=17) ) { for(int i=152; i<=159;  i++){bits[i]=((u>>(159-i))&1);} }
                              if ( (d>=18) ) { for(int i=160; i<=167;  i++){bits[i]=((v>>(167-i))&1);} }
                              if ( (d>=19) ) { for(int i=168; i<=175;  i++){bits[i]=((w>>(175-i))&1);} }
                              if ( (d>=20) ) { for(int i=176; i<=183;  i++){bits[i]=((x>>(183-i))&1);} }
                              if ( (d>=21) ) { for(int i=184; i<=191;  i++){bits[i]=((y>>(191-i))&1);} }
                              if ( (d>=22) ) { for(int i=192; i<=199;  i++){bits[i]=((z>>(199-i))&1);} }
                              if ( (d>=23) ) { for(int i=200; i<=207;  i++){bits[i]=((A>>(207-i))&1);} }
                              if ( (d>=24) ) { for(int i=208; i<=215;  i++){bits[i]=((B>>(215-i))&1);} }
                              if ( (d>=25) ) { for(int i=216; i<=223;  i++){bits[i]=((C>>(223-i))&1);} }
                              if ( (d>=26) ) { for(int i=224; i<=231;  i++){bits[i]=((D>>(231-i))&1);} }
                              if ( (d>=27) ) { for(int i=232; i<=239;  i++){bits[i]=((E>>(239-i))&1);} }
                              int lastitemindex = ( number_of_bits - 1); int firstitemindex = lastitemindex - 15;
                              for(int i = firstitemindex; i<= lastitemindex ; i++){     bits[i] = 0;   }//16 padding
                              int poly[17] = {1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1};//msb(left) to lsb(right)
			      int number_of_ones_in_sequence=0;
			      for(int i=0;i<number_of_bits;i++){   if(bits[i]==1){ number_of_ones_in_sequence = number_of_ones_in_sequence+1; }       }
                              int indices_of_ones_in_bit_sequence [number_of_ones_in_sequence]; for(int i=0;i<number_of_bits;i++){   if(bits[i]==1){ indices_of_ones_in_bit_sequence[i] = i; }      }
                              for(int i=0;i<number_of_ones_in_sequence;i++){
							                   //bits [  indices_of_ones_in_bit_sequence [ i+0 ]   ] = bits[  indices_of_ones_in_bit_sequence [ i+0 ]   ] ^ poly[0+0];
							                   //bits [  indices_of_ones_in_bit_sequence [ i+1 ]   ] = bits[  indices_of_ones_in_bit_sequence [ i+1 ]   ] ^ poly[0+1];
							                   //bits [  indices_of_ones_in_bit_sequence [ i+2 ]   ] = bits[  indices_of_ones_in_bit_sequence [ i+2 ]   ] ^ poly[0+2];
		                                                           for(int k=0;k<=16;k++) {     bits [  indices_of_ones_in_bit_sequence [ i+k ]   ] = (bits[  indices_of_ones_in_bit_sequence [ i+k ]   ] ^ poly[ k ]);    }
                              }//for
                              rslt.byte1 = (bits[ lastitemindex-15 ]*128)+(bits[ lastitemindex-14 ]*64)+(bits[ lastitemindex-13 ]*32)+(bits[ lastitemindex-12 ]*16)+(bits[ lastitemindex-11 ]*8)+(bits[ lastitemindex-10 ]*4)+(bits[ lastitemindex-9 ]*2)+(bits[ lastitemindex-8 ] );
                              rslt.byte2 = (bits[ lastitemindex-7  ]*128)+(bits[ lastitemindex-6  ]*64)+(bits[ lastitemindex-5  ]*32)+(bits[ lastitemindex-4  ]*16)+(bits[ lastitemindex-3  ]*8)+(bits[ lastitemindex-2  ]*4)+(bits[ lastitemindex-1 ]*2)+(bits[ lastitemindex   ] );
return rslt;
}//crc_generator_for_5byte
	
//################# RS485 METHODS/DECLARATIONS ###################

struct ninebyte COMMAND_PARAMETER_RS485  = {0,0,0,0,0,0,0,0,0};
  
int receive_rs485 (){
    int result=0; int r4851=0; int r4852=0;
    RS4851_DE(0); RS4852_DE(0);
    if( (RS4851_RX()+RS4851_RX()+RS4851_RX())>=2 ){r4851=1;}
    if( (RS4852_RX()+RS4852_RX()+RS4852_RX())>=2 ){r4852=1;}
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
int execute_rs485(struct ninebyte input ){ //flag[1], dest[2], src[3], cmd/response[4] , len[5], data[6], crc0[7], crc1[8], flag[9]
    int    source      = input.byte3;
    int    destination = input.byte2;
    int    from_obc_or_from_ccu_to_eps = (int)(  ((source==OBC_ADDRESS)|(source==CCU_ADDRESS)) & (destination==EPS_ADDRESS)  );//who can talk to the EPS MCU
    int    proper_ssp_frame  = 1;//set to 1 is easier
    struct twobyte received_crc = crc16_generator (input.byte2, input.byte3, input.byte4, input.byte5, input.byte6,
                                                   0,0,0,0,0,   0,0,0,0,0,   0,0,0,0,0,   0,0,0,0,0,   0,0,0,0,0,   0); //let's regenerate the crc if the command frame is: dest,src,cmd,len,data1
    int    valid_crc = (received_crc.byte1==input.byte7)&(received_crc.byte2==input.byte8);
    if (valid_crc & from_obc_or_from_ccu_to_eps & proper_ssp_frame) {//proceed
                         int  command  = input.byte4; int parameter= input.byte6;
                         void pause_rs485(int symbol_duration){
			      void DWT_Init(void) {
                              CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
                              DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
                              }
                              void delay_us(uint32_t us) {
                              uint32_t cycles_per_us = HAL_RCC_GetHCLKFreq() / 1000000;
                              uint32_t start = DWT->CYCCNT;
                              uint32_t delay_cycles = us * cycles_per_us;
                              while ((DWT->CYCCNT - start) < delay_cycles);
                              }
                              DWT_Init();
                              delay_us(symbol_duration);  // 52080ms rep 52.08us rep 9600bps rep 19200symbols per s
			 }//mada mada
                         void send_bit_rs485 (int bit){// 
                              if(bit){ RS4851_TX(1); RS4852_TX(1); } else { RS4851_TX(0); RS4852_TX(0); }
                              RS4851_DE(1); RS4852_DE(1);
                              pause_rs485(1000);
                              RS4851_TX(0); RS4852_TX(1);
                              pause_rs485(1000);
	                      RS4851_DE(0);RS4852_DE(0);//may or may not be appropriate...revisit
                         }//send_bit_rs485
                         void send_byte_rs485( int out ){      for( int index= 0; index<= 7; index++ ){  send_bit_rs485( (int) ( ( (int) ( out >>(7 -index) ) ) & 1 ) ); }       }//send_byte_rs485
                         int  write_ssp_response_rs485( int dest, int src, int resp, int len,
                                                        int d1  , int d2 , int d3  , int d4 ,
                                                        int d5  , int d6 , int d7  , int d8 ,
                                                        int d9  , int d10, int d11 , int d12,
                                                        int d13 , int d14, int d15 , int d16,
                                                        int d17 , int d18, int d19 , int d20,
                                                        int d21 , int d22, int d23 , int d24,
                                                        int d25 , int d26, int d27 ) { //flag, dest, src, cmd/response , len, data, crc0, crc1, flag
			                                struct twobyte crc16 = crc16_generator(dest,src,resp,len,
                                                                                               d1 ,d2 ,d3 ,d4 ,d5 ,d6 ,d7 ,d8 ,d9 ,
                                                                                               d10,d11,d12,d13,d14,d15,d16,d17,d18,
                                                                                               d19,d20,d21,d22,d23,d24,d25,d26,d27);
	                                                if(len==0 ){send_byte_rs485( FF );send_byte_rs485( dest );send_byte_rs485( src );send_byte_rs485( resp );send_byte_rs485( len );send_byte_rs485( FF  );}// NO CRC generated
	                                                if(len==1 ){send_byte_rs485( FF   );
                                                                    send_byte_rs485( dest );send_byte_rs485( src        );send_byte_rs485( resp       );send_byte_rs485( len );
                                                                    send_byte_rs485( d1   );send_byte_rs485( crc16.byte1);send_byte_rs485( crc16.byte2);send_byte_rs485( FF   );
                                                        }//len 1
	                                                if(len==27){send_byte_rs485( FF );send_byte_rs485( dest );send_byte_rs485( src );send_byte_rs485( resp );send_byte_rs485( len ); 
		                                                    send_byte_rs485( d1 );send_byte_rs485( d2   );send_byte_rs485( d3  );send_byte_rs485( d4   );send_byte_rs485( d5  );send_byte_rs485( d6  );
                                                                    send_byte_rs485( d7 );send_byte_rs485( d8   );send_byte_rs485( d9  );send_byte_rs485( d10  );send_byte_rs485( d11 );send_byte_rs485( d12 );
                                                                    send_byte_rs485( d13);send_byte_rs485( d14  );send_byte_rs485( d15 );send_byte_rs485( d16 ); send_byte_rs485( d17 );send_byte_rs485( d18 );
                                                                    send_byte_rs485( d19);send_byte_rs485( d20  );send_byte_rs485( d21 );send_byte_rs485( d22 ); send_byte_rs485( d23 );send_byte_rs485( d24 );
                                                                    send_byte_rs485( d25);send_byte_rs485( d26  );send_byte_rs485( d27 );
                                                                    send_byte_rs485( crc16.byte1);                send_byte_rs485( crc16.byte2);                 send_byte_rs485( FF  );
                                                        }//len 27        
                         return 0;
                         }//write_ssp_response_rs485
                         int check_command   (int cmd  ){  if ( command  ==cmd   ){ return 1; }else{ return 0;}  }//check_command
	                 int check_parameter (int param){  if ( parameter==param ){ return 1; }else{ return 0;}  }//check_input
                         if (check_command(PING) ){ write_ssp_response_rs485( OBC,EPS,ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,   0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//ACK...........Fault reporting mechanisms? flag, dest, src, cmd/resp , len, data, crc0, crc1, flag
                         if (check_command(SON ) ){ int else_check=1;
                                                    if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);PL5V_EN   (1); }//ACK.... do action
                                                    if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS5V_EN (1); }//ACK.... do action
                                                    if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);RS12V_EN  (1); }//ACK.... do action
                                                    if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);XB12V_EN  (1); }//ACK.... do action
                                                    if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);RS3V3_EN  (1); }//ACK.... do action
                                                    if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);PL_EN     (1); }//ACK.... do action
                                                    if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS_EN   (1); }//ACK.... do action
                                                    if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);UHF_EN    (1); }//ACK.... do action
                                                    if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);GPS_EN    (1); }//ACK.... do action
                                                    if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS12V_EN(1); }//ACK.... do action
                                                    if(else_check==1                ){                                write_ssp_response_rs485( OBC,EPS,NACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);               }//NACK
                         }//SON
                         if ( check_command(SOF) ){ int else_check=1;
                                                    if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);PL5V_EN   (0); }//ACK.... do action
                                                    if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS5V_EN (0); }//ACK.... do action
                                                    if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);RS12V_EN  (0); }//ACK.... do action
                                                    if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);XB12V_EN  (0); }//ACK.... do action
                                                    if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);RS3V3_EN  (0); }//ACK.... do action
                                                    if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);PL_EN     (0); }//ACK.... do action
                                                    if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS_EN   (0); }//ACK.... do action
                                                    if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);UHF_EN    (0); }//ACK.... do action
                                                    if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);GPS_EN    (0); }//ACK.... do action
                                                    if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS12V_EN(0); }//ACK.... do action
                                                    if(else_check==1                ){                                write_ssp_response_rs485( OBC,EPS,NACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);               }//NACK
                        }//SOF
                        if ( check_command(SM )  ){ int else_check=1;
                                                    if(check_parameter( INITIALIZE    ) ){else_check=0;CURRENTMODE=INITIALIZE   ;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( DETUMBLE      ) ){else_check=0;CURRENTMODE=DETUMBLE     ;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( NORMAL        ) ){else_check=0;CURRENTMODE=NORMAL       ;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( COMMUNICATION ) ){else_check=0;CURRENTMODE=COMMUNICATION;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( PAYLOAD       ) ){else_check=0;CURRENTMODE=PAYLOAD      ;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( IMAGE         ) ){else_check=0;CURRENTMODE=IMAGE        ;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( EMERGENCY     ) ){else_check=0;CURRENTMODE=EMERGENCY    ;write_ssp_response_rs485( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(else_check==1                    ){                                       write_ssp_response_rs485( OBC,EPS,NACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//NACK
                        }//SM
                        if ( check_command(GM   ) ){  write_ssp_response_rs485( OBC,EPS, ACK,1,CURRENTMODE       ,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);   }//ACK........ dest, src, cmd/response , len, data,
                        if ( check_command(GSC  ) ){  write_ssp_response_rs485( OBC,EPS, ACK,1,CURRENTSYSTEMCLOCK,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);   }//ACK........ dest, src, cmd/response , len, data,
                        if ( check_command(SSC  ) ){  write_ssp_response_rs485( OBC,EPS, ACK,0,                 0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); CURRENTSYSTEMCLOCK=input.byte6; }//ACK
                        if ( check_command(GOSTM) ){  //current range / 255 = current value for a step of 1
				                      int d1  =0;//SA1_I      ();
				                      int d2  =0;//SA2_I      (); 
                                                      int d3  =0;//SA3_I      (); 
	   		                              int d4  =0;//OBC_I      ();
			                              int d5  =0;//CCU_I      ();   
			                              int d6  =0;//ADCS_I     (); 
	                     			      int d7  =0;//UHF_I      ();  
			     			      int d8  =0;//PL_I       ();  
			    			      int d9  =0;//RS3V3_I    ();        
			   			      int d10 =0;//GPS_I      ();    
			   		              int d11 =0;//ADCS5V_I   ();  
						      int d12 =0;//PL5V_I     ();  
			  			      int d13 =0;//CCU5V_I    ();  
						      int d14 =0;//XB12V_I    ();   
						      int d15 =0;//ADCS12V_I  ();  
						      int d16 =0;//RS5V_I     ();
	                                              int d17 = ( (OBC_FAULT()<<7) | (CCU_FAULT() <<6)  | (RS12V_FLT()<<5) | (RS5V_FLT ()<<4) | (ADCS_FAULT()<<3) | (UHF_FLT    ()<<2)| (PL_FLT()<<1) | RS3V3_FLT  () );
	                                              int d18 = ( (GPS_FLT  ()<<7) | (ADCS5V_FLT()<<6)  | (PL5V_FLT ()<<5) | (CCU5V_FLT()<<4) | (XB12V_FLT ()<<3) | (ADCS12V_FLT()<<2)|  3                            );
				                      int d19 =0;//bat
				                      int d20 =0;//bat
				                      int d21 =0;//bat
				                      int d22 =0;//bat
				                      int d23 =0;//bat
				                      int d24 =0;//bat
				                      int d25 =0;//bat
				                      int d26 =0;//bat
				                      int d27 =0;//bat
                                                      write_ssp_response_rs485( OBC,EPS, ACK,27,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16,d17,d18,d19,d20,d21,d22,d23,d24,d25,d26,d27);
                        }//ACK //GOSTM
                        if ( check_command(KEN ) ){ write_ssp_response_rs485( OBC,EPS, ACK,1,KEN ,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//ACK ...........shutting down all activity received from GCS or OBC //KEN
                        if ( check_command(KDIS) ){ write_ssp_response_rs485( OBC,EPS, ACK,1,KDIS,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//ACK //KDIS
                        //YOU CAN ALSO ADD LOGIC
}//if proceed
if ( (OBC_FAULT  ()+OBC_FAULT  ()+OBC_FAULT  ())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1,    OBCFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if    
if ( (CCU_FAULT  ()+CCU_FAULT  ()+CCU_FAULT  ())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1,    CCUFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if    
if ( (ADCS_FAULT ()+ADCS_FAULT ()+ADCS_FAULT ())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1,   ADCSFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if    
if ( (UHF_FLT    ()+UHF_FLT    ()+UHF_FLT    ())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1,    UHFFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (PL_FLT     ()+PL_FLT     ()+PL_FLT     ())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1,     PLFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if    
if ( (RS3V3_FLT  ()+RS3V3_FLT  ()+RS3V3_FLT  ())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1,  RS3V3FLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (GPS_FLT    ()+GPS_FLT    ()+GPS_FLT    ())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1,    GPSFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if     
if ( (ADCS5V_FLT ()+ADCS5V_FLT ()+ADCS5V_FLT ())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1, ADCS5VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (PL5V_FLT   ()+PL5V_FLT   ()+PL5V_FLT   ())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1,   PL5VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (CCU5V_FLT  ()+CCU5V_FLT  ()+CCU5V_FLT  ())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1,  CCU5VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (XB12V_FLT  ()+XB12V_FLT  ()+XB12V_FLT  ())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1,  XB12VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (ADCS12V_FLT()+ADCS12V_FLT()+ADCS12V_FLT())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1,ADCS12VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (RS12V_FLT  ()+RS12V_FLT  ()+RS12V_FLT  ())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1,  RS12VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (RS5V_FLT   ()+RS5V_FLT   ()+RS5V_FLT   ())>=2 ){ write_ssp_response_rs485( OBC,EPS, FLT,1,   RS5VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   

return 0;
}//execute
	
//################# END RS485 METHODS ###################

//##################SPI1#################################
struct ninebyte COMMAND_PARAMETER_SPI1  = {0,0,0,0,0,0,0,0,0};
  
int receive_spi1 (){//boom
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
struct ninebyte get_command_parameter_after_leftShift_insertEnd_spi1(int insertionbit){ //flag, dest, src, cmd/response , len, data, crc0, crc1, flag
       COMMAND_PARAMETER_SPI1.byte1 = ( (COMMAND_PARAMETER_SPI1.byte1<<1) | (COMMAND_PARAMETER_SPI1.byte2>>7) ) & 255;//flag
       COMMAND_PARAMETER_SPI1.byte2 = ( (COMMAND_PARAMETER_SPI1.byte2<<1) | (COMMAND_PARAMETER_SPI1.byte3>>7) ) & 255;//dest
       COMMAND_PARAMETER_SPI1.byte3 = ( (COMMAND_PARAMETER_SPI1.byte3<<1) | (COMMAND_PARAMETER_SPI1.byte4>>7) ) & 255;//src
       COMMAND_PARAMETER_SPI1.byte4 = ( (COMMAND_PARAMETER_SPI1.byte4<<1) | (COMMAND_PARAMETER_SPI1.byte5>>7) ) & 255;//cmd/response
       COMMAND_PARAMETER_SPI1.byte5 = ( (COMMAND_PARAMETER_SPI1.byte5<<1) | (COMMAND_PARAMETER_SPI1.byte6>>7) ) & 255;//len
       COMMAND_PARAMETER_SPI1.byte6 = ( (COMMAND_PARAMETER_SPI1.byte6<<1) | (COMMAND_PARAMETER_SPI1.byte7>>7) ) & 255;//data
       COMMAND_PARAMETER_SPI1.byte7 = ( (COMMAND_PARAMETER_SPI1.byte7<<1) | (COMMAND_PARAMETER_SPI1.byte8>>7) ) & 255;//crc1
       COMMAND_PARAMETER_SPI1.byte8 = ( (COMMAND_PARAMETER_SPI1.byte8<<1) | (COMMAND_PARAMETER_SPI1.byte9>>7) ) & 255;//crc0
       COMMAND_PARAMETER_SPI1.byte9 = ( (COMMAND_PARAMETER_SPI1.byte9<<1) | insertionbit                      ) & 255;//flag
return COMMAND_PARAMETER_SPI1;
}//get_command_parameter_after_leftShift_insertEnd_spi1

//###################################

//execute
int execute_spi1(struct ninebyte input ){ //flag[1], dest[2], src[3], cmd/response[4] , len[5], data[6], crc0[7], crc1[8], flag[9]
    int    source      = input.byte3;
    int    destination = input.byte2;
    int    from_obc_or_from_ccu_to_eps = (int)(  ((source==OBC_ADDRESS)|(source==CCU_ADDRESS)) & (destination==EPS_ADDRESS)  );//who can talk to the EPS MCU
    int    proper_ssp_frame  = 1;//set to 1 is easier
    struct twobyte received_crc = crc16_generator (input.byte2,input.byte3,input.byte4,input.byte5,input.byte6,
                                                   0,0,0,0,0,   0,0,0,0,0,   0,0,0,0,0,   0,0,0,0,0, 0,0,0,0,0,   0); //let's regenerate the crc if the command frame is: dest,src,cmd,len,data1
    int    valid_crc = (received_crc.byte1==input.byte7)&(received_crc.byte2==input.byte8);
    if (valid_crc & from_obc_or_from_ccu_to_eps & proper_ssp_frame) {
                         int  command  = input.byte4; int parameter= input.byte6;
                         void pause_spi1(int x){for(int i=0;i<x;i++){}}//mada mada
                         void send_bit_spi1  (int bit){// requires spi1 & spi3 collab
			                     if(bit){ SPI1_MISO(1); SPI3_MISO(1); pause_spi1(1000); SPI1_MISO(0); SPI3_MISO(1); pause_spi1(1000); }
	                                     else   { SPI1_MISO(1); SPI3_MISO(0); pause_spi1(1000); SPI1_MISO(0); SPI3_MISO(1); pause_spi1(1000); }
                         }//send_bit_spi1
                         void send_byte_spi1( int out ){   for( int index= 0; index<= 7; index++ ){  send_bit_spi1( (int) ( ( (int) ( out >>(7 -index) ) ) & 1 ) ); }     }//send_byte_spi1
                         int  write_ssp_response_spi1( int dest, int src, int resp, int len, 
                                                       int d1 , int d2 , int d3 , int d4 , int d5 , int d6 , int d7 , int d8 , int d9 ,
                                                       int d10, int d11, int d12, int d13, int d14, int d15, int d16, int d17, int d18
                                                       int d19, int d20, int d21, int d22, int d23, int d24, int d25, int d26, int d27
                                                     ){ //flag, dest, src, cmd/response , len, data, crc0, crc1, flag
			                             struct twobyte crc16 = crc16_generator(dest,src,resp,len,
                                                                                            d1 ,d2 ,d3 ,d4 ,d5 ,d6 ,d7 ,d8 ,d9 ,d10,
                                                                                            d11,d12,d13,d14,d15,d16,d17,d18,d19,d20,
                                                                                            d21,d22,d23,d24,d25,d26,d27);
	                                             if(len==0 ){send_byte_spi1( FF );send_byte_spi1( dest );send_byte_spi1( src );send_byte_spi1( resp );send_byte_spi1( len );send_byte_spi1( FF  );}//len 0 NO CRC
	                                             if(len==1 ){send_byte_spi1( FF );send_byte_spi1( dest );send_byte_spi1( src );send_byte_spi1( resp );send_byte_spi1( len );send_byte_spi1( d1  );
                                                                 send_byte_spi1( crc16.byte1);               send_byte_spi1( crc16.byte2);                send_byte_spi1( FF  );
                                                     }//len 1
	                                             if(len==27){send_byte_spi1( FF );send_byte_spi1( dest );send_byte_spi1( src );send_byte_spi1( resp );send_byte_spi1( len ); 
		                                                 send_byte_spi1( d1 );send_byte_spi1( d2   );send_byte_spi1( d3  );send_byte_spi1( d4   );send_byte_spi1( d5  );send_byte_spi1( d6  );
                                                                 send_byte_spi1( d7  );send_byte_spi1( d8  );send_byte_spi1( d9 );send_byte_spi1( d10   );send_byte_spi1( d11 );send_byte_spi1( d12  );
                                                                 send_byte_spi1( d13 );send_byte_spi1( d14 );send_byte_spi1( d15 );send_byte_spi1( d16  );send_byte_spi1( d17 );send_byte_spi1( d18 );
                                                                 send_byte_spi1( d19 );send_byte_spi1( d20 );send_byte_spi1( d21 );send_byte_spi1( d22  );send_byte_spi1( d23 );send_byte_spi1( d24 );
                                                                 send_byte_spi1( d25 );send_byte_spi1( d26 );send_byte_spi1( d27 );
		                                                 send_byte_spi1( crc16.byte1);               send_byte_spi1( crc16.byte2);                send_byte_spi1( FF  ); 
                                                     }//len 27        
                         return 0;
                         }//write_ssp_response_spi1
                         int check_command   (int cmd  ){  if ( command  ==cmd   ){ return 1; }else{ return 0;}  }//check_command
	                 int check_parameter (int param){  if ( parameter==param ){ return 1; }else{ return 0;}  }//check_input
                         if (check_command(PING) ){ write_ssp_response_spi1( OBC,EPS,ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//ACK...........Fault reporting mechanisms? flag, dest, src, cmd/resp , len, data, crc0, crc1, flag
                         if (check_command(SON ) ){ int else_check=1; 
                                                    if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);PL5V_EN   (1); }//ACK.... do action
                                                    if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS5V_EN (1); }//ACK.... do action
                                                    if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);RS12V_EN  (1); }//ACK.... do action
                                                    if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);XB12V_EN  (1); }//ACK.... do action
                                                    if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);RS3V3_EN  (1); }//ACK.... do action
                                                    if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);PL_EN     (1); }//ACK.... do action
                                                    if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS_EN   (1); }//ACK.... do action
                                                    if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);UHF_EN    (1); }//ACK.... do action
                                                    if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);GPS_EN    (1); }//ACK.... do action
                                                    if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS12V_EN(1); }//ACK.... do action
                                                    if(else_check==1                ){                                write_ssp_response_spi1( OBC,EPS,NACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);               }//NACK
                         }//SON
                         if ( check_command(SOF) ){ int else_check=1;
                                                    if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);PL5V_EN   (0); }//ACK.... do action
                                                    if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS5V_EN (0); }//ACK.... do action
                                                    if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);RS12V_EN  (0); }//ACK.... do action
                                                    if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);XB12V_EN  (0); }//ACK.... do action
                                                    if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);RS3V3_EN  (0); }//ACK.... do action
                                                    if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);PL_EN     (0); }//ACK.... do action
                                                    if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS_EN   (0); }//ACK.... do action
                                                    if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);UHF_EN    (0); }//ACK.... do action
                                                    if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);GPS_EN    (0); }//ACK.... do action
                                                    if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS12V_EN(0); }//ACK.... do action
                                                    if(else_check==1                ){                                write_ssp_response_spi1( OBC,EPS,NACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);               }//NACK
                        }//SOF
                        if ( check_command(SM )  ){ int else_check=1;
                                                    if(check_parameter( INITIALIZE    ) ){else_check=0;CURRENTMODE=INITIALIZE   ;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( DETUMBLE      ) ){else_check=0;CURRENTMODE=DETUMBLE     ;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( NORMAL        ) ){else_check=0;CURRENTMODE=NORMAL       ;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( COMMUNICATION ) ){else_check=0;CURRENTMODE=COMMUNICATION;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( PAYLOAD       ) ){else_check=0;CURRENTMODE=PAYLOAD      ;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( IMAGE         ) ){else_check=0;CURRENTMODE=IMAGE        ;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( EMERGENCY     ) ){else_check=0;CURRENTMODE=EMERGENCY    ;write_ssp_response_spi1( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(else_check==1                    ){                                       write_ssp_response_spi1( OBC,EPS,NACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//NACK
                        }//SM
                        if ( check_command(GM   ) ){  write_ssp_response_spi1( OBC,EPS, ACK,1,CURRENTMODE       ,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0));   }//ACK........ dest, src, cmd/response , len, data,
                        if ( check_command(GSC  ) ){  write_ssp_response_spi1( OBC,EPS, ACK,1,CURRENTSYSTEMCLOCK,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0));   }//ACK........ dest, src, cmd/response , len, data,
                        if ( check_command(SSC  ) ){  write_ssp_response_spi1( OBC,EPS, ACK,0,                 0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0)); CURRENTSYSTEMCLOCK=input.byte6; }//ACK
                        if ( check_command(GOSTM) ){  //current range / 255 = current value for a step of 1
				                      int d1  =0;//SA1_I      ();
				                      int d2  =0;//SA2_I      (); 
                                                      int d3  =0;//SA3_I      (); 
	   		                              int d4  =0;//OBC_I      ();
			                              int d5  =0;//CCU_I      ();   
			                              int d6  =0;//ADCS_I     (); 
	                     			      int d7  =0;//UHF_I      ();  
			     			      int d8  =0;//PL_I       ();  
			    			      int d9  =0;//RS3V3_I    ();        
			   			      int d10 =0;//GPS_I      ();    
			   		              int d11 =0;//ADCS5V_I   ();  
						      int d12 =0;//PL5V_I     ();  
			  			      int d13 =0;//CCU5V_I    ();  
						      int d14 =0;//XB12V_I    ();   
						      int d15 =0;//ADCS12V_I  ();  
						      int d16 =0;//RS5V_I     ();
	                                              int d17 = ( (OBC_FAULT()<<7) | (CCU_FAULT() <<6)  | (RS12V_FLT()<<5) | (RS5V_FLT ()<<4) | (ADCS_FAULT()<<3) | (UHF_FLT    ()<<2)| (PL_FLT()<<1) | RS3V3_FLT  () );
	                                              int d18 = ( (GPS_FLT  ()<<7) | (ADCS5V_FLT()<<6)  | (PL5V_FLT ()<<5) | (CCU5V_FLT()<<4) | (XB12V_FLT ()<<3) | (ADCS12V_FLT()<<2)|  3                            );
				                      int d19 =0;//bat
				                      int d20 =0;//bat
				                      int d21 =0;//bat
				                      int d22 =0;//bat
				                      int d23 =0;//bat
				                      int d24 =0;//bat
				                      int d25 =0;//bat
				                      int d26 =0;//bat
				                      int d27 =0;//bat
                                                      write_ssp_response_spi1( OBC,EPS, ACK,27,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16,d17,d18,d19,d20,d21,d22,d23,d24,d25,d26,d27);
                        }//ACK //GOSTM
                        if ( check_command(KEN ) ){ write_ssp_response_spi1( OBC,EPS, ACK,1,KEN ,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//ACK ...........shutting down all activity received from GCS or OBC //KEN
                        if ( check_command(KDIS) ){ write_ssp_response_spi1( OBC,EPS, ACK,1,KDIS,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//ACK //KDIS
                        //YOU CAN ALSO ADD LOGIC
}//if proceed

if ( (OBC_FAULT  ()+OBC_FAULT  ()+OBC_FAULT  ())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1,    OBCFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if    
if ( (CCU_FAULT  ()+CCU_FAULT  ()+CCU_FAULT  ())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1,    CCUFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if    
if ( (ADCS_FAULT ()+ADCS_FAULT ()+ADCS_FAULT ())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1,   ADCSFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if    
if ( (UHF_FLT    ()+UHF_FLT    ()+UHF_FLT    ())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1,    UHFFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (PL_FLT     ()+PL_FLT     ()+PL_FLT     ())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1,     PLFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if    
if ( (RS3V3_FLT  ()+RS3V3_FLT  ()+RS3V3_FLT  ())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1,  RS3V3FLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (GPS_FLT    ()+GPS_FLT    ()+GPS_FLT    ())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1,    GPSFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if     
if ( (ADCS5V_FLT ()+ADCS5V_FLT ()+ADCS5V_FLT ())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1, ADCS5VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (PL5V_FLT   ()+PL5V_FLT   ()+PL5V_FLT   ())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1,   PL5VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (CCU5V_FLT  ()+CCU5V_FLT  ()+CCU5V_FLT  ())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1,  CCU5VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (XB12V_FLT  ()+XB12V_FLT  ()+XB12V_FLT  ())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1,  XB12VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (ADCS12V_FLT()+ADCS12V_FLT()+ADCS12V_FLT())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1,ADCS12VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (RS12V_FLT  ()+RS12V_FLT  ()+RS12V_FLT  ())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1,  RS12VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (RS5V_FLT   ()+RS5V_FLT   ()+RS5V_FLT   ())>=2 ){ write_ssp_response_spi1( OBC,EPS, FLT,1,   RS5VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
	
return 0;
}//execute

//##################END SPI1#############################


//####################SPI3################################

struct ninebyte COMMAND_PARAMETER_SPI3  = {0,0,0,0,0,0,0,0,0};
  
int receive_spi3 (){//boom
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
struct ninebyte get_command_parameter_after_leftShift_insertEnd_spi3(int insertionbit){ //flag, dest, src, cmd/response , len, data, crc0, crc1, flag
       COMMAND_PARAMETER_SPI3.byte1 = ( (COMMAND_PARAMETER_SPI3.byte1<<1) | (COMMAND_PARAMETER_SPI3.byte2>>7) ) & 255;//flag
       COMMAND_PARAMETER_SPI3.byte2 = ( (COMMAND_PARAMETER_SPI3.byte2<<1) | (COMMAND_PARAMETER_SPI3.byte3>>7) ) & 255;//dest
       COMMAND_PARAMETER_SPI3.byte3 = ( (COMMAND_PARAMETER_SPI3.byte3<<1) | (COMMAND_PARAMETER_SPI3.byte4>>7) ) & 255;//src
       COMMAND_PARAMETER_SPI3.byte4 = ( (COMMAND_PARAMETER_SPI3.byte4<<1) | (COMMAND_PARAMETER_SPI3.byte5>>7) ) & 255;//cmd/response
       COMMAND_PARAMETER_SPI3.byte5 = ( (COMMAND_PARAMETER_SPI3.byte5<<1) | (COMMAND_PARAMETER_SPI3.byte6>>7) ) & 255;//len
       COMMAND_PARAMETER_SPI3.byte6 = ( (COMMAND_PARAMETER_SPI3.byte6<<1) | (COMMAND_PARAMETER_SPI3.byte7>>7) ) & 255;//data
       COMMAND_PARAMETER_SPI3.byte7 = ( (COMMAND_PARAMETER_SPI3.byte7<<1) | (COMMAND_PARAMETER_SPI3.byte8>>7) ) & 255;//crc1
       COMMAND_PARAMETER_SPI3.byte8 = ( (COMMAND_PARAMETER_SPI3.byte8<<1) | (COMMAND_PARAMETER_SPI3.byte9>>7) ) & 255;//crc0
       COMMAND_PARAMETER_SPI3.byte9 = ( (COMMAND_PARAMETER_SPI3.byte9<<1) | insertionbit                      ) & 255;//flag
return COMMAND_PARAMETER_SPI3;
}//get_command_parameter_after_leftShift_insertEnd_spi3

//###################################

//execute
int execute_spi3(struct ninebyte input ){ //flag[1], dest[2], src[3], cmd/response[4] , len[5], data[6], crc0[7], crc1[8], flag[9]
    int    source      = input.byte3;
    int    destination = input.byte2;
    int    from_obc_or_from_ccu_to_eps = (int)(  ((source==OBC_ADDRESS)|(source==CCU_ADDRESS)) & (destination==EPS_ADDRESS)  );//who can talk to the EPS MCU
    int    proper_ssp_frame  = 1;//set to 1 is easier
    struct twobyte received_crc = crc16_generator (input.byte2,input.byte3,input.byte4,input.byte5,input.byte6,
	                                           0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0, 0); //let's regenerate the crc if the command frame is: dest,src,cmd,len,data1
    int    valid_crc = (received_crc.byte1==input.byte7)&(received_crc.byte2==input.byte8);
    if (valid_crc & from_obc_or_from_ccu_to_eps & proper_ssp_frame) {
                         int  command  = input.byte4; int parameter= input.byte6;
                         void pause_spi3(int x){for(int i=0;i<x;i++){}}//mada mada
                         void send_bit_spi3  (int bit){//requires spi1 and spi3 collab
			      if(bit){ SPI3_MISO(1); SPI3_MISO(1); pause_spi3(1000); SPI3_MISO(0); SPI3_MISO(1); pause_spi3(1000); }
	                      else   { SPI3_MISO(1); SPI3_MISO(0); pause_spi3(1000); SPI3_MISO(0); SPI3_MISO(1); pause_spi3(1000); }
                         }//send_bit_spi3
                         void send_byte_spi3( int out ){   for( int index= 0; index<= 7; index++ ){  send_bit_spi3( (int) ( ( (int) ( out >>(7 -index) ) ) & 1 ) ); }        }//send_byte_spi3
                         int  write_ssp_response_spi3( int dest, int src, int resp, int len,
	                                               int d1  , int d2 , int d3  , int d4 , int d5  , int d6 , int d7  , int d8 , int d9 , 
	                                               int d10 , int d11 ,int d12,  int d13, int d14, int d15 , int d16 , int d17, int d18,
	                                               int d19 , int d20 ,int d21,  int d22, int d23, int d24 , int d25 , int d26, int d27 ){ //flag, dest, src, cmd/response , len, data, crc0, crc1, flag
			                               struct twobyte crc16 = crc16_generator( dest,src,resp,len,
				                                                               d1, d2, d3, d4, d5, d6, d7, d8, d9, d10,
				                                                              d11,d12,d13,d14,d15,d16,d17,d18,d19, d20,
				                                                              d21,d22,d23,d24,d25,d26,d27);
	                                             if(len==0 ){send_byte_spi3( FF );send_byte_spi3( dest );send_byte_spi3( src );send_byte_spi3( resp );send_byte_spi3( len );send_byte_spi3( FF  );}//len 0 NO CRC sent
	                                             if(len==1 ){send_byte_spi3( FF );send_byte_spi3( dest );send_byte_spi3( src );send_byte_spi3( resp );send_byte_spi3( len );send_byte_spi3( d1  );send_byte_spi3( crc16.byte1);send_byte_spi3( crc16.byte2);send_byte_spi3( FF  );}//len 1
	                                             if(len==27){send_byte_spi3( FF );send_byte_spi3( dest );send_byte_spi3( src );send_byte_spi3( resp );send_byte_spi3( len ); 
		                                                 send_byte_spi3( d1  );send_byte_spi3( d2  );send_byte_spi3( d3  );send_byte_spi3( d4   );send_byte_spi3( d5  );send_byte_spi3( d6  );send_byte_spi3( d7  );send_byte_spi3( d8  );send_byte_spi3( d9 );
					                         send_byte_spi3( d10 );send_byte_spi3( d11 );send_byte_spi3( d12  );send_byte_spi3( d13 );send_byte_spi3( d14 );send_byte_spi3( d15 );send_byte_spi3( d16 );send_byte_spi3( d17);send_byte_spi3( d18  );
					                         send_byte_spi3( d19 );send_byte_spi3( d20 );send_byte_spi3( d21  );send_byte_spi3( d22 );send_byte_spi3( d23 );send_byte_spi3( d24 );send_byte_spi3( d25 );send_byte_spi3( d26);send_byte_spi3( d27  );
					                         send_byte_spi3( crc16.byte1);               send_byte_spi3( crc16.byte2);                send_byte_spi3( FF  );
			      }//len 27        
                         return 0;
                         }//write_ssp_response_spi3
                         int check_command   (int cmd  ){  if ( command  ==cmd   ){ return 1; }else{ return 0;}  }//check_command
	                 int check_parameter (int param){  if ( parameter==param ){ return 1; }else{ return 0;}  }//check_input
                         if (check_command(PING) ){ write_ssp_response_spi3( OBC,EPS,ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//ACK...........Fault reporting mechanisms? flag, dest, src, cmd/resp , len, data, crc0, crc1, flag
                         if (check_command(SON ) ){ int else_check=1;
                                                    if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);PL5V_EN   (1); }//ACK.... do action
                                                    if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS5V_EN (1); }//ACK.... do action
                                                    if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);RS12V_EN  (1); }//ACK.... do action
                                                    if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);XB12V_EN  (1); }//ACK.... do action
                                                    if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);RS3V3_EN  (1); }//ACK.... do action
                                                    if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);PL_EN     (1); }//ACK.... do action
                                                    if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS_EN   (1); }//ACK.... do action
                                                    if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);UHF_EN    (1); }//ACK.... do action
                                                    if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);GPS_EN    (1); }//ACK.... do action
                                                    if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS12V_EN(1); }//ACK.... do action
                                                    if(else_check==1                ){                                write_ssp_response_spi3( OBC,EPS,NACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);               }//NACK
                         }//SON
                         if ( check_command(SOF) ){ int else_check=1;
                                                    if(check_parameter( PL5V_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);PL5V_EN   (0); }//ACK.... do action
                                                    if(check_parameter( ADCS5V_EN ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS5V_EN (0); }//ACK.... do action
                                                    if(check_parameter( RS12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);RS12V_EN  (0); }//ACK.... do action
                                                    if(check_parameter( XB12V_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);XB12V_EN  (0); }//ACK.... do action
                                                    if(check_parameter( RS3V3_EN  ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);RS3V3_EN  (0); }//ACK.... do action
                                                    if(check_parameter( PL_EN     ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);PL_EN     (0); }//ACK.... do action
                                                    if(check_parameter( ADCS_EN   ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS_EN   (0); }//ACK.... do action
                                                    if(check_parameter( UHF_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);UHF_EN    (0); }//ACK.... do action
                                                    if(check_parameter( GPS_EN    ) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);GPS_EN    (0); }//ACK.... do action
                                                    if(check_parameter( ADCS12V_EN) ){else_check=0;CURRENTMODE=CUSTOM;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);ADCS12V_EN(0); }//ACK.... do action
                                                    if(else_check==1                ){                                write_ssp_response_spi3( OBC,EPS,NACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);               }//NACK
                        }//SOF
                        if ( check_command(SM )  ){ int else_check=1;
                                                    if(check_parameter( INITIALIZE    ) ){else_check=0;CURRENTMODE=INITIALIZE   ;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( DETUMBLE      ) ){else_check=0;CURRENTMODE=DETUMBLE     ;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( NORMAL        ) ){else_check=0;CURRENTMODE=NORMAL       ;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( COMMUNICATION ) ){else_check=0;CURRENTMODE=COMMUNICATION;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( PAYLOAD       ) ){else_check=0;CURRENTMODE=PAYLOAD      ;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( IMAGE         ) ){else_check=0;CURRENTMODE=IMAGE        ;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(check_parameter( EMERGENCY     ) ){else_check=0;CURRENTMODE=EMERGENCY    ;write_ssp_response_spi3( OBC,EPS, ACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//ACK.... do action
                                                    if(else_check==1                    ){                                       write_ssp_response_spi3( OBC,EPS,NACK,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);     }//NACK
                        }//SM
                        if ( check_command(GM   ) ){  write_ssp_response_spi3( OBC,EPS, ACK,1,CURRENTMODE       ,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);   }//ACK........ dest, src, cmd/response , len, data,
                        if ( check_command(GSC  ) ){  write_ssp_response_spi3( OBC,EPS, ACK,1,CURRENTSYSTEMCLOCK,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0);   }//ACK........ dest, src, cmd/response , len, data,
                        if ( check_command(SSC  ) ){  write_ssp_response_spi3( OBC,EPS, ACK,0,                 0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); CURRENTSYSTEMCLOCK=input.byte6; }//ACK
                        if ( check_command(GOSTM) ){  //current range / 255 = current value for a step of 1
				                      int d1  =0;//SA1_I      ();
				                      int d2  =0;//SA2_I      (); 
                                                      int d3  =0;//SA3_I      (); 
	   		                              int d4  =0;//OBC_I      ();
			                              int d5  =0;//CCU_I      ();   
			                              int d6  =0;//ADCS_I     (); 
	                     			      int d7  =0;//UHF_I      ();  
			     			      int d8  =0;//PL_I       ();  
			    			      int d9  =0;//RS3V3_I    ();        
			   			      int d10 =0;//GPS_I      ();    
			   		              int d11 =0;//ADCS5V_I   ();  
						      int d12 =0;//PL5V_I     ();  
			  			      int d13 =0;//CCU5V_I    ();  
						      int d14 =0;//XB12V_I    ();   
						      int d15 =0;//ADCS12V_I  ();  
						      int d16 =0;//RS5V_I     ();
	                                              int d17 = ( (OBC_FAULT()<<7) | (CCU_FAULT() <<6)  | (RS12V_FLT()<<5) | (RS5V_FLT ()<<4) | (ADCS_FAULT()<<3) | (UHF_FLT    ()<<2)| (PL_FLT()<<1) | RS3V3_FLT  () );
	                                              int d18 = ( (GPS_FLT  ()<<7) | (ADCS5V_FLT()<<6)  | (PL5V_FLT ()<<5) | (CCU5V_FLT()<<4) | (XB12V_FLT ()<<3) | (ADCS12V_FLT()<<2)|  3                            );
				                      int d19 =0;//bat
				                      int d20 =0;//bat
				                      int d21 =0;//bat
				                      int d22 =0;//bat
				                      int d23 =0;//bat
				                      int d24 =0;//bat
				                      int d25 =0;//bat
				                      int d26 =0;//bat
				                      int d27 =0;//bat
                                                      write_ssp_response_spi3( OBC,EPS, ACK,27,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16,d17,d18,d19,d20,d21,d22,d23,d24,d25,d26,d27);
                        }//ACK //GOSTM
                        if ( check_command(KEN ) ){ write_ssp_response_spi3( OBC,EPS, ACK,1,KEN ,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//ACK ...........shutting down all activity received from GCS or OBC //KEN
                        if ( check_command(KDIS) ){ write_ssp_response_spi3( OBC,EPS, ACK,1,KDIS,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//ACK //KDIS
                        //YOU CAN ALSO ADD LOGIC
}//if proceed

if ( (OBC_FAULT  ()+OBC_FAULT  ()+OBC_FAULT  ())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1,    OBCFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if    
if ( (CCU_FAULT  ()+CCU_FAULT  ()+CCU_FAULT  ())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1,    CCUFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if    
if ( (ADCS_FAULT ()+ADCS_FAULT ()+ADCS_FAULT ())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1,   ADCSFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if    
if ( (UHF_FLT    ()+UHF_FLT    ()+UHF_FLT    ())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1,    UHFFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (PL_FLT     ()+PL_FLT     ()+PL_FLT     ())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1,     PLFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if    
if ( (RS3V3_FLT  ()+RS3V3_FLT  ()+RS3V3_FLT  ())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1,  RS3V3FLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (GPS_FLT    ()+GPS_FLT    ()+GPS_FLT    ())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1,    GPSFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if     
if ( (ADCS5V_FLT ()+ADCS5V_FLT ()+ADCS5V_FLT ())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1, ADCS5VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (PL5V_FLT   ()+PL5V_FLT   ()+PL5V_FLT   ())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1,   PL5VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (CCU5V_FLT  ()+CCU5V_FLT  ()+CCU5V_FLT  ())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1,  CCU5VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (XB12V_FLT  ()+XB12V_FLT  ()+XB12V_FLT  ())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1,  XB12VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (ADCS12V_FLT()+ADCS12V_FLT()+ADCS12V_FLT())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1,ADCS12VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (RS12V_FLT  ()+RS12V_FLT  ()+RS12V_FLT  ())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1,  RS12VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   
if ( (RS5V_FLT   ()+RS5V_FLT   ()+RS5V_FLT   ())>=2 ){ write_ssp_response_spi3( OBC,EPS, FLT,1,   RS5VFLT,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0); }//if   

return 0;
}//execute

//#####################END SPI3##########################


	
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
