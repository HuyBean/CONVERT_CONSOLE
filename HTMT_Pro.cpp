#include <iostream>
#include <math.h>
#include <windows.h>
#include <cstring>
#include <string>
#include <conio.h>
#include <cstdint>
#include <iomanip>
#include <algorithm>
using namespace std;

// 21127511 - NGUYỄN QUỐC HUY
// 21127158 - LÊ HOÀNG SANG

// MARKING FUNCTION
void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// SIMPLE CONVERT FUNCTIONS
int Convert(char c)
{
    if (c >= '0' && c <= '9')
    {
        return (int)c - '0';
    }
    else
    {
        return (int)c - 'A' + 10;
    }
}
double toDeci(char *str, int base)
{
    int len = strlen(str);
    int Somu = 1;
    double Res = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (Convert(str[i]) >= base)
        {
            cout << "Wrong Number ";
            return -1;
        }
        Res += Convert(str[i]) * Somu;
        Somu = Somu * base;
    }
    return Res;
}

// FILLING FUNCTIONS
void fillbit(long long x, int bit, int Signed)
{
    int count = 0;
    int a = x;
    while (a != 0)
    {
        count++;
        a = a / 10;
    }
    while (count < bit)
    {
        cout << (Signed < 0) ? "0" : "1";
        count++;
    }
}
void fillbitstring(string str, int bit, int Signed)
{
    int l = str.length();
    int count = 0;
    while (l < bit)
    {
        cout << (Signed < 0) ? "1" : "0";
        l++, count++;
        if (count == 8 || count == 16 || count == 24 || count == 32)
        {
            cout << " ";
        }
    }
    cout << str;
}

// MAKE STRING FUNCTIONS
string findTwoscomplement(string str)
{
    long long n = str.length();
    int i;
    for (i = n - 1; i >= 0; i--)
        if (str[i] == '1')
            break;
    if (i == -1)
        return '1' + str;
    for (int k = i - 1; k >= 0; k--)
    {
        if (str[k] == '1')
        {
            str[k] = '0';
        }
        else
        {
            str[k] = '1';
        }
    }
    return str;
}
string ConvertFromDecimal(long long from, int to)
{
    string res;
    string stringDigit;
    while (from != 0)
    {
        int digit;
        digit = from % to;
        if (digit < 10)
        {
            stringDigit = '0' + digit;
        }
        else
        {
            stringDigit = digit - 10 + 'A';
        }
        res = stringDigit + res;
        from /= to;
    }
    return res;
}
string toBase16(unsigned num)
{
    const string chars = "0123456789ABCDEF";
    string res;
    while (num > 0)
    {
        res = chars[num % 16] + res;
        num /= 16;
    }
    return res;
}

// INPUT BIT TO DECIMAL FUNCTION
void BitToDecimal(int bit, int Signed)
{
    char *str = new char[bit];
    switch (bit)
    {
    case 8:
        if (Signed == 1)
            cout << "Input the 8 bit sequence of Signed Char: ";
        if (Signed != 1)
            cout << "Input the 8 bit sequence of Unsigned Char: ";
        break;
    case 16:
        if (Signed == 1)
            cout << "Input the 16 bit sequence of Signed Short: ";
        if (Signed != 1)
            cout << "Input the 16 bit sequence of Unsigned Short: ";
        break;
    case 32:
        if (Signed == 1)
            cout << "Input the 32 bit sequence of Signed Int: ";
        if (Signed != 1)
            cout << "Input the 32 bit sequence of Unsigned Int: ";
        break;
    }
    cin >> str;
    bool valid = true;
    for (int i = 0; i < strlen(str) - 1; i++)
    {
        if (str[i] == '1' || str[i] == '0')
        {
            valid = true;
        }
        else
        {
            valid = false;
        }
    }
    while (valid == false)
    {
        cout << "The bit sequence must contain only 0 and 1, please try again: ";
        cin >> str;
        for (int i = 0; i < strlen(str) - 1; i++)
        {
            if (str[i] == '1' || str[i] == '0')
            {
                valid = true;
            }
            else
            {
                valid = false;
            }
        }
    }
    double res = toDeci(str, 2);
    cout << "The decimal value of the bit sequence:\n";
    cout << str << " = " << res << endl;
}

