/*--------------------------------------------------------------------------
N76E885.H

Header file for Nuvoton N76E885
--------------------------------------------------------------------------*/

#ifndef __N76E885_H__
#define __N76E885_H__



__sfr __at (0x80) P0;
__sfr __at (0x81) SP;
__sfr __at (0x82) DPL;
__sfr __at (0x83) DPH;
__sfr __at (0x86) RWK;
__sfr __at (0x87) PCON;

__sfr __at (0x88) TCON;
__sfr __at (0x89) TMOD;
__sfr __at (0x8A) TL0;
__sfr __at (0x8B) TL1;
__sfr __at (0x8C) TH0;
__sfr __at (0x8D) TH1;
__sfr __at (0x8E) CKCON;
__sfr __at (0x8F) WKCON;

__sfr __at (0x90) P1;
__sfr __at (0x91) SFRS; //TA Protection
__sfr __at (0x92) CAPCON0;
__sfr __at (0x93) CAPCON1;
__sfr __at (0x94) CAPCON2;
__sfr __at (0x95) CKDIV;
__sfr __at (0x96) CKSWT; //TA Protection
__sfr __at (0x97) CKEN; //TA Protection

__sfr __at (0x98) SCON;
__sfr __at (0x99) SBUF;
__sfr __at (0x9A) SBUF_1;
__sfr __at (0x9B) EIE;
__sfr __at (0x9C) EIE1;
__sfr __at (0x9F) CHPCON; //TA Protection

__sfr __at (0xA0) P2;
__sfr __at (0xA2) AUXR1;
__sfr __at (0xA3) BODCON0; //TA Protection
__sfr __at (0xA4) IAPTRG; //TA Protection
__sfr __at (0xA5) IAPUEN;
__sfr __at (0xA6) IAPAL;
__sfr __at (0xA7) IAPAH;

__sfr __at (0xA8) IE;
__sfr __at (0xA9) SADDR;
__sfr __at (0xAA) WDCON; //TA Protection
__sfr __at (0xAB) BODCON1; //TA Protection
__sfr __at (0xAC) P3M1;
__sfr __at (0xAC) P3S; //Page1
__sfr __at (0xAD) P3M2;
__sfr __at (0xAD) P3SR; //Page1
__sfr __at (0xAE) IAPFD;
__sfr __at (0xAF) IAPCN;

__sfr __at (0xB0) P3;
__sfr __at (0xB1) P0M1;
__sfr __at (0xB1) P0S; //Page1
__sfr __at (0xB2) P0M2;
__sfr __at (0xB2) P0SR; //Page1
__sfr __at (0xB3) P1M1;
__sfr __at (0xB3) P1S; //Page1
__sfr __at (0xB4) P1M2;
__sfr __at (0xB4) P1SR; //Page1
__sfr __at (0xB5) P2M1;
__sfr __at (0xB5) P2S; //Page1
__sfr __at (0xB6) P2M2;
__sfr __at (0xB6) P2SR; //Page1
__sfr __at (0xB7) IPH;

__sfr __at (0xB8) IP;
__sfr __at (0xB9) SADEN;
__sfr __at (0xBA) SADEN_1;
__sfr __at (0xBB) SADDR_1;
__sfr __at (0xBC) I2DAT;
__sfr __at (0xBD) I2STAT;
__sfr __at (0xBE) I2CLK;
__sfr __at (0xBF) I2TOC;

__sfr __at (0xC0) I2CON;
__sfr __at (0xC1) I2ADDR;
__sfr __at (0xC2) ADCRL;
__sfr __at (0xC3) ADCRH;
__sfr __at (0xC4) T3CON;
__sfr __at (0xC5) RL3;
__sfr __at (0xC6) RH3;
__sfr __at (0xC7) TA;

__sfr __at (0xC8) T2CON;
__sfr __at (0xC9) T2MOD;
__sfr __at (0xCA) RCMP2L;
__sfr __at (0xCB) RCMP2H;
__sfr __at (0xCC) TL2;
__sfr __at (0xCD) TH2;
__sfr __at (0xCE) ADCMPL;
__sfr __at (0xCF) ADCMPH;

