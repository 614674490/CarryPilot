/* Copyright (c)  2018-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ������ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������δ��������ɣ����ý�Դ�����ṩ�����ˣ����ý�Դ����ŵ����Ϲ�����������أ� 
*               �������Դ�����Ĳ�����緢��������Ϊ�������ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------/
*               ������Ϣ���ܶ���ֹ��ǰ�����������˳���������
*               ��Դ���ף���ѧ����ϧ��ף������Ϯ�����׳ɹ�������
*               ѧϰ�����ߣ��������Ƽ���DJI��ZEROTECH��XAG��AEE��GDU��AUTEL��EWATT��HIGH GREAT�ȹ�˾��ҵ
*               ��ְ�����뷢�ͣ�15671678205@163.com���豸ע��ְ����λ����λ��������
*               �����ƴ���Դ�ɿ�QQȺ��540707961
*               CSDN���ͣ�http://blog.csdn.net/u011992534
*               �ſ�ID��NamelessCotrun����С��
*               Bվ��ѧ��Ƶ��https://space.bilibili.com/67803559/#/video
*               �ͻ�ʹ���ĵá��Ľ������������http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               �Ա����̣�https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               �ٶ�����:�����ƴ���Դ�ɿ�
*               ��˾����:www.nameless.tech
*               �޸�����:2019/4/12
*               �汾����Ӯ�ߡ���CarryPilot_V1.0
*               ��Ȩ���У�����ؾ���
*               Copyright(C) 2017-2025 �人�������¿Ƽ����޹�˾ 
*               All rights reserved
*               ��Ҫ��ʾ��
*               �����Ա�����ת�ֵķɿء��������ѡ�����ѧ�ܵĶ����Խ��ۺ�Ⱥѧϰ������
*               ����ֱ�����������������������ϣ��������´�����������Ȩ�����˲��ý�
*               ���ϴ��봫���Ϲ��������أ�������ı��ΪĿ���������ϴ��룬�����д˲�
*               ���ߣ���˾����ǰ��֪����1���ڼ�ʱ�����������ѧУ����λ����������
*               ������ַ��Ϣ�ᱻ�����ڹ�˾�������ٷ�΢�Ź���ƽ̨���ٷ��������͡�֪��
*               ר���Լ��Ա�������ҳ���Թ�ʾ���棬����������Ϊ�����Ϊ�����۵㣬Ӱ��
*               ��ѧ���ҹ���������������ܿ�ͺ������˻����������������ء�
*               �����Ϊ����˾����ش���ʧ�ߣ����Է���;���������л���ĺ�����лл������
----------------------------------------------------------------------------------------------------------------------*/
#include "Headfile.h"
#include "WP_Ctrl.h"
#include "control_config.h"

