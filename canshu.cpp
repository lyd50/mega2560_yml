#include "canshu.h"
#include <Arduino.h>

/*--------------------------------���������------------------------------------------*/
//
int diyakg=22,jingshui_chaoyakg = 24, 
jingshui_gaoyakg = 26, shuiliu_chuanganqi = 2; //
    
int chaolv1 = 23,chaolv2=25, jingshui = 27,  gaoyabeng =29;



/*--------------------------------ˮ��������-------------------------------------------*/
volatile int count = 0; //????????????????

/*--------------------------------����-------------------------------------------*/
byte chaolv1_chongxi_maichong_dixian = 20;
byte loushui_maich_biaozhun = 10;
//unsigned int chaolv1chongxi_zongcishu = 0; /*??????????*/
unsigned long accumulative = 0; /*?????????*/
byte chxi_cishu = 1;			//Ĭ��
byte leiji_biaozhun = 30;
bool chaolv_chxi = false, loushui_bool = false; //?????????????
unsigned long chaolv1chongxi_zongcishu = 0,chaolv2chongxi_zongcishu = 0;


/*--------------------------------����-------------------------------------------*/
bool tiaoshikg = true;
/*--------------------------------��ʾ������-------------------------------------------*/
bool display_f=true;
byte buffer[200]; //??????????
unsigned int buffer_index = 0;
byte brightness = 30; //???????50
bool set_once = true; //???????????
byte page = 0;		  //???0?????
byte pre_page = 50;   //???????????��???????
String pre_kongjian, pre_text;
//byte ff_starter = 0;
byte terminator = 0; //?????????
bool parse_ready = false;
bool eeprom_write = false;
bool xsp_shezhi = false;
String order_sended = ""; 
//Chrono    xianshi_jiange;//��ˮ����ʾ�������ʾ
//Chrono  yinyong_shuiman_xianshi_jiange,shch_shuiman_xianshi_jiange;
unsigned long guanji_xianshi_jiange=0;
String message_todisplay[10];
bool at_zhuangtai=false,at_shuju=false;
/*--------------------------------��ˮ-------------------------------------------*/

byte zhishuishijian_set = 100;	 //100����
unsigned long zhishuizongshijian=0; //
byte jigshui_danci=0;//������ˮʱ��-����
byte xianshi=0;
//bool yinyong_zhishui = false, shchan_zhishui = false;
byte shuimandengdaishijian_set = 20; //??????????????????? 6?????

byte zhishui_maichong_biaozhun = 30;
byte xie_jici=0;
byte chaoshi_cishu = 0; /*????2?��???????????*/
byte feishuiguoshao_times = 0;
unsigned long zhishui_starttime = 0,jingshui_dcf_starttime=0,zhishui_stoptime=0;
unsigned long zhishui_xianshi_jiange=0;
byte zhishui_shjian_add=60;
unsigned long yinyong_shuiman_xianshi=0,shch_shuiman_xianshi=0;
unsigned long jingshui_chaoya_xianshi_jiange=0;//��Ϸ�����Ϣ
unsigned long jingshui_bunengman_jiange=0;
/*--------------------------------ϴĤ-------------------------------------------*/
byte jingshuiximo_shichang = 6; //?????6????,??��????
bool xuyao_ximo = false,ximo_yucun=false;
byte moci_ximo_maichong_biaozhun = 9, ximo_shuiliu_jiance_cishu = 10;
//byte dcf_chxi_shichang = 40; //??????????????
 //Chrono ch_ximo;
unsigned long ximo_start=0,ximo_xianshi_jiange=0;
/*--------------------------------����-------------------------------------------*/
//String state = ""; //??????
unsigned long alarm_jiange = 0;
bool jingshui_chaoya = false, feishuiguoshao = false, ximo_buneng_shuiman = false;
 //Chrono ch_alarm;
 //Chrono ch_xianshi_guanji_jiange;
unsigned long baojing_begintime = 0;
//unsigned long feishuiguoshao_xianshi_jiange=0;
bool baojing=false;

 // BgrMax7seg ld = BgrMax7seg(SPI_SPEED, SPI_CSPIN, DISP_AMOUNT);
/*-------------------------------ȱˮ------------------------------------------*/
unsigned long queshui_xianshi_jiange=0;
/*-------------------------------tds���--------------------------------------*/

unsigned long tds_jiange=0;
unsigned int tds;
unsigned char tds_buffer[20];
unsigned int tds_buffer_index=0;
bool tds_jiexi=false;
