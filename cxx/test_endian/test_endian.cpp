#include <iostream>

#include <arpa/inet.h>


static inline uint64_t htonll(uint64_t x)
{
  return (((uint64_t)htonl(x & 0xffffffffull)) << 32) | (htonl(x >> 32));
}

#if !defined(htobe16) && !defined(htobe32) && !defined(htobe64) && \
    !defined(htole16) && !defined(htole32) && !defined(htole64)

#ifndef __BYTE_ORDER__
#  define __BYTE_ORDER__ __LITTLE_ENDIAN__
#endif

#if __BYTE_ORDER__ == __LITTLE_ENDIAN__
#  define htobe16(x)  htons(x)
#  define htobe32(x)  htonl(x)
#  define htobe64(x)  htonll(x)
#  define htole16(x)  (x)
#  define htole32(x)  (x)
#  define htole64(x)  (x)
#elif __BYTE_ORDER__ == __BIG_ENDIAN__
#  define htole16(x)  htons(x)
#  define htole32(x)  htonl(x)
#  define htole64(x)  htonll(x)
#  define htobe16(x)  (x)
#  define htobe32(x)  (x)
#  define htobe64(x)  (x)
#else
#  error unknown byte order
#endif

#endif

template<typename T>
static T bit_field(T x, int lo, int hi)
{
  static_assert(0 <= lo && lo <= hi && hi < sizeof(T)*8, "bit not in range");
  constexpr size_t bits = sizeof(T) * 8;
  return x << bits - 1 - hi >> bits - 1 - hi + lo;
}



int main(int argc, char *argv[])
{
  uint64_t a = 0x1122334455667788;
  uint64_t b = htonll(a);
  std::cout << std::hex << a << "\n" << b << "\n";
  std::cout << bit_field(a, 0, 7);
  return 0;
}
