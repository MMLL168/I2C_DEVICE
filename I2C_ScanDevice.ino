#include <Wire.h>

// 定義 I2C 引腳
#define SDA_PIN 21  // 根據實際接線修改
#define SCL_PIN 22  // 根據實際接線修改

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);     // 等待序列埠準備好
  
  Wire.begin(SDA_PIN, SCL_PIN);
  
  Serial.println("\nI2C 掃描器");
  Serial.printf("SDA: %d, SCL: %d\n", SDA_PIN, SCL_PIN);
  scanI2C();
}

void loop() {
  delay(5000);           // 每5秒掃描一次
  scanI2C();
}

void scanI2C() {
  byte error, address;
  int nDevices = 0;
  
  Serial.println("\n掃描中...");
  
  for(address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.printf("發現I2C設備於地址 0x%02X (十進制:%d)\n", address, address);
      nDevices++;
    }
    else if (error == 4) {
      Serial.printf("地址 0x%02X 發生未知錯誤\n", address);
    }
  }
  
  if (nDevices == 0) {
    Serial.println("未找到I2C設備\n");
    Serial.println("可能的問題：");
    Serial.println("1. 檢查接線是否正確");
    Serial.println("2. 確認SDA和SCL引腳定義是否正確");
    Serial.println("3. 檢查是否有上拉電阻(建議4.7K)");
    Serial.println("4. 確認設備供電是否正常(3.3V)");
  } else {
    Serial.printf("掃描完成，找到 %d 個設備\n", nDevices);
  }
}
