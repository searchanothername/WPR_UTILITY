// Global_CtrlWords.h: interface for the CGlobal_CtrlWords class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBAL_CTRLWORDS_H__3DC927F0_6F7E_4E5B_B614_CFE4D6FE9841__INCLUDED_)
#define AFX_GLOBAL_CTRLWORDS_H__3DC927F0_6F7E_4E5B_B614_CFE4D6FE9841__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////
//Control words defined here
#define G_BEAMNUMBERS 10
#define EH 0
#define EL 1
#define NH 2
#define NL 3
#define VH 4
#define VL 5
#define WH 6
#define WL 7
#define SH 8
#define SL 9

struct control_word_0_fields
{
	unsigned int  phc   : 1;  //Bit 0
	//PCS 脉冲压缩选择             
	//"0"不进行脉冲压缩
    //"1"进行脉冲压缩
	unsigned int  pcs   : 1;  //Bit 1
	//PHC 移相方式控制            
	//"1"按PRT移相
    //"0"按时域平均移相，即每累计完成一次时域平均，移相码变化一次。
	unsigned int  rev240m : 1;  //Bit 2
	unsigned int  fftpts : 3; //Bit 3-5
	//001 = 1    //011 = 256  //101 = 1024
	//010 = 128  //100 = 512  //110 = 2048

	unsigned int  spectra_samples : 8;  //Bit 6-13
	//128-n, n=spectra number
	//SPECTRAL POINT LOAD = 128 - N,
	//where N = number of spectra averages to be collected 
	unsigned int  tda_samples: 9; //Bit 14-22
	//max=512

	unsigned int  dptestctrl:1;   //Bit 23
	//1=dop test, 0=operation mode

	unsigned int  dptestphaseshift : 3;   //Bit 24-26
	//000=0   //010 = 90   //100 = 180  //110 = 270
	//001=45  //011 =135   //101 = 225  //111 = 315

	unsigned int  bmdirchange : 1;// Bit27
	//1=nochange, 0=change
	//set on initialization and whenever the beam direction changes (normally every second beam);

	unsigned int  bmdirection :3; //Bit28-30
	//111=v  //101=w //011=v  //001=e
	//110=s  //100=v //010=n  //000=v
	//BEAM DIRECTION; beam value ---- EAST 1 NORTH 2 VERTICAL 3 

	unsigned int  mode : 1; //Bit 31
	//hi =1, lo =0
};

struct control_word_1_fields
{
	unsigned int  workmode : 3;  //Bit 0-2
	//000=maintain  //010=test  //100=calibration
	//001=i/q save  //011=rass  //111=wpr operation

	//xx1 = rass,	xx0 no rass 
	//x1x = single sweep,	x0x = multiple sweeps 
	//1xx = mode A,	0xx = mode b 
	//unsigned char 		rass_comm : 1;
	//unsigned char 		rass_sweep : 1;
	//unsigned char 		rass_submode : 1;
	
	unsigned int  coaxialdriver : 1; //Bit 3
	//1=antanna , 0=false load

	unsigned int  dif_gate_moving : 4;//Bit 4-7
    //Move DIF_Gate	数字中频复位信号移动控制
    //步进为一个V/O_clk，最大后延16个时钟即2个RB

	//{LIUChen modify this 2009/5/11
	unsigned int two_switcher:1;//Bit 8 //0:test channel 1:main channel.
	unsigned int spare: 2;//Bit 9-10
	//unsigned int  spare : 3;  //Bit 4-10
	//}

	unsigned int  testsrcsel : 4;  //Bit 11-14
	//1000=noise source				//0010 = transmitter output sample
	//0100 = receiver test signal   //0001 = transmitter exciter signal

	unsigned int  rfattenuation: 7; //Bit 15-21
	//0000001 = 1;   //0000100 = 4;  //0010000 = 16;  //1000000 = 40;  
	//0000010 = 2;   //0001000 = 8;  //0100000 = 32;

	unsigned int  noisesrcctrl: 1; //Bit 22
	//1=open noise source
	//0=close noise source

	unsigned int  rxtestoutsel : 1;   //Bit 23
	//1=disable test signal output
	//0=test signal output

