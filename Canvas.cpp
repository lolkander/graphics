#include "Canvas.h"

void point::show(HDC hdc) {
    SetPixel(hdc, x, y, color);
}

void line::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN)); // ����� ������������ ����
    SetDCPenColor(hdc, color); // ��������� ����� ������� ������
    POINT points[2] = { {first.x, first.y}, {second.x, second.y} };
    Polyline(hdc, points, 2);
}

void polygon::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN)); // ����� ������������ ����
    SetDCPenColor(hdc, color); // ��������� ����� ������� ������
    SetDCBrushColor(hdc, background_color); // ��������� ����� ��������
    std::vector<POINT> winPoints;
    for (const auto& pt : points) {
        winPoints.push_back({ pt.x, pt.y });
    }
    if (filled)
    {
        SelectObject(hdc, GetStockObject(DC_BRUSH)); // ����� ����������� �����
    }
    else
    {
        SelectObject(hdc, GetStockObject(NULL_BRUSH)); // ���������� ��������
    }
    Polygon(hdc, winPoints.data(), winPoints.size());
}

void ellipse::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN)); // ����� ������������ ����
    SetDCPenColor(hdc, color); // ��������� ����� ������� ������
    SetDCBrushColor(hdc, background_color); // ��������� ����� ��������
    if (filled)
    {
        SelectObject(hdc, GetStockObject(DC_BRUSH)); // ����� ����������� �����
    }
    else
    {
        SelectObject(hdc, GetStockObject(NULL_BRUSH)); // ���������� ��������
    }
    Ellipse(hdc, left, top, right, bottom);
}

void rectangle::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN)); // ����� ������������ ����
    SetDCPenColor(hdc, color); // ��������� ����� ������� ������
    SetDCBrushColor(hdc, background_color); // ��������� ����� ��������
    if (filled)
    {
        SelectObject(hdc, GetStockObject(DC_BRUSH)); // ����� ����������� �����
    }
    else
    {
        SelectObject(hdc, GetStockObject(NULL_BRUSH)); // ���������� ��������
    }
    Rectangle(hdc, top_left.x, top_left.y, bottom_right.x, bottom_right.y);
}

canvas::canvas()
{
    hWnd = GetConsoleWindow(); // ������ �� ����
    hdc = GetDC(hWnd);		// ������ �� �������� ���������� ������������ ������
}

canvas::~canvas()
{
    ReleaseDC(hWnd, hdc);		// ������������ ��������� ���������� ������
}

void canvas::add(shape* s)
{
    figures.push_back(s);
}

void canvas::del(int i)
{
    figures.erase(figures.begin() + i);
}

void canvas::clear() //������� ������
{
    figures.clear();
}

void canvas::show() { // ����������� ����������� ���������� ������� ������ show()
    for (size_t i = 0; i < figures.size(); i++)
        figures[i]->show(hdc);
}
