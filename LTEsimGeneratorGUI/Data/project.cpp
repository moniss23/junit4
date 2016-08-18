#include "project.h"

Project::Project() {
    this->genScriptDir = "<default>";
}

QString Project::getElementType() const
{
    return QString("Project");
}

QByteArray Project::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << name << fullpath << genScriptDir;

    stream << parametersFile.serializeData();

    stream << trafficFilesList.size();
    for(auto &&file : trafficFilesList) {
        stream << file.serializeData();
    }

    return serializedData.buffer();
}

void Project::deserializeData(const QByteArray &rawData)
{
    int trafficFilesAmount;
    QByteArray rawParamFile;
    QDataStream stream(rawData);
    stream >> name >> fullpath >> genScriptDir;

    stream >> rawParamFile;
    parametersFile.deserializeData(rawParamFile);

    stream >> trafficFilesAmount;
    while(trafficFilesAmount--) {
        QByteArray rawTrafficFile;
        stream >> rawTrafficFile;

        TrafficFileData trafficFileData;
        trafficFileData.deserializeData(rawTrafficFile);
        trafficFilesList.push_back(trafficFileData);
    }
}

TrafficFileData* Project::findTrafficFileByName(const QString &name) {
    auto trafficfile = std::find_if(std::begin(trafficFilesList), std::end(trafficFilesList),
                                    [&name](const auto &traff)->bool{return traff.filename==name;});

    return trafficfile==trafficFilesList.end() ? nullptr : trafficfile;
}
