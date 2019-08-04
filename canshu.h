
#include <Arduino.h>

/*extern作用
作用1，当与“C”一起使用时，如 extern "C" void fun(int a, int b)，则编译器中fun这个函数名按照c语言规则命名，而不是用c++规定命名。故C++中可以利用该法则调用c函数
作用2，当他不与“C"在一起修饰变量或者函数时，如在头文件中，extern int g_Num；其作用就是声明函数或者变量的作用范围的关键字，其声明的函数和变量可以在本编译单元或者其他编译单元使用
 
/*--------------------------------输入与输出------------------------------------------*/
extern  int diyakg, jingshui_gaoyakg,  jingshui_chaoyakg, shuiliu_chuanganqi;//输入 
extern int chaolv1,chaolv2, jingshui,culv,  gaoyabeng ;// 

/*--------------------------------水流传感器-------------------------------------------*/
 extern volatile int count; //????????????????

 /*--------------------------------超滤-------------------------------------------*/
 extern byte chaolv1_chongxi_maichong_dixian ;
extern  byte loushui_maich_biaozhun ;
//unsigned int chaolv1chongxi_zongcishu = 0; /*??????????*/
extern  unsigned long accumulative ; /*?????????*/
extern  byte chxi_cishu ;			//?????????????
extern  byte leiji_biaozhun ;
extern  bool chaolv_chxi , loushui_bool ; //?????????????
extern  unsigned long chaolv1chongxi_zongcishu,chaolv2chongxi_zongcishu;
//extern Chrono ch_chaolv1_dcf;//检查超滤电磁阀漏水

/*--------------------------------粗滤-------------------------------------------*/
extern bool culv_chxi;
extern byte culv_chxi_cishu;
extern unsigned long culv_chxi_time,culvchongxi_zongcishu;
/*--------------------------------调试-------------------------------------------*/
extern bool tiaoshikg ;
/*--------------------------------显示屏串口-------------------------------------------*/
extern bool display_f;
extern  byte buffer[200]; //??????????
extern unsigned int buffer_index ;
extern  byte brightness ; //???????50
extern bool set_once ; //???????????
extern  byte page ;		  //???0?????
extern byte pre_page ;   //???????????锟斤拷???????
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
/*--------------------------------制水-------------------------------------------*/
extern bool guanbi ;			  //远程控制 true关机 false运行
extern  byte zhishuishijian_set ;	 //?????????50?????255????
extern  unsigned long zhishuizongshijian; //
extern byte yinyong_danci,jigshui_danci;//单次分钟时间
extern  byte xianshi;
extern  bool yinyong_zhishui , shchan_zhishui ;
extern byte zhishui_shjian_add;//制水时间存储地址
extern  byte shuimandengdaishijian_set ; //??????????????????? 6?????
extern  unsigned long zhishui_xianshi_jiange;
extern  byte zhishui_maichong_biaozhun ;

extern  byte chaoshi_cishu ; /*????2?锟斤拷???????????*/
extern  byte feishuiguoshao_times ;
extern unsigned long zhishui_starttime,jingshui_dcf_starttime,zhishui_stoptime ;
extern  byte xie_jici;//累计多少次写入eeprom制水总时间
extern unsigned long yinyong_shuiman_xianshi,shch_shuiman_xianshi;
extern unsigned long jingshui_chaoya_xianshi_jiange;
extern unsigned long jingshui_bunengman_jiange;
/*--------------------------------洗膜-------------------------------------------*/
extern  byte jingshuiximo_shichang; //?????6????,??锟斤拷????
extern bool xuyao_ximo,ximo_yucun ;
extern byte moci_ximo_maichong_biaozhun , ximo_shuiliu_jiance_cishu ;
//byte dcf_chxi_shichang = 40; //??????????????
//extern Chrono ch_ximo;
extern unsigned long ximo_start,ximo_xianshi_jiange;

/*--------------------------------报警-------------------------------------------*/
//String state = ""; //??????
extern unsigned long alarm_jiange ;//间断发送报警信息
extern  bool jingshui_chaoya , feishuiguoshao , ximo_buneng_shuiman,baojing; 
//extern Chrono ch_xianshi_guanji_jiange;
//extern Chrono ch_alarm;
extern unsigned long baojing_begintime;//报警时间内机器停机
//extern unsigned long feishuiguoshao_xianshi_jiange;
 extern bool baojing;

/*-------------------------------缺水------------------------------------------*/
extern unsigned long queshui_xianshi_jiange;
/*-------------------------------tdsj检测--------------------------------------*/

//extern  unsigned long tds_jiange;
extern unsigned int tds;
extern unsigned char tds_buffer[20];
extern unsigned int tds_buffer_index;
extern bool tds_jiexi;
