#include <includes.h>

void TaskStar(void *ppdata) reentrant;
OS_STK TaskStartStk[MaxStkSize];//ע�⣺����ASM�ļ�������?STACK�ռ�Ϊ40H��64��

void main(void)
{
    OSInit();
    
    InitTimer0();
    
    OSTaskCreate(TaskStar, (void *)0, &TaskStartStk[0],2);   
    
    OSStart();
}


void TaskStart(void *ppdata) reentrant
{
    ppdata=ppdata;
    
    //ע�⣡��������ȼ�����ѭ��ǰ�򿪶�ʱ���жϣ���������OSStart()ǰ�������жϵ�Ҫ��
    //��ϵͳ����OSInit����ʱ���Զ�����һ�����ȼ���͵�ϵͳ���񣬴��������л����OS_EXIT_CRITICAL������EA��
    //����InitTimer0()���T0�жϣ���Υ������OSStart()ǰ�������жϵ�Ҫ��
    //�мǽ�ET0=1;����������ȼ������OSStart()������OSStartHighRdy()��һ������������ȼ���������ET0=1���ܱ���һ��ִ�С�
    ET0=1;    
    for(;;){
        
        OSTimeDly(OS_TICKS_PER_SEC);    
    }
}

