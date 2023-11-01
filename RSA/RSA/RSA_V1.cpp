#include "RSA_V1.h"

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
long long Modular_Exonentiation(long long a, int b, int n)
{
	int c = 0, bin_num[1000];
	long long d = 1;
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

// Генерация простых чисел в пределах 1000
int ProducePrimeNumber(int prime[])
{
	int c = 0, vis[1001];
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i <= 1000; i++)
		if (!vis[i])
		{
			prime[c++] = i;
			for (int j = i * i; j <= 1000; j += i)
				vis[j] = 1;
		}

	return c;
}


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

// Инициализация RSA
void RSA_Initialize()
{
	// Вынимаем простые числа в пределах 1000 и сохраняем их в массиве prime []
	int prime[5000];
	int count_Prime = ProducePrimeNumber(prime);
	// Случайно возьмем два простых числа p, q
	srand((unsigned)time(NULL));
	int ranNum1 = rand() % count_Prime;
	int ranNum2 = rand() % count_Prime;
	long long unsigned p = prime[ranNum1], q = prime[ranNum2];
	p = 3557;
	q = 2579;
	n = p * q;

	int On = (p - 1) * (q - 1);

	// Используем расширенный алгоритм Евклида, чтобы найти e, d
	for (int j = 3; j < On; j += 1331)
	{
		int gcd = Exgcd(j, On, d);
		if (gcd == 1 && d > 0)
		{
			e = j;
			break;
		}
	}

}

// шифрование RSA
void RSA_Encrypt()
{
	cout << "Public Key (e, n) : e = " << e << " n = " << n << '\n';
	cout << "Private Key (d, n) : d = " << d << " n = " << n << '\n' << '\n';

	int i = 0;
	for (i = 0; i < num; i++)
		Ciphertext[i] = Modular_Exonentiation(Plaintext[i], e, n);

	cout << "Use the public key (e, n) to encrypt:" << '\n';
	for (i = 0; i < num; i++)
		cout << (char)Ciphertext[i] << " ";
	cout << '\n' << '\n';
}

// Расшифровка RSA
void RSA_Decrypt()
{
	int i = 0;
	for (i = 0; i < num; i++)
		Ciphertext[i] = Modular_Exonentiation(Ciphertext[i], d, n);

	cout << "Use private key (d, n) to decrypt:" << '\n';
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
	Ciphertext = new long long[num];

	for (i = 0; i < num; i++)
		Plaintext[i] = text[i];
	cout << "Generate num random numbers:" << '\n';
	for (i = 0; i < num; i++)
		cout << (char)Plaintext[i];
	cout << '\n' << '\n';
}