// BIT TO FLOAT FUNCTIONS
void format_M(char *bin_arr, int &size)
{
    int del = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        if (bin_arr[i] == '0')
        {
            bin_arr[i] = '\0';
            del++;
        }
        else if (bin_arr[i] == '1')
            break;
    }
    for (int i = ((size - 1) - del + 2); i >= 0; i--)
    {
        bin_arr[i] = bin_arr[i - 2];
    }
    bin_arr[0] = '1';
    bin_arr[1] = '.';

    size -= del;
    size += 2;

    return;
}
void swap_2Char(char &a, char &b)
{
    char tmp;
    tmp = a;
    a = b;
    b = tmp;
}
char *add0_Fisrt(char *M, int &M_size, int p_idx, int E_val, int &count_multi)
{
    char *res = new char[M_size + (count_multi - p_idx) + 1];

    int i = 0;

    cout << endl
         << "countMulti: " << count_multi << endl;

    for (; i < M_size + (abs(E_val) - p_idx) + 1; i++)
    {
        res[i] = '0';
        if (count_multi < 0)
            break;
        count_multi--;
    }
    int j = 0;
    for (; i < M_size + (abs(E_val) - p_idx) + 1; i++)
    {
        res[i] = M[j];
        j++;
    }

    M_size = M_size + (abs(E_val) - p_idx) + 1;
    res[M_size] = '\0';

    int point = 0;
    for (; point < M_size; point++)
    {
        if (res[point] == '.')
            break;
    }
    cout << endl
         << res << endl;
    cout << "point " << point << endl;
    for (int k = point; k > 1; k--)
    {
        swap_2Char(res[k], res[k - 1]);
    }
    cout << "after multiply negative: " << res << endl;
    return res;
}
void multiply_2Bin_positive(char *M, int M_size, int E_val)
{
    // finding point
    int point_idx = 0;
    while (point_idx < M_size)
    {
        point_idx++;
        if (M[point_idx] == '.')
            break;
    }

    // case E > 0: doi dau cham ve ben phai
    int count_multi = 0;
    for (int i = point_idx; i < M_size; i++)
    {
        swap_2Char(M[i], M[i + 1]);
        count_multi++;
        if (M[M_size - 1] == '.' && count_multi < E_val)
        {
            do
            {
                M[i++] = 0;
                count_multi++;
            } while (count_multi < E_val);
        }
        if (count_multi == E_val)
            break;
    }
    return;
}
char *multiply_2Bin_negative(char *M, int &M_size, int E_val)
{
    // finding point
    int point_idx = 0;
    while (point_idx < M_size)
    {
        point_idx++;
        if (M[point_idx] == '.')
            break;
    }

    // case E < 0: doi dau cham ve ben trai
    char *res;
    int count_multi = abs(E_val);
    for (int i = point_idx; i >= 0; i--)
    {
        swap_2Char(M[i], M[i - 1]);
        count_multi--;
        if (M[0] == '.' && count_multi > 0)
        {
            res = add0_Fisrt(M, M_size, point_idx, E_val, count_multi);
        }
        if (count_multi == 0)
            break;
    }
    return res;
}
float BinToNum_f(char *M, int M_size)
{
    float res = 0;
    int p_idx = 0;
    int pow2 = 0;
    while (p_idx <= M_size)
    {
        p_idx++;
        if (M[p_idx] == '.')
        {
            for (int i = p_idx - 1; i >= 0; i--)
            {
                if (M[i] == '1')
                    res += float(pow(2, pow2));
                pow2++;
            }
            pow2 = -1;
            for (int i = p_idx + 1; i <= M_size; i++)
            {
                if (M[i] == '1')
                    res += float(pow(2, pow2));
                pow2--;
            }
            return res;
        }
    }
    return 0;
}
float BinTo_FloatPoint(char *arr)
{
    char S = arr[0];
    char E[9];

    for (int i = 0; i < 8; i++)
    {
        E[i] = arr[i + 1];
    }
    // E[9] = '\0';

    int M_size = strlen(arr) - 9;
    char *M = new char[M_size + 1];

    for (int i = 0; i < M_size; i++)
    {
        M[i] = arr[i + 9];
    }

    int S_val = (int)arr[0] - '0';
    int E_val = toDeci(E, 2) - 127;

    format_M(M, M_size);
    M[M_size] = '\0';
    cout << M << endl;

    cout << "S Val: " << S_val << endl;
    cout << "E Val: " << E_val << endl;
    cout << "M Sz: " << M_size << endl;

    if (E_val == 0)
        return (pow((-1), S_val) * BinToNum_f(M, M_size));
    else if (E_val > 0)
    {
        multiply_2Bin_positive(M, M_size, E_val);
        cout << "M: ";
        cout << M << endl;
        float res = pow((-1), S_val) * BinToNum_f(M, M_size);
        return res;
    }
    else if (E_val < 0)
    {
        char *resArr = multiply_2Bin_negative(M, M_size, E_val);
        cout << resArr << endl;
        float res = pow((-1), S_val) * BinToNum_f(resArr, M_size);
        return res;
    }

    return 0;
}

