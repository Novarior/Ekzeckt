#include "SpiralModel.hpp"

#include <random>

SpiralModel::SpiralModel(ModelData* data):mData(data) {
	regenerateSpiral();
}

SpiralModel::~SpiralModel() {
	clearModel();

}

void SpiralModel::clearModel() {
	mPointStar.clear();
	mLines.clear();
	mStarPlus.clear();
	mDust.clear();
	mGas.clear();
}

void SpiralModel::regenerateSpiral() {
	clearModel();
	int cArm = mData->spiralArms * mData->spiralArmCount;

	mLines = sf::VertexArray(sf::PrimitiveType::Lines, cArm);
	mPointStar = sf::VertexArray(sf::PrimitiveType::Points, mData->starCount);
	mStarPlus = sf::VertexArray(sf::PrimitiveType::Lines, mData->starCount); // 2 лінії на + = 4 вертекси
	mDust = sf::VertexArray(sf::PrimitiveType::Points, mData->DustDensity);
	mGas = sf::VertexArray(sf::PrimitiveType::Points, mData->GasDensity);

	generateSpiralArms();
	generateStars();
	generateDust();
	generateGas();
}
sf::Color SpiralModel::getArmColor(float normalizedIntensity) const {
	// Градієнт кольорів для рукавів: червоний -> помаранчевий -> жовтий -> білий
	if (normalizedIntensity < 0.3f) {
		// Темне червоне
		return sf::Color(200, 50, 50, 200);
	} else if (normalizedIntensity < 0.6f) {
		// Помаранчеве
		return sf::Color(255, 140, 50, 180);
	} else if (normalizedIntensity < 0.85f) {
		// Жовтаво-біле
		return sf::Color(255, 220, 100, 160);
	} else {
		// Світле біле
		return sf::Color(255, 255, 200, 140);
	}
}

sf::Color SpiralModel::getStarColor(float randomValue) const {
	// Різні типи зірок залежно від температури
	// randomValue: 0.0f - 1.0f
	randomValue = randomValue * 10.0f; // Перетворюємо в 0-10
	int type = static_cast<int>(randomValue);

	switch (type) {
	case 0:
	case 1:
		// Сині масивні зірки (10%)
		return sf::Color(100, 180, 255, 255);
	case 2:
	case 3:
	case 4:
		// Білі гарячі зірки (30%)
		return sf::Color(255, 255, 255, 255);
	case 5:
	case 6:
	case 7:
		// Жовті сонячні зірки (30%)
		return sf::Color(255, 240, 100, 255);
	case 8:
		// Помаранчеві кулі (10%)
		return sf::Color(255, 150, 80, 255);
	case 9:
		// Червоні карлики (10%)
		return sf::Color(200, 80, 60, 200);
	default:
		return sf::Color::White;
	}
}

sf::Vector2f SpiralModel::calculateSpiralPoint(float angle, float radius) const {
	// Логарифмічна спіраль: r(θ) = a * e^(b * θ)
	// b залежить від кривизни рукава
	float b = mData->spiralArmCurvature / 100.f;
	float r = radius * std::exp(b * angle);

	// Обмежуємо радіус величиною galaxyRadius
	if (r > mData->galaxyRadius) {
		r = mData->galaxyRadius;
	}

	float x = r * std::cos(angle);
	float y = r * std::sin(angle);

	return sf::Vector2f(x, y);
}

