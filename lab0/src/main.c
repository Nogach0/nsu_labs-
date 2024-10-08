#include <stdio.h>
#include <stdlib.h>

int ConvertCharToInt(char sym);
void ConvertFloatToBase(double fracPart, int base);

int main() {
    const int kLimitForNum = 14;
    int base1, base2;

    if (scanf("%d%d", &base1, &base2) != 2) {
        return 0;
    }

    if (base1 < 2 || base1 > 16 || base2 < 2 || base2 > 16) {
        printf("bad input");
        return 0;
    }

    char num_char[kLimitForNum + 1];

    if (scanf("%14s",num_char) != 1) {
        return 0;
    }

    double base1_frac = base1;
    int number;
    int flag = 1;
    long long int sum_int = 0;
    double sum_frac = 0;

    for (int i = 0; i < kLimitForNum; i++) {
        if (num_char[i] == '\0') {
            if (num_char[0] == '.' || num_char[i-1] == '.') {
                printf("bad input");
                return 0;
            }
            break;
        }
        else if (num_char[i] == '.') {
            if (flag == 1) {
                flag = 0;
            }
            else {
                printf("bad input");
                return 0;
            }
        }
        else {
            number = ConvertCharToInt(num_char[i]);
            if (number == -1 || number >= base1) {
                printf("bad input");
                return 0;
            }
            if (flag == 1) {
                sum_int *= base1;
                sum_int += number;
            }
            else {
                sum_frac += (double)number / base1_frac;
                base1_frac *= base1;
            }
        }
    }
    if (sum_int == 0) {
        printf("0");
    }

    char int_number[50];
    int counter = 0;
    const int kVariableInAscii = 48;
    const int kVariableAfterTenInAscii = 55;

    while (sum_int != 0) {
        if (sum_int % base2 < 10) {
            int_number[counter] = (char)((sum_int % base2) + kVariableInAscii);
        }
        else {
            int_number[counter] = (char)((sum_int % base2) + kVariableAfterTenInAscii);
        }
        sum_int /= base2;
        counter++;
    }
    for (;counter > 0; counter--) {
        printf("%c", int_number[counter - 1]);
    }

    if (flag == 0 && sum_frac == 0) {
        printf(".0");
    }
    else if(flag == 0) {
        ConvertFloatToBase(sum_frac, base2);
    }
    return EXIT_SUCCESS;
}

int ConvertCharToInt(char sym) {
    int num;
    if (sym >= '0' && sym <= '9') {
        num = (int)sym - '0';
    }
    else if (sym >= 'a' && sym <= 'f') {
        num = (int)sym - 'W';
    }
    else if (sym >= 'A' && sym <= 'F') {
        num = (int)sym - '7';
    }
    else {
        num = -1;
    }
    return num;
}

void ConvertFloatToBase(double fracPart, int base) {
    const int kLimitForFrac = 12;
    const int kVariableInAscii = 48;
    const int kVariableAfterTenInAscii = 55;
    int counter = 0, last_number = 0;
    double fractional = fracPart;
    char frac_number[kLimitForFrac + 1];
    printf(".");
    while (counter < kLimitForFrac) {
        fractional *= base;
        if ((int)fractional < 10) {
            frac_number[counter] = (char)((int)fractional + kVariableInAscii);
        }
        else {
            frac_number[counter] = (char)((int)fractional + kVariableAfterTenInAscii);
        }
        fractional -= (int)fractional;
        if (frac_number[counter] != '0') {
            last_number = counter;
        }
        counter++;
    }
    for (int i = 0; i <= last_number; i++) {
        printf("%c", frac_number[i]);
    }
}
