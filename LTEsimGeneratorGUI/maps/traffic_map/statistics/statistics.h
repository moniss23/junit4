#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics
{
public:
    Statistics();

    bool getListingStaticInformationforEachUE() const;
    void setListingStaticInformationforEachUE(bool value);

    bool getResettingAllStatisticsCounters() const;
    void setResettingAllStatisticsCounters(bool value);

    bool getListingStatisticsonNAS() const;
    void setListingStatisticsonNAS(bool value);

    bool getListingStatisticsonRRC() const;
    void setListingStatisticsonRRC(bool value);

    bool getListingMobilityStatisticsperModelandArea() const;
    void setListingMobilityStatisticsperModelandArea(bool value);

    bool getListingThroughputStatisticsperAreaandModel() const;
    void setListingThroughputStatisticsperAreaandModel(bool value);

    bool getListingThroughputStatisticsperUEandModel() const;
    void setListingThroughputStatisticsperUEandModel(bool value);

    bool getListingMobilityStatisticsperUE() const;
    void setListingMobilityStatisticsperUE(bool value);

    bool getListingPSStatisticsperModel() const;
    void setListingPSStatisticsperModel(bool value);

    bool getListingPSStatisticsperUE() const;
    void setListingPSStatisticsperUE(bool value);

    bool getListingCSStatisticsperModel() const;
    void setListingCSStatisticsperModel(bool value);

    bool getListingCSStatisticsperUE() const;
    void setListingCSStatisticsperUE(bool value);

    bool getIPGWTG_ProtocolStatistics() const;
    void setIPGWTG_ProtocolStatistics(bool value);

    bool getIPGWTG_TGUStatistics() const;
    void setIPGWTG_TGUStatistics(bool value);

    bool getIPGWTG_ContinuousStatistics() const;
    void setIPGWTG_ContinuousStatistics(bool value);

    bool getPDCP_U_ProtocolStatistics() const;
    void setPDCP_U_ProtocolStatistics(bool value);

    bool getPDCP_U_ROHCProtocolStatistics() const;
    void setPDCP_U_ROHCProtocolStatistics(bool value);

    bool getPDCP_U_GeneralBearerInformation() const;
    void setPDCP_U_GeneralBearerInformation(bool value);

    bool getPDCP_U_BearerROHCinformation() const;
    void setPDCP_U_BearerROHCinformation(bool value);

    bool getPDCP_U_BearerErrorStatistics() const;
    void setPDCP_U_BearerErrorStatistics(bool value);

    bool getPDCP_U_ContinuousStatistics() const;
    void setPDCP_U_ContinuousStatistics(bool value);
private:
    bool ListingStaticInformationforEachUE;
    bool ResettingAllStatisticsCounters;
    bool ListingStatisticsonNAS;
    bool ListingStatisticsonRRC;
    bool ListingMobilityStatisticsperModelandArea;
    bool ListingThroughputStatisticsperAreaandModel;
    bool ListingThroughputStatisticsperUEandModel;
    bool ListingMobilityStatisticsperUE;
    bool ListingPSStatisticsperModel;
    bool ListingPSStatisticsperUE;
    bool ListingCSStatisticsperModel;
    bool ListingCSStatisticsperUE;
    bool IPGWTG_ProtocolStatistics;
    bool IPGWTG_TGUStatistics;
    bool IPGWTG_ContinuousStatistics;
    bool PDCP_U_ProtocolStatistics;
    bool PDCP_U_ROHCProtocolStatistics;
    bool PDCP_U_GeneralBearerInformation;
    bool PDCP_U_BearerROHCinformation;
    bool PDCP_U_BearerErrorStatistics;
    bool PDCP_U_ContinuousStatistics;
};

#endif // STATISTICS_H
