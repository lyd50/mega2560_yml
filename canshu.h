
#include <Arduino.h>

/*extern����
����1�����롰C��һ��ʹ��ʱ���� extern "C" void fun(int a, int b)�����������fun�������������c���Թ�����������������c++�涨��������C++�п������ø÷������c����
����2���������롰C"��һ�����α������ߺ���ʱ������ͷ�ļ��У�extern int g_Num�������þ��������������߱��������÷�Χ�Ĺؼ��֣��������ĺ����ͱ��������ڱ����뵥Ԫ�����������뵥Ԫʹ��
 
/*--------------------------------���������------------------------------------------*/
extern  int diyakg, jingshui_gaoyakg,  jingshui_chaoyakg, shuiliu_chuanganqi;//���� 
extern int chaolv1,chaolv2, jingshui,culv,  gaoyabeng ;// 

/*--------------------------------ˮ��������-------------------------------------------*/
 extern volatile int count; //????????????????

 /*--------------------------------����-------------------------------------------*/
 extern byte chaolv1_chongxi_maichong_dixian ;
extern  byte loushui_maich_biaozhun ;
//unsigned int chaolv1chongxi_zongcishu = 0; /*??????????*/
extern  unsigned long accumulative ; /*?????????*/
extern  byte chxi_cishu ;			//?????????????
extern  byte leiji_biaozhun ;
extern  bool chaolv_chxi , loushui_bool ; //?????????????
extern  unsigned long chaolv1chongxi_zongcishu,chaolv2chongxi_zongcishu;
//extern Chrono ch_chaolv1_dcf;//��鳬�˵�ŷ�©ˮ

/*--------------------------------����-------------------------------------------*/
extern bool culv_chxi;
extern byte culv_chxi_cishu;
extern unsigned long culv_chxi_time,culvchongxi_zongcishu;
/*--------------------------------����-------------------------------------------*/
extern bool tiaoshikg ;
/*--------------------------------��ʾ������-------------------------------------------*/
extern bool display_f;
extern  byte buffer[200]; //??????????
extern unsigned int buffer_index ;
extern  byte brightness ; //???????50
extern bool set_once ; //???????????
extern  byte page ;		  //???0?????
extern byte pre_page ;   //???????????��???????
extern String pre_kongjian, pre_text;
//byte ff_starter = 0;
//  byte terminator ; //?????????
extern bool parse_ready ;
extern  bool eeprom_write ;
extern  bool xsp_shezhi ;
extern  String order_sended ; 
//extern Chrono    xianshi_jiange;
//extern Chrono  yinyong_shuiman_xianshi_jiange,shch_shuiman_xianshi_jiange;
extern unsigned long guanji_xianshi_jiange;
extern bool at_zhuangtai,at_shuju;
extern String message_todisplay[10];
/*--------------------------------��ˮ-------------------------------------------*/
extern bool guanbi ;			  //Զ�̿��� true�ػ� false����
extern  byte zhishuishijian_set ;	 //?????????50?????255????
extern  unsigned long zhishuizongshijian; //
extern byte yinyong_danci,jigshui_danci;//���η���ʱ��
extern  byte xianshi;
extern  bool yinyong_zhishui , shchan_zhishui ;
extern byte zhishui_shjian_add;//��ˮʱ��洢��ַ
extern  byte shuimandengdaishijian_set ; //??????????????????? 6?????
extern  unsigned long zhishui_xianshi_jiange;
extern  byte zhishui_maichong_biaozhun ;

extern  byte chaoshi_cishu ; /*????2?��???????????*/
extern  byte feishuiguoshao_times ;
extern unsigned long zhishui_starttime,jingshui_dcf_starttime,zhishui_stoptime ;
extern  byte xie_jici;//�ۼƶ��ٴ�д��eeprom��ˮ��ʱ��
extern unsigned long yinyong_shuiman_xianshi,shch_shuiman_xianshi;
extern unsigned long jingshui_chaoya_xianshi_jiange;
extern unsigned long jingshui_bunengman_jiange;
/*--------------------------------ϴĤ-------------------------------------------*/
extern  byte jingshuiximo_shichang; //?????6????,??��????
extern bool xuyao_ximo,ximo_yucun ;
extern byte moci_ximo_maichong_biaozhun , ximo_shuiliu_jiance_cishu ;
//byte dcf_chxi_shichang = 40; //??????????????
//extern Chrono ch_ximo;
extern unsigned long ximo_start,ximo_xianshi_jiange;

/*--------------------------------����-------------------------------------------*/
//String state = ""; //??????
extern unsigned long alarm_jiange ;//��Ϸ��ͱ�����Ϣ
extern  bool jingshui_chaoya , feishuiguoshao , ximo_buneng_shuiman,baojing; 
//extern Chrono ch_xianshi_guanji_jiange;
//extern Chrono ch_alarm;
extern unsigned long baojing_begintime;//����ʱ���ڻ���ͣ��
//extern unsigned long feishuiguoshao_xianshi_jiange;
 extern bool baojing;

/*-------------------------------ȱˮ------------------------------------------*/
extern unsigned long queshui_xianshi_jiange;
/*-------------------------------tdsj���--------------------------------------*/

//extern  unsigned long tds_jiange;
extern unsigned int tds;
extern unsigned char tds_buffer[20];
extern unsigned int tds_buffer_index;
extern bool tds_jiexi;
