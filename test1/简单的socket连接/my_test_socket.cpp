//linux下用，windows先不能用
//#include "public/stlplus3/portability/tcp.hpp"
//#include "games/hall/libgateclient/gateclient/client_frame/gate_client.h"
//#include "cocos2d.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "test_socket.h"
#define _BSD_SOCKLEN_T_ int
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define ERRNO errno
#define HERRNO h_errno
#define SOCKET int
#define SOCKET_ERROR -1
#define IOCTL ::ioctl
#define CLOSE ::close
#define SOCKLEN_T socklen_t
#define SEND_FLAGS MSG_NOSIGNAL
#ifdef SOLARIS
// Sun put some definitions in a different place
#include <sys/filio.h>
#endif
#include <string>

// void GateClientDlg_AppendInfo(const char * str)
// {
// 	CCLOG("%s", str);
// }
enum SOCKET_TYPE
{
	TCP = 1,
	UDP = 2
};

void init()
{

}

static void my_convert_address(unsigned long address, unsigned short port, sockaddr& sa)
{
	sa.sa_family = AF_INET;
	unsigned short network_port = htons(port);
	memcpy(&sa.sa_data[0], &network_port, sizeof(network_port));
	unsigned long network_address = htonl(address);
	memcpy(&sa.sa_data[2], &network_address, sizeof(network_address));
}

bool receive(SOCKET &m_socket, std::string& data)
{
	// determine how much data is available to read
	unsigned long bytes = 0;
	if (IOCTL(m_socket, FIONREAD, &bytes) == SOCKET_ERROR)
	{
		printf("ioctl read error\n");
		return false;
	}
	printf("bytes = %d\n", bytes);
	// get the data up to the amount claimed to be present - this is non-blocking
	char* buffer = new char[bytes + 1];
	int read = ::recv(m_socket, buffer, bytes, 0);
	if (read == SOCKET_ERROR)
	{
		delete[] buffer;
		return false;
	}
	if (read == 0)
	{
		// TODO - check whether this is an appropriate conditon to close the socket
		//close();
	}
	else
	{
		// this is binary data so copy the bytes including nulls
		data.append(buffer, read);
		printf("data = %s", data.c_str());
	}
	delete[] buffer;
	return true;
}

bool select(SOCKET &m_socket, bool readable, bool writeable, unsigned wait)
{
	//if (!initialised()) return false;
	// set up the readable set
	fd_set readable_set;
	fd_set* readable_set_ptr = 0;
	if (readable)
	{
		FD_ZERO(&readable_set);
		FD_SET(m_socket, &readable_set);
		readable_set_ptr = &readable_set;
	}
	// set up the writeable set
	fd_set writeable_set;
	fd_set* writeable_set_ptr = 0;
	if (writeable)
	{
		FD_ZERO(&writeable_set);
		FD_SET(m_socket, &writeable_set);
		writeable_set_ptr = &writeable_set;
	}
	// TODO - check the error set and lookup the error?
	fd_set* error_set_ptr = 0;
	// set up the timout value
	// Note: a null pointer implements a blocking select
	//       a pointer to a zero value implements a zero-wait poll
	//       a pointer to a positive value implements a poll with a timeout
	// I currently only implement polling with timeout which may be zero  - no blocking
	timeval timeout;
	timeval* timeout_ptr = 0;
	timeout.tv_sec = wait / 1000000;
	timeout.tv_usec = wait % 1000000;
	timeout_ptr = &timeout;
	// now test the socket
	int select_result = ::select(m_socket + 1, readable_set_ptr, writeable_set_ptr, error_set_ptr, timeout_ptr);
	/*
	switch ( select_result )
	{
	case SOCKET_ERROR:
	// select failed with an error - trap the error
	set_error ( ERRNO );
	return false;
	case 0:
	// timeout exceeded without a connection appearing
	return false;
	default:
	// at least one connection is pending
	// TODO - do we need to do the extra socket options checking on Posix?
	// TODO - does this connect in any way to the error_set above?
	return true;
	}
	*/
	if (writeable_set_ptr && select_result > 0)
	{
		if (FD_ISSET(m_socket, writeable_set_ptr))
		{
			printf("m_socket is writeable already\n");
		}
		else
		{
			printf("m_socket is not in writeable\n");
		}
	}

	if (readable_set_ptr && select_result > 0)
	{
		if (FD_ISSET(m_socket, readable_set_ptr))
		{
			printf("m_socket is readable already\n");
			std::string data;
			receive(m_socket, data);
		}
		else
		{
			printf("m_socket is not in readable\n");
		}
	}
	char buff[100] = "";
	sprintf(buff, "select_result is %d\n", select_result);
	printf(buff);
	return select_result>0;
}

unsigned long ip_lookup(const std::string& remote_address)
{
	unsigned long result = 0;
	// Lookup the IP address to convert it into a host record
	// this DOES lookup IP address names as well (not according to MS help !!)
	// TODO - convert this to use ::getaddrinfo - ::gethostbyname is deprecated

	hostent* host_info = ::gethostbyname(remote_address.c_str());
	if (!host_info)
	{
		printf("get host name error\n");
		return 0;
	}


	// extract the address from the host info
	unsigned long network_address = 0;
	memcpy(&network_address, host_info->h_addr, host_info->h_length);
	result = ntohl(network_address);
	return result;
}

void test_socket()
{
	SOCKET_TYPE type = TCP;
	SOCKET m_socket;
	// create an anonymous socket
	m_socket = ::socket(AF_INET, ((type == TCP) ? SOCK_STREAM : SOCK_DGRAM), 0);
	if (m_socket == INVALID_SOCKET)
	{
		return ;
	}
	printf("m_socket is created, value = %d\n", m_socket);
	// set the socket into non-blocking mode
	unsigned long nonblocking = 1;
 	if (IOCTL(m_socket, FIONBIO, &nonblocking) == SOCKET_ERROR)	//设置非阻塞标志
 	{

 		return ;
 	}

// 	while (1)
// 	{
// 		sleep(2);
// 		select(m_socket, true, true, 0);
// 	}
	
	
	char address[100] = "192.168.10.61";
	unsigned remote_port = 10100;
	unsigned long remote_address = ip_lookup(address);
	
	
	
	sockaddr connect_data;
	my_convert_address(remote_address, remote_port, connect_data);
	// connect binds the socket to a local address
	// if connectionless it simply sets the default remote address
	// if connectioned it makes the connection
	if (::connect(m_socket, &connect_data, sizeof(connect_data)) == SOCKET_ERROR)
	{
		// the socket is non-blocking, so connect will almost certainly fail with EINPROGRESS which is not an error
		// only catch real errors
		int error = ERRNO;
		if (error != EINPROGRESS && error != EWOULDBLOCK)
		{
			
			return false;
		}
	}
	// extract the remote connection details for local storage
	//convert_sockaddr(connect_data, m_remote_address, m_remote_port);
	
}
