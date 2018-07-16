#include <includes.h>

void TaskStar(void *ppdata) reentrant;
OS_STK TaskStartStk[MaxStkSize];//注意：我在ASM文件中设置?STACK空间为40H即64。

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
    
    //注意！在最高优先级任务循环前打开定时器中断，以满足在OSStart()前不产生中断的要求。
    //在系统调用OSInit（）时会自动创建一个优先级最低的系统任务，创建过程中会调用OS_EXIT_CRITICAL（）打开EA。
    //若在InitTimer0()里打开T0中断，则违反了在OSStart()前不产生中断的要求。
    //切记将ET0=1;放在最高优先级任务里，OSStart()将调用OSStartHighRdy()第一个运行最高优先级任务，这样ET0=1总能被第一个执行。
    ET0=1;    
    for(;;){
        
        OSTimeDly(OS_TICKS_PER_SEC);    
    }
}

