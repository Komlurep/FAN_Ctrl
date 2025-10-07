<!--
 * @Author: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @Date: 2025-10-07 16:31:39
 * @LastEditors: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @LastEditTime: 2025-10-07 17:16:20
 * @FilePath: \FAN_Ctrl\README.md
 * @Description: 叙述文件
-->
# FAN_Ctrl

本项目基于 STM32F407VET6 的风扇检测与控制（由 STM32CubeMX 创建）。

## 主要设备

- STM32F407VET6 开发板（示例板：https://gitee.com/zalileo/HX32F4-Board ）
- 12V 电源
- 4-pin PWM 可调电脑风扇（含 FG/TACH）
- 电位器（作为 ADC 输入）

## 功能简述

- 使用定时器输入捕获读取风扇 FG 信号，计算频率/转速（RPM）。
- 使用定时器 PWM 输出控制风扇占空比进行调速。
- 通过 ADC 读取电位器作为目标值输入。
- 在开发板板上支持数码管显示与串口打印，用于调试与显示信息。

## 接线简要（通用）

- 风扇 V+ -> 外部12V电源正极
- 风扇 GND -> 外部12V电源负极（与开发板共地）
- 风扇 FG ->  MCU的定时器输入捕获引脚（TIMx_CHy）
- 风扇 PWM -> MCU的PWM输出引脚
- 电位器中点 -> MCU的ADC引脚

> 提示：不同开发板引脚不同，请以 `FAN_Ctrl.ioc` 中的配置为准。

## 使用

1. 按上面接线，确保共地。
2. 上电并观察串口/数码管输出（串口波特率请参照代码）。
3. 旋转电位器改变目标值，观察转速与占空比变化。

## 工程结构

- `FAN_Ctrl.ioc` — CubeMX 配置（查看外设与引脚）
- `Core/` — 主程序与外设初始化（main.c、tim.c、adc.c 等）
- `Modules/` — 风扇控制/测速、ADC 读取、数码管显示等模块实现
- `APP/` — 应用层
- `MDK-ARM/`、`build/` — Keil 工程与EIDE编译产物

## 注意事项

- 风扇电源不要由 MCU 直接供电。PWM 信号通常为控制信号，需要驱动电路。
- FG 信号可能需要上拉/下拉或滤波，空载时读数可能不稳定。



