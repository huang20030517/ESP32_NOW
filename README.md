# **ESP32_NOW 项目文档**

---

### **1. 项目简介**

ESP-NOW 是由乐鑫（Espressif）开发的一种高效的无线通信协议，允许设备之间在没有传统 Wi-Fi 连接的情况下进行点对点或广播数据传输。它具有**低延迟**、**低功耗**的特点，适用于智能家居、物联网和工业控制等场景。

---

### **2. 功能概述**

- **点对点与广播通信**：支持单对单和一对多的灵活通信模式。
- **低延迟、低功耗**：非常适合需要快速响应的应用，如传感器和实时监控。
- **无连接传输**：无需依赖传统 Wi-Fi 网络即可实现数据传递。

---

### **3. 使用场景**

- **智能家居**：传感器数据采集与状态监控。
- **环境监控**：无 Wi-Fi 覆盖区域的多设备数据采集。
- **工业物联网**：短距离设备间的快速通信与控制。

---

### **4. 使用方法**

### 4.1 **准备环境**

- 安装 **ESP-IDF**（Espressif IoT Development Framework）。
- 准备至少两台 ESP32 设备用于通信测试。

### 4.2 **克隆项目**

```bash

git clone https://github.com/huang20030517/ESP32_NOW.git
cd ESP32_NOW

```

### 4.3 **安装依赖**

确保已正确设置 `IDF_PATH` 环境变量，并运行以下命令安装 Python 依赖：

```bash

python -m pip install -r %IDF_PATH%/requirements.txt

```

### 4.4 **编译与烧录**

将 ESP32 设备连接至电脑，执行以下命令：

```bash

idf.py set-target esp32s3
idf.py build
idf.py -p COMX flash  # 替换 COMX 为实际串口号

```

### 4.5 **监控设备日志**

```bash

idf.py monitor

```

---

### **5. 常见问题与解决**

- **无法发送消息**：确认目标设备 MAC 地址正确且已添加为对等设备。
- **设备未收到消息**：检查 Wi-Fi 信道是否一致，设备是否在有效通信范围内

---

### **6. 终端日志简要解释**

- **Wi-Fi 启动并进入 STA 模式**：
    
    ```
    
    I (556) wifi:mode : sta (c0:4e:30:3b:6a:b8)
    
    ```
    
    - 说明：设备已成功进入 STA 模式，准备发送和接收 ESP-NOW 消息。
- **消息发送成功**：
    
    ```
    
    I (556) ESP-NOW: Message sent successfully.
    
    ```
    
    - 说明：ESP-NOW 消息成功发送到对等设备。
- **消息发送失败**：
    
    ```
    
    E (556) ESP-NOW: Data sent to 24:6f:28:a1:b2:c3 with status: Failed
    
    ```
    
    - 说明：可能对方设备不在线或未正确注册为对等设备。
- **接收到消息**：
    
    ```
    
    I (6586) ESP-NOW: Received data from d2:aa:ca:3f:cc:aa: Hello from ESP-NOW!
    
    ```
    
    - 说明：成功接收到来自设备的 ESP-NOW 数据。

---

### **7. 项目链接与参考**

- [ESP-NOW 使用指南](https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/)
- ESP-IDF 官方文档
