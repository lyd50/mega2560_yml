#include <Arduino.h>
#include "Lyd.h"
#include <stdlib.h>
#include <HardwareSerial.h>
#include <EEPROMex.h>
#include "canshu.h"

void setup()
{

	{							//�����������
		pinMode(diyakg, INPUT); //����
		digitalWrite(diyakg, 1);

		pinMode(jingshui_chaoyakg, INPUT); //��ˮ��ѹ����
		digitalWrite(jingshui_chaoyakg, 1);

		pinMode(jingshui_gaoyakg, INPUT); //����
		digitalWrite(jingshui_chaoyakg, 1);

		pinMode(shuiliu_chuanganqi, INPUT); //����
         pinMode(culv,OUTPUT);
		pinMode(chaolv1, OUTPUT);
		pinMode(chaolv2, OUTPUT); //�ڶ�������

		pinMode(jingshui, OUTPUT); //��ˮϴĤ

		pinMode(gaoyabeng, OUTPUT); //����ˮ��ŷ�
	}

	Serial.begin(9600); //
	Serial1.begin(9600);//��ʾ��
	Serial2.begin(9600);//tds���
  EEPROM.setMemPool(0,200);

	closeall();

	eeprom_read();

	chaolv_chxi = true; //������ϴһ�γ���
	culv_chxi=true;//����������һ�γ�ϴ����
}

