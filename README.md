# ESP32_NOW**项目文档**

## **1. 项目简介**

ESP-NOW 是乐鑫开发的一种低功耗、低延迟的无线通信协议，允许设备之间在没有 Wi-Fi 网络的情况下进行快速的数据传输。它适用于智能家居、物联网等场景。

## **2. 功能概述**

- **点对点和广播通信**：设备可以进行单对单或一对多通信。
- **低延迟、低功耗**：非常适合需要快速响应的应用。
- **无连接传输**：无需 Wi-Fi 连接即可发送数据。

## **3. 使用场景**

- **智能家居**：门窗传感器等设备的实时监控。
- **环境监控**：无需网络覆盖的区域数据采集。
- **工业物联网**：短距离设备间的数据传输。

## **4. 使用方法**

1. **准备环境**：确保安装了 ESP-IDF 和 Python 依赖。
2. **克隆项目**：
    
    ```bash
    
    git clone https://github.com/huang20030517/ESP32_NOW.git
    cd ESP32_NOW
    
    ```
    
3. **编译与烧录**：
    
    ```bash
    
    idf.py set-target esp32s3
    idf.py build
    idf.py -p COMX flash  # 替换 COMX 为实际串口号
    
    ```
    
4. **查看设备日志**：
    
    ```bash
    
    idf.py monitor
    
    ```
    

## **5. 常见问题**

- **esp_event.h 文件丢失**：检查是否正确安装 ESP-IDF。
- **设备无法通信**：确认 MAC 地址正确，且已经添加对等设备。

## **6. 项目链接与参考**

- [ESP-NOW 使用指南](https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/)
- [ESP-IDF 官方文档](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/)