	unsigned int  smrst : 1;   //Bit 24
	//1=status monitor working status
	//0=status monitor reset

	unsigned int  rxtestsignalampctrl : 4; //Bit 25-28
	//0000=0   //0010 = -12   //0100 = -24  //0110 = -36
	//0001=-6  //0011 = -18   //0101 = -30  //0111 = -42
	//1000=-48   //1010 = -60   //1100 = -72  //1110 = -84
	//1001=-54  //1011 = -66   //1101 = -78  //1111 = -90
	//during working, receiver test signal is -90db

	unsigned int  rxtestfresel : 1;// Bit 29
	//1=if test frequency ,
	//0=receiver test frequency

	unsigned int  lophctrl :1; //Bit 30
	//1=local oscillator phase shift(working status) 
	//0==lo not phase shift

	unsigned int  txctrl : 1; //Bit 31
	//1=on, 0=off

};

struct control_word_2_fields
{
	unsigned int  prt : 13;  //Bit 0-12
	//vertical beam, for example =409us(8192/20)
	//oblique beam, for example =426us(8192/19.2)
	
	unsigned int  txpulse : 10; //Bit 13 -22
	//vertical beam, for example = 51us(1024/20)
	//oblique beam, for example = 53us(1024/19.2)

	//unsigned int  spare2 : 9; // Bit 23-31
	//liuchen modikfy this	
	unsigned int spare :1;
	unsigned int rfgatemoving :8;
	//激励门移动控制，步长为一个V/O时钟。
    //最大延时时间：255/20=12.75us


};

struct control_word_3_6_fields
{
	unsigned int  stc1 : 5;  //Bit 0-4
	unsigned int  stc2 : 5;  //Bit 5-9
	unsigned int  stc3 : 5;  //Bit 10-14
	unsigned int  stc4 : 5;  //Bit 15-19
	unsigned int  stc5 : 5;  //Bit 20-24
	unsigned int  stc6 : 5;  //Bit 25-29
	unsigned int  spare : 1; //Bit 30
	unsigned int  stc_cw: 1; //Bit 31
	//"0"低模式下第1～24 RB分别输出STC控制码STC0－STC23
	//"1"无论高低模式，始终输出STC0

	//00001=2    //00100=8    //10000 = 32
	//00010=4    //01000=16
};

union un_cw3_6
{
	control_word_3_6_fields cw3_6_flds;
	UINT cw3_6_ui;
};

extern int pccodemoving;//liuchen add it 2006/12/13

struct control_word_0_6
{
	union 
	{
		control_word_0_fields cw0_flds;
		UINT cw0;
	};

	union 
	{
		control_word_1_fields cw1_flds;
		UINT cw1;
	};

	union 
	{
		control_word_2_fields cw2_flds;
		UINT cw2;
	};
	un_cw3_6  cw3_6[4];
};

extern control_word_0_6 g_submode_ctrlwrds[G_BEAMNUMBERS];
extern control_word_0_6 g_nomal_ctrlwrds;
extern control_word_0_6 g_last;
extern BOOL b_firstdownload;
extern BOOL b_nochanged;

extern float g_duty_cycle[G_BEAMNUMBERS] ;
extern float g_transmitter_pulsewidth[G_BEAMNUMBERS];

enum
{
    WPR_DP_AD_BAR0 = 0,
	WPR_DP_AD_BAR1 = 1,
	WPR_DP_AD_BAR2 = 2,
	WPR_DP_AD_BAR3 = 3,
	WPR_DP_AD_BAR4 = 4,
	WPR_DP_AD_BAR5 = 5,
	WPR_DP_AD_EPROM = 6,
};

extern UINT Data0, Data1, Data2, Data4, Data8;
//extern UINT LOWALLGATES;
//extern UINT HIGHALLGATES;
//extern int g_knumber_of_rangebin[G_BEAMNUMBERS];
extern int g_curbeamnum;
#endif // !defined(AFX_GLOBAL_CTRLWORDS_H__3DC927F0_6F7E_4E5B_B614_CFE4D6FE9841__INCLUDED_)