__sfr __at (0xD0) PSW;
__sfr __at (0xD1) PWMPH;
__sfr __at (0xD2) PWM01H;
__sfr __at (0xD3) PWM23H;
__sfr __at (0xD4) PWM67H;
__sfr __at (0xD5) PWM45H;
__sfr __at (0xD6) PNP;
__sfr __at (0xD7) FBD;

__sfr __at (0xD8) PWMCON0;
__sfr __at (0xD9) PWMPL;
__sfr __at (0xDA) PWM01L;
__sfr __at (0xDB) PWM23L;
__sfr __at (0xDC) PWM67L;
__sfr __at (0xDD) PWM45L;
__sfr __at (0xDE) PIO;
__sfr __at (0xDF) PWMCON1;

__sfr __at (0xE0) ACC;
__sfr __at (0xE1) ADCCON1;
__sfr __at (0xE2) ADCCON2;
__sfr __at (0xE3) ADCDLY;
__sfr __at (0xE4) C0L;
__sfr __at (0xE5) C0H;
__sfr __at (0xE6) C1L;
__sfr __at (0xE7) C1H;

__sfr __at (0xE8) ADCCON0;
__sfr __at (0xE9) PICON;
__sfr __at (0xEA) PINEN;
__sfr __at (0xEB) PIPEN;
__sfr __at (0xEC) PIF;
__sfr __at (0xED) C2L;
__sfr __at (0xEE) C2H;
__sfr __at (0xEF) EIP;

__sfr __at (0xF0) B;
__sfr __at (0xF2) ADCAQT;
__sfr __at (0xF3) SPCR;
__sfr __at (0xF4) SPSR;
__sfr __at (0xF5) SPDR;
__sfr __at (0xF6) P0DIDS;
__sfr __at (0xF7) EIPH;

__sfr __at (0xF8) SCON_1;
__sfr __at (0xF9) PDTEN; //TA Protection
__sfr __at (0xFA) PDTCNT; //TA Protection
__sfr __at (0xFB) PMEN;
__sfr __at (0xFC) PMD;
__sfr __at (0xFE) EIP1;
__sfr __at (0xFF) EIPH1;

/*  BIT Registers  */
/*  SCON_1  */
__sbit __at (0xff) SM0_1;
__sbit __at (0xff) FE_1;
__sbit __at (0xfe) SM1_1;
__sbit __at (0xfd) SM2_1;
__sbit __at (0xfc) REN_1;
__sbit __at (0xfb) TB8_1;
__sbit __at (0xfa) RB8_1;
__sbit __at (0xf9) TI_1;
__sbit __at (0xf8) RI_1;

/*  ADCCON0  */
__sbit __at (0xef) ADCF;
__sbit __at (0xee) ADCS;
__sbit __at (0xed) ETGSEL1;
__sbit __at (0xec) ETGSEL0;
__sbit __at (0xeb) ADCHS3;
__sbit __at (0xea) ADCHS2;
__sbit __at (0xe9) ADCHS1;
__sbit __at (0xe8) ADCHS0;

/*  PWMCON0  */
__sbit __at (0xdf) PWMRUN;
__sbit __at (0xde) LOAD;
__sbit __at (0xdd) PWMF;
__sbit __at (0xdc) CLRPWM;
__sbit __at (0xdb) INTTYP1;
__sbit __at (0xda) INTTYP0;
__sbit __at (0xd9) INTSEL1;
__sbit __at (0xd8) INTSEL0;

/*  PSW */
__sbit __at (0xd7) CY;
__sbit __at (0xd6) AC;
__sbit __at (0xd5) F0;
__sbit __at (0xd4) RS1;
__sbit __at (0xd3) RS0;
__sbit __at (0xd2) OV;
__sbit __at (0xd0) P;

/*  T2CON  */
__sbit __at (0xcf) TF2;
__sbit __at (0xca) TR2;
__sbit __at (0xc8) CM_RL2;

/*  I2CON  */
__sbit __at (0xc6) I2CEN;
__sbit __at (0xc5) STA;
__sbit __at (0xc4) STO;
__sbit __at (0xc3) SI;
__sbit __at (0xc2) AA;

