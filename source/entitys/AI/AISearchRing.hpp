#ifndef A146570F_9E3C_405B_B687_EE968C4DE611
#define A146570F_9E3C_405B_B687_EE968C4DE611

#include "AIOption.hpp"

// class SearchRing used to search the target on radius
class SearchRing {
private:
	bool _ai_targenInRange = false;
	bool _ai_enambleSearch = false;

	sf::CircleShape _ai_searchRing;

public:
	SearchRing() {}
	~SearchRing() {}

	// enable search target on radius
	void searchTarget(AIOption* option) {}

	// set the radius of the search ring
	void setRadius(float radius) {}

	// get the radius of the search ring
	float getRadius() {}
};

#endif /* A146570F_9E3C_405B_B687_EE968C4DE611 */
