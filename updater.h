#ifndef UPDATER_H
#define UPDATER_H

#include <QJsonObject>
#include <QObject>
#include <QString>

class Updater : public QObject
{
    Q_OBJECT

public:
    Updater(const QString &manifestUrl, const QString &repoName);
    ~Updater();

    QString latestVersion() const;
    bool checkForUpdates(const QString &curVersion) const;
    void fetchManifest();
    void install(const QString &curVersion = nullptr);

signals:
    void fetchManifestComplete();

    void installProgress(int progress, const QString &msg = nullptr);
    void subtaskSetup(bool enabled, int max = 100);
    void subtaskProgress(int progress, const QString &msg = nullptr);

private:
    const QString manifestUrl;
    const QString repoName;

    QJsonObject manifest;
    std::map<QString, QJsonObject> versions;

    int totalTasks = 0;
    int completedTasks = 0;

    int getInstallProgress() const { return static_cast<int>(completedTasks / totalTasks * 100.); }

    void fullInstall(const QJsonObject &version);
    void update(const QJsonObject &version, const QString &fromVersion);

    void performTask(const QJsonObject &task);

    void taskDownload(const QString &url);
    void taskDelete(const QString &target);
    void taskDeleteDir(const QString &target);

    void setCurrentVersion(const QJsonObject &version);
};

#endif // UPDATER_H
