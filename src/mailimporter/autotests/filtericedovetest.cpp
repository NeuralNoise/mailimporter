/*
  Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "filtericedovetest.h"
#include "filters/filtericedove.h"
#include "filterimportertest.h"
#include <qtest.h>

class FilterIcecoveAbstract : public MailImporter::FilterIcedove
{
public:
    FilterIcecoveAbstract()
    {
    }

    QString settingsPath() override
    {
        return MailImporter::FilterIcedove::settingsPath();
    }
};

FilterIcedoveTest::FilterIcedoveTest(QObject *parent)
    : QObject(parent)
{
}

FilterIcedoveTest::~FilterIcedoveTest()
{
}

void FilterIcedoveTest::shouldHaveDefaultSettingsPath()
{
    FilterIcecoveAbstract filter;
    QCOMPARE(filter.settingsPath(), MailImporter::FilterIcedove::defaultSettingsPath());
}

void FilterIcedoveTest::shouldImportData()
{
}

void FilterIcedoveTest::canNotImportDataEmptyPath()
{
    MailImporter::FilterIcedove filter;
    MailImporter::FilterInfo *info = new MailImporter::FilterInfo;
    FilterImporterTest *importerTest = new FilterImporterTest(info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(info);
    filter.importMails(QString());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
}

void FilterIcedoveTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterIcedove filter;
    MailImporter::FilterInfo *info = new MailImporter::FilterInfo;
    FilterImporterTest *importerTest = new FilterImporterTest(info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(info);
    filter.importMails(QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
}

void FilterIcedoveTest::canNotImportDataWhenHomeDirSelected()
{
    MailImporter::FilterIcedove filter;
    MailImporter::FilterInfo *info = new MailImporter::FilterInfo;
    FilterImporterTest *importerTest = new FilterImporterTest(info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(info);
    filter.importMails(QDir::homePath());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
}

QTEST_MAIN(FilterIcedoveTest)
