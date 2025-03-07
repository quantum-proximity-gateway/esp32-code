#include <Arduino.h>
#include <mbedtls/md.h>

#define TIME_STEP 30      // Time step in seconds (commonly 30)
#define TOTP_DIGITS 6     // Number of digits in OTP

unsigned int generate_totp(const unsigned char *key, size_t key_len, uint64_t time_now) {
    uint64_t time_counter = time_now / TIME_STEP;
    unsigned char counter[8];

    // Convert time_counter to an 8-byte array
    for (int i = 7; i >= 0; i--) {
        counter[i] = time_counter & 0xFF;
        time_counter >>= 8;
    }
    
    // Set up the HMAC context using SHA-1 (as per RFC 6238 default)
    const mbedtls_md_info_t *md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA1);
    
    unsigned char hmac_result[20]; // SHA-1 produces a 20-byte hash
    mbedtls_md_context_t ctx;
    mbedtls_md_init(&ctx);
    
    if(mbedtls_md_setup(&ctx, md_info, 1) != 0) {
        mbedtls_md_free(&ctx);
        return 0;
    }
    
    if(mbedtls_md_hmac_starts(&ctx, key, key_len) != 0) {
        mbedtls_md_free(&ctx);
        return 0;
    }
    
    if(mbedtls_md_hmac_update(&ctx, counter, sizeof(counter)) != 0) {
        mbedtls_md_free(&ctx);
        return 0;
    }
    
    if(mbedtls_md_hmac_finish(&ctx, hmac_result) != 0) {
        mbedtls_md_free(&ctx);
        return 0;
    }
    
    mbedtls_md_free(&ctx);
    
    // Truncation as specified in RFC 4226
    int offset = hmac_result[19] & 0x0F;
    unsigned int bin_code = ((hmac_result[offset] & 0x7F) << 24) |
                            ((hmac_result[offset + 1] & 0xFF) << 16) |
                            ((hmac_result[offset + 2] & 0xFF) << 8) |
                            (hmac_result[offset + 3] & 0xFF);
    
    // OTP is binary mod 10^TOTP_DIGIT
    unsigned int mod_divisor = 1;
    for (int i = 0; i < TOTP_DIGITS; i++) {
        mod_divisor *= 10;
    }
    
    unsigned int otp = bin_code % mod_divisor;
    return otp;
}