void SpiralModel::generateSpiralArms() {
	float armAngelOffset = 360.f / mData->spiralArms;
	float angleStep = 0.1f;

	uint32_t lineIndex = 0;
	std::mt19937 generator(mData->seed);
	std::normal_distribution<float> distribution(0.f, mData->spiralArmsWigth / 3.f);
	std::uniform_real_distribution<float> intensityDist(0.2f, 1.0f);

	for (uint16_t arm = 0; arm < mData->spiralArms; ++arm) {
		float armOffset = (arm * armAngelOffset) * 3.14159f / 180.f;

		sf::Vector2f previousPoint;
		sf::Color previousColor;
		bool isFirstPoint = true;

		float angle = 0.f;
		for (int i = 0; i <= mData->spiralArmCount; i += 2) {
			angle += angleStep;
			sf::Vector2f point = calculateSpiralPoint(angle, mData->CoreRadius);

			float finalAngle = angle + armOffset;
			sf::Vector2f spiralPoint(
				point.x * std::cos(armOffset) - point.y * std::sin(armOffset),
				point.x * std::sin(armOffset) + point.y * std::cos(armOffset)
			);

			float jitter = distribution(generator);
			sf::Vector2f jitteredPoint = spiralPoint;
			jitteredPoint.x += jitter * std::cos(finalAngle);
			jitteredPoint.y += jitter * std::sin(finalAngle);

			// Обраховуємо інтенсивність від центру до краю рукава
			float distFromCenter = std::sqrt(jitteredPoint.x * jitteredPoint.x + jitteredPoint.y * jitteredPoint.y);
			float normalizedIntensity = intensityDist(generator) * (1.0f - distFromCenter / mData->galaxyRadius * 0.3f);
			sf::Color armColor = getArmColor(normalizedIntensity);

			if (!isFirstPoint) {
				if (i + 1 >= mData->spiralArmCount) break;

				mLines[lineIndex].position = previousPoint;
				mLines[lineIndex].color = previousColor;
				lineIndex++;

				mLines[lineIndex].position = jitteredPoint;
				mLines[lineIndex].color = armColor;
				lineIndex++;
			}

			previousPoint = jitteredPoint;
			previousColor = armColor;
			isFirstPoint = false;

		}

		if (lineIndex >= mData->spiralArmCount * mData->spiralArms) break;
	}
}

void SpiralModel::generateStars() {
	std::mt19937 generator(mData->seed + 1);
	std::uniform_real_distribution<float> angleDist(0.f, 2 * 3.14159f);
	std::uniform_real_distribution<float> radiusDist(0.f, mData->galaxyRadius);
	std::uniform_real_distribution<float> armWeightDist(0.f, 1.f);
	std::uniform_real_distribution<float> starTypeDist(0.f, 1.f);
	std::uniform_int_distribution<int> alphaDist(100, 255);

	uint32_t pointIndex = 0;
	uint32_t plusIndex = 0;
	const float plusSize = 3.f;
	const float armAttraction = 0.01f;

	for (uint32_t i = 0; i < mData->starCount; ++i) {
		sf::Vector2f starPos;

		if (armWeightDist(generator) < armAttraction) {
			float angle = angleDist(generator);
			float radius = radiusDist(generator);
			starPos = calculateSpiralPoint(angle, mData->CoreRadius);

			std::normal_distribution<float> offsetDist(0.f, mData->spiralArmsWigth / 2.f);
			starPos.x += offsetDist(generator);
			starPos.y += offsetDist(generator);
		} else {
			float angle = angleDist(generator);
			float radius = radiusDist(generator);
			starPos.x = radius * std::cos(angle);
			starPos.y = radius * std::sin(angle);
		}

		float distFromCenter = std::sqrt((starPos.x * starPos.x) + (starPos.y * starPos.y));
		uint8_t alpha = static_cast<uint8_t>(alphaDist(generator) * (1.f - distFromCenter / mData->galaxyRadius * 0.5f));

		// Отримуємо колір зірки передавши float
		sf::Color starColor = getStarColor(starTypeDist(generator));
		starColor.a = alpha;

		if (pointIndex < mData->starCount) {
			mPointStar[pointIndex].position = starPos;
			mPointStar[pointIndex].color = starColor;
			pointIndex++;
		}

		if (armWeightDist(generator) < 0.1f && plusIndex + 3 < mData->starCount * 4) {
			mStarPlus[plusIndex].position = sf::Vector2f(starPos.x - plusSize, starPos.y);
			mStarPlus[plusIndex].color = starColor;
			plusIndex++;

			mStarPlus[plusIndex].position = sf::Vector2f(starPos.x + plusSize, starPos.y);
			mStarPlus[plusIndex].color = starColor;
			plusIndex++;

			mStarPlus[plusIndex].position = sf::Vector2f(starPos.x, starPos.y - plusSize);
			mStarPlus[plusIndex].color = starColor;
			plusIndex++;

			mStarPlus[plusIndex].position = sf::Vector2f(starPos.x, starPos.y + plusSize);
			mStarPlus[plusIndex].color = starColor;
			plusIndex++;
		}
	}
}

