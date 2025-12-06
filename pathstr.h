/*
 ******************************************************************
 * A small library for handling filesystem paths as strings (Qt). *
 *                                                                *
 * artemvlas (at) proton (dot) me                                 *
 * https://github.com/artemvlas/pathstr                           *
 ******************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2021 - present Artem Vlasenko
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef PATHSTR_H
#define PATHSTR_H

#include <QString>

namespace pathstr {
/*** Constants ***/
static const QChar s_sep = u'/';
static const QChar s_dot = u'.';

/* Joins two path strings with '/' separator, checking that the path separator is not duplicated:
 * joinPath("/absolutePath", "addPath")   -> "/absolutePath/addPath"
 * joinPath("/absolutePath/", "addPath")  -> "/absolutePath/addPath"
 * joinPath("/absolutePath/", "/addPath") -> "/absolutePath/addPath"
 * joinPath("C:\\folder\\", "\\folder2")  -> "C:\\folder\\folder2"
 */
QString joinPath(const QString &absolutePath, const QString &addPath);

/* Returns the name of the file system entry (file or folder)
 * regardless of the separator presence at the end of the path:
 * "/folder/fooEntry/"       -> "fooEntry"
 * "/folder/fooEntry"        -> "fooEntry"
 * "/folder/archive.zip"     -> "archive.zip"
 * "/"                       -> "Root"
 * "C:/"                     -> "Drive C"
 */
QString entryName(const QString &path);

/* Returns the file name without path and complete suffix.
 * "/folder/archive.tar.gz"     -> "archive"
 * "/folder/archive.zip"        -> "archive"
 * "file.name.with.dots.tar.gz" -> "file.name.with.dots"
 */
QString baseName(const QString &fileName);

/* Returns the path to the parent folder,
 * regardless of the separator presence at the end of the path:
 * "/folder/file_or_folder2/" -> "/folder"
 * "/folder/file_or_folder2"  -> "/folder"
 * "C:/"                      -> "C:/"
 * "/"                        -> "/"
 * "folder/"                  -> ""
 */
QString parentFolder(const QString &path);

// relativePath("/rootFolder", "/rootFolder/folder2/file") -> "folder2/file"
QString relativePath(const QString &rootFolder, const QString &fullPath);

/* Changes the <oldName> filename, keeping the complete suffix and path unchanged.
 * <oldName> is the file name or path.
 * <newName> is the new file name.
 *
 * "fooFile.txt"             -> "newName.txt"
 * "/folder/archive.tar.gz"  -> "/folder/newName.tar.gz"
 */
QString renameFile(const QString &oldName, const QString &newName);

// parentFolder/baseName.ext
QString composeFilePath(const QString &parentFolder,
                        const QString &baseName, const QString &ext);

/* Returns the root of an absolute path.
 * "/home/folder" -> "/"
 * "C:/folder"    -> "C:/"
 */
QString root(const QString &path);

/* Returns the suffix (extension) of the <fileName>.
 * "file.txt"         -> "txt"
 * "archive.tar.gz"   -> "gz"
 * ".hidden_file"     -> ""
 */
QString suffix(const QString &fileName);

/* Returns the complete suffix (extension) of the <fileName>.
 * The last two dots at most are taken into account.
 *
 * "/folder/archive.tar.gz"     -> "tar.gz"
 * "file.name.with.dots.tar.gz" -> "tar.gz"
 * "/folder/archive.zip"        -> "zip"
 * "folder.name/.archive.zip"   -> "zip"
 */
QString completeSuffix(const QString &fileName);

/* Sets or changes an existing filename suffix
 * setSuffix("file", "zip")     -> "file.zip"
 * setSuffix("file.txt", "zip") -> "file.zip"
 */
QString setSuffix(const QString &fileName, const QString &suf);

/* Returns the size of the suffix.
 * If the file name begins with a dot (Linux hidden file), it matters.
 * "/folder/file.txt" -> 3
 * ".hidden_file"     -> 0
 */
int suffixSize(const QString &fileName);

/* Returns the size of the complete suffix (extension).
 * The last two dots at most are taken into account.
 *
 * "/folder/archive.tar.gz"     -> 6
 * "file.name.with.dots.tar.gz" -> 6
 * "/folder/archive.zip"        -> 3
 */
int completeSuffixSize(const QString &fileName);

/* True if the <fileName> string has the <ext> suffix
 * hasExtension("file.txt", "txt") -> true
 * hasExtension("file.txt", "cpp") -> false
 */
bool hasExtension(const QString &fileName, const QString &ext);

/* True if the <fileName> has any extension from the list.
 * hasExtension("file.txt", {"jpg", "txt", "json"}) -> true
 * hasExtension("file.txt", {"zip", "cpp", "epub"}) -> false
 */
bool hasExtension(const QString &fileName, const QStringList &extensions);

// true if starts with "X:"
bool hasWindowsRoot(const QString &path);

// true: "/" or "X:[/]"; else false
bool isRoot(const QString &path);

// true if the <path> starts with '/' or 'X:'
bool isAbsolute(const QString &path);

// true if the path is not Absolute
bool isRelative(const QString &path);

// true if '/' or '\\'
inline bool isSeparator(const QChar sep)
{
    return (sep == s_sep) || (sep == '\\');
}

// true if <path> string ends with a slash or backslash (path separator '/' or '\\')
inline bool endsWithSep(const QString &path)
{
    return !path.isEmpty() && isSeparator(path.back());
}

// ...starts with
inline bool startsWithSep(const QString &path)
{
    return !path.isEmpty() && isSeparator(path.front());
}

// Appends '/' if not any
inline QString appendSep(const QString &path)
{
    return path.endsWith(s_sep) ? path : path + s_sep;
}

// If the <path> ends with a separator, remove it
inline QString chopSep(const QString &path)
{
    return endsWithSep(path) ? path.chopped(1) : path;
}

/*** Additional tools ***/
/* Join strings with the specified separator ('sep'),
 * checks for the absence of 'sep' duplication:
 *
 * joinStrings("string1", "string2", '/')   -> "string1/string2"
 * joinStrings("string1/", "/string2", '/') -> "string1/string2"
 */
QString joinStrings(const QString &str1, const QString &str2, QChar sep);

} // namespace pathstr

#endif // PATHSTR_H