// BIT TO DOUBLE FUNCTIONS
double BinToNum_d(char *M, int M_size)
{
    double res = 0;
    int p_idx = 0;
    int pow2 = 0;
    while (p_idx <= M_size)
    {
        p_idx++;
        if (M[p_idx] == '.')
        {
            for (int i = p_idx - 1; i >= 0; i--)
            {
                if (M[i] == '1')
                    res += double(pow(2, pow2));
                pow2++;
            }
            pow2 = -1;
            for (int i = p_idx + 1; i <= M_size; i++)
            {
                if (M[i] == '1')
                    res += double(pow(2, pow2));
                pow2--;
            }
            return res;
        }
    }
    return 0;
}
double BinTo_DoublePoint(char *arr)
{
    char S = arr[0];
    char E[12];

    for (int i = 0; i < 11; i++)
    {
        E[i] = arr[i + 1];
    }

    int M_size = strlen(arr) - 12;
    char *M = new char[M_size + 1];

    for (int i = 0; i < M_size; i++)
    {
        M[i] = arr[i + 12];
    }

    int S_val = (int)arr[0] - '0';
    int E_val = toDeci(E, 2) - 1023;

    format_M(M, M_size);
    M[M_size] = '\0';

    // cout << "S Val: " << S_val << endl;
    // cout << "E Val: " << E_val << endl;
    // cout << "M Sz: " << M_size << endl;

    if (E_val == 0)
        return (pow((-1), S_val) * BinToNum_d(M, M_size));
    else if (E_val > 0)
    {
        multiply_2Bin_positive(M, M_size, E_val);
        double res = pow((-1), S_val) * BinToNum_d(M, M_size);
        return res;
    }
    else if (E_val < 0)
    {
        char *resArr = multiply_2Bin_negative(M, M_size, E_val);
        double res = pow((-1), S_val) * BinToNum_d(resArr, M_size);
        return res;
    }

    return 0;
}