/*****************ң�����г�����**********************/
//Ĭ�� �رն��� �ر�GPS ��̬����ģʽ �ر��Զ���SDK �رչ���
uint16 Motor_PWM_1,Motor_PWM_2,Motor_PWM_3,Motor_PWM_4,Motor_PWM_5,Motor_PWM_6;//����������PWM
uint16 Last_Motor_PWM_1,Last_Motor_PWM_2,Last_Motor_PWM_3,Last_Motor_PWM_4,Last_Motor_PWM_5,Last_Motor_PWM_6;//�ϴ�����������PWM
uint8_t Controler_High_Mode=1,Last_Controler_High_Mode=1;             
uint8_t Controler_Horizontal_Mode=1,Last_Controler_Horizontal_Mode=1;  //Ĭ�Ϲر�GPS ��̬����ģʽ
uint8_t Controler_Land_Mode=0,Last_Controler_Land_Mode=0;        //Ĭ�ϷǷ���ģʽ
uint8_t Reserve_Mode=1;                      //Ĭ�Ϲرչ���
uint8_t Reserve_Mode_Fast_Exchange_Flag=0,Reserve_Mode_Fast_Exchange_Cnt=0;
uint16_t Reserve_Mode_Cnt=0;
uint8_t Control_Mode_Change=0;
uint16_t High_Hold_Throttle=0;
uint8_t  Pos_Hold_SetFlag=0;
uint8_t SDK_Ctrl_Mode=0;
uint8_t SDK_Take_Over_Ctrl = 2;  // 1��SDK���ƽӹ���Դ��OPENMV����������   2��SDK���ƽӹ���Դ����Ϊ����ָ��  Ĭ��Ϊ��Ϊָ��
uint8_t Start_Task_Flag=0,Start_Fly=0;
uint8_t key_press_flag=0;
/***************************************************
������: void Controler_Mode_Select(void)
˵��:	������ģʽѡ����
���:	��
����:	��
��ע:	�ж�������ȳ�������
****************************************************/
void Controler_Mode_Select()
{
	//�����л������
  Last_Controler_High_Mode=Controler_High_Mode;//�ϴθ߶ȿ���ģʽ
  Last_Controler_Horizontal_Mode=Controler_Horizontal_Mode;//�ϴ�λ�ÿ���ģʽ
  Last_Controler_Land_Mode=Controler_Land_Mode;//�ϴη���ģʽ
	//ͨ��5ʧЧ    ͨ��6����һ��ִ������ ͨ��7���ڿ��Ʒ����뽵��  ͨ��8ʧЧ
  if(PPM_Databuf[4]>=(RC_Calibration[4].max-RC_Calibration[4].deadband))      
  {
		Controler_Land_Mode=2;//��ͣ
		Task_Reset();
		Bling_Set(&Light_2,100,500,0.5,0,GPIO_PORTF_BASE,GPIO_PIN_2,1); 
	}
	if(((PPM_Databuf[5]>=(RC_Calibration[5].max-RC_Calibration[5].deadband)&&key_press_flag==0)||Sun_Sky==1)&&Controler_Land_Mode!=2)  //һ����� ������ ���Ƿ���
	{
		Start_Task_Flag=1;
		Controler_High_Mode=2;       //������
		Reserve_Mode=2;              //������
		Controler_Horizontal_Mode=1; //��GPS
	  Controler_Land_Mode=0;       //��������ģʽ ���Ƿ���ģʽ
		Start_Fly=1;
		key_press_flag=1;
		Sun_Sky=0;  //��ֹ�ظ�����
	}
	else if(PPM_Databuf[5]<=(RC_Calibration[5].min+RC_Calibration[5].deadband)&&Controler_Land_Mode!=2&&realse_lock_status!=4)     //�ض��� ��ִ�������в��� ֱ�Ӽ�ͣ
	{
		Bling_Set(&Light_1,100,800,0.5,0,GPIO_PORTF_BASE,GPIO_PIN_3,1);  //��
		if(Start_Task_Flag==1)  //��֮ͣ������������ܼ����Զ�ִ������
		{
			Start_Task_Flag=2;      //�˴���ʾ����ǿ��ֹͣ  0������ִ����� 1����������ִ�� 2������ǿ��ֹͣ
			Controler_Land_Mode=0;  //�Ƿ���
			Controler_High_Mode=1;
			Reserve_Mode=1;              //�ع���
			SDK_Ctrl_Mode=0;
			key_press_flag=1;       //��ֹ�ٴν���SDKģʽ
			Task_Reset();
		}
		if(Start_Task_Flag!=2)
		{
			key_press_flag=0;
		}
	  Controler_High_Mode=1;    //�л���̬����
	}
  
//  if(PPM_Databuf[6]>=(RC_Calibration[6].max-RC_Calibration[6].deadband))            {Controler_Land_Mode=1;}//����ģʽ
//  else if(PPM_Databuf[6]<=(RC_Calibration[6].middle+RC_Calibration[6].deadband))   {Controler_Land_Mode=0;}//�Ƿ���ģʽ
//  
//  if(PPM_Databuf[6]>=(RC_Calibration[6].middle-RC_Calibration[6].deadband)
//     &&PPM_Databuf[6]<=(RC_Calibration[6].middle+RC_Calibration[6].deadband))//ң�������ο��ش�����λ     
//  {
//    SDK_Ctrl_Mode=1;
//  }
//  else
//  {
//    SDK_Ctrl_Mode=0;
//		NCQ_SDK_Reset();
//		Rectangle_Reset();
//  }  
  
//  if(PPM_Databuf[7]>=(RC_Calibration[7].max-RC_Calibration[7].deadband))      {Reserve_Mode=2;} //��ͨ���ڸ�λ  �����������
//  else if(PPM_Databuf[7]<=(RC_Calibration[7].min+RC_Calibration[7].deadband)) 
//  {
//    Reserve_Mode=1;
//    OpticalFlow_SINS_Reset();
//    OpticalFlow_Ctrl_Reset();
//  }  //��ͨ���ڵ�λ  �������㲻����
  if(Start_Fly==1)
	{
		Start_Fly=0;
		Reserve_Mode_Fast_Exchange_Flag=1;	
		if(Hung_Thing)
			Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW]+Hung_Thing_Target;  //����ܶԵصĸ߶�
		else
			Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW]+Auto_Launch_Target; 
		Unwanted_Lock_Flag=0;
	}
  if(Reserve_Mode_Fast_Exchange_Flag==1)//�������	
  {
		if(!Hung_Thing)
		{
			Total_Controller.High_Acce_Control.Scale_Kp=1.0f;
			Total_Controller.High_Acce_Control.Scale_Ki=1.0f; 
			Total_Controller.High_Speed_Control.Scale_Kp=1.0;
			Total_Controller.High_Speed_Control.Scale_Ki=1.0f;
			Total_Controller.High_Position_Control.Scale_Kp=1.0;
			Total_Controller.High_Position_Control.Scale_Ki=1.0f; 
		}
    else //�����������
		{//ԭ���ٶȻ� 0.3 1.0 1.0f

			Total_Controller.Yaw_Gyro_Control.Scale_Kp=1.3f;
			Total_Controller.Yaw_Gyro_Control.Scale_Ki=1.0f;
			Total_Controller.Yaw_Gyro_Control.Scale_Kd=1.8f;
			
			Total_Controller.Pitch_Gyro_Control.Scale_Kp=1.3f;
			Total_Controller.Pitch_Gyro_Control.Scale_Ki=1.0f;
			Total_Controller.Pitch_Gyro_Control.Scale_Kd=1.8f;

			Total_Controller.Roll_Gyro_Control.Scale_Kp=1.3f;
			Total_Controller.Roll_Gyro_Control.Scale_Ki=1.0f;
			Total_Controller.Roll_Gyro_Control.Scale_Kd=1.8f;
		}
    if(Total_Controller.High_Position_Control.Expect<=NamelessQuad.Position[_YAW])//�����߶ȴ��������߶ȣ����ָ����� ������ ��ʼѲ��
    {
      Reserve_Mode_Fast_Exchange_Flag=0;     //�رտ������ 
			SDK_Take_Over_Ctrl=2;                  //ת�����Զ���SDKģʽ
			SDK_Ctrl_Mode=1;                       //�����Զ���SDKģʽ ����Ѳ��
			yellow_barcode_pos=OpticalFlow_SINS.Position[_ROLL];  //��¼Ѳ��ǰ�Ĺ���λ��
    }	
  }
  else 
  { 
    Total_Controller.High_Acce_Control.Scale_Kp=1.0f;
    Total_Controller.High_Acce_Control.Scale_Ki=1.0f; 
    Total_Controller.High_Speed_Control.Scale_Kp=1.0;
    Total_Controller.High_Speed_Control.Scale_Ki=1.0f; 
    Total_Controller.High_Position_Control.Scale_Kp=1.0;
    Total_Controller.High_Position_Control.Scale_Ki=1.0f; 
  }
  
  if(Unwanted_Lock_Flag==1)//����ģʽ���������κβ���
  {
    Thr_Push_Over_State=Thr_Push_Over_Deadband();
    if(Thr_Push_Over_State==2)//ֻҪ�����ƹ�����λ���������������Զ���������
    {
      Unwanted_Lock_Flag=0;
    }
    else
    {
      Take_Off_Reset();//�����
      //Throttle_Control_Reset();//�����
    }
  }
  
  if(Controler_Land_Mode!=Last_Controler_Land_Mode)
  {
    if(Controler_Land_Mode==0)  
      land_reset();//����ģʽ�л�����ģʽ
    Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW];//�����ز���˲��Ĺߵ��߶�����Ϊ�����߶�
  }
  
  if(Controler_High_Mode!=Last_Controler_High_Mode)
  {
    if(Controler_High_Mode==2)  {Control_Mode_Change=1;}//�����ж��ߣ����û�׼����ֵ����ͣ�߶�
    if(Controler_High_Mode==1)  {Control_Mode_Change=1;}//����������
  }
	if(Control_Mode_Change==1&&Start_Task_Flag!=1)//���ڶ���ģʽ�л�������Ϊ���Զ�ģʽ
  {
    if(Controler_High_Mode==High_Hold_Mode)//����Ϊ����ģʽ���������ж���
    {
      High_Hold_Throttle=Throttle_Control;//���浱ǰ����ֵ��ֻ��һ��
      /*******************����ǰ�ߵ���ֱλ�ù�����ΪĿ��߶�***************************/
    }
    else//����Ϊ����ģʽ��������������
    {
      //Throttle_Control_Reset();
    }
    Control_Mode_Change=0;//��ģʽ�л�λ��0,���ҽ�����һ��
  }
}



