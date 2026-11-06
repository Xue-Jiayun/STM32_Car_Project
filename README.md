# STM32_Car_Project

基于 STM32F103C8 标准库的智能车工程，包含 LED、OLED 显示屏、舵机控制三个功能模块。

## 硬件平台

- 主控芯片：STM32F103C8T6
- 开发环境：Keil MDK-ARM / STM32CubeIDE
- 标准库版本：STM32F10x_StdPeriph_Driver V3.5.0

## 功能模块

| 模块 | 引脚 | 通信方式 | 说明 |
|------|------|----------|------|
| LED | PA8 | GPIO推挽输出 | 闪烁指示系统运行 |
| OLED | PB6(SCL)/PB7(SDA) | I2C软件模拟 | SSD1306 128x64 显示屏 |
| 舵机 | PA0 | TIM2_CH1 PWM | 50Hz PWM，0~180度控制 |

## 目录结构

```
STM32_Car_Project/
├── User/
│   ├── main.c          # 主程序
│   ├── led.c/h         # LED驱动
│   ├── oled.c/h        # OLED驱动（I2C软件模拟）
│   ├── servo.c/h       # 舵机驱动（TIM PWM）
│   └── delay.c/h       # 延时函数（SysTick）
├── StdPeriph_Driver/   # 标准库驱动（需自行添加）
├── CMSIS/              # CMSIS核心（需自行添加）
└── README.md
```

## 使用方法

1. 在Keil中新建工程，选择STM32F103C8芯片
2. 添加User目录下所有.c文件到工程
3. 添加标准库驱动文件（stm32f10x_gpio.c, stm32f10x_tim.c, stm32f10x_rcc.c等）
4. 配置Include路径包含User、StdPeriph_Driver、CMSIS目录
5. 编译下载

## Git分支说明

- `main` - LED亮灯功能（基础GPIO操作）
- `feature/oled` - OLED显示屏功能（I2C通信）
- `feature/servo` - 舵机控制功能（PWM输出）
