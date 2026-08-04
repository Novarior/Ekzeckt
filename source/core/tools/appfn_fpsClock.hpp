#ifndef CORE_APPFN_FPSCLOCK_H
#define CORE_APPFN_FPSCLOCK_H

#include <SFML/System.hpp>

namespace appfn {
class FPS {
public:
	/// @brief Constructor with initialization.
	///
	FPS() {
		mFrame = 0;
		mFps = 0;
	}

	/// @brief Update the frame count.
	static void update() {
		if (mClock.getElapsedTime().asSeconds() >= 1.f) {
			mFps = mFrame;
			mFrame = 0;
			mClock.restart();
		}

		++mFrame;
	}
	static void reset() {
		mFrame = 0;
		mFps = 0;
		mClock.restart();
	}

	/// @brief Get the current FPS count.
	/// @return FPS count.
	static const unsigned int getFPS() { return mFps; }

	static unsigned int mFrame;
	static unsigned int mFps;
	static sf::Clock mClock;
};
};
#endif // CORE_APPFN_FPSCLOCK_H