#include <stdio.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/socket.h>
#include <linux/can.h>
#include <linux/can/error.h>
#include <linux/can/raw.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "cmd.h"
#include "serial.h"

#ifndef AF_CAN
#define AF_CAN 29
#endif
#ifndef PF_CAN
#define PF_CAN AF_CAN
#endif

#define errout(_s)	fprintf(stderr, "error class: %s\n", (_s))
#define errcode(_d) fprintf(stderr, "error code: %02x\n", (_d))

#define SERIAL_SEND 1
#define ttyO1   1

static void handle_frame(struct can_frame *fr)
{
	int i, len;
	unsigned char rdata[10];
	unsigned char tdata[10];
	unsigned char crc = 0;
	//printf("%08x\n", fr->can_id & CAN_EFF_MASK);
	//printf("%08x\n", fr->can_id);
	//printf("dlc = %d\n", fr->can_dlc);
	if(fr->data[0] == 0x02){
		for(i = 0; i < 8; i++){
			rdata[i] = fr->data[i];
		}
	}
	else {
		errout("CMD DATA ERROR");
		return;
	}
#if SERIAL_SEND
	tdata[0] = 0xA5;
	crc = tdata[0];
	for(i = 1; i < 9; i++) {
		tdata[i] = rdata[i-1];
		crc ^= tdata[i];
	}
	tdata[9] = crc;
	len = WriteComPort(tdata, 10);
	if(len < 0){
		fprintf(stderr, "Write data to Serial port %d error\n", ttyO1);
	}
	for (i = 0; i < 10; i++)
		printf("%02x ", tdata[i]);
	printf("\n");
#else
	handle_cmd(rdata);
#endif
}

static void handle_err_frame(const struct can_frame *fr)
{
	if (fr->can_id & CAN_ERR_TX_TIMEOUT) {
		errout("CAN_ERR_TX_TIMEOUT");
	}
	if (fr->can_id & CAN_ERR_LOSTARB) {
		errout("CAN_ERR_LOSTARB");
		errcode(fr->data[0]);
	}
	if (fr->can_id & CAN_ERR_CRTL) {
		errout("CAN_ERR_CRTL");
		errcode(fr->data[1]);
	}
	if (fr->can_id & CAN_ERR_PROT) {
		errout("CAN_ERR_PROT");
		errcode(fr->data[2]);
		errcode(fr->data[3]);
	}
	if (fr->can_id & CAN_ERR_TRX) {
		errout("CAN_ERR_TRX");
		errcode(fr->data[4]);
	}
	if (fr->can_id & CAN_ERR_ACK) {
		errout("CAN_ERR_ACK");
	}
	if (fr->can_id & CAN_ERR_BUSOFF) {
		errout("CAN_ERR_BUSOFF");
	}
	if (fr->can_id & CAN_ERR_BUSERROR) {
		errout("CAN_ERR_BUSERROR");
	}
	if (fr->can_id & CAN_ERR_RESTARTED) {
		errout("CAN_ERR_RESTARTED");
	}
}
#define myerr(str)	fprintf(stderr, "%s, %s, %d: %s\n", __FILE__, __func__, __LINE__, str)

static int test_can_rw(int fd, int master)
{
	int ret;
	struct can_frame frdup;
	struct timeval tv;
	fd_set rset;

	while (1) {
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		FD_ZERO(&rset);
		FD_SET(fd, &rset);

		ret = select(fd+1, &rset, NULL, NULL, NULL);
		if (ret == 0) {
			myerr("select time out");
			return -1;
		}

		ret = read(fd, &frdup, sizeof(frdup));
		if (ret < sizeof(frdup)) {
			myerr("read failed");
			return -1;
		}
		if (frdup.can_id & CAN_ERR_FLAG) { /* 出错设备错误 */
			handle_err_frame(&frdup);
			myerr("CAN device error");
			continue;
		}
		handle_frame(&frdup);
	}

	return 0;
}

int main(int argc, char *argv[])
{
   	int s;
   	int ret;
   	struct sockaddr_can addr;
   	struct ifreq ifr;
	int master = 0;

#if SERIAL_SEND
	// open serial
	ret = OpenComPort(ttyO1, 115200, 8, "1", 10);
	if(ret < 0) {
		fprintf(stderr, "Open Serial port %d failed\n", ttyO1);
		return ret;
	}
	else {
		fprintf(stdout, "Open Serial port %d sucess\n");
	}
#endif

	srand(time(NULL));
   	s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
   	if (s < 0) {
       	perror("socket PF_CAN failed");
       	return 1;
   	}

   	strcpy(ifr.ifr_name, "can0");
   	ret = ioctl(s, SIOCGIFINDEX, &ifr);
   	if (ret < 0) {
       	perror("ioctl failed");
       	return 1;
   	}

   	addr.can_family = PF_CAN;
   	addr.can_ifindex = ifr.ifr_ifindex;

   	ret = bind(s, (struct sockaddr *)&addr, sizeof(addr));
   	if (ret < 0) {
       	perror("bind failed");
       	return 1;
   	}
	/*
	if (1) {
		struct can_filter filter[2];
		filter[0].can_id = 0x200 | CAN_EFF_FLAG;
		filter[0].can_mask = 0xFFF;

		filter[1].can_id = 0x20F | CAN_EFF_FLAG;
		filter[1].can_mask = 0xFFF;


		ret = setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &filter, sizeof(filter));
		if (ret < 0) {
			perror("setsockopt failed");
			return 1;
		}
	}
	*/
	test_can_rw(s, master);

	close(s);
#if SERIAL_SEND
	CloseComPort();
#endif
	return 0;
}