uint16 Value_Limit(uint16 Min,uint16 Max,uint16 Data)
{
  if(Data>=Max) Data=Max;
  else if(Data<=Min) Data=Min;
  return Data;
}



void Angle_Control()//�ǶȻ���
{
  static uint16 Yaw_Cnt=0;
  //�Ƕȷ���
  Total_Controller.Pitch_Angle_Control.FeedBack=(Pitch-Pitch_Offset);
  PID_Control(&Total_Controller.Pitch_Angle_Control);
  Total_Controller.Roll_Angle_Control.FeedBack =(Roll-Roll_Offset);
  PID_Control(&Total_Controller.Roll_Angle_Control);
  
  if(Yaw_Control==0)//ƫ����������λ
  {
    if(Yaw_Cnt<=500)//��ͷģʽ���ɻ��ϵ��һ��ʱ������ƫ���ǣ������ơ��������ں���Ҫһ��ʱ�䣬����ȡ500
    {
      Yaw_Cnt++;
    }
    if(Total_Controller.Yaw_Angle_Control.Expect==0//����ʱ���Ƕ�����ֵ
       ||Yaw_Cnt<=500
         ||Landon_Earth_Flag==1)//�������㴥����������λƫ��������
    {
      Total_Controller.Yaw_Angle_Control.Expect=Yaw;
    }
    Total_Controller.Yaw_Angle_Control.FeedBack=Yaw;//ƫ���Ƿ���
    PID_Control_Yaw(&Total_Controller.Yaw_Angle_Control);//ƫ���Ƕȿ���
    Total_Controller.Yaw_Gyro_Control.Expect=Total_Controller.Yaw_Angle_Control.Control_OutPut;//ƫ�����ٶȻ���������Դ��ƫ���Ƕȿ��������
    
    if(SDK_Line.line_ctrl_enable==1&&SDK_Ctrl_Mode==1)//SDKģʽ�µ�ѭ��ģʽ��ƫ�����ٶ�������Դ��SDK����
    {
      Total_Controller.Yaw_Gyro_Control.Expect=3*SDK_Target_Yaw_Gyro;
      Total_Controller.Yaw_Angle_Control.Expect=0;//ƫ����������0,�����нǶȿ���
      //SDK_Line.flag=0;
    }
  }
  else//����ƫ������˺�ֻ�����ڻ����ٶȿ���
  {
    Total_Controller.Yaw_Angle_Control.Expect=0;//ƫ����������0,�����нǶȿ���
    Total_Controller.Yaw_Gyro_Control.Expect=Yaw_Control;//ƫ�����ٶȻ�������ֱ����Դ��ң���������
  }
  //Total_Controller.Yaw_Gyro_Control.Expect=Yaw_Control;//ƫ�����ٶȻ�������ֱ����Դ��ң���������
}



