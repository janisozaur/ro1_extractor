#include "FeatureExtractorFactory.h"
#include "LeftRightProfile.h"

FeatureExtractorInterface *FeatureExtractorFactory::getExtractor(QStringList args)
{
	FeatureExtractorInterface *extractor = NULL;
	if (args.isEmpty()) {
		return extractor;
	} else if (args.at(0) == "LeftRightProfile") {
		extractor = new LeftRightProfile(args.mid(1));
	}
	return extractor;
}
