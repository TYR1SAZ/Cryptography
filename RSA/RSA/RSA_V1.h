#pragma once
#include <fstream>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

int num;

int* Plaintext; // �������� �����
long long* Ciphertext; // ������������� �����
int n, e = 0, d;

// �������� ��������������
int BianaryTransform(int num, int bin_num[]);

// ��������� ���������� � ������� � �������
long long Modular_Exonentiation(long long a, int b, int n);

// ��������� ������� ����� � �������� 1000
int ProducePrimeNumber(int prime[]);


// ����������� �������� �������
int Exgcd(int m, int n, int& x);

// ������������� RSA
void RSA_Initialize();

// ���������� RSA
void RSA_Encrypt();

// ����������� RSA
void RSA_Decrypt();


// ������������� ���������
void Initialize();
