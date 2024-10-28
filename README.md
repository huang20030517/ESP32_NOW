1. 项目简介
ESP-NOW 是由乐鑫（Espressif）开发的一种轻量级的无线通信协议，主要用于多设备之间的短距离通信。相比于传统的 Wi-Fi 协议，ESP-NOW 不需要建立连接即可发送数据，且具有低延迟和低功耗的优势。它广泛应用于物联网设备、智能家居、环境监控等需要快速响应的场景。

2. 功能概述
点对点通信：支持多个设备之间建立点对点数据传输。
广播模式：允许将同一条消息广播给多个设备。
实时响应：低延迟的数据传输，非常适用于需要快速通信的场景。
离线操作：设备间通信无需依赖 Wi-Fi 网络。
3. 使用场景
智能家居：用于传感器之间的通信，例如门窗状态监控。
环境监控：在无需 Wi-Fi 覆盖的区域，通过多设备采集环境数据。
工业物联网：设备之间短距离、高速数据交换，提高监控效率。
4. 使用步骤
准备工作：

安装 ESP-IDF（Espressif IoT Development Framework）。
准备至少两个 ESP32 设备进行测试。
克隆项目：

bash
复制代码
git clone https://github.com/huang20030517/ESP32_NOW.git
cd ESP32_NOW
安装依赖： 确保已正确安装 ESP-IDF，并使用以下命令安装 Python 依赖：

bash
复制代码
python -m pip install -r %IDF_PATH%/requirements.txt
编译和烧录： 将设备连接至电脑，运行以下命令进行编译并烧录：

bash
复制代码
idf.py set-target esp32s3
idf.py build
idf.py -p COMX flash  # 替换 COMX 为实际串口号
运行与监控： 运行以下命令查看设备的日志输出：

bash
复制代码
idf.py monitor
5. 常见问题与解决
无法找到 esp_event.h 文件：

检查 ESP-IDF 是否正确安装，并确保路径变量 IDF_PATH 设置正确。
设备无法发送或接收消息：

确认两个设备的 MAC 地址正确无误，并且已经使用 esp_now_add_peer 添加对等设备。
编译失败，提示 build.ninja 错误：

运行以下命令重新配置项目：
bash
复制代码
idf.py reconfigure
6. 项目链接与参考
查看完整项目源码和更多说明：ESP32-NOW GitHub 项目

更多 ESP-NOW 详细说明：ESP-NOW 官方文档
