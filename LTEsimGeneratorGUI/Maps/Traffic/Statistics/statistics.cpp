#include "statistics.h"

Statistics::Statistics()
{
    ListingStaticInformationforEachUE = false;
    ResettingAllStatisticsCounters = false;
    ListingStatisticsonNAS = false;
    ListingStatisticsonRRC = false;
    ListingMobilityStatisticsperModelandArea = false;
    ListingThroughputStatisticsperAreaandModel = false;
    ListingThroughputStatisticsperUEandModel = false;
    ListingMobilityStatisticsperUE = false;
    ListingPSStatisticsperModel = false;
    ListingPSStatisticsperUE = false;
    ListingCSStatisticsperModel = false;
    ListingCSStatisticsperUE = false;
    IPGWTG_ProtocolStatistics = false;
    IPGWTG_TGUStatistics = false;
    IPGWTG_ContinuousStatistics = false;
    PDCP_U_ProtocolStatistics = false;
    PDCP_U_ROHCProtocolStatistics = false;
    PDCP_U_GeneralBearerInformation = false;
    PDCP_U_BearerROHCinformation = false;
    PDCP_U_BearerErrorStatistics = false;
    PDCP_U_ContinuousStatistics = false;
}

bool Statistics::getListingStaticInformationforEachUE() const
{
    return ListingStaticInformationforEachUE;
}
void Statistics::setListingStaticInformationforEachUE(bool value)
{
    ListingStaticInformationforEachUE = value;
}

bool Statistics::getResettingAllStatisticsCounters() const
{
    return ResettingAllStatisticsCounters;
}
void Statistics::setResettingAllStatisticsCounters(bool value)
{
    ResettingAllStatisticsCounters = value;
}

bool Statistics::getListingStatisticsonNAS() const
{
    return ListingStatisticsonNAS;
}
void Statistics::setListingStatisticsonNAS(bool value)
{
    ListingStatisticsonNAS = value;
}

bool Statistics::getListingStatisticsonRRC() const
{
    return ListingStatisticsonRRC;
}
void Statistics::setListingStatisticsonRRC(bool value)
{
    ListingStatisticsonRRC = value;
}

bool Statistics::getListingMobilityStatisticsperModelandArea() const
{
    return ListingMobilityStatisticsperModelandArea;
}
void Statistics::setListingMobilityStatisticsperModelandArea(bool value)
{
    ListingMobilityStatisticsperModelandArea = value;
}

bool Statistics::getListingThroughputStatisticsperAreaandModel() const
{
    return ListingThroughputStatisticsperAreaandModel;
}
void Statistics::setListingThroughputStatisticsperAreaandModel(bool value)
{
    ListingThroughputStatisticsperAreaandModel = value;
}

bool Statistics::getListingThroughputStatisticsperUEandModel() const
{
    return ListingThroughputStatisticsperUEandModel;
}
void Statistics::setListingThroughputStatisticsperUEandModel(bool value)
{
    ListingThroughputStatisticsperUEandModel = value;
}

bool Statistics::getListingMobilityStatisticsperUE() const
{
    return ListingMobilityStatisticsperUE;
}
void Statistics::setListingMobilityStatisticsperUE(bool value)
{
    ListingMobilityStatisticsperUE = value;
}

bool Statistics::getListingPSStatisticsperModel() const
{
    return ListingPSStatisticsperModel;
}
void Statistics::setListingPSStatisticsperModel(bool value)
{
    ListingPSStatisticsperModel = value;
}

bool Statistics::getListingPSStatisticsperUE() const
{
    return ListingPSStatisticsperUE;
}
void Statistics::setListingPSStatisticsperUE(bool value)
{
    ListingPSStatisticsperUE = value;
}

bool Statistics::getListingCSStatisticsperModel() const
{
    return ListingCSStatisticsperModel;
}
void Statistics::setListingCSStatisticsperModel(bool value)
{
    ListingCSStatisticsperModel = value;
}

bool Statistics::getListingCSStatisticsperUE() const
{
    return ListingCSStatisticsperUE;
}
void Statistics::setListingCSStatisticsperUE(bool value)
{
    ListingCSStatisticsperUE = value;
}

bool Statistics::getIPGWTG_ProtocolStatistics() const
{
    return IPGWTG_ProtocolStatistics;
}
void Statistics::setIPGWTG_ProtocolStatistics(bool value)
{
    IPGWTG_ProtocolStatistics = value;
}

bool Statistics::getIPGWTG_TGUStatistics() const
{
    return IPGWTG_TGUStatistics;
}
void Statistics::setIPGWTG_TGUStatistics(bool value)
{
    IPGWTG_TGUStatistics = value;
}

bool Statistics::getIPGWTG_ContinuousStatistics() const
{
    return IPGWTG_ContinuousStatistics;
}
void Statistics::setIPGWTG_ContinuousStatistics(bool value)
{
    IPGWTG_ContinuousStatistics = value;
}

bool Statistics::getPDCP_U_ProtocolStatistics() const
{
    return PDCP_U_ProtocolStatistics;
}
void Statistics::setPDCP_U_ProtocolStatistics(bool value)
{
    PDCP_U_ProtocolStatistics = value;
}

bool Statistics::getPDCP_U_ROHCProtocolStatistics() const
{
    return PDCP_U_ROHCProtocolStatistics;
}
void Statistics::setPDCP_U_ROHCProtocolStatistics(bool value)
{
    PDCP_U_ROHCProtocolStatistics = value;
}

bool Statistics::getPDCP_U_GeneralBearerInformation() const
{
    return PDCP_U_GeneralBearerInformation;
}
void Statistics::setPDCP_U_GeneralBearerInformation(bool value)
{
    PDCP_U_GeneralBearerInformation = value;
}

bool Statistics::getPDCP_U_BearerROHCinformation() const
{
    return PDCP_U_BearerROHCinformation;
}
void Statistics::setPDCP_U_BearerROHCinformation(bool value)
{
    PDCP_U_BearerROHCinformation = value;
}

bool Statistics::getPDCP_U_BearerErrorStatistics() const
{
    return PDCP_U_BearerErrorStatistics;
}
void Statistics::setPDCP_U_BearerErrorStatistics(bool value)
{
    PDCP_U_BearerErrorStatistics = value;
}

bool Statistics::getPDCP_U_ContinuousStatistics() const
{
    return PDCP_U_ContinuousStatistics;
}
void Statistics::setPDCP_U_ContinuousStatistics(bool value)
{
    PDCP_U_ContinuousStatistics = value;
}
