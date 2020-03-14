#include "c_types.h"
#include "eagle_soc.h"
#include "gpio.h"
#include "osapi.h"
#include "ip_addr.h"
#include "espconn.h"
#include "debug.h"

void receive_callback(void *arg, char *p_data, unsigned short len); 
void sent_callback(void *arg);
 
// Create UDP function. This is where we finalize our UDP connection block
// with the desination IP and port. Then we create the client UDP connection.
void ICACHE_FLASH_ATTR create_udp(struct espconn *p_espconn)
{
  sint16 result = 0;

  const char udp_remoteip[4] = {192,168,4,2};
  os_memcpy(p_espconn->proto.udp->remote_ip, udp_remoteip, 4);
  p_espconn->proto.udp->remote_port = 8266;

  // Create the UDP connection
  result = espconn_create(p_espconn);

  #ifdef DEBUG_ON
    os_printf("espconn create status: %d\n", result);
  #endif

  // Let's create a pointer to our esp_udp structure so we can more succinctly
  // parse the individual elements of our remote IP array.

  esp_udp *p_udp;
  p_udp = p_espconn->proto.udp;

  #ifdef DEBUG_ON
    os_printf("Remote IP: %d.%d.%d.%d\n", p_udp->remote_ip[0],p_udp->remote_ip[1],p_udp->remote_ip[2],p_udp->remote_ip[3]);
    os_printf("Remote port: %d\n", p_udp->remote_port);
  #endif

  // Register our callbacks
  result = espconn_regist_sentcb(p_espconn, sent_callback);
  #ifdef DEBUG_ON
    os_printf("espconn register sent cb status: %d\n", result);
  #endif
  result = espconn_regist_recvcb(p_espconn, receive_callback);
  #ifdef DEBUG_ON
    os_printf("espconn register recv cb status: %d\n", result);
  #endif

}


// Poll function ... read the status of GPIO2
void ICACHE_FLASH_ATTR poll_function (void) {
  uint8 level;
  level = GPIO_INPUT_GET(GPIO_ID_PIN(2));
  #ifdef DEBUG_ON
    os_printf("GPIO2: %d\n", level);
  #endif
  os_delay_us(100);
}

// Receive callback function. Nothing to do here (yet).
void ICACHE_FLASH_ATTR receive_callback(void *arg, char *p_data, unsigned short len) 
{
}

// Sent callback function. Nothing to do here (yet).
void ICACHE_FLASH_ATTR sent_callback(void *arg) 
{
}

