#include <Arduino.h>
#include "Lyd.h"
#include <stdlib.h>
#include <HardwareSerial.h>
#include <EEPROMex.h>
#include "canshu.h"

void setup()
{

	{							//输入输出设置
		pinMode(diyakg, INPUT); //下拉
		digitalWrite(diyakg, 1);

		pinMode(jingshui_chaoyakg, INPUT); //净水超压下拉
		digitalWrite(jingshui_chaoyakg, 1);

		pinMode(jingshui_gaoyakg, INPUT); //下拉
		digitalWrite(jingshui_chaoyakg, 1);

		pinMode(shuiliu_chuanganqi, INPUT); //上拉
         pinMode(culv,OUTPUT);
		pinMode(chaolv1, OUTPUT);
		pinMode(chaolv2, OUTPUT); //第二个超滤

		pinMode(jingshui, OUTPUT); //净水洗膜

		pinMode(gaoyabeng, OUTPUT); //带进水电磁阀
	}

	Serial.begin(9600); //
	Serial1.begin(9600);//显示屏
	Serial2.begin(9600);//tds检测
  EEPROM.setMemPool(0,200);

	closeall();

	eeprom_read();

	chaolv_chxi = true; //开机冲洗一次超滤
	culv_chxi=true;//开机重启第一次冲洗粗滤
}

