﻿#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;
int main()
{
    
    setlocale(0, "");
    cout << "Введите радиус окружности R: ";
    double R,a,b,X,Y,x,y,x2,y2,d,eps;//X,Y-точка
    cin >> R;
    if (R <= 0)
    {
        cout << "Радиус меньше 0. Завершение программы" << endl;
        system("PAUSE");
        return 0;
    }
    cout << "Введите a из уравнения прямой y = ax + b: ";
    cin >> a;
    cout << "Введите b из уравнения прямой y = ax + b: ";
    cin >> b;
    if (b > 0 && a >= 0)
    {
        cout << "Плоскости нет" << endl;
        system("PAUSE");
        return 0;
    }
    cout << "Введите ширину границы: ";
    cin >> eps;
    x = -400;
    y = a*x+b  ;//1 точка прямой
    x2 = 400;
    y2 = a * x2 + b  ;//2 точка прямой
    d = abs(((x2 - x) * (0 - y) - (0 - x) * (y2 - y)) / sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y)));//расстояние от прямой до центра окр
    bool exsist = 0;
    
    if( ( (b > 0 && a < 0) && (a * R + b <= 0) ) || (b < 0) || (b == 0 && a==0) )
    {
        cout << "Введите X: ";
        cin >> X;
        cout << "Введите Y: ";
        cin >> Y;
        if ((abs(X)<=abs(eps) && X >= 0) || (abs(Y)<=abs(eps) && Y <= 0) || ((a * X + b) <= Y && abs(a * X + b) - abs(Y) <= abs(eps)) || ( (R*R-X*X-Y*Y) >= 0) && (R*R-X*X-Y*Y) <= abs(eps))//попадает на границу
        {
            cout << "Точка на границе" << endl;
            exsist = 1;
        }
        if (X < 0 || Y > 0 || (R*R - Y*Y -X*X) < 0 || Y < a*X+b)//снаружи
        {
            cout << "Точки нет!!" << endl;
            system("PAUSE");
            return 0;
        }
        else
        {
            cout << "Точка существует!!" << endl;
            exsist = 1;
        }
    }
    else
    {
        cout << "Плоскости нет" << endl;
        system("PAUSE");
        return 0;
    }


 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //графическое представление

    if (exsist)
    {
        RenderWindow window(sf::VideoMode(800, 800), "window");
        ContextSettings settings;
        settings.antialiasingLevel = 8.0;
        View view = window.getDefaultView();
        view.setCenter(0, 0);
        view.setSize(2.5 * R, -2.5 * R);
        window.setView(view);
        while (window.isOpen())
        {

            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            window.clear(Color::White);

            CircleShape circle(R);
            circle.setOutlineThickness(0.1);
            circle.setOutlineColor(Color::Black);
            circle.move(-R, -R);
            window.draw(circle);

            sf::VertexArray lineOY(sf::Lines, 2);
            lineOY[0].position = sf::Vector2f(0, 400);
            lineOY[1].position = sf::Vector2f(0, -400);
            lineOY[0].color = sf::Color::Black;
            lineOY[1].color = sf::Color::Green;
            window.draw(lineOY);

            sf::VertexArray lineOX(sf::Lines, 2);
            lineOX[0].position = sf::Vector2f(-400, 0);
            lineOX[1].position = sf::Vector2f(400, 0);
            lineOX[0].color = sf::Color::Magenta;
            lineOX[1].color = sf::Color::Yellow;
            window.draw(lineOX);

            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(x, y);
            line[1].position = sf::Vector2f(x2, y2);
            line[0].color = sf::Color::Red;
            line[1].color = sf::Color::Red;
            window.draw(line);

            CircleShape dot(0.1);
            dot.setFillColor(Color::Cyan);
            dot.move(X-0.1, Y-0.1);
            window.draw(dot);

            window.display();
        }
    }
    system("PAUSE");
    return 0;
}