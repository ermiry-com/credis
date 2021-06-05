#ifndef _REDIS_H_
#define _REDIS_H_

#define REDIS_HOST_SIZE				128

typedef enum RedisStatus {

	REDIS_STATUS_DISCONNECTED		= 0,
	REDIS_STATUS_CONNECTED			= 1

} RedisStatus;

extern RedisStatus redis_get_status (void);

extern void redis_set_hostname (const char *host);

extern void redis_set_port (const unsigned int port);

// sets the connection timeout
// default to 1.5 seconds
extern void redis_set_timeout (
	const long seconds, const long miliseconds
);

// connects to the redis server
// returns 0 on success, 1 on error
extern unsigned int redis_connect (void);

// disconnects from the redis server
// returns 0 on success, 1 on error
extern unsigned int redis_disconnect (void);

// pings the db to test for a success connection
// returns 0 on success, 1 on error
extern unsigned int redis_ping_db (void);

#endif