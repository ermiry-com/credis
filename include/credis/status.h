#ifndef _CREDIS_STATUS_H_
#define _CREDIS_STATUS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum RedisStatus {

	REDIS_STATUS_DISCONNECTED		= 0,
	REDIS_STATUS_CONNECTED			= 1

} RedisStatus;

#ifdef __cplusplus
}
#endif

#endif