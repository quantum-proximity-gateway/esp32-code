#ifndef TOTP_H
#define TOTP_H

#include <cstddef> // For size_t definition
#include <cstdint> // For uint64_t definition

unsigned int generate_totp(const unsigned char *key, size_t key_len, uint64_t time_now);

#endif // TOTP_H