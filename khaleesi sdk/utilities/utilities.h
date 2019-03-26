#pragma once

#include <iostream>
#include <cmath>
#include <Psapi.h>
#include <iomanip>
#include <ctime>
#include <chrono>

#include "vector.h"
#include "..\interfaces\interfaces.h"
#include "singleton.h"
#include ".\..\sdk\source-sdk\c_input.h"

#define in_range(x, a, b)   (x >= a && x <= b)

#define get_bits(x)    (in_range((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (in_range(x,'0','9') ? x - '0' : 0))
#define get_byte(x)    (get_bits(x[0]) << 4 | get_bits(x[1]))

namespace utilities {
	static auto get_signature(const char* szModule, const char* szSignature) -> uintptr_t {
		const char* pat = szSignature;
		DWORD firstMatch = 0;
		DWORD rangeStart = (DWORD)GetModuleHandleA(szModule);
		MODULEINFO miModInfo;
		GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
		DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
		for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++) {
			if (!*pat)
				return firstMatch;

			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == get_byte(pat)) {
				if (!firstMatch)
					firstMatch = pCur;

				if (!pat[2])
					return firstMatch;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else
					pat += 2;
			}
			else {
				pat = szSignature;
				firstMatch = 0;
			}
		} return NULL;
	}

	template <typename T>
	static T call_v_table(void* address, int index) {
		return (*reinterpret_cast<T**>(address))[index];
	}

	template <typename T>
	static T get_v_function(void* pClass, int iIndex) {
		PDWORD p_vtable = *(PDWORD*)pClass;
		DWORD dw_address = p_vtable[iIndex];
		return (T)(dw_address);
	}

	static auto console_log(const std::string& output) -> void {
		std::cout << "[log]: " << output << "\n";
	}

	static auto console_warn(const std::string& output) -> void {
		std::cout << "[warning]: " << output << "\n";
	}

	static auto console_error(const std::string& output) -> void {
		std::cout << "[error]: " << output << "\n";
	}

	static auto set_clantag(const char* tag) -> void {
		static auto clantag_set = reinterpret_cast<void(__fastcall*)(const char*)>((DWORD)(utilities::get_signature("engine.dll", "53 56 57 8B DA 8B F9 FF 15")));
		clantag_set(tag);
	}
}

namespace math {
	
}