#include <iostream>
#include <string.h>
using namespace std;

class HPint
{
	friend ostream& operator<<(ostream &cout, const HPint &x);
	friend istream& operator>>(istream &cin, HPint &x);
private:
	const static int maxlen = 5000;
	int len;
	int s[maxlen];
public:
	HPint();
	HPint(int inte);
	HPint(const char *stre);
	HPint operator=(const HPint &hpe);
	HPint operator=(int inte);
	HPint operator=(const char *stre);
	HPint operator*(const HPint &b);
	HPint operator*(int inte);
	HPint operator+(const HPint &b);
	HPint operator+(int inte);
	HPint operator-(const HPint &b);
	HPint operator-(int inte);
	HPint operator/(const HPint &b);
	HPint operator/(int inte);
	HPint operator%(const HPint &b);
	HPint operator%(int inte);
	int Compare(const HPint &b);
	int Compare(int inte);
};

ostream& operator<<(ostream &cout, const HPint &x)
{
	for (int i = 1; i <= x.len; i++)
		cout << x.s[x.len + 1 - i];
	return cout;
}

istream& operator>>(istream &cin, HPint &x)
{
	char *stre = new char[x.maxlen];
	cin >> stre;
	int strelen = strlen(stre);
	x.len = strelen;
	for (int i = 1; i <= strelen; i++)
		x.s[i] = stre[strelen - i] - '0';
	return cin;
}

HPint::HPint()
{
	len = 1;
	s[1] = 0;
}

HPint::HPint(int inte)
{
	if (inte == 0) { len = 1; s[1] = 0; return; }
	int i = 0;
	while (inte)
	{
		s[++i] = inte % 10;
		inte /= 10;
	}
	len = i; return;
}

HPint::HPint(const char *stre)
{
	len = strlen(stre);
	for (int i = 1; i <= len; i++)
		s[i] = stre[len - i] - '0';
	return;
}

HPint HPint::operator=(const HPint &hpe)
{
	len = hpe.len;
	for (int i = 1; i <= len; i++)
		s[i] = hpe.s[i];
	return (*this);
}

HPint HPint::operator=(int inte)
{
	if (inte == 0) { len = 1; s[1] = 0; return (*this); }
	int i = 0;
	while (inte)
	{
		s[++i] = inte % 10;
		inte /= 10;
	}
	len = i; return (*this);
}

HPint HPint::operator=(const char *stre)
{
	len = strlen(stre);
	for (int i = 1; i <= len; i++)
		s[i] = stre[len - i] - '0';
	return (*this);
}

HPint HPint::operator*(const HPint &b)
{
	int i, j; HPint c;
	c.len = len + b.len;
	for (i = 1; i <= c.len; i++) c.s[i] = 0;
	for (i = 1; i <= len; i++)
		for (j = 1; j <= b.len; j++)
			c.s[i + j - 1] += s[i] * b.s[j];
	for (i = 1; i < c.len; i++)
	{
		c.s[i + 1] += c.s[i] / 10;
		c.s[i] %= 10;
	}
	while (c.s[i])
	{
		c.s[i + 1] = c.s[i] / 10;
		c.s[i] %= 10;
		i++;
	}
	while (i > 1 && c.s[i] == 0) i--;
	c.len = i; return c;
}

HPint HPint::operator*(int inte)
{
	HPint b(inte);
	return ((*this) * b);
}

HPint HPint::operator+(const HPint &b)
{
	int i; HPint c;
	c.s[1] = 0;
	for (i = 1; i <= len || i <= b.len || c.s[i]; i++)
	{
		if (i <= len) c.s[i] += s[i];
		if (i <= b.len) c.s[i] += b.s[i];
		c.s[i + 1] = c.s[i] / 10; c.s[i] %= 10;
	}
	c.len = i - 1; if (c.len == 0) c.len = 1;
	return c;
}

HPint HPint::operator+(int inte)
{
	HPint b(inte);
	return ((*this) + b);
}

HPint HPint::operator-(const HPint &b)
{
	int i, j; HPint c;
	for (i = 1, j = 0; i <= len; i++)
	{
		c.s[i] = s[i] - j;
		if (i <= b.len) c.s[i] -= b.s[i];
		if (c.s[i] < 0) { c.s[i] += 10; j = 1; }
		else j = 0;
	}
	c.len = len;
	while (c.len > 1 && c.s[c.len] == 0) c.len--;
	return c;
}

HPint HPint::operator-(int inte)
{
	HPint b(inte);
	return ((*this) - b);
}

int HPint::Compare(const HPint &b)
{
	if (len > b.len) return 1;
	if (len < b.len) return -1;
	int i = len;
	while (i > 1 && s[i] == b.s[i]) i--;
	return (s[i] - b.s[i]);
}

int HPint::Compare(int inte)
{
	HPint b(inte);
	return ((*this).Compare(b));
}

HPint HPint::operator/(const HPint &b)
{
	int i, j; HPint d(0); HPint c;
	for (i = len; i > 0; i--)
	{
		if (!(d.len == 1 && d.s[1] == 0))
		{
			for (j = d.len; j > 0; j--)
				d.s[j + 1] = d.s[j];
			d.len++;
		}
		d.s[1] = s[i]; c.s[i] = 0;
		while ((j = d.Compare(b)) >= 0)
		{
			d = d - b; c.s[i]++;
			if (j == 0) break;
		}
	}
	c.len = len;
	while (c.len > 1 && c.s[c.len] == 0) c.len--;
	return c;
}

HPint HPint::operator/(int inte)
{
	HPint b(inte);
	return ((*this) / b);
}

HPint HPint::operator%(const HPint &b)
{
	int i, j; HPint d(0);
	for (i = len; i > 0; i--)
	{
		if (!(d.len == 1 && d.s[1] == 0))
		{
			for (j = d.len; j > 0; j--)
				d.s[j + 1] = d.s[j];
			d.len++;
		}
		d.s[1] = s[i];
		while ((j = d.Compare(b)) >= 0)
		{
			d = d - b;
			if (j == 0) break;
		}
	}
	return d;
}

HPint HPint::operator%(int inte)
{
	HPint b(inte);
	return ((*this) % b);
}