// BIT TO 8 - 16 - 32
void Unsigned_Char(long long x)
{
    if (x > 255)
    {
        cout << "The maximum range of Unsigned Char is 255\n";
    }
    if (x < 0)
    {
        cout << "The Unsigned Char must be >= 0 \n";
    }
    else
    {
        cout << "0x";
        string hexa = toBase16(x);
        fillbitstring(hexa, 2, 1);
        cout << " = ";
        string res = ConvertFromDecimal(x, 2);
        fillbitstring(res, 8, 1);
        // system("pause");
    }
}
void Signed_Char(long long x)
{
    if (x > 127)
    {
        cout << "The maximum range of Signed Char is 127\n";
    }
    if (x < -128)
    {
        cout << "The minimum range of Signed Char is -128\n";
    }
    else
    {
        if (x > 0)
        {
            cout << "0x";
            string hexa = toBase16(x);
            fillbitstring(hexa, 2, 1);
            cout << " = ";
            string res = ConvertFromDecimal(x, 2);
            fillbitstring(res, 8, 1);
            return;
        }
        if (x < 0)
        {
            cout << "0x";
            string hexa = toBase16(x);
            fillbitstring(hexa, 2, -1);
            cout << " = ";
            string res = findTwoscomplement(ConvertFromDecimal(abs(x), 2));
            fillbitstring(res, 8, -1);
            return;
        }
    }
}
void Unsigned_Short(long long x)
{
    if (x > 65535)
    {
        cout << "The maximum range of Unsigned Short is 65535\n";
    }
    if (x < 0)
    {
        cout << "The Unsigned Short must be >= 0 \n";
    }
    else
    {
        cout << "0x";
        string hexa = toBase16(x);
        fillbitstring(hexa, 4, 1);
        cout << " = ";
        string res = ConvertFromDecimal(x, 2);
        fillbitstring(res, 16, 1);
    }
}
void Signed_Short(long long x)
{
    if (x > 32767)
    {
        cout << "The maximum range of Signed Short is 32767\n";
    }
    if (x < -32768)
    {
        cout << "The minimum range of Signed Short is -32768\n";
    }
    else
    {
        if (x > 0)
        {
            cout << "0x";
            string hexa = toBase16(x);
            fillbitstring(hexa, 4, 1);
            cout << " = ";
            string res = ConvertFromDecimal(x, 2);
            fillbitstring(res, 16, 1);
            return;
        }
        if (x < 0)
        {
            cout << "0x";
            string hexa = toBase16(x);
            fillbitstring(hexa, 4, -1);
            cout << " = ";
            string res = findTwoscomplement(ConvertFromDecimal(abs(x), 2));
            fillbitstring(res, 16, -1);
            return;
        }
    }
}
void Unsigned_Int(long long x)
{
    if (x > 4294967295)
    {
        cout << "The maximum range of Unsigned Int is 4294967295\n";
    }
    if (x < 0)
    {
        cout << "The Unsigned Int must be >= 0 \n";
    }
    else
    {
        cout << "0x";
        string hexa = toBase16(x);
        fillbitstring(hexa, 8, 1);
        cout << " = ";
        string res = ConvertFromDecimal(x, 2);
        fillbitstring(res, 32, 1);
    }
}
void Signed_Int(long long x)
{
    if (x > 2147483647)
    {
        cout << "The maximum range of Signed Int is 2147483647\n";
    }
    if (x < -2147483648)
    {
        cout << "The minimum range of Signed Int is -2147483648\n";
    }
    else
    {
        if (x > 0)
        {
            cout << "0x";
            string hexa = toBase16(x);
            fillbitstring(hexa, 8, 1);
            cout << " = ";
            string res = ConvertFromDecimal(x, 2);
            fillbitstring(res, 32, 1);
            return;
        }
        if (x < 0)
        {
            cout << "0x";
            string hexa = toBase16(x);
            fillbitstring(hexa, 8, -1);
            cout << " = ";
            string res = findTwoscomplement(ConvertFromDecimal(abs(x), 2));
            fillbitstring(res, 32, -1);
            return;
        }
    }
}