uint16_t Yaw_Control_Fault_Cnt=0;
float Last_Yaw_Gyro_Control_Expect=0,Yaw_Gyro_Control_Expect_Delta=0;
float Last_Pitch_Gyro_Control_Expect=0,Pitch_Gyro_Control_Expect_Delta=0;
float Last_Roll_Gyro_Control_Expect=0,Roll_Gyro_Control_Expect_Delta=0;
float Pitch_Roll_Feedforward_Kp=0.0f,Pitch_Roll_Feedforward_Kd=0.0f;// 1.45  0.25         0.85     //0.45
float Yaw_Feedforward_Kp=0.0f,Yaw_Feedforward_Kd=0.05f;//ƫ����ǰ������ 0.15   1.0  0.3         //0.05
void Gyro_Control()//���ٶȻ�
{
  if(GYRO_CONTROL_MODE==PID_MODE)//���������������̬�ڻ����ٶȿ���������PID������
  {
    /***************�ڻ����ٶ�����****************/
    Total_Controller.Pitch_Gyro_Control.Expect=Total_Controller.Pitch_Angle_Control.Control_OutPut;
    Total_Controller.Roll_Gyro_Control.Expect=Total_Controller.Roll_Angle_Control.Control_OutPut;
    
    /***************�ڻ����ٶȷ���****************/
    Total_Controller.Pitch_Gyro_Control.FeedBack=Pitch_Gyro;
    Total_Controller.Roll_Gyro_Control.FeedBack=Roll_Gyro;
    
    /***************�ڻ����ٶȿ���****************/
    //PID_Control_Div_LPF(&Total_Controller.Pitch_Gyro_Control);
    //PID_Control_Div_LPF(&Total_Controller.Roll_Gyro_Control);    
    /***************�ڻ����ٶȿ��ƣ�΢�ֲ�����̬����****************/
    PID_Control_Div_LPF_For_Gyro(&Total_Controller.Pitch_Gyro_Control);
    PID_Control_Div_LPF_For_Gyro(&Total_Controller.Roll_Gyro_Control);
    
    Pitch_Gyro_Control_Expect_Delta=1000*(Total_Controller.Pitch_Gyro_Control.Expect-Last_Pitch_Gyro_Control_Expect
                                          /Total_Controller.Pitch_Gyro_Control.PID_Controller_Dt.Time_Delta);
    Roll_Gyro_Control_Expect_Delta=1000*(Total_Controller.Roll_Gyro_Control.Expect-Last_Roll_Gyro_Control_Expect
                                         /Total_Controller.Roll_Gyro_Control.PID_Controller_Dt.Time_Delta);
    
    Last_Pitch_Gyro_Control_Expect=Total_Controller.Pitch_Gyro_Control.Expect;
    Last_Roll_Gyro_Control_Expect=Total_Controller.Roll_Gyro_Control.Expect;
    
    Total_Controller.Pitch_Gyro_Control.Control_OutPut+=Pitch_Roll_Feedforward_Kd*Pitch_Gyro_Control_Expect_Delta
      +Pitch_Roll_Feedforward_Kp*Total_Controller.Pitch_Gyro_Control.Expect;
    Total_Controller.Pitch_Gyro_Control.Control_OutPut=constrain_float(Total_Controller.Pitch_Gyro_Control.Control_OutPut,
                                                                       -Total_Controller.Pitch_Gyro_Control.Control_OutPut_Limit,
                                                                       Total_Controller.Pitch_Gyro_Control.Control_OutPut_Limit);
    
    Total_Controller.Roll_Gyro_Control.Control_OutPut+=Pitch_Roll_Feedforward_Kd*Roll_Gyro_Control_Expect_Delta
      +Pitch_Roll_Feedforward_Kp*Total_Controller.Roll_Gyro_Control.Expect;
    Total_Controller.Roll_Gyro_Control.Control_OutPut=constrain_float(Total_Controller.Roll_Gyro_Control.Control_OutPut,
                                                                      -Total_Controller.Roll_Gyro_Control.Control_OutPut_Limit,
                                                                      Total_Controller.Roll_Gyro_Control.Control_OutPut_Limit);
    
  }
  else if(GYRO_CONTROL_MODE==ADRC_MODE)//���������������̬�ڻ����ٶȿ���������ADRC�Կ��ſ�����
  {
    
  }
  else//�����á�����ֻѡ��һ��ģʽ
  {
    /***************�ڻ����ٶ�����****************/
    Total_Controller.Pitch_Gyro_Control.Expect=Total_Controller.Pitch_Angle_Control.Control_OutPut;
    Total_Controller.Roll_Gyro_Control.Expect=Total_Controller.Roll_Angle_Control.Control_OutPut;
    /***************�ڻ����ٶȷ���****************/
    Total_Controller.Pitch_Gyro_Control.FeedBack=Pitch_Gyro;
    Total_Controller.Roll_Gyro_Control.FeedBack=Roll_Gyro;
    
    /***************�ڻ����ٶȿ���****************/
    PID_Control_Div_LPF(&Total_Controller.Pitch_Gyro_Control);
    PID_Control_Div_LPF(&Total_Controller.Roll_Gyro_Control);
  }
  
  //ƫ����ǰ������
  //Total_Controller.Yaw_Gyro_Control.FeedBack=Yaw_Gyro;
  Total_Controller.Yaw_Gyro_Control.FeedBack=Yaw_Gyro_Earth_Frame;//Yaw_Gyro;
  
  PID_Control_Div_LPF(&Total_Controller.Yaw_Gyro_Control);
  Yaw_Gyro_Control_Expect_Delta=1000*(Total_Controller.Yaw_Gyro_Control.Expect-Last_Yaw_Gyro_Control_Expect)
    /Total_Controller.Yaw_Gyro_Control.PID_Controller_Dt.Time_Delta;
  //**************************ƫ����ǰ������**********************************
  Total_Controller.Yaw_Gyro_Control.Control_OutPut+=Yaw_Feedforward_Kp*Total_Controller.Yaw_Gyro_Control.Expect
    +Yaw_Feedforward_Kd*Yaw_Gyro_Control_Expect_Delta;//ƫ����ǰ������
  Total_Controller.Yaw_Gyro_Control.Control_OutPut=constrain_float(Total_Controller.Yaw_Gyro_Control.Control_OutPut,
                                                                   -Total_Controller.Yaw_Gyro_Control.Control_OutPut_Limit,
                                                                   Total_Controller.Yaw_Gyro_Control.Control_OutPut_Limit);
  Last_Yaw_Gyro_Control_Expect=Total_Controller.Yaw_Gyro_Control.Expect;
  /*******ƫ�������쳣����жϣ���ƫ���������ܴ�ʱ��ƫ�����ٶȺ�С�����ʱΪǿ�������š����ŵص�******************************/
  if(ABS(Total_Controller.Yaw_Gyro_Control.Control_OutPut)>Total_Controller.Yaw_Gyro_Control.Control_OutPut_Limit/2//ƫ�����������Խϴ�
     &&ABS(Yaw_Gyro)<=30.0f)//ƫ�����ٶ���Ժ�С
  {
    Yaw_Control_Fault_Cnt++;
    if(Yaw_Control_Fault_Cnt>=500) Yaw_Control_Fault_Cnt=500;
  }
  else Yaw_Control_Fault_Cnt/=2;//�����㣬����������0
  
  if(Yaw_Control_Fault_Cnt>=400)//����5ms*400=2S,���⴦��
  {
    PID_Integrate_Reset(&Total_Controller.Yaw_Gyro_Control);//���ƫ�����ٶȿ��ƵĻ���
    PID_Integrate_Reset(&Total_Controller.Yaw_Angle_Control);//���ƫ���ǿ��ƵĻ���
    Total_Controller.Yaw_Angle_Control.Expect=Yaw;//����ǰƫ���ǣ���Ϊ����ƫ����
    Yaw_Control_Fault_Cnt=0;
  }
  /*******ƫ�������쳣�������******************************/
}

