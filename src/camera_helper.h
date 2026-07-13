/**
 * camera_helper.h — 摄像头拍照模块接口
 *
 * 将 NiusCam 摄像头 + SD 卡存储封装为独立模块。
 * main.cpp 只需 #include "camera_helper.h" 并调用以下三个函数。
 */
#pragma once

#include <Arduino.h>

/**
 * 初始化摄像头和 SD 卡。
 * 在 setup() 中调用一次。
 * @return true 成功，false 失败（串口会打印错误信息）
 */
bool cameraInit();

/**
 * 拍一张照并自动命名保存到 SD 卡 /Pictures 目录。
 * 文件名格式: /Pictures/IMGXXXXXX.jpg（6位序号，自动递增）
 * @return 成功返回文件路径字符串，失败返回空字符串 ""
 */
String capturePhoto();

/**
 * 打印 SD 卡容量和剩余空间到串口。
 * 可选调用，用于监控存储状态。
 */
void cameraInfo();
