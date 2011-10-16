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
	if (arguments.count() < 4) {
		QStringList usage;
		usage << arguments.at(0);
		usage << "[input file]";
		usage << "[output file]";
		usage << "[limit (use 0 to parse all)]";
		qDebug() << usage.join(" ");
		qFatal("Too few arguments");
	}

	bool ok;
	quint32 count = arguments.at(3).toInt(&ok);
	if (!ok) {
		qFatal("Argument 3 (%s) is not a number.\n", arguments.at(3).toStdString().c_str());
	}

	QString fileName = arguments.at(1);
	QFile archive(fileName);
	if (!archive.open(QIODevice::ReadOnly)) {
		qFatal("Failed to open file %s.\n", fileName.toStdString().c_str());
	}

	ImageExtractor ie(&archive);
	count = qBound((quint32)0, count, ie.itemCount());
	if (count == 0) {
		count = ie.itemCount();
	}
	QFile f(arguments.at(2));
	if (!f.open(QIODevice::WriteOnly)) {
		qFatal("Failed to open file %s for writing.\n", f.fileName().toStdString().c_str());
	}
	QTextStream output(&f);
	FeatureExtractorInterface *fei = new LeftRightProfile();
	for (unsigned int i = 0; i < count; i++) {
		//ie.display(1, threshold);
		QVector<float> features = fei->features(ie.extract(i), ie.itemSize());
		for (int j = 0; j < features.size(); j++) {
			output << features.at(j) << " ";
		}
		output << endl;
		qDebug() << "written" << features.size() << "features for item" << i << "to" << f.fileName();
	}
	delete fei;
	f.close();

	archive.close();

	return 0;
}