// FLOAT - DOUBLE TO BIT
int countBit_NeedMode_f(float input)
{
    string bit = ConvertFromDecimal(input, 2);
    int count = 0;
    for (int i = 0; i < bit.length(); i++)
    {
        count++;
    }
    return (24 - count);
}
int countBit_NeedMode_d(double input)
{
    string bit = ConvertFromDecimal(input, 2);
    int count = 0;
    for (int i = 0; i < bit.length(); i++)
    {
        count++;
    }
    return (53 - count);
}
long long multiplyy_d(float input)
{
    int more = countBit_NeedMode_d((int)input);
    return (input * pow(2, more));
}
long long multiplyy_f(float input)
{
    int more = countBit_NeedMode_f((int)input);
    return (input * pow(2, more));
}
char *add_pointBin(long long input)
{
    string f = ConvertFromDecimal(input, 2);

    char *res = new char[f.length() + 2];
    res[f.length() + 1] = '\0';

    strcpy(res, f.c_str());
    for (int i = strlen(res); i > 1; i--)
    {
        res[i] = res[i - 1];
    }
    res[1] = '.';

    return res;
}
int count_Exponent_afterPoint(char *res)
{
    int count = 0;
    for (int i = 2; i < strlen(res); i++)
    {
        if (res[i] != '.')
            count++;
    }
    return count;
}
int count_E_value(int exponent, int needMorebit)
{
    return (exponent - needMorebit);
}
void export_bin_d(double input, char *E_arr, char *man) // sua lai 1 ti o vong for roi nha
{
    char *print = new char[1 + strlen(E_arr) + strlen(man) + 1];

    if (input > 0)
        print[0] = '0';
    else
        print[0] = '1';

    for (int i = 0; i < 11; i++)
    {
        print[i + 1] = E_arr[i];
    }
    for (int i = 2; i < strlen(man); i++)
    {
        print[i + 10] = man[i];
    }
    print[1 + strlen(E_arr) + strlen(man)] = '\0';
    for (int i = 0; i < strlen(print); i++)
    {
        if (print[i] == '0' || print[i] == '1' || print[i] == '/')
        {
            if (print[i] == '/')
            {
                print[i] = '1';
            }
            cout << print[i];
        }
    }
    cout << "\n";
}
void export_bin_f(float input, char *E_arr, char *man)
{
    char *print = new char[1 + strlen(E_arr) + strlen(man) + 1];

    if (input > 0)
        print[0] = '0';
    else
        print[0] = '1';

    for (int i = 0; i < 8; i++)
    {
        print[i + 1] = E_arr[i];
    }
    for (int i = 2; i < strlen(man); i++)
    {
        print[i + 7] = man[i];
    }
    print[1 + strlen(E_arr) + strlen(man)] = '\0';

    for (int i = 0; i < strlen(print); i++)
    {
        if (print[i] == '0' || print[i] == '1' || print[i] == '/')
        {
            if (print[i] == '/')
            {
                print[i] = '1';
            }
            cout << print[i];
        }
    }
    cout << "\n";
}
// INTRO - MENU FUNCTIONS
void INTRO(int &key)
{
    char board = 'w';
    while (board != ' ')
    {
        gotoxy(30, 0);
        cout << "===================== WELCOME TO ======================= ";
        gotoxy(35, 2);
        cout << R"(
                       ___     ___    _  _   __   __   ___     ___    _____    ___     ___   
                      / __|   / _ \  | \| |  \ \ / /  | __|   | _ \  |_   _|  | __|   | _ \  
                     | (__   | (_) | | .` |   \ V /   | _|    |   /    | |    | _|    |   /  
                      \___|   \___/  |_|\_|   _\_/_   |___|   |_|_\   _|_|_   |___|   |_|_\  
                    _|"""""|_|"""""|_|"""""|_| """"|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""| 
                    "`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-' 
        )"
             << "\n";
        gotoxy(35, 15);
        cout << "  =========================================  ";
        if (board == 'w' || board == 72)
        {
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 14);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
            key = 1;
        }
        gotoxy(35, 16);
        cout << "||                                         ||";
        gotoxy(35, 17);
        cout << "||                 START                   ||";
        gotoxy(35, 18);
        cout << "||                                         ||";
        gotoxy(35, 19);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 21);
        cout << "  =========================================  ";

        if (board == 's' || board == 80)
        {
            key = 2;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 20);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
        }
        gotoxy(35, 22);
        cout << "||                                         ||";
        gotoxy(35, 23);
        cout << "||                  END                    ||";
        gotoxy(35, 24);
        cout << "||                                         ||";
        gotoxy(35, 25);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";
        board = _getch();
    }
    system("cls");
}
void INTRO_NEXT(int &key)
{
    key = 1;
    char board = 'w';
    while (board != ' ' || board != 48)
    {
        gotoxy(35, 0);
        cout << "================== MENU GAME =================\n";
        gotoxy(35, 3);
        cout << "  =========================================  ";
        if ((board == 'w' && key == 0) || (board == 72 && key == 0))
        {
            key = 8;
        }
        else
        {
            if (board == 'w' || board == 72)
                key--;
            if (board == 's' || board == 80)
                key++;
        }
        if (key == 1 || key % 9 == 1 || key == -8 || key == -17)
        {
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 6);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
            // key = 1;
        }
        gotoxy(35, 4);
        cout << "||                                         ||";
        gotoxy(35, 5);
        cout << "||             UNSIGNED_CHAR               ||";
        gotoxy(35, 6);
        cout << "||                                         ||";
        gotoxy(35, 7);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 9);
        cout << "  =========================================  ";

        if (key == 2 || key % 9 == 2 || key == -7 || key == -16)
        {
            // key = 2;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 8);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
        }
        gotoxy(35, 10);
        cout << "||                                         ||";
        gotoxy(35, 11);
        cout << "||              SIGNED_CHAR                ||";
        gotoxy(35, 12);
        cout << "||                                         ||";
        gotoxy(35, 13);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 15);
        cout << "  =========================================  ";
        if (key == 3 || key % 9 == 3 || key == -6 || key == -15)
        {
            // key = 3;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 14);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
        }
        gotoxy(35, 16);
        cout << "||                                         ||";
        gotoxy(35, 17);
        cout << "||             UNSIGNED_SHORT              ||";
        gotoxy(35, 18);
        cout << "||                                         ||";
        gotoxy(35, 19);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";
        gotoxy(35, 21);
        cout << "  =========================================  ";
        if (key == 4 || key % 9 == 4 || key == -5 || key == -14)
        {
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 20);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
            // key = 1;
        }

        gotoxy(35, 22);
        cout << "||                                         ||";
        gotoxy(35, 23);
        cout << "||              SIGNED_SHORT               ||";
        gotoxy(35, 24);
        cout << "||                                         ||";
        gotoxy(35, 25);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 27);
        cout << "  =========================================  ";

        if (key == 5 || key % 9 == 5 || key == -4 || key == -13)
        {
            // key = 2;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 26);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
        }
        gotoxy(35, 28);
        cout << "||                                         ||";
        gotoxy(35, 29);
        cout << "||              UNSIGNED_INT               ||";
        gotoxy(35, 30);
        cout << "||                                         ||";
        gotoxy(35, 31);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 33);
        cout << "  =========================================  ";
        if (key == 6 || key % 9 == 6 || key == -3 || key == -12)
        {
            // key = 3;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 32);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
        }
        gotoxy(35, 34);
        cout << "||                                         ||";
        gotoxy(35, 35);
        cout << "||                SIGNED_INT               ||";
        gotoxy(35, 36);
        cout << "||                                         ||";
        gotoxy(35, 37);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 39);
        cout << "  =========================================  ";
        if (key == 7 || key % 9 == 7 || key == -2 || key == -11)
        {
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 38);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
            // key = 1;
        }
        gotoxy(35, 40);
        cout << "||                                         ||";
        gotoxy(35, 41);
        cout << "||                 FLOAT                   ||";
        gotoxy(35, 42);
        cout << "||                                         ||";
        gotoxy(35, 43);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 45);
        cout << "  =========================================  ";

        if (key == 8 || key % 9 == 8 || key == -1 || key == -10)
        {
            // key = 2;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 44);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
        }
        gotoxy(35, 46);
        cout << "||                                         ||";
        gotoxy(35, 47);
        cout << "||                  DOUBLE                 ||";
        gotoxy(35, 48);
        cout << "||                                         ||";
        gotoxy(35, 49);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 51);
        cout << "  =========================================  ";
        if (key == 9 || key % 9 == 0 || key == -9)
        {
            // key = 3;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 50);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
        }
        gotoxy(35, 52);
        cout << "||                                         ||";
        gotoxy(35, 53);
        cout << "||                 QUIT                    ||";
        gotoxy(35, 54);
        cout << "||                                         ||";
        gotoxy(35, 55);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";
        board = _getch();
        if (board == ' ' || board == 32)
            return;
    }
    system("cls");
}
void OPTION(int &BintoDec)
{
    BintoDec = 1;
    char board = '0';
    while (board != ' ')
    {
        gotoxy(35, 0);
        cout << "================== CONVERT OPTION =================\n";
        gotoxy(35, 5);
        cout << "  =========================================  ";
        if (board == 'w' || board == 72)
            BintoDec--;
        if (board == 's' || board == 80)
            BintoDec++;

        if (BintoDec == 1 || BintoDec % 3 == 1)
        {
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 6);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
            // key = 1;
        }
        gotoxy(35, 6);
        cout << "||                                         ||";
        gotoxy(35, 7);
        cout << "||           BINARY TO DECIMAL             ||";
        gotoxy(35, 8);
        cout << "||                                         ||";
        gotoxy(35, 9);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 11);
        cout << "  =========================================  ";

        if (BintoDec == 2 || BintoDec % 3 == 2)
        {
            // key = 2;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 12);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
        }
        gotoxy(35, 12);
        cout << "||                                         ||";
        gotoxy(35, 13);
        cout << "||           DECIMAL TO BINARY             ||";
        gotoxy(35, 14);
        cout << "||                                         ||";
        gotoxy(35, 15);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 17);
        cout << "  =========================================  ";
        if (BintoDec == 3 || BintoDec % 3 == 0)
        {
            // key = 3;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 16);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
            }
        }
        gotoxy(35, 18);
        cout << "||                                         ||";
        gotoxy(35, 19);
        cout << "||              QUIT TO MENU               ||";
        gotoxy(35, 20);
        cout << "||                                         ||";
        gotoxy(35, 21);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";
        board = _getch();
    }
    system("cls");
}
void ConvertAgain(int &Again)
{
    cout << "\n Press 1 or 2:\n";
    cout << "1. Continue \n2. Change type convert\n";
    cout << "Your selection: ";
    cin >> Again;
    while (Again != 2 && Again != 1)
    {
        cout << "You choose wrong, pls choose again \n";
        cin >> Again;
    }
}

