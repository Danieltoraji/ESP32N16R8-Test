/**
 * camera_helper.cpp — 摄像头拍照模块实现
 *
 * 内部封装 NiusCam Camera + Storage 对象，对外只暴露
 * cameraInit() / capturePhoto() / cameraInfo() 三个接口。
 */
#include "camera_helper.h"

#include <NiusCam.h>
#include <NiusCamStorage.h>

using namespace NiusCam;

// ---- 内部对象（不暴露给外部）----
static Camera camera;
static Storage storage;

// 文件序号计数器（saveNextJpeg 成功后自动递增）
static uint32_t photoSeq = 0;

// 拍照保存目录和文件前缀
static const char *PHOTO_DIR = "/Pictures";
static const char *PHOTO_PREFIX = "IMG";

bool cameraInit() {
  Serial.println("========================================");
  Serial.println("  摄像头 + SD 卡初始化中...");
  Serial.println("========================================");

  // 初始化摄像头（自动检测 ESP32-S3-CAM 板子配置）
  Result camResult = camera.begin();
  if (!camResult) {
    Serial.print("[错误] 摄像头初始化失败: ");
    Serial.println(camResult.message());
    return false;
  }
  Serial.println("[OK] 摄像头初始化成功");

  // 初始化 SD 卡（自动检测 SD_MMC 1-bit）
  Result sdResult = storage.begin();
  if (!sdResult) {
    Serial.print("[错误] SD 卡初始化失败: ");
    Serial.println(sdResult.message());
    return false;
  }
  Serial.println("[OK] SD 卡初始化成功");

  // 打印 SD 卡信息
  cameraInfo();

  return true;
}

String capturePhoto() {
  // 拍照
  Frame frame = camera.capture();
  if (!frame) {
    Serial.println("[错误] 拍照失败：未获取到帧");
    return "";
  }

  // 确认是 JPEG 格式
  if (frame.nativeFormat() != PIXFORMAT_JPEG) {
    Serial.println("[错误] 拍照失败：非 JPEG 格式");
    return "";
  }

  Serial.printf("拍照: %ux%u, %u bytes\n",
                (unsigned)frame.width(),
                (unsigned)frame.height(),
                (unsigned)frame.size());

  // 保存到 SD 卡 /Pictures 目录，自动命名 IMG000000.jpg
  uint32_t seqBefore = photoSeq;
  Result saveResult = storage.saveNextJpeg(frame, PHOTO_DIR, PHOTO_PREFIX, &photoSeq);
  if (!saveResult) {
    Serial.print("[错误] 保存失败: ");
    Serial.println(saveResult.message());
    return "";
  }

  // saveNextJpeg 成功后 photoSeq 已递增，实际使用的序号是 seqBefore
  // 但 saveNextJpeg 内部可能从已有文件扫描出更大的序号，所以用 photoSeq - 1 反推
  char path[64];
  snprintf(path, sizeof(path), "%s/%s%06lu.jpg",
           PHOTO_DIR, PHOTO_PREFIX, (unsigned long)(photoSeq - 1));

  Serial.printf("[OK] 已保存: %s\n", path);
  return String(path);
}

void cameraInfo() {
  if (!storage.mounted()) {
    Serial.println("[警告] SD 卡未挂载");
    return;
  }

  StorageInfo info = storage.info();
  Serial.println("---- SD 卡信息 ----");
  Serial.printf("  容量: %llu MB\n", info.capacityBytes / (1024 * 1024));
  Serial.printf("  已用: %llu MB\n", info.usedBytes / (1024 * 1024));
  Serial.printf("  可用: %llu MB\n", info.freeBytes / (1024 * 1024));
  Serial.println("-------------------");
}
