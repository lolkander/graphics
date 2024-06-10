#include "Canvas.h"

void point::show(HDC hdc) {
    SetPixel(hdc, x, y, color);
}

void line::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN)); // выбор стандартного пера
    SetDCPenColor(hdc, color); // установка цвета контура фигуры
    POINT points[2] = { {first.x, first.y}, {second.x, second.y} };
    Polyline(hdc, points, 2);
}

void polygon::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN)); // выбор стандартного пера
    SetDCPenColor(hdc, color); // установка цвета контура фигуры
    SetDCBrushColor(hdc, background_color); // установка цвета закраски
    std::vector<POINT> winPoints;
    for (const auto& pt : points) {
        winPoints.push_back({ pt.x, pt.y });
    }
    if (filled)
    {
        SelectObject(hdc, GetStockObject(DC_BRUSH)); // выбор стандартной кисти
    }
    else
    {
        SelectObject(hdc, GetStockObject(NULL_BRUSH)); // отключение закраски
    }
    Polygon(hdc, winPoints.data(), winPoints.size());
}

void ellipse::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN)); // выбор стандартного пера
    SetDCPenColor(hdc, color); // установка цвета контура фигуры
    SetDCBrushColor(hdc, background_color); // установка цвета закраски
    if (filled)
    {
        SelectObject(hdc, GetStockObject(DC_BRUSH)); // выбор стандартной кисти
    }
    else
    {
        SelectObject(hdc, GetStockObject(NULL_BRUSH)); // отключение закраски
    }
    Ellipse(hdc, left, top, right, bottom);
}

void rectangle::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN)); // выбор стандартного пера
    SetDCPenColor(hdc, color); // установка цвета контура фигуры
    SetDCBrushColor(hdc, background_color); // установка цвета закраски
    if (filled)
    {
        SelectObject(hdc, GetStockObject(DC_BRUSH)); // выбор стандартной кисти
    }
    else
    {
        SelectObject(hdc, GetStockObject(NULL_BRUSH)); // отключение закраски
    }
    Rectangle(hdc, top_left.x, top_left.y, bottom_right.x, bottom_right.y);
}

canvas::canvas()
{
    hWnd = GetConsoleWindow(); // ссылка на окно
    hdc = GetDC(hWnd);		// ссылка на контекст устройства графического вывода
}

canvas::~canvas()
{
    ReleaseDC(hWnd, hdc);		// освобождение контекста устройства вывода
}

void canvas::add(shape* s)
{
    figures.push_back(s);
}

void canvas::del(int i)
{
    figures.erase(figures.begin() + i);
}

void canvas::clear() //очистка холста
{
    figures.clear();
}

void canvas::show() { // отображение графических примитивов вызовом метода show()
    for (size_t i = 0; i < figures.size(); i++)
        figures[i]->show(hdc);
}