void loop()
{

	/*--------------------------------------强制停机洗膜----------------------------*/

	if (xuyao_ximo == true)
	{

		if (digitalRead(gaoyabeng) == 1) //仅运行一次
		{

			digitalWrite(gaoyabeng, LOW);
			delay(1000);

			digitalWrite(jingshui, LOW);

			ximo_start = millis(); //洗膜开始时间
		}

		if (millis() - ximo_xianshi_jiange > 5000) //显示屏间隔显示 5秒
		{

			xianshiping_sendorder2("zhuangtai", "强制停机洗膜");
			delay(1000);
			//edp_upload_string((String)hz[12], (String)hz[19]);											  //上传洗膜状态	 //强制停机洗膜
			xianshiping_sendorder2("shuju", "洗膜设定时长：" + (String)(jingshuiximo_shichang) + "分钟"); //???趨???????
			ximo_xianshi_jiange = millis();																  //

			if (digitalRead(jingshui_gaoyakg) == 1)
			{

				xianshiping_sendorder2("zhuangtai", "生产用净水需要制水");
			}

			if ((millis() - ximo_start) < jingshuiximo_shichang * 60000)
			{
				detect(3000);
				xianshiping_sendorder2("shuju", "洗膜时水流脉冲数：" + (String)count);
				//xianshiping_sendorder2("zhuangtai", "洗膜已用时：" + (String)(ch_ximo.elapsed()));
			}

			else //只进入一次
			{
				xianshiping_sendorder2("zhuangtai", "净水洗膜结束"); //?????????
				xuyao_ximo = false;
			}
		}
	}

	display_message();

	/*--------------------------------意外保护--------------------------------------------*/

	{

		/*if (digitalRead(jingshui_chaoyakg) == 0) //净水压力过高
		{
			if (ch_alarm.hasPassed(20000, true))
			{
				xianshiping_sendorder2("zhuangtai", "净水超压停机，报售后");
				tiaoshi("净水超压，报售后");
				edp_upload_string((String)hz[21], (String)hz[22]); //报警 净水超压停机，报售后
				closeall();
				ld.print("chaoya 1", 0);
			}

			return;
		}*/

		if (feishuiguoshao == true) //废水过少故障停机
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

					tiaoshi("废水过少故障停机,30分钟后再制水");

					add_message("废水过少故障等待");
					add_message("废水过少故障停机,30分钟后再制水");

					alarm_jiange = millis();
				}
				closeall();
				digitalWrite(jingshui, HIGH);

				return;
			}

			else //进入一次
			{
				alarm_jiange = 0;
				add_message("保护停机30分钟后再开始制水");
				tiaoshi("30分钟后再开始制水");
				feishuiguoshao_times = 0; //废水过少次数置零
				feishuiguoshao = false;
				baojing = false;
				digitalWrite(jingshui, LOW);
				chaolvchongxi(); //防止外压式超滤膜堵塞
			}
		}

		if (ximo_buneng_shuiman == true) //只能重启
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

					add_message("净水电磁阀关闭后净水在设定时间内不能水满，保护停机10分钟");
					//xianshiping_sendorder2("guzh_tishi", "?????????7??????????????????????");
					tiaoshi("净水关闭输出7分钟后不能水满停机，报警停机");
					closeall();
					//digitalWrite(zongjin, LOW);
				}
			}

			else
			{
				baojing = false;
				add_message("净水电磁阀关闭后净水在设定时间内不能水满，保护停机10分钟后运行");
				tiaoshi("净水电磁阀关闭后净水在设定时间内不能水满，保护停机10分钟后运行");
				ximo_buneng_shuiman = false;
			}
		}
	}

	if (baojing == false)
	{

		if (digitalRead(diyakg) == 0)
		{    

			/*--------------------超滤粗滤冲洗--------------------------------*/
			if (digitalRead(gaoyabeng) == 0) //保证泵停止状态下冲洗超滤
			{    if (culv_chxi == true || (millis()-culv_chxi_time)>86400000) /*第一次启动冲洗或时间超过24小时冲洗*/
				{  

					xianshiping_sendorder2("zhuangtai", "冲洗粗滤");

					tiaoshi("冲洗粗滤");

					culvchongxi();
					culv_chxi_time=millis();//冲洗时间
				}

				if (chaolv_chxi == true) /*第一次启动冲洗或累积时间超过1小时冲洗*/
				{  

					xianshiping_sendorder2("zhuangtai", "冲洗超滤");

					tiaoshi("冲洗超滤");

					chaolvchongxi();
				}
			}

			if (digitalRead(jingshui_chaoyakg) == 1) //净水没有超压
			{

				if (xuyao_ximo == false)
				{

					/*----------------------------------------------净水制水----------------------------------------*/

					if (digitalRead(jingshui_gaoyakg) == 1) //净水满
					{
						/*if (ch_chaolv1_dcf.hasPassed(600, true)) //10分钟后检查超滤电磁阀漏水否，躲开洗膜，每10分钟检查一次
				           {
					       detect(3000);
					        if (count > 10)
					        {
					     	tiaoshi("超滤冲洗电磁阀漏水");
					     	edp_upload_string((String)hz[21], (String)hz[32]); //超滤冲洗电磁阀漏水
					     	xianshiping_sendorder2("zhuangtai", "超滤冲洗电磁阀漏水");
					        }
					         else
					        {
					      	tiaoshi("超滤冲洗电磁阀不漏水");
						    edp_upload_string((String)hz[21], (String)hz[33]); //超滤冲洗电磁阀不漏水
					      	xianshiping_sendorder2("zhuangtai", "超滤冲洗电磁阀不漏水");
					         }
				              }*/
						if (digitalRead(gaoyabeng) == 1) //只进入一次
						{
							//digitalWrite(mo_jinshui, LOW);
							delay(1000);
							digitalWrite(gaoyabeng, LOW);
							delay(1000);
							zhishui_stoptime = millis();
							digitalWrite(jingshui, LOW);
							chaoshi_cishu = 0; //超时次数置零

							digitalWrite(jingshui, LOW); //打开净水供应
							//fangdong_jiange = millis();
						}

						/* if (millis() - fangdong_jiange > 3600000)
						{
							chaolvchongxi(); //防止管路冻
							
							fangdong_jiange = millis();
						}*/

						if (millis() - shch_shuiman_xianshi > 15000) //间隔显示,多次进入
						{
							xianshiping_sendorder2("zhuangtai", "净水水满"); //
							tiaoshi("净水水满");
							shch_shuiman_xianshi = millis();
						}
					}

					if (digitalRead(jingshui_gaoyakg) == 0) //需要制水
					{

						/*------------------净水过程1：------------------------------------*/
						if (digitalRead(gaoyabeng) == 0) //高压泵没有运转，此设置只进入一次，开始制水后不再进入
						{
							zhishui_starttime = millis(); //高压泵工作开始时间

							xianshiping_sendorder2("zhuangtai", "开始净水制水"); //
							tiaoshi("开始净水制水");

							jigshui_danci = 0;//制水单次工作时间 分钟

							if ((zhishui_starttime - zhishui_stoptime < 180000) && (zhishui_stoptime != 0)) //不超过3分钟并且不是第一次
							{
								ximo_yucun = false; //不需要洗膜水预存
							}
							else
							{
								ximo_yucun = true; //需要洗膜水预存

								jingshui_dcf_starttime = millis(); //净水电磁阀得电开始时间
							}									  

							
							delay(1000);
							digitalWrite(gaoyabeng, HIGH); /*??????*/
							delay(1000);
							
						}
						/*------------------净水过程2：------------------------------------*/

						if (digitalRead(gaoyabeng) == 1) /*泵运转了，制水中，分为储存洗膜水和不储存2种情况*/
						{

							if (ximo_yucun == true) //需要储存洗膜水
							{
								digitalWrite(jingshui, HIGH);
								//if (xianshi_jiange.hasPassed(6000, true))
								if (millis() - zhishui_xianshi_jiange > 5000)

								{
									//ld.print("jshudcf0", 0);
									xianshiping_sendorder2("zhuangtai", "净水电磁阀关闭，等待洗膜压力桶水满");
									tiaoshi("净水电磁阀关闭，等待洗膜压力桶水满");
									delay(1000);
									xianshiping_sendorder2("zhuangtai", "储存洗膜水时水流脉冲最小值：" + (String)zhishui_maichong_biaozhun);

									xianshiping_sendorder2("shuju", "制水时脉冲数：" + (String)count);
									tiaoshi("制水时脉冲数：" + (String)count);
									zhishui_xianshi_jiange = millis();
								}

								if (digitalRead(jingshui_gaoyakg) == 0) //生产高压开关没有断开
								{

									if ((millis() - jingshui_dcf_starttime) > shuimandengdaishijian_set * 60000) //设为5分钟
									{
										//7????????锟斤拷????????????

										xianshiping_sendorder2("zhuangtai", "净水输出关闭" + (String)shuimandengdaishijian_set + "分钟后任然不能水满，故障停机"); //?????????7????????????????????????
										tiaoshi("净水输出关闭" + (String)shuimandengdaishijian_set + "分钟后任然不能水满，故障停机");

										ximo_buneng_shuiman = true; //报警为真
										baojing_begintime = millis();

										return;
									}
								}

								if (digitalRead(jingshui_gaoyakg) == 1) //生产高压开关断开，只进入一次
								{
									digitalWrite(jingshui, LOW); //净水电磁阀失电打开

									ximo_yucun = false;
									xianshiping_sendorder2("shuju", "洗膜压力桶" + String((millis() - jingshui_dcf_starttime) / 60000) + "分钟水满");
									tiaoshi("洗膜压力桶" + String((millis() - jingshui_dcf_starttime) / 60000) + "分钟水满");
									
								}
							}
							else //不需要储存洗膜水
							{
								//显示屏显示
								if (millis() - zhishui_xianshi_jiange > 5000)
								{
									switch (xianshi)
									{
									case 0:
										//ld.print("yiny run", 0);

										xianshiping_sendorder2("zhuangtai", "净水制水中");

										xianshiping_sendorder2("shuju", "净水制水已用时：" + (String)jigshui_danci + "分钟");
										tiaoshi((String)(jigshui_danci) + "分钟");

										xianshiping_sendorder2("zhuangtai", "制水单次设定：" + (String)zhishuishijian_set + "分钟");

										tiaoshi("制水脉冲标准：" + (String)zhishui_maichong_biaozhun);
										break;
									case 1:
										//ld.print("puls" + (String)count, 0);
										xianshiping_sendorder2("zhuangtai", "制水时水流脉冲最小值：" + (String)zhishui_maichong_biaozhun);
										
										xianshiping_sendorder2("shuju", "制水时脉冲数：" + (String)count);
										tiaoshi("制水时脉冲数：" + (String)count);
										break;
									case 2:
										//ld.print("time" + String((int)(ch_beng.elapsed() / 60000), 4), 0);
										xianshiping_sendorder2("zhuangtai", "制水总分钟：" + (String)zhishuizongshijian);
                                        tds_send_parse();//tds值检测
										break;
									}
									xianshi++;
									if (xianshi >= 3)
									{
										xianshi = 0;
									}
									zhishui_xianshi_jiange = millis();
								}

								if (jigshui_danci > zhishuishijian_set) //进入一次,制水时间超过设定
								{

									xianshiping_sendorder2("zhuangtai", "制水时间超过单次设定时间");
									tiaoshi("制水时间超过单次设定时间");
									digitalWrite(jingshui, HIGH);											   //净水电磁阀得电关闭
									xianshiping_sendorder2("shuju", "制水超时次数：" + (String)chaoshi_cishu); //??????????
									chaoshi_cishu++;
									xuyao_ximo = true; //在洗膜程序里关闭有关

									chaolv_chxi = true; //需要冲洗超滤
								}
							}
							//废水测量，净水储存与制水公用
							{

								detect(1000); //???????????????????

								if (count < zhishui_maichong_biaozhun)
								{
									feishuiguoshao_times++;

									xianshiping_sendorder2("zhuangtai", "废水过少:" + (String)feishuiguoshao_times + "次");
								}
								else
								{
									//xianshiping_sendorder2("zhuangtai", "废水流量正常");

									feishuiguoshao_times = 0;
								}
								if (feishuiguoshao_times >= 30)
								{
									
									//xianshiping_sendorder2("zhuangtai", "废水过少布尔值为真");
									//xianshiping_sendorder2(0,"zhuangtai", "????");

									feishuiguoshao = true;
									baojing_begintime = millis();
									return;
								}
							}

							/*------------------净水过程4：公用计算-制水总时间 单次 净水tds值-----------*/
							//泵启动开始计算时间，开始时间由泵启动函数赋值
							{

								if (millis() - zhishui_starttime > 60000) //1分钟
								{
									zhishuizongshijian++; //分钟

									xianshiping_sendorder2("zhuangtai", "制水总时长：" + (String)zhishuizongshijian + "分钟");

									jigshui_danci++;

									xie_jici++;
									if (xie_jici >= 10) //10分钟写入一次
									{					/*-------tds检测------------*/
														//tds_send_parse();//10分钟检测一次

										EEPROM.updateLong(zhishui_shjian_add, zhishuizongshijian);
										/* 	if (EEPROM.commit())
											{
												tiaoshi("成功写入");
											}
											else
											{
												tiaoshi("写入失败");

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
			else //净水超压
			{	
				if (millis() - jingshui_chaoya_xianshi_jiange > 7000)
				{
					jingshui_chaoya_xianshi_jiange = millis();
					xianshiping_sendorder2("zhuangtai", "净水超压停机，报售后");
					tiaoshi("净水超压，报售后");
					
					closeall();
				
				}
			}
		}
		else
		{
			
			//缺水状态下如果没有延时会大量发送数据造成显示屏回传错误报警,间隔给显示屏数据
			if (millis() - queshui_xianshi_jiange > 7000)
			{
				queshui_xianshi_jiange = millis();
				//ld.print("queshui1", 0);
				xianshiping_sendorder2("zhuangtai", "缺水停机");			

				tiaoshi("缺水提示一次");				
				closeall();
				
			}
			
		}

		
		
	}
}
