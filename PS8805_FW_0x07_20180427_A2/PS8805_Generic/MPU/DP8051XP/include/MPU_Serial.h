#ifndef _MPU_SERIAL_H_
#define _MPU_SERIAL_H_
typedef enum _MPU_COMM_STATUS
{
	MPU_COMM_SUCCESS = 0,
	MPU_COMM_QUEUEDUP,
	MPU_COMM_OCCUPIED,
	MPU_COMM_FAIL,
	MPU_COMM_STATUS_MAX
}MPU_COMM_STATUS;
#endif