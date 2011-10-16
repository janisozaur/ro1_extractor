#ifndef IMAGEEXTRACTOR_H
#define IMAGEEXTRACTOR_H

#include <QVector>
#include <QByteArray>
#include <QSize>

class QIODevice;
class QDataStream;

class ImageExtractor
{
private:
	QByteArray mData;
	QDataStream *mStream;
	quint8 mDepth;
	QVector<quint32> mDimensions;
public:
	ImageExtractor(QIODevice *data);
	~ImageExtractor();
	quint8 *extractAll() const;
	quint8 *extract(const unsigned int itemNumber) const;
	void display(const int itemNumber, const quint8 threshold) const;
	quint32 itemCount() const;
	quint32 itemByteSize() const;
	QSize itemSize() const;
	quint32 dimensionCount() const;
	quint32 sizeInDim(const quint32 dim) const;
};

#endif // IMAGEEXTRACTOR_H
