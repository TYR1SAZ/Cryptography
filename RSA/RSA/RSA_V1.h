#pragma once
#include <fstream>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

int num;

int* Plaintext; // Открытый текст
long long* Ciphertext; // Зашифрованный текст
int n, e = 0, d;

// Двоичное преобразование
int BianaryTransform(int num, int bin_num[]);

// Повторное возведение в квадрат в степень
long long Modular_Exonentiation(long long a, int b, int n);

// Генерация простых чисел в пределах 1000
int ProducePrimeNumber(int prime[]);


// Расширенный алгоритм Евклида
int Exgcd(int m, int n, int& x);

// Инициализация RSA
void RSA_Initialize();

// шифрование RSA
void RSA_Encrypt();

// Расшифровка RSA
void RSA_Decrypt();


// Инициализация алгоритма
void Initialize();
