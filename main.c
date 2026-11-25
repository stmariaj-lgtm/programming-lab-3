// Лабораторна робота 3. Номер у журналі: 20.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <ctype.h>

#ifdef _MSC_VER
#include <conio.h>
#include <io.h>
#include <windows.h>
#endif

// Чи поміститься прямокутна грань у двох можливих орієнтаціях?
static int fits(double x, double y, double width, double height)
{
    return (x <= width && y <= height) || (y <= width && x <= height);
}

// Знак показує, з якого боку від напрямленої прямої AB лежить P.
static double side(double ax, double ay, double bx, double by, double px, double py)
{
    return (bx - ax) * (py - ay) - (by - ay) * (px - ax);
}

static double middle(double a, double b, double c)
{
    if ((a < b && b < c) || (c < b && b < a)) return b;
    if ((b < a && a < c) || (c < a && a < b)) return a;
    return c;
}

int main(void)
{
#ifdef _MSC_VER
    SetConsoleOutputCP(CP_UTF8);
#endif
    // 1 (63). Чи поміститься правильний трикутник зі стороною a у колі радіуса R?
    {
        double r, a;
        printf("1 (63). Введіть радіус кола R і сторону трикутника a: ");
        if (scanf("%lf %lf", &r, &a) != 2) return 1;
        if (r <= 0 || a <= 0) puts("Розміри мають бути додатними.");
        else if (a <= sqrt(3.0) * r) puts("Трикутник поміститься.");
        else puts("Трикутник не поміститься.");
    }

    // 2 (70). Чи є додатною сума хоча б однієї пари з трьох чисел?
    {
        double a, b, c;
        printf("2 (70). Введіть три числа: ");
        if (scanf("%lf %lf %lf", &a, &b, &c) != 3) return 1;
        if (a + b > 0 || a + c > 0 || b + c > 0) puts("Є пара з додатною сумою.");
        else puts("Жодна пара не має додатної суми.");
    }

    // 3 (89). Чи поміститься прямокутник a на b всередині прямокутника c на d
    // за умови, що їхні сторони паралельні або перпендикулярні?
    {
        double a, b, c, d;
        printf("3 (89). Введіть сторони внутрішнього (a b) і зовнішнього (c d) прямокутників: ");
        if (scanf("%lf %lf %lf %lf", &a, &b, &c, &d) != 4) return 1;
        if (a <= 0 || b <= 0 || c <= 0 || d <= 0) puts("Розміри мають бути додатними.");
        else if (fits(a, b, c, d)) puts("Прямокутник поміститься.");
        else puts("Прямокутник не поміститься.");
    }

    // 4 (13). Чи є сума цифр двозначного числа двозначною? Чи більша вона за a?
    {
        int number;
        double a;
        printf("4 (13). Введіть двозначне ціле число і значення a: ");
        if (scanf("%d %lf", &number, &a) != 2) return 1;
        if ((number >= 10 && number <= 99) || (number <= -10 && number >= -99)) {
            if (number < 0) number = -number;
            int sum = number / 10 + number % 10;
            printf("Сума цифр = %d. ", sum);
            if (sum >= 10) puts("Сума двозначна.");
            else puts("Сума однозначна.");
            if (sum > a) puts("Сума більша за a.");
            else puts("Сума не більша за a.");
        } else puts("Потрібне двозначне число.");
    }

    // 5 (74). За вартістю книжок і внесеною сумою вивести подяку, здачу або суму нестачі.
    {
        int price, paid;
        printf("5 (74). Введіть вартість книжок і внесену суму в копійках: ");
        if (scanf("%d %d", &price, &paid) != 2) return 1;
        if (price < 0 || paid < 0) puts("Суми мають бути невід’ємними.");
        else if (paid == price) puts("Дякую!");
        else if (paid > price) printf("Візьміть здачу: %.2f грн\n", (paid - price) / 100.0);
        else printf("Недостатньо грошей. Бракує: %.2f грн\n", (price - paid) / 100.0);
    }

    // 6 (52). За координатами вершин трикутника й точки визначити, чи лежить точка всередині.
    {
        double ax, ay, bx, by, cx, cy, px, py;
        printf("6 (52). Введіть координати Ax Ay Bx By Cx Cy Px Py: ");
        if (scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
                 &ax, &ay, &bx, &by, &cx, &cy, &px, &py) != 8) return 1;
        double ab = side(ax, ay, bx, by, px, py);
        double bc = side(bx, by, cx, cy, px, py);
        double ca = side(cx, cy, ax, ay, px, py);
        if (side(ax, ay, bx, by, cx, cy) == 0) puts("Вершини не утворюють трикутник.");
        else if ((ab > 0 && bc > 0 && ca > 0) || (ab < 0 && bc < 0 && ca < 0))
            puts("Точка всередині.");
        else if ((ab >= 0 && bc >= 0 && ca >= 0) || (ab <= 0 && bc <= 0 && ca <= 0))
            puts("Точка на межі.");
        else puts("Точка зовні.");
    }

    // 7 (66). Чи пройде цегла X на Y на Z через прямокутний отвір A на B?
    // Перевіряємо, чи проходить хоча б одна з трьох граней паралельно сторонам отвору.
    {
        double a, b, x, y, z;
        printf("7 (66). Введіть розміри отвору A B та цегли X Y Z: ");
        if (scanf("%lf %lf %lf %lf %lf", &a, &b, &x, &y, &z) != 5) return 1;
        if (a <= 0 || b <= 0 || x <= 0 || y <= 0 || z <= 0) puts("Розміри мають бути додатними.");
        else if (fits(x, y, a, b) || fits(x, z, a, b) || fits(y, z, a, b))
            puts("Цегла пройде.");
        else puts("Цегла не пройде.");
    }

    // 8 (9). За об’ємами й масами двох тіл визначити, який матеріал має більшу густину.
    {
        double v1, m1, v2, m2;
        printf("8 (9). Введіть об’єм і масу першого тіла, потім об’єм і масу другого: ");
        if (scanf("%lf %lf %lf %lf", &v1, &m1, &v2, &m2) != 4) return 1;
        if (v1 <= 0 || v2 <= 0 || m1 <= 0 || m2 <= 0) puts("Об’єми й маси мають бути додатними.");
        else {
            double density1 = m1 / v1;
            double density2 = m2 / v2;
            printf("Густини: %.4f і %.4f. ", density1, density2);
            if (density1 > density2) puts("Перший матеріал густіший.");
            else if (density2 > density1) puts("Другий матеріал густіший.");
            else puts("Густини однакові.");
        }
    }

    // 9 (113). У кожній трійці різних чисел знайти середнє за величиною число.
    // Обчислити середнє арифметичне двох знайдених чисел.
    {
        double a, b, c, d, e, f;
        printf("9 (113). Введіть дві трійки чисел: a b c та d e f: ");
        if (scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f) != 6) return 1;
        if (a == b || a == c || b == c || d == e || d == f || e == f)
            puts("Числа всередині кожної трійки мають бути різними.");
        else {
            double first = middle(a, b, c);
            double second = middle(d, e, f);
            printf("Середні за величиною: %.4f і %.4f. Середнє арифметичне = %.4f\n",
                   first, second, first / 2.0 + second / 2.0);
        }
    }

    // 10 (45). Виводити лише літери й цифри та підписувати тип кожного символу.
    {
        int ch;
        puts("10 (45). Вводьте латинські літери, цифри або інші символи. Enter завершує введення.");
        // Прибираємо кінець рядка, що залишився після введення чисел.
        while ((ch = getchar()) != '\n' && ch != EOF) { }
        for (;;) {
#ifdef _MSC_VER
            ch = _isatty(_fileno(stdin)) ? _getch() : getchar();
            if (_isatty(_fileno(stdin)) && (ch == 0 || ch == 224)) {
                _getch();
                continue;
            }
#else
            ch = getchar();
#endif
            if (ch == EOF || ch == '\r' || ch == '\n') break;
            if (isalpha((unsigned char)ch)) printf("Літера: %c\n", ch);
            else if (isdigit((unsigned char)ch)) printf("Цифра: %c\n", ch);
        }
    }

    return 0;
}