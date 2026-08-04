#ifndef COINS
#define COINS
#include <iostream>

class Coins {
private:
	friend inline Coins operator+(const Coins& left, const Coins& right);
	friend inline Coins& operator+=(Coins& left, const Coins& right);
	friend inline Coins operator-(const Coins& left, const Coins& right);
	friend inline Coins& operator-=(Coins& left, const Coins& right);
	friend inline bool operator==(const Coins& left, const Coins& right);
	friend inline bool operator!=(const Coins& left, const Coins& right);
	friend inline bool operator<(const Coins& left, const Coins& right);
	friend inline bool operator>(const Coins& left, const Coins& right);
	friend inline bool operator<=(const Coins& left, const Coins& right);
	friend inline bool operator>=(const Coins& left, const Coins& right);
	friend inline std::ostream& operator<<(std::ostream& os, const Coins& coin);
	friend inline std::istream& operator>>(std::istream& is, Coins& coin);

protected:
	int m_gold;
	int m_silver;
	int m_copper;

	// Нормализация монет
	void normalizeCoins(int& higher, int& lower, int conversionRate) {
		if (lower >= conversionRate) {
			higher += lower / conversionRate;
			lower %= conversionRate;
		} else if (lower < 0) {
			higher += (lower / conversionRate) - 1;
			lower = conversionRate + (lower % conversionRate);
		}
	}

public:
	/// @brief Конструктор для Coins
	/// @param gold - золотые монеты
	/// @param silver - серебряные монеты
	/// @param copper - медные монеты
	Coins(const int gold = 0, const int silver = 0, const int copper = 0)
		: m_gold(gold), m_silver(silver), m_copper(copper) {}

	virtual ~Coins() {}

	// Сеттеры
	void set_GoldCoinCount(const int value) { m_gold = value; }
	void set_SilverCoinCount(const int value) { m_silver = value; }
	void set_CopperCoinCount(const int value) { m_copper = value; }

	// Добавление монет
	void add_GoldCoinCount(const int value) { m_gold += value; }
	void add_SilverCoinCount(const int value) { m_silver += value; }
	void add_CopperCoinCount(const int value) { m_copper += value; }

	// Геттеры
	inline int get_GoldCointCount() const { return m_gold; }
	inline int get_SilverCointCount() const { return m_silver; }
	inline int get_CopperCointCount() const { return m_copper; }

	// Обновление монет
	void updateCoins() {
		normalizeCoins(m_silver, m_copper, 100);
		normalizeCoins(m_gold, m_silver, 100);
	}
};

inline Coins operator+(const Coins& left, const Coins& right) {
	Coins result(left.m_gold + right.m_gold, left.m_silver + right.m_silver, left.m_copper + right.m_copper);
	result.updateCoins(); // Нормализация монет
	return result;
}

// Plus equal operator for Coins
inline Coins& operator+=(Coins& left, const Coins& right) {
	left.m_gold += right.m_gold;
	left.m_silver += right.m_silver;
	left.m_copper += right.m_copper;
	left.updateCoins(); // Нормализация монет
	return left;
}

// Minus operator for Coins
inline Coins operator-(const Coins& left, const Coins& right) {
	Coins result(left.m_gold - right.m_gold, left.m_silver - right.m_silver, left.m_copper - right.m_copper);
	result.updateCoins(); // Нормализация монет
	return result;
}

// Minus equal operator for Coins
inline Coins& operator-=(Coins& left, const Coins& right) {
	left.m_gold -= right.m_gold;
	left.m_silver -= right.m_silver;
	left.m_copper -= right.m_copper;
	left.updateCoins(); // Нормализация монет
	return left;
}

// Equal operator for Coins
inline bool operator==(const Coins& left, const Coins& right) {
	return (left.m_gold == right.m_gold && left.m_silver == right.m_silver && left.m_copper == right.m_copper);
}

// Not equal operator for Coins
inline bool operator!=(const Coins& left, const Coins& right) {
	return !(left == right);
}

// Less than operator for Coins
inline bool operator<(const Coins& left, const Coins& right) {
	int leftTotal = left.m_gold * 10000 + left.m_silver * 100 + left.m_copper;
	int rightTotal = right.m_gold * 10000 + right.m_silver * 100 + right.m_copper;
	return leftTotal < rightTotal;
}

// Greater than operator for Coins
inline bool operator>(const Coins& left, const Coins& right) {
	return right < left;
}

// Less than or equal operator for Coins
inline bool operator<=(const Coins& left, const Coins& right) {
	return !(right < left);
}

// Greater than or equal operator for Coins
inline bool operator>=(const Coins& left, const Coins& right) {
	return !(left < right);
}

// Output stream operator for Coins
inline std::ostream& operator<<(std::ostream& os, const Coins& coin) {
	os << coin.m_gold << "g " << coin.m_silver << "s " << coin.m_copper << "c";
	return os;
}

// Input stream operator for Coins
inline std::istream& operator>>(std::istream& is, Coins& coin) {
	is >> coin.m_gold >> coin.m_silver >> coin.m_copper;
	coin.updateCoins(); // Нормализация монет после ввода
	return is;
}

#endif /* COINS */