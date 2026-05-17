//#ifndef CPP_MATH_LSYSTEM_HPP
//#define CPP_MATH_LSYSTEM_HPP
//#include "mymath.hpp"
//
//struct GData
//{
//    bool isGeneratorEnable;
//    unsigned int seed;
//    unsigned int steps;
//    float angle;
//    float currentAngle;
//    unsigned chanceSkip;
//    float length;
//    float width;
//    float half_length;
//    std::uint8_t alpha;
//    sf::Vector2f offsetPos;
//    sf::Vector2f pos;
//    sf::Vector2f nextPos;
//};
//// l-system tree pifagor
//// variables "s" and "d" mean "stop" and "Draw" respectively
//// constants: "[" and "]" mean "save position and angle on stack" and "restore
//// position and angle from stack" respectively constants: "+" and "-" mean "turn
//// left" and "turn right" respectively
////  axiom: s
//// charset: s, d, q, [, ], +, -
//// rules:
//// d -> d[+d][-d]
//// s -> d[+s][-s]s
//
//class LSystem
//{
//private:
//    GData data;
//    std::string axiom;
//    std::string sentence;
//    std::map<char, std::string> rules;
//    std::stack<GData> stack;
//    std::vector<sf::RectangleShape> line;
//    sf::VertexArray debug_dots;
//
//    void generateSentence();
//    void applyRules();
//    sf::Vector2f rotate(sf::Vector2f v, float angle);
//
//    static bool compareByGreen(const sf::RectangleShape &a, const sf::RectangleShape &b);
//
//public:
//    LSystem();
//    ~LSystem();
//    // get all sf::RectangleShape on array
//    sf::RectangleShape *internalArray() { return this->line.data(); }
//    size_t getSizeArray() { return this->line.size(); }
//
//    // REWRITING
//    // genetare tree from basic axiom unsing some rules
//    //
//    // see on LSystem::applyRules for more detail
//    void generate();
//    void setAxiom(std::string axiom) { this->axiom = axiom; }
//    void setRules(std::map<char, std::string> rules) { this->rules = rules; }
//    void setRule(char key, std::string value) { this->rules[key] = value; }
//    void setAxiom(char axiom) { this->axiom = axiom; }
//    size_t getAxiomSize();
//    void setOffsetPos(sf::Vector2f offsetPos)
//    {
//        this->data.offsetPos = offsetPos;
//    }
//
//    size_t getSizeTree() { return this->line.size(); }
//
//    void update(const float &delta_time);
//    void render(sf::RenderTarget &target);
//};
//#endif // CPP_MATH_LSYSTEM_HPP