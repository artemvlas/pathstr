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

/* Joins two path strings with '/' separator, checking that the path separator is not duplicated:
 * joinPath("/absolutePath", "addPath")   -> "/absolutePath/addPath"
 * joinPath("/absolutePath/", "addPath")  -> "/absolutePath/addPath"
 * joinPath("/absolutePath/", "/addPath") -> "/absolutePath/addPath"
 */
QString joinPath(const QString &absolutePath, const QString &addPath);

/* Returns the name of the file system entry (file or folder)
 * regardless of the separator presence at the end of the path:
 * "/folder/entry_name'/'" --> "entry_name"
 */
QString entryName(const QString &path);

/* Returns the path to the parent folder,
 * regardless of the separator presence at the end of the path:
 * "/folder/file_or_folder2'/'" --> "/folder"
 */
QString parentFolder(const QString &path);

// relativePath("/rootFolder", "/rootFolder/folder2/file") -> "folder2/file"
QString relativePath(const QString &rootFolder, const QString &fullPath);

/* replaces intermediate folders with dots
 * "/home"                     -> "/home"
 * "/home/fooFolder/file.txt"  -> "/../../file.txt"
 * "C:/fooFolder"              -> "C:/fooFolder"
 * "C:/fooFolder/file.txt"     -> "C:/../file.txt"
 * "fooFolder/barFolder/"      -> "../barFolder"
 */
QString shortenPath(const QString &path);

// parentFolder/baseName.ext
QString composeFilePath(const QString &parentFolder,
                        const QString &baseName, const QString &ext);

/* Returns the root of an absolute path.
 * "/home/folder" -> "/"
 * "C:/Folder"    -> "C:/"
 */
QString root(const QString &path);

/* Returns the file extension (suffix).
 * "file.txt"     -> "txt"
 * ".hidden_file" -> ""
 */
QString suffix(const QString &fileName);

/* Sets or changes an existing filename suffix
 * setSuffix("file", "zip")     -> "file.zip"
 * setSuffix("file.txt", "zip") -> "file.zip"
 */
QString setSuffix(const QString &fileName, const QString &suf);

/* Returns the size of the suffix.
 * If the file name begins with a dot (Linux hidden file), it matters.
 * "/folder/file.txt" -> 3
 * ".hidden_file" --> 0
 */
int suffixSize(const QString &fileName);

/* true if the 'fileName' (name or path) has the 'ext' suffix
 * hasExtension("file.txt", "txt") -> true
 */
bool hasExtension(const QString &fileName, const QString &ext);

/* true if the 'fileName' have any extension from the list
 * hasExtension("file.txt", {"jpg", "txt", "pdf"}) -> true
 */
bool hasExtension(const QString &fileName, const QStringList &extensions);

// true if starts with "X:"
bool hasWindowsRoot(const QString &path);

// true: "/" or "X:[/]"; else false
bool isRoot(const QString &path);

// true if the 'path' starts with '/' or 'X:'
bool isAbsolute(const QString &path);

// true if the path is not Absolute
bool isRelative(const QString &path);

// true if '/' or '\\'
bool isSeparator(const QChar sep);

// path string ends with a slash ('/' or '\\')
bool endsWithSep(const QString &path);

/*** Additional tools ***/
/* Join strings with the specified separator ('sep'),
 * checks for the absence of 'sep' duplication:
 *
 * joinStrings("string1", "string2", '/')   -> "string1/string2"
 * joinStrings("string1/", "/string2", '/') -> "string1/string2"
 */
QString joinStrings(const QString &str1, const QString &str2, QChar sep);

/*** Constants ***/
static const QChar _sep = u'/';
static const QChar _dot = u'.';

} // namespace pathstr

#endif // PATHSTR_H
