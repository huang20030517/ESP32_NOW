#include <string.h>
#include "freertos/FreeRTOS.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_now.h"

#define TAG "ESP-NOW"
#define MESSAGE "Hello from ESP-NOW!"

// 发送回调函数
void on_data_sent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    const char *color_red = "\033[1;31m"; // ANSI 转义码：红色
    const char *color_reset = "\033[0m";  // ANSI 转义码：重置颜色

    if (status == ESP_NOW_SEND_SUCCESS)
    {
        ESP_LOGI(TAG, "Data sent to %02x:%02x:%02x:%02x:%02x:%02x, status: Success",
                 mac_addr[0], mac_addr[1], mac_addr[2],
                 mac_addr[3], mac_addr[4], mac_addr[5]);
    }
    else
    {
        printf("%s", color_red); // 启用红色输出
        ESP_LOGE(TAG, "Data sent to %02x:%02x:%02x:%02x:%02x:%02x, status: Failed",
                 mac_addr[0], mac_addr[1], mac_addr[2],
                 mac_addr[3], mac_addr[4], mac_addr[5]);
        printf("%s", color_reset); // 重置颜色
    }
}

// 接收回调函数
void on_data_recv(const esp_now_recv_info_t *info, const uint8_t *data, int len)
{
    ESP_LOGI(TAG, "Received data from %02x:%02x:%02x:%02x:%02x:%02x: %.*s",
             info->src_addr[0], info->src_addr[1], info->src_addr[2],
             info->src_addr[3], info->src_addr[4], info->src_addr[5], len, data);
}

// 添加对等设备
void add_peer(const uint8_t *peer_mac)
{
    esp_now_peer_info_t peer_info = {};
    memcpy(peer_info.peer_addr, peer_mac, ESP_NOW_ETH_ALEN);
    peer_info.channel = 0;     // 使用当前 Wi-Fi 通道
    peer_info.encrypt = false; // 不加密数据

    ESP_ERROR_CHECK(esp_now_add_peer(&peer_info));
}

// 发送 ESP-NOW 消息
void send_espnow_message(const uint8_t *peer_mac, const char *message)
{
    esp_err_t result = esp_now_send(peer_mac, (uint8_t *)message, strlen(message));
    if (result == ESP_OK)
    {
        ESP_LOGI(TAG, "Message sent successfully.");
    }
    else
    {
        ESP_LOGE(TAG, "Error sending message: %d", result);
    }
}

// 初始化 ESP-NOW 和 Wi-Fi
void espnow_init()
{
    ESP_ERROR_CHECK(nvs_flash_init()); // 初始化 NVS
    ESP_ERROR_CHECK(esp_netif_init()); // 初始化网络接口

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA)); // 设置为 STA 模式
    ESP_ERROR_CHECK(esp_wifi_start());                 // 启动 Wi-Fi

    ESP_ERROR_CHECK(esp_now_init());        // 初始化 ESP-NOW
    esp_now_register_send_cb(on_data_sent); // 注册发送回调
    esp_now_register_recv_cb(on_data_recv); // 注册接收回调
}

// 应用程序主入口
void app_main(void)
{
    uint8_t peer_mac[6] = {0x24, 0x6F, 0x28, 0xA1, 0xB2, 0xC3}; // 对等设备的 MAC 地址

    espnow_init();      // 初始化 ESP-NOW 和 Wi-Fi
    add_peer(peer_mac); // 添加对等设备

    // 循环发送消息
    while (1)
    {
        send_espnow_message(peer_mac, MESSAGE); // 发送消息
        vTaskDelay(pdMS_TO_TICKS(1000));        // 每隔 1 秒发送一次
    }
}