/*  IP  */
__sbit __at (0xbe) PADC;
__sbit __at (0xbd) PBOD;
__sbit __at (0xbc) PS;
__sbit __at (0xbb) PT1;
__sbit __at (0xba) PX1;
__sbit __at (0xb9) PT0;
__sbit __at (0xb8) PX0;

/*  P3  */
__sbit __at (0xb0) P30;
__sbit __at (0xb1) P31;
__sbit __at (0xb2) P32;
__sbit __at (0xb3) P33;
__sbit __at (0xb4) P34;
__sbit __at (0xb5) P35;
__sbit __at (0xb6) P36;
__sbit __at (0xb7) P37;

/*  IE  */
__sbit __at (0xaf) EA;
__sbit __at (0xae) EADC;
__sbit __at (0xad) EBOD;
__sbit __at (0xac) ES;
__sbit __at (0xab) ET1;
__sbit __at (0xaa) EX1;
__sbit __at (0xa9) ET0;
__sbit __at (0xa8) EX0;

/*  P2  */
__sbit __at (0xa0) P20;
__sbit __at (0xa0) RXD;
__sbit __at (0xa0) T0;
__sbit __at (0xa0) IC0;
__sbit __at (0xa0) AIN9;

__sbit __at (0xa1) P21;
__sbit __at (0xa1) MOSI;
__sbit __at (0xa1) T1;
__sbit __at (0xa1) IC1;

__sbit __at (0xa2) P22;
__sbit __at (0xa2) MISO;
__sbit __at (0xa2) IC2;

__sbit __at (0xa3) P23;
__sbit __at (0xa3) SDA;
__sbit __at (0xa3) FB;
__sbit __at (0xa3) STADC;

__sbit __at (0xa4) P24;
__sbit __at (0xa4) RXD_1;

__sbit __at (0xa5) P25;
__sbit __at (0xa5) TXD_1;

__sbit __at (0xa6) P26;
__sbit __at (0xa6) CLO;
__sbit __at (0xa6) AIN8;
__sbit __at (0xa6) PWM7;

/*  SCON  */
__sbit __at (0x9f) SM0;
__sbit __at (0x9f) FE;
__sbit __at (0x9e) SM1;
__sbit __at (0x9d) SM2;
__sbit __at (0x9c) REN;
__sbit __at (0x9b) TB8;
__sbit __at (0x9a) RB8;
__sbit __at (0x99) TI;
__sbit __at (0x98) RI;

/*  P1  */
__sbit __at (0x90) P10;
__sbit __at (0x90) PWM0;
__sbit __at (0x91) P11;
__sbit __at (0x91) PWM1;
__sbit __at (0x92) P12;

/*  TCON  */
__sbit __at (0x8f) TF1;
__sbit __at (0x8e) TR1;
__sbit __at (0x8d) TF0;
__sbit __at (0x8c) TR0;
__sbit __at (0x8b) IE1;
__sbit __at (0x8a) IT1;
__sbit __at (0x89) IE0;
__sbit __at (0x88) IT0;

/*  P0  */
__sbit __at (0x80) P00;
__sbit __at (0x80) INT0;
__sbit __at (0x80) AIN0;
__sbit __at (0x80) VREF;

__sbit __at (0x81) P01;
__sbit __at (0x81) INT1;
__sbit __at (0x81) AIN1;

__sbit __at (0x82) P02;
__sbit __at (0x82) PWM2;
__sbit __at (0x82) AIN2;

__sbit __at (0x83) P03;
__sbit __at (0x83) PWM3;
__sbit __at (0x83) TXD;
__sbit __at (0x83) AIN3;

__sbit __at (0x84) P04;
__sbit __at (0x84) SS;
__sbit __at (0x84) AIN4;

__sbit __at (0x85) P05;
__sbit __at (0x85) PWM4;
__sbit __at (0x85) SPICK;
__sbit __at (0x85) AIN5;

__sbit __at (0x86) P06;
__sbit __at (0x86) SCL;
__sbit __at (0x86) AIN6;
__sbit __at (0x86) PWM5;

__sbit __at (0x87) P07;
__sbit __at (0x87) AIN7;
__sbit __at (0x87) PWM6;



#endif