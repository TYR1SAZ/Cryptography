#include <fstream>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

int num;

int* Plaintext; // Открытый текст
int* Ciphertext; // Зашифрованный текст
int n;
int p, g, k, y, x, a;

// Расширенный алгоритм Евклида
int Exgcd(int m, int n, int& x)
{
	int x1, y1, x0, y0, y;
	x0 = 1; y0 = 0;
	x1 = 0; y1 = 1;
	x = 0; y = 1;
	int r = m % n;
	int q = (m - r) / n;
	while (r)
	{
		x = x0 - q * x1;
		y = y0 - q * y1;
		x0 = x1;
		y0 = y1;
		x1 = x;
		y1 = y;
		m = n;
		n = r;
		r = m % n;
		q = (m - r) / n;
	}
	return n;
}

// Является ли число простым; num - проверяемое число
bool IsPrimeNum(int num)
{
	if (num < 2)
	{
		return false;
	}
	else if (num == 2)
	{
		return true;
	}
	for (int i = 2; i <= num / 2 + 1; i++)
	{
		if (num % i == 0)
		{
			return false;
		}
	}
	return true;
}

int PrimeNum(int num)
{
	int count = 0;
	int num1;
	for (int i = 1; i < num; i++)
	{
		if (Exgcd(num, i, num1) == 1)
		{
			count++;
		}
	}
	return count;
}

// Двоичное преобразование
int BianaryTransform(int num, int bin_num[])
{
	int i = 0, mod = 0;
	// Преобразуется в двоичный, обратный временно сохраняется в массиве temp []
	while (num != 0)
	{
		mod = num % 2;
		bin_num[i] = mod;
		num = num / 2;
		i++;
	}
	// Возвращает количество цифр в двоичных числах
	return i;
}

// Повторное возведение в квадрат в степень
int Modular_Exonentiation(int a, int b, int n)
{
	int c = 0, bin_num[1000];
	int d = 1;
	int k = BianaryTransform(b, bin_num) - 1;

	for (int i = k; i >= 0; i--)
	{
		c = 2 * c;
		d = (d * d) % n;
		if (bin_num[i] == 1)
		{
			c = c + 1;
			d = (d * a) % n;
		}
	}
	return d;
}

int PrimitiveRoot(int num)
{
	if (num == 2)
	{
		return 1;
	}
	bool primitive = 0;
	int count = PrimeNum(num);
	for (int i = 2; i < num; i++)
	{
		primitive = 1;
		if (Modular_Exonentiation(i, count, num) == 1)
		{
			for (int j = 1; j < count; j++)
			{
				if (Modular_Exonentiation(i, j, num) == 1)
				{
					primitive = 0;
					break;
				}
			}
			if (primitive)
			{
				return i;
			}
		}
	}
	return 0;
}


// Повторное возведение в квадрат в степень
int Modular_Exonentiation(int a, int M, int b, int n)
{
	int c = 0, bin_num[1000];
	int d = 1;
	int k = BianaryTransform(b, bin_num) - 1;

	for (int i = k; i >= 0; i--)
	{
		c <<= 1;
		d = (d * d) % n;
		if (bin_num[i] == 1)
		{
			c = c + 1;
			d = (d * a) % n;
		}
	}
	d = (d * (M % n)) % n;
	return d;
}

// Генерация простых чисел в пределах 10000
int ProducePrimeNumber(int prime[])
{
	int c = 0;
	int vis[10001];
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i <= 10000; i++)
		if (!vis[i])
		{
			prime[c++] = i;
			for (int j = i * i; j <= 10000; j += i)
				vis[j] = 1;
		}
	return c;
}

int pow_mod(int a, int b, int m) {
	int res = 1 % m;
	while (b > 0) {
		if (b & 1) res = (res * 1LL * a) % m;
		a = (a * 1LL * a) % m;
		b >>= 1;
	}
	return res;
}

// Инициализация Elgamal
void Elgamal_Initialize()
{
	// Вынимаем простые числа в пределах 1000 и сохраняем их в массиве prime []
	int prime[10000];
	int count_Prime = ProducePrimeNumber(prime);

	// Случайно возьмем два простых числа p, q
	srand((unsigned)time(NULL));
	int ranNum1 = rand() % count_Prime;
	int ranNum2 = rand() % count_Prime;
	p = prime[ranNum1];
	while (p < 9000)
	{
		ranNum1 = rand() % count_Prime;
		p = prime[ranNum1];
	}

	g = PrimitiveRoot(p);

	x = rand() % (p - 2) + 1;

	k = rand() % (p - 2) + 1;

	y = Modular_Exonentiation(g, 1, x, p);

	cout << "Public Key (p, g, y) : p = " << p << ", g = " << g << ", y = " << y << '\n';
	cout << "Private Key (x) : x = " << x << '\n' << '\n';
}

// шифрование Elgamal
void Elgamal_Encrypt()
{
	int i = 0;
	a = Modular_Exonentiation(g, 1, k, p);
	for (i = 0; i < num; i++)
		Ciphertext[i] = Modular_Exonentiation(y, Plaintext[i], k, p);

	cout << "Use the public key (p, g, y) to encrypt:" << '\n';
	for (i = 0; i < num; i++)
		cout << (char)Ciphertext[i] << " ";
	cout << '\n' << '\n';
}

// Расшифровка Elgamal
void Elgamal_Decrypt()
{
	int i = 0;
	for (i = 0; i < num; i++)
		Ciphertext[i] = Modular_Exonentiation(a, Ciphertext[i], p - 1 - x, p);

	cout << "Use private key (x) to decrypt:" << '\n';
	for (i = 0; i < num; i++)
		cout << (char)Ciphertext[i];
	cout << '\n' << '\n';
}


// Инициализация алгоритма
void Initialize()
{
	int i;
	srand((unsigned)time(NULL));
	string line;
	string text;
	ifstream in("D:\\Text.txt");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			text += line;
		}
	}
	in.close();
	num = text.length();

	Plaintext = new int[num];
	Ciphertext = new int[num];

	for (i = 0; i < num; i++)
		Plaintext[i] = text[i];
	cout << "Generate num random numbers:" << '\n';
	for (i = 0; i < num; i++)
		cout << (char)Plaintext[i];
	cout << '\n' << '\n';
}

int main()
{

	Initialize();

	Elgamal_Initialize();

	Elgamal_Encrypt();

	Elgamal_Decrypt();
	return 0;
}