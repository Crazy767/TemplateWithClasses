#include <iostream>
#include <cmath>
#include "Header.h"
/* �������: �������� ����������� ������, �������� �������, ������,
�������� ����� ������� ����������� ����������.

����: main() ������ ����� ������ �������� �����������, ����� ���� �������, ��� ���������� �� ���� ��������� (��� ������������),
�� ��� ���� ��������� �� �� ����� ������.

! � main() ������� ���� ��������� ��������� ��������� ���������. ������ �������� �������� �� �������, ������������� �
�������� ��� � �������������� �������. ��������� ������ �������� ��������.

�� ������� ������ ��������� 4 �������:
0. ������� ������
1. ������� �������
2. ������� ������ � �������� �������� ���
3. ������� ����� ������� �����������

�� ���� �� ��������� ������� ����� ������� ������.

���������:
0. ��������� ������, ������� ��������������� � ���������:
- ����� ���� (���������� �������, ����������� � ���� �������������� � �������������),
- ����� ����� (��� �������� ���������)
- ����� ����������� (� ������������� ������ ������������ ��� ������� ������� ������������).

1. �������:
- ��������� ������� ���� (�������� ���� 1 ������, �������� ���� 2 ������ � �.�.),
- ������� ����� � �������� ������������ ������,
- ������� ��������� �������� ��� �������������: �������� �� �������������, ������� ������� � �.�.

��������. �� ����� �������� ������� ��������������, ��� ������ ������ �������� �� � ������ �������, � ����� ��.
�� ������ ���� ������ � ����������� � ���� �����. ������� ����� ������ - ������� ����, � �������� ������� (�����, ��������) -
������� ���������������� ������.

������ ���������� ����������:
����� 3 ������:
1) ����� ����� �������� (����� ������ ����) - inputSides
2) ����� ����� ����������� (����� ������ �����������) -inputTriangle

����� ������������ ������������ - enum Type {bySides, byBaseAndHeight, byPointsCoords};

Triange tr1;
tr1.inputTriangle(bySides);

void inputTriangle(Type _type) {
  switch (_type) {
   case bySides:
     int side1, side2, side3;
     inputSides(&side1, &side2, &side3);   // ��� ����� ���� ��������
     Triange temp(side1, side2, side3);    // ��� �������� ����������� � ���������� ������
     this = temp;
     break;
   // ...
  }
}

���

void inputTriangle(Type _type) {
  switch (_type) {
   case bySides:
     int side1, side2, side3;
     inputSides(&side1, &side2, &side3);   // ��� ����� ���� ��������
     this->side1 = side1;                  // ��� ���������� ��� ������������ �����������, ���������� ���������� ������
     this->side2 = side2;
     this->side3 = side3;
     break;
   // ...
  }
}

*/
const enum Type { bySides, byBaseAndHeight, byPointsCoords };

