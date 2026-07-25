#include "LSystem.hpp"
#include <cstddef>

bool LSystem::compareByGreen(const sf::RectangleShape &a, const sf::RectangleShape &b)
{
    sf::Color colorA = a.getFillColor();
    sf::Color colorB = b.getFillColor();
    return colorA.g < colorB.g; // Меньший зелёный оттенок будет впереди
}

size_t LSystem::getAxiomSize() { return  sentence.length(); }

LSystem::LSystem()
{
     line.resize(1, sf::RectangleShape(sf::Vector2f(1, 1)));
}

LSystem::~LSystem()
{
    // очистка стека
    while (! stack.empty())
         stack.pop();
    // очистка вектора
     line.clear();
    // очистка правил
     rules.clear();
    // очистка строки
     sentence.clear();
}

void LSystem::generate()
{
    if (! line.empty())
        line.clear();
     line.resize(1, sf::RectangleShape(sf::Vector2f(1, 1)));

     data.isGeneratorEnable = false;
     data.pos = sf::Vector2f(0, 0);
     data.angle = 15;
     data.currentAngle = 0;
     data.width = 15;
     data.length = 25;
     data.half_length = - data.width / 2;
     data.steps = 9;
     data.alpha = 255;
     data.chanceSkip = 50;
     data.seed = 0;
     axiom = "qqqs";
     sentence = axiom;

     generateSentence();

     applyRules();
}

void LSystem::generateSentence()
{
    for (int i = 0; i < data.steps; ++i)
    {
        std::string nextSentence;

        for (char c : sentence)
            if (rules.find(c) != rules.end())
                nextSentence += rules[c]; // Применяем правило
            else
                nextSentence += c; // Оставляем символ без изменений

         sentence = nextSentence;
    }
}

sf::Vector2f LSystem::rotate(sf::Vector2f v, float angle)
{
    float rad = angle * M_PI / 180;
    float x = v.x * cos(rad) - v.y * sin(rad);
    float y = v.x * sin(rad) + v.y * cos(rad);
    return sf::Vector2f(x, y);
}

