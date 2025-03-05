#include <Arduino.h>
#include <mbedtls/md.h>

void hash() {
    const char *message = "Hello, world!";
    unsigned char output[32];
    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
    mbedtls_md_starts(&ctx);
    mbedtls_md_update(&ctx, (const unsigned char *)message, strlen(message));
    mbedtls_md_finish(&ctx, output);
    mbedtls_md_free(&ctx);

    Serial.print("SHA-256 hash: ");
    for (int i = 0; i < 32; i++) {
        Serial.printf("%02x", output[i]);
    }
    Serial.println();
}