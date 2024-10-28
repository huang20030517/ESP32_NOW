#include <string.h>
#include "freertos/FreeRTOS.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_now.h"

#define TAG "ESP-NOW"

// 发送完成的回调函数
void on_data_sent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    ESP_LOGI(TAG, "Data sent to %02x:%02x:%02x:%02x:%02x:%02x with status: %s",
             mac_addr[0], mac_addr[1], mac_addr[2],
             mac_addr[3], mac_addr[4], mac_addr[5],
             status == ESP_NOW_SEND_SUCCESS ? "Success" : "Failed");
}

// 接收数据的回调函数
void on_data_recv(const uint8_t *mac_addr, const uint8_t *data, int len)
{
    ESP_LOGI(TAG, "Received data from %02x:%02x:%02x:%02x:%02x:%02x: %.*s",
             mac_addr[0], mac_addr[1], mac_addr[2],
             mac_addr[3], mac_addr[4], mac_addr[5], len, data);
}

// 添加 ESP-NOW 对等设备
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
    // 初始化 NVS，用于 Wi-Fi 存储
    ESP_ERROR_CHECK(nvs_flash_init());

    // 初始化网络接口和 Wi-Fi
    ESP_ERROR_CHECK(esp_netif_init());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA)); // 设置为 STA 模式
    ESP_ERROR_CHECK(esp_wifi_start());                 // 启动 Wi-Fi

    // 初始化 ESP-NOW
    ESP_ERROR_CHECK(esp_now_init());
    esp_now_register_send_cb(on_data_sent); // 注册发送回调
    esp_now_register_recv_cb(on_data_recv); // 注册接收回调
}

void app_main(void)
{
    // 设置对等设备的 MAC 地址
    uint8_t peer_mac[6] = {0x24, 0x6F, 0x28, 0xA1, 0xB2, 0xC3};

    // 初始化 ESP-NOW 和 Wi-Fi
    espnow_init();

    // 添加对等设备
    add_peer(peer_mac);

    // 要发送的消息
    const char *message = "Hello from ESP-NOW!";

    // 发送消息
    send_espnow_message(peer_mac, message);
}
