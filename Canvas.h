#pragma once

#include <windows.h>
#include <vector>
#include <conio.h>

class shape {
public:
    virtual void show(HDC hdc) = 0; // ����������� �����, ����������� ������������ ����� show ����������� ������
    virtual ~shape() {} // ����������� ���������� ��� ����������� �������� ����� ��������� �� ������� �����
}; // ������� ����� ��� �����

// ����� �����
class point : public shape {
public:
    int x, y;
    COLORREF color;
    point(int x = 0, int y = 0, COLORREF c = RGB(255, 255, 255)) : x(x), y(y), color(c) {}
    void show(HDC hdc) override;
};

// ����� �����
class line : public shape {
    point first, second;
    COLORREF color;

public:
    line(int x1, int y1, int x2, int y2, COLORREF c = RGB(255, 255, 255)) : first(x1, y1), second(x2, y2), color(c) {}
    void show(HDC hdc) override;
};

// ����� �������������
class polygon : public shape {
    std::vector<point> points;
    COLORREF color;
    COLORREF background_color;
    bool filled;

public:
    polygon(std::vector<point> pts, COLORREF c, bool filled = false, COLORREF bc = 0) : points(pts), color(c), background_color(bc), filled(filled) {}
    void show(HDC hdc) override;
};

// ����� ������
class ellipse : public shape {
    int left, top, right, bottom;
    COLORREF color;
    COLORREF background_color;
    bool filled;

public:
    ellipse(int left, int top, int right, int bottom, COLORREF c, bool filled = false, COLORREF bc = 0) : left(left), top(top), right(right), bottom(bottom), color(c), background_color(bc), filled(filled) {}
    void show(HDC hdc) override;
};

// ����� �������������, ������������ ����� �����
class rectangle : public shape {
    point top_left;
    point bottom_right;
    COLORREF color;
    COLORREF background_color;
    bool filled;

public:
    rectangle(int x1, int y1, int x2, int y2, COLORREF c, bool filled = false, COLORREF bc = 0) : top_left(x1, y1), bottom_right(x2, y2), color(c), background_color(bc), filled(filled) {}
    void show(HDC hdc) override;
};

class canvas
{
    std::vector<shape*> figures; // ������ ��� �������� �����
    HWND hWnd;
    HDC hdc;
public:
    canvas();
    ~canvas();
    void add(shape* s);
    void del(int i);
    void clear(); // ������� ������
    void show(); // ����������� ����������� ���������� ������� ������ show()
};