void SpiralModel::generateDust() {
	std::mt19937 generator(mData->seed + 2);
	std::uniform_real_distribution<float> angleDist(0.f, 2 * 3.14159f);
	std::uniform_real_distribution<float> radiusDist(0.f, mData->galaxyRadius);
	std::uniform_real_distribution<float> offsetDist(-mData->spiralArmsWigth, mData->spiralArmsWigth);
	std::uniform_int_distribution<int> colorVariation(0, 2);

	uint32_t dustIndex = 0;
	uint32_t gasIndex = 0;

	// Пил з коричневуватим відтінком
	for (size_t i = 0; i < static_cast<size_t>(mData->DustDensity * 100) && dustIndex < mDust.getVertexCount(); ++i) {
		float angle = angleDist(generator);
		float radius = radiusDist(generator);

		sf::Vector2f dustPos = calculateSpiralPoint(angle, mData->CoreRadius);
		dustPos.x += offsetDist(generator);
		dustPos.y += offsetDist(generator);

		// Різні відтінки коричневого для пилу
		int dustType = colorVariation(generator);
		sf::Color dustColor;
		switch (dustType) {
		case 0:
			dustColor = sf::Color(120, 80, 60, 80);   // Темне коричневе
			break;
		case 1:
			dustColor = sf::Color(140, 100, 70, 70);  // Середнє коричневе
			break;
		case 2:
			dustColor = sf::Color(160, 120, 80, 60);  // Світле коричневе
			break;
		}

		mDust[dustIndex].position = dustPos;
		mDust[dustIndex].color = dustColor;
		dustIndex++;
	}


}

void SpiralModel::generateGas() {
	std::mt19937 generator(mData->seed + 2);
	std::uniform_real_distribution<float> angleDist(0.f, 2 * 3.14159f);
	std::uniform_real_distribution<float> radiusDist(0.f, mData->galaxyRadius);
	std::uniform_int_distribution<int> colorVariation(0, 2);
	uint32_t gasIndex = 0;
	// Газ з синьо-фіолетовим відтінком
	for (size_t i = 0; i < static_cast<size_t>(mData->GasDensity) && gasIndex < mGas.getVertexCount(); ++i) {
		float angle = angleDist(generator);
		float radius = radiusDist(generator);

		sf::Vector2f gasPos;
		gasPos.x = radius * std::cos(angle);
		gasPos.y = radius * std::sin(angle);

		sf::Vector2f armOffset = calculateSpiralPoint(angle, mData->CoreRadius);
		gasPos.x += armOffset.x * 0.3f;
		gasPos.y += armOffset.y * 0.3f;

		// Різні відтінки синього/фіолетового для газу
		int gasType = colorVariation(generator);
		sf::Color gasColor;
		switch (gasType) {
		case 0:
			gasColor = sf::Color(100, 150, 255, 40);  // Синій газ
			break;
		case 1:
			gasColor = sf::Color(150, 100, 200, 35); // Фіолетовий газ
			break;
		case 2:
			gasColor = sf::Color(120, 180, 255, 38); // Світло-синій газ
			break;
		}

		mGas[gasIndex].position = gasPos;
		mGas[gasIndex].color = gasColor;
		gasIndex++;
	}
}

void SpiralModel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;

	// Рисуємо в порядку: пил та газ -> рукава -> зірки
	target.draw(mDust, states);
	target.draw(mGas, states);
	target.draw(mLines, states);
	target.draw(mPointStar, states);
	target.draw(mStarPlus, states);
}