uint16 Throttle=0,Last_Throttle=0;
void Main_Leading_Control(void)
{
  /*********************����ң�����л���λ���ɿؽ��벻ͬģʽ****************************/
  if(Controler_Land_Mode==0)//�Ƿ�����½ģʽ
  {
    if(Controler_High_Mode==1//��̬���ȶ�ģʽ
       &&Controler_Horizontal_Mode==1)//GPS���㵵λδ����   Ĭ��ң��������
    {
      Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
      Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
      
      if(Throttle_Control<=1000)   Throttle=1000;
      else Throttle=Throttle_Control;//����ֱ����Դ��ң�������Ÿ���
      Last_Throttle=Throttle;
    }
    else if(Controler_High_Mode==2//����ģʽ
            &&Controler_Horizontal_Mode==1)//GPS���㵵λδ����
    {
      /**************************����ģʽ��ˮƽ��̬��������Դ��ң����******************************************/
      
#if  (Optical_Enable==0)
      Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
      Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
			ncq_control_althold();//�߶ȿ���
#else   //����������ͣ
      if(Reserve_Mode==2&&OpticalFlow_Is_Work==1
				&&(Sensor_Flag.Hcsr04_Health==1||tfdata.health==1))//��������Ч�Ҵ��ڹ�������ʱ��������������ģʽ
      {  
        if(SDK_Take_Over_Ctrl==1)        //������������߶�ά�������˺�����
        {
          OpticalFlow_Control(0);//��ͨ����ģʽ������������OPENMV�����SDKģʽ
          ncq_control_althold();//�߶ȿ���
        }
        else if(SDK_Take_Over_Ctrl==2)  //�Ƚ���˴����  ������ͨѲ��
        {
					if(SDK_Ctrl_Mode==1)    
					{
						rectangle_duty(365,55,0);//�û�����ָ����SDK������ģʽ 
					}
					else  
					{
						OpticalFlow_Control_Pure(0);//��ͨ����ģʽ
						ncq_control_althold();//�߶ȿ���
					}
        }
      }
      else   //������Чʱ ��Ȼ��ң��������
      {
        Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
        Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
				ncq_control_althold();//�߶ȿ���
      }
#endif
      
    }
    else//����
    {
      Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
      Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
      if(Throttle_Control<=1000)   Throttle=1000;
      else Throttle=Throttle_Control;//����ֱ����Դ��ң�������Ÿ���
      Last_Throttle=Throttle;
    }
    land_state_check();
  }
  else if(Controler_Land_Mode==1)//������½ģʽ
  {
    land_run();
  }
	else if(Controler_Land_Mode==2) //��ͣģʽ
	{
		Throttle=Thr_Min;
		Auto_Relock_Flag=1;
	}
}
/************��̬�����������Ƕ�+���ٶ�****************/
void Attitude_Control(void)
{
  Angle_Control();//�Ƕȿ���
  Gyro_Control();//���ٶȿ���
}


