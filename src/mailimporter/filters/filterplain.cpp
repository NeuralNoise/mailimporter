/***************************************************************************
                          FilterPlain.cxx  -  Plain mail import
                             -------------------
    begin                : Fri Jun 14 2002
    copyright            : (C) 2002 by Laurence Anderson
    email                : l.d.anderson@warwick.ac.uk
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <KLocalizedString>
#include <QFileDialog>

#include "filterplain.h"

using namespace MailImporter;

FilterPlain::FilterPlain()
    : Filter(i18n("Import Plain Text Emails"),
             i18n("Laurence Anderson <p>( Filter accelerated by Danny Kukawka )</p>"),
             i18n("<p>Select the directory containing the emails on your system. "
                  "The emails are placed in a folder with the same name as the "
                  "directory they were in, prefixed by PLAIN-</p>"
                  "<p>This filter will import all .msg, .eml and .txt emails.</p>"))
{
}

FilterPlain::~FilterPlain()
{
}

void FilterPlain::import()
{
    // Select directory containing plain text emails
    const QString mailDir = QFileDialog::getExistingDirectory(filterInfo()->parentWidget(), QString(), QDir::homePath());
    importMails(mailDir);
}

void FilterPlain::importMails(const QString &mailDir)
{
    if (mailDir.isEmpty()) { // No directory selected
        filterInfo()->alert(i18n("No directory selected."));
        return;
    }
    QDir dir(mailDir);
    const QStringList files = dir.entryList(QStringList() << QStringLiteral("*.[eE][mM][lL]") << QStringLiteral("*.[tT][xX][tT]") << QStringLiteral("*.[mM][sS][gG]"), QDir::Files, QDir::Name);
    // Count total number of files to be processed
    filterInfo()->addInfoLogEntry(i18n("Counting files..."));
    int totalFiles = files.count();
    int currentFile = 0;
    if (files.isEmpty()) {
        filterInfo()->addErrorLogEntry(i18n("No files found for import."));
    } else {
        filterInfo()->addInfoLogEntry(i18n("Importing new mail files..."));
        QStringList::ConstIterator end(files.constEnd());
        const QString destName = QStringLiteral("PLAIN-%1").arg(dir.dirName());
        for (QStringList::ConstIterator mailFile = files.constBegin(); mailFile != end; ++mailFile) {
            const QString dirRealPath = dir.filePath(*mailFile);
            filterInfo()->setFrom(dirRealPath);
            filterInfo()->setTo(destName);
            filterInfo()->setCurrent(0);
            if (!importMessage(destName, dirRealPath, filterInfo()->removeDupMessage())) {
                filterInfo()->addErrorLogEntry(i18n("Could not import %1", *mailFile));
            }

            filterInfo()->setCurrent(100);
            filterInfo()->setOverall(100 * ++currentFile / totalFiles);
            if (filterInfo()->shouldTerminate()) {
                break;
            }
        }

        filterInfo()->addInfoLogEntry(i18n("Finished importing emails from %1", mailDir));
        if (countDuplicates() > 0) {
            filterInfo()->addInfoLogEntry(i18np("1 duplicate message not imported", "%1 duplicate messages not imported", countDuplicates()));
        }
        if (filterInfo()->shouldTerminate()) {
            filterInfo()->addInfoLogEntry(i18n("Finished import, canceled by user."));
        }
    }
    clearCountDuplicate();
}
