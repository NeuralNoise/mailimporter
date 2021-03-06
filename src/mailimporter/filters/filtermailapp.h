/***************************************************************************
                          filter_mailapp.h  -  OS X Mail App import
                             -------------------
    copyright            : (C) 2004 by Chris Howells
    email                : howells@kde.org

    Derived from code by:
    copyright            : (C) 2003 by Laurence Anderson
    email                : l.d.anderson@warwick.ac.uk

 ***************************************************************************/

#ifndef MAILIMPORTER_FILTER_MAILAPP_H
#define MAILIMPORTER_FILTER_MAILAPP_H

#include "filters.h"
/**
 *imports mbox archives messages into KMail
 *@author Chris Howells
 */
namespace MailImporter {
class FilterMailAppPrivate;
class MAILIMPORTER_EXPORT FilterMailApp : public Filter
{
public:
    FilterMailApp();
    ~FilterMailApp();

    void import() override;
    void importMails(const QString &maildir);
private:
    FilterMailAppPrivate *const d;
    void traverseDirectory(const QString &);
};
}

#endif