float Active_Para1,Active_Para2;
/***************************************************
������: void Total_Control(void)
˵��:	�ܿ��������У������������
1������ң�������롢��ǰ״̬����������ģʽ������+�����ֶ�������+���ȡ�����+���㣨���٣��ȣ�
2�������ϲ������������̬�������߶ȿ��Ƶ�
3�����ȣ���̬������
���:	��
����:	��
��ע:	�ϵ��ʼ��������һ��
****************************************************/
void Total_Control(void)
{
  /*************����������******************/
  Main_Leading_Control();		
  /*************��̬��������*****************/
  Attitude_Control();
}


void CarryPilot_Control(void)
{
  static uint8_t ctrl_cnt=0;
	static uint16_t lock_cnt=0;
  ctrl_cnt++;  
	if(realse_lock_status==1)
	{
		lock_cnt++;
		if(lock_cnt>=1000)  //���°���5s��ʼ����
		{
			lock_cnt=0;
			realse_lock_status=2;
		}
	}
	else if(realse_lock_status==3)  //������� ͨ����ʱ��һ������
	{
		lock_cnt++;
		//���� ���ٵ�����ʱʱ�� ��ֹ�߶��ںϳ��ֲ���
		if(lock_cnt>=100)  //����500ms��ʼִ������
		{
			lock_cnt=0;
			realse_lock_status=4;   //����״̬����
			Sun_Sky=1;         //����һ������
		}
	}
  /*************������ģʽѡ��******************/
  if(ctrl_cnt>=4)//�Ĵ˼�����ֵ�����Ե�����������
  {  
    Controler_Mode_Select();
    ctrl_cnt=0;
  }
  Total_Control();//�ܿ�������ˮƽλ��+ˮƽ�ٶ�+��̬���Ƕ�+���ٶȣ����������߶�λ��+�߶��ٶ�+�߶ȼ��ٶȿ�����	
  Control_Output();//�����������
}
uint16_t Throttle_Output=0;
void Throttle_Angle_Compensate()//������ǲ���
{
  float CosPitch_CosRoll=ABS(Cos_Pitch*Cos_Roll);
  float Throttle_Makeup=0;
  float Temp=0;
  if(CosPitch_CosRoll>=0.999999f)  CosPitch_CosRoll=0.999999f;
  if(CosPitch_CosRoll<=0.000001f)  CosPitch_CosRoll=0.000001f;
  if(CosPitch_CosRoll<=0.50f)  CosPitch_CosRoll=0.50f;//Pitch,RollԼ����30��
  if(Throttle>=Thr_Start)//������ת������
  {
    Temp=(uint16_t)(MAX(ABS(100*Pitch),ABS(100*Roll)));
    Temp=constrain_float(9000-Temp,0,3000)/(3000*CosPitch_CosRoll);
    Throttle_Makeup=(Throttle-Thr_Start)*Temp;//������ǲ���
    Throttle_Output=(uint16_t)(Thr_Start+Throttle_Makeup);
    Throttle_Output=(uint16_t)(constrain_float(Throttle_Output,Thr_Start,2000));
  }
  else Throttle_Output=Throttle;
}


