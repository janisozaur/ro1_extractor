#include "LeftRightProfile.h"

#include <QString>

#define THRESHOLD 128

LeftRightProfile::LeftRightProfile(const quint8 *data, const QSize size) :
	mData(data),
	mSize(size)
{
}

int LeftRightProfile::size() const
{
	return mSize.height() * 2;
}

QVector<float> LeftRightProfile::features() const
{
	QVector<float> result;
	const int height = mSize.height();
	const int width = mSize.width();
	for (int i = 0; i < height; i++) {
		bool found = false;
		for (int j = 0; j < width; j++) {
			if (mData[i * width + j] > THRESHOLD) {
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
		for (int j = width; j > 0; j--) {
			if (mData[i * width + j] > THRESHOLD) {
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
