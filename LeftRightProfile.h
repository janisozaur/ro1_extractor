#ifndef LEFTRIGHTPROFILE_H
#define LEFTRIGHTPROFILE_H

#include "FeatureExtractorInterface.h"

class LeftRightProfile : public FeatureExtractorInterface
{
public:
	QVector<float> features(const quint8 *data, const QSize size) const;
	QString name() const;
};

#endif // LEFTRIGHTPROFILE_H
