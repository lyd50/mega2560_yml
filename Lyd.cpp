#include <Arduino.h>
#include "canshu.h"
#include <EEPROMex.h>
//#include "hz.h"
#define EEPROM_SIZE 200


#include "Lyd.h"

void add_message(String message)
{
	for (int i = 0; i < 10; i++)
	{
		if (message_todisplay[i] == "")
		{
			message_todisplay[i] = message;
			break;
		}
	}
}

/*void  add_update_message(String message)
{	for (int i = 0; i < 10; i++)
	{
		if (update_message[i] == "")
		{
			update_message[i] = message;
			break;
		}
	}
}*/
void  culvchongxi()
{
	for (int i = 0; i < culv_chxi_cishu; i++) //����1��ϴ
	{
       xianshiping_sendorder2("zhuangtai", "���ڳ�ϴ����1��" + (String)(i + 1) + "��");

		culvchongxi_zongcishu = culvchongxi_zongcishu + 1;
		//String s = itoa(chaolv1chongxi_zongcishu, str, 10);
		EEPROM.updateLong(24, culvchongxi_zongcishu); //?????????
		

		xianshiping_sendorder2("shuju", "���˳�ϴ������" + (String)culvchongxi_zongcishu);
		//delay(1500);
		tiaoshi("chongxi culv");
		//digitalWrite(zongjin, HIGH);//�ر��ܽ�ˮ���ó���ʽ��ŷ�

		digitalWrite(culv, HIGH); //????????

		Serial.println(culvchongxi_zongcishu, DEC);

		//detect(500); //?3??
		//delay(2000);
		//digitalWrite(zongjin, HIGH);

		//xianshiping_sendorder2("shuju", "���˳�ϴ��������" + (String)count);
		//edp_upload_int(hz[1], count); //���˳�ϴ������

		delay(4000);
		//digitalWrite(zongjin, LOW);

		digitalWrite(culv, LOW);
		delay(8000); //??????
	}
	
	culv_chxi=false;


}
void chaolvchongxi()
{ 
	//?????????? ???????????????
	for (int i = 0; i < chxi_cishu; i++) //����1��ϴ
	{
		xianshiping_sendorder2("zhuangtai", "���ڳ�ϴ����1��" + (String)(i + 1) + "��");

		chaolv1chongxi_zongcishu = chaolv1chongxi_zongcishu + 1;
		//String s = itoa(chaolv1chongxi_zongcishu, str, 10);
		EEPROM.updateLong(8, chaolv1chongxi_zongcishu); //?????????
		//edp_upload_int(hz[0], chaolv1chongxi_zongcishu); //���˳�ϴ����

		xianshiping_sendorder2("shuju", "����1��ϴ������" + (String)chaolv1chongxi_zongcishu);
		//delay(1500);
		tiaoshi("chongxi chlv");
		//digitalWrite(zongjin, HIGH);//�ر��ܽ�ˮ���ó���ʽ��ŷ�

		digitalWrite(chaolv1, HIGH); //????????

		Serial.println(chaolv1chongxi_zongcishu, DEC);

		//detect(500); //?3??
		//delay(2000);
		//digitalWrite(zongjin, HIGH);

		//xianshiping_sendorder2("shuju", "���˳�ϴ��������" + (String)count);
		//edp_upload_int(hz[1], count); //���˳�ϴ������

		delay(4000);
		//digitalWrite(zongjin, LOW);

		digitalWrite(chaolv1, LOW);
		delay(8000); //??????

		for (int i = 0; i < chxi_cishu; i++) //����2��ϴ
		{
			xianshiping_sendorder2("zhuangtai", "���ڳ�ϴ����2��" + (String)(i + 1) + "��");

			chaolv2chongxi_zongcishu = chaolv2chongxi_zongcishu + 1;
			//String s = itoa(chaolv1chongxi_zongcishu, str, 10);
			EEPROM.updateLong(16, chaolv2chongxi_zongcishu); //?????????
			//edp_upload_int(hz[0], chaolv1chongxi_zongcishu); //���˳�ϴ����

			xianshiping_sendorder2("shuju", "����2��ϴ������" + (String)chaolv1chongxi_zongcishu);
			//delay(1500);
			tiaoshi("chongxi chlv");
			//digitalWrite(zongjin, HIGH);//�ر��ܽ�ˮ���ó���ʽ��ŷ�

			digitalWrite(chaolv2, HIGH); //????????

			Serial.println(chaolv1chongxi_zongcishu, DEC);

			//detect(500); //?3??
			//delay(2000);
			//digitalWrite(zongjin, HIGH);

			//xianshiping_sendorder2("shuju", "���˳�ϴ��������" + (String)count);
			//edp_upload_int(hz[1], count); //���˳�ϴ������

			delay(4000);
			//digitalWrite(zongjin, LOW);

			digitalWrite(chaolv2, LOW);
			delay(8000); //??????
		}
		chaolv_chxi = false; //һ��Ҫ����
							 //if (EEPROM.commit())
							 //{
							 //tiaoshi("�ɹ�д��");
							 //}
							 //else
							 //{
							 //tiaoshi("д��ʧ��");
							 //}
	}

}

	void count_function()
	{
		count++;
		delay(3);
	}

	void closeall() /*?????????*/
	{
		digitalWrite(chaolv1, LOW);
		//digitalWrite(mo_jinshui, LOW); //????
		//digitalWrite(chongxi, LOW);	//????
		digitalWrite(jingshui, LOW);
		digitalWrite(gaoyabeng, LOW);
		//digitalWrite(zongjin, LOW);
		//digitalWrite(youxian, LOW);
		//digitalWrite(jiare, LOW);
	}
	void display_message() //������ʾ
	{
		for (int i = 0; i < 10; i++)
		{
			if (message_todisplay[i] != "")
			{
				if (at_zhuangtai == false)
				{
					xianshiping_sendorder2("zhuangtai", message_todisplay[i]);
					at_zhuangtai = true;
					at_shuju = false;
					message_todisplay[i] = ""; //���
					delay(1500);
					break;
				}

				if (at_shuju == false)
				{
					xianshiping_sendorder2("shuju", message_todisplay[i]);
					at_zhuangtai = false;
					at_shuju = true;
					message_todisplay[i] = ""; //���
					delay(1500);
					break;
				}
			}
		}
	}

	void decide_chaolv_chxi(unsigned long long1)
	{
		//zhishuizongshijian = zhishuizongshijian + long1;
		//EEPROM.writeLong(3, zhishuizongshijian);

		accumulative = accumulative + long1;

		if (accumulative > leiji_biaozhun * 60000)
		{
			chaolv_chxi = true;
			accumulative = 0;
		}
	}
	void detect(unsigned long yongshi) /*???????,??��????*/
	{
		count = 0; /*????????????,???????*/
		unsigned long begintime2 = millis();
		unsigned long endtime2;
		attachInterrupt(digitalPinToInterrupt(shuiliu_chuanganqi), count_function, RISING);
		do
		{
			endtime2 = millis();
		} while (endtime2 - begintime2 < yongshi);

		detachInterrupt(digitalPinToInterrupt(shuiliu_chuanganqi));
	}

	void eeprom_read()
	{
		/* if (!EEPROM.isReady(EEPROM_SIZE))
		{
			Serial.println("failed to initialise EEPROM");
			delay(1000000);
		}*/

		//chaolv1_chongxi_maichong_dixian = EEPROM.readByte(0); //���˳�ϴ�������
		//loushui_maich_biaozhun = EEPROM.readByte(2);		 //����©ˮ�����׼
		//chxi_cishu = EEPROM.readByte(4);					 //���س��˳�ϴ����
		//leiji_biaozhun = EEPROM.readByte(6);		   //��ˮ�ۼƶ೤ʱ���ϴһ�γ���
		chaolv1chongxi_zongcishu = EEPROM.readLong(8); //����1��ϴ�ܴ���
		// tiaoshi("?????????" + (String)chaolv1chongxi_zongcishu);
		
       chaolv2chongxi_zongcishu = EEPROM.readLong(16); //����2��ϴ�ܴ���
		//zhishuishijian_set = EEPROM.readByte(50); //������ˮ��ʱ,50
		//tiaoshi("��ˮ��ʱ��" + (String)zhishuishijian_set);
		//zhishui_maichong_biaozhun = 60;					 //EEPROM.readByte(52); //��ˮʱ��С������,52
		// tiaoshi("???????????" + (String)zhishui_maichong_biaozhun);
		//chaoshi_cishu = EEPROM.readByte(54);			 //��ˮʱ����ĳ�ʱ����
		//shuimandengdaishijian_set = EEPROM.readByte(56); //��ˮ��ŷ��رպ��ˮ���ȴ�ʱ�� 56

		zhishui_shjian_add = EEPROM.readByte(58); //�����ˮ��ʱ�����ʼ��ַ��Ĭ��60

		zhishuizongshijian = EEPROM.readLong(zhishui_shjian_add); //��ˮ��ʱ��   ��60��ַ��ʼ�����ˮ��ʱ��,ռ4���ֽ�

		tiaoshi("��ˮ�ܷ��ӣ�" + (String)zhishuizongshijian);

		//version = EEPROM.readULong(80); //bin�汾

		//jingshuiximo_shichang = EEPROM.readByte(100);		//��ˮϴĤʱ��
		//ximo_shuiliu_jiance_cishu = EEPROM.readByte(102);   //ϴĤˮ�������� 102
		//moci_ximo_maichong_biaozhun = EEPROM.readByte(104); //ϴĤĩ�������׼�����ڴ�ֵ��Ϊ����ʧЧ 104
		//guanbi = EEPROM.readBool(106);						//Զ�̹ر��趨
	}

	
	
	



	
	
	
	
	
	void xianshiping_sendorder2(String kongjian, String text) //?????????
	{
		if (page == 0)
		{
			Serial1.print(kongjian + ".txt=\"" + text + "\"");
			for (int i = 0; i < 3;)
			{
				Serial1.write(0xff);
				i++;
			}
		}
		//delay(1500);
	}

	void rcvDebug(unsigned char *rcv, int len)
	{
		int i;

		Serial.print("edp���յ�����");
		Serial.println(len, DEC);
		for (i = 0; i < len; i++)
		{
			Serial.print(rcv[i], 16);
			Serial.print(" ");
		}
		Serial.println("");
	}

	

	
	
	void send_order() //��������ش���ʾ��������������?
	{
		/*-----------------------------3��ҳ��:��������---------------------------------*/
		if (page == 3)
		{

			if (set_once == true)
			{

				xianshiping_sendorder1("n0", chaolv1_chongxi_maichong_dixian);
				xianshiping_sendorder1("n1", loushui_maich_biaozhun);
				xianshiping_sendorder1("n2", chxi_cishu);
				xianshiping_sendorder1("n3", leiji_biaozhun);
				set_once = false;
			}
		}
		/*----------------------------4��ҳ��:��ˮ����-----------------------------*/
		if (page == 4)
		{
			if (set_once == true)
			{
				xianshiping_sendorder1("n0", zhishuishijian_set);
				xianshiping_sendorder1("n1", zhishui_maichong_biaozhun);
				xianshiping_sendorder1("n2", chaoshi_cishu);
				xianshiping_sendorder1("n3", shuimandengdaishijian_set);

				set_once = false;
			}
		}
		/*------------------------------5��ϴĤ����---------------------------------*/
		if (page == 5)
		{
			if (set_once == true)
			{
				xianshiping_sendorder1("n0", jingshuiximo_shichang);
				xianshiping_sendorder1("n1", ximo_shuiliu_jiance_cishu);
				xianshiping_sendorder1("n2", moci_ximo_maichong_biaozhun);
				// xianshiping_sendorder1("n3", dcf_chxi_shichang);
				set_once = false;
			}
		}
		/*-------------------------------11������ҳ�洦��----------------------------------*/
		if (page == 7)
		{
			if (set_once == true)
			{

				xianshiping_sendorder1("n0", brightness);
				set_once = false;
			}
		}
	}
	void serial_print(byte * rcv, int len)
	{
		int i;
		Serial.print("jie shou:");
		Serial.println(len, DEC);
		for (i = 0; i < len; i++)
		{
			Serial.print(rcv[i], 16);
			Serial.print(" ");
		}
		Serial.println("");
	}

	

	void tiaoshi(String pingmuxianshi)
	{

		if (tiaoshikg == true)
		{

			Serial.println(pingmuxianshi);
		}
	}

	void tds_send_parse()
	{
		if (tds_jiexi == false)
		{
			while (Serial2.available()) //����ǰ���
			{
				Serial2.read();
			}
			for (int i = 0; i < 3;)
			{
				Serial2.write(0xfd);
				i++;
			}

			//tds_jiange = millis();
			tds_buffer_index = 0;
			tds_jiexi=true;//��ֻ֤����һ��
		}

		while (Serial2.available())
		{ //int byte_count =Serial1.available();

			tds_buffer[tds_buffer_index] = Serial2.read();
			if (tds_buffer[0] == 0xFD) //���ص�ȷ����Ϣ
			{
				tds_jiexi = true;
			}
			else
			{
				while (Serial2.available()) //���
				{
					Serial2.read();
				}
				return;
			}
			tds_buffer_index++;
		}

		if (tds_jiexi == true)
		{
			//rcvDebug(tds_buffer, tds_buffer_index);
			if (tds_buffer[0] == 0xFD)
			{
				tds = tds_buffer[1] + tds_buffer[2] * 256;
			}
			
			add_message("��ˮtdsֵ��" + (String)tds);
			tiaoshi("tds:" + (String)tds);
			tds_jiexi = false;//Ϊ�´η�������׼��
		}
	}

	

	
	
	void xianshiping_sendorder1(String kongjian, int value) //?????????
	{

		Serial1.print(kongjian + ".val=" + value + "");
		for (int i = 0; i < 3;)
		{
			Serial1.write(0xff);
			i++;
		};
	}