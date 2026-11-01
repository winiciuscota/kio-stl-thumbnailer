// KIO thumbnail plugin for STL: shells out to the stl-thumbnailer script.
#include <KIO/ThumbnailCreator>
#include <KPluginFactory>
#include <QDir>
#include <QImage>
#include <QProcess>
#include <QStandardPaths>
#include <QTemporaryDir>

class StlThumbnailCreator : public KIO::ThumbnailCreator
{
    Q_OBJECT
public:
    StlThumbnailCreator(QObject *parent, const QVariantList &args)
        : KIO::ThumbnailCreator(parent, args)
    {
    }

    KIO::ThumbnailResult create(const KIO::ThumbnailRequest &request) override
    {
        QString exe = QStandardPaths::findExecutable(QStringLiteral("stl-thumbnailer"));
        if (exe.isEmpty())
            exe = QDir::homePath() + QStringLiteral("/.local/bin/stl-thumbnailer");
        QTemporaryDir dir;
        if (!dir.isValid())
            return KIO::ThumbnailResult::fail();
        const QString out = dir.filePath(QStringLiteral("t.png"));
        QProcess p;
        p.start(exe, {QString::number(qMax(request.targetSize().width(), request.targetSize().height())), request.url().toLocalFile(), out});
        if (!p.waitForFinished(60000) || p.exitCode() != 0)
            return KIO::ThumbnailResult::fail();
        QImage img(out);
        return img.isNull() ? KIO::ThumbnailResult::fail() : KIO::ThumbnailResult::pass(img);
    }
};

K_PLUGIN_CLASS_WITH_JSON(StlThumbnailCreator, "stlthumbnail.json")
#include "stlthumbnail.moc"
