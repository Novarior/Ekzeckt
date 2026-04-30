#include "LSystem.hpp"
#include <cstddef>

bool LSystem::compareByGreen(const sf::RectangleShape &a, const sf::RectangleShape &b)
{
    sf::Color colorA = a.getFillColor();
    sf::Color colorB = b.getFillColor();
    return colorA.g < colorB.g; // Меньший зелёный оттенок будет впереди
}

size_t LSystem::getAxiomSize() { return this->sentence.length(); }

LSystem::LSystem()
{
    this->line.resize(1, sf::RectangleShape(sf::Vector2f(1, 1)));
}

LSystem::~LSystem()
{
    // очистка стека
    while (!this->stack.empty())
        this->stack.pop();
    // очистка вектора
    this->line.clear();
    // очистка правил
    this->rules.clear();
    // очистка строки
    this->sentence.clear();
}

void LSystem::generate()
{
    if (!this->line.empty())
        line.clear();
    this->line.resize(1, sf::RectangleShape(sf::Vector2f(1, 1)));

    this->data.isGeneratorEnable = false;
    this->data.pos = sf::Vector2f(0, 0);
    this->data.angle = 15;
    this->data.currentAngle = 0;
    this->data.width = 15;
    this->data.length = 25;
    this->data.half_length = -this->data.width / 2;
    this->data.steps = 9;
    this->data.alpha = 255;
    this->data.chanceSkip = 50;
    this->data.seed = 0;
    this->axiom = "qqqs";
    this->sentence = axiom;

    this->generateSentence();

    this->applyRules();
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

        this->sentence = nextSentence;
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
    this->data.isGeneratorEnable = true;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    std::uniform_int_distribution<> dis_angle(0, 25);
    std::uniform_int_distribution<> dis_color(80, 220);

    sf::RectangleShape bufferShape;
    this->debug_dots = sf::VertexArray(sf::PrimitiveType::Points, this->sentence.size());
    sf::Vertex p;
    data.nextPos = {0, 0};
    int randcolor = dis_color(gen);

    for (char current : this->sentence)
    {
        // Перебираем каждый символ текущего предложения
        // (строки команды L-системы)
        // Генерируем случайное число для вероятностных операций
        int chance = dis(gen);
        switch (current) // Обрабатываем символ в зависимости от его значения
        {
        case 'd':
        {
            if (chance < this->data.chanceSkip)
                break;
            // Задаём размеры и параметры формы, представляющей элемент ствола
            bufferShape.setSize(sf::Vector2f(this->data.width, this->data.length));
            // Устанавливаем точку вращения в центр
            bufferShape.setOrigin(sf::Vector2f(data.width / 2, data.length));
            bufferShape.setPosition(data.nextPos + data.offsetPos); // Смещаем позицию с учётом оффсета
            // Устанавливаем угол вращения
            bufferShape.setRotation(sf::degrees(data.currentAngle));
            // Устанавливаем цвет (цвет дерева)
            bufferShape.setFillColor(sf::Color(80, 35, 25, this->data.alpha));

            ////DEBUG

            p.position = sf::Vector2f(data.nextPos + data.offsetPos);
            p.color = sf::Color::White;

            debug_dots.append(p);

            // Рассчитываем следующую позицию для элементов ствола
            data.nextPos = this->data.pos + this->rotate(sf::Vector2f(0, -this->data.length), data.currentAngle + dis_angle(gen) * 0.3);
            this->data.pos = data.nextPos; // Обновляем текущую позицию

            this->line.push_back(bufferShape); // Добавляем форму в линию (список элементов дерева)
            break;
        }
        case 'q':
        { // Дерево — элемент ствола (с смещением)
            if (chance < this->data.chanceSkip)
                break; // Пропускаем текущий элемент с заданной вероятностью

            // Задаём размеры и параметры формы, представляющей элемент ствола
            bufferShape.setSize(sf::Vector2f(this->data.width, this->data.length));
            // Устанавливаем точку вращения в центр
            bufferShape.setOrigin(sf::Vector2f(data.width / 2, data.length));
            bufferShape.setPosition(data.nextPos + data.offsetPos);                          // Смещаем позицию с учётом оффсета
            bufferShape.setRotation(sf::degrees(data.currentAngle + dis_angle(gen) * 0.15)); // Устанавливаем угол вращения
            bufferShape.setFillColor(sf::Color(80, 35, 25, this->data.alpha));               // Устанавливаем цвет (цвет дерева)

            ////DEBUG
            p.position = sf::Vector2f(data.nextPos + data.offsetPos);
            p.color = sf::Color::White;
            debug_dots.append(p);

            // Рассчитываем следующую позицию для элементов ствола
            data.nextPos = this->data.pos + this->rotate(sf::Vector2f(0, -this->data.length), data.currentAngle + dis_angle(gen) * 0.3);
            this->data.pos = data.nextPos;     // Обновляем текущую позицию
            this->line.push_back(bufferShape); // Добавляем форму в линию (список элементов дерева)
            break;
        }
        case 's':
        { // Дерево — элемент листвы
            // Рассчитываем следующую позицию для элемента листвы

            // Настраиваем параметры формы для листвы
            bufferShape.setSize(sf::Vector2f(this->data.length + dis_angle(gen) % 3 + 1, this->data.width * 2.25)); // Генерируем случайный размер листа
            bufferShape.setOrigin(sf::Vector2f(data.width / 2, data.length));                                       // Устанавливаем точку вращения
            bufferShape.setPosition(this->data.pos + data.offsetPos);                                               // Смещаем позицию с учётом
            bufferShape.setRotation(sf::degrees(this->data.currentAngle + dis_angle(gen)));                         // Устанавливаем угол вращения

            // Генерируем случайный оттенок зелёного цвета для листвы
            randcolor = dis_color(gen);
            bufferShape.setFillColor(sf::Color(0, randcolor, 0));
            this->line.push_back(bufferShape); // Добавляем форму в линию
            data.nextPos = this->data.pos + this->rotate(sf::Vector2f(0, -this->data.width), this->data.currentAngle + dis_angle(gen) * 0.5);
            this->data.pos = data.nextPos; // Обновляем текущую позицию
            break;
        }
        case '|':
        {
            // Настраиваем параметры формы для листвы
            bufferShape.setSize(sf::Vector2f(this->data.length + dis_angle(gen) % 3 + 1, this->data.width * 2.25)); // Генерируем случайный размер листа
            bufferShape.setOrigin(sf::Vector2f(data.width / 2, data.length));                                       // Устанавливаем точку вращения
            bufferShape.setPosition(this->data.pos + data.offsetPos);                                               // Смещаем позицию с учётом

            bufferShape.setRotation(
                sf::degrees(this->data.currentAngle +
                            dis_angle(gen))); // Устанавливаем угол вращения

            // Генерируем случайный оттенок зелёного цвета для листвы
            randcolor = dis_color(gen);
            bufferShape.setFillColor(sf::Color(0, randcolor, 0));

            this->line.push_back(bufferShape); // Добавляем форму в линию
            data.nextPos = this->data.pos + this->rotate(sf::Vector2f(0, -this->data.width), this->data.currentAngle + dis_angle(gen) * 0.5);
            this->data.pos = data.nextPos; // Обновляем текущую позицию}
            break;
        }
        case '+': // Вращение направо
            this->data.currentAngle += 25 + dis_angle(gen);
            break;
        case '-': // Вращение налево
            this->data.currentAngle -= 25 + dis_angle(gen);
            break;
        case '[': // Сохраняем текущее состояние в стек
            if (data.length > 2.f)
                this->data.length *= 0.85; // Уменьшаем длину элементов
            if (data.width > 1.f)
                this->data.width *= 0.75;
            this->data.alpha *= 0.9; // Уменьшаем прозрачность
            // this->data.half_length = -this->data.width / 2;
            this->stack.push(this->data); // Сохраняем состояние
            break;
        case ']':                           // Восстанавливаем состояние из стека
            this->data = this->stack.top(); // Восстанавливаем данные
            this->stack.pop();              // Удаляем верхний элемент стека
            break;
        default:
            break;
        };
    }

    std::sort(this->line.begin(), this->line.end(), this->compareByGreen);
    this->data.isGeneratorEnable = false;
}

void LSystem::update(const float &delta_time)
{
    // this->line[1].rotate(sf::radians(delta_time));
}

void LSystem::render(sf::RenderTarget &target)
{ // render shapes
    if (!this->data.isGeneratorEnable)
        for (auto &shape : this->line)
            target.draw(shape);

    // target.draw(debug_dots);
}