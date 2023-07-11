#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "sdkconfig.h"
#include "RTC_Format.h"
#include "BoardParameter.h"



void Brd_LoadDefaultValue()
{
	esp_err_t err = ESP_OK;
	uint32_t valArray[INDEX_SERV_RUN_HOURS_ALARM + 1] = {
		10,
		8,
		2,
		55,
		550,
		1210,
		2250,
		2080,
		2240,
		160,
		400,
		6,
		18000,
		4,
		18650,
		24540
	};
	char s[50];
	for(uint8_t i = INDEX_TOTAL_VAN; i <= INDEX_SERV_RUN_HOURS_ALARM; i++){
		err = Brd_SetParamInt(i,valArray[i],s);
		if(err == ESP_OK) ESP_LOGI("LoadValueBoard","%s",s);
		else ESP_LOGE("LoadValueBoard","%s",s);
		memset(s,0,strlen(s));
	}
}




void app_main(void)
{
	nvs_flash_init();
	// Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );
	
	Brd_LoadDefaultValue();
	// Brd_WriteParamToFlash();
	Brd_ReadParamFromFlash();
	Brd_PrintAllParameter();
}
