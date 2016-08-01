#include "project.h"


QString Project::getElementType() const
{
  return "Project";
}

QByteArray Project::serializeToFile()
{
   return QByteArray();
}

void Project::serializeFromFile(QByteArray rawData)
{
   (void) rawData;
}
