#include <conio.h>
#include <vector>
#include <string>
#include "Canvas.h"
#include <iostream>


using namespace std;

int main() {

    // ��������� ��������� ������� �� CP1251
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // ��������� ������ ��� ����������� ����������� �������� ������
    setlocale(LC_ALL, "Russian");

    canvas c; // ������� �����

    while (true)
    {
        int x1{}, y1{}, x2{}, y2{}, colvo{};
        int r{}, g{}, b{}, br{}, bg{}, bb{};
        bool filled;
        string switch_shape;

        cout << "������� �������� ��������� (point, line, ellipse, rectangle, polygon, refresh): ";
        cin >> switch_shape;

        if (switch_shape == "point") {
            cout << "������� ���������� ����� (x, y): ";
            cin >> x1 >> y1;
            cout << "������� ���� (r, g, b): ";
            cin >> r >> g >> b;
            c.add((shape*)new point(x1, y1, RGB(r, g, b))); // ���������� �����
        }
        else if (switch_shape == "line") {
            cout << "������� ���������� ����� (x1, y1, x2, y2): ";
            cin >> x1 >> y1 >> x2 >> y2;
            cout << "������� ���� (r, g, b): ";
            cin >> r >> g >> b;
            c.add((shape*)new line(x1, y1, x2, y2, RGB(r, g, b))); // ���������� �����
        }
        else if (switch_shape == "ellipse") {
            cout << "������� ���������� ����� (x1, y1, x2, y2): ";
            cin >> x1 >> y1 >> x2 >> y2;
            cout << "������� ���� (r, g, b): ";
            cin >> r >> g >> b;
            cout << "����������� ��� ��� (1 ��� 0): ";
            cin >> filled;
            cout << "������� ���� (r, g, b): ";
            cin >> br >> bg >> bb;
            c.add((shape*)new ellipse(x1, y1, x2, y2, RGB(r, g, b), filled, RGB(br, bg, bb))); // ���������� ������
        }
        else if (switch_shape == "rectangle") {
            cout << "������� ���������� ����� (x1, y1, x2, y2): ";
            cin >> x1 >> y1 >> x2 >> y2;
            cout << "������� ���� (r, g, b): ";
            cin >> r >> g >> b;
            cout << "����������� ��� ��� (1 ��� 0): ";
            cin >> filled;
            cout << "������� ���� (r, g, b): ";
            cin >> br >> bg >> bb;
            c.add((shape*)new rectangle(x1, y1, x2, y2, RGB(r, g, b), filled, RGB(br, bg, bb)));
        }
        else if (switch_shape == "polygon") {

            vector <point> coordinates{};
            int input_x, input_y;
            bool finish_input = false;

            cout << "������� ���������� ����� (��� ���������� ������� 1010): ";
            while (!finish_input && cin >> input_x >> input_y) {
                if (input_x == 1010 || input_y == 1010) {
                    finish_input = true;
                }
                else {
                    point p{};
                    p.x = input_x;
                    p.y = input_y;
                    coordinates.push_back(p);
                }
            }

            // ����� ������ ������ ���� ������������ �� �������� ����
            if (!finish_input) {
                cout << "������� ���������� ����� (��� ���������� ������� 1010): ";
            }

            cout << "������� ���� (r, g, b): ";
            cin >> r >> g >> b;
            cout << "����������� ��� ��� (1 ��� 0): ";
            cin >> filled;
            cout << "������� ���� (r, g, b): ";
            cin >> br >> bg >> bb;
            c.add((shape*)new polygon(coordinates, RGB(r, g, b), filled, RGB(br, bg, bb)));
        }
        else if (switch_shape == "refresh") {

        }
        else {
            break;
        }

        c.show();
    }

    int key = _getch();

    return 0;
}