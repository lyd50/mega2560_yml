
#include <Arduino.h>
void add_message(String message);



void closeall() ;/**/

void tiaoshi(String pingmuxianshi);
void culvchongxi();
void chaolvchongxi();



void count_function();

void detect(unsigned long yongshi); 

void decide_chaolv_chxi(unsigned long long1);

void display_message();
void eeprom_read();
void rcvDebug(unsigned char *rcv, int len);
void Serial2_command_parse();

void serial_print(byte *rcv, int len);

 void tds_send_parse();

extern  void tiaoshi(String pingmuxianshi);
extern  void xianshiping_sendorder1(String kongjian, int value) ;

extern void xianshiping_sendorder2(String kongjian, String text) ;