void LSystem::applyRules()
{
     data.isGeneratorEnable = true;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    std::uniform_int_distribution<> dis_angle(0, 25);
    std::uniform_int_distribution<> dis_color(80, 220);

    sf::RectangleShape bufferShape;
     debug_dots = sf::VertexArray(sf::PrimitiveType::Points,  sentence.size());
    sf::Vertex p;
    data.nextPos = {0, 0};
    int randcolor = dis_color(gen);

    for (char current :  sentence)
    {
        // Перебираем каждый символ текущего предложения
        // (строки команды L-системы)
        // Генерируем случайное число для вероятностных операций
        int chance = dis(gen);
        switch (current) // Обрабатываем символ в зависимости от его значения
        {
        case 'd':
        {
            if (chance <  data.chanceSkip)
                break;
            // Задаём размеры и параметры формы, представляющей элемент ствола
            bufferShape.setSize(sf::Vector2f( data.width,  data.length));
            // Устанавливаем точку вращения в центр
            bufferShape.setOrigin(sf::Vector2f(data.width / 2, data.length));
            bufferShape.setPosition(data.nextPos + data.offsetPos); // Смещаем позицию с учётом оффсета
            // Устанавливаем угол вращения
            bufferShape.setRotation(sf::degrees(data.currentAngle));
            // Устанавливаем цвет (цвет дерева)
            bufferShape.setFillColor(sf::Color(80, 35, 25,  data.alpha));

            ////DEBUG

            p.position = sf::Vector2f(data.nextPos + data.offsetPos);
            p.color = sf::Color::White;

            debug_dots.append(p);

            // Рассчитываем следующую позицию для элементов ствола
            data.nextPos =  data.pos +  rotate(sf::Vector2f(0, - data.length), data.currentAngle + dis_angle(gen) * 0.3);
             data.pos = data.nextPos; // Обновляем текущую позицию

             line.push_back(bufferShape); // Добавляем форму в линию (список элементов дерева)
            break;
        }
        case 'q':
        { // Дерево — элемент ствола (с смещением)
            if (chance <  data.chanceSkip)
                break; // Пропускаем текущий элемент с заданной вероятностью

            // Задаём размеры и параметры формы, представляющей элемент ствола
            bufferShape.setSize(sf::Vector2f( data.width,  data.length));
            // Устанавливаем точку вращения в центр
            bufferShape.setOrigin(sf::Vector2f(data.width / 2, data.length));
            bufferShape.setPosition(data.nextPos + data.offsetPos);                          // Смещаем позицию с учётом оффсета
            bufferShape.setRotation(sf::degrees(data.currentAngle + dis_angle(gen) * 0.15)); // Устанавливаем угол вращения
            bufferShape.setFillColor(sf::Color(80, 35, 25,  data.alpha));               // Устанавливаем цвет (цвет дерева)

            ////DEBUG
            p.position = sf::Vector2f(data.nextPos + data.offsetPos);
            p.color = sf::Color::White;
            debug_dots.append(p);

            // Рассчитываем следующую позицию для элементов ствола
            data.nextPos =  data.pos +  rotate(sf::Vector2f(0, - data.length), data.currentAngle + dis_angle(gen) * 0.3);
             data.pos = data.nextPos;     // Обновляем текущую позицию
             line.push_back(bufferShape); // Добавляем форму в линию (список элементов дерева)
            break;
        }
        case 's':
        { // Дерево — элемент листвы
            // Рассчитываем следующую позицию для элемента листвы

            // Настраиваем параметры формы для листвы
            bufferShape.setSize(sf::Vector2f( data.length + dis_angle(gen) % 3 + 1,  data.width * 2.25)); // Генерируем случайный размер листа
            bufferShape.setOrigin(sf::Vector2f(data.width / 2, data.length));                                       // Устанавливаем точку вращения
            bufferShape.setPosition( data.pos + data.offsetPos);                                               // Смещаем позицию с учётом
            bufferShape.setRotation(sf::degrees( data.currentAngle + dis_angle(gen)));                         // Устанавливаем угол вращения

            // Генерируем случайный оттенок зелёного цвета для листвы
            randcolor = dis_color(gen);
            bufferShape.setFillColor(sf::Color(0, randcolor, 0));
             line.push_back(bufferShape); // Добавляем форму в линию
            data.nextPos =  data.pos +  rotate(sf::Vector2f(0, - data.width),  data.currentAngle + dis_angle(gen) * 0.5);
             data.pos = data.nextPos; // Обновляем текущую позицию
            break;
        }
        case '|':
        {
            // Настраиваем параметры формы для листвы
            bufferShape.setSize(sf::Vector2f( data.length + dis_angle(gen) % 3 + 1,  data.width * 2.25)); // Генерируем случайный размер листа
            bufferShape.setOrigin(sf::Vector2f(data.width / 2, data.length));                                       // Устанавливаем точку вращения
            bufferShape.setPosition( data.pos + data.offsetPos);                                               // Смещаем позицию с учётом

            bufferShape.setRotation(
                sf::degrees( data.currentAngle +
                            dis_angle(gen))); // Устанавливаем угол вращения

            // Генерируем случайный оттенок зелёного цвета для листвы
            randcolor = dis_color(gen);
            bufferShape.setFillColor(sf::Color(0, randcolor, 0));

             line.push_back(bufferShape); // Добавляем форму в линию
            data.nextPos =  data.pos +  rotate(sf::Vector2f(0, - data.width),  data.currentAngle + dis_angle(gen) * 0.5);
             data.pos = data.nextPos; // Обновляем текущую позицию}
            break;
        }
        case '+': // Вращение направо
             data.currentAngle += 25.f + dis_angle(gen);
            break;
        case '-': // Вращение налево
             data.currentAngle -= 25.f + dis_angle(gen);
            break;
        case '[': // Сохраняем текущее состояние в стек
            if (data.length > 2.f)
                 data.length *= 0.85f; // Уменьшаем длину элементов
            if (data.width > 1.f)
                 data.width *= 0.75f;
            data.alpha *= uint8_t(float(data.alpha) * 0.9f); // Уменьшаем прозрачность
            //  data.half_length = - data.width / 2;
             stack.push( data); // Сохраняем состояние
            break;
        case ']':                           // Восстанавливаем состояние из стека
             data =  stack.top(); // Восстанавливаем данные
             stack.pop();              // Удаляем верхний элемент стека
            break;
        default:
            break;
        };
    }

    std::sort( line.begin(),  line.end(),  compareByGreen);
     data.isGeneratorEnable = false;
}

void LSystem::update(const float &delta_time)
{
    //  line[1].rotate(sf::radians(delta_time));
}

void LSystem::render(sf::RenderTarget &target)
{ // render shapes
    if (! data.isGeneratorEnable)
        for (auto &shape :  line)
            target.draw(shape);

    // target.draw(debug_dots);
}