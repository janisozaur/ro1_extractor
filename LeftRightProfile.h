#ifndef LEFTRIGHTPROFILE_H
#define LEFTRIGHTPROFILE_H

#include "FeatureExtractorInterface.h"

class LeftRightProfile : public FeatureExtractorInterface
{
public:
	LeftRightProfile(const quint8 *data, const QSize size);
	int size() const;
	QVector<float> features() const;
	QString name() const;

private:
	const quint8 *mData;
	const QSize mSize;
};

#endif // LEFTRIGHTPROFILE_H
