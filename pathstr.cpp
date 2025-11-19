/*
 ******************************************************************
 * A small library for handling filesystem paths as strings (Qt). *
 *                                                                *
 * artemvlas (at) proton (dot) me                                 *
 * https://github.com/artemvlas/pathstr                           *
 ******************************************************************
 *
 * MIT License
 * Copyright (c) 2021 - present Artem Vlasenko
 */

#include "pathstr.h"
#include <QStringBuilder>
#include <QStringList>

namespace pathstr {
QString joinPath(const QString &absolutePath, const QString &addPath)
{
    // 0, 1, 2
    qint8 sep_count = 0;

    if (endsWithSep(absolutePath))
        ++sep_count;

    if (startsWithSep(addPath))
        ++sep_count;

    switch (sep_count) {
    case 1:
        return absolutePath + addPath;
    case 2: {
        QStringView chopped = QStringView(absolutePath).left(absolutePath.size() - 1);
        return chopped % addPath;
    }
    default: // case 0
        return absolutePath % _sep % addPath;
    }
}

QString entryName(const QString &path)
{
    if (isRoot(path)) {
        const QChar ch = path.at(0);
        return ch.isLetter() ? QStringLiteral(u"Drive_") + ch.toUpper() : "Root";
    }

    // _sep == '/'
    const bool endsWithSep = path.endsWith(_sep);
    const int lastSepInd = path.lastIndexOf(_sep, -2);

    if (lastSepInd == -1) {
        return endsWithSep ? path.chopped(1) : path;
    }

    const int len = endsWithSep ? (path.size() - lastSepInd - 2) : -1;
    return path.mid(lastSepInd + 1, len);
}

QString parentFolder(const QString &path)
{
    const int ind = path.lastIndexOf(_sep, -2);

    switch (ind) {
    case -1: // root --> root; string'/' --> ""
        return isRoot(path) ? path : QString();
    case 0: // /folder'/' --> "/"
        return path.at(ind);
    case 2: // C:/folder'/' --> "C:/"
        return isRoot(path.left(ind)) ? path.left(3) : path.left(ind);
    default: // /folder/item'/' --> /folder
        return path.left(ind);
    }
}

QString relativePath(const QString &rootFolder, const QString &fullPath)
{
    if (rootFolder.isEmpty())
        return fullPath;

    if (!fullPath.startsWith(rootFolder))
        return QString();

    // _sep == u'/';
    const int cut = rootFolder.endsWith(_sep) ? rootFolder.size() - 1 : rootFolder.size();

    return ((cut < fullPath.size()) && (fullPath.at(cut) == _sep)) ? fullPath.mid(cut + 1) : QString();

    // #2 impl. --> x2 slower due to (rootFolder + '/')
    // const QString &_root = rootFolder.endsWith('/') ? rootFolder : rootFolder + '/';
    // return fullPath.startsWith(_root) ? fullPath.mid(_root.size()) : QString();
}

QString shortenPath(const QString &path)
{
    if (isRoot(path) || isRoot(parentFolder(path)))
        return path;

    QString res;

    if (isAbsolute(path))
        res += root(path);

    const QStringList parts = path.split(_sep, Qt::SkipEmptyParts);

    for (int i = hasWindowsRoot(parts.at(0)) ? 1 : 0; i < parts.size(); ++i) {
        if (i < (parts.size() - 1))
            res += QStringLiteral("../");
        else
            res += parts.at(i);
    }

    return res;
}

QString composeFilePath(const QString &parentFolder, const QString &baseName, const QString &ext)
{
    // with sep check
    // const QString _file = joinStrings(baseName, ext, u'.');
    // return joinPath(parentFolder, _file);

    // no sep check
    return parentFolder % _sep % baseName % _dot % ext;
}

QString root(const QString &path)
{
    // Unix-style fs root "/"
    if (path.startsWith(_sep))
        return _sep;

    // Windows-style root "C:/"
    if (hasWindowsRoot(path))
        return path.at(0).toUpper() % ':' % _sep;

    // no root found
    return QString();
}

QString suffix(const QString &fileName)
{
    const int len = suffixSize(fileName);
    return (len > 0) ? fileName.right(len).toLower() : QString();
}

QString setSuffix(const QString &fileName, const QString &suf)
{
    const int cur_suf_size = suffixSize(fileName);

    if (cur_suf_size == 0)
        return joinStrings(fileName, suf, _dot);

    QStringView chopped = QStringView(fileName).left(fileName.size() - cur_suf_size);
    return chopped % suf;
}

int suffixSize(const QString &fileName)
{
    // in case: /folder.22/filename_with_no_dots
    const QString file_name = entryName(fileName);
    const int dot_ind = file_name.lastIndexOf(_dot);

    if (dot_ind < 1)
        return 0;

    return file_name.size() - dot_ind - 1;
}

bool hasExtension(const QString &fileName, const QString &ext)
{
    const int dotInd = fileName.size() - ext.size() - 1;

    return ((dotInd >= 0 && fileName.at(dotInd) == _dot)
            && fileName.endsWith(ext, Qt::CaseInsensitive));
}

bool hasExtension(const QString &fileName, const QStringList &extensions)
{
    for (const QString &ext : extensions) {
        if (hasExtension(fileName, ext))
            return true;
    }

    return false;
}

bool hasWindowsRoot(const QString &path)
{
    return path.size() > 1
           && path.at(1) == u':'
           && path.at(0).isLetter();
}

bool isRoot(const QString &path)
{
    switch (path.length()) {
    case 1:
        return (path.at(0) == _sep); // Linux FS root
    case 2:
    case 3:
        return hasWindowsRoot(path); // Windows drive root
    default:
        return false;
    }
}

bool isAbsolute(const QString &path)
{
    return path.startsWith(_sep) || hasWindowsRoot(path);
}

bool isRelative(const QString &path)
{
    return !isAbsolute(path);
}

QString joinStrings(const QString &str1, const QString &str2, QChar sep)
{
    const bool s1Ends = str1.endsWith(sep);
    const bool s2Starts = str2.startsWith(sep);

    if (s1Ends && s2Starts) {
        QStringView chopped = QStringView(str1).left(str1.size() - 1);
        return chopped % str2;
    }

    if (s1Ends || s2Starts)
        return str1 + str2;

    return str1 % sep % str2;
}

} // namespace pathstr
