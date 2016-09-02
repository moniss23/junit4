#include "project.h"

Project::Project() {
    this->genScriptDir = "<default>";
}

QString Project::getElementType() const
{
    return QString("Project");
}

TrafficFileData* Project::findTrafficFileByName(const QString &name) {
    auto trafficfile = std::find_if(trafficFilesList.begin(), trafficFilesList.end(),
                        [&name](const auto &traff)->bool{return traff.filename==name;});

    return trafficfile==trafficFilesList.end() ? nullptr : trafficfile;
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

    stream << cellsInfo;
    stream << handovers;

    stream << dataGeneratorSettings.serializeData();
    stream << sgwSettings.serializeData();
    stream << ucToolSettings.serializeData();
    stream << channelModelSettings.serializeData();
    stream << mmeSettings.serializeData();
    stream << pagingSettings.serializeData();
    stream << ubSimSettings.serializeData();
    stream << generalConfiguration.serializeData();
    stream << mapRange.serializeData();
    stream << ueParameters.serializeData();

    stream << SimulatedCoreNetwork << SimulatedUe;

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

    stream >> cellsInfo;
    stream >> handovers;

    QByteArray rawDataGeneratorSettings;
    stream >> rawDataGeneratorSettings;
    dataGeneratorSettings.deserializeData(rawDataGeneratorSettings);

    QByteArray rawSgwSettings;
    stream >> rawSgwSettings;
    sgwSettings.deserializeData(rawSgwSettings);

    QByteArray rawUCToolSettings;
    stream >> rawUCToolSettings;
    ucToolSettings.deserializeData(rawUCToolSettings);

    QByteArray rawChannelModelSettings;
    stream >> rawChannelModelSettings;
    channelModelSettings.deserializeData(rawChannelModelSettings);

    QByteArray rawMmeSettings;
    stream >> rawMmeSettings;
    mmeSettings.deserializeData(rawMmeSettings);

    QByteArray rawPagingSettings;
    stream >> rawPagingSettings;
    pagingSettings.deserializeData(rawPagingSettings);

    QByteArray rawUBSimSettings;
    stream >> rawUBSimSettings;
    ubSimSettings.deserializeData(rawUBSimSettings);

    QByteArray rawGeneralConfigurationParameters;
    stream >> rawGeneralConfigurationParameters;
    generalConfiguration.deserializeData(rawGeneralConfigurationParameters);

    QByteArray rawMapRange;
    stream >> rawMapRange;
    mapRange.deserializeData(rawMapRange);

    QByteArray rawUeParameters;
    stream >> rawUeParameters;
    ueParameters.deserializeData(rawUeParameters);

    stream >> SimulatedCoreNetwork >> SimulatedUe;
}
