#include <openssl/aes.h>
#include <openssl/evp.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(const char* msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void encrypt_decrypt(FILE* in, unsigned char* key, int enc, FILE* out)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        error("Ошибка создания контекста");

    if (EVP_CipherInit_ex(ctx, EVP_aes_192_cbc(), NULL, NULL, NULL, enc) != 1)
        error("Ошибка инициализации контекста");

    if (EVP_CipherInit_ex(ctx, NULL, NULL, key, key, enc) != 1)
        error("Ошибка установки ключа и IV");

    unsigned char inbuf[1024];
    int inlen;
    while ((inlen = fread(inbuf, 1, 1024, in)) > 0)
    {
        unsigned char outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
        int outlen;
        if (EVP_CipherUpdate(ctx, outbuf, &outlen, inbuf, inlen) != 1)
            error("Ошибка шифрования/дешифрования данных");
        fwrite(outbuf, 1, outlen, out);
    }

    unsigned char outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
    int outlen;
    if (EVP_CipherFinal_ex(ctx, outbuf, &outlen) != 1)
        error("Ошибка завершения шифрования/дешифрования");
    fwrite(outbuf, 1, outlen, out);
    EVP_CIPHER_CTX_free(ctx);
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    if (argc != 5)
        error("Неверное количество аргументов. Использование: ./program in_file key enc out_file");
    FILE* in;
    errno_t err_in = fopen_s(&in, argv[1], "rb");
    if (err_in != 0 || !in)
        error("Ошибка открытия входного файла");
    unsigned char key[24];
    if (strlen(argv[2]) != 24)
        error("Неверная длина ключа. Ключ должен быть длиной 24 байта (192 бита)");
    memcpy(key, argv[2], 24);
    int enc;
    if (strcmp(argv[3], "1") == 0)
        enc = 1;
    else if (strcmp(argv[3], "0") == 0)
        enc = 0;
    else
        error("Неверный флаг шифрования/дешифрования. Флаг должен быть 1 для шифрования или 0 для дешифрования");
    FILE* out;
    errno_t err_out = fopen_s(&out, argv[4], "wb");
    if (err_out != 0 || !out)
        error("Ошибка открытия выходного файла");

    encrypt_decrypt(in, key, enc, out);

    fclose(in);
    fclose(out);

    return 0;
}
