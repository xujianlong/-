/*
 * server.c
 *
 *  Created on: 2015��7��22��
 *      Author: Administrator
 */
#include "server.h"
void ICACHE_FLASH_ATTR server_recv(void *arg, char *pdata, unsigned short len)
{
	os_printf("*#%s", pdata);
	//espconn_sent((struct espconn *) arg, "�Ѿ��յ�", strlen("�Ѿ��յ�"));
	//espconn_send((struct espconn *) arg, pdata, strlen(pdata));
}
void ICACHE_FLASH_ATTR server_sent(void *arg)
{
	//os_printf("���ͳɹ���");
}
void ICACHE_FLASH_ATTR server_discon(void *arg)
{
	os_printf("*#%d",0xff);
}

void ICACHE_FLASH_ATTR server_listen(void *arg)
{
	struct espconn *pespconn = arg;
	espconn_regist_recvcb(pespconn, server_recv);
	espconn_regist_sentcb(pespconn, server_sent);
	espconn_regist_disconcb(pespconn, server_discon);
}
void ICACHE_FLASH_ATTR server_recon(void *arg, sint8 err)
{
	//os_printf("���Ӵ��󣬴������Ϊ��%d\r\n", err);
}
void ICACHE_FLASH_ATTR server_init(struct ip_addr *local_ip, int port)
{

	//��ʼ��espconn����
	esp_conn.type = ESPCONN_TCP;
	esp_conn.state = ESPCONN_NONE;
	esp_conn.proto.tcp = (esp_tcp *) os_malloc(sizeof(esp_tcp));
	os_memcpy(esp_conn.proto.tcp->local_ip, local_ip, 4);
	esp_conn.proto.tcp->local_port = port;

	//ע�����ӳɹ��ص��������������ӻص�����
	espconn_regist_connectcb(&esp_conn, server_listen);
	espconn_regist_reconcb(&esp_conn, server_recon);

	espconn_accept(&esp_conn);
}