int main()
{
    int key = 0;
    int menu = 0;
    INTRO(key);
    while (key == 1)
    {
        system("cls");
        INTRO_NEXT(menu);
        system("cls");
        menu = abs(menu);
        while (menu == 1)
        {
            int BinToDec = 0;
            OPTION(BinToDec);
            while (BinToDec == 1)
            {
                BitToDecimal(8, 0);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            while (BinToDec == 2)
            {
                cout << "\t\t UNSIGNED - CHAR ";
                long long x;
                cout << "\nInput the number in decimal base: ";
                cin >> x;
                cout << "The binary bits sequence: ";
                Unsigned_Char(x);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            if (BinToDec == 3)
            {
                menu = -1;
            }
        }
        while (menu == 2)
        {
            int BinToDec = 0;
            OPTION(BinToDec);
            while (BinToDec == 1)
            {
                BitToDecimal(8, 1);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            while (BinToDec == 2)
            {
                cout << "\t\t SIGNED - CHAR ";
                long long x;
                cout << "\nInput the number in decimal base: ";
                cin >> x;
                cout << "The binary bits sequence: ";
                Signed_Char(x);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            if (BinToDec == 3)
            {
                menu = -1;
            }
        }
        while (menu == 3)
        {
            int BinToDec = 0;
            OPTION(BinToDec);
            while (BinToDec == 1)
            {
                BitToDecimal(16, 0);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            while (BinToDec == 2)
            {
                cout << "\t\t UNSIGNED - SHORT ";
                long long x;
                cout << "\nInput the number in decimal base: ";
                cin >> x;
                cout << "The binary bits sequence: ";
                Unsigned_Short(x);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            if (BinToDec == 3)
            {
                menu = -1;
            }
        }
        while (menu == 4)
        {
            int BinToDec = 0;
            OPTION(BinToDec);
            while (BinToDec == 1)
            {
                BitToDecimal(16, 0);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            while (BinToDec == 2)
            {
                cout << "\t\t SIGNED - SHORT ";
                long long x;
                cout << "\nInput the number in decimal base: ";
                cin >> x;
                cout << "The binary bits sequence: ";
                Signed_Short(x);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            if (BinToDec == 3)
            {
                menu = -1;
            }
        }
        while (menu == 5)
        {
            int BinToDec = 0;
            OPTION(BinToDec);
            while (BinToDec == 1)
            {
                BitToDecimal(32, 0);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            while (BinToDec == 2)
            {
                cout << "\t\t UNSIGNED - INT ";
                long long x;
                cout << "\nInput the number in decimal base: ";
                cin >> x;
                cout << "The binary bits sequence: ";
                Unsigned_Int(x);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            if (BinToDec == 3)
            {
                menu = -1;
            }
        }
        while (menu == 6)
        {
            int BinToDec = 0;
            OPTION(BinToDec);
            while (BinToDec == 1)
            {
                BitToDecimal(32, 0);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            while (BinToDec == 2)
            {
                cout << "\t\t SIGNED - INT ";
                long long x;
                cout << "\nInput the number in decimal base: ";
                cin >> x;
                cout << "The binary bits sequence: ";
                Signed_Int(x);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            if (BinToDec == 3)
            {
                menu = -1;
            }
        }
        while (menu == 7)
        {
            int BinToDec = 0;
            OPTION(BinToDec);
            while (BinToDec == 1)
            {
                char tmp[100];
                cout << "Input bit sequence of float type:";
                cin >> tmp;
                cout << BinTo_FloatPoint(tmp) << endl;
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            while (BinToDec == 2)
            {
                float input;
                cout << "\t\t FLOAT ";
                cout << "\nInput the floating point number: ";
                cin >> input;
                int need = countBit_NeedMode_f(input);
                int xpn = count_Exponent_afterPoint(add_pointBin(multiplyy_f(input)));
                char *mantissa = add_pointBin(multiplyy_f(input));
                string bit_of_EVal = ConvertFromDecimal(count_E_value(xpn, need) + 127, 2);
                char *E_bits = new char[bit_of_EVal.length() + 1];
                strcpy(E_bits, bit_of_EVal.c_str());
                cout << "The bits sequence of " << input << ":";
                export_bin_f(input, E_bits, mantissa);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            if (BinToDec == 3)
            {
                menu = -1;
            }
        }
        while (menu == 8)
        {
            int BinToDec = 0;
            OPTION(BinToDec);
            while (BinToDec == 1)
            {
                cout << "Input bit sequence of double type:";
                char tmp[100];
                cin >> tmp;
                int count = 0;
                for (int i = 0; i < strlen(tmp); i++)
                {
                    if (tmp[i] == '1' || tmp[i] == '0')
                    {
                        count++;
                    }
                    if (tmp[i] != '1' && tmp[i] != '0')
                    {
                        break;
                    }
                }
                char *res = new char[count + 1];
                for (int i = 0; i < strlen(res); i++)
                {
                    res[i] = tmp[i];
                }
                res[count] = '\0';
                cout << "= " << BinTo_DoublePoint(res) << endl;
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            while (BinToDec == 2)
            {
                double input;
                cout << "\t\t DOUBLE  ";
                cout << "\nInput the double number: ";
                cin >> input;
                int need = countBit_NeedMode_d(input);
                int xpn = count_Exponent_afterPoint(add_pointBin(multiplyy_d(input)));
                char *mantissa = add_pointBin(multiplyy_d(input));
                string bit_of_EVal = ConvertFromDecimal(count_E_value(xpn, need) + 1023, 2);
                char *E_bits = new char[bit_of_EVal.length() + 1];
                strcpy(E_bits, bit_of_EVal.c_str());
                export_bin_d(input, E_bits, mantissa);
                int choose = 0;
                ConvertAgain(choose);
                if (choose == 2)
                {
                    BinToDec = -1;
                    system("cls");
                }
            }
            if (BinToDec == 3)
            {
                menu = -1;
            }
        }
        if (menu == 0)
        {
            key = 2;
            return 0;
        }
    }

    return 0;
}