#ifndef MIC_H
#define MIC_H
typedef enum
{
    MIC_OFF = 0,
    MIC_ON      
   
} Mic_type_value;

//@brief  :获取麦克风的状态，返回值为Mic_type_value类型，返回MIC_OFF表示麦克风关闭，返回MIC_ON表示麦克风开启
Mic_type_value Inf_get_Mic_Value(void);

#endif /* MIC_H */