/**************************************************************
***************************************************************
X�Ͱ�װ��ʽ������������̬�ǹ�ϵ
                   -
                 Pitch
					3#             1#
					   *          *
-   Roll          *         Roll   +
						 *          *
					2#             4#
				         Pitch
								   +
���ٶȴ���������������X��Y��Zͬ�ᣬ������ԭ�㿴����ʱ����ת�Ƕ�Ϊ+
Y Aixs
*
*
*
*
*
*
* * * * * * * *   X Axis
(0)
*******************************************************************
******************************************************************/
uint16_t Idel_Cnt=0;
#define Idel_Transition_Gap 4//���ٵ������ʱ�� 4*5=20ms
#define Idel_Transition_Period (Thr_Idle-Thr_Min)//����������������  20ms*100=1s
uint16_t Thr_Idle_Transition_Cnt=0;
void Control_Output()
{
  Throttle_Angle_Compensate();//������ǲ���
  landon_earth_check();//��½�����Լ�
  if(Controler_State==Unlock_Controler)//����
  {
    if(Landon_Earth_Flag==1)//��⵽��½����
    {
      if(Last_Motor_PWM_1<=Thr_Min
         &&Last_Motor_PWM_2<=Thr_Min
           &&Last_Motor_PWM_3<=Thr_Min
             &&Last_Motor_PWM_4<=Thr_Min
               //&&Last_Motor_PWM_5<=Thr_Min
               //&&Last_Motor_PWM_6<=Thr_Min
               )//ֻ���������ٽ���ʱ�Ż�����
      {
        //����ϴ��������ֵΪ���λ�����뵡��ʱ�����Ź��ɹ���
        Thr_Idle_Transition_Cnt=Idel_Transition_Period;
      }
      else//����ʱ�̽�����½����
      {
        if(Last_Landon_Earth_Flag==0)//�ϴ�Ϊ���״̬������Ϊ��½״̬���������
        {
          Controler_State=Lock_Controler;
          Bling_Set(&Light_1,3000,200,0.5,0,GPIO_PORTF_BASE,GPIO_PIN_1,0);
          Bling_Set(&Light_2,3000,200,0.5,0,GPIO_PORTF_BASE,GPIO_PIN_2,0);
          Bling_Set(&Light_3,3000,200,0.5,0,GPIO_PORTF_BASE,GPIO_PIN_3,0);
        }
      }
      
      Idel_Cnt++;
      if(Idel_Cnt>=Idel_Transition_Gap)
      {
        if(Thr_Idle_Transition_Cnt>=1)
          Thr_Idle_Transition_Cnt--;
        Idel_Cnt=0;
      }
      Motor_PWM_1=Thr_Min+(Idel_Transition_Period-Thr_Idle_Transition_Cnt)*(Thr_Idle-Thr_Min)/Idel_Transition_Period;//���ŵ���
      Motor_PWM_2=Thr_Min+(Idel_Transition_Period-Thr_Idle_Transition_Cnt)*(Thr_Idle-Thr_Min)/Idel_Transition_Period;
      Motor_PWM_3=Thr_Min+(Idel_Transition_Period-Thr_Idle_Transition_Cnt)*(Thr_Idle-Thr_Min)/Idel_Transition_Period;
      Motor_PWM_4=Thr_Min+(Idel_Transition_Period-Thr_Idle_Transition_Cnt)*(Thr_Idle-Thr_Min)/Idel_Transition_Period;
//      Motor_PWM_5=Thr_Min+(Idel_Transition_Period-Thr_Idle_Transition_Cnt)*(Thr_Idle-Thr_Min)/Idel_Transition_Period;
//      Motor_PWM_6=Thr_Min+(Idel_Transition_Period-Thr_Idle_Transition_Cnt)*(Thr_Idle-Thr_Min)/Idel_Transition_Period;
      Take_Off_Reset();//�����
      OpticalFlow_SINS_Reset();
      OpticalFlow_Ctrl_Reset();
    }
    else  //������������½������Ĭ�����
    {
      if(Controler_High_Mode==1)//��̬��λ
      {
        if(Throttle>=Thr_Fly_Start)//�����������
        {
          if(GYRO_CONTROL_MODE==PID_MODE)//ˮƽ��̬�����ٶȶ���������Դ��PID
          {
            Motor_PWM_1=Int_Sort(
                                 Moter1_Thr_Scale*Throttle_Output
                                   +Moter1_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                     +Moter1_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                       +Moter1_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            Motor_PWM_2=Int_Sort(
                                 Moter2_Thr_Scale*Throttle_Output
                                   +Moter2_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                     +Moter2_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                       +Moter2_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            Motor_PWM_3=Int_Sort(
                                 Moter3_Thr_Scale*Throttle_Output
                                   +Moter3_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                     +Moter3_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                       +Moter3_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            Motor_PWM_4=Int_Sort(
                                 Moter4_Thr_Scale*Throttle_Output
                                   +Moter4_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                     +Moter4_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                       +Moter4_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
//            Motor_PWM_5=Int_Sort(
//                                 Moter5_Thr_Scale*Throttle_Output
//                                   +Moter5_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
//                                     +Moter5_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
//                                       +Moter5_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
//            Motor_PWM_6=Int_Sort(
//                                 Moter6_Thr_Scale*Throttle_Output
//                                   +Moter6_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
//                                     +Moter6_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
//                                       +Moter6_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
//            
          }
          else//ˮƽ��̬�����ٶȶ���������Դ��ADRC
          {
            
          }
        }
        else//С���������
        {
          Motor_PWM_1=Int_Sort(Throttle_Output);
          Motor_PWM_2=Int_Sort(Throttle_Output);
          Motor_PWM_3=Int_Sort(Throttle_Output);
          Motor_PWM_4=Int_Sort(Throttle_Output);
//          Motor_PWM_5=Int_Sort(Throttle_Output);
//          Motor_PWM_6=Int_Sort(Throttle_Output);
          Take_Off_Reset();//�����
        }
        Motor_PWM_1=Value_Limit(Thr_Idle,2000,Motor_PWM_1);//������޷�
        Motor_PWM_2=Value_Limit(Thr_Idle,2000,Motor_PWM_2);
        Motor_PWM_3=Value_Limit(Thr_Idle,2000,Motor_PWM_3);
        Motor_PWM_4=Value_Limit(Thr_Idle,2000,Motor_PWM_4);
        Motor_PWM_5=Value_Limit(Thr_Idle,2000,Motor_PWM_5);
        Motor_PWM_6=Value_Limit(Thr_Idle,2000,Motor_PWM_6);
				
				Throttle_Control_Reset();
      }
      else if(Controler_High_Mode==2)//�����йܡ����ߵ�λ
      {
        if(GYRO_CONTROL_MODE==PID_MODE)//ˮƽ��̬�����ٶȶ���������Դ��PID
        {
          Motor_PWM_1=Int_Sort(
                               Moter1_Thr_Scale*Throttle_Output
                                 +Moter1_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                   +Moter1_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                     +Moter1_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          Motor_PWM_2=Int_Sort(
                               Moter2_Thr_Scale*Throttle_Output
                                 +Moter2_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                   +Moter2_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                     +Moter2_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          Motor_PWM_3=Int_Sort(
                               Moter3_Thr_Scale*Throttle_Output
                                 +Moter3_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                   +Moter3_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                     +Moter3_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          Motor_PWM_4=Int_Sort(
                               Moter4_Thr_Scale*Throttle_Output
                                 +Moter4_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                   +Moter4_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                     +Moter4_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
//          Motor_PWM_5=Int_Sort(
//                               Moter5_Thr_Scale*Throttle_Output
//                                 +Moter5_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
//                                   +Moter5_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
//                                     +Moter5_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
//          Motor_PWM_6=Int_Sort(
//                               Moter6_Thr_Scale*Throttle_Output
//                                 +Moter6_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
//                                   +Moter6_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
//                                     +Moter6_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
        }
        else//ˮƽ��̬�����ٶȶ���������Դ��ADRC
        {
          
          
        }
        Motor_PWM_1=Value_Limit(Thr_Idle,2000,Motor_PWM_1);//������޷�
        Motor_PWM_2=Value_Limit(Thr_Idle,2000,Motor_PWM_2);
        Motor_PWM_3=Value_Limit(Thr_Idle,2000,Motor_PWM_3);
        Motor_PWM_4=Value_Limit(Thr_Idle,2000,Motor_PWM_4);
        Motor_PWM_5=Value_Limit(Thr_Idle,2000,Motor_PWM_5);
        Motor_PWM_6=Value_Limit(Thr_Idle,2000,Motor_PWM_6);
      }
    }
  }
  else//δ�����������������λ��ͣת
  {
    Motor_PWM_1=Thr_Min;
    Motor_PWM_2=Thr_Min;
    Motor_PWM_3=Thr_Min;
    Motor_PWM_4=Thr_Min;
//    Motor_PWM_5=Thr_Min;
//    Motor_PWM_6=Thr_Min;
    Take_Off_Reset();//�����
    Throttle_Control_Reset();
	}
  Last_Motor_PWM_1=Motor_PWM_1;
  Last_Motor_PWM_2=Motor_PWM_2;
  Last_Motor_PWM_3=Motor_PWM_3;
  Last_Motor_PWM_4=Motor_PWM_4;
  Last_Motor_PWM_5=Motor_PWM_5;
  Last_Motor_PWM_6=Motor_PWM_6;
  
  Motor_PWM_1=Value_Limit(0,2000,Motor_PWM_1);//������޷�
  Motor_PWM_2=Value_Limit(0,2000,Motor_PWM_2);
  Motor_PWM_3=Value_Limit(0,2000,Motor_PWM_3);
  Motor_PWM_4=Value_Limit(0,2000,Motor_PWM_4);
  Motor_PWM_5=Value_Limit(0,2000,Motor_PWM_5);
  Motor_PWM_6=Value_Limit(0,2000,Motor_PWM_6);
  if(	Controler_Land_Mode==2)
	{
		Motor_PWM_1=0,Motor_PWM_2=0,Motor_PWM_3=0,Motor_PWM_4=0;  //�Ľ����Ϊ1000 ֹͣת��
	}
  PWM_Output(1.25*Motor_PWM_1,1.25*Motor_PWM_2,1.25*Motor_PWM_3,1.25*Motor_PWM_4,Motor_PWM_5,Motor_PWM_6,0,0);//Motor_PWM_5->PITCH   Motor_PWM_6->ROLL
}




