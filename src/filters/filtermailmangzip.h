/*
  Copyright (c) 2013-2017 Montel Laurent <montel@kde.org>

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

#ifndef MAILIMPORTER_FILTER_MAILMANGZIP_H
#define MAILIMPORTER_FILTER_MAILMANGZIP_H

#include "filters.h"

namespace MailImporter
{
class MAILIMPORTER_EXPORT FilterMailmanGzip : public Filter
{
public:
    FilterMailmanGzip();
    ~FilterMailmanGzip();

    void importMails(const QStringList &filenames);
    void import() Q_DECL_OVERRIDE;
};
}

#endif