void loop()
{

	/*--------------------------------------ǿ��ͣ��ϴĤ----------------------------*/

	if (xuyao_ximo == true)
	{

		if (digitalRead(gaoyabeng) == 1) //������һ��
		{

			digitalWrite(gaoyabeng, LOW);
			delay(1000);

			digitalWrite(jingshui, LOW);

			ximo_start = millis(); //ϴĤ��ʼʱ��
		}

		if (millis() - ximo_xianshi_jiange > 5000) //��ʾ�������ʾ 5��
		{

			xianshiping_sendorder2("zhuangtai", "ǿ��ͣ��ϴĤ");
			delay(1000);
			//edp_upload_string((String)hz[12], (String)hz[19]);											  //�ϴ�ϴĤ״̬	 //ǿ��ͣ��ϴĤ
			xianshiping_sendorder2("shuju", "ϴĤ�趨ʱ����" + (String)(jingshuiximo_shichang) + "����"); //???څ???????
			ximo_xianshi_jiange = millis();																  //

			if (digitalRead(jingshui_gaoyakg) == 1)
			{

				xianshiping_sendorder2("zhuangtai", "�����þ�ˮ��Ҫ��ˮ");
			}

			if ((millis() - ximo_start) < jingshuiximo_shichang * 60000)
			{
				detect(3000);
				xianshiping_sendorder2("shuju", "ϴĤʱˮ����������" + (String)count);
				//xianshiping_sendorder2("zhuangtai", "ϴĤ����ʱ��" + (String)(ch_ximo.elapsed()));
			}

			else //ֻ����һ��
			{
				xianshiping_sendorder2("zhuangtai", "��ˮϴĤ����"); //?????????
				xuyao_ximo = false;
			}
		}
	}

	display_message();

	/*--------------------------------���Ᵽ��--------------------------------------------*/

	{

		/*if (digitalRead(jingshui_chaoyakg) == 0) //��ˮѹ������
		{
			if (ch_alarm.hasPassed(20000, true))
			{
				xianshiping_sendorder2("zhuangtai", "��ˮ��ѹͣ�������ۺ�");
				tiaoshi("��ˮ��ѹ�����ۺ�");
				edp_upload_string((String)hz[21], (String)hz[22]); //���� ��ˮ��ѹͣ�������ۺ�
				closeall();
				ld.print("chaoya 1", 0);
			}

			return;
		}*/

		if (feishuiguoshao == true) //��ˮ���ٹ���ͣ��
		{

			baojing = true;
			//ld.print("feishui1");
			unsigned long dengdai;

			if (tiaoshikg == true)
			{
				dengdai = 180000;
			}
			else
			{
				dengdai = 1800000;
			}
			if ((millis() - baojing_begintime) < dengdai)
			{
				if (millis() - alarm_jiange > 6000)
				{

					tiaoshi("��ˮ���ٹ���ͣ��,30���Ӻ�����ˮ");

					add_message("��ˮ���ٹ��ϵȴ�");
					add_message("��ˮ���ٹ���ͣ��,30���Ӻ�����ˮ");

					alarm_jiange = millis();
				}
				closeall();
				digitalWrite(jingshui, HIGH);

				return;
			}

			else //����һ��
			{
				alarm_jiange = 0;
				add_message("����ͣ��30���Ӻ��ٿ�ʼ��ˮ");
				tiaoshi("30���Ӻ��ٿ�ʼ��ˮ");
				feishuiguoshao_times = 0; //��ˮ���ٴ�������
				feishuiguoshao = false;
				baojing = false;
				digitalWrite(jingshui, LOW);
				chaolvchongxi(); //��ֹ��ѹʽ����Ĥ����
			}
		}

		if (ximo_buneng_shuiman == true) //ֻ������
		{

			baojing = true;
			unsigned long dengdai;

			if (tiaoshikg == true)
			{
				dengdai = 60000;
			}
			else
			{
				dengdai = 600000;
			}
			if (millis() - baojing_begintime < dengdai)
			{

				if (millis() - jingshui_bunengman_jiange > 7000)
				{

					add_message("��ˮ��ŷ��رպ�ˮ���趨ʱ���ڲ���ˮ��������ͣ��10����");
					//xianshiping_sendorder2("guzh_tishi", "?????????7??????????????????????");
					tiaoshi("��ˮ�ر����7���Ӻ���ˮ��ͣ��������ͣ��");
					closeall();
					//digitalWrite(zongjin, LOW);
				}
			}

			else
			{
				baojing = false;
				add_message("��ˮ��ŷ��رպ�ˮ���趨ʱ���ڲ���ˮ��������ͣ��10���Ӻ�����");
				tiaoshi("��ˮ��ŷ��رպ�ˮ���趨ʱ���ڲ���ˮ��������ͣ��10���Ӻ�����");
				ximo_buneng_shuiman = false;
			}
		}
	}

	if (baojing == false)
	{

		if (digitalRead(diyakg) == 0)
		{    

			/*--------------------���˴��˳�ϴ--------------------------------*/
			if (digitalRead(gaoyabeng) == 0) //��֤��ֹͣ״̬�³�ϴ����
			{    if (culv_chxi == true || (millis()-culv_chxi_time)>86400000) /*��һ��������ϴ��ʱ�䳬��24Сʱ��ϴ*/
				{  

					xianshiping_sendorder2("zhuangtai", "��ϴ����");

					tiaoshi("��ϴ����");

					culvchongxi();
					culv_chxi_time=millis();//��ϴʱ��
				}

				if (chaolv_chxi == true) /*��һ��������ϴ���ۻ�ʱ�䳬��1Сʱ��ϴ*/
				{  

					xianshiping_sendorder2("zhuangtai", "��ϴ����");

					tiaoshi("��ϴ����");

					chaolvchongxi();
				}
			}

			if (digitalRead(jingshui_chaoyakg) == 1) //��ˮû�г�ѹ
			{

				if (xuyao_ximo == false)
				{

					/*----------------------------------------------��ˮ��ˮ----------------------------------------*/

					if (digitalRead(jingshui_gaoyakg) == 1) //��ˮ��
					{
						/*if (ch_chaolv1_dcf.hasPassed(600, true)) //10���Ӻ��鳬�˵�ŷ�©ˮ�񣬶㿪ϴĤ��ÿ10���Ӽ��һ��
				           {
					       detect(3000);
					        if (count > 10)
					        {
					     	tiaoshi("���˳�ϴ��ŷ�©ˮ");
					     	edp_upload_string((String)hz[21], (String)hz[32]); //���˳�ϴ��ŷ�©ˮ
					     	xianshiping_sendorder2("zhuangtai", "���˳�ϴ��ŷ�©ˮ");
					        }
					         else
					        {
					      	tiaoshi("���˳�ϴ��ŷ���©ˮ");
						    edp_upload_string((String)hz[21], (String)hz[33]); //���˳�ϴ��ŷ���©ˮ
					      	xianshiping_sendorder2("zhuangtai", "���˳�ϴ��ŷ���©ˮ");
					         }
				              }*/
						if (digitalRead(gaoyabeng) == 1) //ֻ����һ��
						{
							//digitalWrite(mo_jinshui, LOW);
							delay(1000);
							digitalWrite(gaoyabeng, LOW);
							delay(1000);
							zhishui_stoptime = millis();
							digitalWrite(jingshui, LOW);
							chaoshi_cishu = 0; //��ʱ��������

							digitalWrite(jingshui, LOW); //�򿪾�ˮ��Ӧ
							//fangdong_jiange = millis();
						}

						/* if (millis() - fangdong_jiange > 3600000)
						{
							chaolvchongxi(); //��ֹ��·��
							
							fangdong_jiange = millis();
						}*/

						if (millis() - shch_shuiman_xianshi > 15000) //�����ʾ,��ν���
						{
							xianshiping_sendorder2("zhuangtai", "��ˮˮ��"); //
							tiaoshi("��ˮˮ��");
							shch_shuiman_xianshi = millis();
						}
					}

					if (digitalRead(jingshui_gaoyakg) == 0) //��Ҫ��ˮ
					{

						/*------------------��ˮ����1��------------------------------------*/
						if (digitalRead(gaoyabeng) == 0) //��ѹ��û����ת��������ֻ����һ�Σ���ʼ��ˮ���ٽ���
						{
							zhishui_starttime = millis(); //��ѹ�ù�����ʼʱ��

							xianshiping_sendorder2("zhuangtai", "��ʼ��ˮ��ˮ"); //
							tiaoshi("��ʼ��ˮ��ˮ");

							jigshui_danci = 0;//��ˮ���ι���ʱ�� ����

							if ((zhishui_starttime - zhishui_stoptime < 180000) && (zhishui_stoptime != 0)) //������3���Ӳ��Ҳ��ǵ�һ��
							{
								ximo_yucun = false; //����ҪϴĤˮԤ��
							}
							else
							{
								ximo_yucun = true; //��ҪϴĤˮԤ��

								jingshui_dcf_starttime = millis(); //��ˮ��ŷ��õ翪ʼʱ��
							}									  

							
							delay(1000);
							digitalWrite(gaoyabeng, HIGH); /*??????*/
							delay(1000);
							
						}
						/*------------------��ˮ����2��------------------------------------*/

						if (digitalRead(gaoyabeng) == 1) /*����ת�ˣ���ˮ�У���Ϊ����ϴĤˮ�Ͳ�����2�����*/
						{

							if (ximo_yucun == true) //��Ҫ����ϴĤˮ
							{
								digitalWrite(jingshui, HIGH);
								//if (xianshi_jiange.hasPassed(6000, true))
								if (millis() - zhishui_xianshi_jiange > 5000)

								{
									//ld.print("jshudcf0", 0);
									xianshiping_sendorder2("zhuangtai", "��ˮ��ŷ��رգ��ȴ�ϴĤѹ��Ͱˮ��");
									tiaoshi("��ˮ��ŷ��رգ��ȴ�ϴĤѹ��Ͱˮ��");
									delay(1000);
									xianshiping_sendorder2("zhuangtai", "����ϴĤˮʱˮ��������Сֵ��" + (String)zhishui_maichong_biaozhun);

									xianshiping_sendorder2("shuju", "��ˮʱ��������" + (String)count);
									tiaoshi("��ˮʱ��������" + (String)count);
									zhishui_xianshi_jiange = millis();
								}

								if (digitalRead(jingshui_gaoyakg) == 0) //������ѹ����û�жϿ�
								{

									if ((millis() - jingshui_dcf_starttime) > shuimandengdaishijian_set * 60000) //��Ϊ5����
									{
										//7????????��????????????

										xianshiping_sendorder2("zhuangtai", "��ˮ����ر�" + (String)shuimandengdaishijian_set + "���Ӻ���Ȼ����ˮ��������ͣ��"); //?????????7????????????????????????
										tiaoshi("��ˮ����ر�" + (String)shuimandengdaishijian_set + "���Ӻ���Ȼ����ˮ��������ͣ��");

										ximo_buneng_shuiman = true; //����Ϊ��
										baojing_begintime = millis();

										return;
									}
								}

								if (digitalRead(jingshui_gaoyakg) == 1) //������ѹ���ضϿ���ֻ����һ��
								{
									digitalWrite(jingshui, LOW); //��ˮ��ŷ�ʧ���

									ximo_yucun = false;
									xianshiping_sendorder2("shuju", "ϴĤѹ��Ͱ" + String((millis() - jingshui_dcf_starttime) / 60000) + "����ˮ��");
									tiaoshi("ϴĤѹ��Ͱ" + String((millis() - jingshui_dcf_starttime) / 60000) + "����ˮ��");
									
								}
							}
							else //����Ҫ����ϴĤˮ
							{
								//��ʾ����ʾ
								if (millis() - zhishui_xianshi_jiange > 5000)
								{
									switch (xianshi)
									{
									case 0:
										//ld.print("yiny run", 0);

										xianshiping_sendorder2("zhuangtai", "��ˮ��ˮ��");

										xianshiping_sendorder2("shuju", "��ˮ��ˮ����ʱ��" + (String)jigshui_danci + "����");
										tiaoshi((String)(jigshui_danci) + "����");

										xianshiping_sendorder2("zhuangtai", "��ˮ�����趨��" + (String)zhishuishijian_set + "����");

										tiaoshi("��ˮ�����׼��" + (String)zhishui_maichong_biaozhun);
										break;
									case 1:
										//ld.print("puls" + (String)count, 0);
										xianshiping_sendorder2("zhuangtai", "��ˮʱˮ��������Сֵ��" + (String)zhishui_maichong_biaozhun);
										
										xianshiping_sendorder2("shuju", "��ˮʱ��������" + (String)count);
										tiaoshi("��ˮʱ��������" + (String)count);
										break;
									case 2:
										//ld.print("time" + String((int)(ch_beng.elapsed() / 60000), 4), 0);
										xianshiping_sendorder2("zhuangtai", "��ˮ�ܷ��ӣ�" + (String)zhishuizongshijian);
                                        tds_send_parse();//tdsֵ���
										break;
									}
									xianshi++;
									if (xianshi >= 3)
									{
										xianshi = 0;
									}
									zhishui_xianshi_jiange = millis();
								}

								if (jigshui_danci > zhishuishijian_set) //����һ��,��ˮʱ�䳬���趨
								{

									xianshiping_sendorder2("zhuangtai", "��ˮʱ�䳬�������趨ʱ��");
									tiaoshi("��ˮʱ�䳬�������趨ʱ��");
									digitalWrite(jingshui, HIGH);											   //��ˮ��ŷ��õ�ر�
									xianshiping_sendorder2("shuju", "��ˮ��ʱ������" + (String)chaoshi_cishu); //??????????
									chaoshi_cishu++;
									xuyao_ximo = true; //��ϴĤ������ر��й�

									chaolv_chxi = true; //��Ҫ��ϴ����
								}
							}
							//��ˮ��������ˮ��������ˮ����
							{

								detect(1000); //???????????????????

								if (count < zhishui_maichong_biaozhun)
								{
									feishuiguoshao_times++;

									xianshiping_sendorder2("zhuangtai", "��ˮ����:" + (String)feishuiguoshao_times + "��");
								}
								else
								{
									//xianshiping_sendorder2("zhuangtai", "��ˮ��������");

									feishuiguoshao_times = 0;
								}
								if (feishuiguoshao_times >= 30)
								{
									
									//xianshiping_sendorder2("zhuangtai", "��ˮ���ٲ���ֵΪ��");
									//xianshiping_sendorder2(0,"zhuangtai", "????");

									feishuiguoshao = true;
									baojing_begintime = millis();
									return;
								}
							}

							/*------------------��ˮ����4�����ü���-��ˮ��ʱ�� ���� ��ˮtdsֵ-----------*/
							//��������ʼ����ʱ�䣬��ʼʱ���ɱ�����������ֵ
							{

								if (millis() - zhishui_starttime > 60000) //1����
								{
									zhishuizongshijian++; //����

									xianshiping_sendorder2("zhuangtai", "��ˮ��ʱ����" + (String)zhishuizongshijian + "����");

									jigshui_danci++;

									xie_jici++;
									if (xie_jici >= 10) //10����д��һ��
									{					/*-------tds���------------*/
														//tds_send_parse();//10���Ӽ��һ��

										EEPROM.updateLong(zhishui_shjian_add, zhishuizongshijian);
										/* 	if (EEPROM.commit())
											{
												tiaoshi("�ɹ�д��");
											}
											else
											{
												tiaoshi("д��ʧ��");

												zhishui_shjian_add = zhishui_shjian_add + 4;
												EEPROM.writeByte(58, zhishui_shjian_add);
												EEPROM.writeULong(64, zhishuizongshijian);

												EEPROM.commit();
											}*/

										xie_jici = 0;
									}

									zhishui_starttime = millis();
								}
							}
						}
					}
				}
			}
			else //��ˮ��ѹ
			{	
				if (millis() - jingshui_chaoya_xianshi_jiange > 7000)
				{
					jingshui_chaoya_xianshi_jiange = millis();
					xianshiping_sendorder2("zhuangtai", "��ˮ��ѹͣ�������ۺ�");
					tiaoshi("��ˮ��ѹ�����ۺ�");
					
					closeall();
				
				}
			}
		}
		else
		{
			
			//ȱˮ״̬�����û����ʱ������������������ʾ���ش����󱨾�,�������ʾ������
			if (millis() - queshui_xianshi_jiange > 7000)
			{
				queshui_xianshi_jiange = millis();
				//ld.print("queshui1", 0);
				xianshiping_sendorder2("zhuangtai", "ȱˮͣ��");			

				tiaoshi("ȱˮ��ʾһ��");				
				closeall();
				
			}
			
		}

		
		
	}
}
