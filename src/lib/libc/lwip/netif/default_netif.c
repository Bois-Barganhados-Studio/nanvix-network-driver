/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

#include "lwip/opt.h"
#include "lwip/netif.h"
#include "lwip/ip_addr.h"
#include "lwip/tcpip.h"
#include "lwip/default_netif.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/etharp.h"
#include "lwip/prot/ethernet.h"
#include "lwip/prot/ip4.h"
#include "lwip/prot/udp.h"
#include "lwip/prot/tcp.h"
#include "sys/times.h"

// add include to lock and unlock interrupts
#include "lwip/sys.h"

#define MAC_SEND_BUFFER_SIZE 2 * 4096 // Adjust the size according to your needs

#define ETHERNET_MTU 1500

static uint8_t mac_send_buffer[MAC_SEND_BUFFER_SIZE];

static struct netif netif;
static int node_number = -1;

float do_float_calc(float start_num)
{
  double resp = start_num;
  int i = 1;
  while (i <= 10000000)
  {
    resp *= i;
    i++;
  }
  return resp;
}

float sum_float()
{
  float resp = -1.0f;
  switch (node_number)
  {
  case 1:
    printf("Processing mult float using Node 1 \n");
    resp = do_float_calc(1.0f);
    break;
  case 2:
    printf("Processing mult float using Node 2 \n");
    resp = do_float_calc(10000.0f);
    break;
  case 3:
    resp = do_float_calc(20000.0f);
    printf("Processing mult float using Node 3 \n");
    break;
  case 4:
    resp = do_float_calc(30000.0f);
    printf("Processing mult float using Node 4 \n");
    break;
  default:
    printf("Node not found \n");
    break;
  }
  return resp;
}

void unlock_interrupts()
{
  printf("unlocking interrupts\n");
  // unlock interrupts
  // __asm__ volatile("sti");
  printf("unlocked interrupts\n");
}

void lock_interrupts()
{
  printf("locking interrupts\n");
  // lock interrupts
  // __asm__ volatile("cli");
  printf("locked interrupts\n");
}

static err_t
netif_output(struct netif *netif, struct pbuf *p)
{
  printf("NETIF OUTPUT start \n");
  LINK_STATS_INC(link.xmit);
  /* Update SNMP stats (only if you use SNMP) */
  MIB2_STATS_NETIF_ADD(netif, ifoutoctets, p->tot_len);
  int unicast = ((*(uint8_t *)(p->payload) & 0x01) == 0);
  if (unicast)
  {
    MIB2_STATS_NETIF_INC(netif, ifoutucastpkts);
  }
  else
  {
    MIB2_STATS_NETIF_INC(netif, ifoutnucastpkts);
  }
  clock_t start = times(NULL);
  printf("Try lock interrupts \n");
  lock_interrupts();
  printf("Locked! \n");
  pbuf_copy_partial(p, mac_send_buffer, MAC_SEND_BUFFER_SIZE, 0);
  printf("PBUF copy ok! \n");
  // do calc on data
  float resp = sum_float();
  printf("Calculated with success! \n");
  unlock_interrupts();
  // write response at the end of the buffer
  *(float *)(mac_send_buffer + MAC_SEND_BUFFER_SIZE - sizeof(float)) = resp;
  printf("Write done! \n");
  clock_t end = times(NULL);
  int time = (int)(end - start);
  printf("Time: %d \n", time);
  printf("NETIF OUTPUT end \n");
  return ERR_OK;
}
static void
netif_status_callback(struct netif *netif)
{
  printf("netif status changed %s\n", ip4addr_ntoa(netif_ip4_addr(netif)));
}
static err_t
my_netif_init(struct netif *netif)
{
  printf("init netif sys\n");
  uint8_t mac_address[ETH_HWADDR_LEN] = {0x52, 0x54, 0x00, 0x12, 0x34, 0x56 + node_number}; // Replace with your MAC address
  netif->linkoutput = netif_output;
  netif->output = etharp_output;
  netif->mtu = ETHERNET_MTU;
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET | NETIF_FLAG_IGMP | NETIF_FLAG_MLD6;
  MIB2_INIT_NETIF(netif, snmp_ifType_ethernet_csmacd, 100000000);
  // add my mac address inside SMEMCPY
  SMEMCPY(netif->hwaddr, mac_address, ETH_HWADDR_LEN);
  netif->hwaddr_len = ETH_HWADDR_LEN;
  printf("init netif sys ended with success\n");
  return ERR_OK;
}

#if LWIP_IPV4
#define NETIF_ADDRS ipaddr, netmask, gw,
void init_default_netif(const ip4_addr_t *ipaddr, const ip4_addr_t *netmask, const ip4_addr_t *gw, int node_id)
#else
#define NETIF_ADDRS
void init_default_netif(void)
#endif
{
  node_number = node_id;
#if NO_SYS
  printf("default netif starting add \n");
  netif_add(&netif, NETIF_ADDRS NULL, my_netif_init, netif_input);
#else
  netif_add(&netif, NETIF_ADDRS NULL, tapif_init, tcpip_input);
#endif
  netif_set_default(&netif);
}

void default_netif_poll(void)
{
  netif_poll(&netif);
}

void default_netif_shutdown(void)
{
}