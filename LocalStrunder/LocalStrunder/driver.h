#pragma once
#include <WinSock2.h>
#include "server_shared.h"
#include "junk.h"

namespace driver
{
	void	initialize();
	void	deinitialize();
	extern int currentProcessId;
	SOCKET	connect();
	void	disconnect(SOCKET connection);

	uint32_t read_memory(SOCKET connection, uint32_t process_id, uintptr_t address, uintptr_t buffer, size_t size);
	uint32_t write_memory(SOCKET connection, uint32_t process_id, uintptr_t address, uintptr_t buffer, size_t size);
	uint64_t get_process_base_address(SOCKET connection, uint32_t process_id);
	uint64_t get_process_pid(SOCKET connection, wchar_t pname[], size_t size);

	template <typename T>
	T read(const SOCKET connection, const uint32_t process_id, const uintptr_t address)
	{		
		T buffer{ };

		read_memory(connection, process_id, address, uint64_t(&buffer), sizeof(T));

		return buffer;
	}

	template <typename T>
	T read_SP(const SOCKET connection, const uint32_t process_id, const uintptr_t address,size_t Size)
	{
		T buffer{ };

		read_memory(connection, process_id, address, uint64_t(&buffer), Size);

		return buffer;
	}

	template <typename T>
	void write(const SOCKET connection, const uint32_t process_id, const uintptr_t address, const T& buffer)
	{
		write_memory(connection, process_id, address, uint64_t(&buffer), sizeof(T));
	}
}