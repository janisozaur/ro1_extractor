#include "LeftRightProfile.h"

#include <QString>

#define THRESHOLD 128

LeftRightProfile::LeftRightProfile(QStringList)
{
}

QVector<float> LeftRightProfile::features(const quint8 *data, const QSize size) const
{
	QVector<float> result;
	const int height = size.height();
	const int width = size.width();
	for (int i = 0; i < height; i++) {
		bool found = false;
		for (int j = 0; j < width; j++) {
			if (data[i * width + j] > THRESHOLD) {
				result.append(j);
				found = true;
				break;
			}
		}
		if (!found) {
			result.append(width - 1);
		}
	}
	for (int i = 0; i < height; i++) {
		bool found = false;
		for (int j = width - 1; j >= 0; j--) {
			if (data[i * width + j] > THRESHOLD) {
				result.append(j);
				found = true;
				break;
			}
		}
		if (!found) {
			result.append(0);
		}
	}
	return result;
}

QString LeftRightProfile::name() const
{
	return QString("Left Right Profile");
}
