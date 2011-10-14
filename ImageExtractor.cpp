#include "ImageExtractor.h"

#include <QDebug>

ImageExtractor::ImageExtractor(QIODevice *data) :
	mStream(new QDataStream(data))
{
	mStream->skipRawData(2);
	quint8 format;
	*mStream >> format;
	if (format != '\x08') {
		qFatal("Improper data format - only unsigned byte (0x08) supported.\n");
	}
	*mStream >> mDepth;
	if (mDepth != 3) {
			qFatal("Improper format depth - expected 3, got %d.\n", mDepth);
	}
	for (int i = 0; i < mDepth; i++) {
		quint32 dim;
		*mStream >> dim;
		mDimensions << dim;
		qDebug() << "dimension: " << dim;
	}
	mData = data->readAll();
	qDebug() << "all ok";
}

ImageExtractor::~ImageExtractor()
{
	delete mStream;
}

quint32 ImageExtractor::itemCount() const
{
	return mDimensions.at(0);
}

quint32 ImageExtractor::dimensionCount() const
{
	return mDimensions.size();
}

quint32 ImageExtractor::sizeInDim(const quint32 dim) const
{
	return mDimensions.at(dim);
}

quint8 *ImageExtractor::extractAll() const
{
	quint8 *buffer = new quint8[mData.size()];
	memcpy(buffer, mData.constData(), mData.size());
	return buffer;
}

quint8 *ImageExtractor::extract(const int itemNumber) const
{
	const quint32 itemsize = mDimensions.at(1) * mDimensions.at(2);
	quint8 *buffer = new quint8[itemsize];
	memcpy(buffer, mData.constData() + itemNumber * itemsize, itemsize);
	return buffer;
}

quint32 ImageExtractor::itemByteSize() const
{
	return mDimensions.at(1) * mDimensions.at(2);
}

void ImageExtractor::display(const int itemNumber, const quint8 threshold) const
{
	quint8 *buffer = extract(itemNumber);
	for (quint32 i = 0; i < mDimensions.at(1); i++) {
		QString row;
		for (quint32 j = 0; j < mDimensions.at(2); j++) {
			if ((const quint8 &)(buffer[i * mDimensions.at(2) + j]) > threshold) {
				row += "#";
			} else {
				row += " ";
			}
		}
		qDebug() << row;
	}
	qDebug() << QString(mDimensions.at(2), '*');
	delete [] buffer;
}

QSize ImageExtractor::itemSize() const
{
	return QSize(mDimensions.at(1), mDimensions.at(2));
}