Triangle tr1;
Menu menu;
int main() {
    int user_choosen;
    int AB, BC, AC, h;
    int A[2], B[2], C[2];
    float p, S;
    bool exit_flag = false, back_flag;

    Type _inputType;

    while (!exit_flag) {
        back_flag = false;
        std::cout << "Ways to define a triangle:" << std::endl
            << "1) by three sides," << std::endl
            << "2) by base and height," << std::endl
            << "3) by three points" << std::endl
            << "Input: ";
        std::cin >> user_choosen;

        switch (user_choosen) {
        case 1:
            _inputType = bySides;
            tr1 = menu.inputSide();
            break;
        case 2:
            _inputType = byBaseAndHeight;
            std::cout << "Input base of triangle: ";
            std::cin >> AB;
            std::cout << "Input height of triangle: ";
            std::cin >> h;
            break;
        case 3:
            _inputType = byPointsCoords;
            std::cout << "Input 1st point's coordinates (between space): ";
            std::cin >> A[0] >> A[1];
            std::cout << "Input 2nd point's coordinates (between space): ";
            std::cin >> B[0] >> B[1];
            std::cout << "Input 3rd point's coordinates (between space): ";
            std::cin >> C[0] >> C[1];
            break;
        default:
            std::cout << "Input error: error in input" << std::endl;
        }

        while (!back_flag) {
            std::cout << "Methods: 1) get square," << std::endl
                << "2) get perimeter, " << std::endl
                << "3) get type of triangle," << std::endl
                << "4) compare with another triangle by square," << std::endl
                << "5) back to first menu," << std::endl
                << "0) exit," << std::endl
                << "Input: ";
            std::cin >> user_choosen;

            switch (user_choosen) {
            case 0:
                exit_flag = true;
                break;
            case 1:
                if (_inputType == bySides) {
                    if (AB + BC > AC && AB + AC > BC && AC + BC > AB) {
                        p = (AB + BC + AC) * 0.5;
                        S = sqrt(p * (p - AB) * (p - BC) * (p - AC));
                        std::cout << "Square of triangle: S = " << S << std::endl;
                    }
                    else {
                        std::cout << "Input error: triangle dont exist" << std::endl;
                    }
                }
                else if (_inputType == byBaseAndHeight) {
                    S = AB * h / 2;
                    std::cout << "Square of triangle: S = " << S << std::endl;
                }
                else if (_inputType == byPointsCoords) {
                    S = 0.5 * ((A[0] - C[0]) * (B[1] - C[1]) - (B[0] - C[0]) * (A[1] - C[1]));
                    std::cout << "Square of triangle: S = " << S << std::endl;
                }
                system("pause");
                system("cls");
                break;
            case 2:
                if (_inputType == bySides) {
                    p = AB + BC + AC;
                    std::cout << "Square of triangle: P = " << p << std::endl;
                }
                else if (_inputType == byBaseAndHeight) {
                    std::cout << "Input error: we couldn't find perimeter by your parameters" << std::endl;
                }
                else if (_inputType == byPointsCoords) {
                    AB = sqrt(pow((B[0] - A[0]), 2) + pow((B[1] - A[1]), 2));
                    AC = sqrt(pow((C[0] - A[0]), 2) + pow((C[1] - A[1]), 2));
                    BC = sqrt(pow((C[0] - B[0]), 2) + pow((C[1] - B[1]), 2));
                    p = AB + AC + BC;
                    std::cout << "Square of triangle: P = " << p << std::endl;
                }
                break;
            case 3:
                // your code
                // Types of triangles:
                // equilateral - ��������������,
                // isosceles - ��������������,
                // right triangle - �������������,
                // scalene - ������������.

                if (_inputType == bySides) {
                    if (   (pow(AC, 2) == pow(AB, 2) + pow(BC, 2)) || 
                           (pow(AB, 2) == pow(AC, 2) + pow(BC, 2)) || 
                           (pow(BC, 2) == pow(AB, 2) + pow(AC, 2))     )
                    { std::cout << "Right triangle" << std::endl; }
                    else if (AB == AC != BC || AB == BC != AC || AC == BC != AB)
                    { std::cout << "Isosceles" << std::endl; }
                    else if (AB == AC == BC)
                    { std::cout << "Equilateral" << std::endl; }
                    else { std::cout << "Scalene" << std::endl; }
                }
                else if (_inputType == byBaseAndHeight) {
                    std::cout << "Input error: we couldn't find perimeter by your parameters" << std::endl;
                }
                else if (_inputType == byPointsCoords) {
                    AB = sqrt(pow((B[0] - A[0]), 2) + pow((B[1] - A[1]), 2));
                    AC = sqrt(pow((C[0] - A[0]), 2) + pow((C[1] - A[1]), 2));
                    BC = sqrt(pow((C[0] - B[0]), 2) + pow((C[1] - B[1]), 2));

                    if (   (pow(AC, 2) == pow(AB, 2) + pow(BC, 2)) ||
                           (pow(AB, 2) == pow(AC, 2) + pow(BC, 2)) ||
                           (pow(BC, 2) == pow(AB, 2) + pow(AC, 2))   )
                    {std::cout << "Right triangle" << std::endl;}
                    else if (AB == AC != BC || AB == BC != AC || AC == BC != AB)
                    {std::cout << "Isosceles" << std::endl;}
                    else if (AB == AC == BC)
                    {std::cout << "Equilateral" << std::endl;}
                    else {std::cout << "Scalene" << std::endl;}
                }
                break;
            case 4:
                // your code
                break;
            case 5:
                back_flag = true;
                break;
            default:
                std::cout << "Input error: error in input" << std::endl;
            }

            if (back_flag || exit_flag) {
                system("cls");
                std::cout << "Last parameters: ";
                if (_inputType == bySides) {
                    std::cout << AB << "x" << BC << "x" << AC << std::endl;
                }
                else if (_inputType == byBaseAndHeight) {
                    std::cout << "a = " << AB << ", h = " << h << std::endl;
                }
                else if (_inputType == byPointsCoords) {
                    std::cout << "(" << A[0] << ", " << A[1] << ")" << ", ";
                    std::cout << "(" << B[0] << ", " << B[1] << ")" << ", ";
                    std::cout << "(" << C[0] << ", " << C[1] << ")" << std::endl;
                }
            }
            break;
        }
    }
    system("cls");
    std::cout << "Goodbay!" << std::endl;
}