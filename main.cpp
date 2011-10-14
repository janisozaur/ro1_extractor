#include "ImageExtractor.h"
#include "FeatureExtractorInterface.h"
#include "LeftRightProfile.h"

#include <QtCore/QCoreApplication>
#include <QStringList>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QStringList arguments = QCoreApplication::instance()->arguments();
	if (arguments.count() < 3) {
		QStringList usage;
		usage << arguments.at(0);
		usage << "[file to open]";
		usage << "[threshold]";
		qDebug() << usage.join(" ");
		qFatal("Too few arguments");
	}
	QString fileName = arguments.at(1);
	QFile archive(fileName);
	if (!archive.open(QIODevice::ReadOnly)) {
		qFatal("Failed to open file %s.\n", fileName.toStdString().c_str());
	}

	bool ok;
	ImageExtractor ie(&archive);
	const quint8 threshold = qBound(0, arguments.at(2).toInt(&ok), 255);
	if (ok) {
		ie.display(1, threshold);
		FeatureExtractorInterface *fei = new LeftRightProfile(ie.extract(1), ie.itemSize());
		QVector<float> features = fei->features();
		for (int i = 0; i < features.size(); i++) {
			qDebug() << features.at(i);
		}
		delete fei;
	}

	archive.close();

	return 0;
}
